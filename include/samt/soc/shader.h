/*
*   SAMT for Sonic Adventure 2 (PC, 2012) - '/soc/shader.h'
*
*   Descriptions:
*     SOC's shader engine for the HD ports.
*/
#ifndef H_SOC_SHADER
#define H_SOC_SHADER

EXTERN_START

/********************************/
/*  Constants                   */
/********************************/
/****** Mode Flags ******************************************************************************/
#define SHADERMDL_FLAG_SHADOWTEX    (1) /* use shadow texture                                   */
#define SHADERMDL_FLAG_FOG          (2) /* use fog                                              */
#define SHADERMDL_FLAG_PALETTE      (4) /* use paletted texture                                 */

/********************************/
/*  Enums                       */
/********************************/
/****** Shader Type *****************************************************************************/
typedef enum
{
    SHADER_TYPE_UI,                 /* 2d/ui shader                                             */

    SHADER_TYPE_MDL,                /* normal model/3d shader                                   */
    SHADER_TYPE_MDL_SIMPLE,         /* "simple" model/3d shader                                 */
    SHADER_TYPE_MDL_SMOKE,          /* "smoke" model/3d shader                                  */
    SHADER_TYPE_MDL_SHADOWGEN,      /* shadowgen model shader                                   */
    SHADER_TYPE_MDL_CA,             /* soc model shader                                         */

    NB_SHADER_TYPE,                 /* enum count                                               */
}
SHADER_TYPE;

/****** Model Modes *****************************************************************************/
typedef enum
{
    SHADERMDL_MODE_NONE,            /* no additional flags                                      */

    SHADERMDL_MODE_S,               /* use shadow texture                                       */
    SHADERMDL_MODE_F,               /* use fog                                                  */
    SHADERMDL_MODE_FS,              /* use fog+stex                                             */
    SHADERMDL_MODE_P,               /* use palette                                              */
    SHADERMDL_MODE_PS,              /* use palette+stex                                         */
    SHADERMDL_MODE_PF,              /* use palette+fog                                          */
    SHADERMDL_MODE_PFS,             /* use palette+fog+stex                                     */

    NB_SHADERMDL_MODE,              /* enum count                                               */
}
SHADERMDL_MODE;

/****** Direct Shader Index *********************************************************************/
typedef enum 
{
    SHADER_INDEX_UI,                /* 2d/ui shader                                             */

    SHADER_INDEX_MDL_NONE,          /* model, no additional effects                             */
    SHADER_INDEX_MDL_S,             /* model, use shadow texture                                */
    SHADER_INDEX_MDL_F,             /* model, use fog                                           */
    SHADER_INDEX_MDL_FS,            /* model, use fog+stex                                      */
    SHADER_INDEX_MDL_P,             /* model, use palette                                       */
    SHADER_INDEX_MDL_PS,            /* model, use palette+stex                                  */
    SHADER_INDEX_MDL_PF,            /* model, use palette+fog                                   */
    SHADER_INDEX_MDL_PFS,           /* model, use palette+fog+stex                              */
    SHADER_INDEX_MDL_SIMPLE,        /* mode, "simple" model/3d shader                           */
    SHADER_INDEX_MDL_SMOKE,         /* mode, "smoke" model/3d shader                            */
    SHADER_INDEX_MDL_SHADOWGEN,     /* mode, shadowgen model shader                             */
    SHADER_INDEX_MDL_CA,            /* mode, soc model shader                                   */

    NB_SHADER_INDEX,                /* enum count                                               */
}
SHADER_INDEX;

/********************************/
/*  Game Defs                   */
/********************************/
/****** Shader Type *****************************************************************************/
#define ShaderTypeLock              DATA_REF(bool, 0x01A55709)
#define ShaderTypeLast              DATA_REF(s32 , 0x01A5579C)

/****** Model Modes *****************************************************************************/
#define ShaderModelMode             DATA_REF(s32, 0x01AF1960)

/********************************/
/*  Prototypes                  */
/********************************/
/****** Set Shaders *****************************************************************************/
/*
*   Description:
*     Set shaders (vertex & pixel) by shader type. This is the intended way to set the shaders.
*
*   Paramters:
*     - type        : shader type to set
*/
void    SetShaderType( SHADER_TYPE type );
/*
*   Description:
*     Directly set shaders (vertex & pixel) by shader index.
*
*   Paramters:
*     - index       : shader index
*/
void    SetShaderIndex( SHADER_INDEX index );

#ifdef SAMT_INCL_FUNCPTRS

/************************/
/*  Function Ptrs       */
/************************/
/****** Function Ptrs ***************************************************************************/
#define SetShaderIndex_p         FUNC_PTR(void, __stdcall, (int32_t), 0x00424050)

/****** User-Function Ptrs **********************************************************************/
#define SetShaderType_p          ((void*)0x0041B1F0)

#endif/*SAMT_INCL_FUNCPTRS*/

EXTERN_END

#endif/*H_SOC_SHADER*/
