/*
*   SA2 Render Fix - '/rf_draw.h'
*
*   Description:
*       Contains useful draw functions
*
*   Contributors:
*   -   Shaddatic
*/
#ifndef _RF_DRAW_H_
#define _RF_DRAW_H_

/************************/
/*  External Headers    */
/************************/
/****** Ninja ***********************************************************************/
#include <sa2b/ninja/ninja.h>   /* ninja                                            */

/****** Utility *********************************************************************/
#include <sa2b/util/anyobj.h>   /* ANY_OBJECT                                       */

/****** Game ************************************************************************/
#include <sa2b/src/motion.h>    /* MOTION_CTRL                                      */

EXTERN_START

/************************/
/*  Functions           */
/************************/
/****** Init ************************************************************************/
/*
*   Init Render Fix 'Ninja' module
*/
void    RF_DrawInit(void);

/****** Null Draw *******************************************************************/
/*
*   Goes through the steps of drawing, such as matrix calculations, without
*   actually drawing anything.
*
*   Parameters:
*     - model   : Pointer to a Chunk model
*     - object  : Pointer to a Chunk object
*/
int     njCnkNullDrawModel(  NJS_CNK_MODEL*  model  );
void    njCnkNullDrawObject( NJS_CNK_OBJECT* object );
/*
*   Goes through the steps of animating, such as matrix calculations & calling
*   motion callbacks, without actually drawing anything.
*
*   Parameters:
*     - object      : Pointer to a Chunk object
*     - motion      : Pointer to a Ninja Motion array
*     - motion_link : Pointer to a Ninja Motion Link
*     - frame       : Frame of the motion to draw
*/
void    njCnkAnimateMotion(     NJS_CNK_OBJECT* object, NJS_MOTION*      motion,      float frame );
void    njCnkAnimateMotionLink( NJS_CNK_OBJECT* object, NJS_MOTION_LINK* motion_link, float frame );
/*
*   Null Draw SA2 motion control.
*
*   Parameters:
*     - pObject  : a Ninja object of any type
*     - pMtnCtrl : a motion control pointer
*/
void    AnimateMotion( ANY_OBJECT* pObject, MOTION_CTRL* pMtnCtrl );

/****** Modifier Volume *************************************************************/
/*
*   Draw modifier volume models and objects. Should only be called inside a
*   Tasks' 'disp_shad' (offset 0x2C) displayer function.
*
*   Parameters:
*     - model   : Pointer to a Chunk modifier volume model
*     - object  : Pointer to a Chunk modifier volume object
*/
int32_t njCnkModDrawModel(  NJS_CNK_MODEL*  model  );
void    njCnkModDrawObject( NJS_CNK_OBJECT* object );
/*
*   Draw modifier volume motions. Should only be called inside a Tasks'
*   'disp_shad' (offset 0x2C) displayer function.
*
*   Parameters:
*     - object      : Pointer to a Chunk modifier volume object
*     - motion      : Pointer to a Ninja Motion array
*     - motion_link : Pointer to a Ninja Motion Link
*     - frame       : Frame of the motion to draw
*/
void    njCnkModDrawMotion(     NJS_CNK_OBJECT* object, NJS_MOTION*      motion,      float frame );
void    njCnkModDrawMotionLink( NJS_CNK_OBJECT* object, NJS_MOTION_LINK* motion_link, float frame );

/****** Generic Shadows *************************************************************/
/*
*   Draw common modifier models.
*/
void    DrawBasicShadow( void );
void    AL_ShadowDraw(   void );

/****** Draw 2D *********************************************************************/
/*
*   Draw a multi-vertex, 2D texture.
*
*   Parameters:
*     - polygon : NJS_TEXTURE_VTX list
*     - count   : NJS_TEXTURE_VTX entry count
*     - trans   : is transparent
*/
void    rjDrawTextureEx(NJS_TEXTURE_VTX* polygon, Int count, Int trans);
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
void    rjDrawPolygon2D(NJS_POINT2COL* p, Sint32 n, Float pri, Uint32 attr);

EXTERN_END

#endif/*_RF_DRAW_H_*/
