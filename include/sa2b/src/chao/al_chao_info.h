/*
*   Sonic Adventure Mod Tools (SA2B) - '/src/chao/al_chao_info.h'
*
*   Contains functions and data related to Chao save data.
*
*   Contributors:
*   -   SEGA - Sonic Team,
*   -   Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC.
*/
#ifndef _SA2B_CHAO_CHAOINFO_H_
#define _SA2B_CHAO_CHAOINFO_H_

/************************/
/*  Structures          */
/************************/
typedef struct
{
    uint32 gid[2];
    uint32 id[2];
    uint32 num;
}
CHAO_ID;

typedef struct
{
    float32 HPos;            // Run : Power Align
    float32 VPos;            // Swim : Fly Align
    float32 APos;            // Dark : Hero Align
    float32 AimHPos;        // Last Run : Power
    float32 AimVPos;        // Last Swim : Fly
    float32 AimAPos;        // Last Alignment
    float32 growth;        // Magitude
    float32 EyePos;
    float32 EyeScl;
    float32 EyeRatio;
    uint8 EyeColor;
    uint8 DefaultEyeNum;
    uint8 DefaultMouthNum;
    uint8 HonbuNum;        // Icon kind
    uint8 HonbuColorNum;    // Inert
    uint8 ObakeHead;        // Hat / Mask
    uint8 ObakeBody;        // Hide Feet
    uint8 MedalNum;
    uint8 ColorNum;
    uint8 NonTex;            // isMonotone
    uint8 JewelNum;
    uint8 MultiNum;        // Shiny
    sint8 EggColor;
    uint8 FormNum;
    uint8 FormSubNum;        // Animal
    uint8 UNDEF0;
}
AL_BODY_INFO;

typedef struct
{
    uint8 minute;
    uint8 second;
    uint8 frame;
}
AL_TIME;

typedef struct
{
    AL_TIME PersonalRecord[10];
    uint8 nbWin[10];
    uint16 MedalFlag;
}
AL_RACE_PERSONAL_INFO;

typedef struct
{
    uint8 rank;
    uint8 level;
    uint8 tournament;
    uint8 UNDEF0;
    uint16 nbBattle;
    uint16 nbWin;
    uint16 nbLose;
    uint16 nbDraw;
}
AL_KARATE_PERSONAL_INFO;

typedef struct 
{
    uint32 MinimalFlag;
    sint8 MinimalParts[8];
}
AL_PARTS;

typedef struct
{
    uint16 Flag;
    uint16 MoodTimer;
    uint16 IllTimer;
    uint16 loc_timer;
    uint8 Mood[8];
    uint16 State[11];
    sint8 Personality[13];
    uint8 Taste;
    uint8 Tv;
    uint8 Music;
    sint8 IllState[6];
}
AL_EMOTION;

typedef struct
{
    sint8 like;
    uint8 fear;
    uint16 distance;
    uint16 meet;
}
AL_KNOWLEDGE_PLAYER;

typedef struct
{
    CHAO_ID id;
    sint8 like;
    uint8 fear;
    uint16 distance;
    uint16 meet;
    uint8 UNDEF0;
    uint8 UNDEF1;
}
AL_KNOWLEDGE_CHAO;

typedef struct
{
    sint8 like;
}
AL_KNOWLEDGE_OTHER;

typedef struct
{
    uint8 ArtFlag;
    uint8 DanceFlag;
    uint8 SongFlag;
    uint8 MusicFlag;
    uint16 SToyFlag;
    uint16 LToyFlag;
    sint32 KwTimer;
    AL_KNOWLEDGE_PLAYER player[6];
    AL_KNOWLEDGE_CHAO chao[20];
    AL_KNOWLEDGE_OTHER bhv[120];
}
AL_KNOWLEDGE_BTL;

typedef struct al_gene
{
    sint8 IsAnalyzed;
    sint8 EggColor;
    uint8 UNDEF0;
    uint8 UNDEF1;
    CHAO_ID MotherID;
    CHAO_ID FatherID;
    ansi MotherName[8];
    ansi FatherName[8];
    ansi MGroundMotherName[8];
    ansi MGroundFatherName[8];
    ansi FGroundMotherName[8];
    ansi FGroundFatherName[8];
    uint8 Abl[8][2];
    uint8 LifeTime[2];
    sint8 HPos[2];
    sint8 VPos[2];
    sint8 APos[2];
    sint8 Personality[13][2];
    uint8 Taste[2];
    uint8 Tv[2];
    uint8 Music[2];
    uint8 Color[2];
    uint8 NonTex[2];    // Monotone
    uint8 Jewel[2];
    uint8 Multi[2];    // Shiny
    uint8 EyePos[2];
    uint8 EyeScl[2];
    uint8 EyeRatio[2];
    uint8 EyeColor[2];
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
    uint8 GBAChao;
    uint8 GBAEgg;
    uint8 GBABerry[8];
    uint8 padding0;
    uint8 padding1;
    uint32 GBARing;                // Rings moving from GBA -> GCN
    uint8 BootMethed;
    uint8 Birthplace;
    uint8 name[7];
    uint8 GBAType;
    uint8 GBASkin;
    uint8 GBAMood;
    uint8 GBABelly;
    uint8 GBASleepy;
    uint8 GBALonelyness;
    uint8 padding2;
    uint8 Exp[8];                // Progress 0 - 100
    uint8 Abl[8];                // Grade E - S
    uint8 Lev[8];                // Level 0 - 99
    uint16 Skill[8];            // Total Points
    uint16 GBAPallete[16];
    uint8 rmsg[16];
    uint32 runaway;
    uint8 dummy[4];
    uint8 type;                    // Chao Type
    uint8 place;                // Chao Area
    sint16 like;                // Happiness
    sint8 ClassNum;
    uint8 UNDEF0;
    uint16 age;                    // total clock rollovers
    uint16 old;                    // adult clock rollovers
    uint16 life;                // Liftime1
    uint16 LifeMax;                // Liftime2
    uint16 nbSucceed;            // reincarnations
    CHAO_ID ChaoID;
    uint32 LifeTimer;
    AL_BODY_INFO body;
    AL_RACE_PERSONAL_INFO race;
    AL_KARATE_PERSONAL_INFO karate;
    uint8 UNDEF1;
    uint8 UNDEF2;
    AL_PARTS PartsBTL;
    AL_EMOTION emotion;
    AL_KNOWLEDGE_BTL knowledge;
    AL_GENE gene;
    bool32 IsInitializedDX;
    AL_PARTS partsDX;
    AL_RACE_PERSONAL_INFO_DX raceDX;
    uint8 UNDEF3;
    AL_KNOWLEDGE_DX knowledgeDX;
}
CHAO_PARAM_GC;

typedef struct chao_save_info
{
    CHAO_PARAM_GC param;
    uint8 dummy[736];
}
CHAO_SAVE_INFO;

/************************/
/*  Data                */
/************************/
#define pSelectedChaoSaveInfoList   DataRef(CHAO_SAVE_INFO*, 0x01A5CC00)
#define pHoldingChaoSaveInfo        DataRef(CHAO_SAVE_INFO*, 0x01A5CA5C)
#define HoldingFront                DataRef(bool32         , 0x01A5CAB4)

/************************/
/*  Functions           */
/************************/
EXTERN_START
CHAO_SAVE_INFO*     AL_GetNewChaoSaveInfo(void);

void    AL_SetChaoOnTheGarden(void);
void    AL_CreateHoldingChao(void);

EXTERN_END

/************************/
/*  Function Ptrs       */
/************************/
#ifdef SAMT_INCLUDE_FUNC_PTRS
/** Function ptrs **/
#define AL_GetNewChaoSaveInfo_p     FuncPtr(CHAO_SAVE_INFO*, __cdecl, (void), 0x00531AA0)
#define AL_SetChaoOnTheGarden_p     FuncPtr(void           , __cdecl, (void), 0x00531B10)
#define AL_CreateHoldingChao_p      FuncPtr(void           , __cdecl, (void), 0x00531E10)

#endif /* SAMT_INCLUDE_FUNC_PTRS */

#endif /* _SA2B_CHAO_CHAOINFO_H_ */