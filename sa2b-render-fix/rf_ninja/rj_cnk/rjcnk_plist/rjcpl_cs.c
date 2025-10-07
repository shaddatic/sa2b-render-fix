/********************************/
/*  Includes                    */
/********************************/
/****** Core Toolkit ****************************************************************************/
#include <samt/core.h>              /* core                                                     */

/****** Ninja ***********************************************************************************/
#include <samt/ninja/ninja.h>       /* ninja                                                    */

/****** Render Fix ******************************************************************************/
#include <rf_core.h>                /* core                                                     */

/****** Self ************************************************************************************/
#include <rf_ninja/rj_cnk/rjcnk_plist/rjcpl_internal.h> /* parent & siblings                    */

/********************************/
/*  Source                      */
/********************************/
/****** Check Specular **************************************************************************/
static bool
UseSpecular(const RJS_CNK_STRIP* restrict pStrip)
{
    return ( !(pStrip->flag & NJD_FST_IS) && (pStrip->flag & NJD_FST_ENV || _rj_cnk_context_.flag & RJD_CXF_NONTEXSPEC) );
}

/************************************************************************************************/
/*
*   Draw Strip
*/
/****** Normal **********************************************************************************/
static void
rjCnkStripDraw(const CNK_STRIP_HEAD* restrict striph, const RJS_VERTEX_BUF* restrict vbuf, RJE_CNK_VCOLFUNC cfunc, RJE_CNK_SPECFUNC sfunc)
{
    RJF_CNK_VCOLFUNC* const fn_color = _rj_cnk_vcol_funcs_[cfunc];
    RJF_CNK_SPECFUNC* const fn_specu = _rj_cnk_spec_funcs_[sfunc];

    const int nb_strip = striph->nbstrip;
    const int ufo      = striph->ufo;

    const CNK_STRIP* p_st = (const CNK_STRIP*) striph->d;

    for (int ix_strip = 0; ix_strip < nb_strip; ++ix_strip)
    {
        const int len = rjStartTriStrip( p_st->len );

        RJS_VERTEX_PCS* p_buf = rjGetVertexBuffer();

        // get strip array
        const CNK_ST* restrict p_polyvtx = p_st->d;

        for (int i = 0; i < len; ++i)
        {
            const RJS_VERTEX_BUF* restrict p_vtx = &vbuf[ p_polyvtx->i ];

            // set position
            p_buf->pos = p_vtx->pos;

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

/****** Environment *****************************************************************************/
static void
rjCnkDrawStrip_ENV(const CNK_STRIP_HEAD* restrict striph, const RJS_VERTEX_BUF* restrict vbuf, RJE_CNK_VCOLFUNC cfunc, RJE_CNK_SPECFUNC sfunc)
{
    RJF_CNK_VCOLFUNC* const fn_color = _rj_cnk_vcol_funcs_[cfunc];
    RJF_CNK_SPECFUNC* const fn_specu = _rj_cnk_spec_funcs_[sfunc];

    const RJS_UV uv_off = rjCnkGetEnvUvScroll();

    const int nb_strip = striph->nbstrip;
    const int ufo      = striph->ufo;

    const CNK_STRIP* p_st = (const CNK_STRIP*) striph->d;

    for (int ix_strip = 0; ix_strip < nb_strip; ++ix_strip)
    {
        const int len = rjStartTriStrip( p_st->len );

        RJS_VERTEX_PTCS* p_buf = rjGetVertexBuffer();

        // get strip array
        const CNK_ST* restrict p_polyvtx = p_st->d;

        for (int i = 0; i < len; ++i)
        {
            const RJS_VERTEX_BUF* restrict p_vtx = &vbuf[ p_polyvtx->i ];

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

/****** Position Environment ********************************************************************/
static void
rjCnkDrawStrip_POS(const CNK_STRIP_HEAD* restrict striph, const RJS_VERTEX_BUF* restrict vbuf, RJE_CNK_VCOLFUNC cfunc, RJE_CNK_SPECFUNC sfunc)
{
    RJF_CNK_VCOLFUNC* const fn_color = _rj_cnk_vcol_funcs_[cfunc];
    RJF_CNK_SPECFUNC* const fn_specu = _rj_cnk_spec_funcs_[sfunc];

    const RJS_UV uv_off = rjCnkGetEnvUvScroll();

    const int nb_strip = striph->nbstrip;
    const int ufo      = striph->ufo;

    const CNK_STRIP* p_st = (const CNK_STRIP*) striph->d;

    for (int ix_strip = 0; ix_strip < nb_strip; ++ix_strip)
    {
        const int len = rjStartTriStrip( p_st->len );

        RJS_VERTEX_PTCS* p_buf = rjGetVertexBuffer();

        // get strip array
        const CNK_ST* restrict p_polyvtx = p_st->d;

        for (int i = 0; i < len; ++i)
        {
            const RJS_VERTEX_BUF* restrict p_vtx = &vbuf[ p_polyvtx->i ];

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

/************************************************************************************************/
/*
*   Draw Strip (Flat Shading)
*/
/****** Normal Flat *****************************************************************************/
static void
rjCnkDrawStrip_FL(const CNK_STRIP_HEAD* restrict striph, const RJS_VERTEX_BUF* restrict vbuf, RJE_CNK_VCOLFUNC cfunc, RJE_CNK_SPECFUNC sfunc)
{
    RJF_CNK_VCOLFUNC* const fn_color = _rj_cnk_vcol_funcs_[cfunc];
    RJF_CNK_SPECFUNC* const fn_specu = _rj_cnk_spec_funcs_[sfunc];

    const int nb_strip = striph->nbstrip;
    const int ufo      = striph->ufo;

    const CNK_STRIP* p_st = (const CNK_STRIP*) striph->d;

    for (int ix_strip = 0; ix_strip < nb_strip; ++ix_strip)
    {
        Bool invst;
        const Sint32 nb_vert = rjStartTriDestrip( p_st->len, &invst );

        // get vertex buffer
        RJS_VERTEX_PCS* p_buf_base = rjGetVertexBuffer();

        // get strip array
        const CNK_ST* restrict p_st_base = p_st->d;

        for (int ix_poly = 0, ix_vert = 0; ix_vert < nb_vert; ++ix_poly, ix_vert += 3)
        {
            RJS_VERTEX_PCS* p_buf = p_buf_base;

            const CNK_ST* restrict p_polyvtx = p_st_base;

            int buf_inc;

            DESTRIP_START(p_buf, buf_inc, invst);

            const RJS_VERTEX_BUF* restrict p_last_vtx;

            for (int j = 0; j < 3; ++j)
            {
                const RJS_VERTEX_BUF* restrict p_vtx = &vbuf[ p_polyvtx->i ];

                // set position
                p_buf->pos = p_vtx->pos;

                // set last vertex
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

        rjEndTriDestrip(nb_vert);

        // we're now two strip indexes short
        p_st_base = CNK_NEXT_POLY(p_st_base, ufo);
        p_st_base = CNK_NEXT_POLY(p_st_base, ufo);

        // next strip chunk starts at the end of the current one
        p_st = (void*) p_st_base;
    }
}

/****** Environment Flat ************************************************************************/
static void
rjCnkDrawStrip_ENV_FL(const CNK_STRIP_HEAD* restrict striph, const RJS_VERTEX_BUF* restrict vbuf, RJE_CNK_VCOLFUNC cfunc, RJE_CNK_SPECFUNC sfunc)
{
    RJF_CNK_VCOLFUNC* const fn_color = _rj_cnk_vcol_funcs_[cfunc];
    RJF_CNK_SPECFUNC* const fn_specu = _rj_cnk_spec_funcs_[sfunc];

    const RJS_UV uv_off = rjCnkGetEnvUvScroll();

    const int nb_strip = striph->nbstrip;
    const int ufo      = striph->ufo;

    const CNK_STRIP* p_st = (const CNK_STRIP*) striph->d;

    for (int ix_strip = 0; ix_strip < nb_strip; ++ix_strip)
    {
        Bool invst;
        const Sint32 len = rjStartTriDestrip( p_st->len, &invst );

        // get vertex buffer
        RJS_VERTEX_PTCS* p_buf_base = rjGetVertexBuffer();

        // get strip array
        const CNK_ST* restrict p_polyvtx_base = p_st->d;

        for (int ix_poly = 0, ix_vert = 0; ix_vert < len; ++ix_poly, ix_vert += 3)
        {
            RJS_VERTEX_PTCS* p_buf = p_buf_base;

            const CNK_ST* restrict p_polyvtx = p_polyvtx_base;

            int buf_inc;

            DESTRIP_START(p_buf, buf_inc, invst);

            const RJS_VERTEX_BUF* restrict p_last_vtx;

            for (int j = 0; j < 3; ++j)
            {
                const RJS_VERTEX_BUF* restrict p_vtx = &vbuf[ p_polyvtx->i ];

                // set position
                p_buf->pos = p_vtx->pos;

                // set uv coords
                p_buf->u = (( p_vtx->nrm.x * 0.5f) + 0.5f) + uv_off.u;
                p_buf->v = ((-p_vtx->nrm.y * 0.5f) + 0.5f) + uv_off.v;

                // set last vertex
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

/****** Positional Environment Flat *************************************************************/
static void
rjCnkDrawStrip_POS_FL(const CNK_STRIP_HEAD* restrict striph, const RJS_VERTEX_BUF* restrict vbuf, RJE_CNK_VCOLFUNC cfunc, RJE_CNK_SPECFUNC sfunc)
{
    RJF_CNK_VCOLFUNC* const fn_color = _rj_cnk_vcol_funcs_[cfunc];
    RJF_CNK_SPECFUNC* const fn_specu = _rj_cnk_spec_funcs_[sfunc];

    const RJS_UV uv_off = rjCnkGetEnvUvScroll();

    const int nb_strip = striph->nbstrip;
    const int ufo      = striph->ufo;

    const CNK_STRIP* p_st = (const CNK_STRIP*) striph->d;

    for (int ix_strip = 0; ix_strip < nb_strip; ++ix_strip)
    {
        Bool invst;
        const Sint32 len = rjStartTriDestrip( p_st->len, &invst );

        // get vertex buffer
        RJS_VERTEX_PTCS* p_buf_base = rjGetVertexBuffer();

        // get strip array
        const CNK_ST* restrict p_polyvtx_base = p_st->d;

        for (int ix_poly = 0, ix_vtx = 0; ix_vtx < len; ++ix_poly, ix_vtx += 3)
        {
            RJS_VERTEX_PTCS* p_buf = p_buf_base;

            const CNK_ST* restrict p_polyvtx = p_polyvtx_base;

            int buf_inc;

            DESTRIP_START(p_buf, buf_inc, invst);

            const RJS_VERTEX_BUF* restrict p_last_vtx;

            for (int j = 0; j < 3; ++j)
            {
                const RJS_VERTEX_BUF* restrict p_vtx = &vbuf[ p_polyvtx->i ];

                // set position
                p_buf->pos = p_vtx->pos;

                // set uv coords
                p_buf->u = -p_vtx->pos.x + uv_off.u;
                p_buf->v = -p_vtx->pos.y + uv_off.v;

                // set last vertex
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

/************************************************************************************************/
/*
*   Chunk Strip
*/
/****** Static **********************************************************************************/
static void
rjCnkStrip_VND8(const RJS_CNK_STRIP* restrict pStrip, const RJS_VERTEX_BUF* restrict vbuf)
{
    RJE_CNK_VCOLFUNC cfunc;
    RJE_CNK_SPECFUNC sfunc = UseSpecular(pStrip) ? _rj_cnk_context_.spec : RJE_CNK_SPECFUNC_NONE;

    if ( pStrip->flag & NJD_FST_ENV )
    {
        if ( pStrip->flag & NJD_FST_IL )
        {
        FST_ENV_IL:
            cfunc = RJE_CNK_VCOLFUNC_D8;

            if ( pStrip->flag & NJD_FST_FL )
            {
                rjCnkDrawStrip_ENV_FL( pStrip->striph, vbuf, cfunc, sfunc );
            }
            else // not flat shading
            {
                rjCnkDrawStrip_ENV( pStrip->striph, vbuf, cfunc, sfunc );
            }
        }
        else // use lighting
        {
            if ( !(_rj_cnk_context_.flag & RJD_CXF_VND8) )
            {
                goto FST_ENV_IL;
            }

            cfunc = RJE_CNK_VCOLFUNC_LIGHTD8;

            if ( pStrip->flag & NJD_FST_FL )
            {
                rjCnkDrawStrip_ENV_FL( pStrip->striph, vbuf, cfunc, sfunc );
            }
            else // not flat shading
            {
                rjCnkDrawStrip_ENV( pStrip->striph, vbuf, cfunc, sfunc );
            }
        }
    }
    else // non environment
    {
        if ( pStrip->flag & NJD_FST_IL )
        {
        FST_IL:
            cfunc = RJE_CNK_VCOLFUNC_D8;

            if ( pStrip->flag & NJD_FST_FL )
            {
                rjCnkDrawStrip_FL( pStrip->striph, vbuf, cfunc, sfunc );
            }
            else // not flat shading
            {
                rjCnkStripDraw( pStrip->striph, vbuf, cfunc, sfunc );
            }
        }
        else // use lighting
        {
            if ( !(_rj_cnk_context_.flag & RJD_CXF_VND8) )
            {
                goto FST_IL;
            }

            cfunc = RJE_CNK_VCOLFUNC_LIGHTD8;

            if ( pStrip->flag & NJD_FST_FL )
            {
                rjCnkDrawStrip_FL( pStrip->striph, vbuf, cfunc, sfunc );
            }
            else // not flat shading
            {
                rjCnkStripDraw( pStrip->striph, vbuf, cfunc, sfunc );
            }
        }
    }
}

static void
rjCnkStrip_VN(const RJS_CNK_STRIP* restrict pStrip, const RJS_VERTEX_BUF* restrict vbuf)
{
    RJE_CNK_VCOLFUNC cfunc;
    RJE_CNK_SPECFUNC sfunc = UseSpecular(pStrip) ? _rj_cnk_context_.spec : RJE_CNK_SPECFUNC_NONE;

    if ( pStrip->flag & NJD_FST_ENV )
    {
        if ( pStrip->flag & NJD_FST_IL )
        {
            cfunc = RJE_CNK_VCOLFUNC_MATERIAL;

            if ( pStrip->flag & NJD_FST_FL )
            {
                rjCnkDrawStrip_ENV_FL( pStrip->striph, vbuf, cfunc, sfunc );
            }
            else // not flat shading
            {
                rjCnkDrawStrip_ENV( pStrip->striph, vbuf, cfunc, sfunc );
            }
        }
        else // use lighting
        {
            cfunc = RJE_CNK_VCOLFUNC_LIGHT;

            if ( pStrip->flag & NJD_FST_FL )
            {
                rjCnkDrawStrip_ENV_FL( pStrip->striph, vbuf, cfunc, sfunc );
            }
            else // not flat shading
            {
                rjCnkDrawStrip_ENV( pStrip->striph, vbuf, cfunc, sfunc );
            }
        }
    }
    else // non environment
    {
        if ( pStrip->flag & NJD_FST_IL )
        {
            cfunc = RJE_CNK_VCOLFUNC_MATERIAL;

            if ( pStrip->flag & NJD_FST_FL )
            {
                rjCnkDrawStrip_FL( pStrip->striph, vbuf, cfunc, sfunc );
            }
            else // not flat shading
            {
                rjCnkStripDraw( pStrip->striph, vbuf, cfunc, sfunc );
            }
        }
        else // use lighting
        {
            cfunc = RJE_CNK_VCOLFUNC_LIGHT;

            if ( pStrip->flag & NJD_FST_FL )
            {
                rjCnkDrawStrip_FL( pStrip->striph, vbuf, cfunc, sfunc );
            }
            else // not flat shading
            {
                rjCnkStripDraw( pStrip->striph, vbuf, cfunc, sfunc );
            }
        }
    }
}

static void
rjCnkStrip_D8(const RJS_CNK_STRIP* restrict pStrip, const RJS_VERTEX_BUF* restrict vbuf)
{
    RJE_CNK_VCOLFUNC const cfunc = RJE_CNK_VCOLFUNC_D8;
    RJE_CNK_SPECFUNC const sfunc = RJE_CNK_SPECFUNC_NONE;

    if ( pStrip->flag & NJD_FST_ENV )
    {
        if ( pStrip->flag & NJD_FST_FL )
        {
            rjCnkDrawStrip_POS_FL(pStrip->striph, vbuf, cfunc, sfunc);
        }
        else // not flat shading
        {
            rjCnkDrawStrip_POS(pStrip->striph, vbuf, cfunc, sfunc);
        }
    }
    else // non environment
    {
        if ( pStrip->flag & NJD_FST_FL )
        {
            rjCnkDrawStrip_FL(pStrip->striph, vbuf, cfunc, sfunc);
        }
        else // not flat shading
        {
            rjCnkStripDraw(pStrip->striph, vbuf, cfunc, sfunc);
        }
    }
}

static void
rjCnkStrip_D8S8(const RJS_CNK_STRIP* restrict pStrip, const RJS_VERTEX_BUF* restrict vbuf)
{
    if ( !UseSpecular(pStrip) )
    {
        rjCnkStrip_D8(pStrip, vbuf);
        return;
    }

    RJE_CNK_VCOLFUNC const cfunc = RJE_CNK_VCOLFUNC_D8;
    RJE_CNK_SPECFUNC const sfunc = RJE_CNK_SPECFUNC_S8;

    if ( pStrip->flag & NJD_FST_ENV )
    {
        if ( pStrip->flag & NJD_FST_FL )
        {
            rjCnkDrawStrip_POS_FL( pStrip->striph, vbuf, cfunc, sfunc );
        }
        else // not flat shading
        {
            rjCnkDrawStrip_POS( pStrip->striph, vbuf, cfunc, sfunc );
        }
    }
    else // non environment
    {
        if ( pStrip->flag & NJD_FST_FL )
        {
            rjCnkDrawStrip_FL( pStrip->striph, vbuf, cfunc, sfunc );
        }
        else // not flat shading
        {
            rjCnkStripDraw( pStrip->striph, vbuf, cfunc, sfunc );
        }
    }
}

static void
rjCnkStrip_CV(const RJS_CNK_STRIP* restrict pStrip, const RJS_VERTEX_BUF* restrict vbuf)
{
    RJE_CNK_VCOLFUNC const cfunc = RJE_CNK_VCOLFUNC_MATERIAL;
    RJE_CNK_SPECFUNC const sfunc = RJE_CNK_SPECFUNC_NONE;

    if ( pStrip->flag & NJD_FST_ENV )
    {
        rjCnkDrawStrip_POS( pStrip->striph, vbuf, cfunc, sfunc );
    }
    else // non environment
    {
        rjCnkStripDraw( pStrip->striph, vbuf, cfunc, sfunc );
    }
}

/****** Extern **********************************************************************************/
void
rjCnkStrip(const RJS_CNK_STRIP* restrict strip, const RJS_VERTEX_BUF* restrict vbuf)
{
    switch ( _rj_cnk_context_.vattr )
    {
        case RJD_CVT_P: default:
        {
            rjCnkStrip_CV(strip, vbuf);
            break;
        }
        case RJD_CVT_PN:
        {
            rjCnkStrip_VN(strip, vbuf);
            break;
        }
        case RJD_CVT_PC:
        {
            rjCnkStrip_D8(strip, vbuf);
            break;
        }
        case RJD_CVT_PNC:
        {
            rjCnkStrip_VND8(strip, vbuf);
            break;
        }
        case RJD_CVT_PCS:
        {
            rjCnkStrip_D8S8(strip, vbuf);
            break;
        }
    }
}
