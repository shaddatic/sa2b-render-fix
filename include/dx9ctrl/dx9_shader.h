/*
*   dx9ctrl (SA2B) - '/dx9_shader.h'
*
*   Description:
*     DirectX 9 control library for SA2PC shader header.
*/
#ifndef H_DX9CTRL_SHADER
#define H_DX9CTRL_SHADER

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
typedef struct dx9_vtx_shader       dx9_vtx_shader; /* IDirect3DVertexShader9                   */
typedef struct dx9_pxl_shader       dx9_pxl_shader; /* IDirect3DPixelShader9                    */

/********************************/
/*  Constants                   */
/********************************/
/****** Shader Constants ************************************************************************/
#define DX9_SCF_REGISTER_MAX        (223) /* shader constant (float4) max register              */
#define DX9_SCI_REGISTER_MAX        (15)  /* shader constant (int4) max register                */
#define DX9_SCB_REGISTER_MAX        (15)  /* shader constant (bool) max register                */

/********************************/
/*  Structures                  */
/********************************/
/****** Shader Macro ****************************************************************************/
typedef struct
{
    const char* pcName;             /* macro symbol (eg. 'MACRO')                               */
    const char* pcDef;              /* macro definition (eg. '1')                               */
}
dx9_macro;

/********************************/
/*  Prototypes                  */
/********************************/
/************************************************************************************************/
/*
*   Vertex Shader
*/
/****** Get Vertex Shader ***********************************************************************/
/*
*   Description:
*     Load a pre-compiled vertex shader file, usually '.fxc'.
* 
*   Examples:
*     - DX9_LoadVtxShader("vs.fxc");
* 
*   Parameters:
*     - puPath      : path to shader file                                         [ASCII/UTF-8]
* 
*   Returns:
*     pointer to a vertex shader; or 'nullptr' on failure.
*/
dx9_vtx_shader* DX9_LoadVtxShader( const char* puPath );
/*
*   Description:
*     Load and compile a vertex shader source file.
* 
*   Notes:
*     - Shader entry is always "main"
*     - Shader profile is always "vs_3_0"
* 
*   Parameters:
*     - puPath      : path to source file                                          [ASCII/UTF-8]
*     - pMacros     : Null terminated macro list                                  [opt: nullptr]
* 
*   Returns:
*     pointer to a vertex shader; or 'nullptr' on failure.
*/
dx9_vtx_shader* DX9_CompileVtxShader( const char* puPath, const dx9_macro* pMacros );

/****** Set Vertex Shader ***********************************************************************/
/*
*   Description:
*     Set the vertex shader.
* 
*   Parameters:
*     - pVtxShader  : vertex shader pointer
* 
*   Returns:
*     'true' on success; or 'false' on failure.
*/
bool    DX9_SetVtxShader( dx9_vtx_shader* pVtxShader );

/****** Set Vertex Shader Constant **************************************************************/
/*
*   Description:
*     Set vertex shader float (F), integer (I), or boolean (B) constant values.
* 
*   Parameters:
*     - reg         : start shader register index
*     - p           : constant values source buffer
*     - nb          : length of buffer/number of constant registers to write to
* 
*   Returns:
*     'true' on success; or 'false' on failure.
*/
bool    DX9_SetVtxShaderConstantF( dx9_uint reg, const dx9_float4* p, dx9_size nb );
bool    DX9_SetVtxShaderConstantI( dx9_uint reg, const dx9_int4*   p, dx9_size nb );
bool    DX9_SetVtxShaderConstantB( dx9_uint reg, const dx9_bool*   p, dx9_size nb );

/************************************************************************************************/
/*
*   Pixel Shader
*/
/****** Get Pixel Shader ************************************************************************/
/*
*   Description:
*     Load a pre-compiled pixel shader file, usually '.fxc'.
* 
*   Examples:
*     - DX9_LoadPxlShader("ps.fxc");
* 
*   Parameters:
*     - puPath      : path to shader file                                          [ASCII/UTF-8]
* 
*   Returns:
*     Created pixel shader; or 'nullptr' on failure.
*/
dx9_pxl_shader* DX9_LoadPxlShader( const char* puPath );
/*
*   Description:
*     Load and compile a pixel shader source file.
* 
*   Notes:
*     - Shader entry is always "main"
*     - Shader profile is always "ps_3_0"
* 
*   Parameters:
*     - puPath      : path to source file                                          [ASCII/UTF-8]
*     - pMacros     : Null terminated macro list                                  [opt: nullptr]
* 
*   Returns:
*     Created pixel shader; or 'nullptr' on failure.
*/
dx9_pxl_shader* DX9_CompilePxlShader( const char* puPath, const dx9_macro* pMacros );

/****** Set Pixel Shader ************************************************************************/
/*
*   Description:
*     Set the pixel shader.
* 
*   Parameters:
*     - pPxlShader  : pixel shader pointer
* 
*   Returns:
*     'true' on success; or 'false' on failure.
*/
bool    DX9_SetPxlShader( dx9_pxl_shader* pPxlShader );

/****** Set Pixel Shader Constant ***************************************************************/
/*
*   Description:
*     Set pixel shader float (F), integer (I), or boolean (B) constant values.
* 
*   Parameters:
*     - reg         : start shader register index
*     - p           : constant values source buffer
*     - nb          : length of buffer/number of constant registers to write to
* 
*   Returns:
*     'true' on success; or 'false' on failure.
*/
bool    DX9_SetPxlShaderConstantF( dx9_uint reg, const dx9_float4* p,  dx9_size nb );
bool    DX9_SetPxlShaderConstantI( dx9_uint reg, const dx9_int4*   p,  dx9_size nb );
bool    DX9_SetPxlShaderConstantB( dx9_uint reg, const dx9_bool*   p,  dx9_size nb );

DX9_HEADER_END

#endif/*H_DX9CTRL_SHADER*/
