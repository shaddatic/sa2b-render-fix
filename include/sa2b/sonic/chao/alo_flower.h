/*
*   Sonic Adventure Mod Tools (SA2B) - '/sonic/chao/alo_flower.h'
*
*   Description:
*       Contains functions related to Chao mating nests and flowers.
*
*   Contributors:
*     - SEGA - Sonic Team,
*     - Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC
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
#ifdef  SAMT_INCL_FUNCPTRS
/** Function ptrs **/
#   define ALO_NestExecutor_p               FUNC_PTR(void, __cdecl, (TASK*), 0x005AAE20)
#   define ALO_NestFlowerExecutor_p         FUNC_PTR(void, __cdecl, (TASK*), 0x005AABF0)
#   define ALO_NestFlowerDisplayer_p        FUNC_PTR(void, __cdecl, (TASK*), 0x005AAC60)

/** User-Function ptrs **/
#   define ALO_CreateNest_p                 ((void*)0x005AAF60)
#   define ALO_NestFlowerCreate_p           ((void*)0x005AAD90)

#endif/*SAMT_INCL_FUNCPTRS*/

#endif/*_SA2B_CHAO_FLOWER_H_*/
