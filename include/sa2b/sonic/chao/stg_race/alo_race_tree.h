/*
*   Sonic Adventure Mod Tools (SA2B) - '/sonic/chao/stg_race/alo_race_tree.h'
*
*   Description:
*       Contains functions for the Race trees.
*
*   Contributors:
*     - SEGA - Sonic Team,
*     - Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC
*/
#ifndef _SA2B_CHAO_RACE_TREE_H_
#define _SA2B_CHAO_RACE_TREE_H_

/************************/
/*  Abstract Types      */
/************************/
typedef struct task     TASK;

/************************/
/*  Functions           */
/************************/
EXTERN_START
/** Task functions **/
void    ALR_TreeExecutor(TASK* tp);

EXTERN_END

/************************/
/*  Function Ptrs       */
/************************/
#ifdef  SAMT_INCL_FUNCPTRS
/** Function ptrs **/
#   define ALR_TreeExecutor_p       FUNC_PTR(void, __cdecl, (TASK*), 0x00537620)

#endif/*SAMT_INCL_FUNCPTRS*/

#endif/*_SA2B_CHAO_RACE_TREE_H_*/
