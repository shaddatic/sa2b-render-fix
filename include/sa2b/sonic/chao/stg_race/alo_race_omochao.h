/*
*   Sonic Adventure Mod Tools (SA2B) - '/sonic/chao/stg_race/alo_race_omochao.h'
*
*   Description:
*       Contains functions for the Race Omochao.
*
*   Contributors:
*     - SEGA - Sonic Team,
*     - Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC
*/
#ifndef _SA2B_CHAO_RACE_OMOCHAO_H_
#define _SA2B_CHAO_RACE_OMOCHAO_H_

/************************/
/*  Abstract Types      */
/************************/
typedef struct task     task;

/************************/
/*  Functions           */
/************************/
EXTERN_START
/** Task functions **/
void    ALR_OmochaoExecutor(task* tp);

EXTERN_END

/************************/
/*  Function Ptrs       */
/************************/
#ifdef  SAMT_INCL_FUNCPTRS
/** Function ptrs **/
#   define ALR_OmochaoExecutor_p        FUNC_PTR(void, __cdecl, (task*), 0x0056A830)

#endif/*SAMT_INCL_FUNCPTRS*/

#endif/*_SA2B_CHAO_RACE_OMOCHAO_H_*/
