/*
*   SA2 Render Fix - '/rf_ninja.h'
*
*   Description:
*       Render Fix Ninja functions (rj).
*
*   Contributors:
*   -   Shaddatic
*/
#ifndef _RF_NINJA_H_
#define _RF_NINJA_H_

/************************/
/*  External Headers    */
/************************/
/****** Ninja ***********************************************************************/
#include <sa2b/ninja/ninja.h>   /* ninja                                            */

EXTERN_START

/************************/
/*  Functions           */
/************************/
/****** Init ************************************************************************/
/*
*   Init Render Fix 'Ninja' module
*/
void    RF_NinjaInit( void );

/****** Draw ************************************************************************/
/*
*   Draw a multi-vertex, 2D texture.
* 
*   Parameters:
*     - polygon : NJS_TEXTURE_VTX list
*     - count   : NJS_TEXTURE_VTX entry count
*     - trans   : is transparent
*/
void    rjDrawTextureEx( NJS_TEXTURE_VTX* polygon, Int count, Int trans );
/*
*   Draw a multi-vertex, 2D polygon.
*
*   Examples:
*       rjDrawPolygon2D(poly, count, -1.0f, NJD_FILL | NJD_TRANSPARENT)
*
*   Parameters:
*     - p       : POINT2COL list
*     - n       : POINT2COL entry count
*     - pri     : draw priority (-1<->-65535)
*     - attr    : draw attributes
*/
void    rjDrawPolygon2D( NJS_POINT2COL* p, Sint32 n, Float pri, Uint32 attr );

/****** State ************************************************************************/
/*
*   Set Cheap Shadow opacity.
*
*   Parameters:
*     - mode    : opacity 0<->255
*/
void    rjSetCheapShadowMode( int32_t mode );

EXTERN_END

#endif/*_RF_NINJA_H_*/
