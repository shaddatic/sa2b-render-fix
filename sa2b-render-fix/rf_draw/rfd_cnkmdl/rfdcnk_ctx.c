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
#include <rf_gx.h>          /* rf gx                                                */

/****** Self ************************************************************************/
#include <rf_draw/rfd_cnkmdl/rfdcnk_internal.h> /* parent & siblings                */

/************************/
/*  Source Constants    */
/************************/
/****** Shifted FST *****************************************************************/
#define CNK_FST_UA              (NJD_FST_UA>>NJD_FST_SHIFT) /* use alpha            */

#define CnkSetTextureList       DATA_ARY(TEXTURE_INFO, 0x01934768, [8])

/************************/
/*  Source              */
/************************/
/****** Static **********************************************************************/
static void
BgraToArgb(const NJS_BGRA* restrict pBgra, NJS_ARGB* restrict pArgb)
{
    pArgb->a = ( (f32)pBgra->a * (1.f/255.f) );
    pArgb->r = ( (f32)pBgra->r * (1.f/255.f) );
    pArgb->g = ( (f32)pBgra->g * (1.f/255.f) );
    pArgb->b = ( (f32)pBgra->b * (1.f/255.f) );
}

static void
rjCnkContextBlend(CNK_CTX* restrict pCtx)
{
    if ( !(pCtx->flag & CTXFLG_CTX_BLEND) )
        return;

    if ( !(_nj_control_3d_flag_ & NJD_CONTROL_3D_CNK_BLEND_MODE) )
    {
        _nj_cnk_blend_mode_ = pCtx->blend;
    }

    pCtx->flag &= ~CTXFLG_CTX_BLEND;
}

static void
rjCnkContextTiny(CNK_CTX* restrict pCtx)
{
    EXTERN NJS_TEXLIST texlist_rf_texerr[];

    if ( !(pCtx->flag & CTXFLG_CTX_TINY) )
        return;

    pCtx->flag &= ~CTXFLG_CTX_TINY;

    /** get context **/

    const Uint16 headbits = pCtx->tiny.headbits;
    const Uint16 texbits  = pCtx->tiny.texbits;

    /** get texture **/

    const s32 texid = texbits & NJD_TID_MASK;

    const NJS_TEXLIST* p_tls = njGetCurrentTexList();

    if (texid >= (s32)p_tls->nbTexture)
    {
    TEX_ERR:
        const NJS_TEXMANAGE* p_texman = (NJS_TEXMANAGE*) texlist_rf_texerr->textures[0].texaddr;

        NJS_TEXSYSTEM* p_texsys = p_texman->texsys;

        const bool flg_tes5 = (bool)( p_texsys->texsurface.fSurfaceFlags & NJD_SURFACEFLAGS_MIPMAPED );

        pTexSurface = &p_texsys->texsurface;

        TEXTURE_INFO* p_tinfo = &CnkSetTextureList[0];

        p_tinfo->surface    = p_texsys->texsurface.pSurface;
        p_tinfo->min_filter = 0;
        p_tinfo->mag_filter = 0;
        p_tinfo->address_u = 1;
        p_tinfo->address_v = 1;
        p_tinfo->palette = -1;

        p_tinfo->mip_level = flg_tes5 != 0;

        RX_SetTexture(p_tinfo, 0);
        return;
        /** purposefully don't unset CTX_TINY flag **/
    }

    NJS_TEXMANAGE* p_texman = (NJS_TEXMANAGE*) p_tls->textures[texid].texaddr;

    if (!p_texman)
        goto TEX_ERR;

    NJS_TEXSYSTEM* p_texsys = p_texman->texsys;

    if (!p_texsys)
        goto TEX_ERR;

    pTexSurface = &p_texsys->texsurface;

    /** texture info start **/

    TEXTURE_INFO* p_tinfo = &CnkSetTextureList[0];

    /** texture pointer and palette **/

    const Uint32 sflag = p_texsys->texsurface.fSurfaceFlags;

    if ( sflag & NJD_SURFACEFLAGS_PALETTIZED )
    {
        p_tinfo->surface = p_texsys->texsurface.pSurface;
        p_tinfo->palette = p_texman->bank;
    }
    else
    {
        p_tinfo->surface = p_texsys->texsurface.pSurface;
        p_tinfo->palette = -1;
    }

    /** texture filtering **/

    switch ( (texbits & NJD_FFM_MASK) >> NJD_FFM_SHIFT )
    {
        case 0: // point
        {
            p_tinfo->min_filter = 0;
            p_tinfo->mag_filter = 0;
            break;
        }
        case 1: // bilinear (default)
        {
            p_tinfo->min_filter = 1;
            p_tinfo->mag_filter = 1;
            break;
        }
        case 2: // trilinear A
        {
            p_tinfo->min_filter = 1;
            p_tinfo->mag_filter = 1;
            break;
        }
        case 3: // trilinear B
        {
            p_tinfo->min_filter = 1;
            p_tinfo->mag_filter = 1;
            break;
        }
    }

    /** texture wrapping **/

    if (headbits & NJD_FCL_U) // CLamp
    {
        p_tinfo->address_u = 0;
    }
    else if (headbits & NJD_FFL_U) // FLip (mirror)
    {
        p_tinfo->address_u = 2;
    }
    else
        p_tinfo->address_u = 1; // repeat

    if (headbits & NJD_FCL_V) // CLamp
    {
        p_tinfo->address_v = 0;
    }
    else if (headbits & NJD_FFL_V) // FLip (mirror)
    {
        p_tinfo->address_v = 2;
    }
    else
        p_tinfo->address_v = 1; // repeat

    /** tes5 **/

    p_tinfo->mip_level = (bool)( sflag & NJD_SURFACEFLAGS_MIPMAPED );

    /** set texture **/

    RX_SetTexture(p_tinfo, 0);
}

static void
rjCnkContextDiff(CNK_CTX* restrict pCtx)
{
    pCtx->flag &= ~CTXFLG_CTX_DIFF;

    const Uint32 nj3dflag = _nj_control_3d_flag_;

    NJS_ARGB diff;

    /** Get initial material color **/
    {
        if ( nj3dflag & NJD_CONTROL_3D_CONSTANT_MATERIAL )
        {
            diff = _nj_constant_material_;
        }
        else if ( nj3dflag & NJD_CONTROL_3D_OFFSET_MATERIAL )
        {
            BgraToArgb(&pCtx->diff, &diff);

            diff.a += _nj_constant_material_.a;
            diff.r += _nj_constant_material_.r;
            diff.g += _nj_constant_material_.g;
            diff.b += _nj_constant_material_.b;
        }
        else
            BgraToArgb(&pCtx->diff, &diff);
    }

    /** diffuse color is clamped **/

    diff.a = CLAMP(diff.a, 0.f, 1.f);
    diff.r = CLAMP(diff.r, 0.f, 1.f);
    diff.g = CLAMP(diff.g, 0.f, 1.f);
    diff.b = CLAMP(diff.b, 0.f, 1.f);

    /** Adjust diffuse depending on Ninja, draw function, and strip context **/
    {
        const s32 funcmd = pCtx->flag & CTXFLG_MASK_FUNC;

        const u32 ctxflg = pCtx->flag;

        /** If using texture AND is not DirectDraw, ELSE keep diffuse **/
        if ( !(ctxflg & CTXFLG_STRIP_NOTEX) && !(funcmd & CTXFLG_FUNC_DIRECT) )
        {
            /** If EasyDraw/EasyMultiDraw **/
            if ( funcmd & CTXFLG_FUNC_EASY )
            {
                diff.r = 1.f;
                diff.g = 1.f;
                diff.b = 1.f;
            }
            /** Constant Texture Material flag, SimpleDraw is implied here **/
            else if ( nj3dflag & NJD_CONTROL_3D_CONSTANT_TEXTURE_MATERIAL )
            {
                /** Not "NormalDraw"          OR is SimpleMulti             OR  not CnkS type **/
                if ( funcmd == CTXFUNC_NORMAL || funcmd & CTXFLG_FUNC_MULTI || !(ctxflg & CTXFLG_STRIP_NOUVS) )
                {
                    diff.r = 1.f;
                    diff.g = 1.f;
                    diff.b = 1.f;
                }
            }
        }
    }

    /** apply diffuse **/

    RX_SetChanMatColor_Direct(0, diff.r, diff.g, diff.b, diff.a);
}

static void
rjCnkContextAmbi(CNK_CTX* restrict pCtx)
{
    EXTERN NJS_ARGB rj_ambi_color;

    pCtx->flag &= ~CTXFLG_CTX_AMBI;

    NJS_ARGB ambi;

    if ( pCtx->fst & NJD_FST_IA )
    {
        ambi.r = 0.f;
        ambi.g = 0.f;
        ambi.b = 0.f;
    }
    else
    {
        const s32 funcmd = pCtx->flag & CTXFLG_MASK_FUNC;

        /**  If Normal Draw           OR  using a MultiDraw variant **/
        if ( funcmd == CTXFUNC_NORMAL || (funcmd & CTXFLG_FUNC_MULTI) )
        {
            ambi.r = rj_ambi_color.r * (f32)(pCtx->ambi.r * (1.f/255.f));
            ambi.g = rj_ambi_color.g * (f32)(pCtx->ambi.g * (1.f/255.f));
            ambi.b = rj_ambi_color.b * (f32)(pCtx->ambi.b * (1.f/255.f));
        }
        else
        {
            ambi.r = rj_ambi_color.r;
            ambi.g = rj_ambi_color.g;
            ambi.b = rj_ambi_color.b;
        }
    }

    RX_SetChanAmbColor_Direct(ambi.r, ambi.g, ambi.b);
}

static void
rjCnkContextSpec(CNK_CTX* restrict pCtx)
{
    if ( !(pCtx->flag & CTXFLG_CTX_SPEC) )
        return;

    pCtx->flag &= ~CTXFLG_CTX_SPEC;
}

static void
SetBlendMode(s32 src, s32 dst, bool ua)
{
    GX_SetBlendMode((src>>NJD_FBS_SHIFT), (dst>>NJD_FBD_SHIFT), ua);
}

static void
rjCnkContextStrip(CNK_CTX* restrict pCtx)
{
    const Sint16 fst = pCtx->fst;

    const bool fst_ua  = ( fst & (NJD_FST_UA|NJD_FST_NAT) );

    const s32 bld = _nj_cnk_blend_mode_;

    const s32 bld_src = (bld & NJD_FBS_MASK);
    const s32 bld_dst = (bld & NJD_FBD_MASK);

    SetBlendMode(bld_src, bld_dst, fst_ua);

    /** Set culling mode **/

    if (pCtx->flag & (CTXFLG_FUNC_EASY|CTXFLG_FUNC_DIRECT))
    {
        const bool nrm = pCtx->flag & CTXFLG_CULL_NORMAL;
        const bool inv = pCtx->flag & CTXFLG_CULL_INVERSE;

        if (nrm)
        {
            if (inv) // both
            {
                GX_SetCullMode(GXD_CULLMODE_NONE);
            }
            else // normal
            {
                GX_SetCullMode(GXD_CULLMODE_CW);
            }
        }
        else // inverse
        {
            GX_SetCullMode(GXD_CULLMODE_CCW);
        }
    }
    else // calc inverted normals
    {
        GX_SetCullMode(GXD_CULLMODE_CW);
    }

    if (fst_ua)
    {
        const bool notex = (pCtx->flag & CTXFLG_STRIP_NOTEX);

        if ( (fst & NJD_FST_NAT)        // IF NoAlphaTest flag
            || bld_src == NJD_FBS_ONE   // OR src is ONE
            || bld_dst == NJD_FBD_ONE   // OR dst is ONE
            || notex                    // OR no texture
            || (pTexSurface && pTexSurface->Type != 14) ) // OR no alpha test tex flag
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
rjCnkContextLight(const CNK_CTX* restrict pCtx)
{
    const int fst_8 = (pCtx->fst >> 8);

    const int light_flag = _nj_cnk_strip_flags_ | (_nj_cnk_last_strip_flags_ ^ fst_8);

    _nj_cnk_last_strip_flags_ = fst_8;

    if (light_flag & 1)
        CnkSetupLights_Ext(fst_8);
}

/****** Extern **********************************************************************/
void
rjCnkSetBlend(CNK_CTX* restrict pCtx, const Sint16* plist)
{
    pCtx->blend = plist[0] & (NJD_FBS_MASK|NJD_FBD_MASK);

    pCtx->flag |= CTXFLG_CTX_BLEND;
}

void
rjCnkSetMaterial(CNK_CTX* restrict pCtx, const Sint16* plist)
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

    pCtx->flag |= ( flag << CTXFLG_SHIFT_MAT );
}

void
rjCnkSetTexture(CNK_CTX* restrict pCtx, const Sint16* plist)
{
    pCtx->tiny = *(CNK_TINY*)(&plist[0]);

    pCtx->flag |= CTXFLG_CTX_TINY;
}

Sint16
GetCnkStripFlags(const Sint16* plist)
{
    Sint16 fst = plist[0];

    if ( _nj_control_3d_flag_ & NJD_CONTROL_3D_CNK_CONSTANT_ATTR )
    {
        fst = (fst & _nj_constant_attr_and_) | _nj_constant_attr_or_;
    }

    switch ( RFRS_GetCnkFuncMode() )
    {
        case RFRS_CNKFUNCMD_NORMAL:
        {
          //fst &= ~(0);
            break;
        }
        case RFRS_CNKFUNCMD_EASY:
        {
            fst &= ~(NJD_FST_IL|NJD_FST_IA|NJD_FST_DB|NJD_FST_ENV);
            break;
        }
        case RFRS_CNKFUNCMD_SIMPLE:
        {
          //fst &= ~(0);
            break;
        }
        case RFRS_CNKFUNCMD_EASYMULTI:
        {
            fst &= ~(NJD_FST_IL|NJD_FST_DB|NJD_FST_ENV);
            break;
        }
        case RFRS_CNKFUNCMD_SIMPLEMULTI:
        {
            fst &= ~(NJD_FST_IL|NJD_FST_DB);
            break;
        }
        case RFRS_CNKFUNCMD_DIRECT:
        {
            fst &= ~(NJD_FST_IL|NJD_FST_IA|NJD_FST_DB);
            break;
        }
    }

    if (RFRS_GetCullMode() == RFRS_CULLMD_NONE)
    {
        fst |= (NJD_FST_DB);
    }

    return fst & NJD_FST_MASK;
}

void
rjCnkSetStrip(CNK_CTX* restrict pCtx, const Sint16* plist)
{
    pCtx->fst = GetCnkStripFlags(plist);
}

void
rjCnkContext(CNK_CTX* restrict pCtx)
{
    rjCnkContextBlend(pCtx);
    rjCnkContextTiny(pCtx);
    rjCnkContextDiff(pCtx);
    rjCnkContextAmbi(pCtx);
    rjCnkContextSpec(pCtx);
    rjCnkContextStrip(pCtx);
    rjCnkContextLight(pCtx);
}
