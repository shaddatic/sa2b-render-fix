/*
*   Sonic Adventure Mod Tools (SA2B) - '/src/chao/stg_race/alo_race_karitoy.h'
*
*   Contains functions for the Race quiz items.
*
*   Contributors:
*   -   SEGA - Sonic Team,
*   -   Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC.
*/
#ifndef _SA2B_CHAO_RACE_KARITOY_H_
#define _SA2B_CHAO_RACE_KARITOY_H_

/************************/
/*  Abstract Types      */
/************************/
typedef struct task     TASK;

/************************/
/*  Functions           */
/************************/
EXTERN_START
/** Task functions **/
void    ALO_RaceKariToyExecutor(TASK* tp);

EXTERN_END

/************************/
/*  Function Ptrs       */
/************************/
#ifdef SAMT_INCLUDE_FUNC_PTRS
/** Function ptrs **/
#define ALO_RaceKariToyExecutor_p       FuncPtr(void, __cdecl, (TASK*), 0x00560470)

#endif /* SAMT_INCLUDE_FUNC_PTRS */

#endif /* _SA2B_CHAO_RACE_KARITOY_H_ */
