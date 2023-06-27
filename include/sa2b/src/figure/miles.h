#pragma once

#include <sa2b/src/player.h>

struct MILES_WORK
{
	playerwk pwk;
	char field_1BC[364];
	void* texData;
	float pSomeFloat;
	char field_38A[120];
	player_objdata* pObject0;
	player_objdata* pObject1;
	NJS_TEXLIST* TextureList;
	CHAR_OBJECT* ModelList;
	player_mot* MotionList;
	shadowwk shadow;
};

DataRef(MILES_WORK*, pMilesWork, 0x01A521EC);

DataRef(NJS_MATRIX, mtx_MilesInv, 0x01A521BC);
DataRef(NJS_MATRIX, mtx_MilesTails, 0x01A5215C);
DataRef(NJS_MATRIX, mtx_MilesShaderTails, 0x01A5218C);

FuncPtr(void, __cdecl, MilesMotionCallBack, (NJS_CNK_OBJECT*), 0x00750320);
FuncPtr(void, __cdecl, MilesShaderMotionCallBack, (NJS_CNK_OBJECT*), 0x0074FEF0);
