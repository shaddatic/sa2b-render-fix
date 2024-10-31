/************************/
/*  Includes            */
/************************/
/****** Core Toolkit ****************************************************************/
#include <sa2b/core.h>      /* core                                                 */

/****** Ninja ***********************************************************************/
#include <sa2b/ninja/ninja.h> /* ninja                                              */

/****** GX **************************************************************************/
#include <sa2b/gx/gx.h>     /* GX                                                   */

/****** Render Fix ******************************************************************/
#include <rf_core.h>        /* core                                                 */
#include <rf_renderstate.h> /* render state                                         */
#include <rf_util.h>        /* utility                                              */

/****** Self ************************************************************************/
#include <rf_draw/rfd_cnkmdl/rfdcnk_internal.h> /* parent & siblings                */

/************************/
/*  Source Constants    */
/************************/
/****** Shifted FST *****************************************************************/
#define CNK_FST_UA              (NJD_FST_UA>>NJD_FST_SHIFT) /* use alpha            */

/************************/
/*  Source              */
/************************/
/****** Static **********************************************************************/
typedef union
{
    struct {
        Uint8 r, g, b, a;
    };
    Uint32 color;
}
GXS_COLOR;

static void
GX_SetChanMatColor(s32 chan, GXS_COLOR color)
{
    static const uintptr_t fptr = 0x0041F4E0;

    __asm
    {
        push [color]
        mov eax, [chan]
        call fptr
        add esp, 4
    }
}

static void
ArgbToGx(const NJS_ARGB* restrict pArgb, GXS_COLOR* restrict pGxCol)
{
    pGxCol->a = (u8)( CLAMP(pArgb->a, 0.f, 1.f) * 255.f );
    pGxCol->r = (u8)( CLAMP(pArgb->r, 0.f, 1.f) * 255.f );
    pGxCol->g = (u8)( CLAMP(pArgb->g, 0.f, 1.f) * 255.f );
    pGxCol->b = (u8)( CLAMP(pArgb->b, 0.f, 1.f) * 255.f );
}

static void
BgraToArgb(const NJS_BGRA* restrict pBgra, NJS_ARGB* restrict pArgb)
{
    pArgb->a = ( (f32)pBgra->a * (1.f/255.f) );
    pArgb->r = ( (f32)pBgra->r * (1.f/255.f) );
    pArgb->g = ( (f32)pBgra->g * (1.f/255.f) );
    pArgb->b = ( (f32)pBgra->b * (1.f/255.f) );
}

static void
rjCnkContextBlend(CNK_CTX* pCtx)
{
    if ( pCtx->flag & (CTXFLG_CTX_BLEND) )
        return;

    if ( _nj_control_3d_flag_ & NJD_CONTROL_3D_CNK_BLEND_MODE )
    {
        pCtx->blend = _nj_cnk_blend_mode_;
    }

    pCtx->flag |= CTXFLG_CTX_BLEND;
}

static void
rjCnkContextTiny(CNK_CTX* pCtx)
{
    if ( pCtx->flag & (CTXFLG_CTX_TINY|CTXFLG_STRIP_NOTEX) )
        return;

    CnkParseTinyData_Ext(pCtx->tiny.flag, pCtx->tiny.id);

    pCtx->flag |= CTXFLG_CTX_TINY;
}

static void
rjCnkContextDiff(CNK_CTX* pCtx)
{
    if ( pCtx->flag & (CTXFLG_CTX_DIFF) )
        return;

    GXS_COLOR color;

    /** Get initial material color **/
    {
        const Uint32 nj3dflag = _nj_control_3d_flag_;

        if ( nj3dflag & NJD_CONTROL_3D_CONSTANT_MATERIAL )
        {
            ArgbToGx(&_nj_constant_material_, &color);
        }
        else if ( nj3dflag & NJD_CONTROL_3D_OFFSET_MATERIAL )
        {
            NJS_ARGB argb;

            BgraToArgb(&pCtx->diff, &argb);

            argb.a += _nj_constant_material_.a;
            argb.r += _nj_constant_material_.r;
            argb.g += _nj_constant_material_.g;
            argb.b += _nj_constant_material_.b;

            ArgbToGx(&argb, &color);
        }
        else
        {
            const NJS_BGRA matcol = pCtx->diff;

            color.a = matcol.a;
            color.r = matcol.r;
            color.g = matcol.g;
            color.b = matcol.b;
        }
    }

    /** Adjust diffuse depending on draw function **/
    {
        const s32 funcmd = RFRS_GetCnkFuncMode();

        if (funcmd & (RFRS_CNKFUNCMD_EASYBIT|RFRS_CNKFUNCMD_SIMPLEBIT))
        {
            if ( !(pCtx->flag & CTXFLG_STRIP_NOTEX) && ( (funcmd & RFRS_CNKFUNCMD_MULTIBIT) || !(pCtx->fst & NJD_FST_ENV) ) )
            {
                color.r = 0xFF;
                color.g = 0xFF;
                color.b = 0xFF;
            }
        }
    }

    GX_SetChanMatColor(0, color);

    pCtx->flag |= CTXFLG_CTX_DIFF;
}

static void
rjCnkContextAmbi(CNK_CTX* pCtx)
{
    if ( pCtx->flag & CTXFLG_CTX_AMBI )
        return;

    pCtx->flag |= CTXFLG_CTX_AMBI;
}

static void
rjCnkContextSpec(CNK_CTX* pCtx)
{
    if ( pCtx->flag & CTXFLG_CTX_SPEC )
        return;

    pCtx->flag |= CTXFLG_CTX_SPEC;
}

inline bool
CheckAlphaTest(const bool nat, const Sint16 blend, const bool notex)
{
    return !nat && !(notex) && *pTexSurface == 14;
}

static void
rjCnkContextStrip(CNK_CTX* pCtx)
{
    const Sint16 fst = pCtx->fst;
    const Sint16 bld = pCtx->blend;

    const Sint16 bld_src = (bld & NJD_FBS_MASK);
    const Sint16 bld_dst = (bld & NJD_FBD_MASK);

    const bool fst_ua  = (fst & NJD_FST_UA);

    GX_SetBlendMode((bld_src >> NJD_FBS_SHIFT), (bld_dst >> NJD_FBD_SHIFT), fst_ua);

    if (fst_ua)
    {
        const bool fst_nat = (fst & NJD_FST_NAT);
        const bool notex   = (pCtx->flag & CTXFLG_STRIP_NOTEX);

        if ( fst_nat ||                      // IF NoAlphaTest flag
            bld_src == NJD_FBS_ONE ||        // OR src is ONE
            bld_dst == NJD_FBD_ONE ||        // OR dst is ONE
          ( !notex && *pTexSurface != 14 ) ) // OR no alpha test tex flag
        {
            SetTransparentDraw();
        }
        else
            SetAlphaTestDraw();
    } 
    else
        SetOpaqueDraw();
}

static void
rjCnkContextLight(const CNK_CTX* pCtx)
{
    const int fst_8 = (pCtx->fst >> 8);

    const int light_flag = _nj_cnk_strip_flags_ | (_nj_cnk_last_strip_flags_ ^ fst_8);

    _nj_cnk_last_strip_flags_ = fst_8;

    if (light_flag & 1)
        CnkSetupLights_Ext((s8)fst_8);
}

/****** Extern **********************************************************************/
void
rjCnkSetBlend(CNK_CTX* const pCtx, const Sint16* const plist)
{
    pCtx->blend = plist[0] & (NJD_FBS_MASK | NJD_FBD_MASK);

    pCtx->flag &= ~CTXFLG_CTX_BLEND;
}

void
rjCnkSetMaterial(CNK_CTX* const pCtx, const Sint16* const plist)
{
    rjCnkSetBlend(pCtx, plist);

    const int flag = ((u8*)plist)[0] & 0x7;

    s32 mat_index = 2;

    if (flag & 1)
    {
        pCtx->diff = *(NJS_BGRA*)(&plist[mat_index]);

        mat_index += 2;
    }
    if (flag & 2)
    {
        pCtx->ambi = *(NJS_BGRA*)(&plist[mat_index]);

        mat_index += 2;
    }
    if (flag & 4)
    {
        pCtx->spec = *(CNK_SPEC*)(&plist[mat_index]);
    }

    pCtx->flag &= ~( flag << CTXFLG_SHIFT_MAT );
}

void
rjCnkSetTexture(CNK_CTX* const pCtx, const Sint16* const plist)
{
    pCtx->tiny = *(CNK_TINY*)(&plist[0]);

    pCtx->flag &= ~CTXFLG_CTX_TINY;
}

void
rjCnkSetStrip(CNK_CTX* const pCtx, const Sint16* const plist)
{
    Sint16 fst = plist[0];

    if ( _nj_control_3d_flag_ & NJD_CONTROL_3D_CNK_CONSTANT_ATTR )
    {
        fst = (fst & _nj_constant_attr_and_) | _nj_constant_attr_or_;
    }

    const s32 funcmd = RFRS_GetCnkFuncMode();

    if (funcmd & RFRS_CNKFUNCMD_EASYBIT)
    {
        fst |=  NJD_FST_DB;
        fst &= ~NJD_FST_ENV;
    }
    else if (funcmd & RFRS_CNKFUNCMD_DIRECTBIT)
    {
        fst |= NJD_FST_DB;
    }

    if (RFRS_GetCullMode() == RFRS_CULLMD_NONE)
    {
        fst |= NJD_FST_DB;
    }

    pCtx->fst = fst;
}

void
rjCnkContext(CNK_CTX* const pCtx)
{
    rjCnkContextBlend(pCtx);
    rjCnkContextTiny(pCtx);
    rjCnkContextDiff(pCtx);
    rjCnkContextAmbi(pCtx);
    rjCnkContextSpec(pCtx);
    rjCnkContextStrip(pCtx);
    rjCnkContextLight(pCtx);
}
