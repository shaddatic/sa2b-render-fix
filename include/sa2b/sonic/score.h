/*
*   Sonic Adventure Mod Tools (SA2B) - '/sonic/score.h'
*
*   Contains data and functions related to player's game & stage scores
*
*   Contributors:
*     - SEGA - Sonic Team,
*     - Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC
*/
#ifndef _SA2B_SCORE_H_
#define _SA2B_SCORE_H_

/************************/
/*  Data                */
/************************/
#define ssNumPlayer     DATA_ARY(int16_t , 0x0174B024, [2])

#define ssNumRing       DATA_ARY(int16_t , 0x0174B028, [2])

#define loop_const      DATA_REF(int32_t , 0x01DEB50C)
#define ulGlobalTimer   DATA_REF(uint32_t, 0x0174B038)

#define GameTimer       DATA_REF(int32_t , 0x0174B03C)

#define ucFrames        DATA_REF(uint8_t , 0x0174AFDD)
#define ucSeconds       DATA_REF(uint8_t , 0x0174AFDC)
#define ucMinutes       DATA_REF(uint8_t , 0x0174AFDB)

#define bWake           DATA_REF(bool    , 0x0174AFF7)

#define gu32TotalRing   DATA_REF(uint32_t, 0x0174B05C)

/************************/
/*  Functions           */
/************************/
EXTERN_START
/** Global Time **/
void     AdvanceGlobalTime( void );
uint32_t GetGlobalTime( void );

/** Game time **/
int32_t  GetGameTime( void );

/** Game time (minutes & seconds) **/
void     SetTime( uint8_t  minutes, uint8_t  second );
void     GetTime( uint8_t* minutes, uint8_t* second );

void     SetTimeFrame( uint8_t  minutes, uint8_t  second, uint8_t  frame );
void     GetTimeFrame( uint8_t* minutes, uint8_t* second, uint8_t* frame );

/** Set/Get total rings **/
void     SetTotalRing( uint32_t num );
uint32_t GetTotalRing( void );

/** Set/Get rings **/
int32_t  GetNumRing(   int8_t player );
void     ResetNumRing( int8_t player );

/** Add rings/lives **/
void     AddNumRing(   int8_t player, int16_t ssNumber );
void     AddNumPlayer( int8_t player, int16_t ssNumber );

EXTERN_END

/************************/
/*  Function Ptrs       */
/************************/
#ifdef SAMT_INCL_FUNCPTRS
/** User-Function ptr **/
#   define AddNumRing_p        ((void*)0x0044CE10)
#   define AddNumPlayer_p      ((void*)0x0044CB10)

#endif /* SAMT_INCL_FUNCPTRS */

#endif /* _SA2B_SCORE_H_ */
