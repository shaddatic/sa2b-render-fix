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
rjCnkModVertex(const Sint32* const pVList, CNK_VERTEX_BUFFER* const pVtxBuf)
{
    const CNK_VLIST_CV* vlist = (void*)pVList;

    const int nb_vtx = vlist->nbindeces;

    for (int i = 0; i < nb_vtx; ++i)
    {
        njCalcPoint(NULL, &vlist->d[i].pos , &pVtxBuf[i].pos);
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
        njCalcPoint(NULL, &vlist->d[i].pos , &pVtxBuf[i].pos);
    }
}

static void
rjCnkModVertexVND8(const Sint32* pVList, CNK_VERTEX_BUFFER* pVtxBuf)
{
    const CNK_VLIST_VN_D8* vlist = (void*)pVList;

    const int nb_vtx = vlist->nbindeces;

    for (int i = 0; i < nb_vtx; ++i)
    {
        njCalcPoint(NULL, &vlist->d[i].pos , &pVtxBuf[i].pos);
    }
}

static void
rjCnkModVertexVNNF(const Sint32* pVList, int type, CNK_VERTEX_BUFFER* pVtxBuf)
{
    const CNK_VLIST_VN_NF* vlist = (void*)pVList;

    const int nb_vtx = vlist->nbindeces;

    for (int i = 0; i < nb_vtx; ++i)
    {
        NJS_POINT3 pos;

        njCalcPoint(NULL, &vlist->d[i].pos , &pos);

        CNK_VERTEX_BUFFER* p_vbuf = &pVtxBuf[ vlist->d[i].idx ];

        const f32 mul = (f32)((f64)vlist->d[i].mul * (1.0/255.0));

        pos.x *= mul;
        pos.y *= mul;
        pos.z *= mul;

        switch (type)
        {
            case 0:
            {
                p_vbuf->pos  = pos;
                break;
            }
            case 2:
            case 1:
            {
                p_vbuf->pos.x += pos.x;
                p_vbuf->pos.y += pos.y;
                p_vbuf->pos.z += pos.z;
                break;
            }
        }
    }
}

/****** Extern **********************************************************************/
int32_t
rjCnkModVList(const Sint32* const pVList, CNK_VERTEX_BUFFER* const njvtxbuf)
{
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
            rjCnkModVertexVNNF(vlist, pvhead->chunkhead & 0x7F, p_vbuf);
            break;
        }

        /** Next data chunk **/
        vlist += pvhead->size + 1;
    }

    return 0;
}
