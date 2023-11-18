/*
*   Sonic Adventure Mod Tools (SA2B) - '/src/score.h'
*
*   Contains data and functions related to player's game & stage scores
*
*   Contributors:
*   -   SEGA - Sonic Team,
*   -   Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC.
*/
#ifndef _SA2B_SCORE_H_
#define _SA2B_SCORE_H_

/************************/
/*  Data                */
/************************/
#define ssNumPlayer     DataAry(sint16, 0x0174B024, [2])

#define ssNumRing       DataAry(sint16, 0x0174B028, [2])

#define loop_const      DataRef(sint32, 0x01DEB50C)
#define ulGlobalTimer   DataRef(uint32, 0x0174B038)

#define GameTimer       DataRef(sint32, 0x0174B03C)

#define ucFrames        DataRef(uint8,  0x0174AFDD)
#define ucSeconds       DataRef(uint8,  0x0174AFDC)
#define ucMinutes       DataRef(uint8,  0x0174AFDB)

#define bWake           DataRef(bool,   0x0174AFF7)

#define gu32TotalRing   DataRef(uint32, 0x174B05C)

/************************/
/*  Functions           */
/************************/
EXTERN_START
void    AdvanceGlobalTime(void);
uint32  GetGlobalTime(void);

void    SetTime(uint8 minutes, uint8 second);
void    GetTime(uint8* minutes, uint8* second);

void    SetTimeFrame(uint8 minutes, uint8 second, uint8 frame);
void    GetTimeFrame(uint8* minutes, uint8* second, uint8* frame);

void    SetTotalRing(uint32 num);
uint32  GetTotalRing(void);

sint32  GetNumRing(sint8 player);
void    ResetNumRing(sint8 player);

void    AddNumRing(sint8 player, sint16 ssNumber);
void    AddNumPlayer(sint8 player, sint16 ssNumber);

EXTERN_END

/************************/
/*  Function Ptrs       */
/************************/
#ifdef SAMT_INCLUDE_FUNC_PTRS
/** User-Function ptr **/
EXTERN const void* const AddNumRing_p;
EXTERN const void* const AddNumPlayer_p;

#endif /* SAMT_INCLUDE_FUNC_PTRS */

#endif /* _SA2B_SCORE_H_ */
