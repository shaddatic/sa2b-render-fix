/*
*   Dx9ctrl (SA2B) - '/dx9ctrl.h'
*
*   Description:
*     Functions to directly control the DirectX9 renderer.
*
*   Contributors:
*     - Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC
*/
#ifndef H_DX9CTRL
#define H_DX9CTRL

/************************/
/*  Library             */
/************************/
/****** Lib *************************************************************************/
#pragma comment(lib, "dx9ctrl.lib")

/************************/
/*  External Includes   */
/************************/
/****** Std *************************************************************************/
#include <stdint.h>

/** EXTERN_START **/
#ifdef __cplusplus
extern "C" {
#endif

/************************/
/*  Constants           */
/************************/
/****** Color Write Flags ***********************************************************/
#define DX9_COL_NONE        (0b0000'0000) /* no color write                         */

#define DX9_COL_RED         (0b0000'0001) /* write red bit                          */
#define DX9_COL_GREEN       (0b0000'0010) /* write green bit                        */
#define DX9_COL_BLUE        (0b0000'0100) /* write blue bit                         */
#define DX9_COL_ALPHA       (0b0000'1000) /* write alpha bit                        */

/************************/
/*  Opaque Types        */
/************************/
/****** Shaders *********************************************************************/
typedef struct dx9_vtx_shader   dx9_vtx_shader; /* IDirect3DVertexShader9           */
typedef struct dx9_pxl_shader   dx9_pxl_shader; /* IDirect3DPixelShader9            */
typedef struct dx9_vtx_decl     dx9_vtx_decl;   /* IDirect3DVertexDeclaration9      */

/************************/
/*  Enums               */
/************************/
/****** Common **********************************************************************/
typedef enum
{
    DX9_CMP_NVR = 1,        /* never                                                */
    DX9_CMP_LSS,            /* less                                                 */
    DX9_CMP_EQU,            /* equal                                                */
    DX9_CMP_LEQ,            /* less or equal                                        */
    DX9_CMP_GTR,            /* greater                                              */
    DX9_CMP_NEQ,            /* not equal                                            */
    DX9_CMP_GEQ,            /* greater or equal                                     */
    DX9_CMP_ALW,            /* always                                               */
}
dx9_compare_op;

/****** Stencil operations **********************************************************/
typedef enum
{
    DX9_STCL_KEEP = 1,      /* keep                                                 */
    DX9_STCL_ZERO,          /* set to zero                                          */
    DX9_STCL_REPL,          /* replace                                              */
    DX9_STCL_INCR_CLMP,     /* increment with clamp                                 */
    DX9_STCL_DECR_CLMP,     /* decrement with clamp                                 */
    DX9_STCL_INVT,          /* invert                                               */
    DX9_STCL_INCR,          /* increment                                            */
    DX9_STCL_DECR,          /* decrement                                            */
}
dx9_stencil_op;

/****** Blending operations *********************************************************/
typedef enum
{
    DX9_BLND_ZERO = 1,          /* zero                                             */
    DX9_BLND_ONE,               /* one                                              */
    DX9_BLND_SRCCOLOR,          /* source color                                     */
    DX9_BLND_INVSRCCOLOR,       /* inverse source color                             */
    DX9_BLND_SRCALPHA,          /* source alpha                                     */
    DX9_BLND_INVSRCALPHA,       /* inverse source alpha                             */
    DX9_BLND_DESTALPHA,         /* destination alpha                                */
    DX9_BLND_INVDESTALPHA,      /* inverse destination alpha                        */
    DX9_BLND_DESTCOLOR,         /* destination color                                */
    DX9_BLND_INVDESTCOLOR,      /* inverse destination color                        */
    DX9_BLND_SRCALPHASAT,       /* source alpha saturated                           */
    DX9_BLND_BOTHSRCALPHA,      /* obsolete                                         */
    DX9_BLND_BOTHINVSRCALPHA,   /* obsolete                                         */
    DX9_BLND_BLENDFACTOR,       /* blend factor                                     */
    DX9_BLND_INVBLENDFACTOR,    /* inverse blend factor                             */
    DX9_BLND_SRCCOLOR2,         /* source color 2, DX9Ex only                       */
    DX9_BLND_INVSRCCOLOR2,      /* inverse source color 2, DX9Ex only               */
}
dx9_blend_op;

/****** Triangle Culling ************************************************************/
typedef enum
{
    DX9_CULL_NONE = 1,      /* cull no triangles                                    */
    DX9_CULL_CW,            /* cull clock-wise triangles                            */
    DX9_CULL_CCW,           /* cull counter-clock-wise triangles                    */
}
dx9_cull_mode;

/****** Vertex Element Type *********************************************************/
enum
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
};

/****** Vertex Element Method *******************************************************/
enum
{
    DX9_VTXMETH_DEFAULT,
    DX9_VTXMETH_PARTIALU,
    DX9_VTXMETH_PARTIALV,
    DX9_VTXMETH_CROSSUV,
    DX9_VTXMETH_UV,
    DX9_VTXMETH_LOOKUP,
    DX9_VTXMETH_LOOKUPPRESAMPLED,
};

/****** Vertex Element Usage ********************************************************/
enum
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
};

/****** Vertex Primitive Type *******************************************************/
typedef enum
{
    DX9_PRITYPE_POINTLIST = 1,
    DX9_PRITYPE_LINELIST,
    DX9_PRITYPE_LINESTRIP,
    DX9_PRITYPE_TRIANGLELIST,
    DX9_PRITYPE_TRIANGLESTRIP,
    DX9_PRITYPE_TRIANGLEFAN,
}
dx9_pri_type;

/************************/
/*  Structures          */
/************************/
/****** Vertex Element Structure ****************************************************/
/*
*   Description:
*     End vertex element structure array.
*/
#define DX9_VTX_ELEM_END()      { 0xFF, 0, DX9_VTXTYPE_UNUSED, 0, 0, 0 }

typedef struct
{
    uint16_t    idxStream;
    uint16_t    idxOffset;
    uint8_t     type;
    uint8_t     method;
    uint8_t     usage;
    uint8_t     idxUsage;
}
dx9_vtx_elem;

/************************/
/*  Prototypes          */
/************************/
/************************************************************************************/
/*
*   Base Functions
*/

/****** Init ************************************************************************/
/*
*   Description:
*     Init DX9 Control library.
*/
void    DX9_Init( void );

/****** D3D9 Device *****************************************************************/
/*
*   Description:
*     Get the DirectX9 device.
* 
*   Returns:
*     Pointer to the 'IDirect3DDevice9'.
*/
void*   DX9_GetDevice( void );

/************************************************************************************/
/*
*   Render State
*/

/****** Z Buffer ********************************************************************/
/*
*   Description:
*     Enable/disable Z buffering.
*
*   Parameters:
*     - state       : z buffer state
* 
*   Returns:
*     'true' on success, or 'false' on failure.
*/
bool    DX9_SetZEnable( bool state );
/*
*   Description:
*     Enable/disable Z buffer write.
*
*   Parameters:
*     - state       : z write state
* 
*   Returns:
*     'true' on success, or 'false' on failure.
*/
bool    DX9_SetZWrite( bool state );
/*
*   Description:
*     Set Z compare function.
*
*   Parameters:
*     - op          : z compare operation
* 
*   Returns:
*     'true' on success, or 'false' on failure.
*/
bool    DX9_SetZFunc( dx9_compare_op op );

/****** Stencil Buffer **************************************************************/
/*
*   Description:
*     Enable/disable the stencil buffer.
*
*   Parameters:
*     - state       : stencil buffer state
*
*   Returns:
*     'true' on success, or 'false' on failure.
*/
bool    DX9_SetStencilEnable( bool state );
/*
*   Description:
*     Enable/disable two sided stencil mode. When enabled, the vertex buffer will be
*   drawn twice on the GPU; a CW pass and a CCW pass. This avoids the need and 
*   performance loss of handling it manually.
*     The CW pass will use the regular stencil operations, the CCW pass will use the
*   'CCW' variants of stencil operations.
*
*   Parameters:
*     - state       : two sided stencil state
*
*   Returns:
*     'true' on success, or 'false' on failure.
*/
bool    DX9_SetStencilTwoSided( bool state );
/*
*   Description:
*     Set stencil compare function. The format of the test is: 'REF CMP VAL'
*
*   Parameters:
*     - op          : stencil compare operation
*
*   Returns:
*     'true' on success, or 'false' on failure.
*/
bool    DX9_SetStencilFunc( dx9_compare_op op );
/*
*   Description:
*     Set stencil compare reference.
*
*   Parameters:
*     - value       : stencil reference value (0~255)
*
*   Returns:
*     'true' on success, or 'false' on failure.
*/
bool    DX9_SetStencilRef( uint32_t value );
/*
*   Description:
*     Set stencil operations for CW triangles in the case of a stencil test fail, Z
*   test fail, and a stencil test pass.
*
*   Parameters:
*     - op          : stencil operation
*
*   Returns:
*     'true' on success, or 'false' on failure.
*/
bool    DX9_SetStencilFail(  dx9_stencil_op op );
bool    DX9_SetStencilZFail( dx9_stencil_op op );
bool    DX9_SetStencilPass(  dx9_stencil_op op );
/*
*   Description:
*     Set stencil operations for CCW triangles in the case of a stencil test fail, Z
*   test fail, and a stencil test pass.
*
*   Parameters:
*     - op          : stencil operation
*
*   Returns:
*     'true' on success, or 'false' on failure.
*/
bool    DX9_SetStencilFailCCW(  dx9_stencil_op op );
bool    DX9_SetStencilZFailCCW( dx9_stencil_op op );
bool    DX9_SetStencilPassCCW(  dx9_stencil_op op );
/*
*   Description:
*     Set stencil read and write value mask. Eg. '(REF & MASK) CMP (VAL & MASK)' and
*   'VAL = (VAL & ~MASK) | (NEWVAL & MASK)'
*
*   Parameters:
*     - op          : stencil operation (0~255)
*
*   Returns:
*     'true' on success, or 'false' on failure.
*/
bool    DX9_SetStencilReadMask(  uint32_t mask );
bool    DX9_SetStencilWriteMask( uint32_t mask );

/****** Color Write *****************************************************************/
/*
*   Description:
*     Set color write bits.
* 
*   Parameters:
*     - flags       : color write bits (DX9_COL_###)
*
*   Returns:
*     'true' on success, or 'false' on failure.
*/
bool    DX9_SetColorWrite( uint32_t flags );

/****** Color Blending **************************************************************/
/*
*   Description:
*     Enable/disable alpha blending.
* 
*   Parameters:
*     - state       : alpha blending state
* 
*   Returns:
*     'true' on success, or 'false' on failure.
*/
bool    DX9_SetAlphaBlendEnable( bool state );
/*
*   Description:
*     Set source and destination blending operations.
* 
*   Parameters:
*     - op          : color blending operation
* 
*   Returns:
*     'true' on success, or 'false' on failure.
*/
bool    DX9_SetSrcBlend( dx9_blend_op op );
bool    DX9_SetDstBlend( dx9_blend_op op );

/****** Alpha Test ******************************************************************/
/*
*   Description:
*     Set alpha test compare function
* 
*   Parameters:
*     - op          : alpha test compare operation
* 
*   Returns:
*     'true' on success, or 'false' on failure.
*/
bool    DX9_SetAlphaFunc( dx9_compare_op op );

/****** Triangle Culling ************************************************************/
/*
*   Description:
*     Set triangle culling mode
* 
*   Parameters:
*     - mode        : triangle culling mode
* 
*   Returns:
*     'true' on success, or 'false' on failure.
*/
bool    DX9_SetCulling( dx9_cull_mode mode );

/****** Point Primitive *************************************************************/
/*
*   Description:
*     Set point primitive size in pixels.
* 
*   Parameters:
*     - size       : point primitive size
* 
*   Returns:
*     'true' on success, or 'false' on failure.
*/
bool    DX9_SetPointSize(   float size  );
/*
*   Description:
*     Enable/disable point primitive scaling depending on distance.
* 
*   Parameters:
*     - state       : point scaling state
* 
*   Returns:
*     'true' on success, or 'false' on failure.
*/
bool    DX9_SetPointScaleEnable(  bool  state );

/************************************************************************************/
/*
*   Vertex Shader
*/

/****** Get Vertex Shader ***********************************************************/
/*
*   Description:
*     Load a pre-compiled vertex shader file, usually '.fxc'.
* 
*   Examples:
*     - DX9_LoadVtxShader("vs.fxc");
* 
*   Parameters:
*     - puPath      : path to shader file (ASCII/UTF-8)
* 
*   Returns:
*     pointer to a vertex shader, or 'nullptr' on failure.
*/
dx9_vtx_shader* DX9_LoadVtxShader( const char* puPath );
/*
*   Description:
*     Load and compile a vertex shader source file. It is not recommended to use
*   this in production code.
* 
*   Examples:
*     - DX9_CompileVtxShader("vs.hlsl", "main", "vs_3_0");
* 
*   Parameters:
*     - puPath      : path to source file (ASCII/UTF-8)
*     - pcFunc      : name of the entry point function
*     - pcProfile   : shader profile name, eg. "vs_3_0"
* 
*   Returns:
*     pointer to a vertex shader, or 'nullptr' on failure.
*/
dx9_vtx_shader* DX9_CompileVtxShader( const char* puPath, const char* pcFunc, const char* pcProfile );

/****** Set Vertex Shader ***********************************************************/
/*
*   Description:
*     Set the vertex shader.
* 
*   Parameters:
*     - pVtxShader  : vertex shader pointer
* 
*   Returns:
*     'true' on success, or 'false' on failure.
*/
bool    DX9_SetVtxShader( dx9_vtx_shader* pVtxShader );

/****** Set Vertex Shader Constant **************************************************/
/*
*   Description:
*     Set vertex shader constants as float (F) or integer (I).
* 
*   Parameters:
*     - p           : data pointer
*     - reg         : start shader register index
*     - nb          : data count, eg. 'sizeof(*p) * nb'
* 
*   Returns:
*     'true' on success, or 'false' on failure.
*/
bool    DX9_SetVtxShaderConstantF( const void* p, uint32_t reg, size_t nb );
bool    DX9_SetVtxShaderConstantI( const void* p, uint32_t reg, size_t nb );

/************************************************************************************/
/*
*   Pixel Shader
*/

/****** Get Pixel Shader ************************************************************/
/*
*   Description:
*     Load a pre-compiled pixel shader file, usually '.fxc'.
* 
*   Examples:
*     - DX9_LoadPxlShader("ps.fxc");
* 
*   Parameters:
*     - puPath      : path to shader file (ASCII/UTF-8)
* 
*   Returns:
*     pointer to a pixel shader, or 'nullptr' on failure.
*/
dx9_pxl_shader* DX9_LoadPxlShader( const char* puPath );
/*
*   Description:
*     Load and compile a pixel shader source file. It is not recommended to use this
*   in production code.
* 
*   Examples:
*     - DX9_CompilePxlShader("ps.hlsl", "main", "ps_3_0");
* 
*   Parameters:
*     - puPath      : path to source file (ASCII/UTF-8)
*     - pcFunc      : name of the entry point function
*     - pcProfile   : shader profile name, eg. "ps_3_0"
* 
*   Returns:
*     pointer to a pixel shader, or 'nullptr' on failure.
*/
dx9_pxl_shader* DX9_CompilePxlShader( const char* puPath, const char* pcFunc, const char* pcProfile );

/****** Set Pixel Shader ************************************************************/
/*
*   Description:
*     Set the pixel shader.
* 
*   Parameters:
*     - pPxlShader  : pixel shader pointer
* 
*   Returns:
*     'true' on success, or 'false' on failure.
*/
bool    DX9_SetPxlShader( dx9_pxl_shader* pPxlShader );

/****** Set Pixel Shader Constant ***************************************************/
/*
*   Description:
*     Set pixel shader constants as float (F) or integer (I).
* 
*   Parameters:
*     - p           : data pointer
*     - reg         : start shader register index
*     - nb          : data count, eg. 'sizeof(*p) * nb'
* 
*   Returns:
*     'true' on success, or 'false' on failure.
*/
bool    DX9_SetPxlShaderConstantF( const void* p, uint32_t reg, size_t nb );
bool    DX9_SetPxlShaderConstantI( const void* p, uint32_t reg, size_t nb );

/************************************************************************************/
/*
*   Vertex Declaration
*/

/****** Create Vertex Declaration ***************************************************/
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

/****** Set Vertex Declaration ******************************************************/
/*
*   Description:
*     Set the current vertex declaration.
* 
*   Parameters:
*     - pVtxDecl    : vertex declaration pointer
* 
*   Returns:
*     'true' on success, or 'false' on failure.
*/
bool    DX9_SetVtxDecl( dx9_vtx_decl* pVtxDecl );

/************************************************************************************/
/*
*   Draw Primitive List
*/

/****** Draw Primitive **************************************************************/
/*
*   Description:
*     Draw primitive list from declared vertex buffer.
* 
*   Parameters:
*     - type        : primitive type
*     - idxStart    : vertex index to draw from
*     - nbPrim      : number of primitives to draw
* 
*   Returns:
*     'true' on success, or 'false' on failure.
*/
bool    DX9_DrawPrimitive( dx9_pri_type type, size_t idxStart, size_t nbPrim );
/*
*   Description:
*     Draw primitive list from a user-defined vertex buffer. This is slower than
*   regular 'DrawPrimitive'.
* 
*   Parameters:
*     - type        : primitive type
*     - nbPrim      : number of primitives to draw
*     - pVtxBuf     : vertex buffer to draw from
*     - szStride    : stride size of each vertex in bytes
* 
*   Returns:
*     'true' on success, or 'false' on failure.
*/
bool    DX9_DrawPrimitiveUP( dx9_pri_type type, size_t nbPrim, const void* pVtxBuf, size_t szStride );

/************************************************************************************/
/*
*   Render State Save/Load
*/

/****** Vertex Shader ***************************************************************/
/*
*   Description:
*     Save/load current vertex shader for restoring a previous state.
* 
*   Returns:
*     'true' on success, or 'false' on failure.
*/
bool    DX9_SaveVtxShaderState( void );
bool    DX9_LoadVtxShaderState( void );

/****** Pixel Shader ****************************************************************/
/*
*   Description:
*     Save/load current pixel shader for restoring a previous state.
* 
*   Returns:
*     'true' on success, or 'false' on failure.
*/
bool    DX9_SavePxlShaderState( void );
bool    DX9_LoadPxlShaderState( void );

/****** Vertex Declaration **********************************************************/
/*
*   Description:
*     Save/load current vertex declaration for restoring a previous state.
* 
*   Returns:
*     'true' on success, or 'false' on failure.
*/
bool    DX9_SaveVtxDeclState( void );
bool    DX9_LoadVtxDeclState( void );

/****** Z Buffer ********************************************************************/
/*
*   Description:
*     Save/load current Z buffering state for restoring a previous state.
* 
*   Returns:
*     'true' on success, or 'false' on failure.
*/
bool    DX9_SaveZEnableState( void );
bool    DX9_LoadZEnableState( void );
/*
*   Description:
*     Save/load current Z write state for restoring a previous state.
* 
*   Returns:
*     'true' on success, or 'false' on failure.
*/
bool    DX9_SaveZWriteState( void );
bool    DX9_LoadZWriteState( void );

/****** Stencil Buffer **************************************************************/
/*
*   Description:
*     Save/load current stencil buffer state for restoring a previous state.
* 
*   Returns:
*     'true' on success, or 'false' on failure.
*/
bool    DX9_SaveStencilEnableState( void );
bool    DX9_LoadStencilEnableState( void );
/*
*   Description:
*     Save/load current stencil two sided state for restoring a previous state.
* 
*   Returns:
*     'true' on success, or 'false' on failure.
*/
bool    DX9_SaveStencilTwoSidedState( void );
bool    DX9_LoadStencilTwoSidedState( void );
/*
*   Description:
*     Save/load current stencil compare function for restoring a previous state.
* 
*   Returns:
*     'true' on success, or 'false' on failure.
*/
bool    DX9_SaveStencilFuncState( void );
bool    DX9_LoadStencilFuncState( void );
/*
*   Description:
*     Save/load current stencil reference for restoring a previous state.
* 
*   Returns:
*     'true' on success, or 'false' on failure.
*/
bool    DX9_SaveStencilRefState( void );
bool    DX9_LoadStencilRefState( void );
/*
*   Description:
*     Save/load current stencil CW fail operation for restoring a previous state.
* 
*   Returns:
*     'true' on success, or 'false' on failure.
*/
bool    DX9_SaveStencilFailState( void );
bool    DX9_LoadStencilFailState( void );
/*
*   Description:
*     Save/load current stencil CW Z fail operation for restoring a previous state.
* 
*   Returns:
*     'true' on success, or 'false' on failure.
*/
bool    DX9_SaveStencilZFailState( void );
bool    DX9_LoadStencilZFailState( void );
/*
*   Description:
*     Save/load current stencil CW pass operation for restoring a previous state.
* 
*   Returns:
*     'true' on success, or 'false' on failure.
*/
bool    DX9_SaveStencilPassState( void );
bool    DX9_LoadStencilPassState( void );
/*
*   Description:
*     Save/load current stencil CCW fail operation for restoring a previous state.
* 
*   Returns:
*     'true' on success, or 'false' on failure.
*/
bool    DX9_SaveStencilFailCCWState( void );
bool    DX9_LoadStencilFailCCWState( void );
/*
*   Description:
*     Save/load current stencil CCW Z fail operation for restoring a previous state.
* 
*   Returns:
*     'true' on success, or 'false' on failure.
*/
bool    DX9_SaveStencilZFailCCWState( void );
bool    DX9_LoadStencilZFailCCWState( void );
/*
*   Description:
*     Save/load current stencil CCW pass operation for restoring a previous state.
* 
*   Returns:
*     'true' on success, or 'false' on failure.
*/
bool    DX9_SaveStencilPassCCWState( void );
bool    DX9_LoadStencilPassCCWState( void );
/*
*   Description:
*     Save/load current stencil read mask for restoring a previous state.
* 
*   Returns:
*     'true' on success, or 'false' on failure.
*/
bool    DX9_SaveStencilReadMaskState( void );
bool    DX9_LoadStencilReadMaskState( void );
/*
*   Description:
*     Save/load current stencil write mask for restoring a previous state.
* 
*   Returns:
*     'true' on success, or 'false' on failure.
*/
bool    DX9_SaveStencilWriteMaskState( void );
bool    DX9_LoadStencilWriteMaskState( void );

/****** Culling *********************************************************************/
/*
*   Description:
*     Save/load current culling state for restoring a previous state.
* 
*   Returns:
*     'true' on success, or 'false' on failure.
*/
bool    DX9_SaveCullingState( void );
bool    DX9_LoadCullingState( void );

/****** Color ***********************************************************************/
/*
*   Description:
*     Save/load current color write state for restoring a previous state.
* 
*   Returns:
*     'true' on success, or 'false' on failure.
*/
bool    DX9_SaveColorWriteState( void );
bool    DX9_LoadColorWriteState( void );

/****** Alpha Test ******************************************************************/
/*
*   Description:
*     Save/load current alpha test compare function for restoring a previous state.
* 
*   Returns:
*     'true' on success, or 'false' on failure.
*/
bool    DX9_SaveAlphaFuncState( void );
bool    DX9_LoadAlphaFuncState( void );

/****** Blending ********************************************************************/
/*
*   Description:
*     Save/load current alpha blend state for restoring a previous state.
* 
*   Returns:
*     'true' on success, or 'false' on failure.
*/
bool    DX9_SaveAlphaBlendEnableState( void );
bool    DX9_LoadAlphaBlendEnableState( void );
/*
*   Description:
*     Save/load current alpha source blend state for restoring a previous state.
* 
*   Returns:
*     'true' on success, or 'false' on failure.
*/
bool    DX9_SaveSrcBlendState( void );
bool    DX9_LoadSrcBlendState( void );
/*
*   Description:
*     Save/load current alpha destination blend state for restoring a previous
*   state.
* 
*   Returns:
*     'true' on success, or 'false' on failure.
*/
bool    DX9_SaveDstBlendState( void );
bool    DX9_LoadDstBlendState( void );

/** EXTERN_END **/
#ifdef __cplusplus
}
#endif

#endif/*H_DX9CTRL*/