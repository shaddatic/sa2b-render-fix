#pragma once

/*
*	Includes
*/

#include <sa2b/ninja/ninja.h>

#include <sa2b/src/Chao/al_chao_info.h>
#include <sa2b/src/Chao/chao.h>

/*
*	Structs
*/

struct GARDEN_ID
{
	sint32 id[2];
};

struct ITEM_SAVE_INFO
{
	sint16 kind; // kind
	sint16 place; // area
	sint16 status; // scl
	sint16 nbVisit; // age
	NJS_POINT3 pos;
};

struct SAlItem
{
	sint8 mCategory;
	sint8 mId;
};

struct KINDER_SAVE_INFO
{
	sint8 LessonNum[4];
	sint32 LessonStartTime[4];
	uint8 free[8];
	sint32 NextBuyListChangeTime;
	sint32 gAlItemBuyNum;
	sint32 gAlItemHaveNum;
	SAlItem gAlItemBuyList[32];
	uint8 dummy[10];
	uint8 UNDEF0;
	uint8 UNDEF1;
};

struct SAVE_DATA_CRC
{
	uint8 crc1;
	uint8 pre0;
	uint8 crc3;
	uint8 post;
	uint8 pre1;
	uint8 crc0;
	uint8 pre2;
	uint8 crc2;
};

struct TREE_SAVE_INFO
{
	uint8 kind; // kind
	uint8 state; // stage
	uint8 param; // growth
	uint8 water;
	sint8 FruitGrowth[3];
	uint8 angy_pos; // up to 240
};

struct AL_RECORD
{
	sint8 RecordFlag;
	AL_TIME time;
	AL_SHAPE_ELEMENT ShapeElement;
};

struct race_save_info
{
	sint8 RaceActiveFlag[6];
	sint8 CourseChallengedLevel[13];
	sint8 BeginnerClearedLevel[4];
	sint8 JewelClearedLevel[6];
	sint8 ChallengeClearedLevel;
	sint8 HeroClearedLevel;
	sint8 DarkClearedLevel;
	AL_RECORD CourseRecord[10];
};

struct KARATE_SAVE_INFO
{
	uint8 free[32];
};

struct CHAO_GARDEN_INFO
{
	GARDEN_ID GardenID;
	uint8 padding[4];
	sint32 flag;
	sint32 ToyGetFlag;
	sint32 timer;
	sint32 nbVisit;
	sint32 nbBorn;
	TREE_SAVE_INFO tree[3][7];
	ITEM_SAVE_INFO fruit[40];
	ITEM_SAVE_INFO seed[12];
	ITEM_SAVE_INFO mask[24];
	ITEM_SAVE_INFO minimal[10];
	race_save_info race;
	KARATE_SAVE_INFO karate;
	KINDER_SAVE_INFO kinder;
	chao_save_info chao[24];
	SAVE_DATA_CRC crc;
};

struct AL_HOLDING_ITEM_INFO
{
	sint32 category;
	ITEM_SAVE_INFO* pSaveInfo;
};

/*
*	Data
*/

DataRef(sint32, GB_vmsdisable, 0x0173D06C);
DataRef(AL_HOLDING_ITEM_INFO, HoldingItemInfo, 0x019F6450);

DataRef(chao_save_info*, pHoldingChaoSaveInfo, 0x01A5CA5C);
DataRef(bool32, HoldingFront, 0x01A5CAB4);

DataAry(CHAO_GARDEN_INFO, GardenInfoList, 0x19F6460, [2]); // 2

DataAry(SAlItem, gAlItemInvList, 0x01DBEDA0, [6]); // 6
DataRef(sint32, gAlItemInvNum, 0x01DBEDAC);

FuncPtr(ITEM_SAVE_INFO*, __thiscall, AL_GetNewItemSaveInfo, (sint32 category), 0x0052F9E0); // 2 = Animal Slots, 3 = Fruit, 7 = Seed, 9 = Hats

FuncPtr(CHAO_GARDEN_INFO*, __cdecl, AL_GetCurrGardenInfo, (), 0x0052E460);

FuncPtr(void, __cdecl, AL_PackageAllSaveInfo, (), 0x0052F090);

FuncPtr(bool, __thiscall, AL_CheckSaveDataCrc2, (CHAO_GARDEN_INFO* info), 0x0052F030);

FuncPtr(void, __cdecl, AL_SetObjectOnTheGarden, (), 0x0052EB70);
FuncPtr(void, __cdecl, AL_CreateHoldingItem, (), 0x0052F2A0);

/*
*	Remade Functions
*/

uint32	ALMC_GetSystemSlot();

CHAO_GARDEN_INFO* AL_GetGardenInfo2(int slot);

void	AL_SetHoldingItemInfo(int category, ITEM_SAVE_INFO* pSaveInfo);
void	AL_ClearHoldingItemInfo();

int				AL_GetHoldingItemKind();
ITEM_SAVE_INFO* AL_GetHoldingItemSaveInfo();
int				AL_GetHoldingItemCategory();

race_save_info* AL_GetRaceSaveInfo();

sint32	AL_GetMaxChao();