/*
*   Sonic Adventure Mod Tools (SA2B) - '/src/chao/stg_race/alo_race_fallobject.h'
*
*   Contains functions for the Race fall object.
*
*   Contributors:
*   -   SEGA - Sonic Team,
*   -   Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC.
*/
#ifndef _SA2B_CHAO_RACE_FALLOBJECT_H_
#define _SA2B_CHAO_RACE_FALLOBJECT_H_

/************************/
/*  Abstract Types      */
/************************/
typedef struct task     TASK;

/************************/
/*  Includes            */
/************************/
#include <sa2b/ninja/njcommon.h>

/************************/
/*  Functions           */
/************************/
EXTERN_START
void    CreateFallObject(NJS_POINT3* pPos);

/** Task functions **/
void    FallObjectExecutor(TASK* tp);

EXTERN_END

/************************/
/*  Function Ptrs       */
/************************/
#ifdef SAMT_INCLUDE_FUNC_PTRS
/** Function ptrs **/
#define CreateFallObject_p      FuncPtr(void, __cdecl, (NJS_POINT3*), 0x0053B0A0)
#define FallObjectExecutor_p    FuncPtr(void, __cdecl, (TASK*)      , 0x0053AE10)

#endif /* SAMT_INCLUDE_FUNC_PTRS */

#endif /* _SA2B_CHAO_RACE_FALLOBJECT_H_ */
