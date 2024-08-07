/*
*   Sonic Adventure Mod Tools (SA2B) - '/sonic/shaders.h'
*
*   Contains data and functions related to SOC's shader engine.
*
*   Contributors:
*     - SEGA - Sonic Team,
*     - Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC
*/
#ifndef _SA2B_SHADERS_H_
#define _SA2B_SHADERS_H_

/************************/
/*  Defines             */
/************************/
#define SHADERMODE_NONE         (0)
#define SHADERMODE_SHADOW       (1)
#define SHADERMODE_FOG          (2)
#define SHADERMODE_PALLETE      (4)

/************************/
/*  Data                */
/************************/
#define LockShaders     DATA_REF(bool,    0x01A55709)
#define ShaderMode      DATA_REF(int32_t, 0x01AF1960)
#define ShaderLast      DATA_REF(int32_t, 0x01A5579C)

/************************/
/*  Functions           */
/************************/
EXTERN_START
void SetShaders(int32_t idx);

void SetAndLoadShader(int32_t idx);

EXTERN_END

/************************/
/*  Function Ptrs       */
/************************/
#ifdef  SAMT_INCL_FUNCPTRS
/** Function Ptrs **/
#   define SetAndLoadShader_p       FUNC_PTR(void, __stdcall, (int32_t), 0x00424050)

/** User-Function Ptrs **/
#   define SetShaders_p             ((void*)0x0041B1F0)

#endif /* SAMT_INCL_FUNCPTRS */

#endif /* _SA2B_SHADERS_H_ */
