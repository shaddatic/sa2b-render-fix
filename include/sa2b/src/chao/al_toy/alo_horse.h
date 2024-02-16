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

/************************/
/*  Functions           */
/************************/
EXTERN_START
void    ALO_HorseCreate(NJS_POINT3* pPos);

/** Internal task functions **/
void    ALO_Horse(TASK* tp);
void    ALO_HorseExecutor(TASK* tp);
void    ALO_HorseDisplayer(TASK* tp);
void    ALO_HorseDestructor(TASK* tp); // Same function as many other ALO objects

EXTERN_END

/************************/
/*  Function Ptrs       */
/************************/
#ifdef SAMT_INCLUDE_FUNC_PTRS
/** Function ptrs **/
#define ALO_Horse_p             FuncPtr(void, __cdecl, (TASK*), 0x00580E80)
#define ALO_HorseExecutor_p     FuncPtr(void, __cdecl, (TASK*), 0x00580BC0)
#define ALO_HorseDisplayer_p    FuncPtr(void, __cdecl, (TASK*), 0x00580CA0)
#define ALO_HorseDestructor_p   FuncPtr(void, __cdecl, (TASK*), 0x0057B9B0)

/** User-Function ptrs **/
EXTERN const void* const ALO_HorseCreate_p;

#endif /* SAMT_INCLUDE_FUNC_PTRS */

#endif /* _SA2B_CHAO_TOY_HORSE_H_ */
