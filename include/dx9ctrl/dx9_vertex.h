/*
*   dx9ctrl (SA2B) - '/dx9_vertex.h'
*
*   Description:
*     DirectX 9 control library for SA2PC vertex declaration and buffer header.
*/
#ifndef H_DX9CTRL_VERTEX
#define H_DX9CTRL_VERTEX

/********************************/
/*  Includes                    */
/********************************/
/****** DX9 Control *****************************************************************************/
#include <dx9ctrl/dx9_common.h>         /* dx9 common                                           */

DX9_HEADER_START

/********************************/
/*  Opaque Types                */
/********************************/
/****** DirectX Types ***************************************************************************/
typedef struct dx9_vtx_decl         dx9_vtx_decl;   /* IDirect3DVertexDeclaration9              */
typedef struct dx9_vtx_buff         dx9_vtx_buff;   /* IDirect3DVertexBuffer9                   */

/********************************/
/*  Enums                       */
/********************************/
/****** Vertex Element Type *********************************************************************/
typedef enum
{
    DX9_VTXTYPE_FLOAT1,
    DX9_VTXTYPE_FLOAT2,
    DX9_VTXTYPE_FLOAT3,
    DX9_VTXTYPE_FLOAT4,
    DX9_VTXTYPE_COLOR,
    DX9_VTXTYPE_UBYTE4,
    DX9_VTXTYPE_SHORT2,
    DX9_VTXTYPE_SHORT4,
    DX9_VTXTYPE_UBYTE4N,
    DX9_VTXTYPE_SHORT2N,
    DX9_VTXTYPE_SHORT4N,
    DX9_VTXTYPE_USHORT2N,
    DX9_VTXTYPE_USHORT4N,
    DX9_VTXTYPE_UDEC3,
    DX9_VTXTYPE_DEC3N,
    DX9_VTXTYPE_FLOAT16_2,
    DX9_VTXTYPE_FLOAT16_4,
    DX9_VTXTYPE_UNUSED,
}
dx9_vtx_type;

/****** Vertex Element Method *******************************************************************/
typedef enum
{
    DX9_VTXMETH_DEFAULT,
    DX9_VTXMETH_PARTIALU,
    DX9_VTXMETH_PARTIALV,
    DX9_VTXMETH_CROSSUV,
    DX9_VTXMETH_UV,
    DX9_VTXMETH_LOOKUP,
    DX9_VTXMETH_LOOKUPPRESAMPLED,
}
dx9_vtx_method;

/****** Vertex Element Usage ********************************************************************/
typedef enum
{
    DX9_VTXUSE_POSITION,
    DX9_VTXUSE_BLENDWEIGHT,
    DX9_VTXUSE_BLENDINDICES,
    DX9_VTXUSE_NORMAL,
    DX9_VTXUSE_PSIZE,
    DX9_VTXUSE_TEXCOORD,
    DX9_VTXUSE_TANGENT,
    DX9_VTXUSE_BINORMAL,
    DX9_VTXUSE_TESSFACTOR,
    DX9_VTXUSE_POSITIONT,
    DX9_VTXUSE_COLOR,
    DX9_VTXUSE_FOG,
    DX9_VTXUSE_DEPTH,
    DX9_VTXUSE_SAMPLE,
}
dx9_vtx_usage;

/********************************/
/*  Structures                  */
/********************************/
/****** Vertex Element Structure ****************************************************************/
/*
*   Description:
*     End vertex element structure array.
*/
#define DX9_VTX_ELEM_END()      { 0xFF, 0, DX9_VTXTYPE_UNUSED, 0, 0, 0 }

typedef struct
{
    uint16_t    ixStream;           /* stream index                                             */
    uint16_t    ixOffset;           /* offset                                                   */
    uint8_t     type;               /* vertex parameter type                                    */
    uint8_t     method;             /* method                                                   */
    uint8_t     usage;              /* usage                                                    */
    uint8_t     ixUsage;            /* usage index                                              */
}
dx9_vtx_elem;

/********************************/
/*  Prototypes                  */
/********************************/
/************************************************************************************************/
/*
*   Vertex Declaration
*/
/****** Create Vertex Declaration ***************************************************************/
/*
*   Description:
*     Create a vertex declaration from a vertex element list. Ensure the array is
*   correctly ended with a 'DX9_VTX_ELEM_END()'.
* 
*   Parameters:
*     - pVtxElements : vertex element list
* 
*   Returns:
*     Vertex declaration pointer.
*/
dx9_vtx_decl* DX9_CreateVtxDecl( const dx9_vtx_elem* pVtxElements );

/****** Set Vertex Declaration ******************************************************************/
/*
*   Description:
*     Set the current vertex declaration.
* 
*   Parameters:
*     - pVtxDecl    : vertex declaration pointer
* 
*   Returns:
*     'true' on success; or 'false' on failure.
*/
bool    DX9_SetVtxDecl( dx9_vtx_decl* pVtxDecl );

/************************************************************************************************/
/*
*   Vertex Buffer
*/
/****** Create Vertex Buffer ********************************************************************/
/*
*   Description:
*     Create a vertex buffer to use with 'SetStreamSource' and 'DrawPrimitive'.
* 
*   Notes:
*     - It is best to set the 'USAGE_WRITEONLY' flag, as doing so will allow for
*       better optimizations on DirectX's side.
* 
*   Parameters:
*     - szBuf       : size of the vertex buffer in bytes
*     - usage       : buffer usage flags                              [optional: 0]
*     - pool        : memory pool settings
* 
*   Returns:
*     Created vertex buffer; or 'nullptr' on failure.
*/
dx9_vtx_buff* DX9_CreateVertexBuffer( dx9_size szBuf, dx9_usage usage, dx9_pool pool );

/****** Get/Lock/Unlock *************************************************************************/
/*
*   Description:
*     Lock a vertex buffer and retrieve its buffer pointer for writing/reading.
* 
*   Parameters:
*     - pBuf        : vertex buffer
*     - ixOffset    : offset to lock, in bytes                        [optional: 0]
*     - szLock      : size to lock, in bytes                          [optional: 0]
*     - flag        : lock flags
* 
*   Returns:
*     Vertex buffer memory; or 'nullptr' on failure.
*/
void*   DX9_VertexBufferLock( dx9_vtx_buff* pBuf, dx9_size ixOffset, dx9_size szLock, dx9_lock flag );
/*
*   Description:
*     Unlock a vertex buffer after writing/reading to its buffer.
* 
*   Parameters:
*     - pBuf        : vertex buffer
* 
*   Returns:
*     'true' on success; or 'false' on failure.
*/
bool    DX9_VertexBufferUnlock( dx9_vtx_buff* pBuf );

/****** Set Vertex Stream ***********************************************************************/
/*
*   Description:
*     Set a vertex buffer source for 'DrawPrimitive'.
* 
*   Parameters:
*     - ixStream    : stream index number
*     - pStream     : vertex buffer
*     - nbOffset    : triangle offset
*     - nbStride    : triangle stride size
* 
*   Returns:
*     'true' on success; or 'false' on failure.
*/
bool    DX9_SetStreamSource( dx9_size ixStream, dx9_vtx_buff* pStream, dx9_size nbOffset, dx9_size nbStride );

DX9_HEADER_END

#endif/*H_DX9CTRL_VERTEX*/