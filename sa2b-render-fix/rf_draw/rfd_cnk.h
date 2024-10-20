/*
*   SA2 Render Fix - '/rf_draw/rfd_cnk.h'
*
*   Description:
*     Internal utility header for CnkDraw functions
*
*   Contributors:
*     - Shaddatic
*/
#ifndef H_RF_DRAW_CNK
#define H_RF_DRAW_CNK

/************************/
/*  External Includes   */
/************************/
/****** Ninja ***********************************************************************/
#include <sa2b/ninja/njcommon.h> /* ninja common                                    */
#include <sa2b/ninja/njmatrix.h> /* ninja matrix                                    */

/************************/
/*  Constants           */
/************************/
/****** Cnk Offsets *****************************************************************/
#define NJD_BITSOFF_MAX         (NJD_CB_DP  +1) /* bits offset                      */
#define NJD_TINYOFF_MAX         (NJD_CT_TID2+1) /* tiny/tex offset                  */
#define NJD_MATOFF_MAX          (NJD_CM_DAS2+1) /* material offset                  */
#define NJD_VOLOFF_MAX          (NJD_CO_ST  +1) /* volume offset                    */
#define NJD_STRIPOFF_MAX        (NJD_CS_UVH2+1) /* strip offset                     */

/************************/
/*  Macro               */
/************************/
/****** Strip Switch ****************************************************************/
#define STSW(type)          ((type) - NJD_STRIPOFF) /* for switch entries           */

/****** Volume Switch ***************************************************************/
#define VOSW(type)          ((type) - NJD_VOLOFF)   /* for switch entries           */

/****** Strip ***********************************************************************/
#define NEXT_STRIP(pst, nbst, ufo)  \
    ((void*)((uintptr_t)(pst) + (sizeof((pst)->d[0]) * nbst) + sizeof((p_str)->len) + ((ufo) * 2)))

/****** PList Vertex Normal *********************************************************/
#define GET_PVN(vn)         ((f32)(vn) * (1.f/32767.f))

/************************/
/*  Structures          */
/************************/
/****** Vertex Buffer ***************************************************************/
typedef struct cnk_vtx_buf
{
    NJS_POINT3 pos;
    NJS_VECTOR norm;
    Uint32     color;
    Sint32     unknown;
}
CNK_VERTEX_BUFFER;

/****** Chunk VList *****************************************************************/
typedef struct
{
    u8  headbits;
    u8  chunkhead;
    u16 size;
    u16 indexoffset;
    u16 nbindeces;
}
CNK_VLIST_HEAD;

typedef struct
{
    CNK_VLIST_HEAD;

    struct
    {
        NJS_POINT3 pos;
        Float      one;
    }
    d[];
}
CNK_VLIST_SH;

typedef struct
{
    CNK_VLIST_HEAD;

    struct
    {
        NJS_POINT3 pos;
        Float      one;
        NJS_VECTOR norm;
        Float      zero;
    }
    d[];
}
CNK_VLIST_VN_SH;

typedef struct
{
    CNK_VLIST_HEAD;

    struct
    {
        NJS_POINT3 pos;
    }
    d[];
}
CNK_VLIST_CV;

typedef struct
{
    CNK_VLIST_HEAD;

    struct
    {
        NJS_POINT3 pos;
        Uint32     color;
    }
    d[];
}
CNK_VLIST_D8;

typedef struct
{
    CNK_VLIST_HEAD;

    struct
    {
        NJS_POINT3 pos;
        NJS_VECTOR norm;
    }
    d[];
}
CNK_VLIST_VN;

typedef struct
{
    CNK_VLIST_HEAD;

    struct
    {
        NJS_POINT3 pos;
        NJS_VECTOR norm;
        Uint32     color;
    }
    d[];
}
CNK_VLIST_VN_D8;

typedef struct
{
    CNK_VLIST_HEAD;

    struct
    {
        NJS_POINT3 pos;
        NJS_VECTOR norm;
        Uint16     idx;
        Uint16     mul;
    }
    d[];
}
CNK_VLIST_VN_NF;

/****** Chunk PList *****************************************************************/
typedef struct
{
    Sint16 len; // negative bit is wind flag

    struct
    {
        Sint16 i;
        Sint16 u, v;
    }
    d[];
}
CNK_STRIP_UV;

typedef struct
{
    Sint16 len; // negative bit is wind flag

    struct
    {
        Sint16 i;
        Sint16 vx, vy, vz;
    }
    d[];
}
CNK_STRIP_VN;

typedef struct
{
    Sint16 len; // negative bit is wind flag

    struct
    {
        Sint16 i;
        Sint16 u, v;
        Sint16 vx, vy, vz;
    }
    d[];
}
CNK_STRIP_UV_VN;

typedef struct
{
    Sint16 len; // negative bit is wind flag

    struct
    {
        Sint16 i;
        Sint16 u, v;
        Sint32 color;
    }
    d[];
}
CNK_STRIP_UV_D8;

typedef struct
{
    Sint16 len; // negative bit is wind flag

    struct
    {
        Sint16 i;
    }
    d[];
}
CNK_STRIP;

#endif/*H_RF_DRAW_CNK*/
