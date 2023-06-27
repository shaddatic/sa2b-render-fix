#pragma once

#include <sa2b/ninja/ninja.h>

#include <sa2b/src/player.h>

struct SONIC_WORK
{
	playerwk pwk;
	char field_1BC[428];
	__int16 SpindashCounter;
	int field_36A;
	int field_36E;
	int field_372;
	__int16 field_376;
	NJS_VECTOR Position_;
	sint8 gap384[2];
	int field_386;
	int field_38A;
	__int16 field_38E;
	float* field_390;
	NJS_TEXLIST* TextureList;
	CHAR_OBJECT* ModelList;
	player_mot* MotionList;
};

DataRef(SONIC_WORK*, pSonicWork, 0x01A51A9C);

DataRef(NJS_MATRIX, mtx_SonicHandL, 0x01A51A3C);
DataRef(NJS_MATRIX, mtx_SonicHandR, 0x01A51AA0);
DataRef(NJS_MATRIX, mtx_SonicFootL, 0x01A51A6C);
DataRef(NJS_MATRIX, mtx_SonicFootR, 0x01A519D0);

FuncPtr(void, __cdecl, SonicMotionCallBack, (NJS_CNK_OBJECT*), 0x0071EAA0);