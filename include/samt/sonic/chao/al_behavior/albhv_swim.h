/*
*   SAMT for Sonic Adventure 2 (PC, 2012) - '/sonic/chao/al_behavior/albhv_swim.h'
*
*   Description:
*       Contains functions related to the Chao swim behaviors.
*/
#ifndef _SA2B_CHAO_ALBVH_SWIM_H_
#define _SA2B_CHAO_ALBVH_SWIM_H_

/************************/
/*  Includes            */
/************************/
#include <samt/sonic/chao/al_behavior.h>

/************************/
/*  Functions           */
/************************/
EXTERN_START
int32_t ALBHV_Swim(     task* tp );
int32_t ALBHV_SwimPuha( task* tp );

EXTERN_END

/************************/
/*  Function Ptrs       */
/************************/
#ifdef  SAMT_INCL_FUNCPTRS
/** Behavior ptrs **/
#   define ALBHV_Swim_p             BHVFUNC_PTR(0x00562330)
#   define ALBHV_SwimPuha_p         BHVFUNC_PTR(0x00562160)

#endif/*SAMT_INCL_FUNCPTRS*/

#endif/*_SA2B_CHAO_ALBVH_SWIM_H_*/
