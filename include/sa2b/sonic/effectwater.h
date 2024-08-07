/*
*   Sonic Adventure Mod Tools (SA2B) - '/sonic/effectwater.h'
*
*   Description:
*       Contains data and functions related to water effects
*
*   Contributors:
*     - SEGA - Sonic Team,
*     - Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC
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
typedef void(__cdecl CreateWaterripple_t)(NJS_POINT3*, NJS_POINT3*, f32);
typedef void(__cdecl CreateWater_t)(NJS_POINT3*, Angle3*, f32, f32);

/************************/
/*  Data                */
/************************/
#define texlist_bsplash         DATA_ARY(NJS_TEXLIST         , 0x00B09818, [1])

#define pCreateWaterripple      DATA_REF(CreateWaterripple_t*, 0x01A5A2A8)
#define pCreateWater            DATA_REF(CreateWater_t*      , 0x01A5A2B0)

/************************/
/*  Functions           */
/************************/
EXTERN_START
void    CreateWaterripple( NJS_POINT3* pPos, NJS_POINT3* pParam, f32 scl );

void    CreateWater( NJS_POINT3* pPos, Angle3* pAng, f32 scl, f32 elemsize );

EXTERN_END

/************************/
/*  Function Ptrs       */
/************************/
#ifdef SAMT_INCL_FUNCPTRS
/** Function ptr **/
#   define CreateWaterripple_p     FUNC_PTR(void, __cdecl, (NJS_POINT3*, NJS_POINT3*, f32)       , 0x006EDAF0)
#   define CreateWater_p           FUNC_PTR(void, __cdecl, (NJS_POINT3*, Angle3*, f32, f32), 0x006EDEE0)

#endif/*SAMT_INCL_FUNCPTRS*/

#endif/*_SA2B_EFFECTWATER_H_*/
