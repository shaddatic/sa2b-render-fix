/*
*   SA2 Render Fix - '/rf_draw/rfd_cnk.h'
*
*   Description:
*     Common header for Chunk draw (Normal/Modifier)
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
#include <samt/util/cnkmdl.h>   /* chunk model structure                            */

/****** Ninja ***********************************************************************/
#include <samt/ninja/njcommon.h> /* ninja common                                    */
#include <samt/ninja/njmatrix.h> /* ninja matrix                                    */

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
*     Normalizes Cnk vertex type values to start from 0 for use in a switch.
*
*   Parameters:
*     - type    : vertex offset type
*/
#define CVSW(type)          ((type) - NJD_VERTOFF)

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
    if (invst) { buf += 2; buf_inc = -1; } else { buf_inc = 1; }

/****** Next Strip Polygon **********************************************************/
/*
*   Description:
*     Get next strip polygon, while also checking the strip index to ensure the user
*   flag offset value is only applied after the 2nd index.
*
*   Parameters:
*     - strip       : current strip polygon
*     - ix          : current strip poly index
*     - ufo         : user flag offset value
*
*   Returns:
*     Next strip polygon.
*/
#define NEXT_STRIP_POLY(strip, ix, ufo)          CNK_NEXT_POLY((strip), ((ix) >= 2) ? (ufo) : 0)

/************************/
/*  Structures          */
/************************/
/****** Vertex Buffer ***************************************************************/
typedef struct rjvtxbuf
{
    NJS_POINT3 pos;             /* position                                         */
    NJS_VECTOR nrm;             /* normal                                           */
    NJS_BGRA   col;             /* color                                            */
    NJS_BGRA   spc;             /* specular                                         */
    Float      inten[6];        /* light intensities                                */

    Uint32     pad[2];
}
RJS_VERTEX_BUF;

/************************/
/*  Prototypes          */
/************************/
/****** Transform Object ************************************************************/
/*
*   Description:
*     Transform and draw a Chunk object with set draw function.
*
*   Parameters:
*     - object      : chunk object
*     - callback    : model draw function
*/
void    rjCnkTransformObject( const NJS_CNK_OBJECT* object, Sint32(*callback)(NJS_CNK_MODEL*) );

EXTERN_END

#endif/*H_RF_DRAW_CNK*/
