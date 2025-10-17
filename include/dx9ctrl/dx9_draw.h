/*
*   dx9ctrl (SA2B) - '/dx9_draw.h'
*
*   Description:
*     DirectX 9 control library for SA2PC get render state header.
*/
#ifndef H_DX9CTRL_DRAW
#define H_DX9CTRL_DRAW

/********************************/
/*  Includes                    */
/********************************/
/****** DX9 Control *****************************************************************************/
#include <dx9ctrl/dx9_common.h>         /* dx9 common                                           */
#include <dx9ctrl/dx9_renderstate.h>    /* blend modes                                          */

DX9_HEADER_START

/********************************/
/*  Enums                       */
/********************************/
/****** Vertex Primitive Type *******************************************************************/
typedef enum
{
    DX9_PRITYPE_POINTLIST = 1,
    DX9_PRITYPE_LINELIST,
    DX9_PRITYPE_LINESTRIP,
    DX9_PRITYPE_TRIANGLELIST,
    DX9_PRITYPE_TRIANGLESTRIP,
    DX9_PRITYPE_TRIANGLEFAN,
}
dx9_primitive_type;

/********************************/
/*  Prototypes                  */
/********************************/
/****** Draw Primitive **************************************************************************/
/*
*   Description:
*     Draw primitive list from declared vertex buffer.
* 
*   Parameters:
*     - type        : primitive type
*     - ixStart     : vertex index to draw from
*     - nbPrim      : number of primitives to draw
* 
*   Returns:
*     'true' on success, or 'false' on failure.
*/
bool    DX9_DrawPrimitive( dx9_primitive_type type, dx9_size ixStart, dx9_size nbPrim );
/*
*   Description:
*     Draw primitive list from a user-defined vertex buffer. This is slower than
*   regular 'DrawPrimitive'.
* 
*   Parameters:
*     - type        : primitive type
*     - nbPrim      : number of primitives to draw
*     - pVtxBuf     : vertex buffer to draw from
*     - szStride    : stride size of each vertex in bytes
* 
*   Returns:
*     'true' on success, or 'false' on failure.
*/
bool    DX9_DrawPrimitiveUP( dx9_primitive_type type, dx9_size nbPrim, const void* pVtxBuf, dx9_size szStride );

DX9_HEADER_END

#endif/*H_DX9CTRL_DRAW*/
