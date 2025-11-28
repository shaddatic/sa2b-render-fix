/*
*   SA2 Render Fix - '/rf_ninja.h'
*
*   Description:
*     Render Fix Ninja header.
*/
#ifndef H_RF_NINJA
#define H_RF_NINJA

/************************/
/*  External Headers    */
/************************/
/****** Ninja ***********************************************************************/
#include <samt/ninja/ninja.h>   /* ninja                                            */

/****** Utility *********************************************************************/
#include <samt/util/anyobj.h>   /* ANY_OBJECT                                       */

/****** Game ************************************************************************/
#include <samt/sonic/motion.h>  /* MOTION_CTRL                                      */

/****** Render Fix ******************************************************************/
#include <rf_njcnk.h>           /* easy, simple, etc                                */

EXTERN_START

/************************/
/*  Macros              */
/************************/
/****** Convert UV Coords ***********************************************************/
#define RJM_UVN(uv)      ((Float)(uv)*(1.f/256.f))  /* uvn to float                 */
#define RJM_UVH(uv)      ((Float)(uv)*(1.f/1024.f)) /* uvh to float                 */

/****** Chunk Control Flags *********************************************************************/
#define RJD_CNK_CTRL_OPAQUE             (1<< 0) /* draw opaque polygons                             */
#define RJD_CNK_CTRL_TRANSLUCENT        (1<< 1) /* draw translucent polygons                        */
#define RJD_CNK_CTRL_NORMAL             (1<< 2) /* draw normal polygon faces                        */
#define RJD_CNK_CTRL_INVERSE            (1<< 3) /* draw inverse polygon faces                       */
#define RJD_CNK_CTRL_VLIST              (1<< 4) /* execute vlist chunk data                         */
#define RJD_CNK_CTRL_PLIST              (1<< 5) /* execute plist chunk data                         */

#define RJD_CNK_CTRL_VNORM              (1<< 8) /* use vertex normal attributes                     */
#define RJD_CNK_CTRL_VCOLR              (1<< 9) /* use vertex color attributes                      */
#define RJD_CNK_CTRL_VSPEC              (1<<10) /* use vertex specular attributes                   */

#define RJD_CNK_CTRL_TEXTURE            (1<<12) /* use textures                                     */
#define RJD_CNK_CTRL_ENVIRONMENT        (1<<13) /* use normal-based environment calculations        */
#define RJD_CNK_CTRL_DOUBLESIDEDLIGHT   (1<<14) /* use double sided lighting when available         */

#define RJD_CNK_CTRL_MASK_DRAW      (RJD_CNK_CTRL_OPAQUE|RJD_CNK_CTRL_TRANSLUCENT)
#define RJD_CNK_CTRL_MASK_CULL      (RJD_CNK_CTRL_NORMAL|RJD_CNK_CTRL_INVERSE)
#define RJD_CNK_CTRL_MASK_MODEL     (RJD_CNK_CTRL_VLIST|RJD_CNK_CTRL_PLIST)
#define RJD_CNK_CTRL_MASK_VTX       (RJD_CNK_CTRL_VNORM|RJD_CNK_CTRL_VCOLR|RJD_CNK_CTRL_VSPEC)
#define RJD_CNK_CTRL_MASK_EFFECT    (RJD_CNK_CTRL_TEXTURE|RJD_CNK_CTRL_ENVIRONMENT|RJD_CNK_CTRL_DOUBLESIDEDLIGHT)

#define RJD_CNK_CTRL_MASK           (RJD_CNK_CTRL_MASK_DRAW|RJD_CNK_CTRL_MASK_CULL|RJD_CNK_CTRL_MASK_MODEL|RJD_CNK_CTRL_MASK_VTX|RJD_CNK_CTRL_MASK_EFFECT)

/****** Chunk Strip flags ***********************************************************************/
#define RJD_FST_EUA                 (NJD_FST_NAT)            /* extended use alpha              */

/************************/
/*  Extern Data         */
/************************/
/****** Depth Queue *****************************************************************************/
EXTERN Float _rj_depth_queue_near_; /* depth queue near plane                                   */
EXTERN Float _rj_depth_queue_far_;  /* depth queue far plane                                    */

/************************/
/*  Functions           */
/************************/
/****** Null Draw *******************************************************************/
/*
*   Description:
*     Emulates a successful Chunk draw, but doesn't actually draw anything.
* 
*   Parameters:
*     - model   : chunk model
*
*   Returns:
*     Always '0' as if model was drawn.
*/
Sint32  njCnkNullDrawModel( const NJS_CNK_MODEL* model );
/*
*   Description:
*     Goes through the steps of drawing, such as matrix transformations, without
*   actually drawing anything.
*
*   Parameters:
*     - object  : chunk object
*/
void    njCnkNullDrawObject( const NJS_CNK_OBJECT* object );
/*
*   Description:
*     Goes through the steps of animating, such as matrix calculations & calling
*   motion callbacks, without actually drawing anything.
*
*   Parameters:
*     - object      : chunk object to animate
*     - motion      : motion data for 'object'
*     - frame       : frame of animation
*/
void    njCnkAnimateMotion( const NJS_CNK_OBJECT* object, const NJS_MOTION* motion, Float frame );
/*
*   Description:
*     Goes through the steps of animating, such as interpolating the motions, matrix
*   calculations, & calling motion callbacks, without actually drawing anything.
*
*   Parameters:
*     - object      : chunk object to animate
*     - motion_link : motion link data and motion datas for 'object'
*     - rate        : ratio of transition from motion 1 to motion 2 (0~1)
*/
void    njCnkAnimateMotionLink( const NJS_CNK_OBJECT* object, const NJS_MOTION_LINK* motion_link, Float rate );
/*
*   Description:
*     Animate an SA2 motion control without actually drawing anything.
*
*   Parameters:
*     - pObject  : a Ninja object of any type
*     - pMtnCtrl : a motion control pointer
*/
void    AnimateMotion( const ANY_OBJECT* pObject, const MOTION_CTRL* pMtnCtrl );

/************************************************************************************/
/*
*   Chunk Modifier Volume
*
*   Notes:
*     - Modifiers should only be drawn inside the 'disp_shad' (offset 0x2C) task
*       displayer function.
*/

/****** Modifier Volume *************************************************************/
/*
*   Description:
*     Draw a Chunk modifier volume model.
*
*   Parameters:
*     - model       : chunk modifier volume model
*
*   Returns:
*     '0' if drawn, or '-1' if the model was clipped.
*/
Sint32  njCnkModDrawModel( const NJS_CNK_MODEL* model );
/*
*   Description:
*     Draw a modifier volume object tree.
*
*   Parameters:
*     - object      : chunk modifier volume object
*/
void    njCnkModDrawObject( const NJS_CNK_OBJECT* object );
/*
*   Description:
*     Draw a Chunk modifier volume motion.
*
*   Parameters:
*     - object      : object to animate and draw
*     - motion      : motion data for 'object'
*     - frame       : frame of animation
*/
void    njCnkModDrawMotion( const NJS_CNK_OBJECT* object, const NJS_MOTION* motion, Float frame );
/*
*   Description:
*     Interpolate and draw two Chunk modifier volume motions.
*
*   Parameters:
*     - object      : chunk modifier volume object to animate
*     - motion_link : motion link data and motion datas for 'object'
*     - rate        : ratio of transition from motion 1 to motion 2 (0~1)
*/
void    njCnkModDrawMotionLink( const NJS_CNK_OBJECT* object, const NJS_MOTION_LINK* motion_link, Float frame );
/*
*   Description:
*     Draw a Chunk modifier volume motion.
*
*   Parameters:
*     - object      : object to animate and draw
*     - motion      : motion data for 'object'
*     - shape       : shape data for 'object'   (optional)
*     - frame       : frame of animation/shape
*/
void    rjCnkModDrawShapeMotion( const NJS_CNK_OBJECT* object, const NJS_MOTION* motion, const NJS_MOTION* shape, Float frame );
/*
*   Description:
*     Interpolate and draw two Chunk modifier volume motions.
*
*   Parameters:
*     - object      : object to animate and draw
*     - motion_link : motion data for 'object'
*     - shape_link  : shape data for 'object'   (optional)
*     - rate        : ratio of transition from motion/shape 1 to motion/shape 2 (0~1)
*/
void    rjCnkModDrawShapeMotionLink( const NJS_CNK_OBJECT* object, const NJS_MOTION_LINK* motion_link, const NJS_MOTION_LINK* shape_link, Float rate );
/*
*   Description:
*     Draw a Chunk modifier volume motion.
*
*   Parameters:
*     - object      : object to animate and draw
*     - motion      : motion data for 'object'
*     - shape       : shape data for 'object'   (optional)
*     - frame       : frame of animation/shape
*/
void    rjCnkModDrawShapeMotionBE( const NJS_CNK_OBJECT* object, const NJS_MOTION* motion, const NJS_MOTION* shape, Float frame );
/*
*   Description:
*     Interpolate and draw two Chunk modifier volume motions.
*
*   Parameters:
*     - object      : object to animate and draw
*     - motion_link : motion data for 'object'
*     - shape_link  : shape data for 'object'   (optional)
*     - rate        : ratio of transition from motion/shape 1 to motion/shape 2 (0~1)
*/
void    rjCnkModDrawShapeMotionLinkBE( const NJS_CNK_OBJECT* object, const NJS_MOTION_LINK* motion_link, const NJS_MOTION_LINK* shape_link, Float rate );

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

/****** Polygon *********************************************************************/
/*
*   Draw a multi-vertex polygon.
*
*   Parameters:
*     - polygon : polygon vertex list
*     - count   : polygon vertex count
*     - trans   : is transparent
*/
void    rjDrawPolygon( const NJS_POLYGON_VTX* polygon, Int count, Int trans );
/*
*   Draw a multi-vertex textured polygon.
*
*   Parameters:
*     - polygon     : polygon vertex list
*     - count       : polygon vertex count
*     - tex         : gbix value of texture to draw
*     - flag        : transparency flag
*/
void    rjDrawTexture( const NJS_TEXTURE_VTX* polygon, Int count, Int tex, Int flag );

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

/************************************************************************************/
/*
*   RF Chunk Draw
*/
/****** Chunk Control ***************************************************************/
/*
*   Description:
*     Set/unset Chunk draw control flags.
*
*   Parameters:
*     - off_flag    : flags to be turned off/and'd
*     - on_flag     : flags to be turned on/or'd
*/
void    rjCnkSetControl( Uint32 off_flag, Uint32 on_flag );
/*
*   Description:
*     Get the current Chunk draw control flags.
*/
Uint32  rjCnkGetControl( void );

/****** Chunk Draw ******************************************************************/
/*
*   Description:
*     Draw a Chunk model.
*
*   Parameters:
*     - model       : chunk model pointer
*
*   Returns:
*     '0' if drawn, or '-1' if the model was clipped.
*/
Sint32  rjCnkDrawModel( const NJS_CNK_MODEL* model );
/*
*   Description:
*     Draw a Chunk object tree.
*
*   Parameters:
*     - object      : chunk object
*/
void    rjCnkDrawObject( const NJS_CNK_OBJECT* object );

/****** Chunk Draw Motion ***********************************************************/
/*
*   Description:
*     Draw a Chunk motion.
*
*   Parameters:
*     - object      : object to animate and draw
*     - motion      : motion data for 'object'
*     - frame       : frame of animation
*/
void    rjCnkDrawMotion( const NJS_CNK_OBJECT* object, const NJS_MOTION* motion, Float frame );
/*
*   Description:
*     Interpolate and draw two Chunk motions.
*
*   Parameters:
*     - object      : object to animate and draw
*     - motion_link : motion link data and motion datas for 'object'
*     - rate        : ratio of transition from motion 1 to motion 2 (0~1)
*/
void    rjCnkDrawMotionLink( const NJS_CNK_OBJECT* object, const NJS_MOTION_LINK* motion_link, Float rate );

/****** Chunk Draw Shape ***********************************************************/
/*
*   Description:
*     Draw a Chunk shape motion.
*
*   Parameters:
*     - object      : object to animate and draw
*     - motion      : motion data for 'object'
*     - shape       : shape data for 'object'   (optional)
*     - frame       : frame of animation/shape
*/
void    rjCnkDrawShapeMotion( const NJS_CNK_OBJECT* object, const NJS_MOTION* motion, const NJS_MOTION* shape, Float frame );
/*
*   Description:
*     Interpolate and draw two Chunk shape motions.
*
*   Parameters:
*     - object      : object to animate and draw
*     - motion_link : motion data for 'object'
*     - shape_link  : shape data for 'object'   (optional)
*     - rate        : ratio of transition from motion/shape 1 to motion/shape 2 (0~1)
*/
void    rjCnkDrawShapeMotionLink( const NJS_CNK_OBJECT* object, const NJS_MOTION_LINK* motion_link, const NJS_MOTION_LINK* shape_link, Float rate );

/****** Chunk Draw Shape BE *********************************************************/
/*
*   Description:
*     Draw a big endian Chunk shape motion.
*
*   Notes:
*     - The 'motion' data is still little endian
*
*   Parameters:
*     - object      : object to animate and draw
*     - motion      : motion data for 'object'
*     - shape       : shape data for 'object'   (optional)
*     - frame       : frame of animation/shape
*/
void    rjCnkDrawShapeMotionBE( const NJS_CNK_OBJECT* object, const NJS_MOTION* motion, const NJS_MOTION* shape, Float frame );
/*
*   Description:
*     Interpolate and draw two big endian Chunk shape motions.
*
*   Notes:
*     - The 'motion_link' data is still little endian
*
*   Parameters:
*     - object      : object to animate and draw
*     - motion_link : motion data for 'object'
*     - shape_link  : shape data for 'object'   (optional)
*     - rate        : ratio of transition from motion/shape 1 to motion/shape 2 (0~1)
*/
void    rjCnkDrawShapeMotionLinkBE( const NJS_CNK_OBJECT* object, const NJS_MOTION_LINK* motion_link, const NJS_MOTION_LINK* shape_link, Float rate );

/****** Chunk Modify ****************************************************************/
/*
*   Description:
*     Set the Chunk UV offset value for regular UVs, for texture scrolling.
*
*   Notes:
*     - This is a Render Fix extension, and is not part of base Ninja.
*     - This will *not* affect environment maps.
*     - Reset these values to '0.f' when drawing is complete.
*
*   Parameters:
*     - u, v        : u and v scroll offset
*/
void    rjCnkSetUvScroll( Float u, Float v );
/*
*   Description:
*     Set the Chunk UV offset value for environment mapping, for texture scrolling.
*   Scrolling applies when 'NJD_CONTROL_3D_ENV_UV_SCROLL' is set.
*
*   Notes:
*     - In base Ninja this is named 'njCnkSetUvScroll', but the functionality is
*     otherwise the same.
*     - Reset these values to '0.f' when drawing is complete.
*     - Currently only applies to normal-less environment maps, as they aren't
*     calculated in-shader.
*
*   Parameters:
*     - u, v        : u and v scroll offset
*/
void    rjCnkSetEnvUvScroll( Float u, Float v );

/****** Chunk Callback **************************************************************************/
/*
*   Description:
*     Set the Chunk object callback function.
*
*   Notes:
*     - This is a Render Fix extension, and is not part of base Ninja.
*     - Called for every object drawn using 'CnkDrawObject'.
*     - Reset the callback to 'NULL' when drawing is complete.
* 
*   Parameters:
*     - callback        : object callback function                               [opt: nullptr]
*       - object        : callback object pointer
*/
void    rjCnkSetObjectCallback( void(__cdecl* callback)(NJS_CNK_OBJECT* object) );
/*
*   Description:
*     Set the Chunk motion callback function.
*
*   Notes:
*     - Called for every object drawn using 'CnkDrawMotion' or its variants.
*     - Reset the callback to 'NULL' when drawing is complete.
* 
*   Parameters:
*     - callback        : object callback function                               [opt: nullptr]
*       - object        : callback object pointer
*/
void    rjCnkSetMotionCallback( void(__cdecl* callback)(NJS_CNK_OBJECT* object) );
/*
*   Description:
*     Set the Chunk model callback function.
*
*   Notes:
*     - This is a Render Fix extension, and is not part of base Ninja.
*     - Called for every NON-CLIPPED model drawn using any draw function.
*     - Reset the callback to 'NULL' when drawing is complete.
* 
*   Parameters:
*     - callback        : model callback function                                [opt: nullptr]
*       - model         : callback model pointer
*/
void    rjCnkSetModelCallback( void(__cdecl* callback)(NJS_CNK_MODEL* model) );

/****** Chunk Plist Callback ********************************************************************/
/*
*   Description:
*     Set the texture ID callback function, for texture animation.
*
*   Notes:
*     - This is a Render Fix extension, and is not part of base Ninja.
*     - The returned value will be used as the new texid.
*     - Called for every 'tiny' chunk data in a drawn model.
*     - Reset the callback to 'NULL' when drawing is complete.
*     - See 'rjCnkGetTextureNum' for callback example
*
*   Parameters:
*     - callback        : texture callback function                              [opt: nullptr]
*       - n             : texture index
*       + return        : new texture index
*/
void    rjCnkSetTextureCallback( Sint16(__cdecl* callback)(Sint16 n) );
/*
*   Description:
*     Set the Chunk material callback function, for changing material colors at draw time.
*
*   Notes:
*     - This is a Render Fix extension, and is not part of base Ninja.
*     - The returned flags determines what colors will be applied to the model
*     - Called for every 'material' chunk data in a drawn model.
*     - Reset the callback to 'NULL' when drawing is complete.
*     - See 'rjCnkGetMaterial' for callback example
*
*   Parameters:
*     - callback        : material callback function                             [opt: nullptr]
*       - dst           : destination material color array                          [RJ_CMC_##]
*       - src           : source material color array                               [RJ_CMC_##]
*       - flag          : material color flags in this material chunk               [RJ_CMF_##]
*       + return        : output material color flags, for adding material colors   [RJ_CMF_##]
*/
void    rjCnkSetMaterialCallback( Uint32(__cdecl* callback)(NJS_BGRA* dst, const NJS_BGRA* src, Uint32 flag) );

/****** Cheap Shadow ****************************************************************/
/*
*   Description:
*     Set the intensity of modifier shadows, also called cheap shadows. The value
*   is divided by '256' and multiplied with the pixel color. For example, a value
*   of '0' would result in a fully black pixel and a value of '256' would result in
*   no change - or in other words cheap shadows would be disabled.
*
*   Notes:
*     - Only one intensity can be used across a single scene. In other words, all
*       shadows will use the same value across a single frame.
*     - The original Ninja version only supported values up to '255'
*
*   Parameters:
*     - mode        : cheap shadow intensity                                [0~256]
*/
void    rjSetCheapShadowMode( Int mode );
/*
*   Description:
*     Set the color of modifier shadows, also called cheap shadows.  The color is
*   additive, and multiplied by the intensity.
*
*   Notes:
*     - The default color is black, or ( 0.f, 0.f, 0.f').
*     - Only one color can be used across a single scene. In other words, all
*       shadows will use the same color across a single frame.
*     - This is a Render Fix extension, and was not available in Ninja.
*
*   Parameters:
*     - r, g, b     : cheap shadow color                                      [0~1]
*/
void    rjSetCheapShadowColor( Float r, Float g, Float b );
/*
*   Description:
*     Enable or disable the Cheap Shadow debug mode, which draws modifier shadows as full
*   models and skips stencil logic.
*
*   Parameters:
*     - mode    : cheap shadow debug mode                                              [ON/OFF]
*/
void    rjCheapShadowDebug( Bool mode );

/*
*   Description:
*     Draw the current modifier buffer to the screen.
*/
void    rjDrawCheapShadow( void );

/****** Reset Modifier Buffer *******************************************************************/
/*
*   Description:
*     Clear the modifier buffer for a new frame.
*/
void    rjModifierResetBuffer( void );

/****** Wait Vsync Count ************************************************************************/
/*
*   Description:
*     Set the number of vsync frames to wait before starting a new frame.
*
*   Parameters:
*     - count       : vsync wait frames (1 = 60fps, 2 = 30fps, etc)
*/
void    rjSetWaitVsyncCount( Sint32 count );
/*
*   Description:
*     Get the current vsync wait count.
*/
Sint32  rjGetWaitVsyncCount( void );

EXTERN_END

#endif/*H_RF_NINJA*/
