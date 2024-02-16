/*
*   Sonic Adventure Mod Tools (SA2B) - '/src/chao/al_icon.h'
*
*   Contains functions related to Chao icons.
*
*   Contributors:
*   -   SEGA - Sonic Team,
*   -   Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC.
*/
#ifndef _SA2B_CHAO_ICON_H_
#define _SA2B_CHAO_ICON_H_

/************************/
/*  Abstract Types      */
/************************/
typedef struct task     TASK;

/************************/
/*  Functions           */
/************************/
EXTERN_START
int32_t  AL_CalcIconColor(TASK* tp);

EXTERN_END

/************************/
/*  Function Ptrs       */
/************************/
#ifdef SAMT_INCLUDE_FUNC_PTRS
/** User-Function ptrs **/
EXTERN const void* const AL_CalcIconColor_p;

#endif /* SAMT_INCLUDE_FUNC_PTRS */

#endif /* _SA2B_CHAO_ICON_H_ */
