/*
*   Sonic Adventure Mod Tools (SA2B) - '/extern/cpp.h'
*
*   Description:
*       Contains functions and pointers to the game's C++
*   standard operators.
*
*   Contributors:
*   -   Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC.
*/
#ifndef _EXTERN_CPP_H_
#define _EXTERN_CPP_H_

/************************/
/*  Functions           */
/************************/
EXTERN_START
void*   ___new(size_t _Size);
void    ___delete(void* _Block);

EXTERN_END

/************************/
/*  Function Ptrs       */
/************************/
#ifdef SAMT_INCLUDE_FUNC_PTRS
/** Function ptr **/
#define ___new_p        FuncPtr(void*, __cdecl, (size_t), 0x007A5DA1)
#define ___delete_p     FuncPtr(void , __cdecl, (void*) , 0x007A5974)

#endif /* SAMT_INCLUDE_FUNC_PTRS */

#endif /* _EXTERN_CPP_H_ */
