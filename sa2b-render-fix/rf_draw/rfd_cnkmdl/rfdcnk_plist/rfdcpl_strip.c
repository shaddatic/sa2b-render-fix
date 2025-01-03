/************************/
/*  Includes            */
/************************/
/****** Core Toolkit ****************************************************************/
#include <sa2b/core.h>      /* core                                                 */
#include <sa2b/memory.h>    /* MemCopy                                              */

/****** Ninja ***********************************************************************/
#include <sa2b/ninja/ninja.h> /* ninja                                              */

/****** GX **************************************************************************/
#include <sa2b/gx/gx.h>     /* GX                                                   */

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
/************************************************************************************/
/*
*   Push to Draw Buffer
*/

/****** Position+Normal *************************************************************/
static void
PushStrip_PosNorm(const CNK_STRIP* restrict pStrip, const int nbStrip, const int ufo, const CNK_VERTEX_BUFFER* restrict njvtxbuf)
{
    const CNK_STRIP* p_strip = pStrip;

    for (int ix_strip = 0; ix_strip < nbStrip; ++ix_strip)
    {
        CnkStartTriStrip( p_strip->len );

        GXBUF_POSNORM* p_buf = GetVertexBuffer();

        // get strip length
        const int len = ABS(p_strip->len);

        // get strip array
        const CNK_ST* restrict p_st = p_strip->d;

        for (int i = 0; i < len; ++i)
        {
            const CNK_VERTEX_BUFFER* restrict p_vtx = &njvtxbuf[ p_st->i ];

            /** Set draw buffer **/

            // set position
            p_buf->pos = p_vtx->pos;

            // Set normal
            p_buf->nrm = p_vtx->nrm;

            /** End set buffer **/

            ++p_buf;

            // user offset only applies per polygon, so we skip the first two
            p_st = (i >= 2) ? CNK_NEXT_POLY(p_st, ufo) : CNK_NEXT_POLY(p_st, 0);
        }

        _gx_vtx_buf_offset_ += sizeof(*p_buf) * len;

        CopyCopyVertex(sizeof(*p_buf));

        p_strip = CNK_NEXT_STRIP(p_strip, len, ufo);
    }
}

static void
PushStrip_PosNorm_INV(const CNK_STRIP* restrict pStrip, const int nbStrip, const int ufo, const CNK_VERTEX_BUFFER* restrict njvtxbuf)
{
    const CNK_STRIP* p_strip = pStrip;

    for (int ix_strip = 0; ix_strip < nbStrip; ++ix_strip)
    {
        CnkStartTriStripInverse( p_strip->len );

        GXBUF_POSNORM* p_buf = GetVertexBuffer();

        // get strip length
        const int len = ABS(p_strip->len);

        // get strip array
        const CNK_ST* restrict p_st = p_strip->d;

        for (int i = 0; i < len; ++i)
        {
            const CNK_VERTEX_BUFFER* restrict p_vtx = &njvtxbuf[ p_st->i ];

            /** Set draw buffer **/

            // set position
            p_buf->pos = p_vtx->pos;

            // Set inverted normal
            p_buf->nrm.x = -p_vtx->nrm.x;
            p_buf->nrm.y = -p_vtx->nrm.y;
            p_buf->nrm.z = -p_vtx->nrm.z;

            /** End set buffer **/

            ++p_buf;

            // user offset only applies per polygon, so we skip the first two
            p_st = (i >= 2) ? CNK_NEXT_POLY(p_st, ufo) : CNK_NEXT_POLY(p_st, 0);
        }

        _gx_vtx_buf_offset_ += sizeof(*p_buf) * len;

        CopyCopyVertex(sizeof(*p_buf));

        p_strip = CNK_NEXT_STRIP(p_strip, len, ufo);
    }
}

/****** Position+Color **************************************************************/
static void
PushStrip_PosCol(const CNK_STRIP* restrict pStrip, const int nbStrip, const int ufo, const CNK_VERTEX_BUFFER* restrict njvtxbuf)
{
    const CNK_STRIP* p_strip = pStrip;

    for (int ix_strip = 0; ix_strip < nbStrip; ++ix_strip)
    {
        CnkStartTriStrip( p_strip->len );

        GXBUF_POSCOL* p_buf = GetVertexBuffer();

        // get strip length
        const int len = ABS(p_strip->len);

        // get strip array
        const CNK_ST* restrict p_st = p_strip->d;

        for (int i = 0; i < len; ++i)
        {
            const CNK_VERTEX_BUFFER* restrict p_vtx = &njvtxbuf[ p_st->i ];

            /** Set draw buffer **/

            // set position
            p_buf->pos = p_vtx->pos;

            // set color
            p_buf->col = p_vtx->col;

            /** End set buffer **/

            ++p_buf;

            // user offset only applies per polygon, so we skip the first two
            p_st = (i >= 2) ? CNK_NEXT_POLY(p_st, ufo) : CNK_NEXT_POLY(p_st, 0);
        }

        _gx_vtx_buf_offset_ += sizeof(*p_buf) * len;

        CopyCopyVertex(sizeof(*p_buf));

        p_strip = CNK_NEXT_STRIP(p_strip, len, ufo);
    }
}

static void
PushStrip_PosCol_INV(const CNK_STRIP* restrict pStrip, const int nbStrip, const int ufo, const CNK_VERTEX_BUFFER* restrict njvtxbuf)
{
    const CNK_STRIP* p_strip = pStrip;

    for (int ix_str = 0; ix_str < nbStrip; ++ix_str)
    {
        CnkStartTriStripInverse( p_strip->len );

        GXBUF_POSCOL* p_buf = GetVertexBuffer();

        // get strip length
        const int len = ABS(p_strip->len);

        // get strip array
        const CNK_ST* restrict p_st = p_strip->d;

        for (int i = 0; i < len; ++i)
        {
            const CNK_VERTEX_BUFFER* restrict p_vtx = &njvtxbuf[ p_st->i ];

            /** Set draw buffer **/

            // set position
            p_buf->pos = p_vtx->pos;

            // set color
            p_buf->col = p_vtx->col;

            /** End set buffer **/

            ++p_buf;

            // user offset only applies per polygon, so we skip the first two
            p_st = (i >= 2) ? CNK_NEXT_POLY(p_st, ufo) : CNK_NEXT_POLY(p_st, 0);
        }

        _gx_vtx_buf_offset_ += sizeof(*p_buf) * len;

        CopyCopyVertex(sizeof(*p_buf));

        p_strip = CNK_NEXT_STRIP(p_strip, len, ufo);
    }
}

/****** Flat Shading: Position+Normal ***********************************************/
static void
PushStrip_PosNorm_FL(const CNK_STRIP* restrict pStrip, const int nbStrip, const int ufo, const CNK_VERTEX_BUFFER* restrict njvtxbuf)
{
    const CNK_STRIP* p_strip = pStrip;

    for (int ix_strip = 0; ix_strip < nbStrip; ++ix_strip)
    {
        CnkStartTriList( p_strip->len );

        GXBUF_POSNORM* p_buf_base = GetVertexBuffer();

        // get inverted strip state
        bool invst = !(p_strip->len < 0);

        // get strip length
        const int len = ABS(p_strip->len);

        // get polygon count
        const int nb_poly = (len - 2);

        // get strip array
        const CNK_ST* restrict p_st = p_strip->d;

        for (int i = 0; i < nb_poly; ++i)
        {
            GXBUF_POSNORM* p_buf = p_buf_base;

            NJS_VECTOR norm = {0}; // normal accumulator

            /** buffer increment value for destripping algorithm **/
            int buf_inc;

            DESTRIP_START(p_buf, buf_inc, invst);

            const CNK_ST* restrict p_st_2 = p_st;

            for (int j = 0; j < 3; ++j)
            {
                const CNK_VERTEX_BUFFER* restrict p_vtx = &njvtxbuf[ p_st_2->i ];

                /** Set draw buffer **/

                // set position
                p_buf->pos = p_vtx->pos;

                // add normal
                norm.x += p_vtx->nrm.x;
                norm.y += p_vtx->nrm.y;
                norm.z += p_vtx->nrm.z;

                /** End set buffer **/

                p_buf += buf_inc;

                // user offset only applies per polygon, so we skip the first two
                p_st_2 = (i+j >= 2) ? CNK_NEXT_POLY(p_st_2, ufo) : CNK_NEXT_POLY(p_st_2, 0);
            }

            /** Adjust accumulated normal (div 3) **/
            norm.x *= (1.f/3.f);
            norm.y *= (1.f/3.f);
            norm.z *= (1.f/3.f);

            /** Set flat normal for triangle **/
            (p_buf_base++)->nrm = norm;
            (p_buf_base++)->nrm = norm;
            (p_buf_base++)->nrm = norm;

            /** Swap strip inverse mode for next tri **/
            invst = !invst;

            // user offset only applies per polygon, so we skip the first two
            p_st = (i >= 2) ? CNK_NEXT_POLY(p_st, ufo) : CNK_NEXT_POLY(p_st, 0);
        }

        _gx_vtx_buf_offset_ += sizeof(*p_buf_base) * (nb_poly * 3);

        p_strip = CNK_NEXT_STRIP(p_strip, len, ufo);
    }
}

static void
PushStrip_PosNorm_FL_INV(const CNK_STRIP* restrict pStrip, const int nbStrip, const int ufo, const CNK_VERTEX_BUFFER* restrict njvtxbuf)
{
    const CNK_STRIP* p_strip = pStrip;

    for (int ix_strip = 0; ix_strip < nbStrip; ++ix_strip)
    {
        CnkStartTriListInverse( p_strip->len );

        GXBUF_POSNORM* p_buf_base = GetVertexBuffer();

        // get inverted strip state
        bool invst = !(p_strip->len < 0);

        // get strip length
        const int len = ABS(p_strip->len);

        // get polygon count
        const int nb_poly = (len - 2);

        // get strip array
        const CNK_ST* restrict p_st = p_strip->d;

        for (int i = 0; i < nb_poly; ++i)
        {
            GXBUF_POSNORM* p_buf = p_buf_base;

            NJS_VECTOR norm = {0}; // normal accumulator

            /** buffer increment value for destripping algorithm **/
            int buf_inc;

            DESTRIP_START(p_buf, buf_inc, invst);

            const CNK_ST* restrict p_st_2 = p_st;

            for (int j = 0; j < 3; ++j)
            {
                const CNK_VERTEX_BUFFER* restrict p_vtx = &njvtxbuf[ p_st_2->i ];

                /** Set draw buffer **/

                // set position
                p_buf->pos = p_vtx->pos;

                // sub normal
                norm.x -= p_vtx->nrm.x;
                norm.y -= p_vtx->nrm.y;
                norm.z -= p_vtx->nrm.z;

                /** End set buffer **/

                p_buf += buf_inc;

                // user offset only applies per polygon, so we skip the first two
                p_st_2 = (i+j >= 2) ? CNK_NEXT_POLY(p_st_2, ufo) : CNK_NEXT_POLY(p_st_2, 0);
            }

            /** Adjust accumulated normal (div 3) **/
            norm.x *= (1.f/3.f);
            norm.y *= (1.f/3.f);
            norm.z *= (1.f/3.f);

            /** Set flat normal for triangle **/
            (p_buf_base++)->nrm = norm;
            (p_buf_base++)->nrm = norm;
            (p_buf_base++)->nrm = norm;

            /** Swap strip inverse mode for next tri **/
            invst = !invst;

            // user offset only applies per polygon, so we skip the first two
            p_st = (i >= 2) ? CNK_NEXT_POLY(p_st, ufo) : CNK_NEXT_POLY(p_st, 0);
        }

        _gx_vtx_buf_offset_ += sizeof(*p_buf_base) * (nb_poly * 3);

        p_strip = CNK_NEXT_STRIP(p_strip, len, ufo);
    }
}

/****** No-Normal Envmap: Position+Col+UV *******************************************/
static void
PushStrip_PosColUV_ENV(const CNK_STRIP* restrict pStrip, const int nbStrip, const int ufo, const CNK_VERTEX_BUFFER* restrict njvtxbuf)
{
    const f32 scroll_u = _rj_cnk_env_scroll_u_;
    const f32 scroll_v = _rj_cnk_env_scroll_v_;

    const CNK_STRIP* p_strip = pStrip;

    for (int i = 0; i < nbStrip; ++i)
    {
        CnkStartTriStrip( p_strip->len );

        GXBUF_POSCOLUV* p_buf = GetVertexBuffer();

        const int len = ABS(p_strip->len);

        const CNK_ST* restrict p_st = p_strip->d;

        for (int i = 0; i < len; ++i)
        {
            const CNK_VERTEX_BUFFER* restrict p_vtx = &njvtxbuf[ p_st->i ];

            /** Set draw buffer **/

            // set position
            p_buf->pos = p_vtx->pos;

            // set color
            p_buf->col = p_vtx->col;

            // set uv coords
            p_buf->u = -p_vtx->pos.x + scroll_u;
            p_buf->v = -p_vtx->pos.y + scroll_v;

            /** End set buffer **/

            ++p_buf;

            // user offset only applies per polygon, so we skip the first two
            p_st = (i >= 2) ? CNK_NEXT_POLY(p_st, ufo) : CNK_NEXT_POLY(p_st, 0);
        }

        _gx_vtx_buf_offset_ += sizeof(*p_buf) * len;

        CopyCopyVertex(sizeof(*p_buf));

        p_strip = CNK_NEXT_STRIP(p_strip, len, ufo);
    }
}

static void
PushStrip_PosColUV_ENV_INV(const CNK_STRIP* restrict pStrip, const int nbStrip, const int ufo, const CNK_VERTEX_BUFFER* restrict njvtxbuf)
{
    const f32 scroll_u = _rj_cnk_env_scroll_u_;
    const f32 scroll_v = _rj_cnk_env_scroll_v_;

    const CNK_STRIP* p_strip = pStrip;

    for (int ix_strip = 0; ix_strip < nbStrip; ++ix_strip)
    {
        CnkStartTriStripInverse( p_strip->len );

        GXBUF_POSCOLUV* p_buf = GetVertexBuffer();

        const int len = ABS(p_strip->len);

        const CNK_ST* restrict p_st = (CNK_ST*)&p_strip->d;

        for (int i = 0; i < len; ++i)
        {
            const CNK_VERTEX_BUFFER* restrict p_vtx = &njvtxbuf[ p_st->i ];

            /** Set draw buffer **/

            // set position
            p_buf->pos = p_vtx->pos;

            // set color
            p_buf->col = p_vtx->col;

            // set uv coords
            p_buf->u = -p_vtx->pos.x + scroll_u;
            p_buf->v = -p_vtx->pos.y + scroll_v;

            /** End set buffer **/

            ++p_buf;

            // user offset only applies per polygon, so we skip the first two
            p_st = (i >= 2) ? CNK_NEXT_POLY(p_st, ufo) : CNK_NEXT_POLY(p_st, 0);
        }

        _gx_vtx_buf_offset_ += sizeof(*p_buf) * len;

        CopyCopyVertex(sizeof(*p_buf));

        p_strip = CNK_NEXT_STRIP(p_strip, len, ufo);
    }
}

/************************************************************************************/
/*
*   Chunk Strip
*/

/****** Static **********************************************************************/
static void
CnkSetupStrip(CNK_CTX* pCtx)
{
    /** Regular strip with no UV info, so set 'NOUVS' flag **/
    pCtx->flag |= CTXFLG_STRIP_NOUVS;
}

/****** Extern **********************************************************************/
static void
rjCnkStrip_DB(CNK_CTX* restrict pCtx, const Sint16* restrict plist, const CNK_VERTEX_BUFFER* restrict njvtxbuf)
{
    const CNK_STRIP_HEAD* restrict head = (CNK_STRIP_HEAD*)plist;

    const int nb_strip = head->nbstrip;
    const int ufo      = head->ufo;

    const CNK_STRIP* restrict p_strip = (const CNK_STRIP*)&head->d;

    if ( pCtx->fst & NJD_FST_ENV )
    {
        if ( _nj_cnk_vtx_attrs_ & CNKVTX_FLG_NONORM )
        {
            CnkSetupTexStrip(pCtx);

            VertexDeclInfo = VertexDecl_PosColUV;

            if (pCtx->flag & CTXFLG_CULL_NORMAL)
                PushStrip_PosColUV_ENV(p_strip, nb_strip, ufo, njvtxbuf);

            if (pCtx->flag & CTXFLG_CULL_INVERSE)
                PushStrip_PosColUV_ENV_INV(p_strip, nb_strip, ufo, njvtxbuf);
        }
        else
        {
            CnkSetupEnvStrip(pCtx);

            VertexDeclInfo = VertexDecl_PosNorm;

            if (pCtx->fst & NJD_FST_FL)
            {
                if (pCtx->flag & CTXFLG_CULL_NORMAL)
                    PushStrip_PosNorm_FL(p_strip, nb_strip, ufo, njvtxbuf);

                if (pCtx->flag & CTXFLG_CULL_INVERSE)
                    PushStrip_PosNorm_FL_INV(p_strip, nb_strip, ufo, njvtxbuf);
            }
            else
            {
                if (pCtx->flag & CTXFLG_CULL_NORMAL)
                    PushStrip_PosNorm(p_strip, nb_strip, ufo, njvtxbuf);

                if (pCtx->flag & CTXFLG_CULL_INVERSE)
                    PushStrip_PosNorm_INV(p_strip, nb_strip, ufo, njvtxbuf);
            }
        }

    }
    else // No tex
    {
        CnkSetupNoTexStrip(pCtx);

        if ( _nj_cnk_vtx_attrs_ & CNKVTX_FLG_VCOLOR )
        {
            VertexDeclInfo = VertexDecl_PosCol;

            if (pCtx->flag & CTXFLG_CULL_NORMAL)
                PushStrip_PosCol(p_strip, nb_strip, ufo, njvtxbuf);

            if (pCtx->flag & CTXFLG_CULL_INVERSE)
                PushStrip_PosCol_INV(p_strip, nb_strip, ufo, njvtxbuf);
        }
        else
        {
            /** We don't need to handle the case where the vertex attributes don't
                include normals, the shader just ignores them anyway. Although,
                this is a potential area of improvement in the future. **/

            VertexDeclInfo = VertexDecl_PosNorm;

            if (pCtx->fst & NJD_FST_FL)
            {
                if (pCtx->flag & CTXFLG_CULL_NORMAL)
                    PushStrip_PosNorm_FL(p_strip, nb_strip, ufo, njvtxbuf);

                if (pCtx->flag & CTXFLG_CULL_INVERSE)
                    PushStrip_PosNorm_FL_INV(p_strip, nb_strip, ufo, njvtxbuf);
            }
            else
            {
                if (pCtx->flag & CTXFLG_CULL_NORMAL)
                    PushStrip_PosNorm(p_strip, nb_strip, ufo, njvtxbuf);

                if (pCtx->flag & CTXFLG_CULL_INVERSE)
                    PushStrip_PosNorm_INV(p_strip, nb_strip, ufo, njvtxbuf);
            }
        }
    }

    /** End CnkStrip and draw buffered vertex list **/

    GX_End();
}

void
rjCnkStrip(CNK_CTX* restrict pCtx, const Sint16* restrict plist, const CNK_VERTEX_BUFFER* restrict njvtxbuf)
{
    CnkSetupStrip(pCtx);

    /** If this strip is double sided and we're not using Easy or Direct draw
        modes, then additional logic is required for correctly inverting normals.
        This logic is done in a seperate '_DB' function, so we can omit the extra
        logic when it isn't needed. Otherwise, the functions are the same. **/
    if ( pCtx->fst & NJD_FST_DB && !(pCtx->flag & (CTXFLG_FUNC_EASY|CTXFLG_FUNC_DIRECT) ))
    {
        rjCnkStrip_DB(pCtx, plist, njvtxbuf);
        return;
    }

    const CNK_STRIP_HEAD* head = (CNK_STRIP_HEAD*)plist;

    const int nb_strip = head->nbstrip;
    const int ufo      = head->ufo;

    const CNK_STRIP* const p_strip = (const CNK_STRIP*)&head->d;

    if ( pCtx->fst & NJD_FST_ENV )
    {
        /** Draw environment mapped strip **/

        if ( _nj_cnk_vtx_attrs_ & CNKVTX_FLG_NONORM )
        {
            CnkSetupTexStrip(pCtx);

            VertexDeclInfo = VertexDecl_PosColUV;

            PushStrip_PosColUV_ENV(p_strip, nb_strip, ufo, njvtxbuf);
        }
        else
        {
            CnkSetupEnvStrip(pCtx);

            VertexDeclInfo = VertexDecl_PosNorm;

            if ( pCtx->fst & NJD_FST_FL )
            {
                PushStrip_PosNorm_FL(p_strip, nb_strip, ufo, njvtxbuf);
            }
            else
            {
                PushStrip_PosNorm(p_strip, nb_strip, ufo, njvtxbuf);
            }
        }

    }
    else // not env mapped
    {
        /** Draw non-tex strip **/

        CnkSetupNoTexStrip(pCtx);

        if ( _nj_cnk_vtx_attrs_ & CNKVTX_FLG_VCOLOR )
        {
            VertexDeclInfo = VertexDecl_PosCol;

            PushStrip_PosCol(p_strip, nb_strip, ufo, njvtxbuf);
        }
        else
        {
            /** We don't need to handle the case where the vertex attributes don't
                include normals, the shader just ignores them anyway. Although,
                this is a potential area of improvement in the future. **/

            VertexDeclInfo = VertexDecl_PosNorm;

            if (pCtx->fst & NJD_FST_FL)
            {
                PushStrip_PosNorm_FL(p_strip, nb_strip, ufo, njvtxbuf);
            }
            else
            {
                PushStrip_PosNorm(p_strip, nb_strip, ufo, njvtxbuf);
            }
        }
    }

    /** End CnkStrip and draw buffered vertex list **/

    GX_End();
}

/************************************************************************************/
/*
*   Chunk Strip VN
*/

void
rjCnkStripVN(CNK_CTX* restrict pCtx, const Sint16* restrict plist, const CNK_VERTEX_BUFFER* restrict njvtxbuf)
{

}

/************************************************************************************/
/*
*   Chunk Strip UV VN
*/

void
rjCnkStripUVVN(CNK_CTX* restrict pCtx, const Sint16* restrict plist, const CNK_VERTEX_BUFFER* restrict njvtxbuf, bool uvh)
{

}

/************************************************************************************/
/*
*   Chunk Strip D8
*/

void
rjCnkStripD8(CNK_CTX* restrict pCtx, const Sint16* restrict plist, const CNK_VERTEX_BUFFER* restrict njvtxbuf)
{
    
}

/************************************************************************************/
/*
*   Chunk Strip UV D8
*/

void
rjCnkStripUVD8(CNK_CTX* restrict pCtx, const Sint16* restrict plist, const CNK_VERTEX_BUFFER* restrict njvtxbuf, bool uvh)
{

}
