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
#define ssNumPlayer     DataAry(int16_t , 0x0174B024, [2])

#define ssNumRing       DataAry(int16_t , 0x0174B028, [2])

#define loop_const      DataRef(int32_t , 0x01DEB50C)
#define ulGlobalTimer   DataRef(uint32_t, 0x0174B038)

#define GameTimer       DataRef(int32_t , 0x0174B03C)

#define ucFrames        DataRef(uint8_t , 0x0174AFDD)
#define ucSeconds       DataRef(uint8_t , 0x0174AFDC)
#define ucMinutes       DataRef(uint8_t , 0x0174AFDB)

#define bWake           DataRef(bool    , 0x0174AFF7)

#define gu32TotalRing   DataRef(uint32_t, 0x0174B05C)

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
#ifdef SAMT_INCLUDE_FUNC_PTRS
/** User-Function ptr **/
EXTERN const void* const AddNumRing_p;
EXTERN const void* const AddNumPlayer_p;

#endif /* SAMT_INCLUDE_FUNC_PTRS */

#endif /* _SA2B_SCORE_H_ */
