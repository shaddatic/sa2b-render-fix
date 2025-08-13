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
/****** API *************************************************************************************/
#include <rfapi_shader.h>           /* shader api                                               */

EXTERN_START

/********************************/
/*  Prototypes                  */
/********************************/
/****** Init ************************************************************************************/
/*
*   Description:
*     Init shader module, and load Render Fix's custom game shaders.
*/
void    RF_ShaderInit( void );

/****** Set/Get Game Shader *********************************************************************/
/*
*   Description:
*     Replace a game shader index with custom shaders.
*
*   Notes:
*     - Using 'nullptr' will restore the shader index to vanilla.
*     - If you're only replacing only one shader in a shader index, please try to have the
*       input and output structures match vanilla to reduce conflicts.
*
*   Parameters:
*     - index       : shader index to replace or reset
*     - p#Shader    : shader to set                                              [opt: nullptr]
*/
void    RF_SetGameVShader( RFE_SHADERIX ixShader, RFS_VSHADER* pVShader );
void    RF_SetGamePShader( RFE_SHADERIX ixShader, RFS_PSHADER* pPShader );
/*
*   Description:
*     Get the current shaders in a game shader index.
*
*   Parameters:
*     - index       : shader index to get
*
*   Returns:
*     Shader set at the shader index; or 'nullptr' if the vanilla shader is still set.
*/
RFS_VSHADER* RF_GetGameVShader( RFE_SHADERIX ixShader );
RFS_PSHADER* RF_GetGamePShader( RFE_SHADERIX ixShader );

/****** Set DX9 Shader **************************************************************************/
/*
*   Description:
*     Set shaders to DirectX 9 device and to Magic's shader cache.
*
*   Parameters:
     - p#Shader    : shader to set
*/
void    RF_DirectSetVShader( RFS_VSHADER* pVShader );
void    RF_DirectSetPShader( RFS_PSHADER* pPShader );

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
RFS_VSHADER* RF_CompileVtxShader( const c8* puSrcName, const RFS_MACRO* pMacros );
RFS_PSHADER* RF_CompilePxlShader( const c8* puSrcName, const RFS_MACRO* pMacros );
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
RFS_VSHADER* RF_DirectCompileVtxShader( const c8* puSrcPath, const RFS_MACRO* pMacros );
RFS_PSHADER* RF_DirectCompilePxlShader( const c8* puSrcPath, const RFS_MACRO* pMacros );

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
RFS_VSHADER* RF_LoadVtxShader( const c8* puSrcName );
RFS_PSHADER* RF_LoadPxlShader( const c8* puSrcName );
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
RFS_VSHADER* RF_DirectLoadVtxShader( const c8* fpath );
RFS_PSHADER* RF_DirectLoadPxlShader( const c8* fpath );

EXTERN_END

#endif/*H_RF_SHADER*/
