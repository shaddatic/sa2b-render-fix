#include <sa2b/core.h>
#include <sa2b/memory.h>
#include <sa2b/funchook.h>
#include <sa2b/d3dcontrol.h>

#include <sa2b/gx/gx.h>

/** Source **/
#include <sa2b/src/debug.h>

/** Render Fix **/
#include <rf_core.h>
#include <rf_shader.h>

/** Self **/
#include <rf_mod.h>

/** Constants **/
#define STENCIL_BIT_ON      (0b1000'0000)
#define STENCIL_BIT_DRAW    (0b0001'0000)

#define STENCIL_BITS_ALL    (0b1111'1111)
#define STENCIL_BITS_LOW    (0b0000'1111)

#define NB_MOD_TRI          (2048)
#define NB_MOD_TRILIST      ( 128)

typedef struct
{
    NJS_POINT3 vtx[3];
}
MOD_TRI;

typedef struct
{
    uint16_t startTri;
    uint16_t nbTri;
}
MOD_TRILIST;

typedef struct
{
    float32_t r, g, b, a;
}
MOD_COLOR;

static d3d_vtx_shader* ModBasicVtxShader;

static d3d_vtx_shader* ModVtxShader;
static d3d_pxl_shader* ModPxlShader;

static d3d_vtx_declaration* ModVtxDeclaration;

static MOD_COLOR ModColor;

static MOD_TRI* ModBuffer;
static size_t   ModBufferNum;
static size_t   ModBufferMax;

static MOD_TRILIST* ModTriListList;
static size_t       ModTriListNum;
static size_t       ModTriListMax;

void
RFMOD_ClearBuffer()
{
    ModBufferNum = 0;
    ModTriListNum = 0;
}

void
RFMOD_SetColor(float r, float g, float b)
{
    ModColor.r = r;
    ModColor.g = g;
    ModColor.b = b;
}

void
RFMOD_SetAlpha(float a)
{
    ModColor.a = a;
}

#define INV_255     (1.f/255.f);

void
RFMOD_SetColorI(uint8_t r, uint8_t g, uint8_t b)
{
    ModColor.r = (float32_t)r * INV_255;
    ModColor.g = (float32_t)g * INV_255;
    ModColor.b = (float32_t)b * INV_255;
}

void
RFMOD_SetAlphaI(uint8_t a)
{
    ModColor.a = (float32_t)a * INV_255;
}

void
RFMOD_PushPolygon(Sint16* plist, NJS_POINT3* vtxBuf, uint16_t nbPoly)
{
    const size_t stacktop = nbPoly + ModBufferNum;

    if (stacktop >= ModBufferMax)
    {
        OutputDebugString("RFDBG: Modifier buffer is full!");
        return;
    }

    if (ModTriListNum == ModTriListMax)
    {
        OutputDebugString("RFDBG: Modifier tri list list is full!");
        return;
    }

    ModTriListList[ModTriListNum].startTri = (uint16_t)ModBufferNum;
    ModTriListList[ModTriListNum].nbTri    = nbPoly;

    for (size_t i = ModBufferNum; i < stacktop; ++i)
    {
        ModBuffer[i].vtx[0] = vtxBuf[*plist++];
        ModBuffer[i].vtx[1] = vtxBuf[*plist++];
        ModBuffer[i].vtx[2] = vtxBuf[*plist++];
    }

    ModBufferNum = stacktop;
    ++ModTriListNum;
}

void
DrawModifierList(size_t startTri, size_t nbTri)
{
    D3D_DrawPrimitiveUP(D3D_PRIMTYPE_TRIANGLELIST, nbTri, &ModBuffer[startTri], sizeof(NJS_POINT3));
}

static void
DrawScreenQuad()
{
#define MOD_SCREEN_QUAD_NUM     (arylen(ModScreenQuad) - 2)
#define SCREEN_QUAD_Z           (0.5f)

    static const NJS_POINT3 ModScreenQuad[] =
    {
        { -1.0f, -1.0f, SCREEN_QUAD_Z },
        {  1.0f, -1.0f, SCREEN_QUAD_Z },
        { -1.0f,  1.0f, SCREEN_QUAD_Z },
        {  1.0f,  1.0f, SCREEN_QUAD_Z },
    };

    D3D_DrawPrimitiveUP(D3D_PRIMTYPE_TRIANGLESTRIP, MOD_SCREEN_QUAD_NUM, ModScreenQuad, sizeof(NJS_POINT3));

#undef  SCREEN_QUAD_Z
#undef  MOD_SCREEN_QUAD_NUM
}

//#define MOD_MDL_DEBUG

void
RFMOD_DrawBuffer()
{
    if (!ModBufferNum)
        return;

    /****** Initial Setup ******/
    /** Save render state **/
    D3D_SaveVertexShader();
    D3D_SavePixelShader();
    D3D_SaveVertexDecl();
    D3D_SaveColorWriteState();
    D3D_SaveAlphaFunc();
    D3D_SaveSrcBlend();
    D3D_SaveDstBlend();
    D3D_SaveZWriteState();
    D3D_SaveZState();
    D3D_SaveTwoSidedStencilMode();
    D3D_SaveAlphaBlendState();

    /** Setup shader info **/
    D3D_SetVtxShader(ModVtxShader);
    D3D_SetPxlShader(ModPxlShader);
    D3D_SetVtxDeclaration(ModVtxDeclaration);

    D3D_SetPxlShaderConstantF(&ModColor, 0, 4);

    /** Enable stencil **/
    D3D_StencilEnable();

    /****** Prep Buffer Write ******/
    /** Alpha blend **/
    D3D_AlphaBlendDisable();

    /** Color write **/
    D3D_ColorWrite(D3D_COLORWRITE_NONE);

    /** Z buffer **/
    D3D_ZWriteDisable();

    /** Stencil ref **/
    D3D_StencilReference(STENCIL_BIT_DRAW);

    /** Stencil masks **/
    D3D_StencilMask(STENCIL_BITS_LOW);

    /** Stencil ops CW **/
    D3D_StencilFail(D3D_STENCIL_KEEP);
    D3D_StencilZFail(D3D_STENCIL_INCREMENT);
//  D3D_StencilPass(D3D_STENCIL_KEEP);      // Optimization: Set in both passes

    /** Stencil ops CCW **/
    D3D_StencilFailCCW(D3D_STENCIL_KEEP);
    D3D_StencilZFailCCW(D3D_STENCIL_DECREMENT);
    D3D_StencilPassCCW(D3D_STENCIL_KEEP);

    MOD_TRILIST* tri_lists = ModTriListList;

    /****** Write to the Stencil Buffer ******/
    for (size_t i = 0; i < ModTriListNum; ++i, ++tri_lists)
    {
        /****** 1st pass: ******/
        /** This pass draws both sides of the current modifier
            and incs/decs the lower half of the stencil buffer **/

        D3D_StencilTwoSidedEnable();

        D3D_ZReadEnable();

        D3D_StencilFunc(D3D_COMPARE_ALWAYS);

        D3D_StencilWriteMask(STENCIL_BITS_LOW);

        D3D_StencilPass(D3D_STENCIL_KEEP);

        DrawModifierList(tri_lists->startTri, tri_lists->nbTri);

        /****** 2nd pass: ******/
        /** This pass draws both sides of the current modifier
            again, but disables the Z buffer and sets the draw
            flag to '1' if the lower half of the stencil buffer isn't 0.
            It then resets the lower half state back to 0 **/

        D3D_StencilTwoSidedDisable();

        D3D_ZReadDisable();

        D3D_StencilFunc(D3D_COMPARE_NOT_EQUAL);

        D3D_StencilWriteMask(STENCIL_BIT_DRAW | STENCIL_BITS_LOW);

        D3D_StencilPass(D3D_STENCIL_REPLACE);

        DrawModifierList(tri_lists->startTri, tri_lists->nbTri);
    }

    /****** Prep Buffer Draw ******/
    /** Alpha blend **/
    D3D_AlphaBlendEnable();
    D3D_SrcBlend(D3D_BLEND_SRCALPHA);
    D3D_DstBlend(D3D_BLEND_INVSRCALPHA);

    /** Color write **/
    D3D_ColorWrite(
        D3D_COLORWRITE_RED |
        D3D_COLORWRITE_GREEN |
        D3D_COLORWRITE_BLUE
    );

    /** Z buffer **/
    D3D_ZReadDisable();

    /** Stencil ref **/
    D3D_StencilReference(STENCIL_BIT_ON | STENCIL_BIT_DRAW);

    /** Stencil masks **/
    D3D_StencilMask(STENCIL_BIT_ON | STENCIL_BIT_DRAW);
    D3D_StencilWriteMask(STENCIL_BITS_ALL);

    /** Stencil compare **/
    D3D_StencilFunc(D3D_COMPARE_EQUAL);

    /** Stencil ops **/
    D3D_StencilFail(D3D_STENCIL_ZERO);
    D3D_StencilZFail(D3D_STENCIL_ZERO);
    D3D_StencilPass(D3D_STENCIL_ZERO);

    /****** Draw the Stencil Buffer ******/
    D3D_SetVtxShader(ModBasicVtxShader);
    DrawScreenQuad();

    /****** End Draw Buffer ******/
    /** Restore stencil state **/
    D3D_StencilReference(STENCIL_BIT_ON);
    D3D_StencilMask(STENCIL_BITS_ALL);
    D3D_StencilFunc(D3D_COMPARE_ALWAYS);
    D3D_StencilFail(D3D_STENCIL_KEEP);
    D3D_StencilZFail(D3D_STENCIL_KEEP);
    D3D_StencilPass(D3D_STENCIL_ZERO);

    /** Load render state **/
    D3D_LoadVertexShader();
    D3D_LoadPixelShader();
    D3D_LoadVertexDecl();
    D3D_LoadColorWriteState();
    D3D_LoadAlphaFunc();
    D3D_LoadSrcBlend();
    D3D_LoadDstBlend();
    D3D_LoadZWriteState();
    D3D_LoadZState();
    D3D_LoadTwoSidedStencilMode();
    D3D_LoadAlphaBlendState();
}

void
RFMOD_Suspend()
{
    D3D_StencilDisable();
}

void
RFMOD_Resume()
{
    D3D_StencilEnable();
}

void
RFMOD_OnShadow()
{
    D3D_StencilPass(D3D_STENCIL_REPLACE);
}

void
RFMOD_OffShadow()
{
    D3D_StencilPass(D3D_STENCIL_ZERO);
}

void
RFMOD_CreateBuffer(size_t nbTri, size_t nbTriList)
{
    if (ModBuffer)
        MemFree(ModBuffer);

    ModBuffer = mAlloc(MOD_TRI, nbTri);
    ModBufferMax = nbTri;
    ModBufferNum = 0;

    if (ModTriListList)
        MemFree(ModTriListList);

    ModTriListList = mAlloc(MOD_TRILIST, nbTriList);
    ModTriListMax = nbTriList;
    ModTriListNum = 0;
}

#define GJD_ALPHAMODE_SOLID (0)
#define GJD_ALPHAMODE_ATEST (1)
#define GJD_ALPHAMODE_BLEND (2)

#define _gj_alpha_mode_     DataRef(uint32_t, 0x025EFE50)

static hook_info* HookInfoGxEnd;

static void
GX_EndStencilCheck()
{
    int i = 0;

    if (_gj_alpha_mode_ == GJD_ALPHAMODE_BLEND)
    {
        RFMOD_Suspend();
        i = 1;
    }
    else if (_nj_control_3d_flag_ & NJD_CONTROL_3D_SHADOW)
    {
        RFMOD_OnShadow();
        i = 2;
    }

    FuncHookCall( HookInfoGxEnd, GX_End() );

    switch (i) {
    case 1:
        RFMOD_Resume();
        break;

    case 2:
        RFMOD_OffShadow();
        break;
    }
}

static hook_info* HookInfoGjDraw;

#define sub_41BE30      FuncPtr(void, __cdecl, (int, char), 0x0041BE30)

static void __cdecl
GjDrawStencilCheck(int a1, char a2)
{
    int i = 0;

    if (_gj_alpha_mode_ == GJD_ALPHAMODE_BLEND)
    {
        RFMOD_Suspend();
        i = 1;
    }
    else if (_nj_control_3d_flag_ & NJD_CONTROL_3D_SHADOW)
    {
        RFMOD_OnShadow();
        i = 2;
    }

    FuncHookCall( HookInfoGjDraw, sub_41BE30(a1, a2) );

    switch (i) {
    case 1:
        RFMOD_Resume();
        break;

    case 2:
        RFMOD_OffShadow();
        break;
    }
}

void
RFMOD_Init()
{
    ModBasicVtxShader = RF_LoadVtxShader("basic_vs");

    ModVtxShader = RF_LoadVtxShader("stencil_vs");
    ModPxlShader = RF_LoadPxlShader("stencil_ps");

    const d3d_vtx_element vtx_ele_list[] =
    {
        { 0, 0, D3D_VTXELE_TYPE_FLOAT3, D3D_VTXELE_METHOD_DEFAULT, D3D_VTXELE_USAGE_POSITION, 0 },
        D3D_VTXELE_END()
    };

    ModVtxDeclaration = D3D_CreateVtxDeclaration(vtx_ele_list);

    RFMOD_CreateBuffer(NB_MOD_TRI, NB_MOD_TRILIST);

    /** Draw hooks **/
    HookInfoGxEnd  = FuncHook(0x0041C070, GX_EndStencilCheck);
    HookInfoGjDraw = FuncHook(sub_41BE30, GjDrawStencilCheck);
}
