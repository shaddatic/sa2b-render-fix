/*
*   Sonic Adventure Mod Tools (SA2B) - '/sonic/chao/al_chao_info.h'
*
*   Description:
*       Contains functions and data related to Chao save data.
*
*   Contributors:
*     - SEGA - Sonic Team,
*     - Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC
*/
#ifndef _SA2B_CHAO_CHAOINFO_H_
#define _SA2B_CHAO_CHAOINFO_H_

/************************/
/*  Structures          */
/************************/
typedef struct
{
    uint32_t gid[2];
    uint32_t id[2];
    uint32_t num;
}
CHAO_ID;

typedef struct
{
    f32       HPos;            // Run : Power Align
    f32       VPos;            // Swim : Fly Align
    f32       APos;            // Dark : Hero Align
    f32       AimHPos;        // Last Run : Power
    f32       AimVPos;        // Last Swim : Fly
    f32       AimAPos;        // Last Alignment
    f32       growth;        // Magitude
    f32       EyePos;
    f32       EyeScl;
    f32       EyeRatio;
    uint8_t EyeColor;
    uint8_t DefaultEyeNum;
    uint8_t DefaultMouthNum;
    uint8_t HonbuNum;        // Icon kind
    uint8_t HonbuColorNum;    // Inert
    uint8_t ObakeHead;        // Hat / Mask
    uint8_t ObakeBody;        // Hide Feet
    uint8_t MedalNum;
    uint8_t ColorNum;
    uint8_t NonTex;            // isMonotone
    uint8_t JewelNum;
    uint8_t MultiNum;        // Shiny
    int8_t EggColor;
    uint8_t FormNum;
    uint8_t FormSubNum;        // Animal
    uint8_t UNDEF0;
}
AL_BODY_INFO;

typedef struct
{
    uint8_t minute;
    uint8_t second;
    uint8_t frame;
}
AL_TIME;

typedef struct
{
    AL_TIME PersonalRecord[10];
    uint8_t nbWin[10];
    uint16_t MedalFlag;
}
AL_RACE_PERSONAL_INFO;

typedef struct
{
    uint8_t rank;
    uint8_t level;
    uint8_t tournament;
    uint8_t UNDEF0;
    uint16_t nbBattle;
    uint16_t nbWin;
    uint16_t nbLose;
    uint16_t nbDraw;
}
AL_KARATE_PERSONAL_INFO;

typedef struct 
{
    uint32_t MinimalFlag;
    int8_t MinimalParts[8];
}
AL_PARTS;

typedef struct
{
    uint16_t Flag;
    uint16_t MoodTimer;
    uint16_t IllTimer;
    uint16_t loc_timer;
    uint8_t Mood[8];
    uint16_t State[11];
    int8_t Personality[13];
    uint8_t Taste;
    uint8_t Tv;
    uint8_t Music;
    int8_t IllState[6];
}
AL_EMOTION;

typedef struct
{
    int8_t like;
    uint8_t fear;
    uint16_t distance;
    uint16_t meet;
}
AL_KNOWLEDGE_PLAYER;

typedef struct
{
    CHAO_ID id;
    int8_t like;
    uint8_t fear;
    uint16_t distance;
    uint16_t meet;
    uint8_t UNDEF0;
    uint8_t UNDEF1;
}
AL_KNOWLEDGE_CHAO;

typedef struct
{
    int8_t like;
}
AL_KNOWLEDGE_OTHER;

typedef struct
{
    uint8_t ArtFlag;
    uint8_t DanceFlag;
    uint8_t SongFlag;
    uint8_t MusicFlag;
    uint16_t SToyFlag;
    uint16_t LToyFlag;
    int32_t KwTimer;
    AL_KNOWLEDGE_PLAYER player[6];
    AL_KNOWLEDGE_CHAO chao[20];
    AL_KNOWLEDGE_OTHER bhv[120];
}
AL_KNOWLEDGE_BTL;

typedef struct al_gene
{
    int8_t IsAnalyzed;
    int8_t EggColor;
    uint8_t UNDEF0;
    uint8_t UNDEF1;
    CHAO_ID MotherID;
    CHAO_ID FatherID;
    char    MotherName[8];
    char    FatherName[8];
    char    MGroundMotherName[8];
    char    MGroundFatherName[8];
    char    FGroundMotherName[8];
    char    FGroundFatherName[8];
    uint8_t Abl[8][2];
    uint8_t LifeTime[2];
    int8_t HPos[2];
    int8_t VPos[2];
    int8_t APos[2];
    int8_t Personality[13][2];
    uint8_t Taste[2];
    uint8_t Tv[2];
    uint8_t Music[2];
    uint8_t Color[2];
    uint8_t NonTex[2];    // Monotone
    uint8_t Jewel[2];
    uint8_t Multi[2];    // Shiny
    uint8_t EyePos[2];
    uint8_t EyeScl[2];
    uint8_t EyeRatio[2];
    uint8_t EyeColor[2];
}
AL_GENE;

typedef struct
{
    AL_TIME PersonalRecord[5];
}
AL_RACE_PERSONAL_INFO_DX;

typedef struct 
{
    AL_KNOWLEDGE_PLAYER player[6];
}
AL_KNOWLEDGE_DX;

typedef struct chao_param_gc
{
    uint8_t GBAChao;
    uint8_t GBAEgg;
    uint8_t GBABerry[8];
    uint8_t padding0;
    uint8_t padding1;
    uint32_t GBARing;                // Rings moving from GBA -> GCN
    uint8_t BootMethed;
    uint8_t Birthplace;
    uint8_t name[7];
    uint8_t GBAType;
    uint8_t GBASkin;
    uint8_t GBAMood;
    uint8_t GBABelly;
    uint8_t GBASleepy;
    uint8_t GBALonelyness;
    uint8_t padding2;
    uint8_t Exp[8];                // Progress 0 - 100
    uint8_t Abl[8];                // Grade E - S
    uint8_t Lev[8];                // Level 0 - 99
    uint16_t Skill[8];            // Total Points
    uint16_t GBAPallete[16];
    uint8_t rmsg[16];
    uint32_t runaway;
    uint8_t dummy[4];
    uint8_t type;                    // Chao Type
    uint8_t place;                // Chao Area
    int16_t like;                // Happiness
    int8_t ClassNum;
    uint16_t age;                    // total clock rollovers
    uint16_t old;                    // adult clock rollovers
    uint16_t life;                // Liftime1
    uint16_t LifeMax;                // Liftime2
    uint16_t nbSucceed;            // reincarnations
    CHAO_ID ChaoID;
    uint32_t LifeTimer;
    AL_BODY_INFO body;
    AL_RACE_PERSONAL_INFO race;
    AL_KARATE_PERSONAL_INFO karate;
    AL_PARTS PartsBTL;
    AL_EMOTION emotion;
    AL_KNOWLEDGE_BTL knowledge;
    AL_GENE gene;
    b32     IsInitializedDX;
    AL_PARTS partsDX;
    AL_RACE_PERSONAL_INFO_DX raceDX;
    AL_KNOWLEDGE_DX knowledgeDX;
}
CHAO_PARAM_GC;

typedef struct chao_save_info
{
    CHAO_PARAM_GC param;
    uint8_t dummy[736];
}
CHAO_SAVE_INFO;

/************************/
/*  Data                */
/************************/
#define pSelectedChaoSaveInfoList   DATA_REF(CHAO_SAVE_INFO*, 0x01A5CC00)
#define pHoldingChaoSaveInfo        DATA_REF(CHAO_SAVE_INFO*, 0x01A5CA5C)
#define HoldingFront                DATA_REF(b32       , 0x01A5CAB4)

#define ChaoSetPositionNeut         DATA_ARY(NJS_POINT3     , 0x01366260, [16])
#define ChaoSetPositionHero         DATA_ARY(NJS_POINT3     , 0x01366320, [16])
#define ChaoSetPositionDark         DATA_ARY(NJS_POINT3     , 0x013663E0, [16])

/************************/
/*  Functions           */
/************************/
EXTERN_START
CHAO_SAVE_INFO* AL_GetNewChaoSaveInfo(void);

void    AL_SetChaoOnTheGarden(void);
void    AL_CreateHoldingChao(void);

EXTERN_END

/************************/
/*  Function Ptrs       */
/************************/
#ifdef  SAMT_INCL_FUNCPTRS
/** Function ptrs **/
#   define AL_GetNewChaoSaveInfo_p      FUNC_PTR(CHAO_SAVE_INFO*, __cdecl, (void), 0x00531AA0)
#   define AL_SetChaoOnTheGarden_p      FUNC_PTR(void           , __cdecl, (void), 0x00531B10)
#   define AL_CreateHoldingChao_p       FUNC_PTR(void           , __cdecl, (void), 0x00531E10)

#endif/*SAMT_INCL_FUNCPTRS*/

#endif/*_SA2B_CHAO_CHAOINFO_H_*/
