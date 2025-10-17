/********************************/
/*  Includes                    */
/********************************/
/****** Core Toolkit ****************************************************************************/
#include <samt/core.h>              /* core                                                     */
#include <samt/writeop.h>           /* WriteJump                                                */
#include <samt/funchook.h>          /* function hook                                            */

/****** SoC *************************************************************************************/
#include <samt/soc/shader.h>        /* shader flags                                             */

/****** Ninja ***********************************************************************************/
#include <samt/ninja/ninja.h>       /* ninja                                                    */
#include <samt/ninja/njcontext.h>   /* ninja context                                            */

/****** Game ************************************************************************************/
#include <samt/sonic/display.h>     /* resolution                                               */
#include <samt/sonic/fog.h>         /* fog */

/****** Render Fix ******************************************************************************/
#include <rf_core.h>                /* core                                                     */

/****** DX9 Control *****************************************************************************/
#include <dx9ctrl/dx9ctrl.h>        /* renderstate                                              */

/****** Self ************************************************************************************/
#include <rf_ninja/rj_internal.h>   /* parent & siblings                                        */

/********************************/
/*  Constants                   */
/********************************/
/****** Static **********************************************************************************/
#define STENCIL_BIT_ON      (0b1000'0000)
#define STENCIL_BIT_DRAW    (0b0001'0000)

#define STENCIL_BITS_ALL    (0b1111'1111)
#define STENCIL_BITS_LOW    (0b0000'1111)

/********************************/
/*  Game Defs                   */
/********************************/
/****** Static **********************************************************************************/
#define GX_End_p                    FUNC_PTR(void, __cdecl, (void)     , 0x0041C070)
#define GX_EndOther_p               FUNC_PTR(void, __cdecl, (int, char), 0x0041BE30)

/********************************/
/*  Data                        */
/********************************/
/****** Static **********************************************************************************/
static bool _rj_shadow_lock_;       /* draw lock for cheap shadow                               */

/****** Static **********************************************************************************/
static Bool     _rj_shadow_debug_;  /* cheap shadow debug draw                                  */
static RJS_RGBA _rj_shadow_color_;  /* cheap shadow color (and shadow tex)                      */

/********************************/
/*  Source                      */
/********************************/
/****** Static **********************************************************************************/
static inline void
ModifierSuspend(void)
{
    DX9_SetStencilEnable(false);
}

static inline void
ModifierResume(void)
{
    DX9_SetStencilEnable(true);
}

static inline void
ModifierOnShadow(void)
{
    DX9_SetStencilPass(DX9_STCL_REPL);
}

static inline void
ModifierOffShadow(void)
{
    DX9_SetStencilPass(DX9_STCL_ZERO);
}

/****** Modifier Draw ***************************************************************************/
static void
LerpModAndFogColor(RJS_RGBA* const pInOutColor, const NJS_COLOR pFogCol, const f32 density)
{
    const f32 inv_density = 1.f - density;

    pInOutColor->r = (pInOutColor->r * inv_density) + (((f32)pFogCol.argb.r/255.f) * density);
    pInOutColor->g = (pInOutColor->g * inv_density) + (((f32)pFogCol.argb.g/255.f) * density);
    pInOutColor->b = (pInOutColor->b * inv_density) + (((f32)pFogCol.argb.b/255.f) * density);
}

static bool
ModifierSetFogColor_Sub(Int mode, NJS_COLOR color, Float far, Float near)
{
    if ( mode != FOG_MD_OFF )
    {
        f32 density = (100.f - near) / (far - near);

        if ( density <= 0.f )
        {
            goto NO_FOG;
        }

        if ( density >= 1.f )
        {
            return false;
        }

        switch ( mode )
        {
            case FOG_MD_EXPONENT:
            {
                density = 1.f - exp2f(-8.f * density);
                break;
            }
            case FOG_MD_EXPONENT2:
            case FOG_MD_REVEXPONENT: case FOG_MD_REVEXPONENT2:
            {
                density = 1.f - exp2f(-8.f * density * density);
                break;
            }
        }

        RJS_RGBA col = _rj_shadow_color_;

        LerpModAndFogColor(&col, color, density);

        DX9_SetPxlShaderConstantF( 0, (dx9_float4*)&col, 1 );
        return true;
    }

NO_FOG:
    DX9_SetPxlShaderConstantF( 0, (dx9_float4*)&_rj_shadow_color_, 1 );
    return true;
}

static bool
ModifierSetFogColor_Multi(void)
{
    const FOG_DATA* restrict p_foga = FogWork.pFogA;
    const FOG_DATA* restrict p_fogb = FogWork.pFogB;

    const Float n_ratio = FogWork.ratio;
    const Float i_ratio = 1.f - n_ratio;

    const NJS_COLOR color =
    {
        .argb.b = (Uint8)( ((f32)p_foga->color.argb.b * i_ratio) + ((f32)p_fogb->color.argb.b * n_ratio) ),
        .argb.g = (Uint8)( ((f32)p_foga->color.argb.g * i_ratio) + ((f32)p_fogb->color.argb.g * n_ratio) ),
        .argb.r = (Uint8)( ((f32)p_foga->color.argb.r * i_ratio) + ((f32)p_fogb->color.argb.r * n_ratio) ),
        .argb.a = (Uint8)( ((f32)p_foga->color.argb.a * i_ratio) + ((f32)p_fogb->color.argb.a * n_ratio) ),
    };

    const Float far  = (p_foga->far  * i_ratio) + (p_fogb->far  * n_ratio);
    const Float near = (p_foga->near * i_ratio) + (p_fogb->near * n_ratio);

    return ModifierSetFogColor_Sub( p_foga->mode, color, far, near );
}

static bool
ModifierSetFogColor_Single(void)
{
    const FOG_DATA* restrict p_foga = FogWork.pFogA;

    return ModifierSetFogColor_Sub( p_foga->mode, p_foga->color, p_foga->far, p_foga->near );
}

static bool
ModSetShaderColor(void)
{
    if ( (ShaderModelMode & SHADERMDL_FLAG_FOG) && FogWork.pFogA )
    {
        if ( FogWork.pFogB )
        {
            return ModifierSetFogColor_Multi();
        }

        return ModifierSetFogColor_Single();
    }

    DX9_SetPxlShaderConstantF( 0, (dx9_float4*)&_rj_shadow_color_, 1 );
    return true;
}

static void
ModifierDrawFast(void)
{
    if ( !ModSetShaderColor() )
    {
        return;
    }

    /****** Initial Setup ******/

    /** Force Z Func **/
    DX9_SetZFunc(DX9_CMP_LEQ);

    /** Enable stencil **/
    DX9_SetStencilEnable(true);

    /****** Prep Buffer Write ******/
    /** Alpha blend **/
    rjSetAlphaMode(RJ_BLEND_SRCALPHA, RJ_BLEND_INVSRCALPHA, RJ_ALPHA_OPAQUE);

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

    rjModifierDrawBuffer();

    DX9_SetStencilTwoSided(false);

    /****** Prep Buffer Draw ******/
    /** Alpha blend **/
    rjSetAlphaMode(RJ_BLEND_SRCALPHA, RJ_BLEND_INVSRCALPHA, RJ_ALPHA_TRANSLUCENT);

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
    rjModifierDrawBuffer();

    /****** End Draw Buffer ******/
    /** Restore stencil state **/
    DX9_SetStencilRef(STENCIL_BIT_ON);
    DX9_SetStencilReadMask(STENCIL_BITS_ALL);
    DX9_SetStencilFunc(DX9_CMP_ALW);
    DX9_SetStencilFail(DX9_STCL_KEEP);
    DX9_SetStencilZFail(DX9_STCL_KEEP);
    DX9_SetStencilPass(DX9_STCL_ZERO);

    // restore Z state
    DX9_SetZEnable(true);
}

static void
ModifierDrawDebug(void)
{
    /****** Initial Setup ******/

    RJS_RGBA color = _rj_shadow_color_;

    color.a *= 0.25f;

    DX9_SetPxlShaderConstantF( 0, (dx9_float4*)&color, 1 );

    /****** Prep Buffer Write ******/
    /** Z buffer **/
    DX9_SetZWrite(false);

    /****** Prep Buffer Draw ******/
    /** Alpha blend **/
    DX9_SetAlphaBlendEnable(true);
    DX9_SetSrcBlend(DX9_BLND_SRCALPHA);
    DX9_SetDstBlend(DX9_BLND_INVSRCALPHA);

    /****** Draw the Modifier Buffer ******/
    rjModifierDrawBuffer();
}

EXTERN Uint32 _rj_mod_vertex_buffer_num_;

/****** Modifier Draw Mode **********************************************************/
void
rjDrawCheapShadow(void)
{
    if ( !_rj_mod_vertex_buffer_num_ || _rj_shadow_lock_ ) // !ModBufferNum ||
    {
        return;
    }

    _rj_shadow_debug_ ? ModifierDrawDebug() : ModifierDrawFast();

    _rj_shadow_lock_ = TRUE;
}

/****** Modifier Effect Draw ********************************************************************/
Sint32
rjCheapShadowEffectStart(void)
{
    switch ( _rj_alpha_mode_ )
    {
        case RJ_ALPHA_OPAQUE:
        case RJ_ALPHA_PUNCHTHROUGH: default:
        {
            if (_nj_control_3d_flag_ & (NJD_CONTROL_3D_SHADOW | NJD_CONTROL_3D_SHADOW_OPAQUE))
            {
                ModifierOnShadow();
                return 2;
            }

            return 0;
        }
        case RJ_ALPHA_TRANSLUCENT:
        {
            ModifierSuspend();
            return 1;
        }
        case RJ_ALPHA_ALPHATEST:
        {
            if (_nj_control_3d_flag_ & NJD_CONTROL_3D_SHADOW)
            {
                ModifierOnShadow();
                return 2;
            }

            return 0;
        }
    }

    return 0;
}

void
rjCheapShadowEffectEnd(const Sint32 n)
{
    switch ( n )
    {
        case 1:
        {
            ModifierResume();
            break;
        }
        case 2:
        {
            _rj_shadow_lock_ = FALSE;

            ModifierOffShadow();
            break;
        }
    }
}

void
rjSetCheapShadowMode(Int mode)
{
    const Int mode_and = mode & 255;

    _rj_shadow_color_.a = 1.f - ( (Float)mode_and * (1.f/256.f) );
}

void
rjSetCheapShadowColor(Float r, Float g, Float b)
{
    _rj_shadow_color_.r = r;
    _rj_shadow_color_.g = g;
    _rj_shadow_color_.b = b;
}

void
rjCheapShadowDebug(Bool mode)
{
    _rj_shadow_debug_ = mode;
}

/****** Function Hooks **************************************************************************/
static mt_hookinfo GX_End_ModifierHookInfo[1];
static void
GX_End_Modifier(void)
{
    const Sint32 i = rjCheapShadowEffectStart();

    FuncHookCall( GX_End_ModifierHookInfo, GX_End_p() );

    rjCheapShadowEffectEnd(i);
}

static mt_hookinfo GX_EndOther_ModifierHookInfo[1];
static void __cdecl
GX_EndOther_Modifier(int a1, char a2)
{
    const Sint32 i = rjCheapShadowEffectStart();

    FuncHookCall( GX_EndOther_ModifierHookInfo, GX_EndOther_p(a1, a2) );

    rjCheapShadowEffectEnd(i);
}

/****** Init ************************************************************************************/
void
RJ_ModifierInit(void)
{
    /** Draw hooks **/
    mtHookFunc(GX_End_ModifierHookInfo     , GX_End_p     , GX_End_Modifier);
    mtHookFunc(GX_EndOther_ModifierHookInfo, GX_EndOther_p, GX_EndOther_Modifier);
}
