/*
*   Sonic Adventure Mod Tools (SA2B) - '/sonic/sound.h'
*
*   ~~ Under Construction ~~
*
*   Description:
*     For play, modifying, and controlling sound effects and the game's sound
*   engine.
*
*   Contributors:
*     - SEGA - Sonic Team,
*     - Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC
*/
#ifndef H_SA2B_SOUND
#define H_SA2B_SOUND

/************************/
/*  External Includes   */
/************************/
/****** Ninja ***********************************************************************/
#include <sa2b/ninja/njcommon.h> /* ninja common                                    */

EXTERN_START

/************************/
/*  Enums               */
/************************/
/****** Bank Number *****************************************************************/
enum
{
    STG_SE,                     /* stage sound effects                     [bank 5] */
    GM,                         /* game sounds                             [bank 1] */
    CH,                         /* character sounds                        [bank 2] */
    VC,                         /* voice clip                              [bank 3] */
    EM,                         /* enemy                                   [bank 4] */
    NA,                         /* nothing                                          */
    STG_ENV,                    /* stage environment sounds                [bank 6] */
    WT,                         /* water sounds                            [bank 7] */
    SY,                         /* system sounds                           [bank 0] */
};

#ifdef SAMT_INCL_INTERNAL

/****** Internal Bank Number ********************************************************/
enum
{
    BNK_SY,
    BNK_GM,
    BNK_CH,
    BNK_VC,
    BNK_EM,
    BNK_STG_SE,
    BNK_STG_ENV,
    BNK_WT,
};

#endif/*SAMT_INCL_INTERNAL*/

/************************/
/*  Structures          */
/************************/
/****** Bank Entry ******************************************************************/
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

/****** SE Entry ********************************************************************/
typedef struct
{
    int8_t      mbank;
    int8_t      index;

    int8_t      pri;            /* priority */
    int8_t      angle;          /* sound panning */

    int8_t      volcur;
    int8_t      vol;
    int8_t      volmax;

    int8_t      bflag;
    uint16_t    mode;

    int16_t     pitch;
    int16_t     timer;
    uint16_t    sctimer;

    void*       idp;            /* play id              */
    uint16_t    tone;           /* sound number         */

    NJS_VECTOR* pPos;
    NJS_VECTOR  pos;

    f32         distmax;
    f32         distcur;
}
SEENTRY;

/****** SE Work *********************************************************************/
#define SEWK_FXFLAG_ON       (1<<0) /* enable forced reverb value                   */
#define SEWK_FXFLAG_GAME     (1<<1) /* set reverb value on sound pause/resume       */

typedef struct
{
    s8          fxflag;
    s8          fxlev_stop;         /* reverb level when paused          [-127~127] */
    s8          fxlev_game;         /* reverb level when playing         [-127~127] */

    s8          next_snd;           /* next sound buffer entry               [0~38] */
    s8          next_seq;           /* next seq buffer entry                [39~42] */

    s8          unk1[3];

    s32         unkBankVal;         /* unknown, always -1                           */

    s8           unk2[4];

    SEENTRY    sebuf[43];           /* sound call buffer                            */

    s8          unk3[32];

    BANK_LIST*  bank[8];            /* bank lists                                   */
}
SEWORK;

#endif/*SAMT_INCL_INTERNAL*/

/************************/
/*  Data                */
/************************/
#ifdef SAMT_INCL_INTERNAL

/****** Sound Work ******************************************************************/
#define sework                  DATA_REF(SEWORK*, 0x01A55874)

/****** Sound Flag ******************************************************************/
#define snd_pause               DATA_REF(s8,      0x0174AFD9)

#endif/*SAMT_INCL_INTERNAL*/

/************************/
/*  Prototypes          */
/************************/
/****** Sound ID Macro **************************************************************/
/*
*   Description:
*     Make a sound effect id using a bank and index value for 'se' parameters.
*
*   Parameters:
*     - bnk         : sound bank to read from
*     - no          : sound effect index
*
*   Returns:
*     Sound number value, or 'tone'.
*/
#define TONE(bnk, no)           (s32)((((bnk)<<12)&0xF000)+(no))

/****** Sound Play ******************************************************************/
/*
*   Description:
*     Call a basic sound effect.
*
*   Parameters:
*     - tone        : sound effect number
*     - id          : sound source id pointer
*     - volofs      : volume offset                                       [-127~127]
*     - pPos        : position pointer for v2
*
*   Returns:
*     Sound effect buffer index; or -1 on failure.
*/
s8      SE_Call(   s32 tone, const void* id, s32 pri, s32 volofs );
s8      SE_CallV2( s32 tone, const void* id, s32 pri, s32 volofs, const NJS_POINT3* pPos );
/*
*   Description:
*     Call an infinitely looped sound effect. To stop the sound, call an 'SE_Stop'
*   variant with the correct arguments.
*
*   Parameters:
*     - tone        : sound effect number
*     - id          : sound source id pointer
*     - volofs      : volume offset                                       [-127~127]
*     - pPos        : position pointer for v2
*
*   Returns:
*     Sound effect buffer index; or -1 on failure.
*/
s8      SE_Call_Loop(   s32 tone, const void* id, s32 volofs );
s8      SE_CallV2_Loop( s32 tone, const void* id, s32 volofs, const NJS_POINT3* pPos );
/*
*   Description:
*     Call a sound effect to play for set amount of frames.
*
*   Notes:
*     - Calling more than once with the same parameters will update the internal
*       timer value, allowing for variable length sound effects to be played.
*
*   Parameters:
*     - tone        : sound effect number
*     - id          : sound source id pointer
*     - volofs      : volume offset                                       [-127~127]
*     - timer       : number of frames to play for
*     - pPos        : position pointer for v2
*
*   Returns:
*     Sound effect buffer index; or -1 on failure.
*/
s8      SE_Call_Timer(   s32 tone, const void* id, s32 pri, s32 volofs, s32 timer );
s8      SE_CallV2_Timer( s32 tone, const void* id, s32 pri, s32 volofs, s32 timer, const NJS_POINT3* pPos );
/*
*   Description:
*     Call a sound effect with sctimer parameters. It isn't currently known what
*   the exact purpose of this is, but some bosses use them.
*
*   Notes:
*     - Call_SCLoop ignores the 'tone', 'pri', and 'volofs' parameters. They are
*       always '0x13', '1', and '0'.
*
*   Parameters:
*     - tone        : sound effect number
*     - id          : sound source id pointer
*     - pri         : priority
*     - volofs      : volume offset                                       [-127~127]
*     - pPos        : position pointer for v2
*
*   Returns:
*     Sound effect buffer index; or -1 on failure.
*/
s8      SE_Call_SCLoop(   s32 tone, const void* id, s32 pri, s32 volofs, s32 sctimer );
s8      SE_CallV2_SCLoop( s32 tone, const void* id, s32 pri, s32 volofs, s32 sctimer, const NJS_POINT3* pPos );

/****** Sound Control ***************************************************************/
/*
*   Description:
*     Stop all sound effects of a set number.
* 
*   Parameters:
*     - tone        : sound effect number
*/
void    SE_Stop_Num( s32 tone );
/*
*   Description:
*     Stop all sound effects of a set ID.
* 
*   Parameters:
*     - id          : sound source id pointer
*/
void    SE_Stop_ID( const void* id );
/*
*   Description:
*     Stop a specific sound effect.
*
*   Parameters:
*     - tone        : sound effect number
*     - id          : sound source id pointer
*/
void    SE_Stop( s32 tone, const void* id );
/*
*   Description:
*     Stop all sound effects.
*/
void    SE_Stop_All( void );

/****** Sound Modify ****************************************************************/
/*
*   Description:
*     Change volume offset of a specific sound, or all sounds with a set ID.
*
*   Notes:
*     - 'tone' can be '-1', and only 'id' will be used for search.
*
*   Parameters:
*     - tone        : sound effect number                             [optional: -1]
*     - id          : sound source id pointer
*     - volofs      : volume offset                                       [-127~127]
*/
void    SE_Change_Volume( s32 tone, const void* id, s32 volofs );
/*
*   Description:
*     Change sound panning of a specific sound, or all sounds with a set ID.
*
*   Notes:
*     - 'tone' can be '-1', and only 'id' will be used for search.
*
*   Parameters:
*     - tone        : sound effect number                             [optional: -1]
*     - id          : sound source id pointer
*     - pan         : panning offset, L to R                              [-127~127]
*/
void    SE_Change_Pan( s32 tone, const void* id, s32 pan );
/*
*   Description:
*     Change pitch offset of a specific sound, or all sounds with a set ID.
*
*   Notes:
*     - 'tone' can be '-1', and only 'id' will be used for search.
*     - a pitch offset of '0x2000' is 1 octave up or down.
*
*   Parameters:
*     - tone        : sound effect number                             [optional: -1]
*     - id          : sound source id pointer
*     - pitch       : pitch offset                                  [-0x4000~0x4000]
*/
void    SE_Change_Pitch( s32 tone, const void* id, s32 pitch );

/****** Set Calculate ***************************************************************/
/*
*   Description:
*     Flag a sound for automatic speaker panning calculations.
*
*   Parameters:
*     - tone        : sound effect number
*     - id          : sound source id pointer
*/
void    SE_Calc_Pan( s32 tone, const void* id );
/*
*   Description:
*     Flag a sound for automatic doppler shift calculations.
*
*   Notes:
*     - Position will only set static position data info for sound, and will not
*       update the internal position pointer.
*
*   Parameters:
*     - tone        : sound effect number
*     - id          : sound source id pointer
*     - pPos        : sound position                                      [optional]
*/
void    SE_Calc_Pitch( s32 tone, const void* id, NJS_POINT3* pPos );

/****** Other Sound *****************************************************************/
/*
*   Description:
*     Sound call used in Events. Specific purpose is unknown.
*
*   Parameters:
*     - tone        : sound effect number
*
*   Returns:
*     Sound effect buffer index; or -1 on failure.
*/
s8      SE_Call_Event( s32 tone );
/*
*   Description:
*     Ring collect sound effect for specified player. Sound panning is decided
*   based on the parity of their ring count; odd is left, even is right.
*
*   Parameters:
*     - pno         : player number
*
*   Returns:
*     Sound effect buffer index; or -1 on failure.
*/
s8      SE_Call_Ring( s8 pno );

/************************/
/*  Function Ptrs       */
/************************/
#ifdef SAMT_INCL_FUNCPTRS

/****** Standard ********************************************************************/
#define SE_Stop_All_p           FUNC_PTR(void, __cdecl, (void), 0x00437E90)
#define SE_Call_Ring_p          FUNC_PTR(s8  , __cdecl, (s8)  , 0x004377D0)

/****** Usercall ********************************************************************/
#define SE_Call_p               ((void*)0x00437260) /*  AL(ESI, STK, STK, STK)      */
#define SE_CallV2_p             ((void*)0x004372E0) /*  AL(EDI, STK, STK, STK, ESI) */
#define SE_Call_Loop_p          ((void*)0x00437360) /*  AL(ESI, STK, STK)           */
#define SE_CallV2_Loop_p        ((void*)0x00437420) /*  AL(EDI, EBX, STK, ESI)      */
#define SE_Call_Timer_p         ((void*)0x004374D0) /*  AL(ESI, STK, STK, STK, STK) */
#define SE_CallV2_Timer_p       ((void*)0x00437590) /*  AL(EDI, EBX, STK, STK, STK, ESI) */
#define SE_Call_SCLoop_p        ((void*)0x00437640) /*  AL(###, STK, ###, ###, EAX) */
#define SE_CallV2_SCLoop_p      ((void*)0x00437710) /*  AL(EDI, EBX, STK, STK, STK, ESI) */
#define SE_Stop_Num_p           ((void*)0x00437DD0) /* ###(EDX)                     */
#define SE_Stop_ID_p            ((void*)0x00437E10) /* ###(EDX)                     */
#define SE_Stop_p               ((void*)0x00437E50) /* ###(ESI, EDX)                */
#define SE_Change_Volume_p      ((void*)0x00437F60) /* ###(ESI, EDI, EDX)           */
#define SE_Change_Pan_p         ((void*)0x00437FB0) /* ###(ESI, EDI, EDX)           */
#define SE_Change_Pitch_p       ((void*)0x00438000) /* ###(ESI, EDI, EDX)           */
#define SE_Calc_Pan_p           ((void*)0x00438050) /* ###(ESI, EDX)                */
#define SE_Calc_Pitch_p         ((void*)0x00438090) /* ###(EDI, ESI, ECX)           */
#define SE_Call_Event_p         ((void*)0x00437960) /*  AL(ESI)                     */

#endif/*SAMT_INCL_FUNCPTRS*/

EXTERN_END

#endif/*_SA2B_SOUND_H_*/
