/*
*   SA2 Render Fix - '/rf_shader.h'
*
*   Description:
*     Functions for loading/compiling shaders, and replacing game shaders.
*/
#ifndef H_RF_SHADER
#define H_RF_SHADER

/********************************/
/*  Includes                    */
/********************************/
/****** Dx9ctrl *********************************************************************************/
#include <dx9ctrl/dx9ctrl.h>        /* dx9ctrl                                                  */

EXTERN_START

/********************************/
/*  Prototypes                  */
/********************************/
/****** Compile Shader Source *******************************************************************/
/*
*   Description:
*     Compile a pixel or vertex shader from a local source file (rf/shader/#.hlsl) with
*   changeable macros.
*
*   Parameters:
*     - puSrcName   : name of the source file, excluding the extension
*     - pMacros     : list of macros terminated by a null'd entry
*
*   Returns:
*     Shader handle; or 'nullptr' on failure.
*/
dx9_vtx_shader* RF_CompileVtxShader( const c8* puSrcName, const dx9_macro* pMacros );
dx9_pxl_shader* RF_CompilePxlShader( const c8* puSrcName, const dx9_macro* pMacros );

/****** Load Compiled Shader ********************************************************************/
/*
*   Description:
*     Load a local pre-compiled pixel or vertex shader (rf/shader/#.fxc).
*
*   Parameters:
*     - puSrcName   : name of the shader file, excluding the extension
*
*   Returns:
*     Shader handle; or 'nullptr' on failure.
*/
dx9_vtx_shader* RF_LoadVtxShader( const c8* puSrcName );
dx9_pxl_shader* RF_LoadPxlShader( const c8* puSrcName );

/****** Replace Game Shader *********************************************************************/
/*
*   Description:
*     Replace a game shader via it's shader index.
*
*   Parameters:
*     - index       : shader index to replace
*     - p###Shader  : shader handle
*/
void    RF_ReplaceVtxShader( int index, dx9_vtx_shader* pVtxShader );
void    RF_ReplacePxlShader( int index, dx9_pxl_shader* pPxlShader );

/****** Direct Shader **************************************************************************/
/*
*   Description:
*     Compile a pixel or vertex shader from any source file (.hlsl) with changeable macros.
*
*   Parameters:
*     - puSrcPath   : path to the source file, including the extension
*     - pMacros     : list of macros terminated by a null'd entry
*
*   Returns:
*     Shader handle; or 'nullptr' on failure.
*/
dx9_vtx_shader* RF_DirectCompileVtxShader( const c8* puSrcPath, const dx9_macro* pMacros );
dx9_pxl_shader* RF_DirectCompilePxlShader( const c8* puSrcPath, const dx9_macro* pMacros );
/*
*   Description:
*     Load any pre-compiled pixel or vertex shader (.fxc).
*
*   Parameters:
*     - puSrcPath   : path to the shader file, including the extension
*
*   Returns:
*     Shader handle; or 'nullptr' on failure.
*/
dx9_vtx_shader* RF_DirectLoadVtxShader( const c8* fpath );
dx9_pxl_shader* RF_DirectLoadPxlShader( const c8* fpath );

EXTERN_END

#endif/*H_RF_SHADER*/
