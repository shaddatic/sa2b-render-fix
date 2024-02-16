/*
*   Sonic Adventure Mod Tools (SA2B) - '/src/chao/al_behavior.h'
*
*   Contains defines, typedefs, and functions for the Chao behavior system.
*
*   Contributors:
*   -   SEGA - Sonic Team,
*   -   Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC.
*/
#ifndef _SA2B_CHAO_ALBVH_H_
#define _SA2B_CHAO_ALBVH_H_

/************************/
/*  Defines             */
/************************/
#define BhvFuncPtr(ADDR)   FuncPtr(int32_t, __cdecl, (TASK*), ADDR)

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
#ifdef SAMT_INCLUDE_FUNC_PTRS
/** User-Function ptrs **/
EXTERN const void* const AL_SetBehaviorWithTimer_p;
EXTERN const void* const AL_SetNextBehavior_p;

#endif /* SAMT_INCLUDE_FUNC_PTRS */

#endif /* _SA2B_CHAO_ALBVH_H_ */
