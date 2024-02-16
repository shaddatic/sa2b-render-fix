/*
*   Sonic Adventure Mod Tools (SA2B) - '/src/chao/al_behavior/albhv_move.h'
*
*   Contains functions related to the Chao move behaviors.
*
*   Contributors:
*   -   SEGA - Sonic Team,
*   -   Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC.
*/
#ifndef _SA2B_CHAO_ALBVH_MOVE_H_
#define _SA2B_CHAO_ALBVH_MOVE_H_

/************************/
/*  Includes            */
/************************/
#include <sa2b/src/chao/al_behavior.h>

/************************/
/*  Functions           */
/************************/
EXTERN_START
int32_t  ALBHV_Climb(TASK* tp);
int32_t  ALBHV_Glide(TASK* tp);
int32_t  ALBHV_NoticePlayer(TASK* tp);

EXTERN_END

/************************/
/*  Function Ptrs       */
/************************/
#ifdef SAMT_INCLUDE_FUNC_PTRS
/** Function ptrs **/
#define ALBHV_Climb_p           BhvFuncPtr(0x00562EB0)
#define ALBHV_Glide_p           BhvFuncPtr(0x005630C0)
#define ALBHV_NoticePlayer_p    BhvFuncPtr(0x005634D0)

#endif /* SAMT_INCLUDE_FUNC_PTRS */

#endif /* _SA2B_CHAO_ALBVH_MOVE_H_ */
