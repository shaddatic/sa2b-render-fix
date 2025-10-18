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
/****** DX9 Control *****************************************************************************/
#include <dx9ctrl/dx9_common.h>     /* float4                                                   */

/****** API *************************************************************************************/
#include <rfapi_shader.h>           /* shader api                                               */

EXTERN_START

/********************************/
/*  Constants                   */
/********************************/
/****** Shader Constants ************************************************************************/
#define RF_SCF_MAX                  (223) /* shader constant (float4) max register              */

#define RF_SCFV_OFFSET              (0)            /* vertex register offset                    */
#define RF_SCFP_OFFSET              (RF_SCF_MAX+1) /* pixel register offset                     */

/********************************/
/*  Enums                       */
/********************************/
/****** Shader Constants ************************************************************************/
typedef enum
{
    /****** Vertex Constants ****************************************************************/
    /*
    *   World Matrix
    */
    RF_SCFV_WORLDMATRIX = 0 + RF_SCFV_OFFSET,
    /*
    *   Projection Matrix
    */
    RF_SCFV_PROJMATRIX = 8 + RF_SCFV_OFFSET,
    /*
    *   World View Inverse Transpose Matrix
    */
    RF_SCFV_WORLDVIEWITMATRIX = 12 + RF_SCFV_OFFSET,
    /*
    *   Light Positions
    */
    RF_SCFV_LIGHTPOS_0 = 20 + RF_SCFV_OFFSET,
    RF_SCFV_LIGHTPOS_1,
    RF_SCFV_LIGHTPOS_2,
    RF_SCFV_LIGHTPOS_3,
    /*
    *   Light Vectors
    */
    RF_SCFV_LIGHTDIR_0 = 24 + RF_SCFV_OFFSET,
    RF_SCFV_LIGHTDIR_1,
    RF_SCFV_LIGHTDIR_2,
    RF_SCFV_LIGHTDIR_3,
    /*
    *   Light Colors
    */
    RF_SCFV_LIGHTCOLOR_0 = 28 + RF_SCFV_OFFSET,
    RF_SCFV_LIGHTCOLOR_1,
    RF_SCFV_LIGHTCOLOR_2,
    RF_SCFV_LIGHTCOLOR_3,
    /*
    *   Light Attenuation (A)
    */
    RF_SCFV_LIGHTATTENA_0 = 32 + RF_SCFV_OFFSET,
    RF_SCFV_LIGHTATTENA_1,
    RF_SCFV_LIGHTATTENA_2,
    RF_SCFV_LIGHTATTENA_3,
    /*
    *   Light Attenuation (K)
    */
    RF_SCFV_LIGHTATTENK_0 = 36 + RF_SCFV_OFFSET,
    RF_SCFV_LIGHTATTENK_1,
    RF_SCFV_LIGHTATTENK_2,
    RF_SCFV_LIGHTATTENK_3,
    /*
    *   Material Source Type
    */
    RF_SCFV_MATERIALSRCTYPE_0 = 40 + RF_SCFV_OFFSET,
    RF_SCFV_MATERIALSRCTYPE_1,
    RF_SCFV_MATERIALSRCTYPE_2,
    RF_SCFV_MATERIALSRCTYPE_3,
    /*
    *   Ambient Source Type
    */
    RF_SCFV_AMBIENTSRCTYPE_0 = 44 + RF_SCFV_OFFSET,
    RF_SCFV_AMBIENTSRCTYPE_1,
    RF_SCFV_AMBIENTSRCTYPE_2,
    RF_SCFV_AMBIENTSRCTYPE_3,
    /*
    *   Diffuse Attenuation Select
    */
    RF_SCFV_DIFFATTENSELECT_0 = 48 + RF_SCFV_OFFSET,
    RF_SCFV_DIFFATTENSELECT_1,
    RF_SCFV_DIFFATTENSELECT_2,
    RF_SCFV_DIFFATTENSELECT_3,
    /*
    *   Light Func Enables
    */
    RF_SCFV_LIGHTFUNCENABLE_0 = 52 + RF_SCFV_OFFSET,
    RF_SCFV_LIGHTFUNCENABLE_1,
    RF_SCFV_LIGHTFUNCENABLE_2,
    RF_SCFV_LIGHTFUNCENABLE_3,
    /*
    *   Light Attenuation Funcs
    */
    RF_SCFV_ATTENFUNC_0 = 56 + RF_SCFV_OFFSET,
    RF_SCFV_ATTENFUNC_1,
    RF_SCFV_ATTENFUNC_2,
    RF_SCFV_ATTENFUNC_3,
    /*
    *   Material Register
    */
    RF_SCFV_MATERIALREG_0 = 66 + RF_SCFV_OFFSET,
    RF_SCFV_MATERIALREG_1,
    /*
    *   Ambient Register
    */
    RF_SCFV_AMBIENTREG_0 = 68 + RF_SCFV_OFFSET,
    RF_SCFV_AMBIENTREG_1,
    /*
    *   Light Masks
    */
    RF_SCFV_LIGHTMASK_0_0 = 70 + RF_SCFV_OFFSET,
    RF_SCFV_LIGHTMASK_0_1,
    RF_SCFV_LIGHTMASK_0_2,
    RF_SCFV_LIGHTMASK_0_3,
    RF_SCFV_LIGHTMASK_1_0,
    RF_SCFV_LIGHTMASK_1_1,
    RF_SCFV_LIGHTMASK_1_2,
    RF_SCFV_LIGHTMASK_1_3,
    RF_SCFV_LIGHTMASK_2_0,
    RF_SCFV_LIGHTMASK_2_1,
    RF_SCFV_LIGHTMASK_2_2,
    RF_SCFV_LIGHTMASK_2_3,
    RF_SCFV_LIGHTMASK_3_0,
    RF_SCFV_LIGHTMASK_3_1,
    RF_SCFV_LIGHTMASK_3_2,
    RF_SCFV_LIGHTMASK_3_3,
    /*
    *   Device/Screen Info
    */
    RF_SCFV_DEVICEINFO = 104 + RF_SCFV_OFFSET,
    /*
    *   Texture Generator Source
    */
    RF_SCFV_TEXGENSRC = 140 + RF_SCFV_OFFSET,
    /*
    *   Texture Generator Number
    */
    RF_SCFV_NUMTEXGENS = 155 + RF_SCFV_OFFSET,
    /*
    *   Texture Matrix
    */
    RF_SCFV_TEXMATRIX_0 = 160 + RF_SCFV_OFFSET,
    RF_SCFV_TEXMATRIX_1,
    RF_SCFV_TEXMATRIX_2,
    RF_SCFV_TEXMATRIX_3,
    RF_SCFV_TEXMATRIX_4,
    RF_SCFV_TEXMATRIX_5,
    RF_SCFV_TEXMATRIX_6,
    RF_SCFV_TEXMATRIX_7,
    RF_SCFV_TEXMATRIX_8,
    RF_SCFV_TEXMATRIX_9,
    /*
    *   Unknown Constants
    */
    RF_SCFV_UNK_004 = 4 + RF_SCFV_OFFSET,
    RF_SCFV_UNK_005,
    RF_SCFV_UNK_006,
    RF_SCFV_UNK_007,
    RF_SCFV_UNK_016 = 16 + RF_SCFV_OFFSET,
    RF_SCFV_UNK_017,
    RF_SCFV_UNK_018,
    RF_SCFV_UNK_019,
    RF_SCFV_UNK_060 = 60 + RF_SCFV_OFFSET,
    RF_SCFV_UNK_061,
    RF_SCFV_UNK_062,
    RF_SCFV_UNK_063,
    RF_SCFV_UNK_064,
    RF_SCFV_UNK_065,
    RF_SCFV_UNK_086 = 86 + RF_SCFV_OFFSET,
    RF_SCFV_UNK_087,
    RF_SCFV_UNK_088,
    RF_SCFV_UNK_089,
    RF_SCFV_UNK_090,
    RF_SCFV_UNK_091,
    RF_SCFV_UNK_092,
    RF_SCFV_UNK_093,
    RF_SCFV_UNK_094,
    RF_SCFV_UNK_095,
    RF_SCFV_UNK_096,
    RF_SCFV_UNK_097,
    RF_SCFV_UNK_098,
    RF_SCFV_UNK_099,
    RF_SCFV_UNK_100,
    RF_SCFV_UNK_101,
    RF_SCFV_UNK_102,
    RF_SCFV_UNK_103,
    RF_SCFV_UNK_105 = 105 + RF_SCFV_OFFSET,
    RF_SCFV_UNK_106,
    RF_SCFV_UNK_107,
    RF_SCFV_UNK_108,
    RF_SCFV_UNK_109,
    RF_SCFV_UNK_110,
    RF_SCFV_UNK_111,
    RF_SCFV_UNK_112,
    RF_SCFV_UNK_113,
    RF_SCFV_UNK_114,
    RF_SCFV_UNK_115,
    RF_SCFV_UNK_116,
    RF_SCFV_UNK_117,
    RF_SCFV_UNK_118,
    RF_SCFV_UNK_119,
    RF_SCFV_UNK_120,
    RF_SCFV_UNK_121,
    RF_SCFV_UNK_122,
    RF_SCFV_UNK_123,
    RF_SCFV_UNK_124,
    RF_SCFV_UNK_125,
    RF_SCFV_UNK_126,
    RF_SCFV_UNK_127,
    RF_SCFV_UNK_128,
    RF_SCFV_UNK_129,
    RF_SCFV_UNK_130,
    RF_SCFV_UNK_131,
    RF_SCFV_UNK_132,
    RF_SCFV_UNK_133,
    RF_SCFV_UNK_134,
    RF_SCFV_UNK_135,
    RF_SCFV_UNK_136,
    RF_SCFV_UNK_137,
    RF_SCFV_UNK_138,
    RF_SCFV_UNK_139,
    RF_SCFV_UNK_141 = 141 + RF_SCFV_OFFSET,
    RF_SCFV_UNK_142,
    RF_SCFV_UNK_143,
    RF_SCFV_UNK_144,
    RF_SCFV_UNK_145,
    RF_SCFV_UNK_146,
    RF_SCFV_UNK_147,
    RF_SCFV_UNK_148,
    RF_SCFV_UNK_149,
    RF_SCFV_UNK_150,
    RF_SCFV_UNK_151,
    RF_SCFV_UNK_152,
    RF_SCFV_UNK_153,
    RF_SCFV_UNK_154,
    RF_SCFV_UNK_156 = 156 + RF_SCFV_OFFSET,
    RF_SCFV_UNK_157,
    RF_SCFV_UNK_158,
    RF_SCFV_UNK_159,
    RF_SCFV_UNK_200 = 200 + RF_SCFV_OFFSET,
    RF_SCFV_UNK_201,
    RF_SCFV_UNK_202,
    RF_SCFV_UNK_203,
    RF_SCFV_UNK_204,
    RF_SCFV_UNK_205,
    RF_SCFV_UNK_206,
    RF_SCFV_UNK_207,
    RF_SCFV_UNK_208,
    RF_SCFV_UNK_209,
    RF_SCFV_UNK_210,
    RF_SCFV_UNK_211,
    RF_SCFV_UNK_212,
    RF_SCFV_UNK_213,
    RF_SCFV_UNK_214,
    RF_SCFV_UNK_215,
    RF_SCFV_UNK_216,
    RF_SCFV_UNK_217,
    RF_SCFV_UNK_218,
    RF_SCFV_UNK_219,
    RF_SCFV_UNK_220,
    RF_SCFV_UNK_221,
    RF_SCFV_UNK_222,
    RF_SCFV_UNK_223,
    /*
    *   Render Fix Constants
    */
    RF_SCFV_SCREENINFO = RF_SCFV_UNK_200,

    /****** Pixel Constants *****************************************************************/
    /*
    *   GX Tevmode
    */
    RF_SCFP_TEVMODE = 0 + RF_SCFP_OFFSET,
    /*
    *   Fog data
    */
    RF_SCFP_FOG_PARAM = 50 + RF_SCFP_OFFSET,
    RF_SCFP_FOG_COLOR = 51 + RF_SCFP_OFFSET,
    /*
    *   Light allergy
    */
    RF_SCFP_LIGHTALLERGY = 70 + RF_SCFP_OFFSET,
    /*
    *   World Matrix
    */
    RF_SCFP_WORLDMATRIX = 100 + RF_SCFP_OFFSET,
    /*
    *   Texture Matrix
    */
    RF_SCFP_TEXMATRIX_0 = 160 + RF_SCFP_OFFSET,
    RF_SCFP_TEXMATRIX_1 = 164 + RF_SCFP_OFFSET,
    RF_SCFP_TEXMATRIX_2 = 168 + RF_SCFP_OFFSET,
    RF_SCFP_TEXMATRIX_3 = 172 + RF_SCFP_OFFSET,
    RF_SCFP_TEXMATRIX_4 = 176 + RF_SCFP_OFFSET,
    RF_SCFP_TEXMATRIX_5 = 180 + RF_SCFP_OFFSET,
    RF_SCFP_TEXMATRIX_6 = 184 + RF_SCFP_OFFSET,
    RF_SCFP_TEXMATRIX_7 = 188 + RF_SCFP_OFFSET,
    RF_SCFP_TEXMATRIX_8 = 192 + RF_SCFP_OFFSET,
    RF_SCFP_TEXMATRIX_9 = 196 + RF_SCFP_OFFSET,
    /*
    *   Unknown Constants
    */
    RF_SCFP_UNK_001 = 1 + RF_SCFP_OFFSET,
    RF_SCFP_UNK_002,
    RF_SCFP_UNK_003,
    RF_SCFP_UNK_004,
    RF_SCFP_UNK_005,
    RF_SCFP_UNK_006,
    RF_SCFP_UNK_007,
    RF_SCFP_UNK_008,
    RF_SCFP_UNK_009,
    RF_SCFP_UNK_010,
    RF_SCFP_UNK_011,
    RF_SCFP_UNK_012,
    RF_SCFP_UNK_013,
    RF_SCFP_UNK_014,
    RF_SCFP_UNK_015,
    RF_SCFP_UNK_016,
    RF_SCFP_UNK_017,
    RF_SCFP_UNK_018,
    RF_SCFP_UNK_019,
    RF_SCFP_UNK_020,
    RF_SCFP_UNK_021,
    RF_SCFP_UNK_022,
    RF_SCFP_UNK_023,
    RF_SCFP_UNK_024,
    RF_SCFP_UNK_025,
    RF_SCFP_UNK_026,
    RF_SCFP_UNK_027,
    RF_SCFP_UNK_028,
    RF_SCFP_UNK_029,
    RF_SCFP_UNK_030,
    RF_SCFP_UNK_031,
    RF_SCFP_UNK_032,
    RF_SCFP_UNK_033,
    RF_SCFP_UNK_034,
    RF_SCFP_UNK_035,
    RF_SCFP_UNK_036,
    RF_SCFP_UNK_037,
    RF_SCFP_UNK_038,
    RF_SCFP_UNK_039,
    RF_SCFP_UNK_040,
    RF_SCFP_UNK_041,
    RF_SCFP_UNK_042,
    RF_SCFP_UNK_043,
    RF_SCFP_UNK_044,
    RF_SCFP_UNK_045,
    RF_SCFP_UNK_046,
    RF_SCFP_UNK_047,
    RF_SCFP_UNK_048,
    RF_SCFP_UNK_049,
    RF_SCFP_UNK_052 = 52 + RF_SCFP_OFFSET,
    RF_SCFP_UNK_053,
    RF_SCFP_UNK_054,
    RF_SCFP_UNK_055,
    RF_SCFP_UNK_056,
    RF_SCFP_UNK_057,
    RF_SCFP_UNK_058,
    RF_SCFP_UNK_059,
    RF_SCFP_UNK_060,
    RF_SCFP_UNK_061,
    RF_SCFP_UNK_062,
    RF_SCFP_UNK_063,
    RF_SCFP_UNK_064,
    RF_SCFP_UNK_065,
    RF_SCFP_UNK_066,
    RF_SCFP_UNK_067,
    RF_SCFP_UNK_068,
    RF_SCFP_UNK_069,
    RF_SCFP_UNK_071 = 71 + RF_SCFP_OFFSET,
    RF_SCFP_UNK_072,
    RF_SCFP_UNK_073,
    RF_SCFP_UNK_074,
    RF_SCFP_UNK_075,
    RF_SCFP_UNK_076,
    RF_SCFP_UNK_077,
    RF_SCFP_UNK_078,
    RF_SCFP_UNK_079,
    RF_SCFP_UNK_080,
    RF_SCFP_UNK_081,
    RF_SCFP_UNK_082,
    RF_SCFP_UNK_083,
    RF_SCFP_UNK_084,
    RF_SCFP_UNK_085,
    RF_SCFP_UNK_086,
    RF_SCFP_UNK_087,
    RF_SCFP_UNK_088,
    RF_SCFP_UNK_089,
    RF_SCFP_UNK_090,
    RF_SCFP_UNK_091,
    RF_SCFP_UNK_092,
    RF_SCFP_UNK_093,
    RF_SCFP_UNK_094,
    RF_SCFP_UNK_095,
    RF_SCFP_UNK_096,
    RF_SCFP_UNK_097,
    RF_SCFP_UNK_098,
    RF_SCFP_UNK_099,
    RF_SCFP_UNK_104 = 104 + RF_SCFP_OFFSET,
    RF_SCFP_UNK_105,
    RF_SCFP_UNK_106,
    RF_SCFP_UNK_107,
    RF_SCFP_UNK_108,
    RF_SCFP_UNK_109,
    RF_SCFP_UNK_110,
    RF_SCFP_UNK_111,
    RF_SCFP_UNK_112,
    RF_SCFP_UNK_113,
    RF_SCFP_UNK_114,
    RF_SCFP_UNK_115,
    RF_SCFP_UNK_116,
    RF_SCFP_UNK_117,
    RF_SCFP_UNK_118,
    RF_SCFP_UNK_119,
    RF_SCFP_UNK_120,
    RF_SCFP_UNK_121,
    RF_SCFP_UNK_122,
    RF_SCFP_UNK_123,
    RF_SCFP_UNK_124,
    RF_SCFP_UNK_125,
    RF_SCFP_UNK_126,
    RF_SCFP_UNK_127,
    RF_SCFP_UNK_128,
    RF_SCFP_UNK_129,
    RF_SCFP_UNK_130,
    RF_SCFP_UNK_131,
    RF_SCFP_UNK_132,
    RF_SCFP_UNK_133,
    RF_SCFP_UNK_134,
    RF_SCFP_UNK_135,
    RF_SCFP_UNK_136,
    RF_SCFP_UNK_137,
    RF_SCFP_UNK_138,
    RF_SCFP_UNK_139,
    RF_SCFP_UNK_140,
    RF_SCFP_UNK_141,
    RF_SCFP_UNK_142,
    RF_SCFP_UNK_143,
    RF_SCFP_UNK_144,
    RF_SCFP_UNK_145,
    RF_SCFP_UNK_146,
    RF_SCFP_UNK_147,
    RF_SCFP_UNK_148,
    RF_SCFP_UNK_149,
    RF_SCFP_UNK_150,
    RF_SCFP_UNK_151,
    RF_SCFP_UNK_152,
    RF_SCFP_UNK_153,
    RF_SCFP_UNK_154,
    RF_SCFP_UNK_155,
    RF_SCFP_UNK_156,
    RF_SCFP_UNK_157,
    RF_SCFP_UNK_158,
    RF_SCFP_UNK_159,
    RF_SCFP_UNK_200 = 200 + RF_SCFP_OFFSET,
    RF_SCFP_UNK_201,
    RF_SCFP_UNK_202,
    RF_SCFP_UNK_203,
    RF_SCFP_UNK_204,
    RF_SCFP_UNK_205,
    RF_SCFP_UNK_206,
    RF_SCFP_UNK_207,
    RF_SCFP_UNK_208,
    RF_SCFP_UNK_209,
    RF_SCFP_UNK_210,
    RF_SCFP_UNK_211,
    RF_SCFP_UNK_212,
    RF_SCFP_UNK_213,
    RF_SCFP_UNK_214,
    RF_SCFP_UNK_215,
    RF_SCFP_UNK_216,
    RF_SCFP_UNK_217,
    RF_SCFP_UNK_218,
    RF_SCFP_UNK_219,
    RF_SCFP_UNK_220,
    RF_SCFP_UNK_221,
    RF_SCFP_UNK_222,
    RF_SCFP_UNK_223,

    RF_SCFP_SHADOWCOLOR = RF_SCFP_UNK_200,
    RF_SCFP_TEXPARAM    = RF_SCFP_UNK_201, /* texshading, texalpha, ???, ???                    */
}
RF_SCF_REGISTER;

/********************************/
/*  Structures                  */
/********************************/
/****** Shader Matrix ***************************************************************************/
typedef struct rfmatrix
{
    dx9_float m[4][4];
}
RFS_MATRIX;

/********************************/
/*  Prototypes                  */
/********************************/
/****** Set Shader ******************************************************************************/
/*
*   Description:
*     Set shader constant register(s) via a float4 list.
*
*   Parameters:
*     - registr     : start register index
*     - p           : float 4 array
*     - nb          : number of constant registers to set
*/
void    RF_ShaderSetConstantF( RF_SCF_REGISTER registr, const dx9_float4* p, size nb );
/*
*   Description:
*     Set a shader constant register via a float4 defined in seperate parameters.
*
*   Parameters:
*     - registr     : register index
*     - x,y,z,w     : vector 4
*/
void    RF_ShaderSetConstantF4( RF_SCF_REGISTER registr, f32 x, f32 y, f32 z, f32 w );
/*
*   Description:
*     Set a 4x4 matrix to multiple constant registers.
*
*   Parameters:
*     - registr     : start register index
*     - m           : 4x4 matrix
*/
void    RF_ShaderSetConstantM( RF_SCF_REGISTER registr, const RFS_MATRIX* m );

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
RFS_VSHADER* RF_CompileVShader( const c8* puSrcName, const RFS_MACRO* pMacros );
RFS_PSHADER* RF_CompilePShader( const c8* puSrcName, const RFS_MACRO* pMacros );
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
RFS_VSHADER* RF_DirectCompileVShader( const c8* puSrcPath, const RFS_MACRO* pMacros );
RFS_PSHADER* RF_DirectCompilePShader( const c8* puSrcPath, const RFS_MACRO* pMacros );

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
RFS_VSHADER* RF_LoadVShader( const c8* puSrcName );
RFS_PSHADER* RF_LoadPShader( const c8* puSrcName );
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
RFS_VSHADER* RF_DirectLoadVShader( const c8* fpath );
RFS_PSHADER* RF_DirectLoadPShader( const c8* fpath );

EXTERN_END

#endif/*H_RF_SHADER*/
