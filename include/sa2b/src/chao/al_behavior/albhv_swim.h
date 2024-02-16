/*
*   Sonic Adventure Mod Tools (SA2B) - '/src/chao/al_behavior/albhv_swim.h'
*
*   Contains functions related to the Chao swim behaviors.
*
*   Contributors:
*   -   SEGA - Sonic Team,
*   -   Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC.
*/
#ifndef _SA2B_CHAO_ALBVH_SWIM_H_
#define _SA2B_CHAO_ALBVH_SWIM_H_

/************************/
/*  Includes            */
/************************/
#include <sa2b/src/chao/al_behavior.h>

/************************/
/*  Functions           */
/************************/
EXTERN_START
int32_t  ALBHV_Swim(TASK* tp);
int32_t  ALBHV_SwimPuha(TASK* tp);

EXTERN_END

/************************/
/*  Function Ptrs       */
/************************/
#ifdef SAMT_INCLUDE_FUNC_PTRS
/** Function ptrs **/
#define ALBHV_Swim_p            BhvFuncPtr(0x00562330)
#define ALBHV_SwimPuha_p        BhvFuncPtr(0x00562160)

#endif /* SAMT_INCLUDE_FUNC_PTRS */

#endif /* _SA2B_CHAO_ALBVH_SWIM_H_ */
