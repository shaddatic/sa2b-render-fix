/*
*   Sonic Adventure Mod Tools (SA2B) - '/sonic/sound.h'
*
*   Contains structs, data, and functions related to the sound engine.
*
*   Contributors:
*     - SEGA - Sonic Team,
*     - Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC
*/
#ifndef _SA2B_SOUND_H_
#define _SA2B_SOUND_H_

/************************/
/*  Includes            */
/************************/
#include <sa2b/ninja/njcommon.h>

/************************/
/*  Structures          */
/************************/
typedef struct bankentry
{
    int8_t  memBank;
    int8_t  index;
    int8_t  seBank;
    int8_t  flags;
    int16_t unk;
    int16_t dist;
}
BANK_ENTRY;

typedef struct banklist
{
    int32_t     nbEntry;
    BANK_ENTRY* pEntry;
}
BANK_LIST;

typedef struct
{
    int8_t      gap0;
    int8_t      gap1;
    int8_t      unkPri;
    int8_t      pan;
    int8_t      gap4;
    int8_t      volume;
    int8_t      volumeMax;
    int8_t      gap7;
    uint16_t    flag;
    int16_t     pitch;
    int16_t     timer;
    uint16_t    flag2;
    void*       pTask;
    uint16_t    soundID;
    NJS_VECTOR* pPos;
    NJS_VECTOR  position;
    f32         distMax;
    f32         distLast;
}
SOUND_ENTRY;

typedef struct
{
    char unk0[3];
    char idxEntry0;
    char idxEntry1;
    char unk1[3];
    int unkInt0;
    char unk2[4];
    SOUND_ENTRY entries[43];
    char unk3[32];
    BANK_LIST* pBanks[8];
}
SOUND_QUEUE;

/************************/
/*  Data                */
/************************/
#define SoundQueue      DATA_REF(SOUND_QUEUE*, 0x01A55874)

/************************/
/*  Functions           */
/************************/
/****** Sound Control ***************************************************************/
/*
*   Description:
*     Stop all sound effects
*/
void    SE_Stop( void );

/****** Sound Play ******************************************************************/
/** Sound Effect macro, use this for 'se' params **/
#define SE(bank, idx)   ((int32_t)((bank*0x1000)+idx))

/** The 'pTask' param is only used as an identifier for the sound entry, and can be NULL.
    The 'pri' param is used for some sort of priority bank sort, but should usually be left as 0. **/

EXTERN_START
void    SE_Call(   int32_t se, void* pTask,                   int8_t pri, int8_t volume );
void    SE_CallV2( int32_t se, void* pTask, NJS_POINT3* pPos, int8_t pri, int8_t volume );

/** The 'timer' param controls how long the sound should play before stopping. Playing 
    the same sound twice with the same 'pTask' will update the timer value, which allows
    variable length sound effects to be played, like grinding or hover boosters. **/

void    SE_Call_Timer(   int32_t se, void* pTask,                   int8_t pri, int8_t volume, int16_t timer );
void    SE_CallV2_Timer( int32_t se, void* pTask, NJS_POINT3* pPos, int8_t pri, int8_t volume, int16_t timer );

void    SE_Call_Loop(   int32_t se, void* pTask,                   int8_t volume );
void    SE_CallV2_Loop( int32_t se, void* pTask, NJS_POINT3* pPos, int8_t volume );

/** The 'Add' functions can modify sound entry params. Match 'se' and 'pTask' with the 
    sound entry to be modified. 'se' can be -1, and only 'pTask' will be matched **/

void    SE_Add_Volume( int32_t se, void* pTask, int8_t  volume );
void    SE_Add_Pitch(  int32_t se, void* pTask, int16_t pitch  );
void    SE_Add_Pan(    int32_t se, void* pTask, int8_t  pan    );

/** Only bosses call these, their exact function isn't fully understood yet. Perhaps, 
    'SC' stands for SpeCial? **/

void    SE_Call_SCLoop(void* pTask, uint16_t flags);
void    SE_CallV2_SCLoop(int32_t se, void* pTask,  NJS_POINT3* pPos, int8_t pri, int8_t volume, int16_t timer);

/** As the name suggests, this is only used once in the entire codebase in the 'event' code. **/
void    SE_Call_One(int32_t se);

/** Specifically plays the ring collect jingle. 'pno' controls which players ring count 
    to read for the sound LR pan control. **/
int8_t  SE_Call_SEQ(int8_t pno);

EXTERN_END

/************************/
/*  Function Ptrs       */
/************************/
#ifdef  SAMT_INCL_FUNCPTRS
/** Function ptr **/
#   define SE_Stop_p            FUNC_PTR(void  , __cdecl, (void)  , 0x00437E90)
#   define SE_Call_SEQ_p        FUNC_PTR(int8_t, __cdecl, (int8_t), 0x004377D0)

/** User-Function ptr **/
#   define SE_Call_p            ((void*)0x00437260)
#   define SE_CallV2_p          ((void*)0x004372E0)
#   define SE_Call_Timer_p      ((void*)0x004374D0)
#   define SE_CallV2_Timer_p    ((void*)0x00437590)
#   define SE_Call_Loop_p       ((void*)0x00437360)
#   define SE_CallV2_Loop_p     ((void*)0x00437420)
#   define SE_Add_Volume_p      ((void*)0x00437F60)
#   define SE_Add_Pitch_p       ((void*)0x00438000)
#   define SE_Add_Pan_p         ((void*)0x00437FB0)
#   define SE_Call_SCLoop_p     ((void*)0x00437640)
#   define SE_CallV2_SCLoop_p   ((void*)0x00437710)
#   define SE_Call_One_p        ((void*)0x00437960)

#endif/*SAMT_INCL_FUNCPTRS*/

#endif/*_SA2B_SOUND_H_*/
