#pragma once

//struct NJS_POINT3;
//struct Angle3;
//struct NJS_TEXLIST;

DataRef(void*, CreateWaterRipple_p, 0x1A5A2A8);

FuncPtr(void, __cdecl, CreateWaterRipple, (NJS_POINT3* pos, NJS_POINT3* vec, float scl), 0x006EDAF0);


DataRef(void*, CreateWater_p, 0x01A5A2B0);

FuncPtr(void, __cdecl, CreateWater, (NJS_POINT3* pPos, Angle3* pAng, float scl, float elemsize), 0x006EDEE0);

DataPtr(NJS_TEXLIST, texlist_bsplash, 0xB09818);