/*
*   Sonic Adventure Mod Tools (SA2B) - '/src/debug.h'
*
*   Description:
*       Contains data and functions related to the game's debug
*   features.
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
#define ShowOverscanGrid            DataRef(bool32_t, 0x0174BA6C)

/************************/
/*  Functions           */
/************************/
EXTERN_START
int32_t  ___OutputDebugString( const char* str, ... );

EXTERN_END

/************************/
/*  Macros              */
/************************/
#define OutputFormat(...)           ___OutputDebugString(__VA_ARGS__)
#define OutputString(_s)            ___OutputDebugString((_s))
#define OutputInt(_i)               ___OutputDebugString("%i", (_i))
#define OutputFloat(_f)             ___OutputDebugString("%f", (_f))
#define OutputCharacter(_c)         ___OutputDebugString("%c", (_c))
#define OutputPointer(_p)           ___OutputDebugString("%p", (_p))

#define OutputPoint3(_p3)           ___OutputDebugString("%f, %f, %f", (_p3).x, (_p3).y, (_p3).z)
#define OutputAngle3(_a3)           ___OutputDebugString("%i, %i, %i", (_a3).x, (_a3).y, (_a3).z)

#ifndef NDEBUG
#define OutputDebugFormat(...)      ___OutputDebugString(__VA_ARGS__)
#define OutputDebugString(_s)       ___OutputDebugString((_s))
#define OutputDebugInt(_i)          ___OutputDebugString("%i", (_i))
#define OutputDebugFloat(_f)        ___OutputDebugString("%f", (_f))
#define OutputDebugCharacter(_c)    ___OutputDebugString("%c", (_c))
#define OutputDebugPointer(_p)      ___OutputDebugString("%p", (_p))

#define OutputDebugPoint3(_p3)      ___OutputDebugString("%f, %f, %f", (_p3).x, (_p3).y, (_p3).z)
#define OutputDebugAngle3(_a3)      ___OutputDebugString("%i, %i, %i", (_a3).x, (_a3).y, (_a3).z)
#else
#define OutputDebugFormat(...)
#define OutputDebugString(_s)
#define OutputDebugInt(_i)
#define OutputDebugFloat(_f)
#define OutputDebugCharacter(_c)
#define OutputDebugPointer(_p)

#define OutputDebugPoint3(_p3)
#define OutputDebugAngle3(_a3)
#endif

/************************/
/*  Function Ptrs       */
/************************/
#ifdef SAMT_INCLUDE_FUNC_PTRS
/** Function ptrs **/
#   define ___OutputDebugString_p      FuncPtr(int32_t, __cdecl, (const char*, ...), 0x00426740)

#endif/*SAMT_INCLUDE_FUNC_PTRS*/

#endif/*_SA2B_DEBUG_H_*/
