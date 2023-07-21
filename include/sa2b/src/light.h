/*
*   Sonic Adventure Mod Tools (SA2B) - '/src/light.h'
*
*   Contains structures, data, and functions related to 
*   game lighting.
*
*   Contributors:
*       SEGA - Sonic Team,
*       Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC.
*/
#pragma once

/************************/
/*  Includes            */
/************************/
#include <sa2b/ninja/njcommon.h>

/************************/
/*  Structures          */
/************************/
typedef struct light
{
	NJS_VECTOR  vec;
	float32     dif;
	float32     amb;
    float32     r;
    float32     g;
    float32     b;
}
LIGHT;

typedef struct lightgc
{
	NJS_VECTOR  vec;
    float32     r;
    float32     g;
    float32     b;
    float32     amb_r;
    float32     amb_g;
    float32     amb_b;
	uint32      flag;
	uint32      unused[2];
}
LIGHT_GC;

/************************/
/*  Data                */
/************************/
/** Lights used by the player **/
DataAry(uint8,      PlayerLight,   0x01DE4664, [2]);

/** Lights used by the player when swinging on bars, always 0 **/
DataAry(uint8,      IronBarLights,  0x01DE4662, [2]);

/** Stage lights, GC is only used if (flag & BIT_0) **/
DataAry(LIGHT,      Lights,         0x01DE4280, [12]);
DataAry(LIGHT_GC,   LightsGC,       0x01DE4420, [12]);

/** Default light indexes, some objects use player light **/
DataRef(uint8,      DefaultPlayerLight,     0x01DE4660);
DataRef(uint8,      DefaultLight,           0x01DE4400);

/************************/
/*  Function Pointers   */
/************************/
FuncPtr(sint32, __fastcall, LoadStageLight, (const char* filename), 0x006C3AE0);

/************************/
/*  User Functions      */
/************************/
void    SetLighting(int light);

/************************/
/*  Functions           */
/************************/
void    SetLight(int light, const LIGHT* pLight);
void    SetLightGC(int light, const LIGHT_GC* pLightDataGC);

void    SetDefaultLight(int light);

void    SetPlayerLight(int player, int light);
void    SetDefaultPlayerLight(int light);

/************************/
/*  User Function Ptrs  */
/************************/
#ifdef SAMT_INCLUDE_USER_PTRS

extern const void* SetLighting_p;

#endif

/************************/
/*  SAMT Functions      */
/************************/
EXTERN void ConvertLight(const LIGHT* pLight, LIGHT_GC* pLightGC);