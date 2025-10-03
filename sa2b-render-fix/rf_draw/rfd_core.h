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

    NB_RJ_VERTEX,                   /* vertex number                                            */

    RJ_VERTEX_M = RJ_VERTEX_P,      /* modifier vertex                                          */
}
RJ_VERTEX_TYPE;

/****** Alpha Blend Mode ************************************************************************/
typedef enum rjalphamd
{
    RJ_ALPHA_OPAQUE,                /* opaque drawing                                           */
    RJ_ALPHA_TRANS,                 /* translucent drawing                                      */
    RJ_ALPHA_ALPHATEST,             /* alpha test drawing (translucent)                         */
    RJ_ALPHA_PUNCHTHROUGH,          /* punchthrough drawing (opaque)                            */
}
RJ_ALPHA;

/****** Alpha Blend Mode ************************************************************************/
typedef enum rjcullmd
{
    RJ_CULL_NONE,                   /* no culling                                               */
    RJ_CULL_CW,                     /* cull clock-wise polygons                                 */
    RJ_CULL_CCW,                    /* cull counter clock-wise polygons                         */
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
EXTERN NJS_TEXLIST texlist_rf_texerr[]; /* error texlist                                        */

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
*     - src, dst    : source and destination blend modes                   [NJD_COLOR_BLENDING]
*     - mode        : alpha mode
*/
void    rjSetAlphaMode( Sint32 src, Sint32 dst, RJ_ALPHA mode );

/****** Culling *********************************************************************************/
/*
*   Description:
*     Set the polygon culling mode.
*
*   Parameters:
*     - mode        : polygon culling mode
*/
void    rjPolygonCulling( RJ_CULL mode );
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

EXTERN_END

#endif/*H_RF_DRAW_CORE*/
