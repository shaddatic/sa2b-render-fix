/************************/
/*  Includes            */
/************************/
/****** Core Toolkit ****************************************************************/
#include <samt/core.h>      /* core                                                 */
#include <samt/memory.h>    /* MemCopy                                              */

/****** Ninja ***********************************************************************/
#include <samt/ninja/ninja.h> /* ninja                                              */

/****** GX **************************************************************************/
#include <samt/gx/gx.h>     /* GX                                                   */

/****** Render Fix ******************************************************************/
#include <rf_core.h>        /* core                                                 */
#include <rf_renderstate.h> /* render state                                         */
#include <rf_util.h>        /* utility                                              */
#include <rf_magic.h>       /* magic                                                */

/****** Self ************************************************************************/
#include <rf_draw/rfd_cnkmdl/rfdcnk_plist/rfdcpl_internal.h> /* parent & siblings   */
#include <rf_draw/rfd_cnkmdl/rfdcnk_plist/rfdcpl_cmn.h>      /* common              */

/************************/
/*  Source              */
/************************/
/****** Check Specular **************************************************************/
static inline bool
UseSpecular(const CNK_CTX* restrict pCtx)
{
    return ( !(pCtx->fst & NJD_FST_IS) );
}

RJS_UV
rjCnkGetUvScroll(void)
{
    return _rj_cnk_uv_scroll_;
}

RJS_UV
rjCnkGetEnvUvScroll(void)
{
    return (_nj_control_3d_flag_ & NJD_CONTROL_3D_ENV_UV_SCROLL) ? _rj_cnk_env_scroll_ : (RJS_UV){0};
}

/************************************************************************************/
/*
*   Draw Strip
*/
/****** Normal **********************************************************************/
static void
rjCnkDrawStripUV(const CNK_STRIP_HEAD* restrict striph, Sint32 uvh, const CNK_VERTEX_BUFFER* restrict vbuf, RJE_CNK_VCOLFUNC cfunc, RJE_CNK_SPECFUNC sfunc)
{
    RJF_CNK_VCOLFUNC* const fn_color = _rj_cnk_vcol_funcs_[cfunc];
    RJF_CNK_SPECFUNC* const fn_specu = _rj_cnk_spec_funcs_[sfunc];

    const RJS_UV uv_off = rjCnkGetUvScroll();

    const f32 uv_mul = GET_UV_MUL(uvh);

    const int nb_strip = striph->nbstrip;
    const int ufo      = striph->ufo;

    const CNK_STRIP_UV* p_st = (const CNK_STRIP_UV*) striph->d;

    for (int ix_strip = 0; ix_strip < nb_strip; ++ix_strip)
    {
        const int len = rjStartTriStrip( p_st->len );

        RJS_VERTEX_PTCS* p_buf = rjGetVertexBuffer();

        // get strip array
        const CNK_ST_UV* restrict p_polyvtx = p_st->d;

        for (int i = 0; i < len; ++i)
        {
            const CNK_VERTEX_BUFFER* restrict p_vtx = &vbuf[ p_polyvtx->i ];

            // set position
            p_buf->pos = p_vtx->pos;

            // set uv coords
            p_buf->u = ((Float)p_polyvtx->u * uv_mul) + uv_off.u;
            p_buf->v = ((Float)p_polyvtx->v * uv_mul) + uv_off.v;

            // set color
            p_buf->col = fn_color( p_vtx );

            // set specular
            p_buf->spc = fn_specu( p_vtx );

            /** End set buffer **/

            ++p_buf;

            // next polygon vertex
            p_polyvtx = NEXT_STRIP_POLY(p_polyvtx, i, ufo);
        }

        rjEndTriStrip(len);

        // next strip chunk starts at the end of the current one
        p_st = (void*) p_polyvtx;
    }
}

/****** Environment *****************************************************************/
static void
rjCnkDrawStripUV_ENV(const CNK_STRIP_HEAD* restrict striph, const CNK_VERTEX_BUFFER* restrict vbuf, RJE_CNK_VCOLFUNC cfunc, RJE_CNK_SPECFUNC sfunc)
{
    RJF_CNK_VCOLFUNC* const fn_color = _rj_cnk_vcol_funcs_[cfunc];
    RJF_CNK_SPECFUNC* const fn_specu = _rj_cnk_spec_funcs_[sfunc];

    const RJS_UV uv_off = rjCnkGetEnvUvScroll();

    const int nb_strip = striph->nbstrip;
    const int ufo      = striph->ufo;

    const CNK_STRIP_UV* p_st = (const CNK_STRIP_UV*) striph->d;

    for (int ix_strip = 0; ix_strip < nb_strip; ++ix_strip)
    {
        const int len = rjStartTriStrip( p_st->len );

        RJS_VERTEX_PTCS* p_buf = rjGetVertexBuffer();

        // get strip array
        const CNK_ST_UV* restrict p_polyvtx = p_st->d;

        for (int i = 0; i < len; ++i)
        {
            const CNK_VERTEX_BUFFER* restrict p_vtx = &vbuf[ p_polyvtx->i ];

            // set position
            p_buf->pos = p_vtx->pos;

            // set uv coords
            p_buf->u = (( p_vtx->nrm.x * 0.5f) + 0.5f) + uv_off.u;
            p_buf->v = ((-p_vtx->nrm.y * 0.5f) + 0.5f) + uv_off.v;

            // set color
            p_buf->col = fn_color( p_vtx );

            // set specular
            p_buf->spc = fn_specu( p_vtx );

            /** End set buffer **/

            ++p_buf;

            // next polygon vertex
            p_polyvtx = NEXT_STRIP_POLY(p_polyvtx, i, ufo);
        }

        rjEndTriStrip(len);

        // next strip chunk starts at the end of the current one
        p_st = (void*) p_polyvtx;
    }
}

/****** Position Environment ********************************************************/
static void
rjCnkDrawStripUV_POS(const CNK_STRIP_HEAD* restrict striph, const CNK_VERTEX_BUFFER* restrict vbuf, RJE_CNK_VCOLFUNC cfunc, RJE_CNK_SPECFUNC sfunc)
{
    RJF_CNK_VCOLFUNC* const fn_color = _rj_cnk_vcol_funcs_[cfunc];
    RJF_CNK_SPECFUNC* const fn_specu = _rj_cnk_spec_funcs_[sfunc];

    const RJS_UV uv_off = rjCnkGetEnvUvScroll();

    const int nb_strip = striph->nbstrip;
    const int ufo      = striph->ufo;

    const CNK_STRIP_UV* p_st = (const CNK_STRIP_UV*) striph->d;

    for (int ix_strip = 0; ix_strip < nb_strip; ++ix_strip)
    {
        const int len = rjStartTriStrip( p_st->len );

        RJS_VERTEX_PTCS* p_buf = rjGetVertexBuffer();

        // get strip array
        const CNK_ST_UV* restrict p_polyvtx = p_st->d;

        for (int i = 0; i < len; ++i)
        {
            const CNK_VERTEX_BUFFER* restrict p_vtx = &vbuf[ p_polyvtx->i ];

            // set position
            p_buf->pos = p_vtx->pos;

            // set uv coords
            p_buf->u = -p_vtx->pos.x + uv_off.u;
            p_buf->v = -p_vtx->pos.y + uv_off.v;

            // set color
            p_buf->col = fn_color( p_vtx );

            // set specular
            p_buf->spc = fn_specu( p_vtx );

            /** End set buffer **/

            ++p_buf;

            // next polygon vertex
            p_polyvtx = NEXT_STRIP_POLY(p_polyvtx, i, ufo);
        }

        rjEndTriStrip(len);

        // next strip chunk starts at the end of the current one
        p_st = (void*) p_polyvtx;
    }
}

/************************************************************************************/
/*
*   Draw Strip (Flat Shading)
*/
/****** Normal Flat *****************************************************************/
static void
rjCnkDrawStripUV_FL(const CNK_STRIP_HEAD* restrict striph, Sint32 uvh, const CNK_VERTEX_BUFFER* restrict vbuf, RJE_CNK_VCOLFUNC cfunc, RJE_CNK_SPECFUNC sfunc)
{
    RJF_CNK_VCOLFUNC* const fn_color = _rj_cnk_vcol_funcs_[cfunc];
    RJF_CNK_SPECFUNC* const fn_specu = _rj_cnk_spec_funcs_[sfunc];

    const RJS_UV uv_off = rjCnkGetUvScroll();

    const f32 uv_mul = GET_UV_MUL(uvh);

    const int nb_strip = striph->nbstrip;
    const int ufo      = striph->ufo;

    const CNK_STRIP_UV* p_st = (const CNK_STRIP_UV*) striph->d;

    for (int ix_strip = 0; ix_strip < nb_strip; ++ix_strip)
    {
        Bool invst;
        const Sint32 len = rjStartTriDestrip( p_st->len, &invst );

        // get vertex buffer
        RJS_VERTEX_PTCS* p_buf_base = rjGetVertexBuffer();

        // get strip array
        const CNK_ST_UV* restrict p_st_base = p_st->d;

        for (int ix_poly = 0, ix_vert = 0; ix_vert < len; ++ix_poly, ix_vert += 3)
        {
            RJS_VERTEX_PTCS* p_buf = p_buf_base;

            const CNK_ST_UV* restrict p_polyvtx = p_st_base;

            int buf_inc;

            DESTRIP_START(p_buf, buf_inc, invst);

            const CNK_VERTEX_BUFFER* restrict p_last_vtx;

            for (int j = 0; j < 3; ++j)
            {
                const CNK_VERTEX_BUFFER* restrict p_vtx = &vbuf[ p_polyvtx->i ];

                // set position
                p_buf->pos = p_vtx->pos;

                // set uv coords
                p_buf->u = ((Float)p_polyvtx->u * uv_mul) + uv_off.u;
                p_buf->v = ((Float)p_polyvtx->v * uv_mul) + uv_off.v;

                p_last_vtx = p_vtx;

                /** End set buffer vertex **/

                p_buf += buf_inc;

                // to next polygon vertex
                p_polyvtx = NEXT_STRIP_POLY(p_polyvtx, ix_poly+j, ufo);
            }

            // get color/spec
            const Uint32 color = fn_color(p_last_vtx);
            const Uint32 specu = fn_specu(p_last_vtx);

            // set color/spec
            p_buf_base[0].col = color;
            p_buf_base[0].spc = specu;
            p_buf_base[1].col = color;
            p_buf_base[1].spc = specu;
            p_buf_base[2].col = color;
            p_buf_base[2].spc = specu;

            p_buf_base += 3;

            // swap strip winding mode for next polygon
            invst = !invst;

            // base to next polygon vertex
            p_st_base = NEXT_STRIP_POLY(p_st_base, ix_poly, ufo);
        }

        rjEndTriDestrip(len);

        // we're now two strip indexes short
        p_st_base = CNK_NEXT_POLY(p_st_base, ufo);
        p_st_base = CNK_NEXT_POLY(p_st_base, ufo);

        // next strip chunk starts at the end of the current one
        p_st = (void*) p_st_base;
    }
}

/****** Environment Flat ************************************************************/
static void
rjCnkDrawStripUV_ENV_FL(const CNK_STRIP_HEAD* restrict striph, const CNK_VERTEX_BUFFER* restrict vbuf, RJE_CNK_VCOLFUNC cfunc, RJE_CNK_SPECFUNC sfunc)
{
    RJF_CNK_VCOLFUNC* const fn_color = _rj_cnk_vcol_funcs_[cfunc];
    RJF_CNK_SPECFUNC* const fn_specu = _rj_cnk_spec_funcs_[sfunc];

    const RJS_UV uv_off = rjCnkGetEnvUvScroll();

    const int nb_strip = striph->nbstrip;
    const int ufo      = striph->ufo;

    const CNK_STRIP_UV* p_st = (const CNK_STRIP_UV*) striph->d;

    for (int ix_strip = 0; ix_strip < nb_strip; ++ix_strip)
    {
        Bool invst;
        const Sint32 len = rjStartTriDestrip( p_st->len, &invst );

        // get vertex buffer
        RJS_VERTEX_PTCS* p_buf_base = rjGetVertexBuffer();

        // get strip array
        const CNK_ST_UV* restrict p_polyvtx_base = p_st->d;

        for (int ix_poly = 0, ix_vert = 0; ix_vert < len; ++ix_poly, ix_vert += 3)
        {
            RJS_VERTEX_PTCS* p_buf = p_buf_base;

            const CNK_ST_UV* restrict p_polyvtx = p_polyvtx_base;

            int buf_inc;

            DESTRIP_START(p_buf, buf_inc, invst);

            const CNK_VERTEX_BUFFER* restrict p_last_vtx;

            for (int j = 0; j < 3; ++j)
            {
                const CNK_VERTEX_BUFFER* restrict p_vtx = &vbuf[ p_polyvtx->i ];

                // set position
                p_buf->pos = p_vtx->pos;

                // set uv coords
                p_buf->u = (( p_vtx->nrm.x * 0.5f) + 0.5f) + uv_off.u;
                p_buf->v = ((-p_vtx->nrm.y * 0.5f) + 0.5f) + uv_off.v;

                p_last_vtx = p_vtx;

                /** End set buffer vertex **/

                p_buf += buf_inc;

                // to next polygon vertex
                p_polyvtx = NEXT_STRIP_POLY(p_polyvtx, ix_poly+j, ufo);
            }

            // get color/spec
            const Uint32 color = fn_color(p_last_vtx);
            const Uint32 specu = fn_specu(p_last_vtx);

            // set color/spec
            p_buf_base[0].col = color;
            p_buf_base[0].spc = specu;
            p_buf_base[1].col = color;
            p_buf_base[1].spc = specu;
            p_buf_base[2].col = color;
            p_buf_base[2].spc = specu;

            p_buf_base += 3;

            // swap strip winding mode for next polygon
            invst = !invst;

            // base to next polygon vertex
            p_polyvtx_base = NEXT_STRIP_POLY(p_polyvtx_base, ix_poly, ufo);
        }

        rjEndTriDestrip(len);

        // we're now two strip indexes short
        p_polyvtx_base = CNK_NEXT_POLY(p_polyvtx_base, ufo);
        p_polyvtx_base = CNK_NEXT_POLY(p_polyvtx_base, ufo);

        // next strip chunk starts at the end of the current one
        p_st = (void*) p_polyvtx_base;
    }
}

/****** Positional Environment Flat *************************************************/
static void
rjCnkDrawStripUV_POS_FL(const CNK_STRIP_HEAD* restrict striph, const CNK_VERTEX_BUFFER* restrict vbuf, RJE_CNK_VCOLFUNC cfunc, RJE_CNK_SPECFUNC sfunc)
{
    RJF_CNK_VCOLFUNC* const fn_color = _rj_cnk_vcol_funcs_[cfunc];
    RJF_CNK_SPECFUNC* const fn_specu = _rj_cnk_spec_funcs_[sfunc];
    
    f32 offset_u;
    f32 offset_v;

    if ( _nj_control_3d_flag_ & NJD_CONTROL_3D_ENV_UV_SCROLL )
    {
        offset_u = _rj_cnk_env_scroll_.u;
        offset_v = _rj_cnk_env_scroll_.v;
    }
    else
    {
        offset_u = 0.f;
        offset_v = 0.f;
    }

    const int nb_strip = striph->nbstrip;
    const int ufo      = striph->ufo;

    const CNK_STRIP_UV* p_st = (const CNK_STRIP_UV*) striph->d;

    for (int ix_strip = 0; ix_strip < nb_strip; ++ix_strip)
    {
        Bool invst;
        const Sint32 len = rjStartTriDestrip( p_st->len, &invst );

        // get vertex buffer
        RJS_VERTEX_PTCS* p_buf_base = rjGetVertexBuffer();

        // get strip array
        const CNK_ST_UV* restrict p_polyvtx_base = p_st->d;

        for (int ix_poly = 0, ix_vert = 0; ix_vert < len; ++ix_poly, ix_vert += 3)
        {
            RJS_VERTEX_PTCS* p_buf = p_buf_base;

            const CNK_ST_UV* restrict p_polyvtx = p_polyvtx_base;

            int buf_inc;

            DESTRIP_START(p_buf, buf_inc, invst);

            const CNK_VERTEX_BUFFER* restrict p_last_vtx;

            for (int j = 0; j < 3; ++j)
            {
                const CNK_VERTEX_BUFFER* restrict p_vtx = &vbuf[ p_polyvtx->i ];

                // set position
                p_buf->pos = p_vtx->pos;

                // set uv coords
                p_buf->u = -p_vtx->pos.x + offset_u;
                p_buf->v = -p_vtx->pos.y + offset_v;

                p_last_vtx = p_vtx;

                /** End set buffer vertex **/

                p_buf += buf_inc;

                // to next polygon vertex
                p_polyvtx = NEXT_STRIP_POLY(p_polyvtx, ix_poly+j, ufo);
            }

            // get color/spec
            const Uint32 color = fn_color(p_last_vtx);
            const Uint32 specu = fn_specu(p_last_vtx);

            // set color/spec
            p_buf_base[0].col = color;
            p_buf_base[0].spc = specu;
            p_buf_base[1].col = color;
            p_buf_base[1].spc = specu;
            p_buf_base[2].col = color;
            p_buf_base[2].spc = specu;

            p_buf_base += 3;

            // swap strip winding mode for next polygon
            invst = !invst;

            // base to next polygon vertex
            p_polyvtx_base = NEXT_STRIP_POLY(p_polyvtx_base, ix_poly, ufo);
        }

        rjEndTriDestrip(len);

        // we're now two strip indexes short
        p_polyvtx_base = CNK_NEXT_POLY(p_polyvtx_base, ufo);
        p_polyvtx_base = CNK_NEXT_POLY(p_polyvtx_base, ufo);

        // next strip chunk starts at the end of the current one
        p_st = (void*) p_polyvtx_base;
    }
}

/************************************************************************************/
/*
*   Chunk Strip UV
*/
/****** Vertex **********************************************************************/
static void
rjCnkStripUV_VND8(CNK_CTX* restrict pCtx, const CNK_STRIP_HEAD* restrict striph, const CNK_VERTEX_BUFFER* restrict vbuf, s32 uvh)
{
    RJE_CNK_VCOLFUNC cfunc;
    RJE_CNK_SPECFUNC sfunc = UseSpecular(pCtx) ? _rj_cnk_spec_mode_ : RJE_CNK_SPECFUNC_NONE;

    rjCnkStartVertexTex(pCtx);

    bool use_light = false;

    if ( pCtx->fst & NJD_FST_ENV )
    {
        if ( pCtx->fst & NJD_FST_IL )
        {
        FST_ENV_IL:
            cfunc = RJE_CNK_VCOLFUNC_D8;

            rjCnkSetPolygonCullingMode(pCtx, FALSE);

            if ( pCtx->fst & NJD_FST_FL )
            {
                rjCnkDrawStripUV_ENV_FL( striph, vbuf, cfunc, sfunc );
            }
            else // not flat shading
            {
                rjCnkDrawStripUV_ENV( striph, vbuf, cfunc, sfunc );
            }
        }
        else // use lighting
        {
            if ( !(pCtx->flag & CTXF_CTL_MULTIVND8) )
            {
                goto FST_ENV_IL;
            }

            cfunc = RJE_CNK_VCOLFUNC_LIGHTD8;

            use_light = true;
            rjCnkBeginLighting(pCtx);

            rjCnkSetPolygonCullingMode(pCtx, TRUE);

            if ( pCtx->fst & NJD_FST_FL )
            {
                rjCnkDrawStripUV_ENV_FL( striph, vbuf, cfunc, sfunc );
            }
            else // not flat shading
            {
                rjCnkDrawStripUV_ENV( striph, vbuf, cfunc, sfunc );
            }
        }
    }
    else // non environment
    {
        if ( pCtx->fst & NJD_FST_IL )
        {
        FST_IL:
            cfunc = RJE_CNK_VCOLFUNC_D8;

            rjCnkSetPolygonCullingMode(pCtx, FALSE);

            if ( pCtx->fst & NJD_FST_FL )
            {
                rjCnkDrawStripUV_FL( striph, uvh, vbuf, cfunc, sfunc );
            }
            else // not flat shading
            {
                rjCnkDrawStripUV( striph, uvh, vbuf, cfunc, sfunc );
            }
        }
        else // use lighting
        {
            if ( !(pCtx->flag & CTXF_CTL_MULTIVND8) )
            {
                goto FST_IL;
            }

            cfunc = RJE_CNK_VCOLFUNC_LIGHTD8;

            use_light = true;
            rjCnkBeginLighting(pCtx);

            rjCnkSetPolygonCullingMode(pCtx, TRUE);

            if ( pCtx->fst & NJD_FST_FL )
            {
                rjCnkDrawStripUV_FL( striph, uvh, vbuf, cfunc, sfunc );
            }
            else // not flat shading
            {
                rjCnkDrawStripUV( striph, uvh, vbuf, cfunc, sfunc );
            }
        }
    }

    /** two pass lighting **/

    if ( use_light && rjCnkBeginTwoPassLighting(pCtx) )
    {
        if ( pCtx->fst & NJD_FST_ENV )
        {
            if ( pCtx->fst & NJD_FST_FL )
            {
                rjCnkDrawStripUV_ENV_FL( striph, vbuf, cfunc, sfunc );
            }
            else // not flat shading
            {
                rjCnkDrawStripUV_ENV( striph, vbuf, cfunc, sfunc );
            }
        }
        else
        {
            if ( pCtx->fst & NJD_FST_FL )
            {
                rjCnkDrawStripUV_FL( striph, uvh, vbuf, cfunc, sfunc );
            }
            else // not flat shading
            {
                rjCnkDrawStripUV( striph, uvh, vbuf, cfunc, sfunc );
            }
        }
    }

    rjCnkEndVertex();
}

static void
rjCnkStripUV_VN(CNK_CTX* restrict pCtx, const CNK_STRIP_HEAD* restrict striph, const CNK_VERTEX_BUFFER* restrict vbuf, s32 uvh)
{
    RJE_CNK_VCOLFUNC cfunc;
    RJE_CNK_SPECFUNC sfunc = UseSpecular(pCtx) ? _rj_cnk_spec_mode_ : RJE_CNK_SPECFUNC_NONE;

    rjCnkStartVertexTex(pCtx);

    bool use_light = false;

    if ( pCtx->fst & NJD_FST_ENV )
    {
        if ( pCtx->fst & NJD_FST_IL )
        {
            cfunc = RJE_CNK_VCOLFUNC_MATERIAL;

            rjCnkSetPolygonCullingMode(pCtx, FALSE);

            if ( pCtx->fst & NJD_FST_FL )
            {
                rjCnkDrawStripUV_ENV_FL( striph, vbuf, cfunc, sfunc );
            }
            else // not flat shading
            {
                rjCnkDrawStripUV_ENV( striph, vbuf, cfunc, sfunc );
            }
        }
        else // use lighting
        {
            cfunc = RJE_CNK_VCOLFUNC_LIGHT;

            use_light = true;
            rjCnkBeginLighting(pCtx);

            rjCnkSetPolygonCullingMode(pCtx, TRUE);

            if ( pCtx->fst & NJD_FST_FL )
            {
                rjCnkDrawStripUV_ENV_FL( striph, vbuf, cfunc, sfunc );
            }
            else // not flat shading
            {
                rjCnkDrawStripUV_ENV( striph, vbuf, cfunc, sfunc );
            }
        }
    }
    else // non environment
    {
        if ( pCtx->fst & NJD_FST_IL )
        {
            cfunc = RJE_CNK_VCOLFUNC_MATERIAL;

            rjCnkSetPolygonCullingMode(pCtx, FALSE);

            if ( pCtx->fst & NJD_FST_FL )
            {
                rjCnkDrawStripUV_FL( striph, uvh, vbuf, cfunc, sfunc );
            }
            else // not flat shading
            {
                rjCnkDrawStripUV( striph, uvh, vbuf, cfunc, sfunc );
            }
        }
        else // use lighting
        {
            cfunc = RJE_CNK_VCOLFUNC_LIGHT;

            use_light = true;
            rjCnkBeginLighting(pCtx);

            rjCnkSetPolygonCullingMode(pCtx, TRUE);

            if ( pCtx->fst & NJD_FST_FL )
            {
                rjCnkDrawStripUV_FL( striph, uvh, vbuf, cfunc, sfunc );
            }
            else // not flat shading
            {
                rjCnkDrawStripUV( striph, uvh, vbuf, cfunc, sfunc );
            }
        }
    }

    /** two pass lighting **/

    if ( use_light && rjCnkBeginTwoPassLighting(pCtx) )
    {
        if ( pCtx->fst & NJD_FST_ENV )
        {
            if ( pCtx->fst & NJD_FST_FL )
            {
                rjCnkDrawStripUV_ENV_FL( striph, vbuf, cfunc, sfunc );
            }
            else // not flat shading
            {
                rjCnkDrawStripUV_ENV( striph, vbuf, cfunc, sfunc );
            }
        }
        else
        {
            if ( pCtx->fst & NJD_FST_FL )
            {
                rjCnkDrawStripUV_FL( striph, uvh, vbuf, cfunc, sfunc );
            }
            else // not flat shading
            {
                rjCnkDrawStripUV( striph, uvh, vbuf, cfunc, sfunc );
            }
        }
    }

    rjCnkEndVertex();
}

static void
rjCnkStripUV_D8(CNK_CTX* restrict pCtx, const CNK_STRIP_HEAD* restrict striph, const CNK_VERTEX_BUFFER* restrict vbuf, s32 uvh)
{
    const RJE_CNK_VCOLFUNC cfunc = RJE_CNK_VCOLFUNC_D8;
    const RJE_CNK_SPECFUNC sfunc = RJE_CNK_SPECFUNC_NONE;

    rjCnkStartVertexTex(pCtx);

    rjCnkSetPolygonCullingMode(pCtx, FALSE);

    if ( pCtx->fst & NJD_FST_ENV )
    {
        if ( pCtx->fst & NJD_FST_FL )
        {
            rjCnkDrawStripUV_POS_FL( striph, vbuf, cfunc, sfunc );
        }
        else // not flat shading
        {
            rjCnkDrawStripUV_POS( striph, vbuf, cfunc, sfunc );
        }
    }
    else // non environment
    {
        if ( pCtx->fst & NJD_FST_FL )
        {
            rjCnkDrawStripUV_FL( striph, uvh, vbuf, cfunc, sfunc );
        }
        else // not flat shading
        {
            rjCnkDrawStripUV( striph, uvh, vbuf, cfunc, sfunc );
        }
    }

    rjCnkEndVertex();
}

static void
rjCnkStripUV_D8S8(CNK_CTX* restrict pCtx, const CNK_STRIP_HEAD* restrict striph, const CNK_VERTEX_BUFFER* restrict vbuf, s32 uvh)
{
    if ( pCtx->fst & NJD_FST_IS )
    {
        rjCnkStripUV_D8(pCtx, striph, vbuf, uvh);
        return;
    }

    const RJE_CNK_VCOLFUNC cfunc = RJE_CNK_VCOLFUNC_D8;
    const RJE_CNK_SPECFUNC sfunc = RJE_CNK_SPECFUNC_S8;

    rjCnkStartVertexTex(pCtx);

    rjCnkSetPolygonCullingMode(pCtx, FALSE);

    if ( pCtx->fst & NJD_FST_ENV )
    {
        if ( pCtx->fst & NJD_FST_FL )
        {
            rjCnkDrawStripUV_POS_FL( striph, vbuf, cfunc, sfunc );
        }
        else // not flat shading
        {
            rjCnkDrawStripUV_POS( striph, vbuf, cfunc, sfunc );
        }
    }
    else // non environment
    {
        if ( pCtx->fst & NJD_FST_FL )
        {
            rjCnkDrawStripUV_FL( striph, uvh, vbuf, cfunc, sfunc );
        }
        else // not flat shading
        {
            rjCnkDrawStripUV( striph, uvh, vbuf, cfunc, sfunc );
        }
    }

    rjCnkEndVertex();
}

static void
rjCnkStripUV_CV(CNK_CTX* restrict pCtx, const CNK_STRIP_HEAD* restrict striph, const CNK_VERTEX_BUFFER* restrict vbuf, s32 uvh)
{
    const RJE_CNK_VCOLFUNC cfunc = RJE_CNK_VCOLFUNC_MATERIAL;
    const RJE_CNK_SPECFUNC sfunc = RJE_CNK_SPECFUNC_NONE;

    rjCnkStartVertexTex(pCtx);

    rjCnkSetPolygonCullingMode(pCtx, FALSE);

    if ( pCtx->fst & NJD_FST_ENV )
    {
        rjCnkDrawStripUV_POS( striph, vbuf, cfunc, sfunc );
    }
    else // non environment
    {
        rjCnkDrawStripUV( striph, uvh, vbuf, cfunc, sfunc );
    }

    rjCnkEndVertex();
}

/****** Static **********************************************************************/
static void
CnkSetupStripUV(CNK_CTX* pCtx)
{
    /** UV strip, so remove 'NOUVS' flag **/
    pCtx->flag &= ~CTXFLG_STRIP_NOUVS;
}

/****** Extern **********************************************************************/
void
rjCnkStripUV(CNK_CTX* restrict pCtx, const Sint16* restrict plist, const CNK_VERTEX_BUFFER* restrict vbuf, s32 uvh)
{
    CnkSetupStripUV(pCtx);

    const CNK_STRIP_HEAD* striph = (const CNK_STRIP_HEAD*) plist;

    if ( _rj_cnk_vertex_attr_ & RJD_CVF_NORMAL )
    {
        if ( _rj_cnk_vertex_attr_ & RJD_CVF_COLOR )
        {
            rjCnkStripUV_VND8(pCtx, striph, vbuf, uvh);
        }
        else // normals only
        {
            rjCnkStripUV_VN(pCtx, striph, vbuf, uvh);
        }
    }
    else if ( _rj_cnk_vertex_attr_ & RJD_CVF_COLOR )
    {
        if ( _rj_cnk_vertex_attr_ & RJD_CVF_SPECULAR )
        {
            rjCnkStripUV_D8S8(pCtx, striph, vbuf, uvh);
        }
        else // color only
        {
            rjCnkStripUV_D8(pCtx, striph, vbuf, uvh);
        }
    }
    else // only position
    {
        rjCnkStripUV_CV(pCtx, striph, vbuf, uvh);
    }
}
