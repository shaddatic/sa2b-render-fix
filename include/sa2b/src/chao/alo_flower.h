/*
*   Sonic Adventure Mod Tools (SA2B) - '/src/chao/alo_flower.h'
*
*   Contains functions related to Chao mating nests and flowers.
*
*   Contributors:
*   -   SEGA - Sonic Team,
*   -   Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC.
*/
#ifndef _SA2B_CHAO_FLOWER_H_
#define _SA2B_CHAO_FLOWER_H_

/************************/
/*  Includes            */
/************************/
#include <sa2b/ninja/njcommon.h>

/************************/
/*  Abstract Types      */
/************************/
typedef struct task     TASK;

/************************/
/*  Functions           */
/************************/
EXTERN_START
/*
*   Chao Nest
*/
TASK*   ALO_CreateNest(TASK* pChaoTask);

/** Task functions **/
void    ALO_NestExecutor(TASK* tp);

/*
*   Chao Nest Flowers
*/
TASK*   ALO_NestFlowerCreate(TASK* pNestTask, NJS_POINT3* pPos);

/** Task functions **/
void    ALO_NestFlowerExecutor(TASK* tp);
void    ALO_NestFlowerDisplayer(TASK* tp);

EXTERN_END

/************************/
/*  Function Ptrs       */
/************************/
#ifdef SAMT_INCLUDE_FUNC_PTRS
/** Function ptrs **/
#define ALO_NestExecutor_p              FuncPtr(void, __cdecl, (TASK*), 0x005AAE20)
#define ALO_NestFlowerExecutor_p        FuncPtr(void, __cdecl, (TASK*), 0x005AABF0)
#define ALO_NestFlowerDisplayer_p       FuncPtr(void, __cdecl, (TASK*), 0x005AAC60)

/** User-Function ptrs **/
EXTERN const void* const ALO_CreateNest_p;
EXTERN const void* const ALO_NestFlowerCreate_p;

#endif /* SAMT_INCLUDE_FUNC_PTRS */

#endif /* _SA2B_CHAO_FLOWER_H_ */
