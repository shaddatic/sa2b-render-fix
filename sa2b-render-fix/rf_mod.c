#include <sa2b/core.h>
#include <sa2b/memory.h>
#include <sa2b/funchook.h>
#include <sa2b/dx9ctrl.h>

/** GX **/
#define SAMT_INCL_FUNCPTRS
#include <sa2b/gx/gx.h>
#undef  SAMT_INCL_FUNCPTRS

/** Source **/
#include <sa2b/sonic/debug.h>

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
    f32 r, g, b, a;
}
MOD_COLOR;

static RFE_MOD_MODE ModMode;

static dx9_vtx_shader* ModBasicVtxShader;

static dx9_vtx_shader* ModVtxShader;
static dx9_pxl_shader* ModPxlShader;

static dx9_vtx_decl* ModVtxDeclaration;

static MOD_COLOR ModColor;

static size_t   ModBufferInitTriNum     = NB_MOD_TRI;
static size_t   ModBufferInitTriListNum = NB_MOD_TRILIST;

static MOD_TRI* ModBuffer;
static size_t   ModBufferNum;
static size_t   ModBufferMax;

static MOD_TRILIST* ModTriListList;
static size_t       ModTriListNum;
static size_t       ModTriListMax;

void
RFMOD_ClearBuffer(void)
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
    ModColor.r = (f32)r * INV_255;
    ModColor.g = (f32)g * INV_255;
    ModColor.b = (f32)b * INV_255;
}

void
RFMOD_SetAlphaI(uint8_t a)
{
    ModColor.a = (f32)a * INV_255;
}

void
RFMOD_SetDrawMode(RFE_MOD_MODE mode)
{
    ModMode = mode;
}

void
RFMOD_PushPolygon(Sint16* plist, NJS_POINT3* vtxBuf, uint16_t nbPoly)
{
    const size_t stacktop = nbPoly + ModBufferNum;

    if (stacktop >= ModBufferMax)
    {
        OutputString("RFDBG: Modifier buffer is full!");
        return;
    }

    if (ModTriListNum == ModTriListMax)
    {
        OutputString("RFDBG: Modifier tri list list is full!");
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

static void
DrawModifierList(size_t startTri, size_t nbTri)
{
    DX9_DrawPrimitiveUP(DX9_PRITYPE_TRIANGLELIST, nbTri, &ModBuffer[startTri], sizeof(NJS_POINT3));
}

static void
DrawScreenQuad(void)
{
#   define MOD_SCREEN_QUAD_NUM     (ARYLEN(ModScreenQuad) - 2)
#   define SCREEN_QUAD_Z           (0.5f)

    static const NJS_POINT3 ModScreenQuad[] =
    {
        { -1.0f, -1.0f, SCREEN_QUAD_Z },
        {  1.0f, -1.0f, SCREEN_QUAD_Z },
        { -1.0f,  1.0f, SCREEN_QUAD_Z },
        {  1.0f,  1.0f, SCREEN_QUAD_Z },
    };

    DX9_DrawPrimitiveUP(DX9_PRITYPE_TRIANGLESTRIP, MOD_SCREEN_QUAD_NUM, ModScreenQuad, sizeof(NJS_POINT3));

#   undef  SCREEN_QUAD_Z
#   undef  MOD_SCREEN_QUAD_NUM
}

//#define MOD_MDL_DEBUG

static void
ModSaveRenderState(void)
{
    DX9_SaveVtxShaderState();
    DX9_SavePxlShaderState();
    DX9_SaveVtxDeclState();
    DX9_SaveColorWriteState();
    DX9_SaveAlphaFuncState();
    DX9_SaveSrcBlendState();
    DX9_SaveDstBlendState();
    DX9_SaveZWriteState();
    DX9_SaveZReadState();
    DX9_SaveStencilTwoSidedState();
    DX9_SaveAlphaBlendState();
}

static void
ModLoadRenderState(void)
{
    DX9_LoadVtxShaderState();
    DX9_LoadPxlShaderState();
    DX9_LoadVtxDeclState();
    DX9_LoadColorWriteState();
    DX9_LoadAlphaFuncState();
    DX9_LoadSrcBlendState();
    DX9_LoadDstBlendState();
    DX9_LoadZWriteState();
    DX9_LoadZReadState();
    DX9_LoadStencilTwoSidedState();
    DX9_LoadAlphaBlendState();
}

static void
DrawBufferAccurate(void)
{
    /****** Initial Setup ******/
    /** Save render state **/
    ModSaveRenderState();

    /** Setup shader info **/
    DX9_SetVtxShader(ModVtxShader);
    DX9_SetPxlShader(ModPxlShader);
    DX9_SetVtxDecl(ModVtxDeclaration);

    DX9_SetPxlShaderConstantF(&ModColor, 0, 4);

    /** Enable stencil **/
    DX9_SetStencil(true);

    /****** Prep Buffer Write ******/
    /** Alpha blend **/
    DX9_SetAlphaBlend(false);

    /** Color write **/
    DX9_SetColorWrite(DX9_COL_NONE);

    /** Z buffer **/
    DX9_SetZWrite(false);

    /** Stencil ref **/
    DX9_SetStencilRef(STENCIL_BIT_DRAW);

    /** Stencil masks **/
    DX9_SetStencilReadMask(STENCIL_BITS_LOW);

    /** Stencil ops CW **/
    DX9_SetStencilFail(DX9_STCL_KEEP);
    DX9_SetStencilZFail(DX9_STCL_INCR);
//  DX9_SetStencilPass(DX9_STCL_KEEP);      // Optimization: Set in both passes

        /** Stencil ops CCW **/
    DX9_SetStencilFailCCW(DX9_STCL_KEEP);
    DX9_SetStencilZFailCCW(DX9_STCL_DECR);
    DX9_SetStencilPassCCW(DX9_STCL_KEEP);

    MOD_TRILIST* tri_lists = ModTriListList;

    /****** Write to the Stencil Buffer ******/
    for (size_t i = 0; i < ModTriListNum; ++i, ++tri_lists)
    {
        /****** 1st pass: ******/
        /** This pass draws both sides of the current modifier
            and incs/decs the lower half of the stencil buffer **/

        DX9_SetStencilTwoSided(true);

        DX9_SetZRead(true);

        DX9_SetStencilFunc(DX9_CMP_ALW);

        DX9_SetStencilWriteMask(STENCIL_BITS_LOW);

        DX9_SetStencilPass(DX9_STCL_KEEP);

        DrawModifierList(tri_lists->startTri, tri_lists->nbTri);

        /****** 2nd pass: ******/
        /** This pass draws both sides of the current modifier
            again, but disables the Z buffer and sets the draw
            flag to '1' if the lower half of the stencil buffer isn't 0.
            It then resets the lower half state back to 0 **/

        DX9_SetStencilTwoSided(false);

        DX9_SetZRead(false);

        DX9_SetStencilFunc(DX9_CMP_NEQ);

        DX9_SetStencilWriteMask(STENCIL_BIT_DRAW | STENCIL_BITS_LOW);

        DX9_SetStencilPass(DX9_STCL_REPL);

        DrawModifierList(tri_lists->startTri, tri_lists->nbTri);
    }

    /****** Prep Buffer Draw ******/
    /** Alpha blend **/
    DX9_SetAlphaBlend(true);
    DX9_SetSrcBlend(DX9_BLND_SRCALPHA);
    DX9_SetDstBlend(DX9_BLND_INVSRCALPHA);

    /** Color write **/
    DX9_SetColorWrite(
        DX9_COL_RED |
        DX9_COL_GREEN |
        DX9_COL_BLUE
    );

    /** Z buffer **/
    DX9_SetZRead(false);

    /** Stencil ref **/
    DX9_SetStencilRef(STENCIL_BIT_ON | STENCIL_BIT_DRAW);

    /** Stencil masks **/
    DX9_SetStencilReadMask(STENCIL_BIT_ON | STENCIL_BIT_DRAW);
    DX9_SetStencilWriteMask(STENCIL_BITS_ALL);

    /** Stencil compare **/
    DX9_SetStencilFunc(DX9_CMP_EQU);

    /** Stencil ops **/
    DX9_SetStencilFail(DX9_STCL_ZERO);
    DX9_SetStencilZFail(DX9_STCL_ZERO);
    DX9_SetStencilPass(DX9_STCL_ZERO);

    /****** Draw the Stencil Buffer ******/
    DX9_SetVtxShader(ModBasicVtxShader);
    DrawScreenQuad();

    /****** End Draw Buffer ******/
    /** Restore stencil state **/
    DX9_SetStencilRef(STENCIL_BIT_ON);
    DX9_SetStencilReadMask(STENCIL_BITS_ALL);
    DX9_SetStencilFunc(DX9_CMP_ALW);
    DX9_SetStencilFail(DX9_STCL_KEEP);
    DX9_SetStencilZFail(DX9_STCL_KEEP);
    DX9_SetStencilPass(DX9_STCL_ZERO);

    /** Load render state **/
    ModLoadRenderState();
}

static void
DrawBufferFast(void)
{
    /****** Initial Setup ******/
    /** Save render state **/
    ModSaveRenderState();

    /** Setup shader info **/
    DX9_SetVtxShader(ModVtxShader);
    DX9_SetPxlShader(ModPxlShader);
    DX9_SetVtxDecl(ModVtxDeclaration);

    DX9_SetPxlShaderConstantF(&ModColor, 0, 4);

    /** Enable stencil **/
    DX9_SetStencil(true);

    /****** Prep Buffer Write ******/
    /** Alpha blend **/
    DX9_SetAlphaBlend(false);

    /** Color write **/
    DX9_SetColorWrite(DX9_COL_NONE);

    /** Z buffer **/
    DX9_SetZWrite(false);

    /** Stencil ref **/
    DX9_SetStencilRef(STENCIL_BIT_DRAW);

    /** Stencil masks **/
    DX9_SetStencilReadMask(STENCIL_BITS_LOW);

    /** Stencil ops CW **/
    DX9_SetStencilFail(DX9_STCL_KEEP);
    DX9_SetStencilZFail(DX9_STCL_INCR);
    DX9_SetStencilPass(DX9_STCL_KEEP);

    /** Stencil ops CCW **/
    DX9_SetStencilFailCCW(DX9_STCL_KEEP);
    DX9_SetStencilZFailCCW(DX9_STCL_DECR);
    DX9_SetStencilPassCCW(DX9_STCL_KEEP);

    /****** Write to the Stencil Buffer ******/
    /****** 1st pass: ******/
    /** This pass draws both sides of the entire modifier
        buffer in just one draw call. While very fast, it
        causes visual bugs in scenarios involving inverted
        modifier models. **/
    DX9_SetStencilTwoSided(true);

    DX9_SetStencilFunc(DX9_CMP_ALW);

    DX9_SetStencilWriteMask(STENCIL_BITS_LOW);

    DrawModifierList(0, ModBufferNum);

    DX9_SetStencilTwoSided(false);

    /****** Prep Buffer Draw ******/
    /** Alpha blend **/
    DX9_SetAlphaBlend(true);
    DX9_SetSrcBlend(DX9_BLND_SRCALPHA);
    DX9_SetDstBlend(DX9_BLND_INVSRCALPHA);

    /** Color write **/
    DX9_SetColorWrite(
        DX9_COL_RED |
        DX9_COL_GREEN |
        DX9_COL_BLUE
    );

    /** Z buffer **/
    DX9_SetZRead(false);

    /** Stencil ref **/
    DX9_SetStencilRef(STENCIL_BIT_ON | STENCIL_BIT_DRAW);

    /** Stencil masks **/
    DX9_SetStencilReadMask(STENCIL_BIT_ON | STENCIL_BITS_LOW);
    DX9_SetStencilWriteMask(STENCIL_BITS_ALL);

    /** Stencil compare **/
    DX9_SetStencilFunc(DX9_CMP_LSS);

    /** Stencil ops **/
    DX9_SetStencilFail(DX9_STCL_ZERO);
    DX9_SetStencilZFail(DX9_STCL_ZERO);
    DX9_SetStencilPass(DX9_STCL_ZERO);

    /****** Draw the Stencil Buffer ******/
    DX9_SetVtxShader(ModBasicVtxShader);
    DrawScreenQuad();

    /****** End Draw Buffer ******/
    /** Restore stencil state **/
    DX9_SetStencilRef(STENCIL_BIT_ON);
    DX9_SetStencilReadMask(STENCIL_BITS_ALL);
    DX9_SetStencilFunc(DX9_CMP_ALW);
    DX9_SetStencilFail(DX9_STCL_KEEP);
    DX9_SetStencilZFail(DX9_STCL_KEEP);
    DX9_SetStencilPass(DX9_STCL_ZERO);

    /** Load render state **/
    ModLoadRenderState();
}

static void
DrawBufferDebug(void)
{
    /****** Initial Setup ******/
    /** Save render state **/
    ModSaveRenderState();

    /** Setup shader info **/
    DX9_SetVtxShader(ModVtxShader);
    DX9_SetPxlShader(ModPxlShader);
    DX9_SetVtxDecl(ModVtxDeclaration);

    DX9_SetPxlShaderConstantF(&ModColor, 0, 4);

    /****** Prep Buffer Write ******/
    /** Z buffer **/
    DX9_SetZWrite(false);

    /****** Prep Buffer Draw ******/
    /** Alpha blend **/
    DX9_SetAlphaBlend(true);
    DX9_SetSrcBlend(DX9_BLND_SRCALPHA);
    DX9_SetDstBlend(DX9_BLND_INVSRCALPHA);

    /****** Draw the Modifier Buffer ******/
    DrawModifierList(0, ModBufferNum);

    /** Load render state **/
    ModLoadRenderState();
}

void
RFMOD_DrawBuffer(void)
{
    if (!ModBufferNum)
        return;

    switch (ModMode) {
    case MODMD_ACCURATE:
        DrawBufferAccurate();
        break;

    case MODMD_FAST:
        DrawBufferFast();
        break;

    case MODMD_DEBUG:
        DrawBufferDebug();
        break;
    }
}

void
RFMOD_Suspend(void)
{
    DX9_SetStencil(false);
}

void
RFMOD_Resume(void)
{
    DX9_SetStencil(true);
}

void
RFMOD_OnShadow(void)
{
    DX9_SetStencilPass(DX9_STCL_REPL);
}

void
RFMOD_OffShadow(void)
{
    DX9_SetStencilPass(DX9_STCL_ZERO);
}

static void
RFMOD_CreateBuffer(void)
{
    ModBuffer    = mAlloc(MOD_TRI, ModBufferInitTriNum);
    ModBufferMax = ModBufferInitTriNum;
    ModBufferNum = 0;

    ModTriListList = mAlloc(MOD_TRILIST, ModBufferInitTriListNum);
    ModTriListMax  = ModBufferInitTriListNum;
    ModTriListNum  = 0;
}

#define GJD_ALPHAMODE_SOLID (0)
#define GJD_ALPHAMODE_ATEST (1)
#define GJD_ALPHAMODE_BLEND (2)

#define _gj_alpha_mode_     DATA_REF(uint32_t, 0x025EFE50)

static hook_info* HookInfoGxEnd;

static void
GX_EndStencilCheck(void)
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

#define sub_41BE30      FUNC_PTR(void, __cdecl, (int, char), 0x0041BE30)

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

/** Extern **/
#define SetIfGreater(_var, _value)  if (_var < _value) _var = _value

void
RFCTRL_SetModBufferSize(size_t nbTri, size_t nbTriList)
{
    SetIfGreater(ModBufferInitTriNum    , nbTri);
    SetIfGreater(ModBufferInitTriListNum, nbTriList);
}

void
RFMOD_Init(void)
{
    ModBasicVtxShader = RF_LoadVtxShader("basic_vs");

    ModVtxShader = RF_LoadVtxShader("stencil_vs");
    ModPxlShader = RF_LoadPxlShader("stencil_ps");

    const dx9_vtx_elem vtx_ele_list[] =
    {
        { 0, 0, DX9_VTXTYPE_FLOAT3, DX9_VTXMETH_DEFAULT, DX9_VTXUSE_POSITION, 0 },
        DX9_VTX_ELEM_END()
    };

    ModVtxDeclaration = DX9_CreateVtxDecl(vtx_ele_list);

    RFMOD_CreateBuffer();

    /** Draw hooks **/
    HookInfoGxEnd  = FuncHook(GX_End_p,   GX_EndStencilCheck);
    HookInfoGjDraw = FuncHook(sub_41BE30, GjDrawStencilCheck);
}
