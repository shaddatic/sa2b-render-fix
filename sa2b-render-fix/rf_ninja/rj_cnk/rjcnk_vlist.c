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
#include <rf_ninja/rj_cnk/rjcnk_internal.h> /* parent & siblings                    */

/************************/
/*  Macro               */
/************************/
/****** Sqrt ************************************************************************/
#define INVSQR(x)               ((1.f/x) * (1.f/x))
#define SQR(x)                  ((x) * (x))

/************************/
/*  Structures          */
/************************/
/****** Vlist Function **************************************************************/
typedef struct
{
    Uint16 vattr;
    Uint16 njflag;

    void (*fnVlist)( const CNK_VERTEX_HEAD* restrict vhead, RJS_VERTEX_BUF* restrict vbuf );
}
RJS_VLIST_ENTRY;

/************************/
/*  Source              */
/************************/
/****** Transform *******************************************************************/
static inline void
rjCnkCalcVlistPos(NJS_POINT3* dst, const NJS_POINT3* src)
{
    njCalcPoint(NULL, src, dst);
}

static inline void
rjCnkCalcVlistNrm(NJS_VECTOR* dst, const NJS_VECTOR* src)
{
    njCalcVector(NULL, src, dst);
}

static inline void
rjCnkCalcVlistCol(NJS_BGRA* dst, const NJS_BGRA* src)
{
    *dst = *src;
}

static inline void
rjCnkCalcVlistSpc(NJS_BGRA* dst, const NJS_BGRA* src)
{
    *dst = *src;
}

/****** Lights **********************************************************************/
static Float
rjCnkCalcLightIntensity(int light, const RJS_VERTEX_BUF* restrict vbuf)
{
    const RJS_LIGHT* p_lite = &_rj_lights_[light];

    switch ( p_lite->mode )
    {
        case RJ_LIGHT_MD_DIR:
        {
            return njInnerProduct( &vbuf->nrm, &p_lite->v ) * p_lite->inten;
        }
        case RJ_LIGHT_MD_POINT: POINT:
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
        case RJ_LIGHT_MD_SPOT:
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
    const Uint32 litesw = _rj_light_sw_;

    if ( litesw & (1<<RJ_LIGHT_1) )
    {
        vbuf->inten[0] = rjCnkCalcLightIntensity(0, vbuf);
    }

    if ( litesw & (1<<RJ_LIGHT_2) )
    {
        vbuf->inten[1] = rjCnkCalcLightIntensity(1, vbuf);
    }

    if ( litesw & (1<<RJ_LIGHT_3) )
    {
        vbuf->inten[2] = rjCnkCalcLightIntensity(2, vbuf);
    }

    if ( litesw & (1<<RJ_LIGHT_4) )
    {
        vbuf->inten[3] = rjCnkCalcLightIntensity(3, vbuf);
    }

    if ( litesw & (1<<RJ_LIGHT_5) )
    {
        vbuf->inten[4] = rjCnkCalcLightIntensity(4, vbuf);
    }

    if ( litesw & (1<<RJ_LIGHT_6) )
    {
        vbuf->inten[5] = rjCnkCalcLightIntensity(5, vbuf);
    }
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
rjCnkGetVlistD5(NJS_ARGB* dst, const CNK_565* src)
{
    // not implemented
}

static inline void
rjCnkGetVlistD4(NJS_ARGB* dst, const CNK_4444* src)
{
    // not implemented
}

static inline void
rjCnkGetVlistDI(NJS_ARGB* dst, const Uint16* src)
{
    // not implemented
}

/****** Specular Color **************************************************************/
static inline void
rjCnkGetVlistS5(NJS_ARGB* dst, const CNK_565* src)
{
    // not implemented
}

static inline void
rjCnkGetVlistS8(NJS_ARGB* dst, const NJS_BGRA* src)
{
    // not implemented
}

static inline void
rjCnkGetVlistSI(NJS_ARGB* dst, const Uint16* src)
{
    // not implemented
}

/************************************************************************************/
/*
*   Calculate Vertex Chunk
*/
/****** Static **********************************************************************/
static void
rjCnkVertex1(const CNK_VERTEX_HEAD* restrict vhead, RJS_VERTEX_BUF* restrict vbuf)
{
    /** Read vertex header **/
    const int           nb_vertex = vhead->nbindeces;
    const CNK_VERTEX_UF* p_vertex = (void*) vhead->d;

    /** Populate vertex buffer **/
    RJS_VERTEX_BUF* restrict p_vbuf = vbuf;

    for (int i = 0; i < nb_vertex; ++i, ++p_vertex, ++p_vbuf)
    {
        rjCnkCalcVlistPos(&p_vbuf->pos, &p_vertex->pos);
    }
}

static void
rjCnkVertexVNSH(const CNK_VERTEX_HEAD* restrict vhead, RJS_VERTEX_BUF* restrict vbuf)
{
    /** Read vertex header **/
    const int              nb_vertex = vhead->nbindeces;
    const CNK_VERTEX_VN_SH* p_vertex = (void*) vhead->d;

    /** Populate vertex buffer **/
    RJS_VERTEX_BUF* restrict p_vbuf = vbuf;

    for (int i = 0; i < nb_vertex; ++i, ++p_vertex, ++p_vbuf)
    {
        rjCnkCalcVlistPos(&p_vbuf->pos, &p_vertex->pos);
        rjCnkCalcVlistNrm(&p_vbuf->nrm, &p_vertex->nrm);

        rjCnkVertexCalculateIntensity(p_vbuf);
    }
}

static void
rjCnkVertex(const CNK_VERTEX_HEAD* restrict vhead, RJS_VERTEX_BUF* restrict vbuf)
{
    /** Read vertex header **/
    const int        nb_vertex = vhead->nbindeces;
    const CNK_VERTEX* p_vertex = (void*) vhead->d;

    /** Populate vertex buffer **/
    RJS_VERTEX_BUF* restrict p_vbuf = vbuf;

    for (int i = 0; i < nb_vertex; ++i, ++p_vertex, ++p_vbuf)
    {
        rjCnkCalcVlistPos(&p_vbuf->pos, &p_vertex->pos);
    }
}

static void
rjCnkVertexD8(const CNK_VERTEX_HEAD* restrict vhead, RJS_VERTEX_BUF* restrict vbuf)
{
    /** Read vertex header **/
    const int           nb_vertex = vhead->nbindeces;
    const CNK_VERTEX_D8* p_vertex = (void*) vhead->d;

    /** Populate vertex buffer **/
    RJS_VERTEX_BUF* restrict p_vbuf = vbuf;

    for (int i = 0; i < nb_vertex; ++i, ++p_vertex, ++p_vbuf)
    {
        rjCnkCalcVlistPos(&p_vbuf->pos, &p_vertex->pos);
        rjCnkCalcVlistCol(&p_vbuf->col, &p_vertex->col);
    }
}

static void
rjCnkVertexVN(const CNK_VERTEX_HEAD* restrict vhead, RJS_VERTEX_BUF* restrict vbuf)
{
    /** Read vertex header **/
    const int           nb_vertex = vhead->nbindeces;
    const CNK_VERTEX_VN* p_vertex = (void*) vhead->d;

    /** Populate vertex buffer **/
    RJS_VERTEX_BUF* restrict p_vbuf = vbuf;

    for (int i = 0; i < nb_vertex; ++i, ++p_vertex, ++p_vbuf)
    {
        rjCnkCalcVlistPos(&p_vbuf->pos, &p_vertex->pos);
        rjCnkCalcVlistNrm(&p_vbuf->nrm, &p_vertex->nrm);

        rjCnkVertexCalculateIntensity(p_vbuf);
    }
}

static void
rjCnkVertexVND8(const CNK_VERTEX_HEAD* restrict vhead, RJS_VERTEX_BUF* restrict vbuf)
{
    /** Read vertex header **/
    const int              nb_vertex = vhead->nbindeces;
    const CNK_VERTEX_VN_D8* p_vertex = (void*) vhead->d;

    /** Populate vertex buffer **/
    RJS_VERTEX_BUF* restrict p_vbuf = vbuf;

    for (int i = 0; i < nb_vertex; ++i, ++p_vertex, ++p_vbuf)
    {
        rjCnkCalcVlistPos(&p_vbuf->pos, &p_vertex->pos);
        rjCnkCalcVlistNrm(&p_vbuf->nrm, &p_vertex->nrm);
        rjCnkCalcVlistCol(&p_vbuf->col, &p_vertex->col);

        rjCnkVertexCalculateIntensity(p_vbuf);
    }
}

static void
rjCnkVertexD8S8(const CNK_VERTEX_HEAD* restrict vhead, RJS_VERTEX_BUF* restrict vbuf)
{
    /** Read vertex header **/
    const int              nb_vertex = vhead->nbindeces;
    const CNK_VERTEX_D8_S8* p_vertex = (void*) vhead->d;

    /** Populate vertex buffer **/
    RJS_VERTEX_BUF* restrict p_vbuf = vbuf;

    for (int i = 0; i < nb_vertex; ++i, ++p_vertex, ++p_vbuf)
    {
        rjCnkCalcVlistPos(&p_vbuf->pos, &p_vertex->pos);
        rjCnkCalcVlistCol(&p_vbuf->col, &p_vertex->col);
        rjCnkCalcVlistSpc(&p_vbuf->spc, &p_vertex->spc);
    }
}

static void
rjCnkVertexVNX(const CNK_VERTEX_HEAD* restrict vhead, RJS_VERTEX_BUF* restrict vbuf)
{
    /** Read vertex header **/
    const int            nb_vertex = vhead->nbindeces;
    const CNK_VERTEX_VNX* p_vertex = (void*) vhead->d;

    /** Populate vertex buffer **/
    RJS_VERTEX_BUF* restrict p_vbuf = vbuf;

    for (int i = 0; i < nb_vertex; ++i, ++p_vertex, ++p_vbuf)
    {
        NJS_VECTOR vect;

        rjCnkGetVlistVNX(&vect, &p_vertex->nrm);

        rjCnkCalcVlistPos(&p_vbuf->pos, &p_vertex->pos);
        rjCnkCalcVlistNrm(&p_vbuf->nrm, &vect);

        rjCnkVertexCalculateIntensity(p_vbuf);
    }
}

static void
rjCnkVertexVNXD8(const CNK_VERTEX_HEAD* restrict vhead, RJS_VERTEX_BUF* restrict vbuf)
{
    /** Read vertex header **/
    const int               nb_vertex = vhead->nbindeces;
    const CNK_VERTEX_VNX_D8* p_vertex = (void*) vhead->d;

    /** Populate vertex buffer **/
    RJS_VERTEX_BUF* restrict p_vbuf = vbuf;

    for (int i = 0; i < nb_vertex; ++i, ++p_vertex, ++p_vbuf)
    {
        NJS_VECTOR vect;

        rjCnkGetVlistVNX(&vect, &p_vertex->nrm);

        rjCnkCalcVlistPos(&p_vbuf->pos, &p_vertex->pos);
        rjCnkCalcVlistNrm(&p_vbuf->nrm, &vect);
        rjCnkCalcVlistCol(&p_vbuf->col, &p_vertex->col);

        rjCnkVertexCalculateIntensity(p_vbuf);
    }
}

static void
rjCnkVertexVNX1(const CNK_VERTEX_HEAD* restrict vhead, RJS_VERTEX_BUF* restrict vbuf)
{
    /** Read vertex header **/
    const int               nb_vertex = vhead->nbindeces;
    const CNK_VERTEX_VNX_UF* p_vertex = (void*) vhead->d;

    /** Populate vertex buffer **/
    RJS_VERTEX_BUF* restrict p_vbuf = vbuf;

    for (int i = 0; i < nb_vertex; ++i, ++p_vertex, ++p_vbuf)
    {
        NJS_VECTOR vect;

        rjCnkGetVlistVNX(&vect, &p_vertex->nrm);

        rjCnkCalcVlistPos(&p_vbuf->pos, &p_vertex->pos);
        rjCnkCalcVlistNrm(&p_vbuf->nrm, &vect);

        rjCnkVertexCalculateIntensity(p_vbuf);
    }
}

static void
rjCnkVertexVN1(const CNK_VERTEX_HEAD* restrict vhead, RJS_VERTEX_BUF* restrict vbuf)
{
    /** Read vertex header **/
    const int              nb_vertex = vhead->nbindeces;
    const CNK_VERTEX_VN_UF* p_vertex = (void*) vhead->d;

    /** Populate vertex buffer **/
    RJS_VERTEX_BUF* restrict p_vbuf = vbuf;

    for (int i = 0; i < nb_vertex; ++i, ++p_vertex, ++p_vbuf)
    {
        rjCnkCalcVlistPos(&p_vbuf->pos, &p_vertex->pos);
        rjCnkCalcVlistNrm(&p_vbuf->nrm, &p_vertex->nrm);

        rjCnkVertexCalculateIntensity(p_vbuf);
    }
}

static void
rjCnkVertexNF(const CNK_VERTEX_HEAD* restrict vhead, RJS_VERTEX_BUF* restrict vbuf)
{
    /** Read vertex header **/
    const Sint32        nb_vertex = vhead->nbindeces;
    const CNK_VERTEX_NF* p_vertex = (void*) vhead->d;
    const Sint32            wstat = vhead->wstat;

    /** Populate vertex buffer **/

    for (int i = 0; i < nb_vertex; ++i, ++p_vertex)
    {
        NJS_POINT3 pos;
        rjCnkCalcVlistPos(&pos, &p_vertex->pos);

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
    /** Read vertex header **/
    const Sint32           nb_vertex = vhead->nbindeces;
    const CNK_VERTEX_VN_NF* p_vertex = (void*) vhead->d;
    const Sint32               wstat = vhead->wstat;

    /** Populate vertex buffer **/

    for (int i = 0; i < nb_vertex; ++i, ++p_vertex)
    {
        NJS_POINT3 pos;
        NJS_VECTOR nrm;
        rjCnkCalcVlistPos(&pos, &p_vertex->pos);
        rjCnkCalcVlistNrm(&nrm, &p_vertex->nrm);

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
    /** Read vertex header **/
    const Sint32           nb_vertex = vhead->nbindeces;
    const CNK_VERTEX_NF_D8* p_vertex = (void*) vhead->d;
    const Sint32               wstat = vhead->wstat;

    /** Populate vertex buffer **/

    for (int i = 0; i < nb_vertex; ++i)
    {
        NJS_POINT3 pos;
        rjCnkCalcVlistPos(&pos, &p_vertex->pos);

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
                p_vbuf->pos.x += pos.x;
                p_vbuf->pos.y += pos.y;
                p_vbuf->pos.z += pos.z;

                rjCnkCalcVlistCol(&p_vbuf->col, &p_vertex->col); // read color only for end verteces
                break;
            }
        }

        ++p_vertex;
    }
}

/************************************************************************************/
/*
*   VList Functions List
*/
/****** Functions *******************************************************************/
static const RJS_VLIST_ENTRY _rj_vlist_funcs_[NJD_CV_NF_D8 - NJD_VERTOFF + 1] =
{
    /*
    *   SH4 Optimized
    */
    [ NJD_CV_SH - NJD_VERTOFF ] = 
    {
        .vattr   = RJD_CVT_P,
        .njflag  = FALSE,
        .fnVlist = rjCnkVertex1,
    },
    [ NJD_CV_VN_SH - NJD_VERTOFF ] =
    {
        .vattr   = RJD_CVT_PN,
        .njflag  = FALSE,
        .fnVlist = rjCnkVertexVNSH,
    },
    /*
    *   Chunk Vertex
    */
    [ NJD_CV - NJD_VERTOFF ] =
    {
        .vattr   = RJD_CVT_P,
        .njflag  = FALSE,
        .fnVlist = rjCnkVertex,
    },
    [ NJD_CV_D8 - NJD_VERTOFF ] =
    {
        .vattr   = RJD_CVT_PC,
        .njflag  = FALSE,
        .fnVlist = rjCnkVertexD8,
    },
    [ NJD_CV_UF - NJD_VERTOFF ] =
    {
        .vattr   = RJD_CVT_P,
        .njflag  = FALSE,
        .fnVlist = rjCnkVertex1,
    },
    [ NJD_CV_NF - NJD_VERTOFF ] =
    {
        .vattr   = RJD_CVT_P,
        .njflag  = TRUE,
        .fnVlist = rjCnkVertexNF,
    },
    [ NJD_CV_S5 - NJD_VERTOFF ] =
    {
        .vattr   = RJD_CVT_P,
        .njflag  = FALSE,
        .fnVlist = rjCnkVertex1,
    },
    [ NJD_CV_S4 - NJD_VERTOFF ] =
    {
        .vattr   = RJD_CVT_P,
        .njflag  = FALSE,
        .fnVlist = rjCnkVertex1,
    },
    [ NJD_CV_IN - NJD_VERTOFF ] =
    {
        .vattr   = RJD_CVT_P,
        .njflag  = FALSE,
        .fnVlist = rjCnkVertex1,
    },
    /*
    *   Chunk Vertex Normals
    */
    [ NJD_CV_VN - NJD_VERTOFF ] =
    {
        .vattr   = RJD_CVT_PN,
        .njflag  = FALSE,
        .fnVlist = rjCnkVertexVN,
    },
    [ NJD_CV_VN_D8 - NJD_VERTOFF ] =
    {
        .vattr   = RJD_CVT_PNC,
        .njflag  = FALSE,
        .fnVlist = rjCnkVertexVND8,
    },
    [ NJD_CV_VN_UF - NJD_VERTOFF ] =
    {
        .vattr   = RJD_CVT_PN,
        .njflag  = FALSE,
        .fnVlist = rjCnkVertexVN1,
    },
    [ NJD_CV_VN_NF - NJD_VERTOFF ] =
    {
        .vattr   = RJD_CVT_PN,
        .njflag  = TRUE,
        .fnVlist = rjCnkVertexVNNF,
    },
    [ NJD_CV_VN_S5 - NJD_VERTOFF ] =
    {
        .vattr   = RJD_CVT_PN,
        .njflag  = FALSE,
        .fnVlist = rjCnkVertexVN1,
    },
    [ NJD_CV_VN_S4 - NJD_VERTOFF ] =
    {
        .vattr   = RJD_CVT_PN,
        .njflag  = FALSE,
        .fnVlist = rjCnkVertexVN1,
    },
    [ NJD_CV_VN_IN - NJD_VERTOFF ] =
    {
        .vattr   = RJD_CVT_PN,
        .njflag  = FALSE,
        .fnVlist = rjCnkVertexVN1,
    },
    /*
    *   Chunk Vertex Normals32 (VNX)
    */
    [ NJD_CV_VNX - NJD_VERTOFF ] =
    {
        .vattr   = RJD_CVT_PN,
        .njflag  = FALSE,
        .fnVlist = rjCnkVertexVNX,
    },
    [ NJD_CV_VNX_D8 - NJD_VERTOFF ] =
    {
        .vattr   = RJD_CVT_PNC,
        .njflag  = FALSE,
        .fnVlist = rjCnkVertexVNXD8,
    },
    [ NJD_CV_VNX_UF - NJD_VERTOFF ] =
    {
        .vattr   = RJD_CVT_PN,
        .njflag  = FALSE,
        .fnVlist = rjCnkVertexVNX1,
    },
    /*
    *   Chunk Vertex Ninja2
    */
    [ NJD_CV_D8_S8 - NJD_VERTOFF ] =
    {
        .vattr   = RJD_CVT_PCS,
        .njflag  = FALSE,
        .fnVlist = rjCnkVertexD8S8,
    },
    [ NJD_CV_NF_D8 - NJD_VERTOFF ] =
    {
        .vattr   = RJD_CVT_PC,
        .njflag  = TRUE,
        .fnVlist = rjCnkVertexNFD8,
    },
};

/************************************************************************************/
/*
*   Calculate VList
*/
/****** Extern **********************************************************************/
Sint32
rjCnkVList(const Sint32* restrict pVList, RJS_VERTEX_BUF* restrict vbuf)
{
    const bool multi = ( _rj_cnk_context_.func & RFRS_CNKFUNCMD_MULTIBIT );

    // Get Chunk Control vertex attribute flags
    const Uint16 vattr_and = (_rj_cnk_ctrl_flag_ & RJD_CNK_CTRL_MASK_VTX) >> RJD_CNK_CTRL_SHIFT_VTX;

    // Start Vlist
    const Sint32* vlist = pVList;

    for ( ; ; )
    {
        const CNK_VERTEX_HEAD* restrict p_vhead = (void*)vlist;

        // If end offset, stop
        if ( p_vhead->head == NJD_ENDOFF )
        {
            break;
        }

        // Get function for this vlist chunk
        const RJS_VLIST_ENTRY* restrict p_vfunc = &_rj_vlist_funcs_[p_vhead->head - NJD_VERTOFF];

        // Multi draw variants don't support vertex types with no normals, so clip them
        if ( multi && !(p_vfunc->vattr & RJD_CVF_NORMAL) )
        {
            return CNK_RETN_CLIP;
        }

        // Verteces are calculated sequentially (excluding weights, which can do arbitrary
        // vertices per vlist index) into the vertex buffer starting from this offset.

        // Get the vertex buffer offset for this vlist.
        RJS_VERTEX_BUF* restrict p_vbuf = &vbuf[ p_vhead->indexoffset ];

        // Set vertex attrs and buffer
        _rj_cnk_context_.vattr = (p_vfunc->vattr & vattr_and);

        p_vfunc->fnVlist(p_vhead, p_vbuf);

        // Calculate the depth queue (fading at distance)
        rjCnkCalculateDepthQueue(p_vhead, p_vbuf, p_vfunc->njflag);

        // next vertex chunk
        vlist += p_vhead->size + CNK_VERTOFF_SIZE_ADD;
    }

    // End Vlist, OK!
    return CNK_RETN_OK;
}
