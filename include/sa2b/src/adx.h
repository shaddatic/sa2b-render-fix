/*
*   Sonic Adventure Mod Tools (SA2B) - '/src/adx.h'
*
*   Description:
*       Contains functions for playing ADX files.
*
*   Contributors:
*   -   SEGA - Sonic Team,
*   -   Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC.
*/
#ifndef _SA2B_ADX_H_
#define _SA2B_ADX_H_

/************************/
/*  Functions           */
/************************/
EXTERN_START
/** Play ADX file **/
void    BGM_Play( const char* f );
/** Set ADX to loop **/
void    BGM_SetRound( void );
/** Stop ADX **/
void    BGM_Stop( void );

/** Plays an ADX for one-loop, while stopping the current 
    BGM and resuming it after **/
void    Jingle_Play( const char* f );

EXTERN_END

/************************/
/*  Function Ptrs       */
/************************/
#ifdef SAMT_INCLUDE_FUNC_PTRS
/** Function ptrs **/
#   define BGM_SetRound_p          FuncPtr(void, __cdecl, (void), 0x00442D90)
#   define BGM_Stop_p              FuncPtr(void, __cdecl, (void), 0x00442F50)

/** User-Function ptrs **/
#   define BGM_Play_p              ((void*)0x00442CF0)
#   define Jingle_Play_p           ((void*)0x00443480)

#endif/*SAMT_INCLUDE_FUNC_PTRS*/

#endif/*_SA2B_ADX_H_*/
