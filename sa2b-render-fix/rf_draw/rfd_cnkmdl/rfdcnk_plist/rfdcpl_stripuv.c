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
PushStripUV_PosNorm(const CNK_STRIP_UV* const pStrip, const int nbStripCnk, const int ufo, const CNK_VERTEX_BUFFER* const njvtxbuf)
{
    const CNK_STRIP_UV* p_str = pStrip;

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

            // set normal
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
PushStripUV_PosNorm_INV(const CNK_STRIP_UV* restrict pStrip, const int nbStripCnk, const int ufo, const CNK_VERTEX_BUFFER* restrict njvtxbuf)
{
    const CNK_STRIP_UV* p_str = pStrip;

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

/****** Position+Normal+UV **********************************************************/
static void
PushStripUV_PosNormUV(const CNK_STRIP_UV* restrict pStrip, const int nbStripCnk, const int ufo, const CNK_VERTEX_BUFFER* restrict njvtxbuf, const f32 uvMul)
{
    const f32 offset_u = _rj_cnk_uv_offset_u_;
    const f32 offset_v = _rj_cnk_uv_offset_v_;

    const CNK_STRIP_UV* p_str = pStrip;

    for (int i = 0; i < nbStripCnk; ++i)
    {
        CnkStartTriStrip( p_str->len );

        GXBUF_POSNORMUV* p_buf = GetVertexBuffer();

        const int nb_vtx = ABS(p_str->len);

        for (int vidx = 0; vidx < nb_vtx; ++vidx)
        {
            const CNK_VERTEX_BUFFER* p_vtx = &njvtxbuf[ p_str->d[vidx].i ];

            /** Set draw buffer **/

            // set position
            p_buf->pos = p_vtx->pos;

            // set normal
            p_buf->norm = p_vtx->norm;

            // set uv coords
            p_buf->u = ((f32)p_str->d[vidx].u * uvMul) + offset_u;
            p_buf->v = ((f32)p_str->d[vidx].v * uvMul) + offset_v;

            ++p_buf;
        }

        _gx_vtx_buf_offset_ += sizeof(*p_buf) * nb_vtx;

        CopyCopyVertex(sizeof(*p_buf));

        p_str = NEXT_STRIP(p_str, nb_vtx, ufo);
    }
}

static void
PushStripUV_PosNormUV_INV(const CNK_STRIP_UV* restrict pStrip, const int nbStripCnk, const int ufo, const CNK_VERTEX_BUFFER* restrict njvtxbuf, const f32 uvMul)
{
    const f32 offset_u = _rj_cnk_uv_offset_u_;
    const f32 offset_v = _rj_cnk_uv_offset_v_;

    const CNK_STRIP_UV* p_str = pStrip;

    for (int i = 0; i < nbStripCnk; ++i)
    {
        CnkStartTriStripInverse( p_str->len );

        GXBUF_POSNORMUV* p_buf = GetVertexBuffer();

        const int nb_vtx = ABS(p_str->len);

        for (int vidx = 0; vidx < nb_vtx; ++vidx)
        {
            const CNK_VERTEX_BUFFER* p_vtx = &njvtxbuf[ p_str->d[vidx].i ];

            /** Set draw buffer **/

            // set pos
            p_buf->pos = p_vtx->pos;

            // Set inverted normal
            p_buf->norm.x = -p_vtx->norm.x;
            p_buf->norm.y = -p_vtx->norm.y;
            p_buf->norm.z = -p_vtx->norm.z;

            // set uv coords
            p_buf->u = ((f32)p_str->d[vidx].u * uvMul) + offset_u;
            p_buf->v = ((f32)p_str->d[vidx].v * uvMul) + offset_v;

            /** End set buffer **/

            ++p_buf;
        }

        _gx_vtx_buf_offset_ += sizeof(*p_buf) * nb_vtx;

        CopyCopyVertex(sizeof(*p_buf));

        p_str = NEXT_STRIP(p_str, nb_vtx, ufo);
    }
}

/****** Position+Color+UV ***********************************************************/
static void
PushStripUV_PosColUV(const CNK_STRIP_UV* restrict pStrip, const int nbStripCnk, const int ufo, const CNK_VERTEX_BUFFER* restrict njvtxbuf, const f32 uvMul)
{
    const f32 offset_u = _rj_cnk_uv_offset_u_;
    const f32 offset_v = _rj_cnk_uv_offset_v_;

    const CNK_STRIP_UV* p_str = pStrip;

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
            p_buf->u = ((f32)p_str->d[vidx].u * uvMul) + offset_u;
            p_buf->v = ((f32)p_str->d[vidx].v * uvMul) + offset_v;

            /** End set buffer **/

            ++p_buf;
        }

        _gx_vtx_buf_offset_ += sizeof(*p_buf) * nb_vtx;

        CopyCopyVertex(sizeof(*p_buf));

        p_str = NEXT_STRIP(p_str, nb_vtx, ufo);
    }
}

static void
PushStripUV_PosColUV_INV(const CNK_STRIP_UV* restrict pStrip, const int nbStripCnk, const int ufo, const CNK_VERTEX_BUFFER* restrict njvtxbuf, const f32 uvMul)
{
    const f32 offset_u = _rj_cnk_uv_offset_u_;
    const f32 offset_v = _rj_cnk_uv_offset_v_;

    const CNK_STRIP_UV* p_str = pStrip;

    for (int i = 0; i < nbStripCnk; ++i)
    {
        CnkStartTriStripInverse( p_str->len );

        GXBUF_POSCOLUV* p_buf = GetVertexBuffer();

        const int nb_vtx = ABS(p_str->len);

        for (int vidx = 0; vidx < nb_vtx; ++vidx)
        {
            const CNK_VERTEX_BUFFER* p_vtx = &njvtxbuf[ p_str->d[vidx].i ];

            /** Set draw buffer **/

            // set pos
            p_buf->pos = p_vtx->pos;

            // set color
            p_buf->col = p_vtx->color;

            // set uv coords
            p_buf->u = ((f32)p_str->d[vidx].u * uvMul) + offset_u;
            p_buf->v = ((f32)p_str->d[vidx].v * uvMul) + offset_v;

            /** End set buffer **/

            ++p_buf;
        }

        _gx_vtx_buf_offset_ += sizeof(*p_buf) * nb_vtx;

        CopyCopyVertex(sizeof(*p_buf));

        p_str = NEXT_STRIP(p_str, nb_vtx, ufo);
    }
}

/****** Flat Shading: Position+Normal ***********************************************/
static void
PushStripUV_PosNorm_FL(const CNK_STRIP_UV* restrict pStrip, const int nbStripCnk, const int ufo, const CNK_VERTEX_BUFFER* restrict njvtxbuf)
{
    const CNK_STRIP_UV* p_str = pStrip;

    for (int i = 0; i < nbStripCnk; ++i)
    {
        CnkStartTriList( p_str->len );

        GXBUF_POSNORM* p_buf = GetVertexBuffer();

        const int nb_vtx = ABS(p_str->len);

        const int nb_tri = (nb_vtx - 2);

        bool inv_strip = (p_str->len < 0);

        for (int tidx = 0; tidx < nb_tri; ++tidx)
        {
            const NJS_POINT3* p_vtxpos[3];

            /** vertex index and vertex increment for de-strip-ing the triangle **/
            int vidx, vinc;

            VIDX_START(vidx, vinc, inv_strip);

            NJS_VECTOR norm = {0}; // normal accumulator

            for (int k = 0; k < 3; ++k)
            {
                const CNK_VERTEX_BUFFER* restrict p_vtx = &njvtxbuf[ p_str->d[tidx+vidx].i ];

                p_vtxpos[k] = &p_vtx->pos;

                /** Set draw buffer **/

                // set pos
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

        p_str = NEXT_STRIP(p_str, nb_vtx, ufo);
    }
}

static void
PushStripUV_PosNorm_FL_INV(const CNK_STRIP_UV* restrict pStrip, const int nbStripCnk, const int ufo, const CNK_VERTEX_BUFFER* restrict njvtxbuf)
{
    const CNK_STRIP_UV* p_str = pStrip;

    for (int i = 0; i < nbStripCnk; ++i)
    {
        CnkStartTriListInverse( p_str->len );

        GXBUF_POSNORM* p_buf = GetVertexBuffer();

        const int nb_vtx = ABS(p_str->len);

        const int nb_tri = (nb_vtx - 2);

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

        p_str = NEXT_STRIP(p_str, nb_vtx, ufo);
    }
}

/****** Flat Shading: Position+Normal+UV *********************************************/
static void
PushStripUV_PosNormUV_FL(const CNK_STRIP_UV* restrict pStrip, const int nbStripCnk, const int ufo, const CNK_VERTEX_BUFFER* restrict njvtxbuf, const f32 uvMul)
{
    const f32 offset_u = _rj_cnk_uv_offset_u_;
    const f32 offset_v = _rj_cnk_uv_offset_v_;

    const CNK_STRIP_UV* p_str = pStrip;

    for (int i = 0; i < nbStripCnk; ++i)
    {
        CnkStartTriList( p_str->len );

        GXBUF_POSNORMUV* p_buf = GetVertexBuffer();

        const int nb_vtx = ABS(p_str->len);

        const int nb_tri = (nb_vtx - 2);

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

                // set uv coords
                p_buf->u = ((f32)p_str->d[tidx+vidx].u * uvMul) + offset_u;
                p_buf->v = ((f32)p_str->d[tidx+vidx].v * uvMul) + offset_v;

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

        p_str = NEXT_STRIP(p_str, nb_vtx, ufo);
    }
}

static void
PushStripUV_PosNormUV_FL_INV(const CNK_STRIP_UV* restrict pStrip, const int nbStripCnk, const int ufo, const CNK_VERTEX_BUFFER* restrict njvtxbuf, const f32 uvMul)
{
    const f32 offset_u = _rj_cnk_uv_offset_u_;
    const f32 offset_v = _rj_cnk_uv_offset_v_;

    const CNK_STRIP_UV* p_str = pStrip;

    for (int i = 0; i < nbStripCnk; ++i)
    {
        CnkStartTriListInverse( p_str->len );

        GXBUF_POSNORMUV* p_buf = GetVertexBuffer();

        const int nb_vtx = ABS(p_str->len);

        const int nb_tri = (nb_vtx - 2);

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

                // set pos
                p_buf->pos = p_vtx->pos;

                // sub normal
                norm.x -= p_vtx->norm.x;
                norm.y -= p_vtx->norm.y;
                norm.z -= p_vtx->norm.z;

                // set uv coords
                p_buf->u = ((f32)p_str->d[tidx+vidx].u * uvMul) + offset_u;
                p_buf->v = ((f32)p_str->d[tidx+vidx].v * uvMul) + offset_v;

                /** End set buffer **/

                vidx += vinc;

                p_buf++;
            }

            /** Adjust accumulated normal (div 3) **/
            norm.x *= (1.f/3.f);
            norm.y *= (1.f/3.f);
            norm.z *= (1.f/3.f);

            /** Set inverted flat normal for triangle **/
            p_buf[-3].norm = norm;
            p_buf[-2].norm = norm;
            p_buf[-1].norm = norm;

            /** Swap strip inverse mode for next tri **/
            inv_strip = !inv_strip;
        }

        _gx_vtx_buf_offset_ += sizeof(*p_buf) * (nb_tri * 3);

        p_str = NEXT_STRIP(p_str, nb_vtx, ufo);
    }
}

/****** No-Normal Envmap: Position+Color+UV *****************************************/
static void
PushStripUV_PosColUV_ENV(const CNK_STRIP_UV* const pStrip, const int nbStripCnk, const int ufo, const CNK_VERTEX_BUFFER* const njvtxbuf)
{
    const f32 offset_u = _rj_cnk_uv_offset_u_;
    const f32 offset_v = _rj_cnk_uv_offset_v_;

    const CNK_STRIP_UV* p_str = pStrip;

    for (int i = 0; i < nbStripCnk; ++i)
    {
        CnkStartTriStrip( p_str->len );

        GXBUF_POSCOLUV* p_buf = GetVertexBuffer();

        const int nb_vtx = ABS(p_str->len);

        for (int vidx = 0; vidx < nb_vtx; ++vidx)
        {
            const CNK_VERTEX_BUFFER* restrict p_vtx = &njvtxbuf[ p_str->d[vidx].i ];

            // set position
            p_buf->pos = p_vtx->pos;

            // set color
            p_buf->col = p_vtx->color;

            // set uv coords
            p_buf->u = -p_vtx->pos.x + offset_u;
            p_buf->v = -p_vtx->pos.y + offset_v;

            /** End set buffer **/

            ++p_buf;
        }

        _gx_vtx_buf_offset_ += sizeof(*p_buf) * nb_vtx;

        CopyCopyVertex(sizeof(*p_buf));

        p_str = NEXT_STRIP(p_str, nb_vtx, ufo);
    }
}

static inline void
PushStripUV_PosColUV_ENV_INV(const CNK_STRIP_UV* const pStrip, const int nbStripCnk, const int ufo, const CNK_VERTEX_BUFFER* const njvtxbuf)
{
    const f32 offset_u = _rj_cnk_uv_offset_u_;
    const f32 offset_v = _rj_cnk_uv_offset_v_;

    const CNK_STRIP_UV* p_str = pStrip;

    for (int i = 0; i < nbStripCnk; ++i)
    {
        CnkStartTriStripInverse( p_str->len );

        GXBUF_POSCOLUV* p_buf = GetVertexBuffer();

        const int nb_vtx = ABS(p_str->len);

        for (int vidx = 0; vidx < nb_vtx; ++vidx)
        {
            const CNK_VERTEX_BUFFER* restrict p_vtx = &njvtxbuf[ p_str->d[vidx].i ];

            /** Set draw buffer **/

            // set position
            p_buf->pos = p_vtx->pos;

            // set color
            p_buf->col = p_vtx->color;

            // set uv coords
            p_buf->u = -p_vtx->pos.x + offset_u;
            p_buf->v = -p_vtx->pos.y + offset_v;

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
*   Chunk Strip UV
*/

/****** Static **********************************************************************/
static void
CnkSetupStripUV(CNK_CTX* pCtx)
{
    pCtx->flag &= ~CTXFLG_STRIP_NOUVS;
}

/****** Extern **********************************************************************/
static void
rjCnkStripUV_DB(CNK_CTX* const pCtx, const Sint16* plist, const CNK_VERTEX_BUFFER* njvtxbuf, bool uvh)
{
    CnkSetupStripUV(pCtx);

    const int count = plist[2];

    const int nb_stcnk = count & ~NJD_UFO_MASK;
    const int ufo      = count >> NJD_UFO_SHIFT;

    const f32 uv_mul = GET_UV_MUL(uvh);

    CNK_STRIP_UV* const p_str = (void*)&plist[3];

    if (pCtx->fst & NJD_FST_ENV)
    {
        if (_nj_cnk_vtx_attrs_ & CNKVTX_FLG_NONORM)
        {
            CnkSetupTexStrip(pCtx);

            VertexDeclInfo = VertexDecl_PosColUV;

            if (pCtx->flag & CTXFLG_CULL_NORMAL)
                PushStripUV_PosColUV_ENV(p_str, nb_stcnk, ufo, njvtxbuf);

            if (pCtx->flag & CTXFLG_CULL_INVERSE)
                PushStripUV_PosColUV_ENV_INV(p_str, nb_stcnk, ufo, njvtxbuf);
        }
        else
        {
            CnkSetupEnvStrip(pCtx);

            VertexDeclInfo = VertexDecl_PosNorm;

            if (pCtx->fst & NJD_FST_FL)
            {
                if (pCtx->flag & CTXFLG_CULL_NORMAL)
                    PushStripUV_PosNorm_FL(p_str, nb_stcnk, ufo, njvtxbuf);

                if (pCtx->flag & CTXFLG_CULL_INVERSE)
                    PushStripUV_PosNorm_FL_INV(p_str, nb_stcnk, ufo, njvtxbuf);
            }
            else
            {
                if (pCtx->flag & CTXFLG_CULL_NORMAL)
                    PushStripUV_PosNorm(p_str, nb_stcnk, ufo, njvtxbuf);

                if (pCtx->flag & CTXFLG_CULL_INVERSE)
                    PushStripUV_PosNorm_INV(p_str, nb_stcnk, ufo, njvtxbuf);
            }
        }
    }
    else
    {
        CnkSetupTexStrip(pCtx);

        if (_nj_cnk_vtx_attrs_ & CNKVTX_FLG_VCOLOR)
        {
            VertexDeclInfo = VertexDecl_PosColUV;

            if (pCtx->flag & CTXFLG_CULL_NORMAL)
                PushStripUV_PosColUV(p_str, nb_stcnk, ufo, njvtxbuf, uv_mul);

            if (pCtx->flag & CTXFLG_CULL_INVERSE)
                PushStripUV_PosColUV_INV(p_str, nb_stcnk, ufo, njvtxbuf, uv_mul);
        }
        else
        {
            VertexDeclInfo = VertexDecl_PosNormUV;

            if (pCtx->fst & NJD_FST_FL)
            {
                if (pCtx->flag & CTXFLG_CULL_NORMAL)
                    PushStripUV_PosNormUV_FL(p_str, nb_stcnk, ufo, njvtxbuf, uv_mul);

                if (pCtx->flag & CTXFLG_CULL_INVERSE)
                    PushStripUV_PosNormUV_FL_INV(p_str, nb_stcnk, ufo, njvtxbuf, uv_mul);
            }
            else
            {
                if (pCtx->flag & CTXFLG_CULL_NORMAL)
                    PushStripUV_PosNormUV(p_str, nb_stcnk, ufo, njvtxbuf, uv_mul);

                if (pCtx->flag & CTXFLG_CULL_INVERSE)
                    PushStripUV_PosNormUV_INV(p_str, nb_stcnk, ufo, njvtxbuf, uv_mul);
            }
        }
    }

    GX_End(); // Draw buffered vertex list
}

void
rjCnkStripUV(CNK_CTX* const pCtx, const Sint16* plist, const CNK_VERTEX_BUFFER* njvtxbuf, bool uvh)
{
    if ( pCtx->fst & NJD_FST_DB && !(pCtx->flag & (CTXFLG_FUNC_EASY|CTXFLG_FUNC_DIRECT) ))
    {
        rjCnkStripUV_DB(pCtx, plist, njvtxbuf, uvh);
        return;
    }

    CnkSetupStripUV(pCtx);

    const int count = plist[2];

    const int nb_stcnk = count & ~NJD_UFO_MASK;
    const int ufo      = count >> NJD_UFO_SHIFT;

    const f32 uv_mul = GET_UV_MUL(uvh);

    CNK_STRIP_UV* const p_str = (void*)&plist[3];

    if (pCtx->fst & NJD_FST_ENV)
    {
        if (_nj_cnk_vtx_attrs_ & CNKVTX_FLG_NONORM)
        {
            CnkSetupTexStrip(pCtx);

            VertexDeclInfo = VertexDecl_PosColUV;

            PushStripUV_PosColUV_ENV(p_str, nb_stcnk, ufo, njvtxbuf);
        }
        else
        {
            CnkSetupEnvStrip(pCtx);

            VertexDeclInfo = VertexDecl_PosNorm;

            if (pCtx->fst & NJD_FST_FL)
            {
                PushStripUV_PosNorm_FL(p_str, nb_stcnk, ufo, njvtxbuf);
            }
            else
            {
                PushStripUV_PosNorm(p_str, nb_stcnk, ufo, njvtxbuf);
            }
        }
    }
    else
    {
        CnkSetupTexStrip(pCtx);

        if (_nj_cnk_vtx_attrs_ & CNKVTX_FLG_VCOLOR)
        {
            VertexDeclInfo = VertexDecl_PosColUV;

            PushStripUV_PosColUV(p_str, nb_stcnk, ufo, njvtxbuf, uv_mul);
        }
        else
        {
            VertexDeclInfo = VertexDecl_PosNormUV;

            if (pCtx->fst & NJD_FST_FL)
            {
                PushStripUV_PosNormUV_FL(p_str, nb_stcnk, ufo, njvtxbuf, uv_mul);
            }
            else
            {
                PushStripUV_PosNormUV(p_str, nb_stcnk, ufo, njvtxbuf, uv_mul);
            }
        }
    }

    GX_End(); // Draw buffered vertex list
}
