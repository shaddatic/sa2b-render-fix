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
            const CNK_VERTEX_BUFFER* p_vtx = &njvtxbuf[ p_str->d[vidx].i ];

            /** Set draw buffer **/

            // set position
            p_buf->pos = p_vtx->pos;

            // Set normal
            p_buf->norm = p_vtx->norm;

            /** End set buffer **/

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
            const CNK_VERTEX_BUFFER* p_vtx = &njvtxbuf[ p_str->d[vidx].i ];

            /** Set draw buffer **/

            // set position
            p_buf->pos = p_vtx->pos;

            // Set inverted normal
            p_buf->norm.x = -p_vtx->norm.x;
            p_buf->norm.y = -p_vtx->norm.y;
            p_buf->norm.z = -p_vtx->norm.z;

            /** End set buffer **/

            ++p_buf;
        }

        _gx_vtx_buf_offset_ += sizeof(*p_buf) * nb_vtx;

        CopyCopyVertex(sizeof(*p_buf));

        p_str = NEXT_STRIP(p_str, nb_vtx, ufo);
    }
}

/****** Position+Color **************************************************************/
static void
PushStrip_PosCol(const CNK_STRIP* restrict pStrip, const int nbStripCnk, const int ufo, const CNK_VERTEX_BUFFER* restrict njvtxbuf)
{
    const CNK_STRIP* p_str = pStrip;

    for (int i = 0; i < nbStripCnk; ++i)
    {
        CnkStartTriStrip( p_str->len );

        GXBUF_POSCOL* p_buf = GetVertexBuffer();

        const int nb_strip = ABS(p_str->len);

        for (int j = 0; j < nb_strip; ++j)
        {
            const CNK_VERTEX_BUFFER* p_vtx = &njvtxbuf[ p_str->d[j].i ];

            /** Set draw buffer **/

            // set position
            p_buf->pos = p_vtx->pos;

            // set color
            p_buf->col = p_vtx->color;

            /** End set buffer **/

            ++p_buf;
        }

        _gx_vtx_buf_offset_ += sizeof(*p_buf) * nb_strip;

        CopyCopyVertex(sizeof(*p_buf));

        p_str = NEXT_STRIP(p_str, nb_strip, ufo);
    }
}

static void
PushStrip_PosCol_INV(const CNK_STRIP* restrict pStrip, const int nbStripCnk, const int ufo, const CNK_VERTEX_BUFFER* restrict njvtxbuf)
{
    const CNK_STRIP* p_str = pStrip;

    for (int i = 0; i < nbStripCnk; ++i)
    {
        CnkStartTriStripInverse( p_str->len );

        GXBUF_POSCOL* p_buf = GetVertexBuffer();

        const int nb_strip = ABS(p_str->len);

        for (int j = 0; j < nb_strip; ++j)
        {
            const CNK_VERTEX_BUFFER* p_vtx = &njvtxbuf[ p_str->d[j].i ];

            /** Set draw buffer **/

            // set position
            p_buf->pos = p_vtx->pos;

            // set color
            p_buf->col = p_vtx->color;

            /** End set buffer **/

            ++p_buf;
        }

        _gx_vtx_buf_offset_ += sizeof(*p_buf) * nb_strip;

        CopyCopyVertex(sizeof(*p_buf));

        p_str = NEXT_STRIP(p_str, nb_strip, ufo);
    }
}

/****** Flat Shading: Position+Normal ***********************************************/
static void
PushStrip_PosNorm_FL(const CNK_STRIP* restrict pStrip, const int nbStripCnk, const int ufo, const CNK_VERTEX_BUFFER* restrict njvtxbuf)
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
            /** vertex index and vertex increment for de-strip-ing the triangle **/
            int vidx, vinc;

            VIDX_START(vidx, vinc, inv_strip);

            NJS_VECTOR norm = {0}; // normal accumulator

            for (int k = 0; k < 3; ++k)
            {
                const CNK_VERTEX_BUFFER* restrict p_vtx = &njvtxbuf[ p_str->d[tidx+vidx].i ];

                /** Set draw buffer **/

                // set position
                p_buf->pos = p_vtx->pos;

                // add normal
                norm.x += p_vtx->norm.x;
                norm.y += p_vtx->norm.y;
                norm.z += p_vtx->norm.z;

                /** End set buffer **/

                vidx += vinc;

                p_buf++;
            }

            /** Adjust accumulated normal (div 3) **/
            norm.x *= (1.f/3.f);
            norm.y *= (1.f/3.f);
            norm.z *= (1.f/3.f);

            /** Set flat normal for triangle **/
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
PushStrip_PosNorm_FL_INV(const CNK_STRIP* restrict pStrip, const int nbStripCnk, const int ufo, const CNK_VERTEX_BUFFER* restrict njvtxbuf)
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
            /** vertex index and vertex increment for de-strip-ing the triangle **/
            int vidx, vinc;

            VIDX_START(vidx, vinc, inv_strip);

            NJS_VECTOR norm = {0}; // normal accumulator

            for (int k = 0; k < 3; ++k)
            {
                const CNK_VERTEX_BUFFER* restrict p_vtx = &njvtxbuf[ p_str->d[tidx+vidx].i ];

                /** Set draw buffer **/

                // set position
                p_buf->pos = p_vtx->pos;

                // sub normal
                norm.x -= p_vtx->norm.x;
                norm.y -= p_vtx->norm.y;
                norm.z -= p_vtx->norm.z;

                /** End set buffer **/

                vidx += vinc;

                p_buf++;
            }

            /** Adjust accumulated normal (div 3) **/
            norm.x *= (1.f/3.f);
            norm.y *= (1.f/3.f);
            norm.z *= (1.f/3.f);

            /** Set flat normal for triangle **/
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

/****** No-Normal Envmap: Position+Col+UV *******************************************/
static void
PushStrip_PosColUV_ENV(const CNK_STRIP* restrict pStrip, const int nbStripCnk, const int ufo, const CNK_VERTEX_BUFFER* restrict njvtxbuf)
{
    const CNK_STRIP* p_str = pStrip;

    for (int i = 0; i < nbStripCnk; ++i)
    {
        CnkStartTriStrip( p_str->len );

        GXBUF_POSCOLUV* p_buf = GetVertexBuffer();

        const int nb_vtx = ABS(p_str->len);

        for (int vidx = 0; vidx < nb_vtx; ++vidx)
        {
            const CNK_VERTEX_BUFFER* p_vtx = &njvtxbuf[ p_str->d[vidx].i ];

            /** Set draw buffer **/

            // set position
            p_buf->pos = p_vtx->pos;

            // set color
            p_buf->col = p_vtx->color;

            // set uv coords
            p_buf->u = -p_vtx->pos.x;
            p_buf->v = -p_vtx->pos.y;

            /** End set buffer **/

            ++p_buf;
        }

        _gx_vtx_buf_offset_ += sizeof(*p_buf) * nb_vtx;

        CopyCopyVertex(sizeof(*p_buf));

        p_str = NEXT_STRIP(p_str, nb_vtx, ufo);
    }
}

static void
PushStrip_PosColUV_ENV_INV(const CNK_STRIP* restrict pStrip, const int nbStripCnk, const int ufo, const CNK_VERTEX_BUFFER* restrict njvtxbuf)
{
    const CNK_STRIP* p_str = pStrip;

    for (int i = 0; i < nbStripCnk; ++i)
    {
        CnkStartTriStripInverse( p_str->len );

        GXBUF_POSCOLUV* p_buf = GetVertexBuffer();

        const int nb_vtx = ABS(p_str->len);

        for (int vidx = 0; vidx < nb_vtx; ++vidx)
        {
            const CNK_VERTEX_BUFFER* p_vtx = &njvtxbuf[ p_str->d[vidx].i ];

            /** Set draw buffer **/

            // set position
            p_buf->pos = p_vtx->pos;

            // set color
            p_buf->col = p_vtx->color;

            // set uv coords
            p_buf->u = -p_vtx->pos.x;
            p_buf->v = -p_vtx->pos.y;

            /** End set buffer **/

            ++p_buf;
        }

        _gx_vtx_buf_offset_ += sizeof(*p_buf) * nb_vtx;

        CopyCopyVertex(sizeof(*p_buf));

        p_str = NEXT_STRIP(p_str, nb_vtx, ufo);
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
rjCnkStrip_DB(CNK_CTX* const pCtx, const Sint16* plist, const CNK_VERTEX_BUFFER* njvtxbuf)
{
    CnkSetupStrip(pCtx);

    const int count = plist[2];

    const int nb_stcnk = count & ~NJD_UFO_MASK;
    const int ufo      = count >> NJD_UFO_SHIFT;

    CNK_STRIP* const p_str = (void*)&plist[3];

    if ( pCtx->fst & NJD_FST_ENV )
    {
        if ( _nj_cnk_vtx_attrs_ & CNKVTX_FLG_NONORM )
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

        if ( _nj_cnk_vtx_attrs_ & CNKVTX_FLG_VCOLOR )
        {
            VertexDeclInfo = VertexDecl_PosCol;

            if (pCtx->flag & CTXFLG_CULL_NORMAL)
                PushStrip_PosCol(p_str, nb_stcnk, ufo, njvtxbuf);

            if (pCtx->flag & CTXFLG_CULL_INVERSE)
                PushStrip_PosCol_INV(p_str, nb_stcnk, ufo, njvtxbuf);
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

    /** End CnkStrip and draw buffered vertex list **/

    GX_End();
}

void
rjCnkStrip(CNK_CTX* restrict pCtx, const Sint16* restrict plist, const CNK_VERTEX_BUFFER* restrict njvtxbuf)
{
    /** If this strip is double sided and we're not using Easy or Direct draw
        modes, then additional logic is required for correctly inverting normals.
        This logic is done in a seperate '_DB' function, so we can omit the extra
        logic when it isn't needed. Otherwise, the functions are the same. **/
    if ( pCtx->fst & NJD_FST_DB && !(pCtx->flag & (CTXFLG_FUNC_EASY|CTXFLG_FUNC_DIRECT) ))
    {
        rjCnkStrip_DB(pCtx, plist, njvtxbuf);
        return;
    }

    CnkSetupStrip(pCtx);

    const Sint16 count = plist[2];

    const int nb_stcnk = count & ~NJD_UFO_MASK;
    const int ufo      = count >> NJD_UFO_SHIFT;

    CNK_STRIP* const p_str = (void*)&plist[3];

    if ( pCtx->fst & NJD_FST_ENV )
    {
        /** Draw environment mapped strip **/

        if ( _nj_cnk_vtx_attrs_ & CNKVTX_FLG_NONORM )
        {
            CnkSetupTexStrip(pCtx);

            VertexDeclInfo = VertexDecl_PosColUV;

            PushStrip_PosColUV_ENV(p_str, nb_stcnk, ufo, njvtxbuf);
        }
        else
        {
            CnkSetupEnvStrip(pCtx);

            VertexDeclInfo = VertexDecl_PosNorm;

            if ( pCtx->fst & NJD_FST_FL )
            {
                PushStrip_PosNorm_FL(p_str, nb_stcnk, ufo, njvtxbuf);
            }
            else
            {
                PushStrip_PosNorm(p_str, nb_stcnk, ufo, njvtxbuf);
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

            PushStrip_PosCol(p_str, nb_stcnk, ufo, njvtxbuf);
        }
        else
        {
            /** We don't need to handle the case where the vertex attributes don't
                include normals, the shader just ignores them anyway. Although,
                this is a potential area of improvement in the future. **/

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

    /** End CnkStrip and draw buffered vertex list **/

    GX_End();
}

/************************************************************************************/
/*
*   Chunk Strip VN
*/

void
rjCnkStripVN(CNK_CTX* const pCtx, const Sint16* plist, const CNK_VERTEX_BUFFER* njvtxbuf)
{

}

/************************************************************************************/
/*
*   Chunk Strip UV VN
*/

void
rjCnkStripUVVN(CNK_CTX* const pCtx, const Sint16* plist, const CNK_VERTEX_BUFFER* njvtxbuf, bool uvh)
{

}

/************************************************************************************/
/*
*   Chunk Strip D8
*/

void
rjCnkStripD8(CNK_CTX* const pCtx, const Sint16* plist, const CNK_VERTEX_BUFFER* njvtxbuf)
{
    
}

/************************************************************************************/
/*
*   Chunk Strip UV D8
*/

void
rjCnkStripUVD8(CNK_CTX* const pCtx, const Sint16* plist, const CNK_VERTEX_BUFFER* njvtxbuf, bool uvh)
{

}
