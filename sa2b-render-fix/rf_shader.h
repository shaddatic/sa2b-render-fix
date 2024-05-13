/*
*   SA2 Render Fix - '/rf_shader.h'
*
*   Description:
*       Functions for loading Render Fix shaders.
*
*   Contributors:
*   -   Shaddatic
*/
#ifndef _RF_SHADER_H_
#define _RF_SHADER_H_

/************************/
/*  Includes            */
/************************/
#include <sa2b/ninja/ninja.h>

/************************/
/*  Local Types         */
/************************/
typedef struct dx9_vtx_shader   dx9_vtx_shader;
typedef struct dx9_pxl_shader   dx9_pxl_shader;

/************************/
/*  Functions           */
/************************/
EXTERN_START
/** Load compiled D3D Shader file (.fxc) **/
dx9_vtx_shader* RF_LoadVtxShader( const char* fname );
dx9_pxl_shader* RF_LoadPxlShader( const char* fname );

/** Replace game shader by index **/
void    RF_ReplaceVtxShader( int index, dx9_vtx_shader* pVtxShader );
void    RF_ReplacePxlShader( int index, dx9_pxl_shader* pPxlShader );

/** Directly load compiled D3D Shader file **/
dx9_vtx_shader* RF_DirectLoadVtxShader( const utf8* fpath );
dx9_pxl_shader* RF_DirectLoadPxlShader( const utf8* fpath );

EXTERN_END

#endif/*_RF_SHADER_H_*/
