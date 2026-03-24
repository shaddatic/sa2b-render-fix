/*
*   SAMT for Sonic Adventure 2 (PC, 2012) - '/ninja/njdraw.h'
*
*   Description:
*     Ninja draw header, for non-model drawing.
*/
#ifndef H_NJ_DRAW
#define H_NJ_DRAW

/********************************/
/*  Includes                    */
/********************************/
/****** System **********************************************************************************/
#include <samt/shinobi/sg_xpt.h>    /* shinobi types                                            */

/****** Ninja ***********************************************************************************/
#include <samt/ninja/njcommon.h>    /* ninja common                                             */

EXTERN_START

/********************************/
/*  Constants                   */
/********************************/
/****** Draw Attribute **************************************************************************/
#define NJD_DRAW_MASK               (0x0000000f) /* mask for triangle type                      */

#define NJD_DRAW_NORMAL             (0x00000000) /* draw triangle list                          */
#define NJD_DRAW_FAN                (0x00000001) /* draw triangle fan                           */
#define NJD_DRAW_CONNECTED          (0x00000002) /* draw triangle strip                         */
#define NJD_DRAW_INSCRIBED          (0x00000010) /* draw inscribed circle                       */
#define NJD_FILL                    (0x00000020) /* fill polygon, else wireframe                */
#define NJD_TRANSPARENT             (0x00000040) /* use alpha                                   */
#define NJD_CALC_LIGHT              (0x40000000) /* use light calculation                       */
#define NJD_USE_TEXTURE             (0x80000000) /* use texture                                 */

/****** Ninja Sprite ****************************************************************************/
#define NJD_SPRITE_ANGLE            BIT_0 /* rotate sprite around center by 'angle' param       */
#define NJD_SPRITE_COLOR            BIT_1 /* use constant material color, else white            */
#define NJD_SPRITE_HFLIP            BIT_2 /* horizontal texture flip                            */
#define NJD_SPRITE_VFLIP            BIT_3 /* vertical texture flip                              */
#define NJD_SPRITE_HVFLIP           (NJD_SPRITE_HFLIP|NJD_SPRITE_VFLIP)
#define NJD_SPRITE_SCALE            BIT_4 /* draw 3d sprite facing screen, eg. scale only       */
#define NJD_SPRITE_ALPHA            BIT_5 /* use alpha                                          */

/********************************/
/*  Structures                  */
/********************************/
/************************************************************************************************/
/*
*   Ninja Sprite
*/
/****** Sprite Texture **************************************************************************/
typedef struct
{
    Sint16      sx, sy;             /* size                                                     */
    Sint16      cx, cy;             /* center                                                   */
    Sint16      u1, v1;             /* upper left uv coordinates                                */
    Sint16      u2, v2;             /* lower right uv coordinates                               */
    Sint16      texid;              /* texture id                                               */
    Sint16      attr;               /* reserved, not used                                       */
}
NJS_TEXANIM;

/****** Sprite **********************************************************************************/
typedef struct
{
    NJS_POINT3   p;                 /* position                                                 */
    Float        sx, sy;            /* scale                                                    */
    Angle        ang;               /* angle                                                    */
    NJS_TEXLIST* tlist;             /* texture list                                             */
    NJS_TEXANIM* tanim;             /* animation list                                           */
}
NJS_SPRITE;

/************************************************************************************************/
/*
*   Ninja Quad Texture
*/
/****** Rectangle Quad **************************************************************************/
typedef struct
{
    Float    x1, y1, x2, y2;        /* upper left (1) and lower right (2) vtx position          */
    Float    u1, v1, u2, v2;        /* upper left (1) and lower right (2) vtx uv coords         */
}
NJS_QUAD_TEXTURE;

/****** Parallelogram Quad **********************************************************************/
typedef struct
{
    Float   x, y, z;                /* upper left vtx position, and quad depth                  */
    Float   vx1, vy1;               /* vector to upper right vtx, from first vtx                */
    Float   vx2, vy2;               /* vector to lower right vtx, from second vtx               */
    Uint32  dmy;                    /* padding                                                  */
    Float   u, v;                   /* upper left vtx uv coordinates                            */
    Float   vu1, vv1;               /* coord vector of upper right vtx, from first vtx          */
    Float   vu2, vv2;               /* coord vector of lower right vtx, from second vtx         */
    Uint32  dmy2[2];                /* padding                                                  */
}
NJS_QUAD_TEXTURE_EX;

/********************************/
/*  Prototypes                  */
/********************************/
/************************************************************************************************/
/*
*   Draw Polygon
*
*   Notes:
*     - Functions use hardware units: x, y, z == 0~640, 0~480, 1.f~0.f
*/
/****** Polygon *********************************************************************************/
/*
*   Description:
*     Draw a non-tex polygon.
*
*   Parameters:
*     - polygon         : polygon vertex list, in strip format
*     - count           : vertex number
*     - trans           : use translucency                                         [TRUE/FALSE]
*/
void    njDrawPolygon( const NJS_POLYGON_VTX* polygon, Int count, Int trans );
/*
*   Description:
*     Draw a textured polygon with texid parameter.
*
*   Parameters:
*     - polygon         : texture vertex list, in strip format
*     - count           : vertex number
*     - tex             : texid
*     - trans           : use translucency                                         [TRUE/FALSE]
*/
void    njDrawTexture( const NJS_TEXTURE_VTX* polygon, Int count, Int tex, Int trans );
/*
*   Description:
*     Draw a textured polygon.
*
*   Notes:
*     - The 'count' argument is ignored, and is always '4' (SA2B only)
*
*   Parameters:
*     - polygon         : texture vertex list, in strip format
*     - count           : vertex number
*     - trans           : use translucency                                         [TRUE/FALSE]
*/
void    njDrawTextureEx( const NJS_TEXTURE_VTX* polygon, Int count, Int trans );

/************************************************************************************************/
/*
*   Draw Polygon 2D
*
*   Notes:
*     - Functions use screen units: x, y, z == 0~640, 0~480, -1~-65535
*/
/****** Polygon 2D ******************************************************************************/
/*
*   Description:
*     Draw a non-tex polygon, in screen space.
*
*   Notes:
*     - The 'n' argument is ignored, and is always '4' (SA2B only)
* 
*   Parameters:
*     - p           : polygon vertex attr list, in strip format
*     - n           : vertex number
*     - pri         : depth priority                                            [-1.f~-65535.f]
*     - attr        : draw attributes
*/
void    njDrawPolygon2D( const NJS_POINT2COL* p, Sint32 n, Float pri, Uint32 attr );

/************************************************************************************************/
/*
*   Draw Polygon 3D
*
*   Notes:
*     - Functions use world units
*/
/****** Polygon 3D ******************************************************************************/
/*
*   Description:
*     Draw a non-tex polygon, in world space.
*
*   Parameters:
*     - p               : polygon vertex list, in strip format
*     - count           : vertex number
*     - trans           : use translucency                                         [TRUE/FALSE]
*/
void    njDrawPolygon3DEx( const NJS_POLYGON_VTX* p, Int count, Int trans );

/****** Start/End *******************************************************************************/
/*
*   Description:
*     Start a non-tex polygon draw.
*
*   Parameters:
*     - trans           : use translucency                                         [TRUE/FALSE]
*/
void    njDrawPolygon3DExStart( Int trans );
/*
*   Description:
*     End a non-tex polygon draw
*
*   Notes:
*     - This is a noop in the HD versions, but should still be called.
*/
void    njDrawPolygon3DExEnd( void );

/****** Set Polygon *****************************************************************************/
/*
*   Description:
*     Add non-tex polygons to the vertex buffer.
*
*   Parameters:
*     - p               : polygon vertex list, in strip format
*     - count           : vertex number
*/
void    njDrawPolygon3DExSetData( const NJS_POLYGON_VTX* p, Int count );

/************************************************************************************************/
/*
*   Draw Line
*/
/****** Start/End *******************************************************************************/
/*
*   Description:
*     Start a line draw.
*
*   Notes:
*     - The 'r' argument is ignored, and has no meaning in the HD versions
*
*   Parameters:
*     - a
*/
void    njDrawLineExStart( Float r, Uint32 BaseColor, Sint32 Trans );
/*
*   Description:
*     End a line draw
*
*   Notes:
*     - This is a noop in the HD versions, but should still be called.
*/
void    njDrawLineExEnd( void );

/****** Set 3D List *****************************************************************************/
/*
*   Description:
*     Add new lines to the vertex buffer, in 3D list mode.
*
*   Parameters:
*     - vtx             : line vertex list
*     - Count           : vertex number
*/
void    njDrawLine3DExSetList( NJS_POINT3* vtx, Sint32 Count );

/************************************************************************************************/
/*
*   Draw Sprite
*/
/****** Sprite **********************************************************************************/
/*
*   Description:
*     Draw a sprite quad, in screen space.
* 
*   Parameters:
*     - sp          : sprite
*     - n           : texanim index
*     - pri         : draw priority/depth                                           [-1~-65535]
*     - attr        : attributes                                                 [NJD_SPRITE_#]
*/
void    njDrawSprite2D( const NJS_SPRITE* sp, Int n, Float pri, Uint32 attr );
/*
*   Description:
*     Draw a sprite quad, in world space.
*
*   Parameters:
*     - sp          : sprite
*     - n           : texanim index
*     - attr        : attributes                                                 [NJD_SPRITE_#]
*/
void    njDrawSprite3D( const NJS_SPRITE* sp, Int n, Uint32 attr );

EXTERN_END

#endif/*H_NJ_DRAW*/
