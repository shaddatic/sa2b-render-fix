/*
*   Sonic Adventure Mod Tools (SA2B) - '/sonic/chao/al_garden_info.h'
*
*   Description:
*       Contains functions, structs, and data related to Chao
*   Garden saves.
*
*   Contributors:
*     - SEGA - Sonic Team,
*     - Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC
*/
#ifndef _SA2B_CHAO_GARDENINFO_H_
#define _SA2B_CHAO_GARDENINFO_H_

/************************/
/*  Includes            */
/************************/
#include <sa2b/ninja/njcommon.h>

#include <sa2b/sonic/chao/chao.h>
#include <sa2b/sonic/chao/al_chao_info.h>
#include <sa2b/sonic/chao/al_itemshop.h>

/************************/
/*  Defines             */
/************************/
#define FLAG_GARDEN_PLAY            (0x01)
#define FLAG_GARDEN_NEUT_PLAY       (0x02)
#define FLAG_GARDEN_KINDER_OPEN     (0x04)
#define FLAG_GARDEN_KINDER_PLAY     (0x08)
#define FLAG_GARDEN_HERO_OPEN       (0x10)
#define FLAG_GARDEN_HERO_PLAY       (0x20)
#define FLAG_GARDEN_DARK_OPEN       (0x40)
#define FLAG_GARDEN_DARK_PLAY       (0x80)

#define FLAG_TOY_TV                 (0x01)
#define FLAG_TOY_RADICASE           (0x02)
#define FLAG_TOY_BOX                (0x04)
#define FLAG_TOY_BALL_N             (0x08)
#define FLAG_TOY_BALL_H             (0x10)
#define FLAG_TOY_BALL_D             (0x20)
#define FLAG_TOY_HORSE              (0x40)

/************************/
/*  Structures          */
/************************/
typedef struct
{
    int32_t id[2];
}
GARDEN_ID;

typedef struct item_save_info
{
    int16_t kind; // kind
    int16_t place; // area
    int16_t status; // scl
    int16_t nbVisit; // age
    NJS_POINT3 pos;
}
ITEM_SAVE_INFO;

typedef struct
{
    int8_t LessonNum[4];
    int32_t LessonStartTime[4];
    uint8_t free[8];
    int32_t NextBuyListChangeTime;
    int32_t gAlItemBuyNum;
    int32_t gAlItemHaveNum;
    SAlItem gAlItemBuyList[32];
    uint8_t dummy[10];
}
KINDER_SAVE_INFO;

typedef struct
{
    uint8_t crc1;
    uint8_t pre0;
    uint8_t crc3;
    uint8_t stPost;
    uint8_t pre1;
    uint8_t crc0;
    uint8_t pre2;
    uint8_t crc2;
}
SAVE_DATA_CRC;

typedef struct tree_save_info
{
    uint8_t kind; // kind
    uint8_t state; // stage
    uint8_t param; // growth
    uint8_t water;
    int8_t FruitGrowth[3];
    uint8_t angy_pos; // up to 240
}
TREE_SAVE_INFO;

typedef struct
{
    int8_t RecordFlag;
    AL_TIME time;
    AL_SHAPE_ELEMENT ShapeElement;
}
AL_RECORD;

typedef struct race_save_info
{
    int8_t RaceActiveFlag[6];
    int8_t CourseChallengedLevel[13];
    int8_t BeginnerClearedLevel[4];
    int8_t JewelClearedLevel[6];
    int8_t ChallengeClearedLevel;
    int8_t HeroClearedLevel;
    int8_t DarkClearedLevel;
    AL_RECORD CourseRecord[10];
}
RACE_SAVE_INFO;

typedef struct
{
    uint8_t free[32];
}
KARATE_SAVE_INFO;

typedef struct chao_garden_info
{
    GARDEN_ID GardenID;
    uint8_t padding[4];
    int32_t flag;
    int32_t ToyGetFlag;
    int32_t timer;
    int32_t nbVisit;
    int32_t nbBorn;
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
    int32_t category;
    ITEM_SAVE_INFO* pSaveInfo;
}
AL_HOLDING_ITEM_INFO;

/************************/
/*  Data                */
/************************/
#define HoldingItemInfo     DATA_REF(AL_HOLDING_ITEM_INFO, 0x019F6450)

#define GardenInfoList      DATA_ARY(CHAO_GARDEN_INFO    , 0x019F6460, [2])

#define gAlItemInvList      DATA_ARY(SAlItem             , 0x01DBEDA0, [6])
#define gAlItemInvNum       DATA_REF(int32_t              , 0x01DBEDAC)

/************************/
/*  Functions           */
/************************/
EXTERN_START
/** Memory card slot **/
uint32_t    ALMC_GetSystemSlot(void);

/** Constants **/
int32_t     AL_GetMaxChao(void);

/** Get info **/
CHAO_GARDEN_INFO* AL_GetCurrGardenInfo(void);
CHAO_GARDEN_INFO* AL_GetGardenInfo2(int32_t slot);
RACE_SAVE_INFO*   AL_GetRaceSaveInfo(void);

/** Flag info **/
void        AL_OnGardenFlag(uint32_t flag);
b32        AL_CheckGardenFlag(uint32_t flag);

/** New info **/
ITEM_SAVE_INFO* AL_GetNewItemSaveInfo(int32_t category);

/** Holding info **/
ITEM_SAVE_INFO* AL_GetHoldingItemSaveInfo(void);
int32_t         AL_GetHoldingItemKind(void);
int32_t         AL_GetHoldingItemCategory(void);
void            AL_SetHoldingItemInfo(int32_t category, ITEM_SAVE_INFO* pSaveInfo);
void            AL_ClearHoldingItemInfo(void);

/** Garden init **/
void    AL_SetObjectOnTheGarden(void);
void    AL_CreateHoldingItem(void);

/** Package save info for saving to file **/
void    AL_PackageAllSaveInfo(void);
void    AL_PackageItemSaveInfo(int32_t category);

/** Internal functions **/
b32     AL_CheckSaveDataCrc2(CHAO_GARDEN_INFO* info);

EXTERN_END

/************************/
/*  Function Ptrs       */
/************************/
#ifdef  SAMT_INCL_FUNCPTRS
/** Function ptrs **/
#   define AL_GetNewItemSaveInfo_p          FUNC_PTR(ITEM_SAVE_INFO*  , __fastcall, (int32_t)          , 0x0052F9E0)
#   define AL_GetCurrGardenInfo_p           FUNC_PTR(CHAO_GARDEN_INFO*, __cdecl   , (void)             , 0x0052E440)
#   define AL_GetAnotherGardenInfo_p        FUNC_PTR(CHAO_GARDEN_INFO*, __cdecl   , (void)             , 0x0052E460)
#   define AL_PackageAllSaveInfo_p          FUNC_PTR(void             , __cdecl   , (void)             , 0x0052F090)
#   define AL_PackageItemSaveInfo_p         FUNC_PTR(void             , __cdecl   , (int32_t)          , 0x0052E710)
#   define AL_CheckSaveDataCrc2_p           FUNC_PTR(b32         , __fastcall, (CHAO_GARDEN_INFO*), 0x0052F030)
#   define AL_SetObjectOnTheGarden_p        FUNC_PTR(void             , __cdecl   , (void)             , 0x0052EB70)
#   define AL_CreateHoldingItem_p           FUNC_PTR(void             , __cdecl   , (void)             , 0x0052F2A0)

#endif/*SAMT_INCL_FUNCPTRS*/

#endif/*_SA2B_CHAO_GARDENINFO_H_*/
