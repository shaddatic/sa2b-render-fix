/*
*   dx9ctrl (SA2B) - '/dx9_getstate.h'
*
*   Description:
*     DirectX 9 control library for SA2PC get render state header.
*/
#ifndef H_DX9CTRL_GETSTATE
#define H_DX9CTRL_GETSTATE

/********************************/
/*  Includes                    */
/********************************/
/****** DX9 Control *****************************************************************************/
#include <dx9ctrl/dx9_common.h>      /* dx9 common                                              */
#include <dx9ctrl/dx9_renderstate.h> /* blend modes                                             */
#include <dx9ctrl/dx9_shader.h>      /* shader types                                            */
#include <dx9ctrl/dx9_vertex.h>      /* vertex types                                            */

DX9_HEADER_START

/********************************/
/*  Prototypes                  */
/********************************/
/************************************************************************************************/
/*
*   Render State
*/
/****** Shading Mode ****************************************************************************/
/*
*   Description:
*     Get the current polygon shading mode.
* 
*   Returns:
*     Current shading mode setting; or '-1' on failure.
*/
dx9_shade_mode DX9_GetShadingMode( void );

/****** Z Buffer ********************************************************************************/
/*
*   Description:
*     Get the current Z buffer state.
* 
*   Returns:
*     Current Z buffer state (true/false); or '-1' on failure.
*/
dx9_int DX9_GetZEnable( void );
/*
*   Description:
*     Get the current Z write state.
* 
*   Returns:
*     Current Z write state (true/false); or '-1' on failure.
*/
dx9_int DX9_GetZWrite( void );
/*
*   Description:
*     Get the current Z compare function.
* 
*   Returns:
*     Current Z function; or '-1' on failure.
*/
dx9_blend_op DX9_GetZFunc( void );

/****** Stencil *********************************************************************************/
/*
*   Description:
*     Get the current stencil buffer state.
* 
*   Returns:
*     Current stencil buffer state (true/false); or '-1' on failure.
*/
dx9_int DX9_GetStencilEnable( void );
/*
*   Description:
*     Get the current two sided stencil state.
* 
*   Returns:
*     Current two sided state (true/false); or '-1' on failure.
*/
dx9_int DX9_GetStencilTwoSided( void );
/*
*   Description:
*     Get the current stencil compare mode.
* 
*   Returns:
*     Current stencil compare mode; or '-1' on failure.
*/
dx9_compare_op DX9_GetStencilFunc( void );
/*
*   Description:
*     Get the current stencil reference.
* 
*   Returns:
*     Current stencil reference (uint8); or '-1' on failure.
*/
dx9_int DX9_GetStencilRef( void );
/*
*   Description:
*     Get the current stencil read mask.
* 
*   Returns:
*     Current stencil read mask (uint8); or '-1' on failure.
*/
dx9_int DX9_GetStencilReadMask( void );
/*
*   Description:
*     Get the current stencil write mask.
* 
*   Returns:
*     Current stencil write mask (uint8); or '-1' on failure.
*/
dx9_int DX9_GetStencilWriteMask( void );

/****** Culling *********************************************************************************/
/*
*   Description:
*     Get the current polygon culling mode.
* 
*   Returns:
*     Current polygon culling mode; or '-1' on failure.
*/
dx9_cull_mode DX9_GetFaceCulling( void );

/****** Color Write *****************************************************************************/
/*
*   Description:
*     Get the current color write flags.
* 
*   Returns:
*     Current color write flags; or '-1' on failure.
*/
dx9_int DX9_GetColorWrite( void );

/****** Blending ********************************************************************************/
/*
*   Description:
*     Get the current alpha blending state.
* 
*   Returns:
*     Current alpha blending state (true/false); or '-1' on failure.
*/
dx9_int DX9_GetAlphaBlendEnable( void );
/*
*   Description:
*     Get the current alpha test compare function.
* 
*   Returns:
*     Current alpha compare function; or '-1' on failure.
*/
dx9_compare_op DX9_GetAlphaFunc( void );
/*
*   Description:
*     Get the current alpha blend functions.
* 
*   Returns:
*     Current alpha blend function; or '-1' on failure.
*/
dx9_blend_op DX9_GetSrcBlend( void );
dx9_blend_op DX9_GetDstBlend( void );

/****** Point Primitive *************************************************************************/
/*
*   Description:
*     Get the current point primitive size.
* 
*   Returns:
*     Current point primitive size; or '-1.f' on failure.
*/
dx9_float DX9_GetPointSize( void );
/*
*   Description:
*     Get the current point primitive distance scaling state.
* 
*   Returns:
*     Current point primitive distance scaling state (true/false); or '-1' on failure.
*/
dx9_int DX9_GetPointScaleEnable( void );

/************************************************************************************************/
/*
*   Shader
*/
/****** Vertex Shader ***************************************************************************/
/*
*   Description:
*     Get the current vertex shader.
* 
*   Returns:
*     Current set vertex shader; or 'nullptr' on failure.
*/
dx9_vtx_shader* DX9_GetVtxShader( void );
/*
*   Description:
*     Get the current shader constant register values.
* 
*   Parameters:
*     - p           : constant values destination buffer
*     - nb          : number of constant registers to read
*     - reg         : start register to read from
* 
*   Returns:
*     'p' argument; or 'nullptr' on failure.
*/
dx9_float4* DX9_GetVtxShaderConstantF( dx9_float4* p, dx9_size nb, dx9_uint reg );
dx9_int4*   DX9_GetVtxShaderConstantI( dx9_int4*   p, dx9_size nb, dx9_uint reg );
dx9_bool*   DX9_GetVtxShaderConstantB( dx9_bool*   p, dx9_size nb, dx9_uint reg );

/****** Pixel Shader ****************************************************************************/
/*
*   Description:
*     Get the current pixel shader.
* 
*   Returns:
*     Current set pixel shader; or 'nullptr' on failure.
*/
dx9_pxl_shader* DX9_GetPxlShader( void );
/*
*   Description:
*     Get the current shader constant register values.
*
*   Parameters:
*     - p           : constant values destination buffer
*     - nb          : number of constant registers to read
*     - reg         : start register to read from
* 
*   Returns:
*     'p' argument; or 'nullptr' on failure.
*/
dx9_float4* DX9_GetPxlShaderConstantF( dx9_float4* p, dx9_size nb, dx9_uint reg );
dx9_int4*   DX9_GetPxlShaderConstantI( dx9_int4*   p, dx9_size nb, dx9_uint reg );
dx9_bool*   DX9_GetPxlShaderConstantB( dx9_bool*   p, dx9_size nb, dx9_uint reg );

/************************************************************************************************/
/*
*   Vertex
*/
/****** Vertex Declaration **********************************************************************/
/*
*   Description:
*     Get the current vertex declaration.
* 
*   Returns:
*     Current vertex declaration; or 'nullptr' on failure.
*/
dx9_vtx_decl* DX9_GetVtxDecl( void );

/****** Vertex Declaration **********************************************************************/
/*
*   Description:
*     Get the current vertex buffer stream.
* 
*   Parameter:
*     - ixStream    : stream index
* 
*   Returns:
*     Current vertex buffer stream; or 'nullptr' on failure.
*/
dx9_vtx_buff* DX9_GetStreamSource( dx9_size ixStream );

DX9_HEADER_END

#endif/*H_DX9CTRL_GETSTATE*/
