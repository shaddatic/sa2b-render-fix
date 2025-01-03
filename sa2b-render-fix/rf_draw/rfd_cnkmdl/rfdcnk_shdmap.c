/************************/
/*  Includes            */
/************************/
/****** Core Toolkit ****************************************************************/
#include <sa2b/core.h>      /* core                                                 */

/****** Ninja ***********************************************************************/
#include <sa2b/ninja/ninja.h> /* ninja                                              */

/****** Render Fix ******************************************************************/
#include <rf_core.h>        /* core                                                 */
#include <rf_renderstate.h> /* render state                                         */

/****** Self ************************************************************************/
#include <rf_draw/rfd_cnkmdl/rfdcnk_internal.h> /* parent & siblings                */

/************************/
/*  Source              */
/************************/
/****** Static **********************************************************************/
static void
rjCnkVertexD8(const Sint32* restrict pVList, CNK_VERTEX_BUFFER* restrict pVtxBuf)
{
    const CNK_VERTEX_HEAD* p_vhead = (void*) pVList;

    const int nb_vtx = p_vhead->nbindeces;

    /** Populate vertex buffer **/

    const CNK_VERTEX_D8* p_vtx = (void*) p_vhead->d;

    CNK_VERTEX_BUFFER* p_buf = pVtxBuf;

    for (int i = 0; i < nb_vtx; ++i)
    {
        p_buf->pos = p_vtx->pos;
        p_buf->col = p_vtx->col;

        ++p_vtx;
        ++p_buf;
    }
}

static void
rjCnkVertexVN(const Sint32* restrict pVList, CNK_VERTEX_BUFFER* restrict pVtxBuf)
{
    const CNK_VERTEX_HEAD* p_vhead = (void*) pVList;

    const int nb_vtx = p_vhead->nbindeces;

    /** Populate vertex buffer **/

    const CNK_VERTEX_VN* p_vtx = (void*) p_vhead->d;

    CNK_VERTEX_BUFFER* p_buf = pVtxBuf;

    for (int i = 0; i < nb_vtx; ++i)
    {
        p_buf->pos = p_vtx->pos;
        p_buf->nrm = p_vtx->nrm;

        ++p_vtx;
        ++p_buf;
    }
}

static void
rjCnkVertexVND8(const Sint32* restrict pVList, CNK_VERTEX_BUFFER* restrict pVtxBuf)
{
    const CNK_VERTEX_HEAD* p_vhead = (void*) pVList;

    const int nb_vtx = p_vhead->nbindeces;

    /** Populate vertex buffer **/

    const CNK_VERTEX_VN_D8* p_vtx = (void*) p_vhead->d;

    CNK_VERTEX_BUFFER* p_buf = pVtxBuf;

    for (int i = 0; i < nb_vtx; ++i)
    {
        p_buf->pos = p_vtx->pos;
        p_buf->nrm = p_vtx->nrm;
        p_buf->col = p_vtx->col;

        ++p_vtx;
        ++p_buf;
    }
}

/****** Extern **********************************************************************/
int
rjCnkVListSM(const Sint32* restrict pVList, CNK_VERTEX_BUFFER* restrict njvtxbuf)
{
    /** Shadow map variant of 'CnkVList'. It's the same as the regular VList
        function, but doesn't transform the vertexes and supports fewer vertex
        types, mainly those found on LandTables. **/

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
            case NJD_CV_D8: // chunk vertex + color
            {
                _nj_cnk_vtx_attrs_ = CNKVTX_POS_COL;

                if (multi)
                    return -1;

                rjCnkVertexD8(vlist, p_vbuf);
                break;
            }
            case NJD_CV_VN: // chunk vertex + normal
            {
                _nj_cnk_vtx_attrs_ = CNKVTX_POS_NRM;

                rjCnkVertexVN(vlist, p_vbuf);
                break;
            }
            case NJD_CV_VN_D8: // chunk vertex + normal + color
            {
                _nj_cnk_vtx_attrs_ = CNKVTX_POS_NRM_COL;

                rjCnkVertexVND8(vlist, p_vbuf);
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
