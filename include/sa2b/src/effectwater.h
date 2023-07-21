/*
*   Sonic Adventure Mod Tools (SA2B) - '/src/effectwater.h'
*
*   Contains data and functions related to water effects
*
*   Contributors:
*   -   SEGA - Sonic Team,
*   -   Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC.
*/
#pragma once

/************************/
/*  Includes            */
/************************/
#include <sa2b/ninja/njcommon.h>

/************************/
/*  Data                */
/************************/
DataPtr(NJS_TEXLIST, texlist_bsplash, 0xB09818);

DataRef(void*, CreateWaterRipple_p, 0x1A5A2A8);
DataRef(void*, CreateWater_p, 0x01A5A2B0);

/************************/
/*  Function Pointers   */
/************************/
FuncPtr(void, __cdecl, CreateWaterRipple, (NJS_POINT3* pos, NJS_POINT3* vec, float scl), 0x006EDAF0);
FuncPtr(void, __cdecl, CreateWater, (NJS_POINT3* pPos, Angle3* pAng, float scl, float elemsize), 0x006EDEE0);
