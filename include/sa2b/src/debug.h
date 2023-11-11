/*
*   Sonic Adventure Mod Tools (SA2B) - '/src/debug.h'
*
*   Contains data and functions related to the game's debug features.
*
*   Contributors:
*   -   SEGA - Sonic Team,
*   -   Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC.
*/
#ifndef _SA2B_DEBUG_H_
#define _SA2B_DEBUG_H_

/************************/
/*  Functions           */
/************************/
#define ShowOverscanGrid            DataRef(bool32, 0x0174BA6C)

/************************/
/*  Functions           */
/************************/
EXTERN_START
sint32  ___OutputDebugString(const char* str, ...);

EXTERN_END

/************************/
/*  Function Ptrs       */
/************************/
#ifdef SAMT_INCLUDE_FUNC_PTRS
/** Function ptrs **/
#define ___OutputDebugString_p      FuncPtr(sint32, __cdecl, (const char*, ...), 0x00426740)

#endif /* SAMT_INCLUDE_FUNC_PTRS */

#endif /* _SA2B_DEBUG_H_ */
