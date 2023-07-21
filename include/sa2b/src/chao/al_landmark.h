#pragma once

#include <sa2b/ninja/njcommon.h>

enum eLANDMARK_ATTR
{
	LMA_NONE = 0x0,
	LMA_GROUND1 = 0x1,
	LMA_GROUND2 = 0x2,
	LMA_GROUND3 = 0x3,
	LMA_SPECIAL1 = 0x4,
	LMA_SPECIAL2 = 0x5,
	LMA_BRIDGE = 0x6,
	LMA_NONE7 = 0x7,
	LMA_WG = 0x8,
	LMA_WATER = 0x9,
};

struct POS_XZ
{
	sint32 x;
	sint32 z;
};

struct LAND_ATTR_INDEX
{
	sint32 nbIndex;
	POS_XZ pos[512]; /* SADX = 1024 */
};

DataAry(LAND_ATTR_INDEX, AttrIndexList, 0x01A15938, [16]);

DataAry(sint32, LandAttrNeut, 0x01362130, [1280]);
DataAry(sint32, LandAttrHero, 0x01363530, [1280]);
DataAry(sint32, LandAttrDark, 0x01364930, [1280]);

FuncPtr(void, __cdecl, AL_InitLandMark, (), 0x00534EF0);

int		AL_GetRandomAttrPos(eLANDMARK_ATTR attr, NJS_POINT3* pPos);

/*
*	AL_InitLandMark
*	AL_GetRandomAttrPos
*	AL_GetCurrLandAttr
*/