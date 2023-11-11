/*
*   Sonic Adventure Mod Tools (SA2B) - '/src/chao/stg_race/alo_race_box.h'
*
*   Contains functions for the Race Box object.
*
*   Contributors:
*   -   SEGA - Sonic Team,
*   -   Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC.
*/
#ifndef _SA2B_CHAO_RACE_BOX_H_
#define _SA2B_CHAO_RACE_BOX_H_

/************************/
/*  Abstract Types      */
/************************/
typedef struct task     TASK;

/************************/
/*  Functions           */
/************************/
EXTERN_START
/** Task functions **/
void    ALR_BoxExecutor(TASK* tp);

EXTERN_END

/************************/
/*  Function Ptrs       */
/************************/
#ifdef SAMT_INCLUDE_FUNC_PTRS
/** Function ptrs **/
#define ALR_BoxExecutor_p   FuncPtr(void, __cdecl, (TASK*), 0x0056A110)

#endif /* SAMT_INCLUDE_FUNC_PTRS */

#endif /* _SA2B_CHAO_RACE_BOX_H_ */
