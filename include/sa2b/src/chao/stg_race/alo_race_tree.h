/*
*   Sonic Adventure Mod Tools (SA2B) - '/src/chao/stg_race/alo_race_tree.h'
*
*   Contains functions for the Race trees.
*
*   Contributors:
*   -   SEGA - Sonic Team,
*   -   Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC.
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
#ifdef SAMT_INCLUDE_FUNC_PTRS
/** Function ptrs **/
#define ALR_TreeExecutor_p  FuncPtr(void, __cdecl, (TASK*), 0x00537620)

#endif /* SAMT_INCLUDE_FUNC_PTRS */

#endif /* _SA2B_CHAO_RACE_TREE_H_ */
