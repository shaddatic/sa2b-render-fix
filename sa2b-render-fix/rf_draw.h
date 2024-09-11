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
#include <sa2b/sonic/motion.h>    /* MOTION_CTRL                                      */

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
int     njCnkNullDrawModel(  const NJS_CNK_MODEL*  model  );
void    njCnkNullDrawObject( const NJS_CNK_OBJECT* object );
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
void    njCnkAnimateMotion(     const NJS_CNK_OBJECT* object, const NJS_MOTION*      motion,      float frame );
void    njCnkAnimateMotionLink( const NJS_CNK_OBJECT* object, const NJS_MOTION_LINK* motion_link, float frame );
/*
*   Null Draw SA2 motion control.
*
*   Parameters:
*     - pObject  : a Ninja object of any type
*     - pMtnCtrl : a motion control pointer
*/
void    AnimateMotion( const ANY_OBJECT* pObject, const MOTION_CTRL* pMtnCtrl );

/****** Modifier Volume *************************************************************/
/*
*   Draw modifier volume models and objects. Should only be called inside a
*   Tasks' 'disp_shad' (offset 0x2C) displayer function.
*
*   Parameters:
*     - model   : Pointer to a Chunk modifier volume model
*     - object  : Pointer to a Chunk modifier volume object
*/
int32_t njCnkModDrawModel(  const NJS_CNK_MODEL*  model  );
void    njCnkModDrawObject( const NJS_CNK_OBJECT* object );
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
void    njCnkModDrawMotion(     const NJS_CNK_OBJECT* object, const NJS_MOTION*      motion,      float frame );
void    njCnkModDrawMotionLink( const NJS_CNK_OBJECT* object, const NJS_MOTION_LINK* motion_link, float frame );

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
void    rjDrawTextureEx( const NJS_TEXTURE_VTX* polygon, Int count, Int trans );
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
void    rjDrawPolygon2D( const NJS_POINT2COL* p, Sint32 n, Float pri, Uint32 attr );

/****** Draw Line *******************************************************************/
/*
*   Description:
*     Begin draw line and set draw parameters.
*
*   Parameters:
*     - r         : radius, in 480p pixels
*     - BaseColor : line color to draw (in 0xAA'RR'GG'BB format)
*     - Trans     : use transparancy
*/
void    rjDrawLineExStart( Float r, Uint32 BaseColor, Sint32 Trans );
/*
*   Description:
*     Draw 3D line in either strip or list mode.
*
*   Parameters:
*     - vtx     : list of line vertexes
*     - Count   : number of line vertexes
*/
void    rjDrawLine3DExSetStrip( const NJS_POINT3* vtx, Sint32 Count );
void    rjDrawLine3DExSetList(  const NJS_POINT3* vtx, Sint32 Count  );
/*
*   Description:
*     Draw 2D line in either strip or list mode.
*
*   Parameters:
*     - vtx     : list of line vertexes
*     - ooz     : 1/z, 'z' being the depth of the line
*     - Count   : number of line vertexes
*/
void    rjDrawLine2DExSetList(  const NJS_POINT2* vtx, Float ooz, Sint32 Count );
void    rjDrawLine2DExSetStrip( const NJS_POINT2* vtx, Float ooz, Sint32 Count );
/*
*   Description:
*     End draw line.
*/
void    rjDrawLineExEnd( void );

/****** Draw Line (Combined) ********************************************************/
/*
*   Description:
*     Draw 3D line in either strip or list mode. Internally calls the seperated line
*   draw functions
*
*   Parameters:
*     - vtx     : list of line vertexes
*     - Count   : number of line vertexes
*     - r       : radius, in 480p pixels
*     - Color   : line color to draw (in 0xAA'RR'GG'BB format)
*/
void    rjDrawLineStrip3D( const NJS_POINT3* vtx, Sint32 Count, Float r, Uint32 Color );
void    rjDrawLineList3D(  const NJS_POINT3* vtx, Sint32 Count, Float r, Uint32 Color );
/*
*   Description:
*     Draw 2D line in either strip or list mode. Internally calls the seperated line
*   draw functions
*
*   Parameters:
*     - vtx     : list of line vertexes
*     - ooz     : 1/z, 'z' being the depth of the line
*     - Count   : number of line vertexes
*     - r       : radius, in 480p pixels
*     - Color   : line color to draw (in 0xAA'RR'GG'BB format)
*/
void    rjDrawLineStrip2D( const NJS_POINT2* vtx, Float ooz, Sint32 Count, Float r, Uint32 Color );
void    rjDrawLineList2D(  const NJS_POINT2* vtx, Float ooz, Sint32 Count, Float r, Uint32 Color );

EXTERN_END

#endif/*_RF_DRAW_H_*/
