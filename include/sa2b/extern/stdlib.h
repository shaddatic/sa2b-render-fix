/*
*   Sonic Adventure Mod Tools (SA2B) - '/extern/stdlib.h'
*
*   Description:
*       Contains functions and pointers to the game's stdlib
*   imports.
*
*   Contributors:
*   -   Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC.
*/
#ifndef _EXTERN_STDLIB_H_
#define _EXTERN_STDLIB_H_

/************************/
/*  Constants           */
/************************/
#define ___RAND_MAX      (0x7fff)

/************************/
/*  Functions           */
/************************/
EXTERN_START
void*   ___malloc(size_t _Size);
void    ___free(void* _Block);
void*   ___realloc(void* _Block, size_t _Size);

int32_t  ___rand(void);
void    ___srand(uint32_t _Seed);

void    ___exit(int32_t);

EXTERN_END

/************************/
/*  Function Ptrs       */
/************************/
#ifdef SAMT_INCLUDE_FUNC_PTRS
/** Function ptr **/
#define ___malloc_p         FuncPtr(void* , __cdecl, (size_t)       , 0x007A84A5)
#define ___free_p           FuncPtr(void  , __cdecl, (void*)        , 0x007A80DD)
#define ___realloc_p        FuncPtr(void* , __cdecl, (void*, size_t), 0x007A8607)
#define ___rand_p           FuncPtr(int32_t, __cdecl, (void)         , 0x007A89D8)
#define ___srand_p          FuncPtr(void  , __cdecl, (uint32_t)       , 0x007A89C6)
#define ___exit_p           FuncPtr(void  , __cdecl, (int32_t)       , 0x007ACB70)

#endif /* SAMT_INCLUDE_FUNC_PTRS */

#endif /* _EXTERN_STDLIB_H_ */
