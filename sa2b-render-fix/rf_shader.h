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
typedef void                d3d_vtx_shader;
typedef void                d3d_pxl_shader;

/************************/
/*  Functions           */
/************************/
EXTERN_START
/** Load compiled D3D Shader file (.fxc) **/
d3d_vtx_shader* RF_LoadVtxShader(const char* fname);
d3d_pxl_shader* RF_LoadPxlShader(const char* fname);

/** Replace game shader by index **/
void    RF_ReplaceVtxShader(int index, d3d_vtx_shader* pVtxShader);
void    RF_ReplacePxlShader(int index, d3d_pxl_shader* pPxlShader);

EXTERN_END

#endif/*_RF_SHADER_H_*/