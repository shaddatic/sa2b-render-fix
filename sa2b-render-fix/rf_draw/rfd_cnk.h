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
#define NJD_BITSOFF_MAX         (NJD_CB_DP  +1)  /* bits offset                     */
#define NJD_TINYOFF_MAX         (NJD_CT_TID2+1)  /* tiny/tex offset                 */
#define NJD_MATOFF_MAX          (NJD_CM_DAS2+1)  /* material offset                 */
#define NJD_VERTOFF_MAX         (NJD_CV_NF_D8+1) /* vertex offset                   */
#define NJD_VOLOFF_MAX          (NJD_CO_ST  +1)  /* volume offset                   */
#define NJD_STRIPOFF_MAX        (NJD_CS_UVH2+1)  /* strip offset                    */

/************************/
/*  Macro               */
/************************/
/****** Strip Switch ****************************************************************/
/*
*   Description:
*     Normalizes Cnk strip type values to start from 0 for use in a switch.
*
*   Parameters:
*     - type    : raw strip type
*/
#define STSW(type)          ((type) - NJD_STRIPOFF)

/****** Volume Switch ***************************************************************/
/*
*   Description:
*     Normalizes Cnk volume type values to start from 0 for use in a switch.
*
*   Parameters:
*     - type    : raw volume type
*/
#define VOSW(type)          ((type) - NJD_VOLOFF)

/****** Strip ***********************************************************************/
/*
*   Description:
*     Move plist pointer from the base of the current strip chunk to the base of the
*   next strip chunk in the list.
*
*   Parameters:
*     - pst     : current plist strip pointer
*     - nbst    : number of strip verteces in the current strip
*     - ufo     : user offset value
*
*   Returns:
*     Pointer to next strip chunk
*/
#define NEXT_STRIP(pst, nbst, ufo)  \
    ((void*)((uintptr_t)(pst) + (sizeof((pst)->d[0]) * nbst) + sizeof((p_str)->len) + ((ufo) * 2)))

/****** PList Info ******************************************************************/
/*
*   Description:
*     Get multiplier to convert strip UVs into normalized 0~1 UVs
*
*   Parameters:
*     - uvh     : if the strip uses HD UVs
*/
#define GET_UV_MUL(uvh)     ((uvh) ? (1.f/1024.f) : (1.f/256.f))
/*
*   Description:
*     Get vertex normal information stored in the Cnk strip info.
*
*   Parameters:
*     - vn      : s16 normal value
*/
#define GET_PVN(vn)         ((f32)(vn) * (1.f/32767.f))

/****** Strip to Triangle ***********************************************************/
/*
*   Description:
*     Start vertex index variabnles for converting a strip triangle to a regular
*   triangle by un-stripping the verteces.
*
*   Parameters:
*     - vidx    : starting vertex index into the stripped triangle
*     - vinc    : increment value depending on the triangle winding
*     - binv    : if this triangle has inverted inverted
*/
#define VIDX_START(vidx, vinc, binv)  \
    if (!(binv)) { vidx = 0; vinc = 1; } else { vidx = 2; vinc = -1; }

/************************/
/*  Structures          */
/************************/
/****** Vertex Buffer ***************************************************************/
typedef struct cnk_vtx_buf
{
    NJS_POINT3 pos;
    NJS_VECTOR norm;
    Uint32     color;
    Sint32     dmy;
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

/************************/
/*  Game References     */
/************************/
/****** Cnk Matrix ******************************************************************/
#define _env_matrix_44_         DATA_REF(NJS_MATRIX44, 0x01AF14E0)
#define _unit_matrix_44_        DATA_REF(NJS_MATRIX44, 0x01AF1A10)

#endif/*H_RF_DRAW_CNK*/
