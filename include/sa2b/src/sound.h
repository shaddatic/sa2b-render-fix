/*
*   Sonic Adventure Mod Tools (SA2B) - '/src/sound.h'
*
*   Contains structs, data, and functions related to the sound engine.
*
*   Contributors:
*   -   SEGA - Sonic Team,
*   -   Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC.
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
    sint8 memBank;
    sint8 index;
    sint8 seBank;
    sint8 flags;
    sint16 unk;
    sint16 dist;
}
BANK_ENTRY;

typedef struct banklist
{
    sint32 nbEntry;
    BANK_ENTRY* pEntry;
}
BANK_LIST;

typedef struct 
{
    sint8 gap0;
    sint8 gap1;
    sint8 unkPri;
    sint8 pan;
    sint8 gap4;
    sint8 volume;
    sint8 volumeMax;
    sint8 gap7;
    uint16 flag;
    sint16 pitch;
    sint16 timer;
    uint16 flag2;
    void* pTask;
    uint16 soundID;
    NJS_VECTOR* pPos;
    NJS_VECTOR position;
    float32 distMax;
    float32 distLast;
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
#define SoundQueue      DataRef(SOUND_QUEUE*, 0x01A55874)

/************************/
/*  Functions           */
/************************/
/** Sound Effect macro, use this for 'se' params **/
#define SE(bank, idx)   ((sint32)((bank*0x1000)+idx))

/** The 'pTask' param is only used as an identifier for the sound entry, and can be NULL.
    The 'pri' param is used for some sort of priority bank sort, but should usually be left as 0. **/

EXTERN_START
void    SE_Call(sint32 se, void* pTask, sint8 pri, sint8 volume);
void    SE_CallV2(sint32 se, void* pTask, NJS_POINT3* pPos, sint8 pri, sint8 volume);

/** The 'timer' param controls how long the sound should play before stopping. Playing 
    the same sound twice with the same 'pTask' will update the timer value, which allows
    variable length sound effects to be played, like grinding or hover boosters. **/

void    SE_Call_Timer(sint32 se, void* pTask, sint8 pri, sint8 volume, sint16 timer);
void    SE_CallV2_Timer(sint32 se, void* pTask, NJS_POINT3* pPos, sint8 pri, sint8 volume, sint16 timer);

void    SE_Call_Loop(sint32 se, void* pTask, sint8 volume);
void    SE_CallV2_Loop(sint32 se, void* pTask, NJS_POINT3* pPos, sint8 volume);

/** The 'Add' functions can modify sound entry params. Match 'se' and 'pTask' with the 
    sound entry to be modified. 'se' can be -1, and only 'pTask' will be matched **/

void    SE_Add_Volume(sint32 se, void* pTask, sint8 volume);
void    SE_Add_Pitch(sint32 se, void* pTask, sint16 pitch);
void    SE_Add_Pan(sint32 se, void* pTask, sint8 pan);

/** Only bosses call these, their exact function isn't fully understood yet. Perhaps, 
    'SC' stands for SpeCial? **/

void    SE_Call_SCLoop(void* pTask, uint16 flags);
void    SE_CallV2_SCLoop(sint32 se, void* pTask,  NJS_POINT3* pPos, sint8 pri, sint8 volume, sint16 timer);

/** As the name suggests, this is only used once in the entire codebase in the 'event' code. **/
void    SE_Call_One(sint32 se);

/** Specifically plays the ring collect jingle. 'pno' controls which players ring count 
    to read for the sound LR pan control. **/
sint8   SE_Call_SEQ(sint8 pno);

EXTERN_END

/************************/
/*  Function Ptrs       */
/************************/
#ifdef SAMT_INCLUDE_FUNC_PTRS
/** Function ptr **/
#define SE_Call_SEQ_p       FuncPtr(sint8, __cdecl, (sint8), 0x004377D0)

/** User-Function ptr **/
EXTERN const void* SE_Call_p;
EXTERN const void* SE_CallV2_p;
EXTERN const void* SE_Call_Timer_p;
EXTERN const void* SE_CallV2_Timer_p;
EXTERN const void* SE_Call_Loop_p;
EXTERN const void* SE_CallV2_Loop_p;
EXTERN const void* SE_Add_Volume_p;
EXTERN const void* SE_Add_Pitch_p;
EXTERN const void* SE_Add_Pan_p;
EXTERN const void* SE_Call_SCLoop_p;
EXTERN const void* SE_CallV2_SCLoop_p;
EXTERN const void* SE_Call_One_p;

#endif /* SAMT_INCLUDE_FUNC_PTRS */

#endif /* _SA2B_SOUND_H_ */