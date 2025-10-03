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

/************************/
/*  Macro               */
/************************/
/****** Sqrt ************************************************************************/
#define INVSQR(x)               ((1.f/x) * (1.f/x))
#define SQR(x)                  ((x) * (x))

/************************/
/*  Source              */
/************************/
/****** Lights **********************************************************************/
static Float
rjCnkCalcLightIntensity(int light, const RJS_VERTEX_BUF* restrict vbuf)
{
    const RJS_LIGHT* p_lite = &_rj_cnk_light_[light];

    switch ( p_lite->type )
    {
        case RJD_CNK_LIGHTMD_DIR:
        {
            return njInnerProduct( &vbuf->nrm, &p_lite->v ) * p_lite->inten;
        }
        case RJD_CNK_LIGHTMD_POINT: POINT:
        {
            NJS_VECTOR v =
            {
                p_lite->p.x - vbuf->pos.x,
                p_lite->p.y - vbuf->pos.y,
                p_lite->p.z - vbuf->pos.z
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

                return njInnerProduct( &vbuf->nrm, &v ) * p_lite->inten * dist_inten;
            }
            else // no distance calcs
            {
                njUnitVector(&v);

                return njInnerProduct( &vbuf->nrm, &v ) * p_lite->inten;
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
                p_lite->p.x - vbuf->pos.x,
                p_lite->p.y - vbuf->pos.y,
                p_lite->p.z - vbuf->pos.z
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

            return njInnerProduct( &vbuf->nrm, &v ) * p_lite->inten * dist_inten * angle_inten;
        }
    }

    return 0.f;
}

void
rjCnkVertexCalculateIntensity(RJS_VERTEX_BUF* restrict vbuf)
{
    const int litesw = _rj_cnk_light_switch_;

    if ( litesw & RJD_CNK_LIGHTSW_1 )
    {
        vbuf->inten[0] = rjCnkCalcLightIntensity(0, vbuf);
    }

    if ( litesw & RJD_CNK_LIGHTSW_2 )
    {
        vbuf->inten[1] = rjCnkCalcLightIntensity(1, vbuf);
    }

    if ( litesw & RJD_CNK_LIGHTSW_3 )
    {
        vbuf->inten[2] = rjCnkCalcLightIntensity(2, vbuf);
    }

    if ( litesw & RJD_CNK_LIGHTSW_4 )
    {
        vbuf->inten[3] = rjCnkCalcLightIntensity(3, vbuf);
    }

    if ( litesw & RJD_CNK_LIGHTSW_5 )
    {
        vbuf->inten[4] = rjCnkCalcLightIntensity(4, vbuf);
    }

    if ( litesw & RJD_CNK_LIGHTSW_6 )
    {
        vbuf->inten[5] = rjCnkCalcLightIntensity(5, vbuf);
    }
}

/****** Vertex **********************************************************************/
void
rjCnkCalcVlistPosition(NJS_POINT3* dst, const NJS_POINT3* src)
{
    njCalcPoint(NULL, src, dst);
}

void
rjCnkCalcVlistNormal(NJS_VECTOR* dst, const NJS_VECTOR* src)
{
    njCalcVector(NULL, src, dst);
}

void
rjCnkCalcVlistColor(NJS_ARGB* dst, const NJS_ARGB* src)
{
    *dst = *src;
}

void
rjCnkCalcVlistSpecular(NJS_ARGB* dst, const NJS_ARGB* src)
{
    *dst = *src;
}

void
rjCnkCalcVlistNormalUnit(NJS_VECTOR* dst, const NJS_VECTOR* src)
{
    njCalcVector(NULL, src, dst);

    njUnitVector(dst);
}

/************************************************************************************/
/*
*   Get Attribute
*/
/****** VN32 ************************************************************************/
static inline void
rjCnkGetVlistVNX(NJS_VECTOR* dst, const CNK_VNX* src)
{
    dst->x = CNK_GET_VNX(src->x);
    dst->y = CNK_GET_VNX(src->y);
    dst->z = CNK_GET_VNX(src->z);
}

/****** Diffuse Color ***************************************************************/
static inline void
rjCnkGetVlistD8(NJS_ARGB* dst, const NJS_BGRA* src)
{
    dst->a = (f32)src->a * (1.f/255.f);
    dst->r = (f32)src->r * (1.f/255.f);
    dst->g = (f32)src->g * (1.f/255.f);
    dst->b = (f32)src->b * (1.f/255.f);
}

static inline void
rjCnkGetVlistVND8(NJS_ARGB* dst, const NJS_BGRA* src)
{
    dst->a = (f32)src->a * (1.f/128.f);
    dst->r = (f32)src->r * (1.f/128.f);
    dst->g = (f32)src->g * (1.f/128.f);
    dst->b = (f32)src->b * (1.f/128.f);
}

static inline void
rjCnkGetVlistD5(NJS_ARGB* dst, const CNK_565* src)
{
    dst->a = 1.f;
    dst->r = (f32)src->r * (1.f/31.f);
    dst->g = (f32)src->g * (1.f/63.f);
    dst->b = (f32)src->b * (1.f/31.f);
}

static inline void
rjCnkGetVlistD4(NJS_ARGB* dst, const CNK_4444* src)
{
    dst->a = (f32)src->a * (1.f/15.f);
    dst->r = (f32)src->r * (1.f/15.f);
    dst->g = (f32)src->g * (1.f/15.f);
    dst->b = (f32)src->b * (1.f/15.f);
}

static inline void
rjCnkGetVlistDI(NJS_ARGB* dst, const Uint16* src)
{
    const f32 f = (f32)(*src) * (1.f/65535.f);

    dst->a = 1.f;
    dst->r = f;
    dst->g = f;
    dst->b = f;
}

/****** Specular Color **************************************************************/
static inline void
rjCnkGetVlistS5(NJS_ARGB* dst, const CNK_565* src)
{
    dst->a = 0.f;
    dst->r = (f32)src->r * (1.f/31.f);
    dst->g = (f32)src->g * (1.f/63.f);
    dst->b = (f32)src->b * (1.f/31.f);
}

static inline void
rjCnkGetVlistS8(NJS_ARGB* dst, const NJS_BGRA* src)
{
    dst->a = 0.f;
    dst->r = (f32)src->r * (1.f/255.f);
    dst->g = (f32)src->g * (1.f/255.f);
    dst->b = (f32)src->b * (1.f/255.f);
}

static inline void
rjCnkGetVlistSI(NJS_ARGB* dst, const Uint16* src)
{
    const f32 f = (f32)(*src) * (1.f/65535.f);

    dst->a = 0.f;
    dst->r = f;
    dst->g = f;
    dst->b = f;
}

/************************************************************************************/
/*
*   Calculate Vertex Chunk
*/
/****** Static **********************************************************************/
static void
rjCnkVertexSH(const CNK_VERTEX_HEAD* restrict vhead, RJS_VERTEX_BUF* restrict vbuf)
{
    /** Get function constants **/
    RJF_CNK_VLIST_POS* const fn_pfunc = _rj_cnk_vlist_pfunc_;

    /** Read vertex header **/
    const int           nb_vertex = vhead->nbindeces;
    const CNK_VERTEX_SH* p_vertex = (void*) vhead->d;

    /** Populate vertex buffer **/
    RJS_VERTEX_BUF* restrict p_vbuf = vbuf;

    for (int i = 0; i < nb_vertex; ++i, ++p_vertex, ++p_vbuf)
    {
        fn_pfunc(&p_vbuf->pos, &p_vertex->pos);
    }
}

static void
rjCnkVertexVNSH(const CNK_VERTEX_HEAD* restrict vhead, RJS_VERTEX_BUF* restrict vbuf)
{
    /** Get function constants **/
    RJF_CNK_VLIST_POS* const fn_pfunc = _rj_cnk_vlist_pfunc_;
    RJF_CNK_VLIST_NRM* const fn_nfunc = _rj_cnk_vlist_nfunc_;

    /** Read vertex header **/
    const int              nb_vertex = vhead->nbindeces;
    const CNK_VERTEX_VN_SH* p_vertex = (void*) vhead->d;

    /** Populate vertex buffer **/
    RJS_VERTEX_BUF* restrict p_vbuf = vbuf;

    for (int i = 0; i < nb_vertex; ++i, ++p_vertex, ++p_vbuf)
    {
        fn_pfunc(&p_vbuf->pos, &p_vertex->pos);
        fn_nfunc(&p_vbuf->nrm, &p_vertex->nrm);

        rjCnkVertexCalculateIntensity(p_vbuf);
    }
}

static void
rjCnkVertex(const CNK_VERTEX_HEAD* restrict vhead, RJS_VERTEX_BUF* restrict vbuf)
{
    /** Get function constants **/
    RJF_CNK_VLIST_POS* const fn_pfunc = _rj_cnk_vlist_pfunc_;

    /** Read vertex header **/
    const int        nb_vertex = vhead->nbindeces;
    const CNK_VERTEX* p_vertex = (void*) vhead->d;

    /** Populate vertex buffer **/
    RJS_VERTEX_BUF* restrict p_vbuf = vbuf;

    for (int i = 0; i < nb_vertex; ++i, ++p_vertex, ++p_vbuf)
    {
        fn_pfunc(&p_vbuf->pos, &p_vertex->pos);
    }
}

static void
rjCnkVertexD8(const CNK_VERTEX_HEAD* restrict vhead, RJS_VERTEX_BUF* restrict vbuf)
{
    /** Get function constants **/
    RJF_CNK_VLIST_POS* const fn_pfunc = _rj_cnk_vlist_pfunc_;
    RJF_CNK_VLIST_COL* const fn_cfunc = _rj_cnk_vlist_cfunc_;

    /** Read vertex header **/
    const int           nb_vertex = vhead->nbindeces;
    const CNK_VERTEX_D8* p_vertex = (void*) vhead->d;

    /** Populate vertex buffer **/
    RJS_VERTEX_BUF* restrict p_vbuf = vbuf;

    for (int i = 0; i < nb_vertex; ++i, ++p_vertex, ++p_vbuf)
    {
        NJS_ARGB argb;

        fn_pfunc(&p_vbuf->pos, &p_vertex->pos);

        rjCnkGetVlistD8(&argb, &p_vertex->col);

        fn_cfunc(&p_vbuf->col, &argb);
    }
}

static void
rjCnkVertexVN(const CNK_VERTEX_HEAD* restrict vhead, RJS_VERTEX_BUF* restrict vbuf)
{
    /** Get function constants **/
    RJF_CNK_VLIST_POS* const fn_pfunc = _rj_cnk_vlist_pfunc_;
    RJF_CNK_VLIST_NRM* const fn_nfunc = _rj_cnk_vlist_nfunc_;

    /** Read vertex header **/
    const int           nb_vertex = vhead->nbindeces;
    const CNK_VERTEX_VN* p_vertex = (void*) vhead->d;

    /** Populate vertex buffer **/
    RJS_VERTEX_BUF* restrict p_vbuf = vbuf;

    for (int i = 0; i < nb_vertex; ++i, ++p_vertex, ++p_vbuf)
    {
        fn_pfunc(&p_vbuf->pos, &p_vertex->pos);
        fn_nfunc(&p_vbuf->nrm, &p_vertex->nrm);

        rjCnkVertexCalculateIntensity(p_vbuf);
    }
}

static void
rjCnkVertexUF(const CNK_VERTEX_HEAD* restrict vhead, RJS_VERTEX_BUF* restrict vbuf)
{
    /** Get function constants **/
    RJF_CNK_VLIST_POS* const fn_pfunc = _rj_cnk_vlist_pfunc_;

    /** Read vertex header **/
    const int           nb_vertex = vhead->nbindeces;
    const CNK_VERTEX_UF* p_vertex = (void*) vhead->d;

    /** Populate vertex buffer **/
    RJS_VERTEX_BUF* restrict p_vbuf = vbuf;

    for (int i = 0; i < nb_vertex; ++i, ++p_vertex, ++p_vbuf)
    {
        fn_pfunc(&p_vbuf->pos, &p_vertex->pos);
    }
}

static void
rjCnkVertexVND8(const CNK_VERTEX_HEAD* restrict vhead, RJS_VERTEX_BUF* restrict vbuf)
{
    /** Get function constants **/
    RJF_CNK_VLIST_POS* const fn_pfunc = _rj_cnk_vlist_pfunc_;
    RJF_CNK_VLIST_NRM* const fn_nfunc = _rj_cnk_vlist_nfunc_;
    RJF_CNK_VLIST_COL* const fn_cfunc = _rj_cnk_vlist_cfunc_;

    /** Read vertex header **/
    const int              nb_vertex = vhead->nbindeces;
    const CNK_VERTEX_VN_D8* p_vertex = (void*) vhead->d;

    /** Populate vertex buffer **/
    RJS_VERTEX_BUF* restrict p_vbuf = vbuf;

    for (int i = 0; i < nb_vertex; ++i, ++p_vertex, ++p_vbuf)
    {
        NJS_ARGB argb;

        fn_pfunc(&p_vbuf->pos, &p_vertex->pos);
        fn_nfunc(&p_vbuf->nrm, &p_vertex->nrm);

        rjCnkGetVlistVND8(&argb, &p_vertex->col);

        fn_cfunc(&p_vbuf->col, &argb);

        rjCnkVertexCalculateIntensity(p_vbuf);
    }
}

static void
rjCnkVertexD8S8(const CNK_VERTEX_HEAD* restrict vhead, RJS_VERTEX_BUF* restrict vbuf)
{
    /** Get function constants **/
    RJF_CNK_VLIST_POS* const fn_pfunc = _rj_cnk_vlist_pfunc_;
    RJF_CNK_VLIST_COL* const fn_cfunc = _rj_cnk_vlist_cfunc_;
    RJF_CNK_VLIST_SPC* const fn_sfunc = _rj_cnk_vlist_sfunc_;

    /** Read vertex header **/
    const int              nb_vertex = vhead->nbindeces;
    const CNK_VERTEX_D8_S8* p_vertex = (void*) vhead->d;

    /** Populate vertex buffer **/
    RJS_VERTEX_BUF* restrict p_vbuf = vbuf;

    for (int i = 0; i < nb_vertex; ++i, ++p_vertex, ++p_vbuf)
    {
        NJS_ARGB argb;

        fn_pfunc(&p_vbuf->pos, &p_vertex->pos);

        rjCnkGetVlistD8(&argb, &p_vertex->col);

        fn_cfunc(&p_vbuf->col, &argb);

        rjCnkGetVlistS8(&argb, &p_vertex->spc);

        fn_sfunc(&p_vbuf->spc, &argb);
    }
}

static void
rjCnkVertexVNX(const CNK_VERTEX_HEAD* restrict vhead, RJS_VERTEX_BUF* restrict vbuf)
{
    /** Get function constants **/
    RJF_CNK_VLIST_POS* const fn_pfunc = _rj_cnk_vlist_pfunc_;
    RJF_CNK_VLIST_NRM* const fn_nfunc = _rj_cnk_vlist_nfunc_;

    /** Read vertex header **/
    const int            nb_vertex = vhead->nbindeces;
    const CNK_VERTEX_VNX* p_vertex = (void*) vhead->d;

    /** Populate vertex buffer **/
    RJS_VERTEX_BUF* restrict p_vbuf = vbuf;

    for (int i = 0; i < nb_vertex; ++i, ++p_vertex, ++p_vbuf)
    {
        NJS_VECTOR vect;

        fn_pfunc(&p_vbuf->pos, &p_vertex->pos);

        rjCnkGetVlistVNX(&vect, &p_vertex->nrm);

        fn_nfunc(&p_vbuf->nrm, &vect);

        rjCnkVertexCalculateIntensity(p_vbuf);
    }
}

static void
rjCnkVertexVNXD8(const CNK_VERTEX_HEAD* restrict vhead, RJS_VERTEX_BUF* restrict vbuf)
{
    /** Get function constants **/
    RJF_CNK_VLIST_POS* const fn_pfunc = _rj_cnk_vlist_pfunc_;
    RJF_CNK_VLIST_NRM* const fn_nfunc = _rj_cnk_vlist_nfunc_;
    RJF_CNK_VLIST_COL* const fn_cfunc = _rj_cnk_vlist_cfunc_;

    /** Read vertex header **/
    const int               nb_vertex = vhead->nbindeces;
    const CNK_VERTEX_VNX_D8* p_vertex = (void*) vhead->d;

    /** Populate vertex buffer **/
    RJS_VERTEX_BUF* restrict p_vbuf = vbuf;

    for (int i = 0; i < nb_vertex; ++i, ++p_vertex, ++p_vbuf)
    {
        NJS_VECTOR vect;
        NJS_ARGB   argb;

        fn_pfunc(&p_vbuf->pos, &p_vertex->pos);

        rjCnkGetVlistVNX(&vect, &p_vertex->nrm);

        fn_nfunc(&p_vbuf->nrm, &vect);

        rjCnkGetVlistVND8(&argb, &p_vertex->col);

        fn_cfunc(&p_vbuf->col, &argb);

        rjCnkVertexCalculateIntensity(p_vbuf);
    }
}

static void
rjCnkVertexVNXUF(const CNK_VERTEX_HEAD* restrict vhead, RJS_VERTEX_BUF* restrict vbuf)
{
    /** Get function constants **/
    RJF_CNK_VLIST_POS* const fn_pfunc = _rj_cnk_vlist_pfunc_;
    RJF_CNK_VLIST_NRM* const fn_nfunc = _rj_cnk_vlist_nfunc_;

    /** Read vertex header **/
    const int               nb_vertex = vhead->nbindeces;
    const CNK_VERTEX_VNX_UF* p_vertex = (void*) vhead->d;

    /** Populate vertex buffer **/
    RJS_VERTEX_BUF* restrict p_vbuf = vbuf;

    for (int i = 0; i < nb_vertex; ++i, ++p_vertex, ++p_vbuf)
    {
        NJS_VECTOR vect;

        fn_pfunc(&p_vbuf->pos, &p_vertex->pos);

        rjCnkGetVlistVNX(&vect, &p_vertex->nrm);

        fn_nfunc(&p_vbuf->nrm, &vect);

        rjCnkVertexCalculateIntensity(p_vbuf);
    }
}

static void
rjCnkVertexVNUF(const CNK_VERTEX_HEAD* restrict vhead, RJS_VERTEX_BUF* restrict vbuf)
{
    /** Get function constants **/
    RJF_CNK_VLIST_POS* const fn_pfunc = _rj_cnk_vlist_pfunc_;
    RJF_CNK_VLIST_NRM* const fn_nfunc = _rj_cnk_vlist_nfunc_;

    /** Read vertex header **/
    const int              nb_vertex = vhead->nbindeces;
    const CNK_VERTEX_VN_UF* p_vertex = (void*) vhead->d;

    /** Populate vertex buffer **/
    RJS_VERTEX_BUF* restrict p_vbuf = vbuf;

    for (int i = 0; i < nb_vertex; ++i, ++p_vertex, ++p_vbuf)
    {
        fn_pfunc(&p_vbuf->pos, &p_vertex->pos);
        fn_nfunc(&p_vbuf->nrm, &p_vertex->nrm);

        rjCnkVertexCalculateIntensity(p_vbuf);
    }
}

static void
rjCnkVertexNF(const CNK_VERTEX_HEAD* restrict vhead, RJS_VERTEX_BUF* restrict vbuf)
{
    /** Get function constants **/
    RJF_CNK_VLIST_POS* const fn_pfunc = _rj_cnk_vlist_pfunc_;

    /** Read vertex header **/
    const Sint32        nb_vertex = vhead->nbindeces;
    const CNK_VERTEX_NF* p_vertex = (void*) vhead->d;
    const Sint32            wstat = vhead->wstat;

    /** Populate vertex buffer **/

    for (int i = 0; i < nb_vertex; ++i, ++p_vertex)
    {
        NJS_POINT3 pos;

        fn_pfunc(&pos, &p_vertex->pos);

        RJS_VERTEX_BUF* restrict p_vbuf = &vbuf[ p_vertex->i ];

        const f32 mul = CNK_GET_WEIGHT(p_vertex->w);

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
    }
}

static void
rjCnkVertexVNNF(const CNK_VERTEX_HEAD* restrict vhead, RJS_VERTEX_BUF* restrict vbuf)
{
    /** Get function constants **/
    RJF_CNK_VLIST_POS* const fn_pfunc = _rj_cnk_vlist_pfunc_;
    RJF_CNK_VLIST_NRM* const fn_nfunc = _rj_cnk_vlist_nfunc_;

    /** Read vertex header **/
    const Sint32           nb_vertex = vhead->nbindeces;
    const CNK_VERTEX_VN_NF* p_vertex = (void*) vhead->d;
    const Sint32               wstat = vhead->wstat;

    /** Populate vertex buffer **/

    for (int i = 0; i < nb_vertex; ++i, ++p_vertex)
    {
        NJS_POINT3 pos;
        NJS_VECTOR nrm;

        /** Calculate vertex attributes **/
        fn_pfunc(&pos, &p_vertex->pos);
        fn_nfunc(&nrm, &p_vertex->nrm);

        /** Apply weights **/
        RJS_VERTEX_BUF* restrict p_vbuf = &vbuf[ p_vertex->i ];

        const f32 mul = CNK_GET_WEIGHT(p_vertex->w);

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

                rjCnkVertexCalculateIntensity(p_vbuf);
                break;
            }
        }
    }
}

static void
rjCnkVertexNFD8(const CNK_VERTEX_HEAD* restrict vhead, RJS_VERTEX_BUF* restrict vbuf)
{
    /** Get function constants **/
    RJF_CNK_VLIST_POS* const fn_pfunc = _rj_cnk_vlist_pfunc_;
    RJF_CNK_VLIST_COL* const fn_cfunc = _rj_cnk_vlist_cfunc_;

    /** Read vertex header **/
    const Sint32           nb_vertex = vhead->nbindeces;
    const CNK_VERTEX_NF_D8* p_vertex = (void*) vhead->d;
    const Sint32               wstat = vhead->wstat;

    /** Populate vertex buffer **/

    for (int i = 0; i < nb_vertex; ++i)
    {
        NJS_POINT3 pos;

        fn_pfunc(&pos, &p_vertex->pos);

        RJS_VERTEX_BUF* restrict p_vbuf = &vbuf[ p_vertex->i ];

        const f32 mul = CNK_GET_WEIGHT(p_vertex->w);

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
            {
                p_vbuf->pos.x += pos.x;
                p_vbuf->pos.y += pos.y;
                p_vbuf->pos.z += pos.z;
                break;
            }
            case CNK_WEIGHT_END:
            {
                NJS_ARGB argb;

                p_vbuf->pos.x += pos.x;
                p_vbuf->pos.y += pos.y;
                p_vbuf->pos.z += pos.z;

                rjCnkGetVlistD8(&argb, &p_vertex->col);

                fn_cfunc(&p_vbuf->col, &argb); // read color only for end verteces
                break;
            }
        }

        ++p_vertex;
    }
}

/************************************************************************************/
/*
*   Calculate VList
*/
/****** Extern **********************************************************************/
Sint32
rjCnkVList(const Sint32* restrict pVList, RJS_VERTEX_BUF* restrict vbuf)
{
    const bool multi = ( RFRS_GetCnkFuncMode() & RFRS_CNKFUNCMD_MULTIBIT );

    const Sint32* vlist = pVList;

    for ( ; ; )
    {
        bool nf = false; // has weights

        const CNK_VERTEX_HEAD* restrict p_vhead = (void*)vlist;

        /** Get vertex chunk type **/
        const Sint32 type = p_vhead->head;

        if ( type == NJD_ENDOFF )
        {
            /** NJD_ENDOFF **/
            break;
        }

        /** Get the vertex buffer offset for this vertex list. Verteces are copied from the
            'vlist' sequentially (excluding weights) into the vertex buffer starting from this
            offset. The vertex buffer struct is fixed as mixed vertex chunk types are possible. **/
        RJS_VERTEX_BUF* restrict p_vbuf = &vbuf[ p_vhead->indexoffset ];

        switch ( CVSW(type) )
        {
            /*
            *   SH4 Optimized
            */
            case CVSW( NJD_CV_SH ):
            {
                _rj_cnk_context_.vattr = RJD_CVT_P;

                /** No normals, halt drawing if 'MultiDraw' **/
                if ( multi )
                {
                    return CNK_RETN_CLIP;
                }

                rjCnkVertexSH(p_vhead, p_vbuf);
                break;
            }
            case CVSW( NJD_CV_VN_SH ):
            {
                _rj_cnk_context_.vattr = RJD_CVT_PN;

                /** No normals, halt drawing if 'MultiDraw' **/
                if ( multi )
                {
                    return CNK_RETN_CLIP;
                }

                rjCnkVertexVNSH(p_vhead, p_vbuf);
                break;
            }
            /*
            *   Chunk Vertex
            */
            case CVSW( NJD_CV ):
            {
                _rj_cnk_context_.vattr = RJD_CVT_P;

                /** No normals, halt drawing if 'MultiDraw' **/
                if ( multi )
                {
                    return CNK_RETN_CLIP;
                }

                rjCnkVertex(p_vhead, p_vbuf);
                break;
            }
            case CVSW( NJD_CV_D8 ):
            {
                _rj_cnk_context_.vattr = RJD_CVT_PC;

                /** No normals, halt drawing if 'MultiDraw' **/
                if ( multi )
                {
                    return CNK_RETN_CLIP;
                }

                rjCnkVertexD8(p_vhead, p_vbuf);
                break;
            }
            case CVSW( NJD_CV_UF ):
            {
                _rj_cnk_context_.vattr = RJD_CVT_P;

                /** No normals, halt drawing if 'MultiDraw' **/
                if ( multi )
                {
                    return CNK_RETN_CLIP;
                }

                rjCnkVertexUF(p_vhead, p_vbuf);
                break;
            }
            case CVSW( NJD_CV_NF ):
            {
                _rj_cnk_context_.vattr = RJD_CVT_P;

                /** No normals, halt drawing if 'MultiDraw' **/
                if ( multi )
                {
                    return CNK_RETN_CLIP;
                }

                nf = true;

                rjCnkVertexNF(p_vhead, p_vbuf);
                break;
            }
            /*
            *   Chunk Vertex Normals
            */
            case CVSW( NJD_CV_VN ):
            {
                _rj_cnk_context_.vattr = RJD_CVT_PN;

                rjCnkVertexVN(p_vhead, p_vbuf);
                break;
            }
            case CVSW( NJD_CV_VN_D8 ):
            {
                _rj_cnk_context_.vattr = RJD_CVT_PNC;

                rjCnkVertexVND8(p_vhead, p_vbuf);
                break;
            }
            case CVSW( NJD_CV_VN_UF ):
            {
                _rj_cnk_context_.vattr = RJD_CVT_PN;

                rjCnkVertexVNUF(p_vhead, p_vbuf);
                break;
            }
            case CVSW( NJD_CV_VN_NF ):
            {
                _rj_cnk_context_.vattr = RJD_CVT_PN;

                nf = true;

                rjCnkVertexVNNF(p_vhead, p_vbuf);
                break;
            }
            /*
            *   Chunk Vertex Normals32
            */
            case CVSW( NJD_CV_VNX ):
            {
                _rj_cnk_context_.vattr = RJD_CVT_PN;

                rjCnkVertexVNX(p_vhead, p_vbuf);
                break;
            }
            case CVSW( NJD_CV_VNX_D8 ):
            {
                _rj_cnk_context_.vattr = RJD_CVT_PNC;

                rjCnkVertexVNXD8(p_vhead, p_vbuf);
                break;
            }
            case CVSW( NJD_CV_VNX_UF ):
            {
                _rj_cnk_context_.vattr = RJD_CVT_PN;

                rjCnkVertexVNXUF(p_vhead, p_vbuf);
                break;
            }
            /*
            *   Chunk Ninja2 Vertex
            */
            case CVSW( NJD_CV_D8_S8 ):
            {
                _rj_cnk_context_.vattr = RJD_CVT_PCS;

                /** No normals, halt drawing if 'MultiDraw' **/
                if ( multi )
                {
                    return CNK_RETN_CLIP;
                }

                rjCnkVertexD8S8(p_vhead, p_vbuf);
                break;
            }
            case CVSW( NJD_CV_NF_D8 ):
            {
                _rj_cnk_context_.vattr = RJD_CVT_PC;

                /** No normals, halt drawing if 'MultiDraw' **/
                if ( multi )
                {
                    return CNK_RETN_CLIP;
                }

                nf = true;

                rjCnkVertexNFD8(p_vhead, p_vbuf);
                break;
            }
            /*
            *   End
            */
            default:
            {
                /** Unhandled vertex type, halt draw. **/
                return CNK_RETN_CLIP;
            }
        }

        /** Calculate depth queue **/

        nf ? rjCnkCalculateDepthQueueNF(p_vhead, p_vbuf) :
             rjCnkCalculateDepthQueue(  p_vhead, p_vbuf);

        /** Next data chunk **/
        vlist += p_vhead->size + 1;
    }

    return CNK_RETN_OK;
}
