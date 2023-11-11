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
#ifndef _SA2B_LIGHT_H_
#define _SA2B_LIGHT_H_

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
#define PlayerLight             DataAry(uint8     , 0x01DE4664, [2])

/** Lights used by the player when swinging on bars, always 0 **/
#define IronBarLights           DataAry(uint8     , 0x01DE4662, [2])

/** Stage lights, GC is only used if (flag & BIT_0) **/
#define Lights                  DataAry(LIGHT     , 0x01DE4280, [12])
#define LightsGC                DataAry(LIGHT_GC  , 0x01DE4420, [12])

/** Default light indexes, some objects use player light **/
#define DefaultPlayerLight      DataRef(uint8     , 0x01DE4660)
#define DefaultLight            DataRef(uint8     , 0x01DE4400)

/** An unused vector that's set whenever the lights are set **/
#define UnusedLightVec          DataRef(NJS_VECTOR, 0x1DD94A0)

/************************/
/*  Functions           */
/************************/
EXTERN_START
/** Set current light for drawing via index **/
void    SetLighting(int light);

/** Load light file into 'Lights' or 'LightsGC' **/
sint32  LoadStageLight(const char* filename);

/** Manually change light entry via index **/
void    SetLight(int light, const LIGHT* pLight);
void    SetLightGC(int light, const LIGHT_GC* pLightGC);

/** Set default light index for most objects **/
void    SetDefaultLight(int light);

/** Set default and draw light index for the players **/
void    SetPlayerLight(int player, int light);
void    SetDefaultPlayerLight(int light);

/** SAMT function to convert DC lights to GC lights **/
void    ConvertLight(LIGHT_GC* pLightGC, const LIGHT* pLight);

EXTERN_END

/************************/
/*  Function Ptrs       */
/************************/
#ifdef SAMT_INCLUDE_FUNC_PTRS
/** Function ptrs **/
#define LoadStageLight_p    FuncPtr(sint32, __fastcall, (const char*), 0x006C3AE0)

/** User-Function ptrs **/
EXTERN const void* SetLighting_p;

#endif /* SAMT_INCLUDE_FUNC_PTRS */

#endif /* _SA2B_LIGHT_H_ */
