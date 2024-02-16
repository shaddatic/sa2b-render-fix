/*
*   Sonic Adventure Mod Tools (SA2B) - '/src/chao/al_behavior/albhv_thirsty.h'
*
*   Contains functions related to the Chao get-to-water behaviors.
*
*   Contributors:
*   -   SEGA - Sonic Team,
*   -   Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC.
*/
#ifndef _SA2B_CHAO_ALBVH_THIRSTY_H_
#define _SA2B_CHAO_ALBVH_THIRSTY_H_

/************************/
/*  Includes            */
/************************/
#include <sa2b/src/chao/al_behavior.h>

/************************/
/*  Functions           */
/************************/
EXTERN_START
int32_t  ALBHV_JumpToPond(TASK* tp);

EXTERN_END

/************************/
/*  Function Ptrs       */
/************************/
#ifdef SAMT_INCLUDE_FUNC_PTRS
/** Function ptrs **/
#define ALBHV_JumpToPond_p      BhvFuncPtr(0x005A0F40)

#endif /* SAMT_INCLUDE_FUNC_PTRS */

#endif /* _SA2B_CHAO_ALBVH_THIRSTY_H_ */
