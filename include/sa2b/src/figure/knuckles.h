#pragma once

#include <sa2b/ninja/ninja.h>

#include <sa2b/src/player.h>

struct KNUCKLES_WORK
{
	playerwk pwk;
	char field_1BC[492];
	Angle someAng0;
	__int16 someShrt;
	int someAnimationIndex;
	char field_3B0[4];
	float someFlt;
	Angle someHeadAng;
	char field_3C0[36];
	player_objdata* pObjectData0;
	player_objdata* pObjectData1;
	player_objdata* pObjectData2;
	NJS_TEXLIST* TextureList;
	NJS_TEXLIST* EffectTextureList;
	CHAR_OBJECT* ModelList;
	player_mot* MotionList;
	NJS_MOTION_LINK pMotionLink;
	char field_400[16];
};

DataRef(KNUCKLES_WORK*, pKnucklesWork, 0x01A51C88);

DataRef(NJS_MATRIX, mtx_KnucklesHead, 0x01A51CBC);
DataRef(NJS_MATRIX, mtx_KnucklesBody, 0x01A51B3C);
DataRef(NJS_MATRIX, mtx_KnucklesHandL, 0x01A51C58);
DataRef(NJS_MATRIX, mtx_KnucklesHandR, 0x01A51C8C);

FuncPtr(void, __cdecl, KnucklesMotionCallBack, (NJS_CNK_OBJECT*), 0x0072EAA0);