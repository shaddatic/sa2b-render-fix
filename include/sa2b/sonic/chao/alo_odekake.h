/*
*   Sonic Adventure Mod Tools (SA2B) - '/sonic/chao/alo_odekake.h'
*
*   Description:
*       Contains enums and functions related to Odekake machine.
*
*   Contributors:
*     - SEGA - Sonic Team,
*     - Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC
*/
#ifndef _SA2B_CHAO_ODEKAKE_H_
#define _SA2B_CHAO_ODEKAKE_H_

/************************/
/*  Includes            */
/************************/
#include <sa2b/ninja/ninja.h>

/************************/
/*  Abstract Types      */
/************************/
typedef struct task        task;

/************************/
/*  Structures          */
/************************/
#define GET_ODEKAKE_WORK(tp) ((ODEKAKE_WORK*)tp->awp)

typedef struct // AnyWk
{
    s32     ButtonState;
    s32     CoverMode;
    f32     CoverFrame;
    f32     ButtonPos;
    task*   pChaotask;
    s32     FileFlag;
    s32     BuyoFlag;
    s32     BuyoPhase;
    s32     MonitorMode;
    s32     MonitorCount;
    s32     MonitorTimer;
    s32     ring;
}
ODEKAKE_WORK;

/************************/
/*  Data                */
/************************/
#define OdekakeTaskPointer      DATA_REF(task*, 0x01AED318)
#define EnteringOdekake         DATA_REF(b32  , 0x01AED31C)

/** Crappy, half-baked, replacement case model by SOC **/
#define pSOCOdekakeModel        DATA_REF(void*, 0x1AED320)

/************************/
/*  Functions           */
/************************/
EXTERN_START
void    ALO_OdekakeMachineCreate(NJS_POINT3* pPos, Angle angy);

/** Task functions **/
void    ALO_OdekakeMachine(task* tp);
void    ALO_OdekakeMachineExecutor(task* tp);
void    ALO_OdekakeMachineDisplayerNeut(task* tp);
void    ALO_OdekakeMachineDestructor(task* tp);

EXTERN_END

/************************/
/*  Function Ptrs       */
/************************/
#ifdef  SAMT_INCL_FUNCPTRS
/** Function ptrs **/
#   define ALO_OdekakeMachine_p                     FUNC_PTR(void, __cdecl, (task*), 0x0057E460)
#   define ALO_OdekakeMachineExecutor_p             FUNC_PTR(void, __cdecl, (task*), 0x0057D540)
#   define ALO_OdekakeMachineDisplayerNeut_p        FUNC_PTR(void, __cdecl, (task*), 0x0057E060)
#   define ALO_OdekakeMachineDestructor_p           FUNC_PTR(void, __cdecl, (task*), 0x0057E040)

/** User-Function ptrs **/
#   define ALO_OdekakeMachineCreate_p               ((void*)0x0057E4F0)

#endif/*SAMT_INCL_FUNCPTRS*/

#endif/*_SA2B_CHAO_ODEKAKE_H_*/
