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
#include <rf_light.h>

/****** Self ************************************************************************/
#include <rf_draw/rfd_cnkmdl/rfdcnk_internal.h> /* parent & siblings                */

#include <samt/sonic/score.h>

/************************/
/*  Source              */
/************************/
#define INVSQR(x)               ((1.f/x) * (1.f/x))

#define SQR(x)                  ((x) * (x))

static Float
rjCnkCalcLightIntensity(int light, const NJS_POINT3* pPos, const NJS_VECTOR* pNormal)
{
    const RJS_LIGHT* p_lite = &_rj_cnk_light_[light];

    switch ( p_lite->type )
    {
        case RJD_CNK_LIGHTMD_DIR:
        {
            return njInnerProduct( pNormal, &p_lite->v ) * p_lite->inten;
        }
        case RJD_CNK_LIGHTMD_POINT: POINT:
        {
            NJS_VECTOR v =
            {
                p_lite->p.x - pPos->x,
                p_lite->p.y - pPos->y,
                p_lite->p.z - pPos->z
            };

            if ( p_lite->far != 0.f )
            {
                const Float dist = njScalor2(&v) - p_lite->near;

                Float dist_inten = 1.f + (p_lite->far * dist);

                if ( dist_inten < 0.f )
                {
                    return 0.f;
                }

                dist_inten = MIN(dist_inten, 1.f);

                njUnitVector(&v);

                return njInnerProduct( pNormal, &v ) * p_lite->inten * dist_inten;
            }
            else // no distance calcs
            {
                njUnitVector(&v);

                return njInnerProduct( pNormal, &v ) * p_lite->inten;
            }
        }
        case RJD_CNK_LIGHTMD_SPOT:
        {
            if ( p_lite->angmax == 0.f )
            {
                goto POINT;
            }

            NJS_VECTOR v =
            {
                p_lite->p.x - pPos->x,
                p_lite->p.y - pPos->y,
                p_lite->p.z - pPos->z
            };

            Float dist_inten;

            if ( p_lite->far != 0.f )
            {
                const Float dist = njScalor2(&v) - p_lite->near;

                dist_inten = 1.f + (p_lite->far * dist);

                if ( dist_inten < 0.f )
                {
                    return 0.f;
                }

                dist_inten = MIN(dist_inten, 1.f);
            }
            else // no distance calcs
            {
                dist_inten = 1.f;
            }

            njUnitVector(&v);

            Float angle = (1.f - ( ( njInnerProduct( &v, &p_lite->v ) * 0.5f ) + 0.5f )) - p_lite->angmin;

            Float angle_inten = 1.f + (angle * p_lite->angmax);

            if ( angle_inten < 0.f )
            {
                return 0.f;
            }

            angle_inten = MIN(angle_inten, 1.f);

            return njInnerProduct( pNormal, &v ) * p_lite->inten * dist_inten * angle_inten;
        }
    }

    return 0.f;
}

void
rjCnkVertexCalculateIntensity(CNK_VERTEX_BUFFER* pVertex, const NJS_POINT3* pPos, const NJS_VECTOR* pNormal)
{
    const int litesw = _rj_cnk_light_switch_;

    if ( litesw & RJD_CNK_LIGHTSW_1 )
    {
        pVertex->inten[0] = rjCnkCalcLightIntensity(0, pPos, pNormal);
    }

    if ( litesw & RJD_CNK_LIGHTSW_2 )
    {
        pVertex->inten[1] = rjCnkCalcLightIntensity(1, pPos, pNormal);
    }

    if ( litesw & RJD_CNK_LIGHTSW_3 )
    {
        pVertex->inten[2] = rjCnkCalcLightIntensity(2, pPos, pNormal);
    }

    if ( litesw & RJD_CNK_LIGHTSW_4 )
    {
        pVertex->inten[3] = rjCnkCalcLightIntensity(3, pPos, pNormal);
    }

    if ( litesw & RJD_CNK_LIGHTSW_5 )
    {
        pVertex->inten[4] = rjCnkCalcLightIntensity(4, pPos, pNormal);
    }

    if ( litesw & RJD_CNK_LIGHTSW_6 )
    {
        pVertex->inten[5] = rjCnkCalcLightIntensity(5, pPos, pNormal);
    }
}

/****** Vertex **********************************************************************/
void
rjCnkCalcVlistPosition(const NJS_POINT3* pIn, NJS_POINT3* pOut)
{
    njCalcPoint(NULL, pIn, pOut);

// wobble
#if 0
    const f32 time = ((f32)ulGlobalTimer / 50.f);

    pOut->y += sinf((pOut->x * 1.f) + time);
#endif
}

void
rjCnkCalcVlistNormal(const NJS_VECTOR* pIn, NJS_VECTOR* pOut)
{
    njCalcVector(NULL, pIn, pOut);
}

void
rjCnkCalcVlistColor(const NJS_ARGB* pIn, NJS_ARGB* pOut)
{
    *pOut = *pIn;
}

void
rjCnkCalcVlistSpecular(const NJS_ARGB* pIn, NJS_ARGB* pOut)
{
    *pOut = *pIn;
}

void
rjCnkCalcVlistNormalUnit(const NJS_VECTOR* pIn, NJS_VECTOR* pOut)
{
    njCalcVector(NULL, pIn, pOut);

    njUnitVector(pOut);
}

/****** Get Attribute ***************************************************************/
static inline void
rjCnkGetVlistVNX(const CNK_VNX* pIn, NJS_VECTOR* pOut)
{
    pOut->x = CNK_GET_VNX(pIn->x);
    pOut->y = CNK_GET_VNX(pIn->y);
    pOut->z = CNK_GET_VNX(pIn->z);
}

static inline void
rjCnkGetVlistD8(const NJS_BGRA* pIn, NJS_ARGB* pOut)
{
    pOut->a = (f32)pIn->a * (1.f/255.f);
    pOut->r = (f32)pIn->r * (1.f/255.f);
    pOut->g = (f32)pIn->g * (1.f/255.f);
    pOut->b = (f32)pIn->b * (1.f/255.f);
}

static inline void
rjCnkGetVlistVND8(const NJS_BGRA* pIn, NJS_ARGB* pOut)
{
    pOut->a = (f32)pIn->a * (1.f/128.f);
    pOut->r = (f32)pIn->r * (1.f/128.f);
    pOut->g = (f32)pIn->g * (1.f/128.f);
    pOut->b = (f32)pIn->b * (1.f/128.f);
}

static inline void
rjCnkGetVlistD5(const CNK_565* pIn, NJS_ARGB* pOut)
{
    pOut->a = 1.f;
    pOut->r = (f32)pIn->r * (1.f/31.f);
    pOut->g = (f32)pIn->g * (1.f/63.f);
    pOut->b = (f32)pIn->b * (1.f/31.f);
}

static inline void
rjCnkGetVlistD4(const CNK_4444* pIn, NJS_ARGB* pOut)
{
    pOut->a = (f32)pIn->a * (1.f/15.f);
    pOut->r = (f32)pIn->r * (1.f/15.f);
    pOut->g = (f32)pIn->g * (1.f/15.f);
    pOut->b = (f32)pIn->b * (1.f/15.f);
}

static inline void
rjCnkGetVlistDI(const Uint16* pIn, NJS_ARGB* pOut)
{
    const f32 f = (f32)(*pIn) * (1.f/65535.f);

    pOut->a = 1.f;
    pOut->r = f;
    pOut->g = f;
    pOut->b = f;
}

static inline void
rjCnkGetVlistS5(const CNK_565* pIn, NJS_ARGB* pOut)
{
    pOut->a = 0.f;
    pOut->r = (f32)pIn->r * (1.f/31.f);
    pOut->g = (f32)pIn->g * (1.f/63.f);
    pOut->b = (f32)pIn->b * (1.f/31.f);
}

static inline void
rjCnkGetVlistS8(const NJS_BGRA* pIn, NJS_ARGB* pOut)
{
    pOut->a = 0.f;
    pOut->r = (f32)pIn->r * (1.f/255.f);
    pOut->g = (f32)pIn->g * (1.f/255.f);
    pOut->b = (f32)pIn->b * (1.f/255.f);
}

static inline void
rjCnkGetVlistSI(const Uint16* pIn, NJS_ARGB* pOut)
{
    const f32 f = (f32)(*pIn) * (1.f/65535.f);

    pOut->a = 0.f;
    pOut->r = f;
    pOut->g = f;
    pOut->b = f;
}

/****** Static **********************************************************************/
static void
rjCnkVertexSH(const Sint32* pVList, CNK_VERTEX_BUFFER* pVtxBuf)
{
    RJF_CNK_VLIST_POS* posfunc = _rj_cnk_vlistfunc_pos_;

    const CNK_VERTEX_HEAD* p_vhead = (void*) pVList;

    const int nb_vtx = p_vhead->nbindeces;

    /** Populate vertex buffer **/

    const CNK_VERTEX_SH* p_vtx = (void*) p_vhead->d;

    CNK_VERTEX_BUFFER* p_buf = pVtxBuf;

    for (int i = 0; i < nb_vtx; ++i)
    {
        posfunc(&p_vtx->pos, &p_buf->pos);

        ++p_vtx;
        ++p_buf;
    }
}

static void
rjCnkVertexVNSH(const Sint32* pVList, CNK_VERTEX_BUFFER* pVtxBuf)
{
    RJF_CNK_VLIST_POS* posfunc = _rj_cnk_vlistfunc_pos_;
    RJF_CNK_VLIST_NRM* nrmfunc = _rj_cnk_vlistfunc_nrm_;

    const CNK_VERTEX_HEAD* p_vhead = (void*) pVList;

    const int nb_vtx = p_vhead->nbindeces;

    /** Populate vertex buffer **/

    const CNK_VERTEX_VN_SH* p_vtx = (void*) p_vhead->d;

    CNK_VERTEX_BUFFER* p_buf = pVtxBuf;

    for (int i = 0; i < nb_vtx; ++i)
    {
        posfunc(&p_vtx->pos, &p_buf->pos);
        nrmfunc(&p_vtx->nrm, &p_buf->nrm);

        rjCnkVertexCalculateIntensity(p_buf, &p_buf->pos, &p_buf->nrm);

        ++p_vtx;
        ++p_buf;
    }
}

static void
rjCnkVertex(const Sint32* pVList, CNK_VERTEX_BUFFER* pVtxBuf)
{
    RJF_CNK_VLIST_POS* posfunc = _rj_cnk_vlistfunc_pos_;

    const CNK_VERTEX_HEAD* p_vhead = (void*) pVList;

    const int nb_vtx = p_vhead->nbindeces;

    /** Populate vertex buffer **/

    const CNK_VERTEX* p_vtx = (void*) p_vhead->d;

    CNK_VERTEX_BUFFER* p_buf = pVtxBuf;

    for (int i = 0; i < nb_vtx; ++i)
    {
        posfunc(&p_vtx->pos, &p_buf->pos);

        ++p_vtx;
        ++p_buf;
    }
}

static void
rjCnkVertexD8(const CNK_VERTEX_HEAD* vhead, CNK_VERTEX_BUFFER* vbuf)
{
    RJF_CNK_VLIST_POS* const posfunc = _rj_cnk_vlistfunc_pos_;
    RJF_CNK_VLIST_COL* const colfunc = _rj_cnk_vlistfunc_col_;

    const int nb_vtx = vhead->nbindeces;

    /** Populate vertex buffer **/

    const CNK_VERTEX_D8* p_vtx = (void*) vhead->d;

    CNK_VERTEX_BUFFER* p_buf = vbuf;

    for (int i = 0; i < nb_vtx; ++i)
    {
        NJS_ARGB argb;

        posfunc(&p_vtx->pos, &p_buf->pos);

        rjCnkGetVlistD8(&p_vtx->col, &argb);

        colfunc(&argb, &p_buf->col);

        ++p_vtx;
        ++p_buf;
    }
}

static void
rjCnkVertexVN(const Sint32* pVList, CNK_VERTEX_BUFFER* pVtxBuf)
{
    RJF_CNK_VLIST_POS* posfunc = _rj_cnk_vlistfunc_pos_;
    RJF_CNK_VLIST_NRM* nrmfunc = _rj_cnk_vlistfunc_nrm_;

    const CNK_VERTEX_HEAD* p_vhead = (void*) pVList;

    const int nb_vtx = p_vhead->nbindeces;

    /** Populate vertex buffer **/

    const CNK_VERTEX_VN* p_vtx = (void*) p_vhead->d;

    CNK_VERTEX_BUFFER* p_buf = pVtxBuf;

    for (int i = 0; i < nb_vtx; ++i)
    {
        posfunc(&p_vtx->pos, &p_buf->pos);
        nrmfunc(&p_vtx->nrm, &p_buf->nrm);

        rjCnkVertexCalculateIntensity(p_buf, &p_buf->pos, &p_buf->nrm);

        ++p_vtx;
        ++p_buf;
    }
}

static void
rjCnkVertexUF(const Sint32* pVList, CNK_VERTEX_BUFFER* pVtxBuf)
{
    RJF_CNK_VLIST_POS* posfunc = _rj_cnk_vlistfunc_pos_;

    const CNK_VERTEX_HEAD* p_vhead = (void*) pVList;

    const int nb_vtx = p_vhead->nbindeces;

    /** Populate vertex buffer **/

    const CNK_VERTEX_UF* p_vtx = (void*) p_vhead->d;

    CNK_VERTEX_BUFFER* p_buf = pVtxBuf;

    for (int i = 0; i < nb_vtx; ++i)
    {
        posfunc(&p_vtx->pos, &p_buf->pos);

        ++p_vtx;
        ++p_buf;
    }
}

static void
rjCnkVertexVND8(const Sint32* pVList, CNK_VERTEX_BUFFER* pVtxBuf)
{
    RJF_CNK_VLIST_POS* const posfunc = _rj_cnk_vlistfunc_pos_;
    RJF_CNK_VLIST_NRM* const nrmfunc = _rj_cnk_vlistfunc_nrm_;
    RJF_CNK_VLIST_COL* const colfunc = _rj_cnk_vlistfunc_col_;

    const CNK_VERTEX_HEAD* p_vhead = (void*) pVList;

    const int nb_vtx = p_vhead->nbindeces;

    /** Populate vertex buffer **/

    const CNK_VERTEX_VN_D8* p_vtx = (void*) p_vhead->d;

    CNK_VERTEX_BUFFER* p_buf = pVtxBuf;

    for (int i = 0; i < nb_vtx; ++i)
    {
        NJS_ARGB argb;

        posfunc(&p_vtx->pos, &p_buf->pos);
        nrmfunc(&p_vtx->nrm, &p_buf->nrm);

        rjCnkGetVlistVND8(&p_vtx->col, &argb);

        colfunc(&argb, &p_buf->col);

        rjCnkVertexCalculateIntensity(p_buf, &p_buf->pos, &p_buf->nrm);

        ++p_vtx;
        ++p_buf;
    }
}

static void
rjCnkVertexD8S8(const Sint32* pVList, CNK_VERTEX_BUFFER* pVtxBuf)
{
    RJF_CNK_VLIST_POS* posfunc = _rj_cnk_vlistfunc_pos_;
    RJF_CNK_VLIST_COL* colfunc = _rj_cnk_vlistfunc_col_;
    RJF_CNK_VLIST_SPC* spcfunc = _rj_cnk_vlistfunc_spc_;

    const CNK_VERTEX_HEAD* p_vhead = (void*) pVList;

    const int nb_vtx = p_vhead->nbindeces;

    /** Populate vertex buffer **/

    const CNK_VERTEX_D8_S8* p_vtx = (void*) p_vhead->d;

    CNK_VERTEX_BUFFER* p_buf = pVtxBuf;

    for (int i = 0; i < nb_vtx; ++i)
    {
        NJS_ARGB argb;

        posfunc(&p_vtx->pos, &p_buf->pos);

        rjCnkGetVlistD8(&p_vtx->col, &argb);

        colfunc(&argb, &p_buf->col);

        rjCnkGetVlistS8(&p_vtx->spc, &argb);

        spcfunc(&argb, &p_buf->spc);

        ++p_vtx;
        ++p_buf;
    }
}

static void
rjCnkVertexVNX(const Sint32* pVList, CNK_VERTEX_BUFFER* pVtxBuf)
{
    RJF_CNK_VLIST_POS* posfunc = _rj_cnk_vlistfunc_pos_;
    RJF_CNK_VLIST_NRM* nrmfunc = _rj_cnk_vlistfunc_nrm_;

    const CNK_VERTEX_HEAD* p_vhead = (void*) pVList;

    const int nb_vtx = p_vhead->nbindeces;

    /** Populate vertex buffer **/

    const CNK_VERTEX_VNX* p_vtx = (void*) p_vhead->d;

    CNK_VERTEX_BUFFER* p_buf = pVtxBuf;

    for (int i = 0; i < nb_vtx; ++i)
    {
        const NJS_VECTOR vnx_nrm =
        {
            .x = CNK_GET_VNX(p_vtx->nrm.x),
            .y = CNK_GET_VNX(p_vtx->nrm.y),
            .z = CNK_GET_VNX(p_vtx->nrm.z),
        };

        posfunc(&p_vtx->pos, &p_buf->pos);
        nrmfunc(&vnx_nrm   , &p_buf->nrm);

        rjCnkVertexCalculateIntensity(p_buf, &p_buf->pos, &p_buf->nrm);

        ++p_vtx;
        ++p_buf;
    }
}

static void
rjCnkVertexVNXD8(const Sint32* pVList, CNK_VERTEX_BUFFER* vbuf)
{
    RJF_CNK_VLIST_POS* posfunc = _rj_cnk_vlistfunc_pos_;
    RJF_CNK_VLIST_NRM* nrmfunc = _rj_cnk_vlistfunc_nrm_;
    RJF_CNK_VLIST_COL* colfunc = _rj_cnk_vlistfunc_col_;

    const CNK_VERTEX_HEAD* p_vhead = (void*) pVList;

    const int nb_vtx = p_vhead->nbindeces;

    /** Populate vertex buffer **/

    const CNK_VERTEX_VNX_D8* p_vtx = (void*) p_vhead->d;

    CNK_VERTEX_BUFFER* p_buf = vbuf;

    for (int i = 0; i < nb_vtx; ++i)
    {
        NJS_VECTOR vect;
        NJS_ARGB   argb;

        posfunc(&p_vtx->pos, &p_buf->pos);

        rjCnkGetVlistVNX(&p_vtx->nrm, &vect);

        nrmfunc(&vect, &p_buf->nrm);

        rjCnkGetVlistVND8(&p_vtx->col, &argb);

        colfunc(&argb, &p_buf->col);

        rjCnkVertexCalculateIntensity(p_buf, &p_buf->pos, &p_buf->nrm);

        ++p_vtx;
        ++p_buf;
    }
}

static void
rjCnkVertexVNXUF(const Sint32* pVList, CNK_VERTEX_BUFFER* pVtxBuf)
{
    RJF_CNK_VLIST_POS* posfunc = _rj_cnk_vlistfunc_pos_;
    RJF_CNK_VLIST_NRM* nrmfunc = _rj_cnk_vlistfunc_nrm_;

    const CNK_VERTEX_HEAD* p_vhead = (void*) pVList;

    const int nb_vtx = p_vhead->nbindeces;

    /** Populate vertex buffer **/

    const CNK_VERTEX_VNX_UF* p_vtx = (void*) p_vhead->d;

    CNK_VERTEX_BUFFER* p_buf = pVtxBuf;

    for (int i = 0; i < nb_vtx; ++i)
    {
        NJS_VECTOR vect;

        posfunc(&p_vtx->pos, &p_buf->pos);

        rjCnkGetVlistVNX(&p_vtx->nrm, &vect);

        nrmfunc(&vect, &p_buf->nrm);

        rjCnkVertexCalculateIntensity(p_buf, &p_buf->pos, &p_buf->nrm);

        ++p_vtx;
        ++p_buf;
    }
}

static void
rjCnkVertexVNUF(const Sint32* pVList, CNK_VERTEX_BUFFER* pVtxBuf)
{
    RJF_CNK_VLIST_POS* posfunc = _rj_cnk_vlistfunc_pos_;
    RJF_CNK_VLIST_NRM* nrmfunc = _rj_cnk_vlistfunc_nrm_;

    const CNK_VERTEX_HEAD* p_vhead = (void*) pVList;

    const int nb_vtx = p_vhead->nbindeces;

    /** Populate vertex buffer **/

    const CNK_VERTEX_VN_UF* p_vtx = (void*) p_vhead->d;

    CNK_VERTEX_BUFFER* p_buf = pVtxBuf;

    for (int i = 0; i < nb_vtx; ++i)
    {
        posfunc(&p_vtx->pos, &p_buf->pos);
        nrmfunc(&p_vtx->nrm, &p_buf->nrm);

        rjCnkVertexCalculateIntensity(p_buf, &p_buf->pos, &p_buf->nrm);

        ++p_vtx;
        ++p_buf;
    }
}

static void
rjCnkVertexNF(const Sint32* pVList, CNK_VERTEX_BUFFER* pVtxBuf)
{
    RJF_CNK_VLIST_POS* posfunc = _rj_cnk_vlistfunc_pos_;

    const CNK_VERTEX_HEAD* p_vhead = (void*) pVList;

    const int nb_vtx = p_vhead->nbindeces;

    const int wstat = p_vhead->wstat;

    /** Populate vertex buffer **/

    const CNK_VERTEX_NF* p_vtx = (void*) p_vhead->d;

    for (int i = 0; i < nb_vtx; ++i)
    {
        NJS_POINT3 pos;

        posfunc(&p_vtx->pos, &pos);

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
    RJF_CNK_VLIST_POS* posfunc = _rj_cnk_vlistfunc_pos_;
    RJF_CNK_VLIST_NRM* nrmfunc = _rj_cnk_vlistfunc_nrm_;

    const CNK_VERTEX_HEAD* p_vhead = (void*) pVList;

    const int nb_vtx = p_vhead->nbindeces;

    const int wstat = p_vhead->wstat;

    /** Populate vertex buffer **/

    const CNK_VERTEX_VN_NF* p_vtx = (void*) p_vhead->d;

    for (int i = 0; i < nb_vtx; ++i)
    {
        NJS_POINT3 pos;
        NJS_VECTOR nrm;

        posfunc(&p_vtx->pos, &pos);
        nrmfunc(&p_vtx->nrm, &nrm);

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
            {
                p_vbuf->pos.x += pos.x;
                p_vbuf->pos.y += pos.y;
                p_vbuf->pos.z += pos.z;

                p_vbuf->nrm.x += nrm.x;
                p_vbuf->nrm.y += nrm.y;
                p_vbuf->nrm.z += nrm.z;
                break;
            }
            case CNK_WEIGHT_END:
            {
                p_vbuf->pos.x += pos.x;
                p_vbuf->pos.y += pos.y;
                p_vbuf->pos.z += pos.z;

                p_vbuf->nrm.x += nrm.x;
                p_vbuf->nrm.y += nrm.y;
                p_vbuf->nrm.z += nrm.z;

                rjCnkVertexCalculateIntensity(p_vbuf, &p_vbuf->pos, &p_vbuf->nrm);
                break;
            }
        }

        ++p_vtx;
    }
}

static void
rjCnkVertexNFD8(const Sint32* pVList, CNK_VERTEX_BUFFER* pVtxBuf)
{
    RJF_CNK_VLIST_POS* posfunc = _rj_cnk_vlistfunc_pos_;
    RJF_CNK_VLIST_COL* colfunc = _rj_cnk_vlistfunc_col_;

    const CNK_VERTEX_HEAD* p_vhead = (void*) pVList;

    const int nb_vtx = p_vhead->nbindeces;

    const int wstat = p_vhead->wstat;

    /** Populate vertex buffer **/

    const CNK_VERTEX_NF_D8* p_vtx = (void*) p_vhead->d;

    for (int i = 0; i < nb_vtx; ++i)
    {
        NJS_POINT3 pos;

        posfunc(&p_vtx->pos, &pos );

        CNK_VERTEX_BUFFER* p_buf = &pVtxBuf[ p_vtx->i ];

        const f32 mul = CNK_GET_WEIGHT(p_vtx->w);

        pos.x *= mul;
        pos.y *= mul;
        pos.z *= mul;

        switch (wstat)
        {
            case CNK_WEIGHT_START:
            {
                p_buf->pos = pos;
                break;
            }
            case CNK_WEIGHT_MIDDLE:
            {
                p_buf->pos.x += pos.x;
                p_buf->pos.y += pos.y;
                p_buf->pos.z += pos.z;
                break;
            }
            case CNK_WEIGHT_END:
            {
                NJS_ARGB argb;

                p_buf->pos.x += pos.x;
                p_buf->pos.y += pos.y;
                p_buf->pos.z += pos.z;

                rjCnkGetVlistD8(&p_vtx->col, &argb);

                colfunc(&argb, &p_buf->col); // read color only for end verteces
                break;
            }
        }

        ++p_vtx;
    }
}

/****** Extern **********************************************************************/
int
rjCnkVList(const Sint32* restrict pVList, CNK_VERTEX_BUFFER* restrict vbuf)
{
    const bool multi = ( RFRS_GetCnkFuncMode() & RFRS_CNKFUNCMD_MULTIBIT );

    const Sint32* vlist = pVList;

    for ( ; ; )
    {
        /** It is possible for models to contain more than 1 vertex list, but it's
            incredibly unlikely and I don't think it's even used in SA2. **/

        const int type = CNK_GET_OFFTYPE(vlist);

        if ( type == NJD_ENDOFF )
        {
            /** NJD_ENDOFF **/
            break;
        }

        bool nf = false;

        const CNK_VERTEX_HEAD* vhead = (void*)vlist;

        /** Get the vertex buffer offset for this vertex list. Verteces are copied
            from the 'vlist' sequentially into the vertex buffer starting from this
            offset. The vertex buffer struct def is fixed. **/
        CNK_VERTEX_BUFFER* p_buf = &vbuf[ vhead->indexoffset ];

        switch ( CVSW(type) )
        {
            case CVSW( NJD_CV_SH ):
            {
                _rj_cnk_vertex_attr_ = RJD_CVT_POS;

                /** No normals, halt drawing if 'MultiDraw' **/
                if ( multi )
                {
                    return -1;
                }

                rjCnkVertexSH(vlist, p_buf);
                break;
            }
            case CVSW( NJD_CV_VN_SH ):
            {
                _rj_cnk_vertex_attr_ = RJD_CVT_POS_NRM;

                /** No normals, halt drawing if 'MultiDraw' **/
                if ( multi )
                {
                    return -1;
                }

                rjCnkVertexVNSH(vlist, vbuf);
                break;
            }
            case CVSW( NJD_CV ):
            {
                _rj_cnk_vertex_attr_ = RJD_CVT_POS;

                /** No normals, halt drawing if 'MultiDraw' **/
                if ( multi )
                {
                    return -1;
                }

                rjCnkVertex(vlist, p_buf);
                break;
            }
            case CVSW( NJD_CV_D8 ):
            {
                _rj_cnk_vertex_attr_ = RJD_CVT_POS_COL;

                /** No normals, halt drawing if 'MultiDraw' **/
                if ( multi )
                {
                    return -1;
                }

                rjCnkVertexD8(vhead, p_buf);
                break;
            }
            case CVSW( NJD_CV_UF ):
            {
                _rj_cnk_vertex_attr_ = RJD_CVT_POS;

                /** No normals, halt drawing if 'MultiDraw' **/
                if ( multi )
                {
                    return -1;
                }

                rjCnkVertexUF(vlist, p_buf);
                break;
            }
            case CVSW( NJD_CV_NF ):
            {
                _rj_cnk_vertex_attr_ = RJD_CVT_POS;

                /** No normals, halt drawing if 'MultiDraw' **/
                if ( multi )
                {
                    return -1;
                }

                nf = true;

                rjCnkVertexNF(vlist, p_buf);
                break;
            }
            case CVSW( NJD_CV_VN ):
            {
                _rj_cnk_vertex_attr_ = RJD_CVT_POS_NRM;

                rjCnkVertexVN(vlist, p_buf);
                break;
            }
            case CVSW( NJD_CV_VN_D8 ):
            {
                _rj_cnk_vertex_attr_ = RJD_CVT_POS_NRM_COL;

                rjCnkVertexVND8(vlist, p_buf);
                break;
            }
            case CVSW( NJD_CV_VN_UF ):
            {
                _rj_cnk_vertex_attr_ = RJD_CVT_POS_NRM;

                rjCnkVertexVNUF(vlist, p_buf);
                break;
            }
            case CVSW( NJD_CV_VN_NF ):
            {
                _rj_cnk_vertex_attr_ = RJD_CVT_POS_NRM;

                nf = true;
                
                rjCnkVertexVNNF(vlist, p_buf);
                break;
            }
            case CVSW( NJD_CV_VNX ):
            {
                _rj_cnk_vertex_attr_ = RJD_CVT_POS_NRM;

                rjCnkVertexVNX(vlist, p_buf);
                break;
            }
            case CVSW( NJD_CV_VNX_D8 ):
            {
                _rj_cnk_vertex_attr_ = RJD_CVT_POS_NRM_COL;

                rjCnkVertexVNXD8(vlist, p_buf);
                break;
            }
            case CVSW( NJD_CV_VNX_UF ):
            {
                _rj_cnk_vertex_attr_ = RJD_CVT_POS_NRM;

                rjCnkVertexVNXUF(vlist, p_buf);
                break;
            }
            case CVSW( NJD_CV_D8_S8 ):
            {
                _rj_cnk_vertex_attr_ = RJD_CVT_POS_COL_SPC;

                /** No normals, halt drawing if 'MultiDraw' **/
                if ( multi )
                {
                    return -1;
                }

                rjCnkVertexD8S8(vlist, p_buf);
                break;
            }
            case CVSW( NJD_CV_NF_D8 ):
            {
                _rj_cnk_vertex_attr_ = RJD_CVT_POS_COL;

                /** No normals, halt drawing if 'MultiDraw' **/
                if ( multi )
                {
                    return -1;
                }

                nf = true;

                rjCnkVertexNFD8(vlist, p_buf);
                break;
            }
            default:
            {
                /** Unhandled vertex type, halt draw. **/
                return -1;
            }
        }

        /** Calculate depth queue **/

        if ( nf )
        {
            rjCnkCalculateDepthQueueNF(vhead, p_buf);
        }
        else
        {
            rjCnkCalculateDepthQueue(vhead, p_buf);
        }

        /** Next data chunk **/
        vlist += vhead->size + 1;
    }

    return 0;
}
