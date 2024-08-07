/*
*   Sonic Adventure Mod Tools (SA2B) - '/sonic/chao/al_behavior.h'
*
*   Description:
*       Contains defines, typedefs, and functions for the Chao
*   behavior system.
*
*   Contributors:
*     - SEGA - Sonic Team,
*     - Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC
*/
#ifndef _SA2B_CHAO_ALBVH_H_
#define _SA2B_CHAO_ALBVH_H_

/************************/
/*  Defines             */
/************************/
#define BhvFUNC_PTR(ADDR)   FUNC_PTR(int32_t, __cdecl, (TASK*), ADDR)

/************************/
/*  Absract Types       */
/************************/
typedef struct task     TASK;

/************************/
/*  Typedefs             */
/************************/
typedef int32_t(__cdecl* BHV_FUNC)(TASK*);

/************************/
/*  Enums               */
/************************/
enum
{
    BHV_RET_CONTINUE,
    BHV_RET_FINISH,
    BHV_RET_THINK,
    BHV_RET_BREAK,
};

/************************/
/*  Functions           */
/************************/
EXTERN_START
void    AL_SetBehavior(TASK* tp, BHV_FUNC bhav);
void    AL_SetBehaviorWithTimer(TASK* tp, BHV_FUNC bhav, int timer);

void    AL_SetNextBehavior(TASK* tp, BHV_FUNC bhav);

EXTERN_END

/************************/
/*  Function Ptrs       */
/************************/
#ifdef  SAMT_INCL_FUNCPTRS
/** User-Function ptrs **/
#   define AL_SetBehaviorWithTimer_p    ((void*)0x0053D890)
#   define AL_SetNextBehavior_p         ((void*)0x0053D970)

#endif/*SAMT_INCL_FUNCPTRS*/

#endif/*_SA2B_CHAO_ALBVH_H_*/
