/*
*   Sonic Adventure Mod Tools (SA2B) - '/src/chao/al_toy/alo_horse.h'
*
*   Contains functions and data related to the horse garden object.
*
*   Contributors:
*   -   SEGA - Sonic Team,
*   -   Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC.
*/
#ifndef _SA2B_CHAO_TOY_HORSE_H_
#define _SA2B_CHAO_TOY_HORSE_H_

/************************/
/*  Includes            */
/************************/
#include <sa2b/ninja/njcommon.h>

/************************/
/*  Abstract Types      */
/************************/
typedef struct task         TASK;
typedef struct taskwk       TASKWK;

/************************/
/*  Functions           */
/************************/
EXTERN_START
TASKWK* ALO_HorseCreateTask(NJS_POINT3* pPos);

/** Internal task functions **/
void    ALO_HorseExecutor(TASK* tp);

EXTERN_END

/************************/
/*  Function Ptrs       */
/************************/
#ifdef SAMT_INCLUDE_FUNC_PTRS
/** Function ptrs **/
#define ALO_HorseExecutor_p     FuncPtr(void, __cdecl, (TASK*), 0x00580BC0)

/** User-Function ptrs **/
EXTERN const void* const ALO_HorseCreateTask_p;

#endif /* SAMT_INCLUDE_FUNC_PTRS */

#endif /* _SA2B_CHAO_TOY_HORSE_H_ */
