/*
*   SA2 Render Fix - '/rf_ninja.h'
*
*   Description:
*     Render Fix Ninja header.
*/
#ifndef H_RF_NINJA
#define H_RF_NINJA

/********************************/
/*  Includes                    */
/********************************/
/****** Ninja ***********************************************************************************/
#include <samt/ninja/ninja.h>   /* ninja                                                        */

EXTERN_START

/********************************/
/*  Constants                   */
/********************************/
/****** Chunk Control Flags *********************************************************************/
#define RJD_CNK_CTRL_OPAQUE         (1<< 0) /* draw opaque polygons                             */
#define RJD_CNK_CTRL_TRANSLUCENT    (1<< 1) /* draw translucent polygons                        */
#define RJD_CNK_CTRL_NORMAL         (1<< 2) /* draw normal polygon faces                        */
#define RJD_CNK_CTRL_INVERSE        (1<< 3) /* draw inverse polygon faces                       */
#define RJD_CNK_CTRL_VLIST          (1<< 4) /* execute vlist chunk data                         */
#define RJD_CNK_CTRL_PLIST          (1<< 5) /* execute plist chunk data                         */

#define RJD_CNK_CTRL_VNORM          (1<< 8) /* use vertex normal attributes                     */
#define RJD_CNK_CTRL_VCOLR          (1<< 9) /* use vertex color attributes                      */
#define RJD_CNK_CTRL_VSPEC          (1<<10) /* use vertex specular attributes                   */

#define RJD_CNK_CTRL_TEXTURE        (1<<12) /* use textures                                     */
#define RJD_CNK_CTRL_ENVIRONMENT    (1<<13) /* use normal-based environment calculations        */
#define RJD_CNK_CTRL_DBLIGHT        (1<<14) /* use double sided lighting when available         */

#define RJD_CNK_CTRL_MASK_DRAW      (RJD_CNK_CTRL_OPAQUE|RJD_CNK_CTRL_TRANSLUCENT)
#define RJD_CNK_CTRL_MASK_CULL      (RJD_CNK_CTRL_NORMAL|RJD_CNK_CTRL_INVERSE)
#define RJD_CNK_CTRL_MASK_MODEL     (RJD_CNK_CTRL_VLIST|RJD_CNK_CTRL_PLIST)
#define RJD_CNK_CTRL_MASK_VTX       (RJD_CNK_CTRL_VNORM|RJD_CNK_CTRL_VCOLR|RJD_CNK_CTRL_VSPEC)
#define RJD_CNK_CTRL_MASK_EFFECT    (RJD_CNK_CTRL_TEXTURE|RJD_CNK_CTRL_ENVIRONMENT|RJD_CNK_CTRL_DBLIGHT)

#define RJD_CNK_CTRL_MASK           (RJD_CNK_CTRL_MASK_DRAW|RJD_CNK_CTRL_MASK_CULL|RJD_CNK_CTRL_MASK_MODEL|RJD_CNK_CTRL_MASK_VTX|RJD_CNK_CTRL_MASK_EFFECT)

/****** Chunk Strip flags ***********************************************************************/
#define RJD_FST_EUA                 (0x80<<NJD_FST_SHIFT)    /* extended use alpha              */

/********************************/
/*  Enums                       */
/********************************/
/****** Light Index *****************************************************************************/
typedef enum rjlight
{
    RJ_LIGHT_ALL = -1,              /* apply to all lights                                      */

    RJ_LIGHT_1,                     /* light index 1                                            */
    RJ_LIGHT_2,                     /* light index 2                                            */
    RJ_LIGHT_3,                     /* light index 3                                            */
    RJ_LIGHT_4,                     /* light index 4                                            */
    RJ_LIGHT_5,                     /* light index 5                                            */
    RJ_LIGHT_6,                     /* light index 6                                            */

    RJ_LIGHT_NUM,                   /* enum count                                               */
}
RJ_LIGHT;

/****** Light Mode ******************************************************************************/
typedef enum rjlightmd
{
    RJ_LIGHT_MD_DIR,                /* directional light                                         */
    RJ_LIGHT_MD_POINT,              /* point light                                               */
    RJ_LIGHT_MD_SPOT,               /* spot light                                       (GX emu) */
}
RJ_LIGHT_MODE;

/********************************/
/*  Structures                  */
/********************************/
/****** Rj Light ********************************************************************************/
typedef struct
{
    RJ_LIGHT_MODE mode;         /* light mode                                                   */

    /** Directional Light **/

    NJS_VECTOR  v;              /* light vector                                                 */

    Float       r,g,b;          /* color                                                        */
    Float       inten;          /* light intensity                                              */

    /** Point Light **/

    NJS_POINT3 p;               /* world position                                               */

    f32        near;            /* near light plane                                             */
    f32        far;             /* far light plane                                              */

    /** Spot Light **/

    f32          iang;          /* inner angle                                                  */
    f32          oang;          /* outer angle                                                  */
}
RJS_LIGHT;

/****** Ambient *********************************************************************************/
typedef struct
{
    Float       r,g,b;          /* color                                                        */
    Float       inten;          /* ambient intensity                                            */
}
RJS_AMBIENT;

/********************************/
/*  Macros                      */
/********************************/
/****** Convert UV Coords ***********************************************************************/
#define RJM_UVN(uv)      ((Float)(uv)*(1.f/256.f))  /* uvn to float                             */
#define RJM_UVH(uv)      ((Float)(uv)*(1.f/1024.f)) /* uvh to float                             */

/********************************/
/*  Extern Variables            */
/********************************/
/****** Light Switch ****************************************************************************/
#define _rj_light_sw_               DATA_REF(Uint32, 0x026702E0)

/****** Light Data ******************************************************************************/
EXTERN RJS_LIGHT   _rj_lights_[6];  /* light data                                               */
EXTERN RJS_AMBIENT _rj_ambient_;    /* ambient data                                             */

/****** Depth Queue *****************************************************************************/
EXTERN Float _rj_depth_queue_near_; /* depth queue near plane                                   */
EXTERN Float _rj_depth_queue_far_;  /* depth queue far plane                                    */

/********************************/
/*  Prototypes                  */
/********************************/
/************************************************************************************************/
/*
*   Back Texture
*/
/****** Set *************************************************************************************/
/*
*   Description:
*     Set the back color (non-tex), which will be used to clear the framebuffer.
*
*   Parameters:
*     - color1      : upper left color                                          [0xAA'RR'GG'BB]
*     - color2      : upper right color                                         [0xAA'RR'GG'BB]
*     - color3      : bottom left & right color                                 [0xAA'RR'GG'BB]
*/
void    rjSetBackColor( Uint32 color1, Uint32 color2, Uint32 color3 );
/*
*   Description:
*     Set the back texture, which will be used to clear the framebuffer.
*
*   Notes:
*     - Set the texture first before calling, using 'SetTextureNum' or 'SetTextureG'.
*     - Vertex position info is ignored.
*     - The bottom right vertex is generated automatically from the bottom left vertex
*       (color/offset) and its relationship to the top right vertex (texture coords).
*
*   Parameters:
*     - vtx         : the upper left, upper right, & bottom left vertex params
*/
void    rjSetBackTexture( const NJS_TEXTUREH_VTX vtx[3] );

/************************************************************************************************/
/*
*   Ninja Draw
*
*   Notes:
*     - Functions use vertex strip format.
*     - 'x/y' vertex components are in screen coordinates (0~640/480).
*     - 'z' vertex component is in the 0~1 range (back~front).
*     - A 3D z value can be converted to the 0~1 range with 'z = 1/(-z_3d)'.
*/
/****** Normal **********************************************************************************/
/*
*   Description:
*     Draw a non-tex polygon.
*
*   Parameters:
*     - polygon     : vertex list
*     - count       : vertex count
*     - trans       : translucency flag                                            [TRUE/FALSE]
*/
void    rjDrawPolygon( const NJS_POLYGON_VTX* polygon, Int count, Int trans );
/*
*   Description:
*     Draw a textured polygon, with texture GBIX parameter.
*
*   Parameters:
*     - polygon     : vertex list
*     - count       : vertex count
*     - tex         : texture gbix
*     - flag        : translucency flag                                            [TRUE/FALSE]
*/
void    rjDrawTexture( const NJS_TEXTURE_VTX* polygon, Int count, Int tex, Int flag );
/*
*   Description:
*     Draw a textured polygon with highlights (specular/offset), with texture GBIX parameter.
*
*   Parameters:
*     - polygon     : vertex list
*     - count       : vertex count
*     - tex         : texture gbix
*     - flag        : translucency flag                                            [TRUE/FALSE]
*/
void    rjDrawTextureH( const NJS_TEXTUREH_VTX* polygon, Int count, Int tex, Int flag );

/****** Ninja Draw Ex ***************************************************************************/
/*
*   Description:
*     Draw a textured polygon.
*
*   Notes:
*     - A texture must be set before drawing, using 'SetTextureNum' or 'SetTextureG'.
*
*   Parameters:
*     - polygon     : vertex list
*     - count       : vertex count
*     - trans       : translucency flag                                            [TRUE/FALSE]
*/
void    rjDrawTextureEx( const NJS_TEXTURE_VTX* polygon, Int count, Int trans );
/*
*   Description:
*     Draw a textured polygon with highlights (specular/offset).
*
*   Notes:
*     - A texture must be set before drawing, using 'SetTextureNum' or 'SetTextureG'.
*
*   Parameters:
*     - polygon     : vertex list
*     - count       : vertex count
*     - trans       : translucency flag                                            [TRUE/FALSE]
*/
void    rjDrawTextureHEx( const NJS_TEXTUREH_VTX* polygon, Int count, Int trans );

/************************************************************************************************/
/*
*   Polygon 2/3D
*/
/****** Polygon 2D ******************************************************************************/
/*
*   Description:
*     Draw a non-tex polygon, with Ninja '2D draw' params.
*
*   Examples:
*     - rjDrawPolygon2D(poly, count, -1.0f, NJD_FILL|NJD_TRANSPARENT);
*
*   Parameters:
*     - p           : vertex list
*     - n           : vertex count
*     - pri         : draw priority/depth                                           [-1~-65535]
*     - attr        : attributes
*/
void    rjDrawPolygon2D( const NJS_POINT2COL* p, Sint32 n, Float pri, Uint32 attr );

/****** Polygon 3D ******************************************************************************/
/*
*   Description:
*     Draw a non-tex polygon, in world space.
*
*   Parameters:
*     - p           : vertex list
*     - count       : vertex count
*     - trans       : translucency flag                                            [TRUE/FALSE]
*/
void    rjDrawPolygon3DEx( const NJS_POLYGON_VTX* p, Int count, Int trans );
/*
*   Description:
*     Draw a textured polygon, in world space.
*
*   Notes:
*     - A texture must be set before drawing, using 'SetTextureNum' or 'SetTextureG'.
*
*   Parameters:
*     - p           : vertex list
*     - count       : vertex count
*     - trans       : translucency flag                                            [TRUE/FALSE]
*/
void    rjDrawTexture3DEx( const NJS_TEXTURE_VTX* p, Int count, Int trans );
/*
*   Description:
*     Draw a textured polygon with highlights (specular/offset), in world space.
*
*   Notes:
*     - A texture must be set before drawing, using 'SetTextureNum' or 'SetTextureG'.
*
*   Parameters:
*     - p           : vertex list
*     - count       : vertex count
*     - trans       : translucency flag                                            [TRUE/FALSE]
*/
void    rjDrawTexture3DHEx( const NJS_TEXTUREH_VTX* p, Int count, Int trans );

/************************************************************************************************/
/*
*   Line
*/
/****** Draw Line *******************************************************************************/
/*
*   Description:
*     Draw a line in either strip or list mode, in screen space.
*
*   Parameters:
*     - vtx         : list of line vertexes
*     - ooz         : 1/z, 'z' being the 3D depth of the line
*     - Count       : number of line vertexes
*     - r           : radius, in 480p pixels
*     - Color       : line color                                                [0xAA'RR'GG'BB]
*/
void    rjDrawLineStrip2D( const NJS_POINT2* vtx, Float ooz, Sint32 Count, Float r, Uint32 Color );
void    rjDrawLineList2D(  const NJS_POINT2* vtx, Float ooz, Sint32 Count, Float r, Uint32 Color );
/*
*   Description:
*     Draw a line in either strip or list mode, in world space.
*
*   Parameters:
*     - vtx         : list of line vertexes
*     - Count       : number of line vertexes
*     - r           : radius, in 480p pixels
*     - Color       : line color                                                [0xAA'RR'GG'BB]
*/
void    rjDrawLineStrip3D( const NJS_POINT3* vtx, Sint32 Count, Float r, Uint32 Color );
void    rjDrawLineList3D(  const NJS_POINT3* vtx, Sint32 Count, Float r, Uint32 Color );

/************************************************************************************************/
/*
*   Sprite
*/
/****** Draw Sprite *****************************************************************************/
/*
*   Description:
*     Draw a sprite, in screen space.
*
*   Parameters:
*     - sp          : sprite
*     - n           : texanim index
*     - pri         : draw priority/depth                                           [-1~-65535]
*     - attr        : attributes                                                 [NJD_SPRITE_#]
*/
void    rjDrawSprite2D( const NJS_SPRITE* sp, Int n, Float pri, Uint32 attr );
/*
*   Description:
*     Draw a sprite, in world space.
*
*   Parameters:
*     - sp          : sprite
*     - n           : texanim index
*     - attr        : attributes                                                 [NJD_SPRITE_#]
*/
void    rjDrawSprite3D( const NJS_SPRITE* sp, Int n, Uint32 attr );

/************************************************************************************************/
/*
*   Lights
*/
/****** Light Switch ****************************************************************************/
/*
*   Description:
*     Switch a light on/off.
*
*   Parameters:
*     - light       : chunk light                                                  [RJ_LIGHT_#]
*     - flag        : on/off flag                                                      [ON/OFF]
*/
void    rjSetLightSwitch( Int light, Int flag );

/****** Light Color *****************************************************************************/
/*
*   Description:
*     Set a Chunk light color.
*
*   Notes:
*     - Internal light intensity is set to '1.f' when this function is called. To
*       set a custom intensity, use 'SetLightIntensity'.
*
*   Parameters:
*     - light       : chunk light                                                  [RJ_LIGHT_#]
*     - lr,lg,lb    : color                                                           [0.f~1.f]
*/
void    rjSetLightColor( Int light, Float lr, Float lg, Float lb );
/*
*   Description:
*     Set the Chunk ambient light color.
*
*   Notes:
*     - Ambient is set here OR via intensity, but can't be both.
*     - Internal ambient intensity value is set to the largest color component
*       value when this function is called.
*
*   Parameters:
*     - ar,ag,ab    : color                                                           [0.f~1.f]
*/
void    rjSetAmbient( Float ar, Float ag, Float ab );
/*
*   Description:
*     Set a Chunk light intensity, and optionally the ambient intensity.
*
*   Notes:
*     - This will overwrite the ambient light color if ambient intensity is set.
*     - Ambient is not updated when 'LIGHT_ALL' is used.
*
*   Parameters:
*     - light       : chunk light                                                  [RJ_LIGHT_#]
*     - inten       : light intensity                                                 [0.f~1.f]
*     - ambient     : ambient intensity                                    [opt: -1.f, 0.f~1.f]
*/
void    rjSetLightIntensity( Int light, Float inten, Float ambient );

/****** Light Modes *****************************************************************************/
/*
*   Description:
*     Set a light vector, and set the light mode to directional light.
*
*   Notes:
*     - Vector is not normalized in-function.
*
*   Parameters:
*     - light       : light index                                                 [RJ_LIGHT_#] 
*     - vx,vy,vz    : vector
*/
void    rjSetLightVector( Int light, Float vx, Float vy, Float vz );
/*
*   Description:
*     Set a light position, and set the light mode to point light.
*
*   Parameters:
*     - light       : light index                                                 [RJ_LIGHT_#] 
*     - px,py,pz    : vector
*/
void    rjSetLightPoint( Int light, Float px, Float py, Float pz );

/****** Light Param *****************************************************************************/
/*
*   Description:
*     Set Chunk point light near and far ranges.
*
*   Notes:
*     - Anything closer than near is clamped to max intensity, then intensity falls
*       off linearly until the far range.
*
*   Parameters:
*     - light       : light index                                                 [RJ_LIGHT_#] 
*     - nrange      : near range
*     - frange      : far range
*/
void    rjSetLightRange( Int light, Float nrange, Float frange );

/****** Light Matrix ****************************************************************************/
/*
*   Description:
*     Set Chunk light vectors/points to the current matrix, if it hasn't been done.
*
*   Parameters:
*     - light       : light index                                                 [RJ_LIGHT_#] 
*/
void    rjSetLightMatrix( Int light );

/************************************************************************************************/
/*
*   Chunk Draw
*/
/****** Chunk Control ***************************************************************************/
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

/****** Chunk Modify ****************************************************************************/
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
*
*   Parameters:
*     - u, v        : u and v scroll offset
*/
void    rjCnkSetEnvUvScroll( Float u, Float v );

/****** Chunk Draw ******************************************************************************/
/*
*   Description:
*     Draw a Chunk model with the draw function pulled from the renderstate.
*
*   Parameters:
*     - model       : chunk model pointer
*
*   Returns:
*     '0' if drawn; or '-1' if the model was clipped.
*/
Sint32  rjCnkDrawModel( NJS_CNK_MODEL* model );
/*
*   Description:
*     Draw a Chunk model normally, using all model parameters and features as expected.
*
*   Notes:
*     - This is a Render Fix extension, and is not part of base Ninja; although Ninja had a
*       type of 'Normal' draw, it wasn't referenced for this function.
*
*   Parameters:
*     - model       : chunk model
* 
*   Returns:
*     '0' on success; or '-1' if the model was clipped.
*/
Sint32  rjCnkNormalDrawModel( NJS_CNK_MODEL* model );
/*
*   Description:
*     Draw a Chunk model with 'Easy' emulation, which is the fastest but most limited
*   draw function. It lacks support for many Chunk features.
*
*   Parameters:
*     - model       : chunk model
* 
*   Returns:
*     '0' on success; or '-1' if the model was clipped.
*/
Sint32  njCnkEasyDrawModel( NJS_CNK_MODEL* model );
/*
*   Description:
*     Draw a Chunk model with 'Simple' emulation, which is the least limited draw
*   function.
*
*   Parameters:
*     - model       : chunk model
* 
*   Returns:
*     '0' on success; or '-1' if the model was clipped.
*/
Sint32  njCnkSimpleDrawModel( NJS_CNK_MODEL* model );
/*
*   Description:
*     Draw a Chunk model with 'EasyMulti' emulation, which is the multi-light variant of
*   the 'Easy' draw function.
*
*   Parameters:
*     - model       : chunk model
* 
*   Returns:
*     '0' on success; or '-1' if the model was clipped.
*/
Sint32  njCnkEasyMultiDrawModel( NJS_CNK_MODEL* model );
/*
*   Description:
*     Draw a Chunk model with 'SimpleMulti' emulation, which is the multi-light variant of
*   the 'Simple' draw function.
*
*   Parameters:
*     - model       : chunk model
* 
*   Returns:
*     '0' on success; or '-1' if the model was clipped.
*/
Sint32  njCnkSimpleMultiDrawModel( NJS_CNK_MODEL* model );
/*
*   Description:
*     Draw a Chunk model as if it was compiled with 'njCnkDirectObjectCompile' and then
*   drawn with 'njDirectDrawObject'.
* 
*   Notes:
*     - This is a Render Fix extension, and is not part of base Ninja; although the
*   behavior it emulates is.
*
*   Parameters:
*     - model       : chunk model
* 
*   Returns:
*     '0' on success; or '-1' if the model was clipped.
*/
Sint32  njCnkDirectDrawModel( NJS_CNK_MODEL* model );
/*
*   Description:
*     Draw a Chunk model as a modifier volume, usually for shadows.
*
*   Parameters:
*     - model       : chunk model
* 
*   Returns:
*     '0' on success; or '-1' if the model was clipped.
*/
Sint32  njCnkModDrawModel( NJS_CNK_MODEL* model );

/************************************************************************************************/
/*
*   Transform Object
*/
/****** Object **********************************************************************************/
/*
*   Description:
*     Transform a Chunk object tree, with model callback.
* 
*   Notes:
*     - Calls 'Object' and 'Model' callback functions.
*
*   Parameters:
*     - object      : chunk object head
*     - callback    : model callback function (eg. CnkEasyDrawModel)
*       - model     : chunk model
*       + return    : clip status
*/
void    rjCnkTransformObject( NJS_CNK_OBJECT* object, Sint32(*callback)(NJS_CNK_MODEL* model) );

/****** Motion **********************************************************************************/
/*
*   Description:
*     Transform a Chunk object with a motion, with model callback.
* 
*   Notes:
*     - Calls 'Motion' and 'Model' callback functions.
*
*   Parameters:
*     - object      : chunk object head
*     - motion      : motion structure
*     - frame       : motion frame
*     - callback    : model callback function
*/
void    rjCnkTransformMotion( NJS_CNK_OBJECT* object, NJS_MOTION* motion, Float frame, Sint32(*callback)(NJS_CNK_MODEL*) );
/*
*   Description:
*     Transform a Chunk object with a motion link (interpolated motions), with model callback.
* 
*   Notes:
*     - Calls 'Motion' and 'Model' callback functions.
*
*   Parameters:
*     - object      : chunk object head
*     - motion_link : motion link structure
*     - rate        : motion ratio                                                        [0~1]
*     - callback    : model callback function
*/
void    rjCnkTransformMotionLink( NJS_CNK_OBJECT* object, NJS_MOTION_LINK* motion_link, Float rate, Sint32(*callback)(NJS_CNK_MODEL*) );

/****** Shape Motion ****************************************************************************/
/*
*   Description:
*     Transform a Chunk object with a motion and shape motion, with model callback.
* 
*   Notes:
*     - Calls 'Motion' and 'Model' callback functions.
*     - If no shape motion is given, functions as 'CnkDrawMotion'
*
*   Parameters:
*     - object      : chunk object head
*     - motion      : motion structure
*     - shape       : shape motion structure                                     [opt: nullptr]
*     - frame       : motion frame
*     - sframe      : shape motion frame (the normal functions re-use 'frame')
*     - callback    : model callback function
*/
void    rjCnkTransformShapeMotion( NJS_CNK_OBJECT* object, NJS_MOTION* motion, NJS_MOTION* shape, Float frame, Float sframe, Sint32(*callback)(NJS_CNK_MODEL*) );
/*
*   Description:
*     Transform a Chunk object with a motion link and shape motion link (interpolated motions),
*   with model callback.
* 
*   Notes:
*     - Calls 'Motion' and 'Model' callback functions.
*     - If no shape motion is given, functions as 'CnkDrawMotionLink'
*
*   Parameters:
*     - object      : chunk object head
*     - motion_link : motion link structure
*     - shape_link  : shape motion link structure                                [opt: nullptr]
*     - rate        : motion ratio                                                        [0~1]
*     - callback    : model callback function
*/
void    rjCnkTransformShapeMotionLink( NJS_CNK_OBJECT* object, NJS_MOTION_LINK* motion_link, NJS_MOTION_LINK* shape_link, Float rate, Sint32(*callback)(NJS_CNK_MODEL*) );

/****** Shape Motion BE *************************************************************************/
/*
*   Description:
*     Transform a Chunk object with a motion and big endian shape motion.
* 
*   Notes:
*     - Only the shape vertex data is big endian.
*/
void    rjCnkTransformShapeMotionBE( NJS_CNK_OBJECT* object, NJS_MOTION* motion, NJS_MOTION* shape, Float frame, Float sframe, Sint32(*callback)(NJS_CNK_MODEL*) );
/*
*   Description:
*     Transform a Chunk object with a motion link and big endian shape motion link.
* 
*   Notes:
*     - Only the shape vertex data is big endian.
*/
void    rjCnkTransformShapeMotionLinkBE( NJS_CNK_OBJECT* object, NJS_MOTION_LINK* motion_link, NJS_MOTION_LINK* shape_link, Float rate, Sint32(*callback)(NJS_CNK_MODEL*) );

/****** Shadow Texture **************************************************************************/
/*
*   Description:
*     Start/end Chunk shadow texture.
*/
void    rjCnkBeginShadowTex( void );
void    rjCnkEndShadowTex( void );

/************************************************************************************************/
/*
*   Modifier Shadow
*/
/****** Cheap Shadow ****************************************************************************/
/*
*   Description:
*     Set the intensity of modifier shadows, also called cheap shadows. The value is divided by
*   '256' and multiplied with the pixel color. For example, a value of '0' would result in a
*   fully black pixel and a value of '256' would result in no change - or in other words cheap
*   shadows would be disabled.
*
*   Notes:
*     - Only one intensity can be used across a single scene. In other words, all shadows will
*       use the same value across a single frame.
*     - The original Ninja version only supported values up to '255'
*
*   Parameters:
*     - mode        : cheap shadow intensity                                            [0~256]
*/
void    rjSetCheapShadowMode( Int mode );
/*
*   Description:
*     Set the color of modifier shadows, also called cheap shadows. The color is additive, and
*   multiplied by the intensity.
*
*   Notes:
*     - The default color is black, or ( 0.f, 0.f, 0.f').
*     - Only one color can be used across a single scene. In other words, all
*       shadows will use the same color across a single frame.
*     - This is a Render Fix extension, and was not available in Ninja.
*
*   Parameters:
*     - r, g, b     : cheap shadow color                                                  [0~1]
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

/************************************************************************************************/
/*
*   Vsync
*/
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
