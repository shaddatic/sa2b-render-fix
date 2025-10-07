/************************/
/*  Includes            */
/************************/
/****** Core Toolkit ****************************************************************/
#include <samt/core.h>      /* core                                                 */

/****** Ninja ***********************************************************************/
#include <samt/ninja/ninja.h> /* ninja                                              */

/****** Render Fix ******************************************************************/
#include <rf_core.h>        /* core                                                 */

/****** Self ************************************************************************/
#include <rf_ninja/rj_cnkmod/rfdmod_internal.h> /* parent & siblings                */

/************************/
/*  Source              */
/************************/
/****** Static **********************************************************************/
static void
rjCnkModVertex(const Sint32* pVList, RJS_VERTEX_BUF* pVtxBuf)
{
    const CNK_VERTEX_HEAD* p_vhead = (void*) pVList;

    const int nb_vtx = p_vhead->nbindeces;

    /** Populate vertex buffer **/

    const CNK_VERTEX* p_vtx = (void*) p_vhead->d;

    RJS_VERTEX_BUF* p_buf = pVtxBuf;

    for (int i = 0; i < nb_vtx; ++i)
    {
        njCalcPoint(NULL, &p_vtx->pos, &p_buf->pos);

        p_vtx++;
        p_buf++;
    }
}

static void
rjCnkModVertexD8(const Sint32* pVList, RJS_VERTEX_BUF* pVtxBuf)
{
    const CNK_VERTEX_HEAD* p_vhead = (void*) pVList;

    const int nb_vtx = p_vhead->nbindeces;

    /** Populate vertex buffer **/

    const CNK_VERTEX_D8* p_vtx = (void*) p_vhead->d;

    RJS_VERTEX_BUF* p_buf = pVtxBuf;

    for (int i = 0; i < nb_vtx; ++i)
    {
        njCalcPoint(NULL, &p_vtx->pos, &p_buf->pos);

        p_vtx++;
        p_buf++;
    }
}

static void
rjCnkModVertexVN(const Sint32* pVList, RJS_VERTEX_BUF* pVtxBuf)
{
    const CNK_VERTEX_HEAD* p_vhead = (void*) pVList;

    const int nb_vtx = p_vhead->nbindeces;

    /** Populate vertex buffer **/

    const CNK_VERTEX_VN* p_vtx = (void*) p_vhead->d;

    RJS_VERTEX_BUF* p_buf = pVtxBuf;

    for (int i = 0; i < nb_vtx; ++i)
    {
        njCalcPoint(NULL, &p_vtx->pos, &p_buf->pos);

        p_vtx++;
        p_buf++;
    }
}

static void
rjCnkModVertexVND8(const Sint32* pVList, RJS_VERTEX_BUF* pVtxBuf)
{
    const CNK_VERTEX_HEAD* p_vhead = (void*) pVList;

    const int nb_vtx = p_vhead->nbindeces;

    /** Populate vertex buffer **/

    const CNK_VERTEX_VN_D8* p_vtx = (void*) p_vhead->d;

    RJS_VERTEX_BUF* p_buf = pVtxBuf;

    for (int i = 0; i < nb_vtx; ++i)
    {
        njCalcPoint(NULL, &p_vtx->pos, &p_buf->pos);

        p_vtx++;
        p_buf++;
    }
}

static void
rjCnkModVertexVNNF(const Sint32* pVList, RJS_VERTEX_BUF* vbuf)
{
    const CNK_VERTEX_HEAD* p_vhead = (void*) pVList;

    const int nb_vtx = p_vhead->nbindeces;

    const int wstat = p_vhead->wstat;

    /** Populate vertex buffer **/

    const CNK_VERTEX_VN_NF* p_vtx = (void*) p_vhead->d;

    for (int i = 0; i < nb_vtx; ++i)
    {
        NJS_POINT3 pos;

        njCalcPoint(NULL, &p_vtx->pos, &pos);

        RJS_VERTEX_BUF* p_vbuf = &vbuf[ p_vtx->i ];

        const f32 mul = CNK_GET_WEIGHT(p_vtx->w);

        pos.x *= mul;
        pos.y *= mul;
        pos.z *= mul;

        switch (wstat)
        {
            case CNK_WEIGHT_START:
            {
                p_vbuf->pos  = pos;
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
Sint32
rjCnkModVList(const Sint32* const pVList, RJS_VERTEX_BUF* const vbuf)
{
    const Sint32* vlist = pVList;

    for ( ; ; )
    {
        const int type = CNK_GET_OFFTYPE(vlist);

        if (type == NJD_ENDOFF)
        {
            /** NJD_ENDOFF **/
            break;
        }

        const CNK_VERTEX_HEAD* pvhead = (void*)vlist;

        RJS_VERTEX_BUF* p_vbuf = &vbuf[ pvhead->indexoffset ];

        switch (type)
        {
            case NJD_CV: /** Original Mod Vertex Fmt **/
            {
                rjCnkModVertex(vlist, p_vbuf);
                break;
            }
            case NJD_CV_D8:
            {
                rjCnkModVertexD8(vlist, p_vbuf);
                break;
            }
            case NJD_CV_VN:
            {
                rjCnkModVertexVN(vlist, p_vbuf);
                break;
            }
            case NJD_CV_VN_D8:
            {
                rjCnkModVertexVND8(vlist, p_vbuf);
                break;
            }
            case NJD_CV_VN_NF:
            {
                rjCnkModVertexVNNF(vlist, p_vbuf);
                break;
            }
            default:
            {
                return CNK_RETN_CLIP;
            }
        }

        /** Next data chunk **/
        vlist += pvhead->size + 1;
    }

    return CNK_RETN_OK;
}
