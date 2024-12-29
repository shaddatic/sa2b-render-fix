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
rjCnkVertexD8(const Sint32* pVList, CNK_VERTEX_BUFFER* pVtxBuf)
{
    const CNK_VLIST_D8* vlist = (void*)pVList;

    const int nb_vtx = vlist->nbindeces;

    for (int i = 0; i < nb_vtx; ++i)
    {
        pVtxBuf[i].pos  = vlist->d[i].pos;

        pVtxBuf[i].color = vlist->d[i].color;
    }
}

static void
rjCnkVertexVN(const Sint32* pVList, CNK_VERTEX_BUFFER* pVtxBuf)
{
    const CNK_VLIST_VN* vlist = (void*)pVList;

    const int nb_vtx = vlist->nbindeces;

    for (int i = 0; i < nb_vtx; ++i)
    {
        pVtxBuf[i].pos  = vlist->d[i].pos;
        pVtxBuf[i].norm = vlist->d[i].norm;
    }
}

static void
rjCnkVertexVND8(const Sint32* pVList, CNK_VERTEX_BUFFER* pVtxBuf)
{
    const CNK_VLIST_VN_D8* vlist = (void*)pVList;

    const int nb_vtx = vlist->nbindeces;

    for (int i = 0; i < nb_vtx; ++i)
    {
        pVtxBuf[i].pos  = vlist->d[i].pos;
        pVtxBuf[i].norm = vlist->d[i].norm;

        pVtxBuf[i].color = vlist->d[i].color;
    }
}

/****** Extern **********************************************************************/
int
rjCnkVListSM(const Sint32* const pVList, CNK_VERTEX_BUFFER* const njvtxbuf)
{
    const bool multi = ( RFRS_GetCnkFuncMode() & RFRS_CNKFUNCMD_MULTIBIT );

    const Sint32* vlist = pVList;

    int type;

    for ( ; ; )
    {
        type = ((u8*)vlist)[0];

        if (type == NJD_ENDOFF)
        {
            /** NJD_ENDOFF **/
            break;
        }

        const CNK_VLIST_HEAD* pvhead = (void*)vlist;

        CNK_VERTEX_BUFFER* p_vbuf = &njvtxbuf[pvhead->indexoffset];

        switch (type)
        {
            case NJD_CV_D8:
            {
                _nj_cnk_vtx_attrs_ = CNKVTX_POS_COL;

                if (multi)
                    return -1;

                rjCnkVertexD8(vlist, p_vbuf);
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
        }

        /** Next data chunk **/
        vlist += pvhead->size + 1;
    }

    return 0;
}
