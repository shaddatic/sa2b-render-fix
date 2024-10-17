/*
*   Sonic Adventure Mod Tools (SA2B) - '/sonic/chao/al_icon.h'
*
*   Description:
*       Contains functions related to Chao icons.
*
*   Contributors:
*     - SEGA - Sonic Team,
*     - Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC
*/
#ifndef _SA2B_CHAO_ICON_H_
#define _SA2B_CHAO_ICON_H_

/************************/
/*  Abstract Types      */
/************************/
typedef struct task     task;

/************************/
/*  Functions           */
/************************/
EXTERN_START
int32_t  AL_CalcIconColor(task* tp);

EXTERN_END

/************************/
/*  Function Ptrs       */
/************************/
#ifdef  SAMT_INCL_FUNCPTRS
/** User-Function ptrs **/
#   define AL_CalcIconColor_p       ((void*)0x0053B940)

#endif/*SAMT_INCL_FUNCPTRS*/

#endif/*_SA2B_CHAO_ICON_H_*/
