/************************/
/*  Includes            */
/************************/
/****** Core Toolkit ****************************************************************/
#include <samt/core.h>      /* core                                                 */

/****** Ninja ***********************************************************************/
#include <samt/ninja/ninja.h> /* ninja                                              */

/****** Render Fix ******************************************************************/
#include <rf_core.h>        /* core                                                 */
#include <rf_renderstate.h> /* render state                                         */

/****** Self ************************************************************************/
#include <rf_draw/rfd_cnkmdl/rfdcnk_internal.h> /* parent & siblings                */

/************************/
/*  Constants           */
/************************/
/****** Ninja Vertex Max ************************************************************/
#define NJD_VERTOFF_MAX         (NJD_CV_NF_D8+1)

/************************/
/*  Source              */
/************************/
/****** Static **********************************************************************/
static void
rjCnkVertex(const Sint32* pVList, CNK_VERTEX_BUFFER* pVtxBuf)
{
    const CNK_VERTEX_HEAD* p_vhead = (void*) pVList;

    const int nb_vtx = p_vhead->nbindeces;

    /** Populate vertex buffer **/

    const CNK_VERTEX* p_vtx = (void*) p_vhead->d;

    CNK_VERTEX_BUFFER* p_buf = pVtxBuf;

    for (int i = 0; i < nb_vtx; ++i)
    {
        njCalcPoint(NULL, &p_vtx->pos, &p_buf->pos);

        ++p_vtx;
        ++p_buf;
    }
}

static void
rjCnkVertexD8(const Sint32* pVList, CNK_VERTEX_BUFFER* pVtxBuf)
{
    const CNK_VERTEX_HEAD* p_vhead = (void*) pVList;

    const int nb_vtx = p_vhead->nbindeces;

    /** Populate vertex buffer **/

    const CNK_VERTEX_D8* p_vtx = (void*) p_vhead->d;

    CNK_VERTEX_BUFFER* p_buf = pVtxBuf;

    for (int i = 0; i < nb_vtx; ++i)
    {
        njCalcPoint(NULL, &p_vtx->pos, &p_buf->pos);

        p_buf->col = p_vtx->col;

        ++p_vtx;
        ++p_buf;
    }
}

static void
rjCnkVertexVN(const Sint32* pVList, CNK_VERTEX_BUFFER* pVtxBuf)
{
    const CNK_VERTEX_HEAD* p_vhead = (void*) pVList;

    const int nb_vtx = p_vhead->nbindeces;

    /** Populate vertex buffer **/

    const CNK_VERTEX_VN* p_vtx = (void*) p_vhead->d;

    CNK_VERTEX_BUFFER* p_buf = pVtxBuf;

    for (int i = 0; i < nb_vtx; ++i)
    {
        njCalcPoint( NULL, &p_vtx->pos, &p_buf->pos);
        njCalcVector(NULL, &p_vtx->nrm, &p_buf->nrm);

        ++p_vtx;
        ++p_buf;
    }
}

static void
rjCnkVertexUF(const Sint32* pVList, CNK_VERTEX_BUFFER* pVtxBuf)
{
    const CNK_VERTEX_HEAD* p_vhead = (void*) pVList;

    const int nb_vtx = p_vhead->nbindeces;

    /** Populate vertex buffer **/

    const CNK_VERTEX_UF* p_vtx = (void*) p_vhead->d;

    CNK_VERTEX_BUFFER* p_buf = pVtxBuf;

    for (int i = 0; i < nb_vtx; ++i)
    {
        njCalcPoint(NULL, &p_vtx->pos, &p_buf->pos);

        ++p_vtx;
        ++p_buf;
    }
}

static void
rjCnkVertexVND8(const Sint32* pVList, CNK_VERTEX_BUFFER* pVtxBuf)
{
    const CNK_VERTEX_HEAD* p_vhead = (void*) pVList;

    const int nb_vtx = p_vhead->nbindeces;

    /** Populate vertex buffer **/

    const CNK_VERTEX_VN_D8* p_vtx = (void*) p_vhead->d;

    CNK_VERTEX_BUFFER* p_buf = pVtxBuf;

    for (int i = 0; i < nb_vtx; ++i)
    {
        njCalcPoint( NULL, &p_vtx->pos, &p_buf->pos);
        njCalcVector(NULL, &p_vtx->nrm, &p_buf->nrm);

        p_buf->col = p_vtx->col;

        ++p_vtx;
        ++p_buf;
    }
}

static void
rjCnkVertexVNUF(const Sint32* pVList, CNK_VERTEX_BUFFER* pVtxBuf)
{
    const CNK_VERTEX_HEAD* p_vhead = (void*) pVList;

    const int nb_vtx = p_vhead->nbindeces;

    /** Populate vertex buffer **/

    const CNK_VERTEX_VN_UF* p_vtx = (void*) p_vhead->d;

    CNK_VERTEX_BUFFER* p_buf = pVtxBuf;

    for (int i = 0; i < nb_vtx; ++i)
    {
        njCalcPoint( NULL, &p_vtx->pos, &p_buf->pos);
        njCalcVector(NULL, &p_vtx->nrm, &p_buf->nrm);

        ++p_vtx;
        ++p_buf;
    }
}

static void
rjCnkVertexNF(const Sint32* pVList, CNK_VERTEX_BUFFER* pVtxBuf)
{
    const CNK_VERTEX_HEAD* p_vhead = (void*) pVList;

    const int nb_vtx = p_vhead->nbindeces;

    const int wstat = p_vhead->wstat;

    /** Populate vertex buffer **/

    const CNK_VERTEX_NF* p_vtx = (void*) p_vhead->d;

    for (int i = 0; i < nb_vtx; ++i)
    {
        NJS_POINT3 pos;

        njCalcPoint( NULL, &p_vtx->pos , &pos);

        CNK_VERTEX_BUFFER* p_vbuf = &pVtxBuf[ p_vtx->i ];

        const f32 mul = CNK_GET_WEIGHT(p_vtx->w);

        pos.x *= mul;
        pos.y *= mul;
        pos.z *= mul;

        switch (wstat)
        {
            case CNK_WEIGHT_START:
            {
                p_vbuf->pos = pos;
                break;
            }
            case CNK_WEIGHT_MIDDLE:
            case CNK_WEIGHT_END:
            {
                p_vbuf->pos.x += pos.x;
                p_vbuf->pos.y += pos.y;
                p_vbuf->pos.z += pos.z;
                break;
            }
        }

        ++p_vtx;
    }
}

static void
rjCnkVertexVNNF(const Sint32* pVList, CNK_VERTEX_BUFFER* pVtxBuf)
{
    const CNK_VERTEX_HEAD* p_vhead = (void*) pVList;

    const int nb_vtx = p_vhead->nbindeces;

    const int wstat = p_vhead->wstat;

    /** Populate vertex buffer **/

    const CNK_VERTEX_VN_NF* p_vtx = (void*) p_vhead->d;

    for (int i = 0; i < nb_vtx; ++i)
    {
        NJS_POINT3 pos;
        NJS_VECTOR nrm;

        njCalcPoint( NULL, &p_vtx->pos , &pos);
        njCalcVector(NULL, &p_vtx->nrm, &nrm);

        CNK_VERTEX_BUFFER* p_vbuf = &pVtxBuf[ p_vtx->i ];

        const f32 mul = CNK_GET_WEIGHT(p_vtx->w);

        pos.x *= mul;
        pos.y *= mul;
        pos.z *= mul;

        nrm.x *= mul;
        nrm.y *= mul;
        nrm.z *= mul;

        switch (wstat)
        {
            case CNK_WEIGHT_START:
            {
                p_vbuf->pos = pos;
                p_vbuf->nrm = nrm;
                break;
            }
            case CNK_WEIGHT_MIDDLE:
            case CNK_WEIGHT_END:
            {
                p_vbuf->pos.x += pos.x;
                p_vbuf->pos.y += pos.y;
                p_vbuf->pos.z += pos.z;

                p_vbuf->nrm.x += nrm.x;
                p_vbuf->nrm.y += nrm.y;
                p_vbuf->nrm.z += nrm.z;
                break;
            }
        }

        ++p_vtx;
    }
}

static void
rjCnkVertexNFD8(const Sint32* pVList, CNK_VERTEX_BUFFER* pVtxBuf)
{
    const CNK_VERTEX_HEAD* p_vhead = (void*) pVList;

    const int nb_vtx = p_vhead->nbindeces;

    const int wstat = p_vhead->wstat;

    /** Populate vertex buffer **/

    const CNK_VERTEX_NF_D8* p_vtx = (void*) p_vhead->d;

    ___NOTE("Still undecided on how this will function.");

    for (int i = 0; i < nb_vtx; ++i)
    {
        NJS_POINT3 pos;

        njCalcPoint( NULL, &p_vtx->pos , &pos);

        CNK_VERTEX_BUFFER* p_vbuf = &pVtxBuf[ p_vtx->i ];

        const f32 mul = CNK_GET_WEIGHT(p_vtx->w);

        pos.x *= mul;
        pos.y *= mul;
        pos.z *= mul;

        switch (wstat)
        {
            case CNK_WEIGHT_START:
            {
                p_vbuf->pos = pos;
                p_vbuf->col = p_vtx->col;
                break;
            }
            case CNK_WEIGHT_MIDDLE:
            case CNK_WEIGHT_END:
            {
                p_vbuf->pos.x += pos.x;
                p_vbuf->pos.y += pos.y;
                p_vbuf->pos.z += pos.z;
                break;
            }
        }

        ++p_vtx;
    }
}

/****** Extern **********************************************************************/
int
rjCnkVList(const Sint32* pVList, CNK_VERTEX_BUFFER* njvtxbuf)
{
    const bool multi = ( RFRS_GetCnkFuncMode() & RFRS_CNKFUNCMD_MULTIBIT );

    const Sint32* vlist = pVList;

    for ( ; ; )
    {
        /** It is possible for models to contain more than 1 vertex list, but it's
            incredibly unlikely and I don't think it's even used in SA2. **/

        const int type = CNK_GET_OFFTYPE(vlist);

        if (type == NJD_ENDOFF)
        {
            /** NJD_ENDOFF **/
            break;
        }

        const CNK_VERTEX_HEAD* p_vhead = (void*)vlist;

        /** Get the vertex buffer offset for this vertex list. Verteces are copied
            from the 'vlist' sequentially into the vertex buffer starting from this
            offset. The vertex buffer struct def is fixed. **/
        CNK_VERTEX_BUFFER* p_vbuf = &njvtxbuf[ p_vhead->indexoffset ];

        switch (type)
        {
            case NJD_CV:
            {
                _nj_cnk_vtx_attrs_ = CNKVTX_POS;

                /** No normals, halt drawing if 'MultiDraw' **/
                if (multi)
                    return -1;

                rjCnkVertex(vlist, p_vbuf);
                break;
            }
            case NJD_CV_D8:
            {
                _nj_cnk_vtx_attrs_ = CNKVTX_POS_COL;

                /** No normals, halt drawing if 'MultiDraw' **/
                if (multi)
                    return -1;

                rjCnkVertexD8(vlist, p_vbuf);
                break;
            }
            case NJD_CV_UF:
            {
                _nj_cnk_vtx_attrs_ = CNKVTX_POS;

                /** No normals, halt drawing if 'MultiDraw' **/
                if (multi)
                    return -1;

                rjCnkVertexUF(vlist, p_vbuf);
                break;
            }
            case NJD_CV_NF:
            {
                _nj_cnk_vtx_attrs_ = CNKVTX_POS_NJF;

                /** No normals, halt drawing if 'MultiDraw' **/
                if (multi)
                    return -1;

                rjCnkVertexNF(vlist, p_vbuf);
                break;
            }
            case NJD_CV_VN:
            {
                _nj_cnk_vtx_attrs_ = CNKVTX_POS_NRM;

                rjCnkVertexVN(vlist, p_vbuf);
                break;
            }
            case NJD_CV_VN_D8:
            {
                _nj_cnk_vtx_attrs_ = CNKVTX_POS_NRM_COL;

                rjCnkVertexVND8(vlist, p_vbuf);
                break;
            }
            case NJD_CV_VN_UF:
            {
                _nj_cnk_vtx_attrs_ = CNKVTX_POS_NRM;

                rjCnkVertexVNUF(vlist, p_vbuf);
                break;
            }
            case NJD_CV_VN_NF:
            {
                _nj_cnk_vtx_attrs_ = CNKVTX_POS_NRM_NJF;
                
                rjCnkVertexVNNF(vlist, p_vbuf);
                break;
            }
            case NJD_CV_NF_D8:
            {
                _nj_cnk_vtx_attrs_ = CNKVTX_POS_NJF_COL;

                /** No normals, halt drawing if 'MultiDraw' **/
                if (multi)
                    return -1;

                rjCnkVertexNFD8(vlist, p_vbuf);
                break;
            }
            default:
            {
                /** Unhandled vertex type, halt draw. **/
                return -1;
            }
        }

        /** Next data chunk **/
        vlist += p_vhead->size + 1;
    }

    return 0;
}
