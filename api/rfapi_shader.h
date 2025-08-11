/*
*   SA2 Render Fix - '/rfapi_shader.h'
*
*   Description:
*     The 'Shader' API module is for loading, compiling, and replacing the Game's vanilla
*   shaders with your own.
* 
*   Version History:
*     - v1.3.0.0: Version 0, initial release
* 
*   Availability:
*     - RF_EarlyInit    : Yes
*     - RF_Init         : Yes
*     - After Init      : Yes
*/
#ifndef H_RFAPI_SHADER
#define H_RFAPI_SHADER

/********************************/
/*  Opaque Types                */
/********************************/
/****** Shaders *********************************************************************************/
typedef struct dx9_vtx_shader       dx9_vtx_shader; /* 'IDirect3DVertexShader9'                 */
typedef struct dx9_pxl_shader       dx9_pxl_shader; /* 'IDirect3DPixelShader9'                  */

/********************************/
/*  API Structures              */
/********************************/
/****** Shader API ******************************************************************************/
typedef struct
{
    uint32_t version;               /* structure version                                        */

    /****** Version >= 0 ************************************************************************/

    /**** Load shader ***************************************/
    /*
    *   Description:
    *     Load a pre-compiled shader file (usually .fxc).
    *
    *   Parameters:
    *     - puPath      : file path to pre-compiled shader
    *   
    *   Returns:
    *     Loaded DX9 shader object; or 'nullptr' on failure.
    */
    dx9_vtx_shader* (__cdecl* LoadVtxShader)( const c8* puPath );
    dx9_pxl_shader* (__cdecl* LoadPxlShader)( const c8* puPath );

    /**** Replace shader ************************************/
    /*
    *   Description:
    *     Replace a vanilla game shader by index.
    *
    *   Parameters:
    *     - ixShader    : Index of the shader as called for by the game
    *     - p___Shader  : Pointer to the new shader object
    */
    void (__cdecl* ReplaceVtxShader)( int ixShader, dx9_vtx_shader* pVtxShader );
    void (__cdecl* ReplacePxlShader)( int ixShader, dx9_pxl_shader* pPxlShader );
}
RFAPI_SHADER;

#endif/*H_RFAPI_SHADER*/
