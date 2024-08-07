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
typedef struct task        TASK;
typedef struct taskwk    TASKWK;

/************************/
/*  Structures          */
/************************/
#define GET_ODEKAKE_WORK(tp) ((ODAKAKE_WORK*)tp->awp)

typedef struct // ANYWK
{
    int32_t ButtonState;
    int32_t CoverMode;
    f32       CoverFrame;
    f32       ButtonPos;
    TASK* pChaoTask;
    int32_t FileFlag;
    int32_t BuyoFlag;
    int32_t BuyoPhase;
    int32_t MonitorMode;
    int32_t MonitorCount;
    int32_t MonitorTimer;
    int32_t ring;
}
ODAKAKE_WORK;

/************************/
/*  Data                */
/************************/
#define OdekakeTaskPointer      DATA_REF(TASK*, 0x01AED318)
#define EnteringOdekake         DATA_REF(b32  , 0x01AED31C)

/** Crappy, half-baked, replacement case model by SOC **/
#define pSOCOdekakeModel        DATA_REF(void*, 0x1AED320)

/************************/
/*  Functions           */
/************************/
EXTERN_START
void    ALO_OdekakeMachineCreate(NJS_POINT3* pPos, Angle angy);

/** Task functions **/
void    ALO_OdekakeMachine(TASK* tp);
void    ALO_OdekakeMachineExecutor(TASK* tp);
void    ALO_OdekakeMachineDisplayerNeut(TASK* tp);
void    ALO_OdekakeMachineDestructor(TASK* tp);

EXTERN_END

/************************/
/*  Function Ptrs       */
/************************/
#ifdef  SAMT_INCL_FUNCPTRS
/** Function ptrs **/
#   define ALO_OdekakeMachine_p                     FUNC_PTR(void, __cdecl, (TASK*), 0x0057E460)
#   define ALO_OdekakeMachineExecutor_p             FUNC_PTR(void, __cdecl, (TASK*), 0x0057D540)
#   define ALO_OdekakeMachineDisplayerNeut_p        FUNC_PTR(void, __cdecl, (TASK*), 0x0057E060)
#   define ALO_OdekakeMachineDestructor_p           FUNC_PTR(void, __cdecl, (TASK*), 0x0057E040)

/** User-Function ptrs **/
#   define ALO_OdekakeMachineCreate_p               ((void*)0x0057E4F0)

#endif/*SAMT_INCL_FUNCPTRS*/

#endif/*_SA2B_CHAO_ODEKAKE_H_*/
