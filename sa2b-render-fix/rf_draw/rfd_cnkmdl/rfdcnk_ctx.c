/************************/
/*  Includes            */
/************************/
/****** Core Toolkit ****************************************************************/
#include <samt/core.h>      /* core                                                 */

/****** Ninja ***********************************************************************/
#include <samt/ninja/ninja.h> /* ninja                                              */

/****** GX **************************************************************************/
#include <samt/gx/gx.h>     /* GX                                                   */

/****** Render Fix ******************************************************************/
#include <rf_core.h>        /* core                                                 */
#include <rf_renderstate.h> /* render state                                         */
#include <rf_util.h>        /* utility                                              */
#include <rf_gx.h>          /* rf gx                                                */
#include <rf_light.h>

/****** Self ************************************************************************/
#include <rf_draw/rfd_cnkmdl/rfdcnk_internal.h> /* parent & siblings                */

/************************/
/*  Source Constants    */
/************************/
/****** Chunk Texinfo ***************************************************************/
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
    if ( _nj_control_3d_flag_ & NJD_CONTROL_3D_CNK_BLEND_MODE )
    {
        _rj_cnk_blend_mode_ = _nj_cnk_blend_mode_;
    }
    else
    {
        _rj_cnk_blend_mode_ = pCtx->blend;
    }
}

static void
rjCnkContextTiny(CNK_CTX* restrict pCtx)
{
    EXTERN NJS_TEXNAME texture_rf_texerr[];

    if ( !(pCtx->flag & CTXF_TINY) )
        return;

    pCtx->flag &= ~CTXF_TINY;

    /** get texture **/

    s16 texid = pCtx->tiny.texid;

    // call texture callback
    if (_rj_cnk_texture_callback_) texid = _rj_cnk_texture_callback_(texid);

    const NJS_TEXLIST* p_tls = njGetCurrentTexList();

    if ( !p_tls || texid >= (s16)p_tls->nbTexture )
    {
    TEX_ERR:
        const NJS_TEXMANAGE* p_texman = (NJS_TEXMANAGE*) texture_rf_texerr[0].texaddr;

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

    switch ( pCtx->tiny.filter )
    {
        case CNK_FILTER_POINTSAMPLE:
        {
            p_tinfo->min_filter = 0;
            p_tinfo->mag_filter = 0;
            break;
        }
        case CNK_FILTER_BILINEAR:
        {
            p_tinfo->min_filter = 1;
            p_tinfo->mag_filter = 1;
            break;
        }
        case CNK_FILTER_TRILINEAR_A:
        {
            p_tinfo->min_filter = 1;
            p_tinfo->mag_filter = 1;
            break;
        }
        case CNK_FILTER_TRILINEAR_B:
        {
            p_tinfo->min_filter = 1;
            p_tinfo->mag_filter = 1;
            break;
        }
    }

    /** texture wrapping **/

    switch (pCtx->tiny.flip)
    {
        case CNK_FLIP_NONE:
        {
            p_tinfo->address_u = 1; // repeat
            p_tinfo->address_v = 1; // repeat
            break;
        }
        case CNK_FLIP_V:
        {
            p_tinfo->address_u = 1; // repeat
            p_tinfo->address_v = 2; // flip
            break;
        }
        case CNK_FLIP_U:
        {
            p_tinfo->address_u = 2; // flip
            p_tinfo->address_v = 1; // repeat
            break;
        }
        case CNK_FLIP_UV:
        {
            p_tinfo->address_u = 2; // flip
            p_tinfo->address_v = 2; // flip
            break;
        }
    }

    switch (pCtx->tiny.clamp)
    {
        case CNK_CLAMP_NONE:
        {
            break;
        }
        case CNK_CLAMP_V:
        {
            p_tinfo->address_v = 0;
            break;
        }
        case CNK_CLAMP_U:
        {
            p_tinfo->address_u = 0;
            break;
        }
        case CNK_CLAMP_UV:
        {
            p_tinfo->address_u = 0;
            p_tinfo->address_v = 0;
            break;
        }
    }

    /** tes5 **/

    p_tinfo->mip_level = (bool)( sflag & NJD_SURFACEFLAGS_MIPMAPED );

    /** set texture **/

    RX_SetTexture(p_tinfo, 0);
}

static void
rjCnkContextDiff(CNK_CTX* restrict pCtx)
{
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

    /** Adjust diffuse depending on Ninja, draw function, and strip context **/
    {
        const s32 funcmd = pCtx->flag & CTXF_MASK_FUNC;

        const u32 ctxflg = pCtx->flag;

        /** If using texture AND is not DirectDraw, ELSE keep diffuse **/
        if ( !(ctxflg & CTXF_STATE_NONTEX) && !(funcmd & CTXF_FUNC_DIRECT) )
        {
            /** If EasyDraw/EasyMultiDraw **/
            if ( funcmd & CTXF_FUNC_EASY )
            {
                diff.r = 1.f;
                diff.g = 1.f;
                diff.b = 1.f;
            }
            /** Constant Texture Material flag, SimpleDraw is implied here **/
            else if ( nj3dflag & NJD_CONTROL_3D_CONSTANT_TEXTURE_MATERIAL )
            {
                /** is NormalDraw             OR is SimpleMulti             OR  not CnkS type **/
                if ( funcmd == CTX_FUNC_NORMAL || funcmd & CTXF_FUNC_MULTI || !(ctxflg & CTXFLG_STRIP_NOUVS) )
                {
                    diff.r = 1.f;
                    diff.g = 1.f;
                    diff.b = 1.f;
                }
                else goto CLAMP_DIFF;
            }
            else goto CLAMP_DIFF;
        }
        else
        {
        CLAMP_DIFF:
            diff.r = CLAMP(diff.r, 0.f, 1.f);
            diff.g = CLAMP(diff.g, 0.f, 1.f);
            diff.b = CLAMP(diff.b, 0.f, 1.f);
        }
    }

    diff.a = CLAMP(diff.a, 0.f, 1.f);

    /** apply diffuse **/

    _rj_cnk_diff_material_ = diff;
}

static void
rjCnkContextAmbi(CNK_CTX* restrict pCtx)
{
    if ( pCtx->fst & NJD_FST_IA )
    {
        _rj_cnk_ambi_material_.r = 0.f;
        _rj_cnk_ambi_material_.g = 0.f;
        _rj_cnk_ambi_material_.b = 0.f;
    }
    else if ( pCtx->flag & CTXF_CTL_AMBIMATERIAL )
    {
        _rj_cnk_ambi_material_.r = _rj_cnk_light_ambient_.r * ( (f32)pCtx->ambi.r * (1.f/255.f) );
        _rj_cnk_ambi_material_.g = _rj_cnk_light_ambient_.g * ( (f32)pCtx->ambi.g * (1.f/255.f) );
        _rj_cnk_ambi_material_.b = _rj_cnk_light_ambient_.b * ( (f32)pCtx->ambi.b * (1.f/255.f) );
    }
    else
    {
        _rj_cnk_ambi_material_.r = _rj_cnk_light_ambient_.r;
        _rj_cnk_ambi_material_.g = _rj_cnk_light_ambient_.g;
        _rj_cnk_ambi_material_.b = _rj_cnk_light_ambient_.b;
    }
}

static void
rjCnkContextSpec(CNK_CTX* restrict pCtx)
{
    _rj_cnk_spec_material_.a =  (Float)pCtx->spec.a;
    _rj_cnk_spec_material_.r = ((Float)pCtx->spec.r * (1.f/255.f));
    _rj_cnk_spec_material_.g = ((Float)pCtx->spec.g * (1.f/255.f));
    _rj_cnk_spec_material_.b = ((Float)pCtx->spec.b * (1.f/255.f));
}

static void
rjCnkContextStrip(CNK_CTX* restrict pCtx)
{
    const Sint16 fst = pCtx->fst;

    const s32 bld = _rj_cnk_blend_mode_;

    const s32 bld_src = (bld & NJD_FBS_MASK);
    const s32 bld_dst = (bld & NJD_FBD_MASK);

    RJE_ALPHA alphamd;

    if ( fst & (NJD_FST_UA|NJD_FST_NAT) )
    {
        if ( _nj_control_3d_flag_ & NJD_CONTROL_3D_USE_PUNCHTHROUGH )
        {
            alphamd = RJE_ALPHA_PUNCHTHROUGH;
        }
        else // not punchthrough
        {
            if ( (pCtx->flag & CTXF_STATE_NONTEX) ||        // no texture
                 (fst & NJD_FST_NAT)              ||        // OR NAT flag
                 (bld_src == NJD_FBS_ONE)         ||        // OR src is ONE
                 (bld_dst == NJD_FBD_ONE)         ||        // OR dst is ONE
                 (pTexSurface && pTexSurface->Type != 14) ) // OR texture is NOT ARGB1555
            {
                alphamd = RJE_ALPHA_TRANS;
            }
            else
            {
                alphamd = RJE_ALPHA_ALPHATEST;
            }
        }
    }        
    else // opaque strip
    {
        alphamd = RJE_ALPHA_OPAQUE;
    }

    rjSetAlphaMode(bld_src>>NJD_FBS_SHIFT, bld_dst>>NJD_FBD_SHIFT, alphamd);
}

/****** Extern **********************************************************************/
void
rjCnkBeginContext(CNK_CTX* restrict pCtx)
{
    const RFRS_CNKFUNCMD funcmd = RFRS_GetCnkFuncMode();

    pCtx->flag = funcmd;

    if ( funcmd == RFRS_CNKFUNCMD_NORMAL || funcmd == RFRS_CNKFUNCMD_SIMPLE || funcmd == RFRS_CNKFUNCMD_SIMPLEMULTI )
    {
        pCtx->flag |= CTXF_CTL_BACKFACECULL;

        if ( RFRS_GetTwoPassLightingMode() == RFRS_TWOPASSLIGHTMD_ENABLED )
        {
            pCtx->flag |= CTXF_CTL_TWOPASSLIGHT;
        }
    }

    if ( funcmd == RFRS_CNKFUNCMD_NORMAL || funcmd & RFRS_CNKFUNCMD_MULTIBIT )
    {
        pCtx->flag |= (CTXF_CTL_AMBIMATERIAL|CTXF_CTL_MULTIVND8);
    }

    if ( true ) ___TODO("This will be a setting to allow specular on non-textured polygons");
    {
        pCtx->flag |= CTXF_CTL_NONTEXSPEC;
    }

    // set default material
    pCtx->diff = (NJS_BGRA){  1,  1,  1,  1 };
    pCtx->ambi = (NJS_BGRA){  1,  1,  1,  1 };
    pCtx->spec = (NJS_BGRA){  0,  0,  0, 16 };

    // to fix a cloud blending bug in metal harbor
    pCtx->blend = (Uint16) _rj_cnk_blend_mode_;
}

void
rjCnkSetBlend(CNK_CTX* restrict pCtx, const Sint16* plist)
{
    pCtx->blend = plist[0] & (NJD_FBS_MASK|NJD_FBD_MASK);
}

void
rjCnkSetExponent(CNK_CTX* restrict pCtx, const Sint16* plist)
{
    pCtx->spec.a = ((CNK_BITS_EXPONENT*)plist)->exp;
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
        pCtx->spec = *(NJS_BGRA*)(&plist[mat_index]);
    }
}

void
rjCnkSetTexture(CNK_CTX* restrict pCtx, const Sint16* plist)
{
    pCtx->tiny = *(CNK_TINY_HEAD*)(&plist[0]);

    pCtx->flag |= CTXF_TINY;
}

void
rjCnkSetStrip(CNK_CTX* restrict pCtx, const Sint16* plist)
{
    Sint16 fst = plist[0];

    if ( _nj_control_3d_flag_ & NJD_CONTROL_3D_CNK_CONSTANT_ATTR )
    {
        fst = (fst & _nj_constant_attr_and_) | _nj_constant_attr_or_;
    }

    switch ( RFRS_GetCnkFuncMode() )
    {
        case RFRS_CNKFUNCMD_NORMAL:
        case RFRS_CNKFUNCMD_SIMPLE:
        {
            break;
        }
        case RFRS_CNKFUNCMD_EASY:
        {
            fst &= ~(NJD_FST_IL|NJD_FST_IA|NJD_FST_DB|NJD_FST_ENV);
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

    switch ( _rj_cnk_depth_queue_ )
    {
        case RJD_CNK_DEPTHQUEUE_OFF:
        case RJD_CNK_DEPTHQUEUE_NEAR:
        {
            break;
        }
        case RJD_CNK_DEPTHQUEUE_ON:
        {
            fst |= NJD_FST_UA;
            break;
        }
    }

    pCtx->fst = fst & NJD_FST_MASK;
}

void
rjCnkSetPolygonCullingMode(CNK_CTX* restrict pCtx, Bool light)
{
    const Uint32 nrm = pCtx->flag & CTXF_DRAW_NORMAL;
    const Uint32 inv = pCtx->flag & CTXF_DRAW_INVERSE;

    if ( pCtx->flag & CTXF_CTL_BACKFACECULL )
    {
        if ( nrm ) // normal
        {
            /*
            *   if both sides are set to draw, meaning opaque pass, we need to
            *   first determine if this strip is double sided. If it is, we then check
            *   if lighting calculations are going to be used. If not, then no cull.
            * 
            *   If either of those things fail though, cull CW and let the
            *   'BeginTwoPass' functions handle the inverse side.
            */

            if ( inv && (pCtx->fst & NJD_FST_DB) && !light ) // both
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
    else // easy/multi/direct
    {
        if ( nrm )
        {
            if ( inv ) // both
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
}

void
rjCnkExecContext(CNK_CTX* restrict pCtx)
{
    rjCnkContextBlend(pCtx);
    rjCnkContextTiny(pCtx);
    rjCnkContextDiff(pCtx);
    rjCnkContextAmbi(pCtx);
    rjCnkContextSpec(pCtx);
    rjCnkContextStrip(pCtx);
}
