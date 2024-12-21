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
/****** Push Strip ******************************************************************/
static void
PushStrip_PosColUV_ENV(const CNK_STRIP* const pStrip, const int nbStripCnk, const int ufo, const CNK_VERTEX_BUFFER* const njvtxbuf)
{
    const CNK_STRIP* p_str = pStrip;

    for (int i = 0; i < nbStripCnk; ++i)
    {
        CnkStartTriStrip( p_str->len );

        GXBUF_POSCOLUV* p_buf = GetVertexBuffer();

        const int nb_vtx = ABS(p_str->len);

        for (int vidx = 0; vidx < nb_vtx; ++vidx)
        {
            const int idx = p_str->d[vidx].i;

            const CNK_VERTEX_BUFFER* p_vtx = &njvtxbuf[idx];

            CopyPos(&p_buf->pos, &p_vtx->pos);

            p_buf->col = p_vtx->color;

            p_buf->u = -p_vtx->pos.x;
            p_buf->v = -p_vtx->pos.y;

            ++p_buf;
        }

        _gx_vtx_buf_offset_ += sizeof(*p_buf) * nb_vtx;

        CopyCopyVertex(sizeof(*p_buf));

        p_str = NEXT_STRIP(p_str, nb_vtx, ufo);
    }
}

static void
PushStrip_PosColUV_ENV_INV(const CNK_STRIP* const pStrip, const int nbStripCnk, const int ufo, const CNK_VERTEX_BUFFER* const njvtxbuf)
{
    const CNK_STRIP* p_str = pStrip;

    for (int i = 0; i < nbStripCnk; ++i)
    {
        CnkStartTriStripInverse( p_str->len );

        GXBUF_POSCOLUV* p_buf = GetVertexBuffer();

        const int nb_vtx = ABS(p_str->len);

        for (int vidx = 0; vidx < nb_vtx; ++vidx)
        {
            const int idx = p_str->d[vidx].i;

            const CNK_VERTEX_BUFFER* p_vtx = &njvtxbuf[idx];

            CopyPos(&p_buf->pos, &p_vtx->pos);

            p_buf->col = p_vtx->color;

            p_buf->u = -p_vtx->pos.x;
            p_buf->v = -p_vtx->pos.y;

            ++p_buf;
        }

        _gx_vtx_buf_offset_ += sizeof(*p_buf) * nb_vtx;

        CopyCopyVertex(sizeof(*p_buf));

        p_str = NEXT_STRIP(p_str, nb_vtx, ufo);
    }
}

static void
PushStrip_PosNorm(const CNK_STRIP* const pStrip, const int nbStripCnk, const int ufo, const CNK_VERTEX_BUFFER* const njvtxbuf)
{
    const CNK_STRIP* p_str = pStrip;

    for (int i = 0; i < nbStripCnk; ++i)
    {
        CnkStartTriStrip( p_str->len );

        GXBUF_POSNORM* p_buf = GetVertexBuffer();

        const int nb_vtx = ABS(p_str->len);

        for (int vidx = 0; vidx < nb_vtx; ++vidx)
        {
            const int idx = p_str->d[vidx].i;

            const CNK_VERTEX_BUFFER* p_vtx = &njvtxbuf[idx];

            CopyPos( &p_buf->pos , &p_vtx->pos);
            CopyNorm(&p_buf->norm, &p_vtx->norm);

            ++p_buf;
        }

        _gx_vtx_buf_offset_ += sizeof(*p_buf) * nb_vtx;

        CopyCopyVertex(sizeof(*p_buf));

        p_str = NEXT_STRIP(p_str, nb_vtx, ufo);
    }
}

static void
PushStrip_PosNorm_INV(const CNK_STRIP* const pStrip, const int nbStripCnk, const int ufo, const CNK_VERTEX_BUFFER* const njvtxbuf)
{
    const CNK_STRIP* p_str = pStrip;

    for (int i = 0; i < nbStripCnk; ++i)
    {
        CnkStartTriStripInverse( p_str->len );

        GXBUF_POSNORM* p_buf = GetVertexBuffer();

        const int nb_vtx = ABS(p_str->len);

        for (int vidx = 0; vidx < nb_vtx; ++vidx)
        {
            const int idx = p_str->d[vidx].i;

            const CNK_VERTEX_BUFFER* p_vtx = &njvtxbuf[idx];

            CopyPos(&p_buf->pos, &p_vtx->pos);

            CopyNormInverse(&p_buf->norm, &p_vtx->norm);

            ++p_buf;
        }

        _gx_vtx_buf_offset_ += sizeof(*p_buf) * nb_vtx;

        CopyCopyVertex(sizeof(*p_buf));

        p_str = NEXT_STRIP(p_str, nb_vtx, ufo);
    }
}

static void
PushStrip_PosNorm_FL(const CNK_STRIP* const pStrip, const int nbStripCnk, const int ufo, const CNK_VERTEX_BUFFER* const njvtxbuf)
{
    const CNK_STRIP* p_str = pStrip;

    for (int i = 0; i < nbStripCnk; ++i)
    {
        CnkStartTriList( p_str->len );

        GXBUF_POSNORM* p_buf = GetVertexBuffer();

        const int nb_strip = ABS(p_str->len);

        const int nb_tri = (nb_strip - 2);

        bool inv_strip = (p_str->len < 0);

        for (int tidx = 0; tidx < nb_tri; ++tidx)
        {
            const NJS_POINT3* p_vtxpos[3];

            /** vertex index and vertex increment for de-strip-ing the triangle **/
            int vidx, vinc;

            VIDX_START(vidx, vinc, inv_strip);

            for (int k = 0; k < 3; ++k)
            {
                const CNK_VERTEX_BUFFER* p_vtx = &njvtxbuf[ p_str->d[tidx+vidx].i ];

                p_vtxpos[k] = &p_vtx->pos;

                CopyPos(&p_buf->pos, &p_vtx->pos);

                vidx += vinc;

                p_buf++;
            }

            /** Calculate flat normal for triangle and apply it to the triangle **/
            NJS_VECTOR norm;
            CalcFlatNormal(p_vtxpos[0], p_vtxpos[1], p_vtxpos[2], &norm);

            p_buf[-3].norm = norm;
            p_buf[-2].norm = norm;
            p_buf[-1].norm = norm;

            /** Swap strip inverse mode for next tri **/
            inv_strip = !inv_strip;
        }

        _gx_vtx_buf_offset_ += sizeof(*p_buf) * (nb_tri * 3);

        p_str = NEXT_STRIP(p_str, nb_strip, ufo);
    }
}

static void
PushStrip_PosNorm_FL_INV(const CNK_STRIP* const pStrip, const int nbStripCnk, const int ufo, const CNK_VERTEX_BUFFER* const njvtxbuf)
{
    const CNK_STRIP* p_str = pStrip;

    for (int i = 0; i < nbStripCnk; ++i)
    {
        CnkStartTriListInverse( p_str->len );

        GXBUF_POSNORM* p_buf = GetVertexBuffer();

        const int nb_strip = ABS(p_str->len);

        const int nb_tri = (nb_strip - 2);

        bool inv_strip = !(p_str->len < 0);

        for (int tidx = 0; tidx < nb_tri; ++tidx)
        {
            const NJS_POINT3* p_vtxpos[3];

            /** vertex index and vertex increment for de-strip-ing the triangle **/
            int vidx, vinc;

            VIDX_START(vidx, vinc, inv_strip);

            for (int k = 0; k < 3; ++k)
            {
                const CNK_VERTEX_BUFFER* p_vtx = &njvtxbuf[ p_str->d[tidx+vidx].i ];

                p_vtxpos[k] = &p_vtx->pos;

                CopyPos(&p_buf->pos, &p_vtx->pos);

                vidx += vinc;

                p_buf++;
            }

            /** Calculate flat normal for triangle and apply it to the triangle **/
            NJS_VECTOR norm;
            CalcFlatNormal(p_vtxpos[0], p_vtxpos[1], p_vtxpos[2], &norm);

            p_buf[-3].norm = norm;
            p_buf[-2].norm = norm;
            p_buf[-1].norm = norm;

            /** Swap strip inverse mode for next tri **/
            inv_strip = !inv_strip;
        }

        _gx_vtx_buf_offset_ += sizeof(*p_buf) * (nb_tri * 3);

        p_str = NEXT_STRIP(p_str, nb_strip, ufo);
    }
}

static void
PushStrip_PosCol(const CNK_STRIP* const pStrip, const int nbStripCnk, const int ufo, const CNK_VERTEX_BUFFER* const njvtxbuf)
{
    const CNK_STRIP* p_str = pStrip;

    for (int i = 0; i < nbStripCnk; ++i)
    {
        CnkStartTriStrip( p_str->len );

        GXBUF_POSCOL* p_buf = GetVertexBuffer();

        const int nb_strip = ABS(p_str->len);

        for (int j = 0; j < nb_strip; ++j)
        {
            const int idx = p_str->d[j].i;

            const CNK_VERTEX_BUFFER* p_vtx = &njvtxbuf[idx];

            CopyPos(&p_buf->pos, &p_vtx->pos  );
            CopyCol(&p_buf->col, &p_vtx->color);

            ++p_buf;
        }

        _gx_vtx_buf_offset_ += sizeof(*p_buf) * nb_strip;

        CopyCopyVertex(sizeof(*p_buf));

        p_str = NEXT_STRIP(p_str, nb_strip, ufo);
    }
}

static void
PushStrip_PosCol_INV(const CNK_STRIP* const pStrip, const int nbStripCnk, const int ufo, const CNK_VERTEX_BUFFER* const njvtxbuf)
{
    const CNK_STRIP* p_str = pStrip;

    for (int i = 0; i < nbStripCnk; ++i)
    {
        CnkStartTriStripInverse( p_str->len );

        GXBUF_POSCOL* p_buf = GetVertexBuffer();

        const int nb_strip = ABS(p_str->len);

        for (int j = 0; j < nb_strip; ++j)
        {
            const int idx = p_str->d[j].i;

            const CNK_VERTEX_BUFFER* p_vtx = &njvtxbuf[idx];

            CopyPos(&p_buf->pos, &p_vtx->pos  );
            CopyCol(&p_buf->col, &p_vtx->color);

            ++p_buf;
        }

        _gx_vtx_buf_offset_ += sizeof(*p_buf) * nb_strip;

        CopyCopyVertex(sizeof(*p_buf));

        p_str = NEXT_STRIP(p_str, nb_strip, ufo);
    }
}

/****** Static **********************************************************************/
static void
CnkSetupStrip(CNK_CTX* pCtx)
{
    pCtx->flag |= CTXFLG_STRIP_NOUVS;
}

/****** Extern **********************************************************************/
static void
rjCnkStrip_DB(CNK_CTX* const pCtx, const Sint16* plist, const CNK_VERTEX_BUFFER* njvtxbuf)
{
    CnkSetupStrip(pCtx);

    const int count = plist[2];

    const int nb_stcnk = count & ~NJD_UFO_MASK;
    const int ufo      = count >> NJD_UFO_SHIFT;

    CNK_STRIP* const p_str = (void*)&plist[3];

    if (pCtx->fst & NJD_FST_ENV)
    {
        if (_nj_cnk_vtx_attrs_ & CNKVTX_NO_NORMALS)
        {
            CnkSetupTexStrip(pCtx);

            VertexDeclInfo = VertexDecl_PosColUV;

            if (pCtx->flag & CTXFLG_CULL_NORMAL)
                PushStrip_PosColUV_ENV(p_str, nb_stcnk, ufo, njvtxbuf);

            if (pCtx->flag & CTXFLG_CULL_INVERSE)
                PushStrip_PosColUV_ENV_INV(p_str, nb_stcnk, ufo, njvtxbuf);
        }
        else
        {
            CnkSetupEnvStrip(pCtx);

            VertexDeclInfo = VertexDecl_PosNorm;

            if (pCtx->fst & NJD_FST_FL)
            {
                if (pCtx->flag & CTXFLG_CULL_NORMAL)
                    PushStrip_PosNorm_FL(p_str, nb_stcnk, ufo, njvtxbuf);

                if (pCtx->flag & CTXFLG_CULL_INVERSE)
                    PushStrip_PosNorm_FL_INV(p_str, nb_stcnk, ufo, njvtxbuf);
            }
            else
            {
                if (pCtx->flag & CTXFLG_CULL_NORMAL)
                    PushStrip_PosNorm(p_str, nb_stcnk, ufo, njvtxbuf);

                if (pCtx->flag & CTXFLG_CULL_INVERSE)
                    PushStrip_PosNorm_INV(p_str, nb_stcnk, ufo, njvtxbuf);
            }
        }

    }
    else // No tex
    {
        CnkSetupNoTexStrip(pCtx);

        if (_nj_cnk_vtx_attrs_ & CNKVTX_HAS_VCOLORS)
        {
            VertexDeclInfo = VertexDecl_PosCol;

            if (pCtx->flag & CTXFLG_CULL_NORMAL)
                PushStrip_PosCol(p_str, nb_stcnk, ufo, njvtxbuf);

            if (pCtx->flag & CTXFLG_CULL_INVERSE)
                PushStrip_PosCol_INV(p_str, nb_stcnk, ufo, njvtxbuf);
        }
        else
        {
            VertexDeclInfo = VertexDecl_PosNorm;

            if (pCtx->fst & NJD_FST_FL)
            {
                if (pCtx->flag & CTXFLG_CULL_NORMAL)
                    PushStrip_PosNorm_FL(p_str, nb_stcnk, ufo, njvtxbuf);

                if (pCtx->flag & CTXFLG_CULL_INVERSE)
                    PushStrip_PosNorm_FL_INV(p_str, nb_stcnk, ufo, njvtxbuf);
            }
            else
            {
                if (pCtx->flag & CTXFLG_CULL_NORMAL)
                    PushStrip_PosNorm(p_str, nb_stcnk, ufo, njvtxbuf);

                if (pCtx->flag & CTXFLG_CULL_INVERSE)
                    PushStrip_PosNorm_INV(p_str, nb_stcnk, ufo, njvtxbuf);
            }
        }
    }

    GX_End(); // Draw buffered vertex list
}

void
rjCnkStrip(CNK_CTX* const pCtx, const Sint16* plist, const CNK_VERTEX_BUFFER* njvtxbuf)
{
    if ( pCtx->fst & NJD_FST_DB && !(pCtx->flag & (CTXFLG_FUNC_EASY|CTXFLG_FUNC_DIRECT) ))
    {
        rjCnkStrip_DB(pCtx, plist, njvtxbuf);
        return;
    }

    CnkSetupStrip(pCtx);

    const int count = plist[2];

    const int nb_stcnk = count & ~NJD_UFO_MASK;
    const int ufo      = count >> NJD_UFO_SHIFT;

    CNK_STRIP* const p_str = (void*)&plist[3];

    if (pCtx->fst & NJD_FST_ENV)
    {
        if (_nj_cnk_vtx_attrs_ & CNKVTX_NO_NORMALS)
        {
            CnkSetupTexStrip(pCtx);

            VertexDeclInfo = VertexDecl_PosColUV;

            PushStrip_PosColUV_ENV(p_str, nb_stcnk, ufo, njvtxbuf);
        }
        else
        {
            CnkSetupEnvStrip(pCtx);

            VertexDeclInfo = VertexDecl_PosNorm;

            if (pCtx->fst & NJD_FST_FL)
            {
                PushStrip_PosNorm_FL(p_str, nb_stcnk, ufo, njvtxbuf);
            }
            else
            {
                PushStrip_PosNorm(p_str, nb_stcnk, ufo, njvtxbuf);
            }
        }

    }
    else // No tex
    {
        CnkSetupNoTexStrip(pCtx);

        if (_nj_cnk_vtx_attrs_ & CNKVTX_HAS_VCOLORS)
        {
            VertexDeclInfo = VertexDecl_PosCol;

            PushStrip_PosCol(p_str, nb_stcnk, ufo, njvtxbuf);
        }
        else
        {
            VertexDeclInfo = VertexDecl_PosNorm;

            if (pCtx->fst & NJD_FST_FL)
            {
                PushStrip_PosNorm_FL(p_str, nb_stcnk, ufo, njvtxbuf);
            }
            else
            {
                PushStrip_PosNorm(p_str, nb_stcnk, ufo, njvtxbuf);
            }
        }
    }

    GX_End(); // Draw buffered vertex list
}

void
rjCnkStripVN(CNK_CTX* const pCtx, const Sint16* plist, const CNK_VERTEX_BUFFER* njvtxbuf)
{

}

void
rjCnkStripUVVN(CNK_CTX* const pCtx, const Sint16* plist, const CNK_VERTEX_BUFFER* njvtxbuf, bool uvh)
{

}

void
rjCnkStripD8(CNK_CTX* const pCtx, const Sint16* plist, const CNK_VERTEX_BUFFER* njvtxbuf)
{
    
}

void
rjCnkStripUVD8(CNK_CTX* const pCtx, const Sint16* plist, const CNK_VERTEX_BUFFER* njvtxbuf, bool uvh)
{

}
