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
rjCnkModVertexVNSH(const Sint32* pVList, CNK_VERTEX_BUFFER* pVtxBuf)
{
    const CNK_VLIST_VN_SH* vlist = (void*)pVList;

    const int nb_vtx = vlist->nbindeces;

    for (int i = 0; i < nb_vtx; ++i)
    {
        njCalcPoint( NULL, &vlist->d[i].pos , &pVtxBuf[i].pos);
    }
}

static void
rjCnkModVertex(const Sint32* const pVList, CNK_VERTEX_BUFFER* const pVtxBuf)
{
    const CNK_VLIST_CV* vlist = (void*)pVList;

    const int nb_vtx = vlist->nbindeces;

    for (int i = 0; i < nb_vtx; ++i)
    {
        njCalcPoint( NULL, &vlist->d[i].pos , &pVtxBuf[i].pos);
    }
}

static void
rjCnkModVertexD8(const Sint32* pVList, CNK_VERTEX_BUFFER* pVtxBuf)
{
    const CNK_VLIST_D8* vlist = (void*)pVList;

    const int nb_vtx = vlist->nbindeces;

    for (int i = 0; i < nb_vtx; ++i)
    {
        njCalcPoint(NULL, &vlist->d[i].pos, &pVtxBuf[i].pos);
    }
}

static void
rjCnkModVertexVN(const Sint32* pVList, CNK_VERTEX_BUFFER* pVtxBuf)
{
    const CNK_VLIST_VN* vlist = (void*)pVList;

    const int nb_vtx = vlist->nbindeces;

    for (int i = 0; i < nb_vtx; ++i)
    {
        njCalcPoint( NULL, &vlist->d[i].pos , &pVtxBuf[i].pos);
    }
}

static void
rjCnkModVertexVND8(const Sint32* pVList, CNK_VERTEX_BUFFER* pVtxBuf)
{
    const CNK_VLIST_VN_D8* vlist = (void*)pVList;

    const int nb_vtx = vlist->nbindeces;

    for (int i = 0; i < nb_vtx; ++i)
    {
        njCalcPoint( NULL, &vlist->d[i].pos , &pVtxBuf[i].pos);
    }
}

/****** Extern **********************************************************************/
int32_t
rjCnkModVList(const Sint32* const pVList, CNK_VERTEX_BUFFER* const njvtxbuf)
{
    const Sint32* vlist = pVList;

    int type;

    while (1)
    {
        type = ((u8*)vlist)[0];

        if (type == NJD_ENDOFF)
        {
            /** NJD_ENDOFF **/
            break;
        }

        const CNK_VLIST_HEAD* pvhead = (void*)vlist;

        CNK_VERTEX_BUFFER* p_vbuf = &njvtxbuf[pvhead->indexoffset];

        switch (type) {
        case NJD_CV_VN_SH:
            rjCnkModVertexVNSH(vlist, p_vbuf);
            break;

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
            return 1;
        }

        /** Next data chunk **/
        vlist += pvhead->size + 1;
    }

    return 0;
}
