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
    return ( !(pStrip->flag & NJD_FST_IS) && (pStrip->flag & RJD_CSF_USEOFF || _rj_cnk_context_.flag & RJD_CXF_NONTEXSPEC) );
}

/************************************************************************************************/
/*
*   Draw Strip
*/
/****** Normal **********************************************************************************/
static void
rjCnkDrawStrip(const CNK_STRIP_HEAD* restrict striph, const RJS_VERTEX_BUF* restrict vbuf, RJE_CNK_VCOLFUNC cfunc, RJE_CNK_SPECFUNC sfunc)
{
    RJF_CNK_VCOLFUNC* const fn_color = _rj_cnk_vcol_funcs_[cfunc];
    RJF_CNK_SPECFUNC* const fn_specu = _rj_cnk_spec_funcs_[sfunc];

    const int nb_strip = striph->nbstrip;
    const int ufo      = striph->ufo;

    const CNK_STRIP* p_st = (const CNK_STRIP*) striph->d;

    for (int ix_strip = 0; ix_strip < nb_strip; ++ix_strip)
    {
        const int len = rjStartTriStrip( p_st->len );

        RJS_VERTEX_PCO* p_buf = rjGetVertexBuffer();

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
            p_buf->off = fn_specu( p_vtx );

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

        RJS_VERTEX_PTCO* p_buf = rjGetVertexBuffer();

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
            p_buf->off = fn_specu( p_vtx );

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
    if ( !(_rj_cnk_ctrl_flag_ & RJD_CNK_CTRL_ENVIRONMENT) )
    {
        rjCnkDrawStrip_POS(striph, vbuf, cfunc, sfunc);
        return;
    }

    RJF_CNK_VCOLFUNC* const fn_color = _rj_cnk_vcol_funcs_[cfunc];
    RJF_CNK_SPECFUNC* const fn_specu = _rj_cnk_spec_funcs_[sfunc];

    const RJS_UV uv_off = rjCnkGetEnvUvScroll();

    const int nb_strip = striph->nbstrip;
    const int ufo      = striph->ufo;

    const CNK_STRIP* p_st = (const CNK_STRIP*) striph->d;

    for (int ix_strip = 0; ix_strip < nb_strip; ++ix_strip)
    {
        const int len = rjStartTriStrip( p_st->len );

        RJS_VERTEX_PTCO* p_buf = rjGetVertexBuffer();

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
            p_buf->off = fn_specu( p_vtx );

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

            rjCnkDrawStrip_ENV( pStrip->striph, vbuf, cfunc, sfunc );
        }
        else // use lighting
        {
            if ( !(_rj_cnk_context_.flag & RJD_CXF_VND8) )
            {
                goto FST_ENV_IL;
            }

            cfunc = RJE_CNK_VCOLFUNC_LIGHTD8;

            rjCnkDrawStrip_ENV( pStrip->striph, vbuf, cfunc, sfunc );
        }
    }
    else // non environment
    {
        if ( pStrip->flag & NJD_FST_IL )
        {
        FST_IL:
            cfunc = RJE_CNK_VCOLFUNC_D8;

            rjCnkDrawStrip( pStrip->striph, vbuf, cfunc, sfunc );
        }
        else // use lighting
        {
            if ( !(_rj_cnk_context_.flag & RJD_CXF_VND8) )
            {
                goto FST_IL;
            }

            cfunc = RJE_CNK_VCOLFUNC_LIGHTD8;

            rjCnkDrawStrip( pStrip->striph, vbuf, cfunc, sfunc );
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

            rjCnkDrawStrip_ENV( pStrip->striph, vbuf, cfunc, sfunc );
        }
        else // use lighting
        {
            cfunc = RJE_CNK_VCOLFUNC_LIGHT;

            rjCnkDrawStrip_ENV( pStrip->striph, vbuf, cfunc, sfunc );
        }
    }
    else // non environment
    {
        if ( pStrip->flag & NJD_FST_IL )
        {
            cfunc = RJE_CNK_VCOLFUNC_MATERIAL;

            rjCnkDrawStrip( pStrip->striph, vbuf, cfunc, sfunc );
        }
        else // use lighting
        {
            cfunc = RJE_CNK_VCOLFUNC_LIGHT;

            rjCnkDrawStrip( pStrip->striph, vbuf, cfunc, sfunc );
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
        rjCnkDrawStrip_POS(pStrip->striph, vbuf, cfunc, sfunc);
    }
    else // non environment
    {
        rjCnkDrawStrip(pStrip->striph, vbuf, cfunc, sfunc);
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
        rjCnkDrawStrip_POS( pStrip->striph, vbuf, cfunc, sfunc );
    }
    else // non environment
    {
        rjCnkDrawStrip( pStrip->striph, vbuf, cfunc, sfunc );
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
        rjCnkDrawStrip( pStrip->striph, vbuf, cfunc, sfunc );
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
