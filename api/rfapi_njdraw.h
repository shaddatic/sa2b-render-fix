/*
*   SA2 Render Fix - '/rfapi_njdraw.h'
*
*   Description:
*     The 'Ninja Draw' API module is for non-model drawing, such as sprites.
* 
*   Version History:
*     - v1.5.0.0        : Version 0, initial release
* 
*   Availability:
*     - Before Init     : No
*     - At Init         : Yes
*     - After Init      : Yes
*/
#ifndef H_RFAPI_NJDRAW
#define H_RFAPI_NJDRAW

/********************************/
/*  Constants                   */
/********************************/
/****** API Module Version **********************************************************************/
#define RFAPI_NJDRAW_VER            (0) /* ninja draw api version                               */

/********************************/
/*  API Structures              */
/********************************/
/****** Font API ********************************************************************************/
typedef struct
{
    uint32_t version;               /* structure version                                        */

    /****** Version >= 0 ********************************************************************/

    /**** Direct Polygon ************************************/
    /*
    *   Description:
    *     Draw a non-tex polygon, in screen space.
    *
    *   Parameters:
    *     - polygon     : vertex list
    *     - count       : vertex count
    *     - trans       : translucency flag                                        [TRUE/FALSE]
    */
    void (*DrawPolygon)( const NJS_POLYGON_VTX* polygon, Int count, Int trans );
    /*
    *   Description:
    *     Draw a textured polygon with texture GBIX parameter, in screen space.
    *
    *   Parameters:
    *     - polygon     : vertex list
    *     - count       : vertex count
    *     - tex         : texture gbix
    *     - flag        : translucency flag                                        [TRUE/FALSE]
    */
    void (*DrawTexture)( const NJS_TEXTURE_VTX* polygon, Int count, Int tex, Int flag );
    /*
    *   Description:
    *     Draw a textured polygon with highlights (specular/offset) with texture GBIX
    *   parameter, in screen space.
    *
    *   Parameters:
    *     - polygon     : vertex list
    *     - count       : vertex count
    *     - tex         : texture gbix
    *     - flag        : translucency flag                                        [TRUE/FALSE]
    */
    void (*DrawTextureH)( const NJS_TEXTUREH_VTX* polygon, Int count, Int tex, Int flag );

    /**** Polygon Ex ****************************************/
    /*
    *   Description:
    *     Draw a textured polygon, in screen space.
    *
    *   Notes:
    *     - A texture must be set before drawing, using 'SetTextureNum' or 'SetTextureG'.
    *
    *   Parameters:
    *     - polygon     : vertex list
    *     - count       : vertex count
    *     - trans       : translucency flag                                        [TRUE/FALSE]
    */
    void (*DrawTextureEx)( const NJS_TEXTURE_VTX* polygon, Int count, Int trans );
    /*
    *   Description:
    *     Draw a textured polygon with highlights (specular/offset), in screen space.
    *
    *   Notes:
    *     - A texture must be set before drawing, using 'SetTextureNum' or 'SetTextureG'.
    *
    *   Parameters:
    *     - polygon     : vertex list
    *     - count       : vertex count
    *     - trans       : translucency flag                                        [TRUE/FALSE]
    */
    void (*DrawTextureHEx)( const NJS_TEXTUREH_VTX* polygon, Int count, Int trans );

    /**** Polygon 3D ****************************************/
    /*
    *   Description:
    *     Draw a non-tex polygon, in world space.
    *
    *   Parameters:
    *     - p           : vertex list
    *     - count       : vertex count
    *     - trans       : translucency flag                                        [TRUE/FALSE]
    */
    void (*DrawPolygon3DEx)( const NJS_POLYGON_VTX* p, Int count, Int trans );
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
    *     - trans       : translucency flag                                        [TRUE/FALSE]
    */
    void (*DrawTexture3DEx)( const NJS_TEXTURE_VTX* p, Int count, Int trans );
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
    *     - trans       : translucency flag                                        [TRUE/FALSE]
    */
    void (*DrawTexture3DHEx)( const NJS_TEXTUREH_VTX* p, Int count, Int trans );

    /**** Line 2D ********************************************/
    /*
    *   Description:
    *     Draw a line in either strip or list mode, in screen space.
    *
    *   Parameters:
    *     - vtx         : list of line vertexes
    *     - ooz         : 1/z, 'z' being the 3D depth of the line
    *     - Count       : number of line vertexes
    *     - r           : radius, in 480p pixels
    *     - Color       : line color to draw                                    [0xAA'RR'GG'BB]
    */
    void (*DrawLineStrip2D)( const NJS_POINT2* vtx, Float ooz, Sint32 Count, Float r, Uint32 Color );
    void (*DrawLineList2D)(  const NJS_POINT2* vtx, Float ooz, Sint32 Count, Float r, Uint32 Color );

    /**** Line 3D ********************************************/
    /*
    *   Description:
    *     Draw a line in either strip or list mode, in world space.
    *
    *   Parameters:
    *     - vtx         : list of line vertexes
    *     - Count       : number of line vertexes
    *     - r           : radius, in 480p pixels
    *     - Color       : line color to draw                                    [0xAA'RR'GG'BB]
    */
    void (*DrawLineStrip3D)( const NJS_POINT3* vtx, Sint32 Count, Float r, Uint32 Color );
    void (*DrawLineList3D)(  const NJS_POINT3* vtx, Sint32 Count, Float r, Uint32 Color );

    /**** Sprite ********************************************/
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
    void (*DrawSprite2D)( const NJS_SPRITE* sp, Int n, Float pri, Uint32 attr );
    /*
    *   Description:
    *     Draw a sprite, in world space.
    *
    *   Parameters:
    *     - sp          : sprite
    *     - n           : texanim index
    *     - attr        : attributes                                                 [NJD_SPRITE_#]
    */
    void (*DrawSprite3D)( const NJS_SPRITE* sp, Int n, Uint32 attr );

    /**** Draw 2D *******************************************/
    /*
    *   Description:
    *     Draw a non-tex polygon, with Ninja '2D draw' params.
    *
    *   Examples:
    *     - rjDrawPolygon2D(poly, count, -1.0f, NJD_FILL|NJD_TRANSPARENT);
    *
    *   Parameters:
    *     - p       : vertex list
    *     - n       : vertex count
    *     - pri     : draw priority/depth                                           [-1~-65535]
    *     - attr    : attributes
    */
    void (*DrawPolygon2D)( const NJS_POINT2COL* p, Sint32 n, Float pri, Uint32 attr );
}
RFAPI_NJDRAW;

#endif/*H_RFAPI_NJDRAW*/
