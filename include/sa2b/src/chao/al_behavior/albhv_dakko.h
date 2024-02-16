/*
*   Sonic Adventure Mod Tools (SA2B) - '/src/chao/al_behavior/albhv_dakko.h'
*
*   Contains functions related to the Chao dakko (hug) behaviors.
*
*   Contributors:
*   -   SEGA - Sonic Team,
*   -   Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC.
*/
#ifndef _SA2B_CHAO_ALBVH_DAKKO_H_
#define _SA2B_CHAO_ALBVH_DAKKO_H_

/************************/
/*  Includes            */
/************************/
#include <sa2b/src/chao/al_behavior.h>

/************************/
/*  Functions           */
/************************/
EXTERN_START
int32_t  ALBHV_DakkoNormal(TASK* tp);
int32_t  ALBHV_DakkoDislike(TASK* tp);
int32_t  ALBHV_DakkoLike(TASK* tp);
int32_t  ALBHV_DakkoTron(TASK* tp);
int32_t  ALBHV_Dakko(TASK* tp);

EXTERN_END

/************************/
/*  Function Ptrs       */
/************************/
#ifdef SAMT_INCLUDE_FUNC_PTRS
/** Function ptrs **/
#define ALBHV_DakkoNormal_p     BhvFuncPtr(0x005662B0)
#define ALBHV_DakkoDislike_p    BhvFuncPtr(0x00566300)
#define ALBHV_DakkoLike_p       BhvFuncPtr(0x005660A0)
#define ALBHV_DakkoTron_p       BhvFuncPtr(0x00566580)
#define ALBHV_Dakko_p           BhvFuncPtr(0x00566670)

#endif /* SAMT_INCLUDE_FUNC_PTRS */

#endif /* _SA2B_CHAO_ALBVH_DAKKO_H_ */
