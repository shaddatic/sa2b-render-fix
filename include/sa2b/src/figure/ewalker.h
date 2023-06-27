#pragma once

#include <sa2b/ninja/ninja.h>

#include <sa2b/src/player.h>

struct EWALKER_WORK
{
	playerwk pwk;
	char field_1BC[128];
	float field_23C;
	char field_240[4];
	float field_244;
	NJS_POINT3 somePoint;
	float field_254;
	float field_258;
	float field_25C;
	char field_260[120];
	float field_2D8;
	float field_2DC;
	float field_2E0;
	NJS_POINT3 somePoint2;
	float field_2F0;
	float field_2F4;
	float field_2F8;
	char field_2FC[96];
	char field_35C;
	char field_35D;
	char field_35E;
	char field_35F;
	char field_360;
	char field_361[3];
	__int16 field_364;
	__int16 field_366;
	__int16 field_368;
	__int16 field_36A;
	__int16 field_36C;
	__int16 field_36E;
	char field_370[4];
	float field_374;
	char field_378[8];
	int field_380;
	char field_384[12];
	float field_390;
	float field_394;
	float field_398;
	int field_39C;
	char field_3A0[132];
	int alsosomerotation;
	int field_428;
	int field_42C;
	int CannonRecoil;
	int alsomayberotation;
	float field_438;
	float field_43C;
	float field_440;
	NJS_TEXLIST* CommonTextureList;
	NJS_TEXLIST* TextureList;
	CHAR_OBJECT* ModelList;
	player_mot* MotionList;
};

DataRef(EWALKER_WORK*, pEWalkerWork, 0x01A51F0C);

DataRef(NJS_MATRIX, mtx_EWalkerLaserBlaster, 0x01A51EAC);
DataRef(NJS_MATRIX, mtx_EWalkerLargeCannon, 0x01A51D2C);
DataRef(NJS_MATRIX, mtx_EWalkerJetEngineL, 0x01A52000);
DataRef(NJS_MATRIX, mtx_EWalkerJetEngineR, 0x01A52060);
DataRef(NJS_MATRIX, mtx_EWalkerProtectiveArmor, 0x01A520C0);

FuncPtr(void, __cdecl, EggWalkerMotionCallBack, (NJS_CNK_OBJECT*), 0x00744020);
