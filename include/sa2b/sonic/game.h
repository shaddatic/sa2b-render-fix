/*
*   Sonic Adventure Mod Tools (SA2B) - '/sonic/game.h'
*
*   ~~ Under Construction ~~
* 
*   Description:
*       Contains data and functions related to core game elements.
*
*   Contributors:
*     - SEGA - Sonic Team,
*     - Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC
*/
#ifndef _SA2B_GAME_H_
#define _SA2B_GAME_H_

/************************/
/*  Enums               */
/************************/
/****** Global Mode *****************************************************************/
enum /* ulGlobalMode */
{
    MD_START,
    MD_LOGO,
    MD_TITLE,
    MD_UNKOWN_03,
    MD_ACTION_INIT,
    MD_ACTION,          /* gameplay/action                                          */
    MD_UNKOWN_06,
    MD_EVENT_INIT,      /* init event                                               */
    MD_EVENT,           /* event                                                    */
    MD_UNKOWN_09,
    MD_UNKOWN_10,
    MD_UNKOWN_11,
    MD_SEQUENCE_NEXT,   /* progress to next sequence section                        */
    MD_ADVERTISE_INIT,  /* init advertise menus                                     */
    MD_ADVERTISE,       /* advertise menus                                          */
    MD_ENDING_INIT,     /* init ending                                              */
    MD_ENDING,          /* ending                                                   */
    MD_EMBLEMGET_INIT,  /* init emblem get screen                                   */
    MD_EMBLEMGET,       /* emblem get screen                                        */
    MD_MCWARN_INIT,
    MD_MCWARN,
    MD_OTHERPRINT_INIT,
    MD_OTHERPRINT,
    MD_MCWARN2_INIT,
    MD_MCWARN2,
    MD_UNKNOWN_25,
    NUM_MODE,
};

enum /* ssGameMode */
{
    MD_GAME_INIT,
    MD_GAME_FADEIN = 0x07,
    MD_GAME_FADEOUT_CLEAR = 0x08,
    MD_GAME_FADEOUT_MISS,
    MD_GAME_FADEOUT_RESTART = 0x0D,
    MD_GAME_PAUSE = 0x11,
    NUM_GAMEMD,
};

enum
{
    JAPANESE,
    ENGLISH,
    GERMAN,
    FRENCH,
    SPANISH,
    ITALIAN,
    NUM_LANGUAGE,
};

/************************/
/*  Data                */
/************************/
#define ulGlobalMode        DATA_REF(uint32_t, 0x0174B040)
#define ulNextGlobalMode    DATA_REF(uint32_t, 0x0174B044)

#define ssGameMode          DATA_REF(int16_t , 0x01934BE0)

#define ssGameModeChange    DATA_REF(int16_t , 0x01A558A4)

#define ssStageNumber       DATA_REF(int16_t , 0x01934B70)
#define ssActNumber         DATA_REF(uint8_t , 0x0174AFE3)

#define Language            DATA_REF(int8_t  , 0x0174AFD1)
#define Speech              DATA_REF(int8_t  , 0x0174AFD2)

#define ucPauseSelect       DATA_REF(uint8_t , 0x01933EB1)

#define bPauseDisable       DATA_REF(int8_t  , 0x0174AFD6)

#define pause_flg           DATA_REF(int8_t  , 0x0174AFD7)

/************************/
/*  Functions           */
/************************/
EXTERN_START
void    RestartStageWithFadeOut( void );

void    PauseEnable( void );
void    PauseDisable( void );

b32     ChkPause( void );

EXTERN_END

#endif/*_SA2B_GAME_H_*/
