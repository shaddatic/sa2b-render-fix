/*
*   SA2 Render Fix - '/rfapi_draw.h'
*
*   Description:
*     The 'Draw' API module is for drawing polygons, modifiers, or models to the screen.
* 
*   Version History:
*     - v1.3.0.0        : Version 0, initial release
*     - v1.3.1.0        : Version 1, added 'DrawTextureEx' & 'DrawPolygon2D'
*     - v1.3.2.0        : Version 2, added 'DrawLine' function set
*     - v1.4.0.0        : Version 3, added additional modifier and Chunk related functions
*     - v1.4.0.1        : Version 4, added 'SetCheapShadowColor'
*     - v1.5.0.0        : Version 5, most functions were depricated - although many are still
*                         fully functional, there's just a newer way to access them now.
* 
*   Availability:
*     - Before Init     : No
*     - At Init         : Yes
*     - After Init      : Yes
*/
#ifndef H_RFAPI_DRAW
#define H_RFAPI_DRAW

/********************************/
/*  Constants                   */
/********************************/
/****** API Module Version **********************************************************************/
#define RFAPI_DRAW_VER              (5) /* draw api version                                     */

/********************************/
/*  API Structures              */
/********************************/
/****** Draw API ********************************************************************************/
typedef struct
{
    uint32_t version;               /* structure version                                        */

    /****** Version >= 0 ************************************************************************/

    /**** Null Draw/Animate Motion **************************/
    /*
    *   [[ DEPRICATED : Version 5 ]]
    * 
    *   Deprication Info:
    *     - state           : non-functional, no-op
    *     - reason          : very little usage with major internal changes
    *     - alternative     : make your own if needed
    * 
    *   Description:
    *     Emulates a successful Chunk draw, but doesn't actually draw anything.
    * 
    *   Parameters:
    *     - model   : chunk model
    *
    *   Returns:
    *     Always '0' as if model was drawn.
    */
    Sint32 (__cdecl* CnkNullDrawModel)( const NJS_CNK_MODEL* model );
    /*
    *   [[ DEPRICATED : Version 5 ]]
    * 
    *   Deprication Info:
    *     - state           : non-functional, no-op
    *     - reason          : very little usage with major internal changes
    *     - alternative     : make your own if needed
    * 
    *   Description:
    *     Goes through the steps of drawing, such as matrix transformations, without
    *   actually drawing anything.
    *
    *   Parameters:
    *     - object  : chunk object
    */
    void (__cdecl* CnkNullDrawObject)( const NJS_CNK_OBJECT* object );
    /*
    *   [[ DEPRICATED : Version 5 ]]
    * 
    *   Deprication Info:
    *     - state           : non-functional, no-op
    *     - reason          : very little usage with major internal changes
    *     - alternative     : make your own if needed
    * 
    *   Description:
    *     Goes through the steps of animating, such as matrix calculations & calling
    *   motion callbacks, without actually drawing anything.
    *
    *   Parameters:
    *     - object      : chunk object to animate
    *     - motion      : motion data for 'object'
    *     - frame       : frame of animation
    */
    void (__cdecl* CnkAnimateMotion)( const NJS_CNK_OBJECT* object, NJS_MOTION* motion, Float frame );
    /*
    *   [[ DEPRICATED : Version 5 ]]
    * 
    *   Deprication Info:
    *     - state           : non-functional, no-op
    *     - reason          : very little usage with major internal changes
    *     - alternative     : make your own if needed
    * 
    *   Description:
    *     Goes through the steps of animating, such as interpolating the motions, matrix
    *   calculations, & calling motion callbacks, without actually drawing anything.
    *
    *   Parameters:
    *     - object      : chunk object to animate
    *     - motion_link : motion link data and motion datas for 'object'
    *     - rate        : ratio of transition from motion 1 to motion 2 (0~1)
    */
    void (__cdecl* CnkAnimateMotionLink)( const NJS_CNK_OBJECT* object, NJS_MOTION_LINK* motion_link, Float rate );

    /********************************************************/
    /*
    *   Chunk Modifier Volume
    *
    *   Notes:
    *     - Modifiers should only be drawn inside the 'disp_shad' (offset 0x2C) task
    *       displayer function.
    */

    /**** Modifier Draw *************************************/
    /*
    *   [[ DEPRICATED : Version 5 ]]
    * 
    *   Deprication Info:
    *     - state           : fully functional
    *     - reason          : there's now a dedicated 'Chunk' API module
    *     - alternative     : use the 'Chunk' API module instead
    * 
    *   Description:
    *     Draw a Chunk modifier volume model.
    *
    *   Parameters:
    *     - model       : chunk modifier volume model
    *
    *   Returns:
    *     '0' if drawn, or '-1' if the model was clipped.
    */
    Sint32 (__cdecl* CnkModDrawModel)( NJS_CNK_MODEL* model );
    /*
    *   [[ DEPRICATED : Version 5 ]]
    * 
    *   Deprication Info:
    *     - state           : fully functional
    *     - reason          : there's now a dedicated 'Chunk' API module
    *     - alternative     : use the 'Chunk' API module instead
    * 
    *   Description:
    *     Draw a modifier volume object tree.
    *
    *   Parameters:
    *     - object      : chunk modifier volume object
    */
    void (__cdecl* CnkModDrawObject)( NJS_CNK_OBJECT* object );
    /*
    *   [[ DEPRICATED : Version 5 ]]
    * 
    *   Deprication Info:
    *     - state           : fully functional
    *     - reason          : there's now a dedicated 'Chunk' API module
    *     - alternative     : use the 'Chunk' API module instead
    * 
    *   Description:
    *     Draw a Chunk modifier volume motion.
    *
    *   Parameters:
    *     - object      : object to animate and draw
    *     - motion      : motion data for 'object'
    *     - frame       : frame of animation
    */
    void (__cdecl* CnkModDrawMotion)( NJS_CNK_OBJECT* object, NJS_MOTION* motion, Float frame );
    /*
    *   [[ DEPRICATED : Version 5 ]]
    * 
    *   Deprication Info:
    *     - state           : non-functional, no-op
    *     - reason          : very little usage with major internal changes
    *     - alternative     : create your own using the 'Chunk' API module
    * 
    *   Description:
    *     Interpolate and draw two Chunk modifier volume motions.
    *
    *   Parameters:
    *     - object      : chunk modifier volume object to animate
    *     - motion_link : motion link data and motion datas for 'object'
    *     - rate        : ratio of transition from motion 1 to motion 2 (0~1)
    */
    void (__cdecl* CnkModDrawMotionLink)( NJS_CNK_OBJECT* object, NJS_MOTION_LINK* motion_link, Float rate );

    /**** Modifier Common Draw ******************************/
    /*
    *   Description:
    *     Draw common modifier models.
    */
    void (__cdecl* DrawBasicShadow)( void );
    void (__cdecl* AL_ShadowDraw)( void );

    /****** Version >= 1 ************************************************************/

    /********************************************************/
    /*
    *   2D Draw
    */
    /********************************************************/
    /*
    *   [[ DEPRICATED : Version 5 ]]
    * 
    *   Deprication Info:
    *     - state           : fully functional
    *     - reason          : there's now a dedicated 'Ninja Draw' API module
    *     - alternative     : use the 'Ninja Draw' API module instead
    * 
    *   Description:
    *     Draw a multi-vertex, 2D texture with 'count'.
    *
    *   Parameters:
    *     - polygon : NJS_TEXTURE_VTX list
    *     - count   : number of entries in 'polygon'
    *     - trans   : is transparent
    */
    void (__cdecl* DrawTextureEx)(const NJS_TEXTURE_VTX* polygon, Int count, Int trans);
    /*
    *   [[ DEPRICATED : Version 5 ]]
    * 
    *   Deprication Info:
    *     - state           : fully functional
    *     - reason          : there's now a dedicated 'Ninja Draw' API module
    *     - alternative     : use the 'Ninja Draw' API module instead
    * 
    *   Description:
    *     Draw a multi-vertex, 2D polygon with 'n'.
    *
    *   Examples:
    *     - p->DrawPolygon2D(poly, count, -1.0f, NJD_FILL|NJD_TRANSPARENT)
    *
    *   Parameters:
    *     - p       : POINT2COL list
    *     - n       : number of entries in 'p'
    *     - pri     : draw priority (-1<->-65535)
    *     - attr    : draw attributes
    */
    void (__cdecl* DrawPolygon2D)(const NJS_POINT2COL* p, Sint32 n, Float pri, Uint32 attr);

    /****** Version >= 2 ************************************************************/

    /********************************************************/
    /*
    *   Draw Line (2D/3D)
    */
    /********************************************************/
    /*
    *   [[ DEPRICATED : Version 5 ]]
    * 
    *   Deprication Info:
    *     - state           : fully functional
    *     - reason          : there's now a dedicated 'Ninja Draw' API module
    *     - alternative     : use the 'Ninja Draw' API module instead
    * 
    *   Description:
    *     Draw a 3D line in either strip or list mode. 'Strip' will use the end
    *   vertex of the last line as the start vertex of the next line; 'List' will
    *   draw each pair of vertexes as seperate lines. Eg:
    *
    *     - Strip: (0, 1), (1, 2), (2, 3), ...
    *     - List : (0, 1), (2, 3), (4, 5), ...
    *
    *   Parameters:
    *     - vtx     : list of line vertexes
    *     - Count   : number of line vertexes
    *     - r       : radius, in 480p pixels
    *     - Color   : line color to draw (in 0xAA'RR'GG'BB format)
    */
    void (__cdecl* DrawLineStrip3D)( const NJS_POINT3* vtx, Sint32 Count, Float r, Uint32 Color );
    void (__cdecl* DrawLineList3D)(  const NJS_POINT3* vtx, Sint32 Count, Float r, Uint32 Color );
    /*
    *   [[ DEPRICATED : Version 5 ]]
    * 
    *   Deprication Info:
    *     - state           : fully functional
    *     - reason          : there's now a dedicated 'Ninja Draw' API module
    *     - alternative     : use the 'Ninja Draw' API module instead
    * 
    *   Description:
    *     Draw a 2D line in either strip or list mode. 'Strip' will use the end
    *   vertex of the last line as the start vertex of the next line; 'List' will
    *   draw each pair of vertexes as seperate lines. Eg:
    *
    *     - Strip: (0, 1), (1, 2), (2, 3), ...
    *     - List : (0, 1), (2, 3), (4, 5), ...
    *
    *   Parameters:
    *     - vtx     : list of line vertexes
    *     - ooz     : 1/z, 'z' being the depth of the line
    *     - Count   : number of line vertexes
    *     - r       : radius, in 480p pixels
    *     - Color   : line color to draw (in 0xAA'RR'GG'BB format)
    */
    void (__cdecl* DrawLineStrip2D)( const NJS_POINT2* vtx, Float ooz, Sint32 Count, Float r, Uint32 Color );
    void (__cdecl* DrawLineList2D)(  const NJS_POINT2* vtx, Float ooz, Sint32 Count, Float r, Uint32 Color );

    /****** Version >= 3 ************************************************************/

    /********************************************************/
    /*
    *   Chunk Modifier Volume (pt. 2)
    *
    *   Notes:
    *     - Modifiers should only be drawn inside the 'disp_shad' (offset 0x2C) task
    *       displayer function.
    */
    /**** Modifier Draw Shape Motion ************************/
    /*
    *   [[ DEPRICATED : Version 5 ]]
    * 
    *   Deprication Info:
    *     - state           : non-functional, no-op
    *     - reason          : very little usage with major internal changes
    *     - alternative     : create your own using the 'Chunk' API module
    * 
    *   Description:
    *     Draw a Chunk modifier volume motion.
    *
    *   Parameters:
    *     - object      : object to animate and draw
    *     - motion      : motion data for 'object'
    *     - shape       : shape data for 'object'   (optional)
    *     - frame       : frame of animation/shape
    */
    void (__cdecl* CnkModDrawShapeMotion)( NJS_CNK_OBJECT* object, NJS_MOTION* motion, NJS_MOTION* shape, Float frame );
    /*
    *   [[ DEPRICATED : Version 5 ]]
    * 
    *   Deprication Info:
    *     - state           : non-functional, no-op
    *     - reason          : very little usage with major internal changes
    *     - alternative     : create your own using the 'Chunk' API module
    * 
    *   Description:
    *     Interpolate and draw two Chunk modifier volume motions.
    *
    *   Parameters:
    *     - object      : object to animate and draw
    *     - motion_link : motion data for 'object'
    *     - shape_link  : shape data for 'object'   (optional)
    *     - rate        : ratio of transition from motion/shape 1 to motion/shape 2 (0~1)
    */
    void (__cdecl* CnkModDrawShapeMotionLink)( NJS_CNK_OBJECT* object, NJS_MOTION_LINK* motion_link, NJS_MOTION_LINK* shape_link, Float rate );
    /*
    *   [[ DEPRICATED : Version 5 ]]
    * 
    *   Deprication Info:
    *     - state           : non-functional, no-op
    *     - reason          : very little usage with major internal changes
    *     - alternative     : create your own using the 'Chunk' API module
    * 
    *   Description:
    *     Draw a Chunk modifier volume motion.
    *
    *   Parameters:
    *     - object      : object to animate and draw
    *     - motion      : motion data for 'object'
    *     - shape       : shape data for 'object'   (optional)
    *     - frame       : frame of animation/shape
    */
    void (__cdecl* CnkModDrawShapeMotionBE)( NJS_CNK_OBJECT* object, NJS_MOTION* motion, NJS_MOTION* shape, Float frame );
    /*
    *   [[ DEPRICATED : Version 5 ]]
    * 
    *   Deprication Info:
    *     - state           : non-functional, no-op
    *     - reason          : very little usage with major internal changes
    *     - alternative     : create your own using the 'Chunk' API module
    * 
    *   Description:
    *     Interpolate and draw two Chunk modifier volume motions.
    *
    *   Parameters:
    *     - object      : object to animate and draw
    *     - motion_link : motion data for 'object'
    *     - shape_link  : shape data for 'object'   (optional)
    *     - rate        : ratio of transition from motion/shape 1 to motion/shape 2 (0~1)
    */
    void (__cdecl* CnkModDrawShapeMotionLinkBE)( NJS_CNK_OBJECT* object, NJS_MOTION_LINK* motion_link, NJS_MOTION_LINK* shape_link, Float rate );

    /********************************************************/
    /*
    *   Chunk Draw
    */
    /**** Chunk Draw ****************************************/
    /*
    *   [[ DEPRICATED : Version 5 ]]
    * 
    *   Deprication Info:
    *     - state           : fully functional
    *     - reason          : there's now a dedicated 'Chunk' API module
    *     - alternative     : use the 'Chunk' API module instead
    * 
    *   Description:
    *     Draw a Chunk model.
    *
    *   Parameters:
    *     - model       : chunk model pointer
    *
    *   Returns:
    *     '0' if drawn, or '-1' if the model was clipped.
    */
    Sint32 (__cdecl* CnkDrawModel)( NJS_CNK_MODEL* model );
    /*
    *   [[ DEPRICATED : Version 5 ]]
    * 
    *   Deprication Info:
    *     - state           : fully functional
    *     - reason          : there's now a dedicated 'Chunk' API module
    *     - alternative     : use the 'Chunk' API module instead
    * 
    *   Description:
    *     Draw a Chunk object tree.
    *
    *   Parameters:
    *     - object      : chunk object
    */
    void (__cdecl* CnkDrawObject)( NJS_CNK_OBJECT* object );

    /**** Chunk Draw Motion *********************************/
    /*
    *   [[ DEPRICATED : Version 5 ]]
    * 
    *   Deprication Info:
    *     - state           : fully functional
    *     - reason          : there's now a dedicated 'Chunk' API module
    *     - alternative     : use the 'Chunk' API module instead
    * 
    *   Description:
    *     Draw a Chunk motion.
    *
    *   Parameters:
    *     - object      : object to animate and draw
    *     - motion      : motion data for 'object'
    *     - frame       : frame of animation
    */
    void (__cdecl* CnkDrawMotion)( NJS_CNK_OBJECT* object, NJS_MOTION* motion, Float frame );
    /*
    *   [[ DEPRICATED : Version 5 ]]
    * 
    *   Deprication Info:
    *     - state           : fully functional
    *     - reason          : there's now a dedicated 'Chunk' API module
    *     - alternative     : use the 'Chunk' API module instead
    * 
    *   Description:
    *     Interpolate and draw two Chunk motions.
    *
    *   Parameters:
    *     - object      : object to animate and draw
    *     - motion_link : motion link data and motion datas for 'object'
    *     - rate        : ratio of transition from motion 1 to motion 2 (0~1)
    */
    void (__cdecl* CnkDrawMotionLink)( NJS_CNK_OBJECT* object, NJS_MOTION_LINK* motion_link, Float rate );

    /**** Chunk Draw Shape Motion ***************************/
    /*
    *   [[ DEPRICATED : Version 5 ]]
    * 
    *   Deprication Info:
    *     - state           : fully functional
    *     - reason          : there's now a dedicated 'Chunk' API module
    *     - alternative     : use the 'Chunk' API module instead
    * 
    *   Description:
    *     Draw a Chunk shape motion.
    *
    *   Parameters:
    *     - object      : object to animate and draw
    *     - motion      : motion data for 'object'
    *     - shape       : shape data for 'object'   (optional)
    *     - frame       : frame of animation/shape
    */
    void (__cdecl* CnkDrawShapeMotion)( NJS_CNK_OBJECT* object, NJS_MOTION* motion, NJS_MOTION* shape, Float frame );
    /*
    *   [[ DEPRICATED : Version 5 ]]
    * 
    *   Deprication Info:
    *     - state           : fully functional
    *     - reason          : there's now a dedicated 'Chunk' API module
    *     - alternative     : use the 'Chunk' API module instead
    * 
    *   Description:
    *     Interpolate and draw two Chunk shape motions.
    *
    *   Parameters:
    *     - object      : object to animate and draw
    *     - motion_link : motion data for 'object'
    *     - shape_link  : shape data for 'object'   (optional)
    *     - rate        : ratio of transition from motion/shape 1 to motion/shape 2 (0~1)
    */
    void (__cdecl* CnkDrawShapeMotionLink)( NJS_CNK_OBJECT* object, NJS_MOTION_LINK* motion_link, NJS_MOTION_LINK* shape_link, Float rate );

    /**** Chunk Draw Shape Motion (Big Endian) **************/
    /*
    *   [[ DEPRICATED : Version 5 ]]
    * 
    *   Deprication Info:
    *     - state           : fully functional
    *     - reason          : there's now a dedicated 'Chunk' API module
    *     - alternative     : use the 'Chunk' API module instead
    * 
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
    void (__cdecl* CnkDrawShapeMotionBE)( NJS_CNK_OBJECT* object, NJS_MOTION* motion, NJS_MOTION* shape, Float frame );
    /*
    *   [[ DEPRICATED : Version 5 ]]
    * 
    *   Deprication Info:
    *     - state           : fully functional
    *     - reason          : there's now a dedicated 'Chunk' API module
    *     - alternative     : use the 'Chunk' API module instead
    * 
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
    void (__cdecl* CnkDrawShapeMotionLinkBE)( NJS_CNK_OBJECT* object, NJS_MOTION_LINK* motion_link, NJS_MOTION_LINK* shape_link, Float rate );

    /**** Chunk Modify **************************************/
    /*
    *   [[ DEPRICATED : Version 5 ]]
    * 
    *   Deprication Info:
    *     - state           : fully functional
    *     - reason          : there's now a dedicated 'Chunk' API module
    *     - alternative     : use the 'Chunk' API module instead
    * 
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
    void (__cdecl* CnkSetUvScroll)( Float u, Float v );
    /*
    *   [[ DEPRICATED : Version 5 ]]
    * 
    *   Deprication Info:
    *     - state           : fully functional
    *     - reason          : there's now a dedicated 'Chunk' API module
    *     - alternative     : use the 'Chunk' API module instead
    * 
    *   Description:
    *     Set the Chunk UV offset value for environment mapping, for texture
    *   scrolling. Scrolling applies when 'NJD_CONTROL_3D_ENV_UV_SCROLL' is set.
    *
    *   Notes:
    *     - In base Ninja this is named 'njCnkSetUvScroll', but the functionality
    *     is otherwise the same.
    *     - Reset these values to '0.f' when drawing is complete.
    *     - Currently only applies to normal-less environment maps, as they aren't
    *     calculated in-shader.
    *
    *   Parameters:
    *     - u, v        : u and v scroll offset
    */
    void (__cdecl* CnkSetEnvUvScroll)( Float u, Float v );
    /*
    *   [[ DEPRICATED : Version 5 ]]
    * 
    *   Deprication Info:
    *     - state           : fully functional
    *     - reason          : there's now a dedicated 'Chunk' API module
    *     - alternative     : use the 'Chunk' API module instead
    * 
    *   Description:
    *     Set the texture ID callback function, for texture animation.
    *
    *   Notes:
    *     - This is a Render Fix extension, and is not part of base Ninja.
    *     - The returned value will be used as the new texid.
    *     - Reset the callback to 'NULL' when drawing is complete.
    *
    *   Parameters:
    *     - callback    : texture callback function
    */
    void (__cdecl* CnkSetTextureCallback)( Sint16(__cdecl* callback)(Sint16 texid) );

    /**** Cheap Shadows *************************************/
    /*
    *   [[ DEPRICATED : Version 5 ]]
    * 
    *   Deprication Info:
    *     - state           : fully functional
    *     - reason          : there's now a dedicated 'Ninja' API module
    *     - alternative     : use the 'Ninja' API module instead
    * 
    *   Description:
    *     Set the intensity of modifier shadows, also called cheap shadows. The
    *   value is divided by '256' and multiplied with the pixel color. For example,
    *   a value of '0' would result in a fully black pixel and a value of '256'
    *   would result in no change - or in other words cheap shadows would be
    *   disabled.
    *
    *   Notes:
    *     - The game uses a value of '80' for the main game, and a value of '115'
    *     for Chao World.
    *     - Only one intensity can be used across a single scene. In other words,
    *     all shadows will use the same value across a single frame.
    *     - The original Ninja version only supported values up to '255'.
    *
    *   Parameters:
    *     - mode        : cheap shadow intensity                            [0~256]
    */
    void (__cdecl* SetCheapShadowMode)( Int mode );

    /****** Version >= 4 ************************************************************/
    /*
    *   Description:
    *     Set the color of modifier shadows, also called cheap shadows. The color
    *   is additive, and multiplied by the intensity.
    *
    *   Notes:
    *     - The default color is black, or ( 0.f, 0.f, 0.f ).
    *     - Only one color can be used across a single scene. In other words, all
    *       shadows will use the same color across a single frame.
    *     - This is a Render Fix extension, and was not available in Ninja.
    *
    *   Parameters:
    *     - r, g, b     : cheap shadow color                                  [0~1]
    */
    void (__cdecl* SetCheapShadowColor)( Float r, Float g, Float b );
}
RFAPI_DRAW;

#endif/*H_RFAPI_DRAW*/
