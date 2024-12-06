/*
*   Sonic Adventure Mod Tools (SA2B) - '/sonic/savedata.h'
*
*   ~~ Under Construction ~~
* 
*   Contains data related to the game's save data.
*
*   Contributors:
*     - SEGA - Sonic Team,
*     - Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC
*/
#ifndef H_SA2B_SAVEDATA
#define H_SA2B_SAVEDATA

EXTERN_START

enum
{
    RANK_NONE,
    RANK_E,
    RANK_D,
    RANK_C,
    RANK_B,
    RANK_A,
};

typedef struct
{
    s8      m, s, f;        /* minute, second, millisecond                          */
}
CLEAR_TIME;

typedef struct
{
    s32        ring;        /* ring count                                           */
    s32        score;       /* points score                                         */
    CLEAR_TIME time;        /* time                                                 */
}
STAGE_BEST;

typedef struct
{
    s8         rank[5];     /* stage rank for each mission                          */
    s16        playno[5];   /* play count for each mission                          */
    STAGE_BEST best[5][3];  /* last 3 best data for each mission, '[0]' is newest   */
}
STAGE_DATA;

typedef struct
{
    CLEAR_TIME time;        /* time across all 3 laps                               */
    s8         plno;        /* cart character number                                */
}
CART_BEST;

typedef struct
{
    s8        win;          /* race has been won                                    */
    CART_BEST best[3];      /* 3 best records                                       */
}
CART_DATA;

typedef struct
{
    char equipment[29];
    u8 nextsec;
    u8 sec;
    u8 seqno;
    char inseq;
    char minieventsomething;
    u8 someboolean;
    u8 flgReloadSave;
    int gap2;
    char flgJingle[8];
    char unk1[8];
    char flgGreenHill;
    int data1[9];
    char data2[2];
    char emblemAll;
    char data3[5];
    int data4[102];
}
SEQ_DATA;

#pragma pack(push, 1)
typedef struct
{
    int code;
    int totalTime;
    char monoSound;
    char language;
    char speech;
    char unk0;
    unsigned __int8 seqSection;
    unsigned __int8 emblem__not;
    unsigned __int8 emblemNum;
    char vibration;
    char lastStage;
    char unk2;
    char unk3;
    char menuTheme;
    int gap1;
    int gap2;
    __int16 numPlayer1;
    __int16 numPlayer2;
    __int16 numWinP1;
    __int16 numWinP2;
    int gap3;
    int emblemTime;
    int totalTime_2;
    unsigned int u32TotalRing;
    int saveCount;
    STAGE_DATA stages[60];
    STAGE_DATA bigCart[2];
    char data0[12];
    CART_DATA miniCart[3];
    char data1[577];
    char flgChao[17];
    char gap[2];
    SEQ_DATA seqData;
    char flgEvent[86];
    char flgBoss[13];
    char data4[10];
}
SAVE_DATA;
#pragma pack(pop)

/************************/
/*  Data                */
/************************/
#define vmsindex        DATA_REF(int32_t, 0x0173D06C)

#define SaveData        DATA_REF(SAVE_DATA, 0x01DEC600)

EXTERN_END

#endif/*H_SA2B_SAVEDATA*/
