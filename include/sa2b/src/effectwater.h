/*
*   Sonic Adventure Mod Tools (SA2B) - '/src/effectwater.h'
*
*   Description:
*       Contains data and functions related to water effects
*
*   Contributors:
*   -   SEGA - Sonic Team,
*   -   Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC.
*/
#ifndef _SA2B_EFFECTWATER_H_
#define _SA2B_EFFECTWATER_H_

/************************/
/*  Includes            */
/************************/
#include <sa2b/ninja/njcommon.h>

/************************/
/*  Typedefs            */
/************************/
typedef void(__cdecl CreateWaterripple_t)(NJS_POINT3*, NJS_POINT3*, float32_t);
typedef void(__cdecl CreateWater_t)(NJS_POINT3*, Angle3*, float32_t, float32_t);

/************************/
/*  Data                */
/************************/
#define texlist_bsplash         DataAry(NJS_TEXLIST         , 0x00B09818, [1])

#define pCreateWaterripple      DataRef(CreateWaterripple_t*, 0x01A5A2A8)
#define pCreateWater            DataRef(CreateWater_t*      , 0x01A5A2B0)

/************************/
/*  Functions           */
/************************/
EXTERN_START
void    CreateWaterripple( NJS_POINT3* pPos, NJS_POINT3* pParam, float32_t scl );

void    CreateWater( NJS_POINT3* pPos, Angle3* pAng, float32_t scl, float32_t elemsize );

EXTERN_END

/************************/
/*  Function Ptrs       */
/************************/
#ifdef SAMT_INCLUDE_FUNC_PTRS
/** Function ptr **/
#   define CreateWaterripple_p     FuncPtr(void, __cdecl, (NJS_POINT3*, NJS_POINT3*, float32_t)       , 0x006EDAF0)
#   define CreateWater_p           FuncPtr(void, __cdecl, (NJS_POINT3*, Angle3*, float32_t, float32_t), 0x006EDEE0)

#endif/*SAMT_INCLUDE_FUNC_PTRS*/

#endif/*_SA2B_EFFECTWATER_H_*/
