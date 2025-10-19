/********************************/
/*  Includes                    */
/********************************/
/****** Core Toolkit ****************************************************************************/
#include <samt/core.h>              /* core                                                     */

/****** Ninja ***********************************************************************************/
#include <samt/ninja/ninja.h>       /* ninja                                                    */

/****** Render Fix ******************************************************************************/
#include <rf_core.h>                /* core                                                     */
#include <rf_renderstate.h>         /* render state                                             */
#include <rf_light.h>               /* lights                                                   */
#include <rf_gx.h>                  /* set texture                                              */

/****** Self ************************************************************************************/
#include <rf_ninja/rj_cnk/rjcnk_internal.h>             /* parent & siblings                    */
#include <rf_ninja/rj_cnk/rjcnk_plist/rjcpl_internal.h> /* self                                 */

/********************************/
/*  Constants                   */
/********************************/
/****** Chunk Strip Draw Flags ******************************************************************/
#define RJD_CSD_NORMAL              (1<<0) /* draw normal triangles                             */
#define RJD_CSD_INVERT              (1<<1) /* draw inverse triangles                            */
#define RJD_CSD_SKIPEND             (1<<2) /* skip end vertex                                   */
#define RJD_CSD_SKIPMAT             (1<<3) /* skip material reads/setting                       */

/****** Check Struct ****************************************************************************/
#define RJD_CST_MAX                 (128) /* chunk strip entry count                            */

/********************************/
/*  Macros                      */
/********************************/
/****** Check Struct ****************************************************************************/
#define AS_INT(a)                   *(int*)(&a)

/********************************/
/*  Game Defs                   */
/********************************/
/****** Chunk Texture ***************************************************************************/
#define CnkSetTextureList           DATA_ARY(TEXTURE_INFO, 0x01934768, [8])

/********************************/
/*  Source                      */
/********************************/
/****** Static **********************************************************************************/
static inline void
BgraToArgb(const NJS_BGRA* restrict pBgra, NJS_ARGB* restrict pArgb)
{
    pArgb->a = ( (f32)pBgra->a * (1.f/255.f) );
    pArgb->r = ( (f32)pBgra->r * (1.f/255.f) );
    pArgb->g = ( (f32)pBgra->g * (1.f/255.f) );
    pArgb->b = ( (f32)pBgra->b * (1.f/255.f) );
}

static inline bool
CheckTrans(const RJS_CNK_STRIP* restrict strip)
{
    /*
    *     We check if either UA or NAT strip flag is enabled and/or if Punchthrough alpha mode
    *   will be used (as PT is just a cutout opaque draw and not really translucent)
    */
    return (strip->flag & RJD_FST_TRANSLUCENT) && !(strip->ctrl3d & NJD_CONTROL_3D_USE_PUNCHTHROUGH);
}

/****** Set Strip *******************************************************************************/
static Sint32
rjCnkSetBlend(RJS_CNK_STRIP* restrict pStrip, const Sint16* restrict plist)
{
    if ( _nj_control_3d_flag_ & NJD_CONTROL_3D_CNK_BLEND_MODE )
    {
        pStrip->blend = _nj_cnk_blend_mode_;
    }
    else
    {
        pStrip->blend = plist[0] & (NJD_FBS_MASK|NJD_FBD_MASK);
    }

    return CNK_BITSOFF_SIZE;
}

static Sint32
rjCnkSetExponent(RJS_CNK_STRIP* restrict pStrip, const Sint16* restrict plist)
{
    pStrip->mats[RJ_CMC_SPEC].a = ((CNK_BITS_EXPONENT*)plist)->exp;

    return CNK_BITSOFF_SIZE;
}

static Sint32
rjCnkSetCache(RJS_CNK_STRIP* restrict pStrip, const Sint16* restrict plist)
{
    const CNK_BITS_HEAD*     restrict p_bits  = (const void*) plist;
    const CNK_BITS_POLYLIST* restrict p_cache = (const void*) &p_bits->d;

    const s32 ix_cache = p_cache->list;

    _nj_cnk_polygon_cache_tbl_[ix_cache] = plist + CNK_BITSOFF_SIZE; // cache next offset

    _nj_cnk_polygon_cache_num_++;

    return CNK_BITSOFF_SIZE;
}

static const Sint16* restrict
rjCnkDrawCache(RJS_CNK_STRIP* restrict pStrip, const Sint16* restrict plist)
{
    const CNK_BITS_HEAD*     restrict p_bits  = (const void*) plist;
    const CNK_BITS_POLYLIST* restrict p_cache = (const void*) &p_bits->d;

    const s32 ix_cache = p_cache->list;

    _nj_cnk_polygon_cache_num_--;

    return _nj_cnk_polygon_cache_tbl_[ix_cache];
}

static Sint32
rjCnkSetMaterial(RJS_CNK_STRIP* restrict pStrip, const Sint16* restrict plist)
{
    rjCnkSetBlend(pStrip, plist);

    const CNK_MATERIAL_HEAD* restrict p_mat = (void*) plist;

    int nb_mat = 0;

    if ( p_mat->head & 1 ) pStrip->mats[RJ_CMC_DIFF] = p_mat->d[ nb_mat++ ];
    if ( p_mat->head & 2 ) pStrip->mats[RJ_CMC_AMBI] = p_mat->d[ nb_mat++ ];
    if ( p_mat->head & 4 ) pStrip->mats[RJ_CMC_SPEC] = p_mat->d[ nb_mat++ ];

    return p_mat->size + CNK_MATOFF_SIZE_ADD;
}

static Sint32
rjCnkSetTexture(RJS_CNK_STRIP* restrict pStrip, const Sint16* restrict plist)
{
    const CNK_TINY_HEAD* restrict p_tiny = (void*) plist;

    pStrip->tiny  = *p_tiny;
    pStrip->texid = _rj_cnk_texture_callback_( p_tiny->texid );

    return CNK_TINYOFF_SIZE;
}

static Sint32
rjCnkSetStrip(RJS_CNK_STRIP* restrict pStrip, const Sint16* restrict plist)
{
    const CNK_STRIP_HEAD* restrict p_striph = (void*) plist;

    Uint16 fst = p_striph->flag << NJD_FST_SHIFT;

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

    if ( !(_rj_cnk_context_.flag & RJD_CXF_BACKFACECULL) )
    {
        fst |= (NJD_FST_DB);
    }

    switch ( _rj_cnk_context_.depthq )
    {
        case RJ_CNK_DQ_OFF:
        case RJ_CNK_DQ_NEAR:
        {
            break;
        }
        case RJ_CNK_DQ_ON:
        {
            fst |= NJD_FST_UA;
            break;
        }
    }

    const Uint32 sttype = p_striph->head;

    pStrip->flag = (fst | sttype);

    if ( (sttype - NJD_STRIPOFF) % 3 ) // UVN/UVH
    {
        pStrip->flag |= (RJD_CSF_USETEX|RJD_CSF_HASUVS);
    }
    else if ( fst & NJD_FST_ENV )
    {
        pStrip->flag |= RJD_CSF_USETEX;
    }

    if ( sttype >= NJD_CS_VN )
    {
        pStrip->flag |= ( sttype <= NJD_CS_UVH_VN ) ? RJD_CSF_HASNRM : RJD_CSF_HASCOL;
    }

    pStrip->ctrl3d = _nj_control_3d_flag_;
    pStrip->striph = p_striph;

    return p_striph->size + CNK_STRIPOFF_SIZE_ADD;
}

/****** Start Attribute *************************************************************************/
static void
rjCnkStripStartTexture(const RJS_CNK_STRIP* restrict strip)
{
    EXTERN NJS_TEXNAME texture_rf_texerr[];

    if ( !(strip->flag & RJD_CSF_USETEX) )
    {
        return;
    }

    if ( AS_INT(_rj_cnk_context_.tiny) == AS_INT(strip->tiny) && _rj_cnk_context_.texid == strip->texid )
    {
        return;
    }

    /** get texture **/

    const s16 texid = strip->texid;

    const NJS_TEXLIST* p_tls = njGetCurrentTexList();

    if ( !p_tls || texid >= (s16)p_tls->nbTexture )
    {
    TEX_ERR:
        const NJS_TEXMANAGE* p_texman = (NJS_TEXMANAGE*) texture_rf_texerr[0].texaddr;
        const NJS_TEXSYSTEM* p_texsys = p_texman->texsys;

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

        _rj_cnk_context_.tiny = (CNK_TINY_HEAD){ 0 };
        return;
    }

    const NJS_TEXMANAGE* p_texman = (NJS_TEXMANAGE*) p_tls->textures[texid].texaddr;

    if (!p_texman) goto TEX_ERR;

    const NJS_TEXSYSTEM* p_texsys = p_texman->texsys;

    if (!p_texsys) goto TEX_ERR;

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

    switch ( strip->tiny.filter )
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

    switch ( strip->tiny.flip )
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

    switch ( strip->tiny.clamp )
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

    RX_SetTexture( p_tinfo, 0 );

    _rj_cnk_context_.texid = strip->texid;
    _rj_cnk_context_.tiny  = strip->tiny;
}

static void
rjCnkStripStartShading(const RJS_CNK_STRIP* restrict strip)
{
    rjSetPolygonShading( strip->flag & NJD_FST_FL ? RJ_SHADE_FLAT : RJ_SHADE_GOURAUD );

    rjSetTextureParamCtx();
}

static void
rjCnkStripStartMaterial(const RJS_CNK_STRIP* restrict strip)
{
    const RFRS_CNKFUNCMD funcmd = RFRS_GetCnkFuncMode();

    const Uint32 nj3dflag = strip->ctrl3d;

    /****** Diffuse Material ****************************************************************/

    NJS_ARGB diff;

    /** Get initial material color **/
    {
        if ( nj3dflag & NJD_CONTROL_3D_CONSTANT_MATERIAL )
        {
            diff = _nj_constant_material_;
        }
        else if ( nj3dflag & NJD_CONTROL_3D_OFFSET_MATERIAL )
        {
            BgraToArgb(&strip->mats[RJ_CMC_DIFF], &diff);

            diff.a += _nj_constant_material_.a;
            diff.r += _nj_constant_material_.r;
            diff.g += _nj_constant_material_.g;
            diff.b += _nj_constant_material_.b;
        }
        else // no control flags
        {
            BgraToArgb(&strip->mats[RJ_CMC_DIFF], &diff);
        }
    }

    /** Adjust diffuse depending on Ninja, draw function, and strip context **/

    /** If using texture AND is not DirectDraw, ELSE keep diffuse **/
    if ( (strip->flag & RJD_CSF_USETEX) && funcmd != RFRS_CNKFUNCMD_DIRECT )
    {
        /** If EasyDraw/EasyMultiDraw **/
        if ( funcmd & RFRS_CNKFUNCMD_EASYBIT )
        {
            diff.r = 1.f;
            diff.g = 1.f;
            diff.b = 1.f;
        }
        /** Constant Texture Material flag, SimpleDraw is implied here **/
        else if ( nj3dflag & NJD_CONTROL_3D_CONSTANT_TEXTURE_MATERIAL )
        {
            /** is NormalDraw                    OR is SimpleMulti                   OR  not CnkS type **/
            if ( funcmd == RFRS_CNKFUNCMD_NORMAL || (funcmd & RFRS_CNKFUNCMD_MULTIBIT) || (strip->flag & RJD_CSF_HASUVS) )
            {
                diff.r = 1.f;
                diff.g = 1.f;
                diff.b = 1.f;
            }
            else goto KEEP_DIFFUSE;
        }
        else goto KEEP_DIFFUSE;
    }
    else // keep diffuse as-is
    {
    KEEP_DIFFUSE:
        diff.r = CLAMP(diff.r, 0.f, 1.f);
        diff.g = CLAMP(diff.g, 0.f, 1.f);
        diff.b = CLAMP(diff.b, 0.f, 1.f);
    }

    diff.a = CLAMP(diff.a, 0.f, 1.f);

    /** apply diffuse **/

    _rj_cnk_diff_material_ = diff;

    /****** Ambient Material ****************************************************************/

    if ( strip->flag & NJD_FST_IA )
    {
        _rj_cnk_ambi_material_.r = 0.f;
        _rj_cnk_ambi_material_.g = 0.f;
        _rj_cnk_ambi_material_.b = 0.f;
    }
    else if ( _rj_cnk_context_.flag & RJD_CXF_AMBIMATERIAL )
    {
        _rj_cnk_ambi_material_.r = _rj_cnk_light_ambient_.r * ( (f32)strip->mats[RJ_CMC_AMBI].r * (1.f/255.f) );
        _rj_cnk_ambi_material_.g = _rj_cnk_light_ambient_.g * ( (f32)strip->mats[RJ_CMC_AMBI].g * (1.f/255.f) );
        _rj_cnk_ambi_material_.b = _rj_cnk_light_ambient_.b * ( (f32)strip->mats[RJ_CMC_AMBI].b * (1.f/255.f) );
    }
    else
    {
        _rj_cnk_ambi_material_.r = _rj_cnk_light_ambient_.r;
        _rj_cnk_ambi_material_.g = _rj_cnk_light_ambient_.g;
        _rj_cnk_ambi_material_.b = _rj_cnk_light_ambient_.b;
    }

    /****** Specular Material ***************************************************************/

    _rj_cnk_spec_material_.a =  (Float)strip->mats[RJ_CMC_SPEC].a;
    _rj_cnk_spec_material_.r = ((Float)strip->mats[RJ_CMC_SPEC].r * (1.f/255.f));
    _rj_cnk_spec_material_.g = ((Float)strip->mats[RJ_CMC_SPEC].g * (1.f/255.f));
    _rj_cnk_spec_material_.b = ((Float)strip->mats[RJ_CMC_SPEC].b * (1.f/255.f));
}

static void
rjCnkStripStartAlpha(const RJS_CNK_STRIP* restrict strip)
{
    RJ_ALPHA alphamd;

    const s32 bld_src = (strip->blend & NJD_FBS_MASK);
    const s32 bld_dst = (strip->blend & NJD_FBD_MASK);

    if ( strip->flag & RJD_FST_TRANSLUCENT )
    {
        if ( strip->ctrl3d & NJD_CONTROL_3D_USE_PUNCHTHROUGH )
        {
            alphamd = RJ_ALPHA_PUNCHTHROUGH;
        }
        else // not punchthrough
        {
            if ( (bld_src == NJD_FBS_ONE) || (bld_dst == NJD_FBD_ONE) )                 
            {
                alphamd = RJ_ALPHA_TRANSLUCENT;
            }
            else if ( strip->flag & RJD_FST_EUA )
            {
                alphamd = (strip->flag & NJD_FST_UA) ? RJ_ALPHA_ALPHATEST : RJ_ALPHA_TRANSLUCENT;
            }
            else if ( (strip->flag & RJD_CSF_USETEX) && pTexSurface->Type == 14 && !(_nj_curr_ctx_->tspparam & NJD_IGNORETEXALPHA_ON) )
            {
                alphamd = RJ_ALPHA_ALPHATEST;
            }
            else
            {
                alphamd = RJ_ALPHA_TRANSLUCENT;
            }
        }
    }
    else // opaque strip
    {
        alphamd = RJ_ALPHA_OPAQUE;
    }

    rjSetAlphaMode(bld_src>>NJD_FBS_SHIFT, bld_dst>>NJD_FBD_SHIFT, alphamd);
}

static void
rjCnkStripStartVertex(const RJS_CNK_STRIP* restrict strip)
{
    if ( strip->flag & RJD_CSF_USETEX )
    {
        rjCnkStartVertexTex();
    }
    else
    {
        rjCnkStartVertexNonTex();
    }
}

static size
rjCnkExecPlist(const Sint16* restrict pPList, RJS_CNK_STRIP* pOutStrips)
{
    const bool trans_only = (RFRS_GetCullMode() == RFRS_CULLMD_INVERSE);

    RJS_CNK_STRIP* restrict p_stentry = pOutStrips;

    size nb_strip = 0;

    const Sint16* plist = pPList;

    for ( ; ; )
    {
        const int type = CNK_GET_OFFTYPE(plist);

        if ( type == NJD_CE )
        {
            break; // END PLIST
        }

        if ( type == NJD_CN )
        {
            plist += CNK_NULLOFF_SIZE;
            continue;
        }

        if ( type <= CNK_BITSOFF_MAX )
        {
            const CNK_BITS_HEAD* restrict p_bits = (const void*) plist;

            /** NJD_BITSOFF **/
            switch ( type )
            {
                case NJD_CB_BA: // CnkBits Blend Alpha
                {
                    rjCnkSetBlend(p_stentry, plist);
                    break;
                }
                case NJD_CB_DA: // CnkBits mipmap 'D' Adjust
                {
                    break;
                }
                case NJD_CB_EXP: // CnkBits specular EXPonent
                {
                    rjCnkSetExponent(p_stentry, plist);
                    break;
                }
                case NJD_CB_CP: // CnkBits Cache Polygons
                {
                    rjCnkSetCache(p_stentry, plist);
                    return nb_strip;
                }
                case NJD_CB_DP: // CnkBits Draw Polygons
                {
                    const Sint16* restrict p_cache = rjCnkDrawCache(p_stentry, plist);

                    nb_strip += rjCnkExecPlist( p_cache, &pOutStrips[nb_strip] );
                    p_stentry = &pOutStrips[ nb_strip ];
                    break;
                }
            }

            /** Next offset **/
            plist += CNK_BITSOFF_SIZE;
            continue;
        }

        if ( type <= CNK_TINYOFF_MAX )
        {
            plist += rjCnkSetTexture(p_stentry, plist);
            continue;
        }

        if ( type <= CNK_MATOFF_MAX )
        {
            plist += rjCnkSetMaterial(p_stentry, plist);
            continue;
        }

        if ( type <= CNK_STRIPOFF_MAX )
        {
            plist += rjCnkSetStrip(p_stentry, plist);
            /*
            *     This is an optimization. If we cull out strips that can't be drawn anyway, we
            *   don't have to handle them during the build index or draw index stages. If you
            *   remove this, the result will be the same but it will be a bit slower.
            */
            if ( trans_only && !(p_stentry->flag & NJD_FST_DB) )
            {
                continue;
            }

            nb_strip++;

            if ( nb_strip >= RJD_CST_MAX ) 
            {
                RF_DbgWarn("Ran out of Chunk strip slots!");
                return nb_strip;
            }

            // push
            p_stentry[1] = p_stentry[0];
            p_stentry++;

            continue;
        }

        /** An error occured, stop **/
        break;
    }

    return nb_strip;
}

static void
rjCnkStripStartPolygon(Uint32 flag)
{
    if ( flag & RJD_CSD_NORMAL )
    {
        rjInvertPolygons( OFF );

        rjCnkInvertLightDirection( OFF );

        if ( flag & RJD_CSD_INVERT )
        {
            rjCnkPolygonCulling( RJ_CULL_NONE );
            return;
        }
    }
    else // inverse only
    {
        rjInvertPolygons( ON );

        rjCnkInvertLightDirection( _rj_cnk_context_.flag & RJD_CXF_TWOPASSLIGHT );
    }

    rjCnkPolygonCulling( RJ_CULL_CW );
}

static void
rjCnkStripDraw(const RJS_CNK_STRIP* restrict strip, const RJS_VERTEX_BUF* restrict vbuf, Uint32 flag)
{
    /*
    *     If neither normal polygons or inverted polygons are being drawn this pass, then we
    *   can stop right here before going any further.
    */
    if ( !(flag & (RJD_CSD_NORMAL|RJD_CSD_INVERT)) )
    {
        return;
    }

    if ( !(flag & RJD_CSD_SKIPMAT) )
    {
        /*
        *   Alpha must run after Texture, as the alpha code checks the current texture
        */
        rjCnkStripStartTexture( strip );
        rjCnkStripStartAlpha( strip );
        rjCnkStripStartShading( strip );
        rjCnkStripStartMaterial( strip );
        rjCnkStripStartVertex( strip );
    }

    rjCnkStripStartPolygon( flag );

    switch ( STSW( strip->flag & RJD_CSF_MASK_TYPE ) )
    {
        case STSW( NJD_CS ):
        {
            rjCnkStrip(strip, vbuf);
            break;
        }
        case STSW( NJD_CS_UVN ):
        {
            rjCnkStripUV(strip, vbuf, IS_UVN);
            break;
        }
        case STSW( NJD_CS_UVH ):
        {
            rjCnkStripUV(strip, vbuf, IS_UVH);
            break;
        }
        case STSW( NJD_CS_VN ):
        {
            rjCnkStripVN(strip, vbuf);
            break;
        }
        case STSW( NJD_CS_UVN_VN ):
        {
            rjCnkStripUVVN(strip, vbuf, IS_UVN);
            break;
        }
        case STSW( NJD_CS_UVH_VN ):
        {
            rjCnkStripUVVN(strip, vbuf, IS_UVH);
            break;
        }
        case STSW( NJD_CS_D8 ):
        {
            rjCnkStripD8(strip, vbuf);
            break;
        }
        case STSW( NJD_CS_UVN_D8 ):
        {
            rjCnkStripUVD8(strip, vbuf, IS_UVN);
            break;
        }
        case STSW( NJD_CS_UVH_D8 ):
        {
            rjCnkStripUVD8(strip, vbuf, IS_UVH);
            break;
        }
    }

    if ( !(flag & RJD_CSD_SKIPEND) )
    {
        rjCnkEndVertex();
    }
}

static void
rjCnkStripDrawList(const RJS_CNK_STRIP* restrict strips, const size nbStrip, const RJS_VERTEX_BUF* restrict vbuf)
{
#define STDRAW_OPAQUE       (1<<0)
#define STDRAW_TRANS        (1<<1)

    /*
    *     To handle the configurable cull modes, we & away any flags we don't want to be used
    *   during the draw stage. This is simple for the CPU and simple for me to wrap my head
    *   around (I tried a lot of ideas before this).
    */
    Uint32 csd_and;

    switch ( RFRS_GetCullMode() )
    {
        case RFRS_CULLMD_AUTO: default:
        case RFRS_CULLMD_NONE:
        {
            csd_and = ~0;
            break;
        }
        case RFRS_CULLMD_NORMAL:
        {
            csd_and = ~(RJD_CSD_INVERT|RJD_CSD_SKIPEND|RJD_CSD_SKIPMAT);
            break;
        }
        case RFRS_CULLMD_INVERSE:
        {
            csd_and = ~(RJD_CSD_NORMAL|RJD_CSD_SKIPEND|RJD_CSD_SKIPMAT);
            break;
        }
    }
    /*
    *     To handle the configurable transparency modes, we handle the mode logic here and
    *   check the flags during the different passes.
    */
    Uint32 drawattr;

    switch ( RFRS_GetCnkDrawMode() )
    {
        case RFRS_CNKDRAWMD_ALL: default:
        {
            drawattr = (STDRAW_OPAQUE|STDRAW_TRANS);
            break;
        }
        case RFRS_CNKDRAWMD_OPAQUE:
        {
            drawattr = (STDRAW_OPAQUE);
            break;
        }
        case RFRS_CNKDRAWMD_TRANSPARENT:
        {
            drawattr = (STDRAW_TRANS);
            break;
        }
    }

    /****** Opaque **************************************************************************/

    if ( drawattr & STDRAW_OPAQUE )
    {
        const Uint32 ctxflg = _rj_cnk_context_.flag;
        const Sint16 vattr  = _rj_cnk_context_.vattr;

        const bool has_vnrm = vattr & RJD_CVF_NORMAL;
        const bool has_vcol = vattr & RJD_CVF_COLOR;

        for ( size ix_st = 0; ix_st < nbStrip; ++ix_st )
        {
            const RJS_CNK_STRIP* p_strip = &strips[ix_st];

            if ( CheckTrans(p_strip) )
            {
                continue;
            }

            if ( ctxflg & RJD_CXF_BACKFACECULL )
            {
                if ( p_strip->flag & NJD_FST_DB )
                {
                    /*
                    *     These are an optimization. If lighting isn't going to be used, or if
                    *   two pass lighting is disabled, we have no need to draw opaque strips in
                    *   two passes (technically one pass with doubled polygons).
                    */
                    if ( !(ctxflg & RJD_CXF_TWOPASSLIGHT) )
                    {
                        goto OPAQUE_ONEPASS;
                    }

                    const bool has_color = ( has_vcol || p_strip->flag & RJD_CSF_HASCOL );
                    const bool has_nrmal = ( has_vnrm || p_strip->flag & RJD_CSF_HASNRM );

                    if ( has_color && (!(ctxflg & RJD_CXF_VND8) || !has_nrmal) )
                    {
                        goto OPAQUE_ONEPASS;
                    }

                    // draw two pass

                    rjCnkStripDraw( p_strip, vbuf, (RJD_CSD_NORMAL|RJD_CSD_SKIPEND) & csd_and );
                    rjCnkStripDraw( p_strip, vbuf, (RJD_CSD_INVERT|RJD_CSD_SKIPMAT) & csd_and );
                }
                else // not double sided
                {
                    rjCnkStripDraw( p_strip, vbuf, (RJD_CSD_NORMAL) & csd_and );
                }
            }
            else // no culling / twopass lighting
            {
            OPAQUE_ONEPASS:
                rjCnkStripDraw( p_strip, vbuf, (RJD_CSD_NORMAL|RJD_CSD_INVERT) & csd_and );
            }
        }
    }

    /****** Translucent *********************************************************************/
    /*
    *     For the translucent pass, we need to seperate out the normal and inverse triangles
    *   for easy transparency sorting. Models can be drawn with inverted scaling though, which
    *   reverses the order we need to draw them in. The 'NJD_CONTROL_3D_MIRROR_MODEL' flag
    *   determines if the reverse order should be used.
    */
    if ( drawattr & STDRAW_TRANS )
    {
        bool do_inv = !( _nj_control_3d_flag_ & NJD_CONTROL_3D_MIRROR_MODEL );

        for ( int i = 0; i < 2; ++i )
        {
            const Uint16 csd_on = do_inv ? RJD_CSD_INVERT : RJD_CSD_NORMAL;

            for ( size ix_st = 0; ix_st < nbStrip; ++ix_st )
            {
                const RJS_CNK_STRIP* p_strip = &strips[ix_st];

                if ( !CheckTrans(p_strip) || ( do_inv && !(p_strip->flag & NJD_FST_DB) ) )
                {
                    continue;
                }

                rjCnkStripDraw( p_strip, vbuf, csd_on & csd_and );
            }

            do_inv = !do_inv;
        }
    }

#undef STDRAW_OPAQUE
#undef STDRAW_TRANS
}

/****** Extern **********************************************************************************/
void
rjCnkPList(const Sint16* restrict plist, const RJS_VERTEX_BUF* restrict vbuf)
{
    static RJS_CNK_STRIP strips[RJD_CST_MAX];

    rjCnkStartPlist( &strips[0] );

    // build strips and exec
    const size nb_strip = rjCnkExecPlist( plist, strips );

    if ( !nb_strip )
    {
        return;
    }

    rjCnkStripDrawList( strips, nb_strip, vbuf );
    rjCnkEndPlist();
}
