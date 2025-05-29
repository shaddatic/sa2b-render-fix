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

/************************/
/*  Opaque Types        */
/************************/
/****** Cnk Draw ********************************************************************/
typedef struct cnk_vtx_buf      CNK_VERTEX_BUFFER;

/************************/
/*  Enums               */
/************************/
/****** Vertex Type *****************************************************************/
typedef enum
{
    RJE_VERTEX_P,           /* position                                             */
    RJE_VERTEX_PT,          /* pos + texture (uv)                                   */
    RJE_VERTEX_PC,          /* pos + color                                          */
    RJE_VERTEX_PTC,         /* pos + tex + color                                    */
    RJE_VERTEX_PCS,         /* pos + color + specular                               */
    RJE_VERTEX_PTCS,        /* pos + tex + color + spec                             */

    NB_RJE_VERTEX,          /* vertex number                                        */

    RJE_VERTEX_M = RJE_VERTEX_P, /* modifier vertex                                 */
}
RJE_VERTEX_TYPE;

/************************/
/*  Structures          */
/************************/
/****** Vertex Type *****************************************************************/
typedef struct
{
    NJS_POINT3  pos;        /* position                                             */
}
RJS_VERTEX_P, RJS_VERTEX_M;

typedef struct
{
    NJS_POINT3  pos;        /* position                                             */
    Float       u,v;        /* texture coordinates                                  */
}
RJS_VERTEX_PT;

typedef struct
{
    NJS_POINT3  pos;        /* position                                             */
    Uint32      col;        /* diffuse color                                 [BGRA] */
}
RJS_VERTEX_PC;

typedef struct
{
    NJS_POINT3  pos;        /* position                                             */
    Float       u,v;        /* texture coordinates                                  */
    Uint32      col;        /* diffuse color                                 [BGRA] */
}
RJS_VERTEX_PTC;

typedef struct
{
    NJS_POINT3  pos;        /* position                                             */
    Uint32      col;        /* diffuse color                                 [BGRA] */
    Uint32      spc;        /* specular color                                [BGR_] */
}
RJS_VERTEX_PCS;

typedef struct
{
    NJS_POINT3  pos;        /* position                                             */
    Float       u,v;        /* texture coordinates                                  */
    Uint32      col;        /* diffuse color                                 [BGRA] */
    Uint32      spc;        /* specular color                                [BGR_] */
}
RJS_VERTEX_PTCS;

/****** Texture UV ******************************************************************/
typedef struct
{
    Float       u,v;        /* texture coordinates                                  */
}
RJS_UV;

/************************/
/*  Extern Data         */
/************************/
/****** Polygon Winding *************************************************************/
EXTERN Sint32 _rj_invert_polygons_; /* invert polygon winding                       */

/****** Depth Queue *****************************************************************/
EXTERN Float _rj_depth_queue_near_; /* depth queue near plane                       */
EXTERN Float _rj_depth_queue_far_;  /* depth queue far plane                        */

/************************/
/*  Prototypes          */
/************************/
/************************************************************************************/
/*
*   Draw Core
*/
/****** Common **********************************************************************/
/*
*   Description:
*     Start 2D draw, no perspective.
*/
void    rjStartDraw2D( void );
/*
*   Description:
*     Start 3D draw, use perspective.
*/
void    rjStartDraw3D( void );

/****** 2D Draw *********************************************************************/
/*
*   Description:
*     Start 2D draw, no perspective.
*/
void    rjSetBlend2D( Int trans );

/****** Start/End Vertex ************************************************************/
/*
*   Description:
*     Start draw state and vertex buffer for specific vertex type.
*
*   Parameters:
*     - vtype       : vertex type
*/
void    rjStartVertex( RJE_VERTEX_TYPE vtype );
/*
*   Description:
*     End vertex, and draw vertex buffer.
*/
void    rjEndVertex( void );

/****** Get Vertex Buffer ***********************************************************/
/*
*   Description:
*     Get the top of the vertex buffer.
*
*   Notes:
*     - Ensure this is called after calling a 'rjStartTri' function, such as
*       'rjStartTriStrip'.
*/
void*   rjGetVertexBuffer( void );

/****** Triangle Strip **************************************************************/
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

/****** Destrip (Tri List) **********************************************************/
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

/************************************************************************************/
/*
*   Modifier Volume Core
*/
/****** Modifier Buffer *************************************************************/
/*
*   Description:
*     Get the top of the modifier vertex buffer.
*
*   Notes:
*     - Ensure this is called after calling a 'rjStartModTri' function, such as
*       'rjStartModTriList'.
*/
RJS_VERTEX_M* rjGetModVertexBuffer( void );

/****** Modifier List ***************************************************************/
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

/****** Modifier Destrip ************************************************************/
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
