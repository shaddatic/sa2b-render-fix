/*
*   SA2 Render Fix - '/rf_draw/rfd_core.h'
*
*   Description:
*     Core draw header.
*
*   Contributors:
*     - Shaddatic
*/
#ifndef H_RF_DRAW_CORE
#define H_RF_DRAW_CORE

/********************************/
/*  Includes                    */
/********************************/
/****** Ninja ***********************************************************************************/
#include <samt/ninja/ninja.h>       /* ninja                                                    */
#include <samt/ninja/njcontext.h>   /* ninja context                                            */

EXTERN_START

/********************************/
/*  Opaque Types                */
/********************************/
/****** Cnk Draw ********************************************************************************/
typedef struct rjvtxbuf             RJS_VERTEX_BUF; /* polygon vertex buffer                    */

/********************************/
/*  Enums                       */
/********************************/
/****** Vertex Type *****************************************************************************/
typedef enum rjvtxtype
{
    RJ_VERTEX_P,                    /* position                                                 */
    RJ_VERTEX_PT,                   /* pos + texture (uv)                                       */
    RJ_VERTEX_PC,                   /* pos + color                                              */
    RJ_VERTEX_PTC,                  /* pos + tex + color                                        */
    RJ_VERTEX_PCS,                  /* pos + color + specular                                   */
    RJ_VERTEX_PTCS,                 /* pos + tex + color + spec                                 */

    RJ_NB_VERTEX,                   /* vertex number                                            */

    RJ_VERTEX_M = RJ_VERTEX_P,      /* modifier vertex                                          */
}
RJ_VERTEX_TYPE;

/****** Alpha Blend Mode ************************************************************************/
typedef enum rjblend
{
    RJ_BLEND_ZERO,                  /* tgt_color * { 0   , 0   , 0   , 0    }                   */
    RJ_BLEND_ONE,                   /* tgt_color * { 1   , 1   , 1   , 1    }                   */
    RJ_BLEND_SRCCOLOR,              /* tgt_color * { As  , Rs  , Gs  , Bs   }                   */
    RJ_BLEND_INVSRCCOLOR,           /* tgt_color * { 1-As, 1-Rs, 1-Gs, 1-Bs }                   */
    RJ_BLEND_SRCALPHA,              /* tgt_color * { As  , As  , As  , As   }                   */
    RJ_BLEND_INVSRCALPHA,           /* tgt_color * { 1-As, 1-As, 1-As, 1-As }                   */
    RJ_BLEND_DSTALPHA,              /* tgt_color * { Ad  , Ad  , Ad  , Ad   }                   */
    RJ_BLEND_INVDSTALPHA,           /* tgt_color * { 1-Ad, 1-Ad, 1-Ad, 1-Ad }                   */
}
RJ_BLEND;

typedef enum rjalphamd
{
    RJ_ALPHA_RESET = -1,            /* reset alpha mode to default (opaque)                     */

    RJ_ALPHA_OPAQUE,                /* opaque drawing                                           */
    RJ_ALPHA_TRANSLUCENT,           /* translucent drawing                                      */
    RJ_ALPHA_ALPHATEST,             /* alpha test drawing (translucent)                         */
    RJ_ALPHA_PUNCHTHROUGH,          /* punchthrough drawing (opaque)                            */
}
RJ_ALPHA;

/****** Shading Mode ****************************************************************************/
typedef enum rjshade
{
    RJ_SHADE_FLAT,                  /* entire face is shaded with the same color                */
    RJ_SHADE_GOURAUD,               /* each vertex color is interpolated across the face        */
}
RJ_SHADE;

typedef enum rjtexshade
{
    /*
    *   t = texture
    *   c = color
    *   o = offset color
    * 
    *   pixel_color | pixel_alpha
    */
    RJ_TEXSHADE_DECAL,              /*  RGBt + RGBo                         | At                */
    RJ_TEXSHADE_MODULATE,           /* (RGBc * RGBt) + RGBo                 | Ac                */
    RJ_TEXSHADE_DECALALPHA,         /* (RGBt * At) + (RGBc * (1-At)) + RGBo | Ac                */
    RJ_TEXSHADE_MODULATEALPHA,      /* (RGBc * RGBt) + RGBo                 | Ac * At           */
}
RJ_TEXSHADE;

/****** Polygon Culling Mode ********************************************************************/
typedef enum rjcullmd
{
    RJ_CULL_NONE,                   /* no culling                                               */
    RJ_CULL_CW,                     /* cull clock-wise polygons                                 */
    RJ_CULL_ACW,                    /* cull anti-clock-wise polygons                            */
}
RJ_CULL;

/********************************/
/*  Structures                  */
/********************************/
/****** Vertex Type *****************************************************************************/
typedef struct rjvtxp
{
    NJS_POINT3  pos;                /* position                                                 */
}
RJS_VERTEX_P, RJS_VERTEX_M;

typedef struct rjvtxpt
{
    NJS_POINT3  pos;                /* position                                                 */
    Float       u,v;                /* texture coordinates                                      */
}
RJS_VERTEX_PT;

typedef struct rjvtxpc
{
    NJS_POINT3  pos;                /* position                                                 */
    Uint32      col;                /* diffuse color                                     [BGRA] */
}
RJS_VERTEX_PC;

typedef struct rjvtxptc
{
    NJS_POINT3  pos;                /* position                                                 */
    Float       u,v;                /* texture coordinates                                      */
    Uint32      col;                /* diffuse color                                     [BGRA] */
}
RJS_VERTEX_PTC;

typedef struct rjvtxpcs
{
    NJS_POINT3  pos;                /* position                                                 */
    Uint32      col;                /* diffuse color                                     [BGRA] */
    Uint32      spc;                /* specular color                                    [BGR_] */
}
RJS_VERTEX_PCS;

typedef struct rjvtxptcs
{
    NJS_POINT3  pos;                /* position                                                 */
    Float       u,v;                /* texture coordinates                                      */
    Uint32      col;                /* diffuse color                                     [BGRA] */
    Uint32      spc;                /* specular color                                    [BGR_] */
}
RJS_VERTEX_PTCS;

/****** Texture UV ******************************************************************************/
typedef struct rjuv
{
    Float       u,v;                /* texture coordinates                                      */
}
RJS_UV;

/********************************/
/*  Extern Data                 */
/********************************/
/****** Depth Queue *****************************************************************************/
EXTERN Float _rj_depth_queue_near_; /* depth queue near plane                                   */
EXTERN Float _rj_depth_queue_far_;  /* depth queue far plane                                    */

/****** Texture Error ***************************************************************************/
EXTERN NJS_TEXNAME texture_rf_texerr[]; /* error texname                                        */
EXTERN NJS_TEXLIST texlist_rf_texerr[]; /* error texlist                                        */

/****** Translucency Mode ***********************************************************************/
#define _rj_alpha_mode_             DATA_REF(RJ_ALPHA, 0x025EFE50)

/********************************/
/*  Prototypes                  */
/********************************/
/************************************************************************************************/
/*
*   Draw Core
*/
/****** Set Alpha Blend *************************************************************************/
/*
*   Description:
*     Set blend mode via ninja context struct.
*
*   Parameters:
*     - src, dst    : source and destination blend modes
*     - mode        : alpha mode
*/
void    rjSetAlphaMode( RJ_BLEND src, RJ_BLEND dst, RJ_ALPHA mode );

/****** Shading Mode ****************************************************************************/
/*
*   Description:
*     Set polygon shading mode.
*
*   Parameters:
*     - mode        : polygon shading mode
*/
void    rjSetPolygonShading( RJ_SHADE mode );
/*
*   Description:
*     Set texture shading parameters.
*
*   Parameters:
*     - shade       : texture shading mode
*     - igntexalpha : ignore texture alpha mode
*/
void    rjSetTextureParam( RJ_TEXSHADE shade, Bool igntexalpha );

/****** Culling *********************************************************************************/
/*
*   Description:
*     Set the polygon culling mode.
*
*   Parameters:
*     - mode        : polygon culling mode
*/
void    rjSetPolygonCulling( RJ_CULL mode );
/*
*   Description:
*     Set the invert polygon mode. If this is enabled, CW polygons will be drawn as CCW
*   polygons, and vice versa.
*
*   Parameters:
*     - mode        : ON/OFF
*/
void    rjInvertPolygons( Bool mode );

/****** 2D Draw *********************************************************************************/
/*
*   Description:
*     Set blend mode via ninja context struct.
*
*   Parameters:
*     - trans       : use translucency
*/
void    rjSetBlend2D( Int trans );
/*
*   Description:
*     Set texture parameters from ninja context struct.
*
*   Parameters:
*     - clamp       : force clamped texture coordinates
*/
void    rjSetTexture2D( Int clamp );
/*
*   Description:
*     Convert 2D depth value to hw depth value.
*
*   Parameters:
*     - pri         : z priority                                              [-1.f ~ -65536.f]
*
*   Returns:
*     Hardware Z depth.
*/
f32     rjGetDepth2D( f32 pri );

/****** Texture Surface *************************************************************************/
/*
*   Description:
*     Get loaded texture surface via the current texlist index.
*
*   Parameters:
*     - n           : texlist index
*
*   Returns:
*     Texture surface; or 'nullptr' on failure.
*/
NJS_TEXSURFACE* rjGetTextureSurface( Int n );
/*
*   Description:
*     Get loaded texture surface via it's global texture index.
*
*   Parameters:
*     - gbix        : global texture index value
*
*   Returns:
*     Texture surface; or 'nullptr' on failure.
*/
NJS_TEXSURFACE* rjGetTextureSurfaceG( Int gbix );

/****** Context *********************************************************************************/
/*
*   Description:
*     Set polygon culling parameters via Ninja context automatically.
*/
void    rjSetPolygonCullingCtx( void );
/*
*   Description:
*     Set texture shading parameters via Ninja context automatically.
*/
void    rjSetTextureParamCtx( void );

/****** Start/End Vertex ************************************************************************/
/*
*   Description:
*     Start 2D draw state and vertex buffer for specific vertex type.
*
*   Parameters:
*     - vtype       : vertex type
*/
void    rjStartVertex2D( RJ_VERTEX_TYPE vtype );
/*
*   Description:
*     Start 3D draw state and vertex buffer for specific vertex type.
*
*   Parameters:
*     - vtype       : vertex type
*/
void    rjStartVertex3D( RJ_VERTEX_TYPE vtype );
/*
*   Description:
*     End vertex, and draw vertex buffer.
*/
void    rjEndVertex( void );

/****** Get Vertex Buffer ***********************************************************************/
/*
*   Description:
*     Get the top of the vertex buffer.
*
*   Notes:
*     - Ensure this is called after calling a 'rjStartTri' function, such as
*       'rjStartTriStrip'.
*/
void*   rjGetVertexBuffer( void );

/****** Triangle Strip **************************************************************************/
/*
*   Description:
*     Start a triangle strip.
*
*   Parameters:
*     - count       : strip len
*
*   Returns:
*     Number of verteces in the triangle strip (the absolute value of 'len')
*/
Sint32  rjStartTriStrip( Sint32 len );
/*
*   Description:
*     End a triangle strip.
*
*   Parameters:
*     - vtx         : vertex count, as returned by 'rjStartTriStrip'
*/
void    rjEndTriStrip( Sint32 vtx );

/****** Destrip (Tri List) **********************************************************************/
/*
*   Description:
*     Start a de-stripped triangle strip, for flat shading.
*
*   Parameters:
*     - count       : strip len
*     - pOutInvst   : return pointer for strip winding
*
*   Returns:
*     Number of verteces in triangle list when de-stripped.
*/
Sint32  rjStartTriDestrip( Sint32 len, Bool* pOutInvst );
/*
*   Description:
*     End a de-stripped triangle strip, for flat shading.
*
*   Parameters:
*     - vtx         : vertex count, as returned by 'Start'
*/
void    rjEndTriDestrip( Sint32 vtx );

/************************************************************************************************/
/*
*   Modifier Volume Core
*/
/****** Modifier Buffer *************************************************************************/
/*
*   Description:
*     Draw the current modifier vertex buffer to the screen.
*/
void    rjModifierDrawBuffer( void );
/*
*   Description:
*     Get the top of the modifier vertex buffer.
*
*   Notes:
*     - Ensure this is called after calling a 'rjStartModTri' function, such as
*       'rjStartModTriList'.
*/
RJS_VERTEX_M* rjGetModVertexBuffer( void );

/****** Modifier List ***************************************************************************/
/*
*   Description:
*     Start a modifier triangle list.
*
*   Parameters:
*     - poly        : polygon count
*
*   Returns:
*     Vertex count.
*/
Sint32  rjStartModTriList( Sint32 poly );
/*
*   Description:
*     End a modifier triangle list.
*
*   Parameters:
*     - vtx         : vertex count, as returned by 'Start'
*/
void    rjEndModTriList( Sint32 vtx );

/****** Modifier Destrip ************************************************************************/
/*
*   Description:
*     Start a modifier triangle destrip.
*
*   Parameters:
*     - poly        : polygon count
*     - pOutInvst   : return pointer for strip winding
*/
Sint32  rjStartModTriDestrip( Sint32 poly, Bool* pOutInvst );
/*
*   Description:
*     Start a modifier triangle destrip.
*
*   Parameters:
*     - vtx         : vertex count, as returned by 'Start'
*/
void    rjEndModTriDestrip( Sint32 vtx );

/****** Cheap Shadow Effect *********************************************************************/
/*
*   Description:
*     Start cheap shadow effect logic before draw call.
*
*   Returns:
*     Mode number for 'End' function.
*/
Sint32  rjCheapShadowEffectStart( void );
/*
*   Description:
*     End cheap shadow effect logic after draw call.
*
*   Parameters:
*     - n       : mode number from 'Start' function.
*/
void    rjCheapShadowEffectEnd( Sint32 n );

EXTERN_END

#endif/*H_RF_DRAW_CORE*/
