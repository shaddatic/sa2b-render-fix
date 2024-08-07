/*
*   Sonic Adventure Mod Tools (SA2B) - '/sonic/chao/al_behavior/albhv_swim.h'
*
*   Description:
*       Contains functions related to the Chao swim behaviors.
*
*   Contributors:
*     - SEGA - Sonic Team,
*     - Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC
*/
#ifndef _SA2B_CHAO_ALBVH_SWIM_H_
#define _SA2B_CHAO_ALBVH_SWIM_H_

/************************/
/*  Includes            */
/************************/
#include <sa2b/sonic/chao/al_behavior.h>

/************************/
/*  Functions           */
/************************/
EXTERN_START
int32_t ALBHV_Swim(     TASK* tp );
int32_t ALBHV_SwimPuha( TASK* tp );

EXTERN_END

/************************/
/*  Function Ptrs       */
/************************/
#ifdef  SAMT_INCL_FUNCPTRS
/** Behavior ptrs **/
#   define ALBHV_Swim_p             BhvFUNC_PTR(0x00562330)
#   define ALBHV_SwimPuha_p         BhvFUNC_PTR(0x00562160)

#endif/*SAMT_INCL_FUNCPTRS*/

#endif/*_SA2B_CHAO_ALBVH_SWIM_H_*/
