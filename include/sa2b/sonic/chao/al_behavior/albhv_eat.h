/*
*   Sonic Adventure Mod Tools (SA2B) - '/sonic/chao/al_behavior/albhv_eat.h'
*
*   Description:
*       Contains functions related to the Chao eat behaviors.
*
*   Contributors:
*     - SEGA - Sonic Team,
*     - Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC
*/
#ifndef _SA2B_CHAO_ALBVH_EAT_H_
#define _SA2B_CHAO_ALBVH_EAT_H_

/************************/
/*  Includes            */
/************************/
#include <sa2b/sonic/chao/al_behavior.h>

/************************/
/*  Functions           */
/************************/
EXTERN_START
int32_t ALBHV_Eat(         task* tp );
int32_t ALBHV_TurnToFruit( task* tp );

EXTERN_END

/************************/
/*  Function Ptrs       */
/************************/
#ifdef  SAMT_INCL_FUNCPTRS
/** Behavior ptrs **/
#   define ALBHV_Eat_p              BHVFUNC_PTR(0x005607C0)
#   define ALBHV_TurnToFruit_p      BHVFUNC_PTR(0x00569240)

#endif/*SAMT_INCL_FUNCPTRS*/

#endif/*_SA2B_CHAO_ALBVH_EAT_H_*/
