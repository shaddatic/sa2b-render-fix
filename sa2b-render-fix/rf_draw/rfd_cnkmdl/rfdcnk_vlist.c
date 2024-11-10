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

#define NJD_VERTOFF_MAX         (NJD_CV_NF_D8+1)

static void
CalcPoint(const NJS_POINT3* ps, NJS_POINT3* pd)
{
    njCalcPoint(NULL, ps, pd);
}

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

static void
rjCnkVertex(const Sint32* pVList, CNK_VERTEX_BUFFER* pVtxBuf)
{
    const CNK_VLIST_CV* vlist = (void*)pVList;

    const int nb_vtx = vlist->nbindeces;

    const f32 uratio = GetUnitRatio();

    for (int i = 0; i < nb_vtx; ++i)
    {
        CalcPoint(&vlist->d[i].pos , &pVtxBuf[i].pos);
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

    const f32 uratio = GetUnitRatio();

    for (int i = 0; i < nb_vtx; ++i)
    {
        CalcPoint( &vlist->d[i].pos , &pVtxBuf[i].pos);
        CalcNormal(&vlist->d[i].norm, &pVtxBuf[i].norm, uratio);
    }
}

static void
rjCnkVertexVND8(const Sint32* pVList, CNK_VERTEX_BUFFER* pVtxBuf)
{
    const CNK_VLIST_VN_D8* vlist = (void*)pVList;

    const int nb_vtx = vlist->nbindeces;

    const f32 uratio = GetUnitRatio();

    for (int i = 0; i < nb_vtx; ++i)
    {
        CalcPoint( &vlist->d[i].pos , &pVtxBuf[i].pos);
        CalcNormal(&vlist->d[i].norm, &pVtxBuf[i].norm, uratio);

        pVtxBuf[i].color = vlist->d[i].color;
    }
}

static void
rjCnkVertexVNNF(const Sint32* pVList, int type, CNK_VERTEX_BUFFER* pVtxBuf)
{
    const CNK_VLIST_VN_NF* vlist = (void*)pVList;

    const int nb_vtx = vlist->nbindeces;

    const f32 uratio = GetUnitRatio();

    for (int i = 0; i < nb_vtx; ++i)
    {
        NJS_POINT3 pos;
        NJS_VECTOR norm;

        CalcPoint( &vlist->d[i].pos , &pos);
        CalcNormal(&vlist->d[i].norm, &norm, uratio);

        CNK_VERTEX_BUFFER* p_vbuf = &pVtxBuf[ vlist->d[i].idx ];

        const f32 mul = (f32)((f64)vlist->d[i].mul * (1.0/255.0));

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

int
rjCnkVList(const Sint32* pVList, CNK_VERTEX_BUFFER* njvtxbuf)
{
    const bool multi = ( RFRS_GetCnkFuncMode() & RFRS_CNKFUNCMD_MULTIBIT );

    _nj_cnk_vtx_attrs_ = 0;

    const Sint32* vlist = pVList;

    for ( ; ; )
    {
        const int type = ((u8*)vlist)[0];

        if (type == NJD_ENDOFF)
        {
            /** NJD_ENDOFF **/
            break;
        }

        const CNK_VLIST_HEAD* pvhead = (void*)vlist;

        CNK_VERTEX_BUFFER* p_vbuf = &njvtxbuf[pvhead->indexoffset];

        switch (type)
        {
            case NJD_CV:
            {
                _nj_cnk_vtx_attrs_ |= CNKVTX_NO_NORMALS;

                if (multi)
                    return -1;

                rjCnkVertex(vlist, p_vbuf);
                break;
            }
            case NJD_CV_D8:
            {
                _nj_cnk_vtx_attrs_ |= (CNKVTX_NO_NORMALS | CNKVTX_HAS_VCOLORS);

                if (multi)
                    return -1;

                rjCnkVertexD8(vlist, p_vbuf);
                break;
            }
            case NJD_CV_VN:
            {
                rjCnkVertexVN(vlist, p_vbuf);
                break;
            }
            case NJD_CV_VN_D8:
            {
                _nj_cnk_vtx_attrs_ |= CNKVTX_HAS_VCOLORS;
                rjCnkVertexVND8(vlist, p_vbuf);
                break;
            }
            case NJD_CV_VN_NF:
            {
                rjCnkVertexVNNF(vlist, pvhead->chunkhead & 0x7F, p_vbuf);
                break;
            }
        }

        /** Next data chunk **/
        vlist += pvhead->size + 1;
    }

    return 0;
}
