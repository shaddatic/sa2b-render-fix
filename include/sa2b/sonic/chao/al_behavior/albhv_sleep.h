/*
*   Sonic Adventure Mod Tools (SA2B) - '/sonic/chao/al_behavior/albhv_sleep.h'
*
*   Description:
*       Contains functions related to the Chao sleep behaviors.
*
*   Contributors:
*     - SEGA - Sonic Team,
*     - Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC
*/
#ifndef _SA2B_CHAO_ALBVH_SLEEP_H_
#define _SA2B_CHAO_ALBVH_SLEEP_H_

/************************/
/*  Includes            */
/************************/
#include <sa2b/sonic/chao/al_behavior.h>

/************************/
/*  Functions           */
/************************/
EXTERN_START
int32_t ALBHV_Sleep(       TASK* tp );
int32_t ALBHV_SleepSelect( TASK* tp );

EXTERN_END

/************************/
/*  Function Ptrs       */
/************************/
#ifdef  SAMT_INCL_FUNCPTRS
/** Behavior ptrs **/
#   define ALBHV_Sleep_p            BhvFUNC_PTR(0x0054EF10)
#   define ALBHV_SleepSelect_p      BhvFUNC_PTR(0x0054EE10)

#endif/*SAMT_INCL_FUNCPTRS*/

#endif/*_SA2B_CHAO_ALBVH_SLEEP_H_*/
