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
#define RFAPI_NJDRAW_VER            (1) /* ninja draw api version                               */

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

    /****** Version >= 1 ********************************************************************/

    /********************************************************/
    /*
    *   Set Texture
    */
    /**** Set Texture ***************************************/
    /*
    *   Description:
    *     Set the current Texlist.
    *
    *   Parameters:
    *     - texlist     : texlist pointer
    *
    *   Returns:
    *     Always '1'.
    */
    Sint32 (*SetTexture)( NJS_TEXLIST* texlist );
    /*
    *   Description:
    *     Set the active texture for use with draw functions via texlist index.
    *
    *   Parameters:
    *     - n           : texname index into current texlist
    *
    *   Returns:
    *     '1' on success; or '-1' on failure.
    */
    Sint32 (*SetTextureNum)( Uint32 n );
    /*
    *   Description:
    *     Set the active texture for use with draw functions via a global index. Seaches all
    *   loaded textures and picks the first GBIX match.
    *
    *   Parameters:
    *     - globalIndex : global index
    *
    *   Returns:
    *     '1' on success; or '-1' on failure.
    */
    Sint32 (*SetTextureNumG)( Uint32 globalIndex );

    /********************************************************/
    /*
    *   Quad Texture
    */
    /**** Start/End *****************************************/
    /*
    *   Description:
    *     Start quad texture draw.
    *
    *   Notes:
    *     - DO NOT draw any other polygons other than quad textures until drawing is completed
    *       with 'QuadTextureEnd'. Doing so is undefined behavior.
    *
    *   Parameters:
    *     - trans       : use translucent drawing                                  [TRUE/FALSE]
    */
    void (*QuadTextureStart)( Sint32 trans );
    /*
    *   Description:
    *     End quad texture draw, and draw all buffered polygons.
    */
    void (*QuadTextureEnd)( void );

    /****** Set Quad Attr ***********************************/
    /*
    *   Description:
    *     Set a quad texture via texlist id or global id, set the colors, and set Ninja ctx to
    *   render state.
    *
    *   Notes:
    *     - Calling between quad texture draw calls will incur a performance penalty.
    *
    *   Parameters:
    *     - texid       : texlist index
    *     - gid         : texture gbix
    *     - col         : quad color
    *     - off         : quad highlight color
    */
    void (*SetQuadTexture)(  Sint32 texid, Uint32 col );
    void (*SetQuadTextureG)( Sint32 gid,   Uint32 col );
    void (*SetQuadTextureH)( Sint32 texid, Uint32 col, Uint32 off );
    /*
    *   Description:
    *     Set a quad texture color and highlight colors, and set Ninja ctx to render state.
    *
    *   Notes:
    *     - Calling between quad texture draw calls will incur a performance penalty, although
    *       a lesser penalty than regular 'SetQuad' functions.
    *
    *   Parameters:
    *     - col         : quad color
    *     - off         : quad highlight color
    */
    void (*SetQuadTextureColor)(  Uint32 col );
    void (*SetQuadTextureHColor)( Uint32 col, Uint32 off );

    /****** Draw Quad ***************************************/
    /*
    *   Description:
    *     Buffer a quad texture for rectangle drawing.
    *
    *   Notes:
    *     - The x1 members define the top left vertex, and x2 define the bottom right; the other
    *       vertexes of the quad are implied.
    *
    *   Parameters:
    *     - q           : quad texture
    *     - z           : depth                                                           [1.f~0.f]
    */
    void (*DrawQuadTexture)( const NJS_QUAD_TEXTURE* q, Float z );
    /*
    *   Description:
    *     Buffer a quad texture ex for parallelogram drawing.
    *
    *   Notes:
    *     - The x,y,u,v members define the top left vertex. xx1 members define the top right
    *       vertex as an offset from the first vertex. xx2 members define the bottom right vertex,
    *       as an offset from the second vertex. The bottom left vertex is implied.
    *     - The z member defines the depth for all vertexes.
    *
    *   Parameters:
    *     - q           : quad texture ex
    */
    void (*DrawQuadTextureEx)( const NJS_QUAD_TEXTURE_EX* q );
}
RFAPI_NJDRAW;

#endif/*H_RFAPI_NJDRAW*/
