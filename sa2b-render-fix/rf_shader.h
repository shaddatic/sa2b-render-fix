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
/*  Constants                   */
/********************************/
/****** Shader Constants ************************************************************************/
#define MAX_SHC                     (223) /* max shader constant register                       */

#define SHC_VTX_OFF                 (0)         /* vertex register offset                       */
#define SHC_PXL_OFF                 (MAX_SHC+1) /* pixel register offset                        */

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
    SHC_VTX_WORLDMATRIX = 0 + SHC_VTX_OFF,
    /*
    *   Projection Matrix
    */
    SHC_VTX_PROJMATRIX = 8 + SHC_VTX_OFF,
    /*
    *   World View Inverse Transpose Matrix
    */
    SHC_VTX_WORLDVIEWITMATRIX = 12 + SHC_VTX_OFF,
    /*
    *   Light Positions
    */
    SHC_VTX_LIGHTPOS_0 = 20 + SHC_VTX_OFF,
    SHC_VTX_LIGHTPOS_1,
    SHC_VTX_LIGHTPOS_2,
    SHC_VTX_LIGHTPOS_3,
    /*
    *   Light Vectors
    */
    SHC_VTX_LIGHTDIR_0 = 24 + SHC_VTX_OFF,
    SHC_VTX_LIGHTDIR_1,
    SHC_VTX_LIGHTDIR_2,
    SHC_VTX_LIGHTDIR_3,
    /*
    *   Light Colors
    */
    SHC_VTX_LIGHTCOLOR_0 = 28 + SHC_VTX_OFF,
    SHC_VTX_LIGHTCOLOR_1,
    SHC_VTX_LIGHTCOLOR_2,
    SHC_VTX_LIGHTCOLOR_3,
    /*
    *   Light Attenuation (A)
    */
    SHC_VTX_LIGHTATTENA_0 = 32 + SHC_VTX_OFF,
    SHC_VTX_LIGHTATTENA_1,
    SHC_VTX_LIGHTATTENA_2,
    SHC_VTX_LIGHTATTENA_3,
    /*
    *   Light Attenuation (K)
    */
    SHC_VTX_LIGHTATTENK_0 = 36 + SHC_VTX_OFF,
    SHC_VTX_LIGHTATTENK_1,
    SHC_VTX_LIGHTATTENK_2,
    SHC_VTX_LIGHTATTENK_3,
    /*
    *   Material Source Type
    */
    SHC_VTX_MATERIALSRCTYPE_0 = 40 + SHC_VTX_OFF,
    SHC_VTX_MATERIALSRCTYPE_1,
    SHC_VTX_MATERIALSRCTYPE_2,
    SHC_VTX_MATERIALSRCTYPE_3,
    /*
    *   Ambient Source Type
    */
    SHC_VTX_AMBIENTSRCTYPE_0 = 44 + SHC_VTX_OFF,
    SHC_VTX_AMBIENTSRCTYPE_1,
    SHC_VTX_AMBIENTSRCTYPE_2,
    SHC_VTX_AMBIENTSRCTYPE_3,
    /*
    *   Diffuse Attenuation Select
    */
    SHC_VTX_DIFFATTENSELECT_0 = 48 + SHC_VTX_OFF,
    SHC_VTX_DIFFATTENSELECT_1,
    SHC_VTX_DIFFATTENSELECT_2,
    SHC_VTX_DIFFATTENSELECT_3,
    /*
    *   Light Func Enables
    */
    SHC_VTX_LIGHTFUNCENABLE_0 = 52 + SHC_VTX_OFF,
    SHC_VTX_LIGHTFUNCENABLE_1,
    SHC_VTX_LIGHTFUNCENABLE_2,
    SHC_VTX_LIGHTFUNCENABLE_3,
    /*
    *   Light Attenuation Funcs
    */
    SHC_VTX_ATTENFUNC_0 = 56 + SHC_VTX_OFF,
    SHC_VTX_ATTENFUNC_1,
    SHC_VTX_ATTENFUNC_2,
    SHC_VTX_ATTENFUNC_3,
    /*
    *   Material Register
    */
    SHC_VTX_MATERIALREG_0 = 66 + SHC_VTX_OFF,
    SHC_VTX_MATERIALREG_1,
    /*
    *   Ambient Register
    */
    SHC_VTX_AMBIENTREG_0 = 68 + SHC_VTX_OFF,
    SHC_VTX_AMBIENTREG_1,
    /*
    *   Light Masks
    */
    SHC_VTX_LIGHTMASK_0_0 = 70 + SHC_VTX_OFF,
    SHC_VTX_LIGHTMASK_0_1,
    SHC_VTX_LIGHTMASK_0_2,
    SHC_VTX_LIGHTMASK_0_3,
    SHC_VTX_LIGHTMASK_1_0,
    SHC_VTX_LIGHTMASK_1_1,
    SHC_VTX_LIGHTMASK_1_2,
    SHC_VTX_LIGHTMASK_1_3,
    SHC_VTX_LIGHTMASK_2_0,
    SHC_VTX_LIGHTMASK_2_1,
    SHC_VTX_LIGHTMASK_2_2,
    SHC_VTX_LIGHTMASK_2_3,
    SHC_VTX_LIGHTMASK_3_0,
    SHC_VTX_LIGHTMASK_3_1,
    SHC_VTX_LIGHTMASK_3_2,
    SHC_VTX_LIGHTMASK_3_3,
    /*
    *   Device/Screen Info
    */
    SHC_VTX_DEVICEINFO = 104 + SHC_VTX_OFF,
    /*
    *   Texture Generator Source
    */
    SHC_VTX_TEXGENSRC = 140 + SHC_VTX_OFF,
    /*
    *   Texture Generator Number
    */
    SHC_VTX_NUMTEXGENS = 155 + SHC_VTX_OFF,
    /*
    *   Texture Matrix
    */
    SHC_VTX_TEXMATRIX_0 = 160 + SHC_VTX_OFF,
    SHC_VTX_TEXMATRIX_1,
    SHC_VTX_TEXMATRIX_2,
    SHC_VTX_TEXMATRIX_3,
    SHC_VTX_TEXMATRIX_4,
    SHC_VTX_TEXMATRIX_5,
    SHC_VTX_TEXMATRIX_6,
    SHC_VTX_TEXMATRIX_7,
    SHC_VTX_TEXMATRIX_8,
    SHC_VTX_TEXMATRIX_9,
    /*
    *   Unknown Constants
    */
    SHC_VTX_UNK_004 = 4 + SHC_VTX_OFF,
    SHC_VTX_UNK_005,
    SHC_VTX_UNK_006,
    SHC_VTX_UNK_007,
    SHC_VTX_UNK_016 = 16 + SHC_VTX_OFF,
    SHC_VTX_UNK_017,
    SHC_VTX_UNK_018,
    SHC_VTX_UNK_019,
    SHC_VTX_UNK_060 = 60 + SHC_VTX_OFF,
    SHC_VTX_UNK_061,
    SHC_VTX_UNK_062,
    SHC_VTX_UNK_063,
    SHC_VTX_UNK_064,
    SHC_VTX_UNK_065,
    SHC_VTX_UNK_086 = 86 + SHC_VTX_OFF,
    SHC_VTX_UNK_087,
    SHC_VTX_UNK_088,
    SHC_VTX_UNK_089,
    SHC_VTX_UNK_090,
    SHC_VTX_UNK_091,
    SHC_VTX_UNK_092,
    SHC_VTX_UNK_093,
    SHC_VTX_UNK_094,
    SHC_VTX_UNK_095,
    SHC_VTX_UNK_096,
    SHC_VTX_UNK_097,
    SHC_VTX_UNK_098,
    SHC_VTX_UNK_099,
    SHC_VTX_UNK_100,
    SHC_VTX_UNK_101,
    SHC_VTX_UNK_102,
    SHC_VTX_UNK_103,
    SHC_VTX_UNK_105 = 105 + SHC_VTX_OFF,
    SHC_VTX_UNK_106,
    SHC_VTX_UNK_107,
    SHC_VTX_UNK_108,
    SHC_VTX_UNK_109,
    SHC_VTX_UNK_110,
    SHC_VTX_UNK_111,
    SHC_VTX_UNK_112,
    SHC_VTX_UNK_113,
    SHC_VTX_UNK_114,
    SHC_VTX_UNK_115,
    SHC_VTX_UNK_116,
    SHC_VTX_UNK_117,
    SHC_VTX_UNK_118,
    SHC_VTX_UNK_119,
    SHC_VTX_UNK_120,
    SHC_VTX_UNK_121,
    SHC_VTX_UNK_122,
    SHC_VTX_UNK_123,
    SHC_VTX_UNK_124,
    SHC_VTX_UNK_125,
    SHC_VTX_UNK_126,
    SHC_VTX_UNK_127,
    SHC_VTX_UNK_128,
    SHC_VTX_UNK_129,
    SHC_VTX_UNK_130,
    SHC_VTX_UNK_131,
    SHC_VTX_UNK_132,
    SHC_VTX_UNK_133,
    SHC_VTX_UNK_134,
    SHC_VTX_UNK_135,
    SHC_VTX_UNK_136,
    SHC_VTX_UNK_137,
    SHC_VTX_UNK_138,
    SHC_VTX_UNK_139,
    SHC_VTX_UNK_141 = 141 + SHC_VTX_OFF,
    SHC_VTX_UNK_142,
    SHC_VTX_UNK_143,
    SHC_VTX_UNK_144,
    SHC_VTX_UNK_145,
    SHC_VTX_UNK_146,
    SHC_VTX_UNK_147,
    SHC_VTX_UNK_148,
    SHC_VTX_UNK_149,
    SHC_VTX_UNK_150,
    SHC_VTX_UNK_151,
    SHC_VTX_UNK_152,
    SHC_VTX_UNK_153,
    SHC_VTX_UNK_154,
    SHC_VTX_UNK_156 = 156 + SHC_VTX_OFF,
    SHC_VTX_UNK_157,
    SHC_VTX_UNK_158,
    SHC_VTX_UNK_159,
    SHC_VTX_UNK_200 = 200 + SHC_VTX_OFF,
    SHC_VTX_UNK_201,
    SHC_VTX_UNK_202,
    SHC_VTX_UNK_203,
    SHC_VTX_UNK_204,
    SHC_VTX_UNK_205,
    SHC_VTX_UNK_206,
    SHC_VTX_UNK_207,
    SHC_VTX_UNK_208,
    SHC_VTX_UNK_209,
    SHC_VTX_UNK_210,
    SHC_VTX_UNK_211,
    SHC_VTX_UNK_212,
    SHC_VTX_UNK_213,
    SHC_VTX_UNK_214,
    SHC_VTX_UNK_215,
    SHC_VTX_UNK_216,
    SHC_VTX_UNK_217,
    SHC_VTX_UNK_218,
    SHC_VTX_UNK_219,
    SHC_VTX_UNK_220,
    SHC_VTX_UNK_221,
    SHC_VTX_UNK_222,
    SHC_VTX_UNK_223,
    /*
    *   Render Fix Constants
    */
    SHC_VTX_SCRNINFO = SHC_VTX_UNK_200,

    /****** Pixel Constants *****************************************************************/
    /*
    *   GX Tevmode
    */
    SHC_PXL_TEVMODE = 0 + SHC_PXL_OFF,
    /*
    *   Fog data
    */
    SHC_PXL_FOG_PARAM = 50 + SHC_PXL_OFF,
    SHC_PXL_FOG_COLOR = 51 + SHC_PXL_OFF,
    /*
    *   Light allergy
    */
    SHC_PXL_LIGHTALLERGY = 70 + SHC_PXL_OFF,
    /*
    *   World Matrix
    */
    SHC_PXL_WORLDMATRIX = 100 + SHC_PXL_OFF,
    /*
    *   Texture Matrix
    */
    SHC_PXL_TEXMATRIX_0 = 160 + SHC_PXL_OFF,
    SHC_PXL_TEXMATRIX_1 = 164 + SHC_PXL_OFF,
    SHC_PXL_TEXMATRIX_2 = 168 + SHC_PXL_OFF,
    SHC_PXL_TEXMATRIX_3 = 172 + SHC_PXL_OFF,
    SHC_PXL_TEXMATRIX_4 = 176 + SHC_PXL_OFF,
    SHC_PXL_TEXMATRIX_5 = 180 + SHC_PXL_OFF,
    SHC_PXL_TEXMATRIX_6 = 184 + SHC_PXL_OFF,
    SHC_PXL_TEXMATRIX_7 = 188 + SHC_PXL_OFF,
    SHC_PXL_TEXMATRIX_8 = 192 + SHC_PXL_OFF,
    SHC_PXL_TEXMATRIX_9 = 196 + SHC_PXL_OFF,
    /*
    *   Unknown Constants
    */
    SHC_PXL_UNK_001 = 1 + SHC_PXL_OFF,
    SHC_PXL_UNK_002,
    SHC_PXL_UNK_003,
    SHC_PXL_UNK_004,
    SHC_PXL_UNK_005,
    SHC_PXL_UNK_006,
    SHC_PXL_UNK_007,
    SHC_PXL_UNK_008,
    SHC_PXL_UNK_009,
    SHC_PXL_UNK_010,
    SHC_PXL_UNK_011,
    SHC_PXL_UNK_012,
    SHC_PXL_UNK_013,
    SHC_PXL_UNK_014,
    SHC_PXL_UNK_015,
    SHC_PXL_UNK_016,
    SHC_PXL_UNK_017,
    SHC_PXL_UNK_018,
    SHC_PXL_UNK_019,
    SHC_PXL_UNK_020,
    SHC_PXL_UNK_021,
    SHC_PXL_UNK_022,
    SHC_PXL_UNK_023,
    SHC_PXL_UNK_024,
    SHC_PXL_UNK_025,
    SHC_PXL_UNK_026,
    SHC_PXL_UNK_027,
    SHC_PXL_UNK_028,
    SHC_PXL_UNK_029,
    SHC_PXL_UNK_030,
    SHC_PXL_UNK_031,
    SHC_PXL_UNK_032,
    SHC_PXL_UNK_033,
    SHC_PXL_UNK_034,
    SHC_PXL_UNK_035,
    SHC_PXL_UNK_036,
    SHC_PXL_UNK_037,
    SHC_PXL_UNK_038,
    SHC_PXL_UNK_039,
    SHC_PXL_UNK_040,
    SHC_PXL_UNK_041,
    SHC_PXL_UNK_042,
    SHC_PXL_UNK_043,
    SHC_PXL_UNK_044,
    SHC_PXL_UNK_045,
    SHC_PXL_UNK_046,
    SHC_PXL_UNK_047,
    SHC_PXL_UNK_048,
    SHC_PXL_UNK_049,
    SHC_PXL_UNK_052 = 52 + SHC_PXL_OFF,
    SHC_PXL_UNK_053,
    SHC_PXL_UNK_054,
    SHC_PXL_UNK_055,
    SHC_PXL_UNK_056,
    SHC_PXL_UNK_057,
    SHC_PXL_UNK_058,
    SHC_PXL_UNK_059,
    SHC_PXL_UNK_060,
    SHC_PXL_UNK_061,
    SHC_PXL_UNK_062,
    SHC_PXL_UNK_063,
    SHC_PXL_UNK_064,
    SHC_PXL_UNK_065,
    SHC_PXL_UNK_066,
    SHC_PXL_UNK_067,
    SHC_PXL_UNK_068,
    SHC_PXL_UNK_069,
    SHC_PXL_UNK_071 = 71 + SHC_PXL_OFF,
    SHC_PXL_UNK_072,
    SHC_PXL_UNK_073,
    SHC_PXL_UNK_074,
    SHC_PXL_UNK_075,
    SHC_PXL_UNK_076,
    SHC_PXL_UNK_077,
    SHC_PXL_UNK_078,
    SHC_PXL_UNK_079,
    SHC_PXL_UNK_080,
    SHC_PXL_UNK_081,
    SHC_PXL_UNK_082,
    SHC_PXL_UNK_083,
    SHC_PXL_UNK_084,
    SHC_PXL_UNK_085,
    SHC_PXL_UNK_086,
    SHC_PXL_UNK_087,
    SHC_PXL_UNK_088,
    SHC_PXL_UNK_089,
    SHC_PXL_UNK_090,
    SHC_PXL_UNK_091,
    SHC_PXL_UNK_092,
    SHC_PXL_UNK_093,
    SHC_PXL_UNK_094,
    SHC_PXL_UNK_095,
    SHC_PXL_UNK_096,
    SHC_PXL_UNK_097,
    SHC_PXL_UNK_098,
    SHC_PXL_UNK_099,
    SHC_PXL_UNK_104 = 104 + SHC_PXL_OFF,
    SHC_PXL_UNK_105,
    SHC_PXL_UNK_106,
    SHC_PXL_UNK_107,
    SHC_PXL_UNK_108,
    SHC_PXL_UNK_109,
    SHC_PXL_UNK_110,
    SHC_PXL_UNK_111,
    SHC_PXL_UNK_112,
    SHC_PXL_UNK_113,
    SHC_PXL_UNK_114,
    SHC_PXL_UNK_115,
    SHC_PXL_UNK_116,
    SHC_PXL_UNK_117,
    SHC_PXL_UNK_118,
    SHC_PXL_UNK_119,
    SHC_PXL_UNK_120,
    SHC_PXL_UNK_121,
    SHC_PXL_UNK_122,
    SHC_PXL_UNK_123,
    SHC_PXL_UNK_124,
    SHC_PXL_UNK_125,
    SHC_PXL_UNK_126,
    SHC_PXL_UNK_127,
    SHC_PXL_UNK_128,
    SHC_PXL_UNK_129,
    SHC_PXL_UNK_130,
    SHC_PXL_UNK_131,
    SHC_PXL_UNK_132,
    SHC_PXL_UNK_133,
    SHC_PXL_UNK_134,
    SHC_PXL_UNK_135,
    SHC_PXL_UNK_136,
    SHC_PXL_UNK_137,
    SHC_PXL_UNK_138,
    SHC_PXL_UNK_139,
    SHC_PXL_UNK_140,
    SHC_PXL_UNK_141,
    SHC_PXL_UNK_142,
    SHC_PXL_UNK_143,
    SHC_PXL_UNK_144,
    SHC_PXL_UNK_145,
    SHC_PXL_UNK_146,
    SHC_PXL_UNK_147,
    SHC_PXL_UNK_148,
    SHC_PXL_UNK_149,
    SHC_PXL_UNK_150,
    SHC_PXL_UNK_151,
    SHC_PXL_UNK_152,
    SHC_PXL_UNK_153,
    SHC_PXL_UNK_154,
    SHC_PXL_UNK_155,
    SHC_PXL_UNK_156,
    SHC_PXL_UNK_157,
    SHC_PXL_UNK_158,
    SHC_PXL_UNK_159,
    SHC_PXL_UNK_200 = 200 + SHC_PXL_OFF,
    SHC_PXL_UNK_201,
    SHC_PXL_UNK_202,
    SHC_PXL_UNK_203,
    SHC_PXL_UNK_204,
    SHC_PXL_UNK_205,
    SHC_PXL_UNK_206,
    SHC_PXL_UNK_207,
    SHC_PXL_UNK_208,
    SHC_PXL_UNK_209,
    SHC_PXL_UNK_210,
    SHC_PXL_UNK_211,
    SHC_PXL_UNK_212,
    SHC_PXL_UNK_213,
    SHC_PXL_UNK_214,
    SHC_PXL_UNK_215,
    SHC_PXL_UNK_216,
    SHC_PXL_UNK_217,
    SHC_PXL_UNK_218,
    SHC_PXL_UNK_219,
    SHC_PXL_UNK_220,
    SHC_PXL_UNK_221,
    SHC_PXL_UNK_222,
    SHC_PXL_UNK_223,
}
SHC_REGISTER;

/********************************/
/*  Prototypes                  */
/********************************/
/****** Init ************************************************************************************/
/*
*   Description:
*     Init shader module, and load Render Fix's custom game shaders.
*/
void    RF_ShaderInit( void );

/****** Set Shader ******************************************************************************/
/*
*   Description:
*     Set a shader constant register via a full 4d vector.
*
*   Parameters:
*     - registr     : register index
*     - x,y,z,w     : vector 4
*/
void    RF_ShaderSetConstant( SHC_REGISTER registr, f32 x, f32 y, f32 z, f32 w );
/*
*   Description:
*     Set the first float of a constant register.
*
*   Parameters:
*     - registr     : register index
*     - f           : value
*/
void    RF_ShaderSetConstantF( SHC_REGISTER registr, f32 f );
/*
*   Description:
*     Set a 4x4 matrix to multiple constant registers.
*
*   Parameters:
*     - registr     : start register index
*     - m           : 4x4 matrix
*/
void    RF_ShaderSetConstantM( SHC_REGISTER registr, const f32* m );

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
