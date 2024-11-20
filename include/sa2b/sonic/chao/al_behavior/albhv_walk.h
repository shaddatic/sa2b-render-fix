/*
*   Sonic Adventure Mod Tools (SA2B) - '/sonic/chao/al_behavior/albhv_walk.h'
*
*   Description:
*       Contains functions related to the Chao walk behaviors.
*
*   Contributors:
*     - SEGA - Sonic Team,
*     - Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC
*/
#ifndef _SA2B_CHAO_ALBVH_WALK_H_
#define _SA2B_CHAO_ALBVH_WALK_H_

/************************/
/*  Includes            */
/************************/
#include <sa2b/sonic/chao/al_behavior.h>

/************************/
/*  Functions           */
/************************/
EXTERN_START
void    AL_WalkSelect( task* tp );

int32_t ALBHV_Move( task* tp );

EXTERN_END

/************************/
/*  Function Ptrs       */
/************************/
#ifdef SAMT_INCL_FUNCPTRS
/** Behavior ptrs **/
#   define ALBHV_Move_p         BHVFUNC_PTR(0x00562D20)

/** User-Function ptrs **/
#   define AL_WalkSelect_p      ((void*)0x005A3650)

#endif/*SAMT_INCL_FUNCPTRS*/

#endif/*_SA2B_CHAO_ALBVH_WALK_H_*/
