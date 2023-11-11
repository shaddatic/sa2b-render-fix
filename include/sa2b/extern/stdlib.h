/*
*   Sonic Adventure Mod Tools (SA2B) - '/extern/stdlib.h'
*
*   Contains functions and pointers to the game's stdlib imports.
*
*   Contributors:
*   -   Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC.
*/
#ifndef _EXTERN_STDLIB_H_
#define _EXTERN_STDLIB_H_

/************************/
/*  Functions           */
/************************/
EXTERN_START
void*   __malloc(size_t _Size);
void    __free(void* _Block);
void*   __realloc(void* _Block, size_t _Size);

sint32  __rand(void);
void    __srand(uint32 _Seed);

void    __exit(sint32);

EXTERN_END

/************************/
/*  Function Ptrs       */
/************************/
#ifdef SAMT_INCLUDE_FUNC_PTRS
/** Function ptr **/
#define __malloc_p      FuncPtr(void* , __cdecl, (size_t)       , 0x007A84A5)
#define __free_p        FuncPtr(void  , __cdecl, (void*)        , 0x007A80DD)
#define __realloc_p     FuncPtr(void* , __cdecl, (void*, size_t), 0x007A8607)
#define __rand_p        FuncPtr(sint32, __cdecl, (void)         , 0x007A89D8)
#define __srand_p       FuncPtr(void  , __cdecl, (uint32)       , 0x007A89C6)
#define __exit_p        FuncPtr(void  , __cdecl, (sint32)       , 0x007ACB70)

#endif /* SAMT_INCLUDE_FUNC_PTRS */

#endif /* _EXTERN_STDLIB_H_ */