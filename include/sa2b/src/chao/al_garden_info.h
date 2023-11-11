/*
*   Sonic Adventure Mod Tools (SA2B) - '/src/chao/al_garden_info.h'
*
*   Contains functions, structs, and data related to Chao garden saves.
*
*   Contributors:
*   -   SEGA - Sonic Team,
*   -   Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC.
*/
#ifndef _SA2B_CHAO_GARDENINFO_H_
#define _SA2B_CHAO_GARDENINFO_H_

/************************/
/*  Includes            */
/************************/
#include <sa2b/ninja/njcommon.h>

#include <sa2b/src/chao/al_chao_info.h>
#include <sa2b/src/chao/chao.h>
#include <sa2b/src/chao/al_itemshop.h>

/************************/
/*  Structures          */
/************************/
typedef struct
{
    sint32 id[2];
}
GARDEN_ID;

typedef struct item_save_info
{
    sint16 kind; // kind
    sint16 place; // area
    sint16 status; // scl
    sint16 nbVisit; // age
    NJS_POINT3 pos;
}
ITEM_SAVE_INFO;

typedef struct
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
}
KINDER_SAVE_INFO;

typedef struct
{
    uint8 crc1;
    uint8 pre0;
    uint8 crc3;
    uint8 post;
    uint8 pre1;
    uint8 crc0;
    uint8 pre2;
    uint8 crc2;
}
SAVE_DATA_CRC;

typedef struct tree_save_info
{
    uint8 kind; // kind
    uint8 state; // stage
    uint8 param; // growth
    uint8 water;
    sint8 FruitGrowth[3];
    uint8 angy_pos; // up to 240
}
TREE_SAVE_INFO;

typedef struct
{
    sint8 RecordFlag;
    AL_TIME time;
    AL_SHAPE_ELEMENT ShapeElement;
}
AL_RECORD;

typedef struct race_save_info
{
    sint8 RaceActiveFlag[6];
    sint8 CourseChallengedLevel[13];
    sint8 BeginnerClearedLevel[4];
    sint8 JewelClearedLevel[6];
    sint8 ChallengeClearedLevel;
    sint8 HeroClearedLevel;
    sint8 DarkClearedLevel;
    AL_RECORD CourseRecord[10];
}
RACE_SAVE_INFO;

typedef struct
{
    uint8 free[32];
}
KARATE_SAVE_INFO;

typedef struct chao_garden_info
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
    RACE_SAVE_INFO race;
    KARATE_SAVE_INFO karate;
    KINDER_SAVE_INFO kinder;
    CHAO_SAVE_INFO chao[24];
    SAVE_DATA_CRC crc;
}
CHAO_GARDEN_INFO;

typedef struct
{
    sint32 category;
    ITEM_SAVE_INFO* pSaveInfo;
}
AL_HOLDING_ITEM_INFO;

/************************/
/*  Data                */
/************************/
#define HoldingItemInfo     DataRef(AL_HOLDING_ITEM_INFO, 0x019F6450)

#define GardenInfoList      DataAry(CHAO_GARDEN_INFO    , 0x019F6460, [2])

#define gAlItemInvList      DataAry(SAlItem             , 0x01DBEDA0, [6])
#define gAlItemInvNum       DataRef(sint32              , 0x01DBEDAC)

/************************/
/*  Functions           */
/************************/
EXTERN_START
/** Memory card slot **/
uint32  ALMC_GetSystemSlot(void);

/** Constants **/
sint32  AL_GetMaxChao(void);

/** Get info **/
CHAO_GARDEN_INFO*   AL_GetCurrGardenInfo(void);
CHAO_GARDEN_INFO*   AL_GetGardenInfo2(sint32 slot);
RACE_SAVE_INFO*     AL_GetRaceSaveInfo(void);

/** New info **/
ITEM_SAVE_INFO*     AL_GetNewItemSaveInfo(sint32 category);

/** Holding info **/
ITEM_SAVE_INFO*     AL_GetHoldingItemSaveInfo(void);
sint32              AL_GetHoldingItemKind(void);
sint32              AL_GetHoldingItemCategory(void);
void                AL_SetHoldingItemInfo(sint32 category, ITEM_SAVE_INFO* pSaveInfo);
void                AL_ClearHoldingItemInfo(void);

/** Garden init **/
void    AL_SetObjectOnTheGarden(void);
void    AL_CreateHoldingItem(void);

/** Package save info for saving to file **/
void    AL_PackageAllSaveInfo(void);
void    AL_PackageItemSaveInfo(sint32 category);

/** Internal functions **/
bool32  AL_CheckSaveDataCrc2(CHAO_GARDEN_INFO* info);

EXTERN_END

/************************/
/*  Function Ptrs       */
/************************/
#ifdef SAMT_INCLUDE_FUNC_PTRS
/** Function ptrs **/
#define AL_GetNewItemSaveInfo_p         FuncPtr(ITEM_SAVE_INFO*  , __fastcall, (sint32)           , 0x0052F9E0)
#define AL_GetCurrGardenInfo_p          FuncPtr(CHAO_GARDEN_INFO*, __cdecl   , (void)             , 0x0052E440)
#define AL_GetAnotherGardenInfo_p       FuncPtr(CHAO_GARDEN_INFO*, __cdecl   , (void)             , 0x0052E460)
#define AL_PackageAllSaveInfo_p         FuncPtr(void             , __cdecl   , (void)             , 0x0052F090)
#define AL_PackageItemSaveInfo_p        FuncPtr(void             , __cdecl   , (sint32)           , 0x0052E710)
#define AL_CheckSaveDataCrc2_p          FuncPtr(bool32           , __fastcall, (CHAO_GARDEN_INFO*), 0x0052F030)
#define AL_SetObjectOnTheGarden_p       FuncPtr(void             , __cdecl   , (void)             , 0x0052EB70)
#define AL_CreateHoldingItem_p          FuncPtr(void             , __cdecl   , (void)             , 0x0052F2A0)

#endif /* SAMT_INCLUDE_FUNC_PTRS */

#endif /* _SA2B_CHAO_GARDENINFO_H_ */