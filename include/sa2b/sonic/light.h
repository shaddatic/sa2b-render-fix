/*
*   Sonic Adventure Mod Tools (SA2B) - '/sonic/light.h'
*
*   Description:
*       Contains structures, data, and functions related to
*   game lighting.
*
*   Contributors:
*       SEGA - Sonic Team,
*       Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC
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
    f32         dif;
    f32         amb;
    f32         r;
    f32         g;
    f32         b;
}
LIGHT;

typedef struct lightgc
{
    NJS_VECTOR  vec;
    f32         r;
    f32         g;
    f32         b;
    f32         amb_r;
    f32         amb_g;
    f32         amb_b;
    uint32_t    flag;
    uint32_t    unused[2];
}
LIGHT_GC;

/************************/
/*  Data                */
/************************/
/** Lights used by the player **/
#define PlayerLight             DATA_ARY(uint8_t   , 0x01DE4664, [2])

/** Lights used by the player when swinging on bars, always 0 **/
#define IronBarLights           DATA_ARY(uint8_t   , 0x01DE4662, [2])

/** Stage lights, GC is only used if (flag & BIT_0) **/
#define Lights                  DATA_ARY(LIGHT     , 0x01DE4280, [12])
#define LightsGC                DATA_ARY(LIGHT_GC  , 0x01DE4420, [12])

/** Default light indexes, some objects use player light **/
#define DefaultPlayerLight      DATA_REF(uint8_t   , 0x01DE4660)
#define DefaultLight            DATA_REF(uint8_t   , 0x01DE4400)

/** An unused vector that's set whenever the lights are set **/
#define UnusedLightVec          DATA_REF(NJS_VECTOR, 0x1DD94A0)

/************************/
/*  Functions           */
/************************/
EXTERN_START
/** Set current light for drawing via index **/
void    SetLighting( int light );

/** Load light file into 'Lights' or 'LightsGC' **/
int32_t LoadLightFile( const char* fname );

/** Manually change light entry via index **/
void    SetLight(   int light, const LIGHT*    pLight   );
void    SetLightGC( int light, const LIGHT_GC* pLightGC );

/** Set default light index for most objects **/
void    SetDefaultLight( int light );

/** Set default and draw light index for the players **/
void    SetPlayerLight( int player, int light );
void    SetDefaultPlayerLight(      int light );

/** SAMT function to convert DC lights to GC lights **/
void    ConvertLight( LIGHT_GC* pLightGC, const LIGHT* pLight );

EXTERN_END

/************************/
/*  Function Ptrs       */
/************************/
#ifdef SAMT_INCL_FUNCPTRS
/** Function ptrs **/
#   define LoadLightFile_p      FUNC_PTR(int32_t, __fastcall, (const char*), 0x006C3AE0)

/** User-Function ptrs **/
#   define SetLighting_p        ((void*)0x00487060)

#endif/*SAMT_INCL_FUNCPTRS*/

#endif/*_SA2B_LIGHT_H_*/
