/************************/
/*  Includes            */
/************************/
/****** Core Toolkit ****************************************************************/
#include <sa2b/core.h>      /* core                                                 */

/****** Ninja ***********************************************************************/
#include <sa2b/ninja/ninja.h> /* ninja                                              */

/****** Render Fix ******************************************************************/
#include <rf_core.h>        /* core                                                 */

/****** Self ************************************************************************/
#include <rf_draw/rfd_cnkmod/rfdmod_internal.h> /* parent & siblings                */

/************************/
/*  Source              */
/************************/
/****** Static **********************************************************************/
static void
rjCnkModVertex(const Sint32* pVList, CNK_VERTEX_BUFFER* pVtxBuf)
{
    const CNK_VERTEX_HEAD* p_vhead = (void*) pVList;

    const int nb_vtx = p_vhead->nbindeces;

    /** Populate vertex buffer **/

    const CNK_VERTEX* p_vtx = (void*) p_vhead->d;

    CNK_VERTEX_BUFFER* p_buf = pVtxBuf;

    for (int i = 0; i < nb_vtx; ++i)
    {
        njCalcPoint(NULL, &(p_vtx++)->pos, &(p_buf++)->pos);
    }
}

static void
rjCnkModVertexD8(const Sint32* pVList, CNK_VERTEX_BUFFER* pVtxBuf)
{
    const CNK_VERTEX_HEAD* p_vhead = (void*) pVList;

    const int nb_vtx = p_vhead->nbindeces;

    /** Populate vertex buffer **/

    const CNK_VERTEX_D8* p_vtx = (void*) p_vhead->d;

    CNK_VERTEX_BUFFER* p_buf = pVtxBuf;

    for (int i = 0; i < nb_vtx; ++i)
    {
        njCalcPoint(NULL, &(p_vtx++)->pos, &(p_buf++)->pos);
    }
}

static void
rjCnkModVertexVN(const Sint32* pVList, CNK_VERTEX_BUFFER* pVtxBuf)
{
    const CNK_VERTEX_HEAD* p_vhead = (void*) pVList;

    const int nb_vtx = p_vhead->nbindeces;

    /** Populate vertex buffer **/

    const CNK_VERTEX_VN* p_vtx = (void*) p_vhead->d;

    CNK_VERTEX_BUFFER* p_buf = pVtxBuf;

    for (int i = 0; i < nb_vtx; ++i)
    {
        njCalcPoint(NULL, &(p_vtx++)->pos, &(p_buf++)->pos);
    }
}

static void
rjCnkModVertexVND8(const Sint32* pVList, CNK_VERTEX_BUFFER* pVtxBuf)
{
    const CNK_VERTEX_HEAD* p_vhead = (void*) pVList;

    const int nb_vtx = p_vhead->nbindeces;

    /** Populate vertex buffer **/

    const CNK_VERTEX_VN_D8* p_vtx = (void*) p_vhead->d;

    CNK_VERTEX_BUFFER* p_buf = pVtxBuf;

    for (int i = 0; i < nb_vtx; ++i)
    {
        njCalcPoint(NULL, &(p_vtx++)->pos, &(p_buf++)->pos);
    }
}

static void
rjCnkModVertexVNNF(const Sint32* pVList, CNK_VERTEX_BUFFER* pVtxBuf)
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

        CNK_VERTEX_BUFFER* p_vbuf = &pVtxBuf[ p_vtx->i ];

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
int32_t
rjCnkModVList(const Sint32* const pVList, CNK_VERTEX_BUFFER* const njvtxbuf)
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

        CNK_VERTEX_BUFFER* p_vbuf = &njvtxbuf[ pvhead->indexoffset ];

        switch (type) {
        case NJD_CV: /** Original Mod Vertex Fmt **/
            rjCnkModVertex(vlist, p_vbuf);
            break;

        case NJD_CV_D8:
            rjCnkModVertexD8(vlist, p_vbuf);
            break;

        case NJD_CV_VN:
            rjCnkModVertexVN(vlist, p_vbuf);
            break;

        case NJD_CV_VN_D8:
            rjCnkModVertexVND8(vlist, p_vbuf);
            break;

        case NJD_CV_VN_NF:
            rjCnkModVertexVNNF(vlist, p_vbuf);
            break;
        }

        /** Next data chunk **/
        vlist += pvhead->size + 1;
    }

    return 0;
}
