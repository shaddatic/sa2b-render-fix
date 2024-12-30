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
/*  Constants           */
/************************/
/****** Ninja Vertex Max ************************************************************/
#define NJD_VERTOFF_MAX         (NJD_CV_NF_D8+1)

/************************/
/*  Source              */
/************************/
/****** Static **********************************************************************/
static void
CalcPoint(const NJS_POINT3* ps, NJS_POINT3* pd)
{
    njCalcPoint(NULL, ps, pd);
}

#if 0

static void
CalcNormal(const NJS_VECTOR* ns, NJS_VECTOR* nd, Float funitratio)
{
    /** The vector must be normalized here, or else environment maps break when
        models are scaled. They normalize them in-shader for the lighting,
        but not env maps... But, since all normals are supposed to be unit, we can
        just use the same adjustment value from previous unit calcs **/

    njCalcVector(NULL, ns, nd);

    nd->x *= funitratio;
    nd->y *= funitratio;
    nd->z *= funitratio;
}

static Float
GetUnitRatio(void)
{
    NJS_VECTOR v = { 1.f, 0.f, 0.f };

    njCalcVector(NULL, &v, &v);

    return 1.f / njSqrt( (v.x * v.x) + (v.y * v.y) + (v.z * v.z) );
}

#endif

static void
CalcNormal(const NJS_VECTOR* ns, NJS_VECTOR* nd)
{
    njCalcVector(NULL, ns, nd);
}

static void
rjCnkVertex(const Sint32* pVList, CNK_VERTEX_BUFFER* pVtxBuf)
{
    const CNK_VLIST_CV* vlist = (void*)pVList;

    const int nb_vtx = vlist->nbindeces;

    for (int i = 0; i < nb_vtx; ++i)
    {
        CalcPoint(&vlist->d[i].pos, &pVtxBuf[i].pos);
    }
}

static void
rjCnkVertexD8(const Sint32* pVList, CNK_VERTEX_BUFFER* pVtxBuf)
{
    const CNK_VLIST_D8* vlist = (void*)pVList;

    const int nb_vtx = vlist->nbindeces;

    for (int i = 0; i < nb_vtx; ++i)
    {
        CalcPoint(&vlist->d[i].pos, &pVtxBuf[i].pos);

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
        CalcPoint( &vlist->d[i].pos , &pVtxBuf[i].pos);
        CalcNormal(&vlist->d[i].norm, &pVtxBuf[i].norm);
    }
}

static void
rjCnkVertexVND8(const Sint32* pVList, CNK_VERTEX_BUFFER* pVtxBuf)
{
    const CNK_VLIST_VN_D8* vlist = (void*)pVList;

    const int nb_vtx = vlist->nbindeces;

    for (int i = 0; i < nb_vtx; ++i)
    {
        CalcPoint( &vlist->d[i].pos , &pVtxBuf[i].pos);
        CalcNormal(&vlist->d[i].norm, &pVtxBuf[i].norm);

        pVtxBuf[i].color = vlist->d[i].color;
    }
}

static void
rjCnkVertexVNNF(const Sint32* pVList, int type, CNK_VERTEX_BUFFER* pVtxBuf)
{
    const CNK_VLIST_VN_NF* vlist = (void*)pVList;

    const int nb_vtx = vlist->nbindeces;

    for (int i = 0; i < nb_vtx; ++i)
    {
        NJS_POINT3 pos;
        NJS_VECTOR norm;

        CalcPoint( &vlist->d[i].pos , &pos);
        CalcNormal(&vlist->d[i].norm, &norm);

        CNK_VERTEX_BUFFER* p_vbuf = &pVtxBuf[ vlist->d[i].idx ];

        const f32 mul = (f32)vlist->d[i].mul * (1.f/255.f);

        pos.x *= mul;
        pos.y *= mul;
        pos.z *= mul;

        norm.x *= mul;
        norm.y *= mul;
        norm.z *= mul;

        switch (type)
        {
            case 0:
            {
                p_vbuf->pos  = pos;
                p_vbuf->norm = norm;
                break;
            }
            case 2:
            case 1:
            {
                p_vbuf->pos.x += pos.x;
                p_vbuf->pos.y += pos.y;
                p_vbuf->pos.z += pos.z;

                p_vbuf->norm.x += norm.x;
                p_vbuf->norm.y += norm.y;
                p_vbuf->norm.z += norm.z;
                break;
            }
        }
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

        const CNK_VLIST_HEAD* p_vhead = (void*)vlist;

        const int type = p_vhead->headbits;

        if (type == NJD_ENDOFF)
        {
            /** NJD_ENDOFF **/
            break;
        }

        /** Get the vertex buffer offset for this vertex list. Verteces are copied
            from the 'vlist' sequentially into the vertex buffer starting from this
            offset. The vertex buffer struct def is fixed. **/
        CNK_VERTEX_BUFFER* p_vbuf = &njvtxbuf[p_vhead->indexoffset];

        switch (type)
        {
            case NJD_CV: // chunk vertex
            {
                _nj_cnk_vtx_attrs_ = CNKVTX_POS;

                /** No normals, halt drawing if 'MultiDraw' **/
                if (multi)
                    return -1;

                rjCnkVertex(vlist, p_vbuf);
                break;
            }
            case NJD_CV_D8: // chunk vertex + color
            {
                _nj_cnk_vtx_attrs_ = CNKVTX_POS_COL;

                /** No normals, halt drawing if 'MultiDraw' **/
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
            case NJD_CV_VN_NF: // chunk vertex + normal + ninja flag (weighted)
            {
                _nj_cnk_vtx_attrs_ = CNKVTX_POS_NRM_NJF;
                
                rjCnkVertexVNNF(vlist, p_vhead->chunkhead & 0x7F, p_vbuf);
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
