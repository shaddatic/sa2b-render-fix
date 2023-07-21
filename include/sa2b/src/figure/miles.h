/*
*   Sonic Adventure Mod Tools (SA2B) - '/src/figure/miles.h'
*
*   ~~ Under Construction ~~
*   Contains functions, structs, and data for Miles 'Tails' Prower
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

#include <sa2b/src/player.h>

/************************/
/*  Structures          */
/************************/
typedef struct mileswk
{
	PLAYERWK pwk;
	char field_1BC[364];
	void* texData;
	float pSomeFloat;
	char field_38A[120];
	PLAYER_OBJECT* pObject0;
    PLAYER_OBJECT* pObject1;
	NJS_TEXLIST* TextureList;
	CHAR_OBJECT* ModelList;
	PLAYER_MOTION* MotionList;
	shadowwk shadow;
}
MILESWK;

/************************/
/*  Data                */
/************************/
DataRef(MILESWK*, pMilesWork, 0x01A521EC);

DataRef(NJS_MATRIX, mtx_MilesInv, 0x01A521BC);
DataRef(NJS_MATRIX, mtx_MilesTails, 0x01A5215C);
DataRef(NJS_MATRIX, mtx_MilesShaderTails, 0x01A5218C);

/************************/
/*  Function Pointers   */
/************************/
FuncPtr(void, __cdecl, MilesMotionCallBack, (NJS_CNK_OBJECT*), 0x00750320);
FuncPtr(void, __cdecl, MilesShaderMotionCallBack, (NJS_CNK_OBJECT*), 0x0074FEF0);
