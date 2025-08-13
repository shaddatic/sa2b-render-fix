/*
*   SA2 Render Fix - '/rfapi_shader.h'
*
*   Description:
*     The 'Shader' API module is for loading, compiling, and replacing the Game's vanilla
*   shaders with your own.
* 
*   Version History:
*     - v1.3.0.0        : Version 0, initial release
*     - v1.4.1.0        : Version 1, added 'GetGame#Shader' & 'Compile#Shader' functions.
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
    *     Shader handle; or 'nullptr' on failure.
    */
    RFS_VSHADER* (__cdecl* LoadVShader)( const c8* puPath );
    RFS_PSHADER* (__cdecl* LoadPShader)( const c8* puPath );

    /**** Set Game Shader ***********************************/
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
    *     - p#Shader    : shader to set                                          [opt: nullptr]
    */
    void (__cdecl* SetGameVShader)( RFE_SHADERIX ixShader, RFS_VSHADER* pVShader );
    void (__cdecl* SetGamePShader)( RFE_SHADERIX ixShader, RFS_PSHADER* pPShader );

    /****** Version >= 1 ************************************************************************/

    /**** Get Game Shader ***********************************/
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
    RFS_VSHADER* (__cdecl* GetGameVShader)( RFE_SHADERIX ixShader );
    RFS_PSHADER* (__cdecl* GetGamePShader)( RFE_SHADERIX ixShader );

    /**** Compile Shader ************************************/
    /*
    *   Description:
    *     Compile a pixel or vertex shader from a source file (.hlsl) with changeable macros.
    *
    *   Parameters:
    *     - puPath      : path to the source file, including the extension
    *     - pMacros     : list of macros terminated by a null'd entry
    *
    *   Returns:
    *     Shader handle; or 'nullptr' on failure.
    */
    RFS_VSHADER* (__cdecl* CompileVShader)( const c8* puPath, const RFS_MACRO* pMacros );
    RFS_PSHADER* (__cdecl* CompilePShader)( const c8* puPath, const RFS_MACRO* pMacros );
}
RFAPI_SHADER;

#endif/*H_RFAPI_SHADER*/
