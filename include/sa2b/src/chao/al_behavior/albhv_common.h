/*
*   Sonic Adventure Mod Tools (SA2B) - '/src/chao/al_behavior/albhv_common.h'
*
*   Contains functions related to the Chao common behaviors.
*
*   Contributors:
*   -   SEGA - Sonic Team,
*   -   Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC.
*/
#ifndef _SA2B_CHAO_ALBVH_COMMON_H_
#define _SA2B_CHAO_ALBVH_COMMON_H_

/************************/
/*  Includes            */
/************************/
#include <sa2b/src/chao/al_behavior.h>

/************************/
/*  Functions           */
/************************/
EXTERN_START
int32_t  ALBHV_Turn(TASK* tp);
int32_t  ALBHV_TurnRandom(TASK* tp);
int32_t  ALBHV_GoToLockOn(TASK* tp);

EXTERN_END

/************************/
/*  Function Ptrs       */
/************************/
#ifdef SAMT_INCLUDE_FUNC_PTRS
/** Function ptrs **/
#define ALBHV_Turn_p            BhvFuncPtr(0x0056B740)
#define ALBHV_TurnRandom_p      BhvFuncPtr(0x0056B960)
#define ALBHV_GoToLockOn_p      BhvFuncPtr(0x0056BA80)

#endif /* SAMT_INCLUDE_FUNC_PTRS */

#endif /* _SA2B_CHAO_ALBVH_COMMON_H_ */
