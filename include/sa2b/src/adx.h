/*
*   Sonic Adventure Mod Tools (SA2B) - '/src/adx.h'
*
*   Contains functions for playing ADX files
*
*   Contributors:
*   -   SEGA - Sonic Team,
*   -   Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC.
*/
#pragma once

/************************/
/*  Function Pointers   */
/************************/
FuncPtr(void, __cdecl, BGM_SetRound, (), 0x00442D90);
FuncPtr(void, __cdecl, BGM_Stop, (), 0x00442F50);

/************************/
/*  User Functions      */
/************************/
void    BGM_Play(const char* f);

/** Plays an ADX for one-loop, while stopping the current 
    BGM and resuming it after **/
void    Jingle_Play(const char* f);

/************************/
/*  User Functions Ptrs */
/************************/
#ifdef SAMT_INCLUDE_USER_PTRS

extern const void* BGM_Play_p;

extern const void* Jingle_Play_p;

#endif