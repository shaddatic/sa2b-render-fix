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
/****** Utility *********************************************************************/
#include <sa2b/util/cnkmdl.h>   /* chunk model structure                            */

/****** Ninja ***********************************************************************/
#include <sa2b/ninja/njcommon.h> /* ninja common                                    */
#include <sa2b/ninja/njmatrix.h> /* ninja matrix                                    */

EXTERN_START

/************************/
/*  Constants           */
/************************/
/****** UV Modes ********************************************************************/
#define IS_UVN                  (0) /* is normal uv values                          */
#define IS_UVH                  (1) /* is hd uv values                              */

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

/****** PList Info ******************************************************************/
/*
*   Description:
*     Get multiplier to convert strip UVs into normalized 0~1 UVs
*
*   Parameters:
*     - uvh     : if the strip uses HD UVs
*/
#define GET_UV_MUL(is_uvh)  ((is_uvh) ? CNK_UVH_MUL : CNK_UVN_MUL)

/****** Strip to Triangle List ******************************************************/
/*
*   Description:
*     Start vertex buffer variables for de-stripping a triangle. It is recommended
*   you use a seperate buffer pointer variable for de-stripping, as logic can
*   quickly become complicated otherwise.
*     The idea is strip logic can remain the same but rather than 'buf++' you
*   write 'buf += buf_inc'.
*
*   Parameters:
*     - buf     : vertex buffer pointer                                       [set]
*     - buf_inc : buffer increment value                                      [set]
*     - invst   : if this stripped triangle is inverted
*/
#define DESTRIP_START(buf, buf_inc, invst) \
    if (invst) { buf_inc = 1; } else { buf += 2; buf_inc = -1; }

/************************/
/*  Structures          */
/************************/
/****** Vertex Buffer ***************************************************************/
typedef struct cnk_vtx_buf
{
    NJS_POINT3 pos;             /* position                                         */
    NJS_VECTOR nrm;             /* normal                                           */
    Uint32     col;             /* color                                            */
    Sint32     dmy;             /* dummy                                            */
}
CNK_VERTEX_BUFFER;

/************************/
/*  Game References     */
/************************/
/****** Cnk Matrix ******************************************************************/
#define _env_matrix_44_         DATA_REF(NJS_MATRIX44, 0x01AF14E0)
#define _unit_matrix_44_        DATA_REF(NJS_MATRIX44, 0x01AF1A10)

EXTERN_END

#endif/*H_RF_DRAW_CNK*/
