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
*     - Before Init     : No
*     - At Init         : Yes
*     - After Init      : Yes
*/
#ifndef H_RFAPI_SHADER
#define H_RFAPI_SHADER

/********************************/
/*  Constants                   */
/********************************/
/****** API Module Version **********************************************************************/
#define RFAPI_SHADER_VER            (1) /* shader api version                                   */

/********************************/
/*  Opaque Types                */
/********************************/
/****** Shaders *********************************************************************************/
typedef struct rfshaderv            RFS_VSHADER; /* 'IDirect3DVertexShader9'                    */
typedef struct rfshaderp            RFS_PSHADER; /* 'IDirect3DPixelShader9'                     */

/********************************/
/*  Enums                       */
/********************************/
/****** Game Shaders ****************************************************************************/
typedef enum
{
    /**** 2D Shaders ****************************************/

    RFE_SHADERIX_UI,                /* 2d/ui shader                      [sonicuivs, sonicuips] */

    /**** Basic Model Shaders *******************************/

    RFE_SHADERIX_MDL_NONE,          /* no additional effects                 [sonicvs, sonicps] */
    RFE_SHADERIX_MDL_S,             /* use shadow texture                  [sonicvs, sonicps_s] */
    RFE_SHADERIX_MDL_F,             /* use fog                             [sonicvs, sonicps_f] */
    RFE_SHADERIX_MDL_FS,            /* use fog+stex                      [sonicvs, sonicps_s_f] */
    RFE_SHADERIX_MDL_P,             /* use palette                         [sonicvs, sonicps_p] */
    RFE_SHADERIX_MDL_PS,            /* use palette+stex                  [sonicvs, sonicps_s_p] */
    RFE_SHADERIX_MDL_PF,            /* use palette+fog                   [sonicvs, sonicps_f_p] */
    RFE_SHADERIX_MDL_PFS,           /* use palette+fog+stex            [sonicvs, sonicps_s_f_p] */

    /**** Other Model Shaders *******************************/

    RFE_SHADERIX_MDL_SIMPLE,        /* simple model/3d shader      [sonicvs_nolighting, sonicps_simple] */
    RFE_SHADERIX_MDL_SMOKE,         /* smoke model/3d shader       [sonicvs_nolighting, sonicps_smoke]  */
    RFE_SHADERIX_MDL_SHADOWGEN,     /* shadowgen model shader    [sonicvs_shadowgen, sonicps_shadowgen] */
    RFE_SHADERIX_MDL_CA,            /* soc model shader                  [sonicvs_normaluv, sonicps_ca] */

    /**** End Enum ******************************************/

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
    *     - ixShader    : shader index to replace or reset
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
    *     - ixShader    : shader index to get
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
    *     - pMacros     : list of macros terminated by a null'd entry            [opt: nullptr]
    *
    *   Returns:
    *     Shader handle; or 'nullptr' on failure.
    */
    RFS_VSHADER* (__cdecl* CompileVShader)( const c8* puPath, const RFS_MACRO* pMacros );
    RFS_PSHADER* (__cdecl* CompilePShader)( const c8* puPath, const RFS_MACRO* pMacros );
}
RFAPI_SHADER;

#endif/*H_RFAPI_SHADER*/
