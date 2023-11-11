/*
*   Sonic Adventure Mod Tools (SA2B) - '/extern/string.h'
*
*   Contains functions and pointers to the game's std string imports.
*
*   Contributors:
*   -   Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC.
*/
#ifndef _EXTERN_STRING_H_
#define _EXTERN_STRING_H_

/************************/
/*  Functions           */
/************************/
EXTERN_START
int     __strcmp(const char* _Str1, const char* _Str2);

void*   __memset(void* _Dst, int _Val, size_t _Size);
void*   __memcpy(void* _Dst, const void* _Src, size_t _Size);

EXTERN_END

/************************/
/*  Function Ptrs       */
/************************/
#ifdef SAMT_INCLUDE_FUNC_PTRS
/** Function ptr **/
#define __strcmp_p      FuncPtr(int   , __cdecl, (const char*, const char*)  , 0x007ACED0)
#define __memset_p      FuncPtr(void* , __cdecl, (void*, int, size_t)        , 0x007ACDE0)
#define __strncat_p     FuncPtr(char* , __cdecl, (char*, const char*, size_t), 0x007ACED0)
#define __strlen_p      FuncPtr(size_t, __cdecl, (const char*)               , 0x007A8C00)
#define __memcpy_p      FuncPtr(void* , __cdecl, (void*, const void*, size_t), 0x007AB860)

#endif /* SAMT_INCLUDE_FUNC_PTRS */

#endif /* _EXTERN_STRING_H_ */