/*
*   Sonic Adventure Mod Tools (SA2B) - '/src/chao/al_behavior/albhv_eat.h'
*
*   Contains functions related to the Chao eat behaviors.
*
*   Contributors:
*   -   SEGA - Sonic Team,
*   -   Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC.
*/
#ifndef _SA2B_CHAO_ALBVH_EAT_H_
#define _SA2B_CHAO_ALBVH_EAT_H_

/************************/
/*  Includes            */
/************************/
#include <sa2b/src/chao/al_behavior.h>

/************************/
/*  Functions           */
/************************/
EXTERN_START
int32_t  ALBHV_Eat(TASK* tp);
int32_t  ALBHV_TurnToFruit(TASK* tp);

EXTERN_END

/************************/
/*  Function Ptrs       */
/************************/
#ifdef SAMT_INCLUDE_FUNC_PTRS
/** Function ptrs **/
#define ALBHV_Eat_p             BhvFuncPtr(0x005607C0)
#define ALBHV_TurnToFruit_p     BhvFuncPtr(0x00569240)

#endif /* SAMT_INCLUDE_FUNC_PTRS */

#endif /* _SA2B_CHAO_ALBVH_EAT_H_ */
