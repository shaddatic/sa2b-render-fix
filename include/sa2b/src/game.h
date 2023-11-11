/*
*   Sonic Adventure Mod Tools (SA2B) - '/src/game.h'
*
*   ~~ Under Construction ~~
*   Contains data and functions related to core game elements
*
*   Contributors:
*   -   SEGA - Sonic Team,
*   -   Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC.
*/
#ifndef _SA2B_GAME_H_
#define _SA2B_GAME_H_

/************************/
/*  Enums               */
/************************/
enum /* ulGlobalMode */
{
    MD_ACTION_INIT = 0x04,
    MD_ACTION,
    MD_MOVIE_INIT = 0x07,
    MD_MOVIE,
    MD_ADVERTISE_INIT = 0xD,
    MD_ADVERTISE,
    MD_ENDING = 0x10,
    MD_EGET_INIT = 0x11,
    MD_EGET,
    MD_MCWARN_INIT = 0x18,
    MD_MCWARN,
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
#define ulGlobalMode        DataRef(uint32, 0x0174B040)

#define ssGameMode          DataRef(sint16, 0x01934BE0)

#define ssGameModeChange    DataRef(sint16, 0x01A558A4)

#define ssStageNumber       DataRef(sint16, 0x01934B70)
#define ssActNumber         DataRef(uint8,  0x0174AFE3)

#define Language            DataRef(sint8,  0x0174AFD1)
#define Speech              DataRef(sint8,  0x0174AFD2)

#define ucPauseSelect       DataRef(sint8,  0x01933EB1)

#define bPauseDisable       DataRef(sint8,  0x0174AFD6)

#define pause_flg           DataRef(sint8,  0x0174AFD7)

/************************/
/*  Functions           */
/************************/
EXTERN_START
void    RestartStageWithFadeOut(void);

void    PauseEnable(void);
void    PauseDisable(void);

bool32  ChkPause(void);

EXTERN_END

#endif /* _SA2B_GAME_H_ */
