/*
*   Sonic Adventure Mod Tools (SA2B) - '/sonic/sound.h'
*
*   ~~ Under Construction ~~
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

EXTERN_START

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

#ifdef SAMT_INCL_INTERNAL

typedef struct
{
    int8_t      gap0;
    int8_t      gap1;
    int8_t      pri;
    int8_t      pan;
    int8_t      gap4;
    int8_t      volume;
    int8_t      volume_max;
    int8_t      gap7;
    uint16_t    flag;
    int16_t     pitch;
    int16_t     timer;
    uint16_t    flag2;
    void*       idp;
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

#endif/*SAMT_INCL_INTERNAL*/

/************************/
/*  Data                */
/************************/
#ifdef SAMT_INCL_INTERNAL

/****** Sound Queue *****************************************************************/
#define SoundQueue              DATA_REF(SOUND_QUEUE*, 0x01A55874)

#endif/*SAMT_INCL_INTERNAL*/

/************************/
/*  Prototypes          */
/************************/
/****** Sound Control ***************************************************************/
/*
*   Description:
*     Stop all sound effects
*/
void    SE_Stop( void );

/****** Sound ID Macro **************************************************************/
/*
*   Description:
*     Make a sound effect id using a bank and index value for 'se' parameters.
*
*   Parameters:
*     - bank        : sound bank to read from
*     - index       : sound effect index
*
*   Returns:
*     Sound ID value.
*/
#define SE(bank, index)         ((s32)(((bank)*0x1000)+(index)))

/****** Sound Play ******************************************************************/
/*
*   Notes:
*     - The 'idp' parameter is used for identifying specific sound entries for
*       modification via the 'SE_Add_###' functions. This pointer is never used
*       except for comparing, so can be anything; usually it's a task or task work.
*     - The 'pri' parameter is used for some priority bank sort, usually it's '0'
*/

/*
*   Description:
*     Call a basic sound effect.
*
*   Parameters:
*     - se          : sound effect id, use 'SE' macro
*     - idp         : pointer for sound ID                               [optional]
*     - pri         : priority                                        [usually '0']
*     - volume      : volume                                             [-128~127]
*/
void    SE_Call( s32 se, const void* idp, s8 pri, s8 volume );

/** The 'timer' param controls how long the sound should play before stopping. Playing 
    the same sound twice with the same 'pTask' will update the timer value, which allows
    variable length sound effects to be played, like grinding or hover boosters. **/

void    SE_Call_TIMER( s32 se, const void* idp, s8 pri, s8 volume, s16 timer );

void    SE_Call_LOOP( s32 se, const void* idp, s8 volume );

/** Only bosses call these, their exact function isn't fully understood yet. Perhaps, 
    'SC' stands for SpeCial? **/
void    SE_Call_SCLOOP( s32 se, const void* idp, u16 flags );

/** As the name suggests, this is only used once in the entire codebase in the 'event' code. **/
void    SE_Call_One( s32 se );

/** Specifically plays the ring collect jingle. 'pno' controls which players ring count 
    to read for the sound LR pan control. **/
int8_t  SE_Call_SEQ( s8 pno );

/****** Sound Play With Position ****************************************************/
/*
*   Notes:
*     - The 'idp' parameter is used for identifying specific sound entries for
*       modification via the 'SE_Add_###' functions. This pointer is never used
*       except for comparing, so can be anything; usually it's a task or task work.
*     - The 'pri' parameter is used for some priority bank sort, usually it's '0'
*/

void    SE_CallV2( s32 se, const void* idp, const NJS_POINT3* pPos, s8 pri, s8 volume );
void    SE_CallV2_TIMER( s32 se, const void* idp, const NJS_POINT3* pPos, s8 pri, s8 volume, s16 timer );
void    SE_CallV2_LOOP( s32 se, const void* idp, const NJS_POINT3* pPos, s8 volume );
void    SE_CallV2_SCLOOP( s32 se, const void* idp, const NJS_POINT3* pPos, s8 pri, s8 volume, s16 timer );

/****** Sound Modify ****************************************************************/

/** The 'Add' functions can modify sound entry params. Match 'se' and 'pTask' with the 
sound entry to be modified. 'se' can be -1, and only 'pTask' will be matched **/

void    SE_Add_VOLUME( s32 se, const void* idp, s8  volume );
void    SE_Add_PITCH(  s32 se, const void* idp, s16 pitch  );
void    SE_Add_PAN(    s32 se, const void* idp, s8  pan    );

/************************/
/*  Function Ptrs       */
/************************/
#ifdef SAMT_INCL_FUNCPTRS

/****** Standard ********************************************************************/
#define SE_Stop_p               FUNC_PTR(void, __cdecl, (void), 0x00437E90)
#define SE_Call_SEQ_p           FUNC_PTR(s8  , __cdecl, (s8)  , 0x004377D0)

/****** Usercall ********************************************************************/
#define SE_Call_p               ((void*)0x00437260)
#define SE_Call_TIMER_p         ((void*)0x004374D0)
#define SE_Call_LOOP_p          ((void*)0x00437360)
#define SE_Call_SCLOOP_p        ((void*)0x00437640)
#define SE_Call_ONE_p           ((void*)0x00437960)
#define SE_Add_VOLUME_p         ((void*)0x00437F60)
#define SE_Add_PITCH_p          ((void*)0x00438000)
#define SE_Add_PAN_p            ((void*)0x00437FB0)
#define SE_CallV2_p             ((void*)0x004372E0)
#define SE_CallV2_TIMER_p       ((void*)0x00437590)
#define SE_CallV2_LOOP_p        ((void*)0x00437420)
#define SE_CallV2_SCLOOP_p      ((void*)0x00437710)

#endif/*SAMT_INCL_FUNCPTRS*/

EXTERN_END

#endif/*_SA2B_SOUND_H_*/
