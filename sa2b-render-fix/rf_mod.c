#include <samt/core.h>
#include <samt/memory.h>
#include <samt/funchook.h>

#include <samt/ninja/ninja.h>

/** GX **/
#define SAMT_INCL_FUNCPTRS
#include <samt/gx/gx.h>
#undef  SAMT_INCL_FUNCPTRS

/****** SOC *************************************************************************/
#include <samt/soc/shader.h>    /* setshader                                        */

/** Render Fix **/
#include <rf_core.h>
#include <rf_shader.h>

/** DX9 Control **/
#include <dx9ctrl/dx9ctrl.h>

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

static s32      ModBufferInitTriNum     = NB_MOD_TRI;

//static MOD_TRI* ModBuffer;
//static s32      ModBufferNum;
//static s32      ModBufferMax;

static s16      ModDrawShadow;

void
rjClearModVertexBuffer(void);

void
RFMOD_ClearBuffer(void)
{
    rjClearModVertexBuffer();

    //ModBufferNum = 0;
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

void
RFMOD_SetDrawMode(RFE_MOD_MODE mode)
{
    ModMode = mode;
}


//MOD_TRI*
//RFMOD_GetBuffer(s32 nbTri)
//{
//    const s32 buf_cur = ModBufferNum;
//
//    const s32 buf_top = nbTri + buf_cur;
//
//    if (buf_top >= ModBufferMax)
//    {
//        OutputString("RFDBG: Modifier buffer is full!");
//        return nullptr;
//    }
//
//    ModBufferNum = buf_top;
//
//    return &ModBuffer[buf_cur];
//}

//static void
//DrawModifierList(void)
//{
//    DX9_DrawPrimitive(DX9_PRITYPE_TRIANGLELIST, ModBufferNum, ModBuffer, sizeof(NJS_POINT3));
//}

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
    DX9_SaveZEnableState();
    DX9_SaveStencilTwoSidedState();
    DX9_SaveAlphaBlendEnableState();
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
    DX9_LoadZEnableState();
    DX9_LoadStencilTwoSidedState();
    DX9_LoadAlphaBlendEnableState();
}

typedef struct
{
    s16 unk;
    s16 mode;
    NJS_COLOR color;
    f32 far;
    f32 near;
    f32 fogtable[128];
}
FOG_DATA;

#define FogDataP        DATA_REF(FOG_DATA*, 0x01AEFEA4)

static void
LerpModAndFogColor(MOD_COLOR* const pModCol, const NJS_COLOR* const pFogCol, const f32 density)
{
    const f32 inv_density = 1.f - density;

    pModCol->r = (pModCol->r * inv_density) + (((f32)pFogCol->argb.r/255.f) * density);
    pModCol->g = (pModCol->g * inv_density) + (((f32)pFogCol->argb.g/255.f) * density);
    pModCol->b = (pModCol->b * inv_density) + (((f32)pFogCol->argb.b/255.f) * density);
}

static bool
ModSetShaderColor(void)
{
    ___TODO("Remove this flag check, this is probably what's breaking Egg Quaters' water");

    if (FogDataP && ShaderModelMode & SHADERMDL_FLAG_FOG)
    {
        f32 density = (100.f - FogDataP->near) / (FogDataP->far - FogDataP->near);

        if (density <= 0.f)
            goto NO_FOG;
        
        if (density >= 1.f)
            return false;

        switch (FogDataP->mode) {
        case 2:
            density = 1.f - exp2f(-8.f * density);
            break;
        case 3: case 4: case 5:
            density = 1.f - exp2f(-8.f * density * density);
            break;
        }

        MOD_COLOR col = ModColor;

        LerpModAndFogColor(&col, &FogDataP->color, density);

        DX9_SetPxlShaderConstantF(&col, 0, 4);
        return true;
    }

NO_FOG:
    DX9_SetPxlShaderConstantF(&ModColor, 0, 4);
    return true;
}

void
rjRenderModVertexBuffer(void);

static void
DrawBufferFast(void)
{
    /** Early fail if the shadows wouldn't
        be visible in the fog **/
    if ( !ModSetShaderColor() )
        return;

    /****** Initial Setup ******/
    /** Save render state **/
    ModSaveRenderState();

    /** Force Z Func **/
    DX9_SetZFunc(DX9_CMP_LEQ);

    /** Setup shader info **/
    DX9_SetVtxShader(ModVtxShader);
    DX9_SetPxlShader(ModPxlShader);
    DX9_SetVtxDecl(ModVtxDeclaration);

    /** Enable stencil **/
    DX9_SetStencilEnable(true);

    /****** Prep Buffer Write ******/
    /** Alpha blend **/
    DX9_SetAlphaBlendEnable(false);

    /** Color write **/
    DX9_SetColorWrite(DX9_WCOL_NONE);

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
    /** This pass draws both sides of the entire modifier buffer in just one draw
        call. While very fast, it can cause visual bugs in scenarios involving
        inverted modifier models. But that's why we have the new render state! **/
    DX9_SetStencilTwoSided(true);

    DX9_SetStencilFunc(DX9_CMP_ALW);

    DX9_SetStencilWriteMask(STENCIL_BITS_LOW);

    rjRenderModVertexBuffer();

    DX9_SetStencilTwoSided(false);

    /****** Prep Buffer Draw ******/
    /** Alpha blend **/
    DX9_SetAlphaBlendEnable(true);
    DX9_SetSrcBlend(DX9_BLND_SRCALPHA);
    DX9_SetDstBlend(DX9_BLND_INVSRCALPHA);

    /** Color write **/
    DX9_SetColorWrite(
        DX9_WCOL_RED |
        DX9_WCOL_GREEN |
        DX9_WCOL_BLUE
    );

    /** Z buffer **/
    DX9_SetZEnable(false);

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
    DX9_SetAlphaBlendEnable(true);
    DX9_SetSrcBlend(DX9_BLND_SRCALPHA);
    DX9_SetDstBlend(DX9_BLND_INVSRCALPHA);

    /****** Draw the Modifier Buffer ******/
    rjRenderModVertexBuffer();

    /** Load render state **/
    ModLoadRenderState();
}

EXTERN Uint32 _rj_mod_vertex_buffer_num_;

void
RFMOD_DrawBuffer(void)
{
    if (!_rj_mod_vertex_buffer_num_ || !ModDrawShadow) // !ModBufferNum || 
        return;

    switch (ModMode)
    {
        case MODMD_FAST:
        {
            DrawBufferFast();
            break;
        }
        case MODMD_DEBUG:
        {
            DrawBufferDebug();
            break;
        }
    }

    ModDrawShadow = FALSE;
}

void
RFMOD_Suspend(void)
{
    DX9_SetStencilEnable(false);
}

void
RFMOD_Resume(void)
{
    DX9_SetStencilEnable(true);
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

void
rjInitModVertexBuffer(Sint32 size);

static void
RFMOD_CreateBuffer(void)
{
    rjInitModVertexBuffer(0x8000);

    //ModBuffer    = mtAlloc(MOD_TRI, ModBufferInitTriNum);
    //ModBufferMax = ModBufferInitTriNum;
    //ModBufferNum = 0;
}

#define GJD_ALPHAMODE_SOLID (0)
#define GJD_ALPHAMODE_ATEST (1)
#define GJD_ALPHAMODE_BLEND (2)

#define _gj_alpha_mode_     DATA_REF(uint32_t, 0x025EFE50)

s32
ModifierStart(void)
{
    switch (_gj_alpha_mode_)
    {
        case GJD_ALPHAMODE_SOLID:
        {
            if (_nj_control_3d_flag_ & (NJD_CONTROL_3D_SHADOW | NJD_CONTROL_3D_SHADOW_OPAQUE))
            {
                RFMOD_OnShadow();
                return 2;
            }

            return 0;
        }
        case GJD_ALPHAMODE_ATEST:
        {
            if (_nj_control_3d_flag_ & NJD_CONTROL_3D_SHADOW)
            {
                RFMOD_OnShadow();
                return 2;
            }

            return 0;

        }
        case GJD_ALPHAMODE_BLEND: default:
        {
            RFMOD_Suspend();
            return 1;
        }
    }

    return 0;
}

void
ModifierEnd(const s32 i)
{
    switch (i)
    {
        case 1:
        {
            RFMOD_Resume();
            break;
        }
        case 2:
        {
            ModDrawShadow = TRUE;

            RFMOD_OffShadow();
            break;
        }
    }
}

static mt_hookinfo HookInfoGxEnd[1];
static void
GX_EndStencilCheck(void)
{
    const s32 i = ModifierStart();

    FuncHookCall( HookInfoGxEnd, GX_End() );

    ModifierEnd(i);
}

static mt_hookinfo HookInfoGjDraw[1];

#define sub_41BE30      FUNC_PTR(void, __cdecl, (int, char), 0x0041BE30)

static void __cdecl
GjDrawStencilCheck(int a1, char a2)
{
    const s32 i = ModifierStart();

    FuncHookCall( HookInfoGjDraw, sub_41BE30(a1, a2) );

    ModifierEnd(i);
}

/** Extern **/
#define SetIfGreater(_var, _value)  if (_var < _value) _var = _value

void
RFCTRL_SetModBufferSize(s32 nbTri, s32 nbTriList)
{
    SetIfGreater(ModBufferInitTriNum, nbTri);
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
    FuncHook(HookInfoGxEnd , GX_End_p,   GX_EndStencilCheck);
    FuncHook(HookInfoGjDraw, sub_41BE30, GjDrawStencilCheck);
}
