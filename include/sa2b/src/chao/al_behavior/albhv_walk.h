/*
*   Sonic Adventure Mod Tools (SA2B) - '/src/chao/al_behavior/albhv_walk.h'
*
*   Contains functions related to the Chao walk behaviors.
*
*   Contributors:
*   -   SEGA - Sonic Team,
*   -   Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC.
*/
#ifndef _SA2B_CHAO_ALBVH_WALK_H_
#define _SA2B_CHAO_ALBVH_WALK_H_

/************************/
/*  Includes            */
/************************/
#include <sa2b/src/chao/al_behavior.h>

/************************/
/*  Functions           */
/************************/
EXTERN_START
void    AL_WalkSelect(TASK* tp);

int32_t  ALBHV_Move(TASK* tp);

EXTERN_END

/************************/
/*  Function Ptrs       */
/************************/
#ifdef SAMT_INCLUDE_FUNC_PTRS
/** Function ptrs **/
#define ALBHV_Move_p        BhvFuncPtr(0x00562D20)

/** User-Function ptrs **/
EXTERN const void* const AL_WalkSelect_p;

#endif /* SAMT_INCLUDE_FUNC_PTRS */

#endif /* _SA2B_CHAO_ALBVH_WALK_H_ */
