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
typedef struct rfs_vshader          RFS_VSHADER; /* 'IDirect3DVertexShader9'                    */
typedef struct rfs_pshader          RFS_PSHADER; /* 'IDirect3DPixelShader9'                     */

/********************************/
/*  Enums                       */
/********************************/
/****** Game Shaders ****************************************************************************/
typedef enum
{
    RFE_SHADERIX_UI,                /* 2d/ui shader                                             */

    RFE_SHADERIX_MDL_NONE,          /* model, no additional effects                             */
    RFE_SHADERIX_MDL_S,             /* model, use shadow texture                                */
    RFE_SHADERIX_MDL_F,             /* model, use fog                                           */
    RFE_SHADERIX_MDL_FS,            /* model, use fog+stex                                      */
    RFE_SHADERIX_MDL_P,             /* model, use palette                                       */
    RFE_SHADERIX_MDL_PS,            /* model, use palette+stex                                  */
    RFE_SHADERIX_MDL_PF,            /* model, use palette+fog                                   */
    RFE_SHADERIX_MDL_PFS,           /* model, use palette+fog+stex                              */

    RFE_SHADERIX_MDL_SIMPLE,        /* mode, "simple" model/3d shader                           */
    RFE_SHADERIX_MDL_SMOKE,         /* mode, "smoke" model/3d shader                            */
    RFE_SHADERIX_MDL_SHADOWGEN,     /* mode, shadowgen model shader                             */
    RFE_SHADERIX_MDL_CA,            /* mode, soc model shader                                   */

    NB_RFE_SHADERIX,                /* enum count                                               */
}
RFE_SHADERIX;

/********************************/
/*  Structures                  */
/********************************/
/****** Shader Macro ****************************************************************************/
typedef struct
{
    const char* pcSym;              /* macro symbol (eg. "USE_FEATURE")                         */
    const char* pcDef;              /* macro definition (eg. "1")                               */
}
RFS_MACRO;

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
