/*
*   SAMT for Sonic Adventure 2 (PC, 2012) - '/sonic/chao/alo_odekake.h'
*
*   Description:
*       Contains enums and functions related to Odekake machine.
*/
#ifndef _SA2B_CHAO_ODEKAKE_H_
#define _SA2B_CHAO_ODEKAKE_H_

/************************/
/*  Includes            */
/************************/
#include <samt/ninja/ninja.h>

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
    i32     ButtonState;
    i32     CoverMode;
    f32     CoverFrame;
    f32     ButtonPos;
    task*   pChaotask;
    i32     FileFlag;
    i32     BuyoFlag;
    Angle   BuyoPhase;
    i32     MonitorMode;
    i32     MonitorCount;
    i32     MonitorTimer;
    i32     ring;
}
ODEKAKE_WORK;

enum 
{
    MD_ODEKAKE_INIT = 0x0,
    MD_ODEKAKE_INIT_WAIT = 0x1,
    MD_ODEKAKE_CHECK_GBA = 0x2,
    MD_ODEKAKE_NORMAL = 0x3,
    MD_ODEKAKE_JOY_COPY_CONFIRM_00 = 0x4,
    MD_ODEKAKE_JOY_COPY_CONFIRM_005 = 0x5,
    MD_ODEKAKE_JOY_COPY_CONFIRM_01 = 0x6,
    MD_ODEKAKE_JOY_COPY_CONFIRM_02 = 0x7,
    MD_ODEKAKE_ODE_COPY_CONFIRM_00 = 0x8,
    MD_ODEKAKE_ODE_COPY_CONFIRM_005 = 0x9,
    MD_ODEKAKE_ODE_COPY_CONFIRM_01 = 0xA,
    MD_ODEKAKE_ODE_COPY_CONFIRM_02 = 0xB,
    MD_ODEKAKE_ODEKAKE_START = 0xC,
    MD_ODEKAKE_ODEKAKE_WAIT = 0xD,
    MD_ODEKAKE_ODEKAKE_FILESAVE_START = 0xE,
    MD_ODEKAKE_ODEKAKE_FILESAVE_WAIT = 0xF,
    MD_ODEKAKE_JOYBOOT_START = 0x10,
    MD_ODEKAKE_JOYBOOT_WAIT = 0x11,
    MD_ODEKAKE_JOYBOOT_FILESAVE_START = 0x12,
    MD_ODEKAKE_JOYBOOT_FILESAVE_WAIT = 0x13,
    MD_ODEKAKE_WARNING = 0x14,
    MD_ODEKAKE_DECIDE = 0x15,
    MD_ODEKAKE_END_WAIT = 0x16,
    MD_ODEKAKE_END_WAIT2 = 0x17,
    MD_ODEKAKE_END = 0x18,
    MD_ODEKAKE_WHITE_OUT = 0x19,
};

/************************/
/*  Data                */
/************************/
#define OdekakeMachineTask      DATA_REF(task*, 0x01AED318)

#define OdekakeInitPosFlag      DATA_REF(b32  , 0x01AED314)
#define OdekakeMenuFlag         DATA_REF(b32  , 0x01AED31C)
#define GetChaoFlag             DATA_REF(b32  , 0x01AED310)

/** Crappy, half-baked, replacement case model by SOC **/
#define pSOCOdekakeModel        DATA_REF(void*, 0x1AED320)

/************************/
/*  Functions           */
/************************/
EXTERN_START
void    ALO_OdekakeMachineCreate(const NJS_POINT3* pPos, Angle angy);

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
#   define ALO_OdekakeMachineCreate_p               0x0057E4F0

#endif/*SAMT_INCL_FUNCPTRS*/

#endif/*_SA2B_CHAO_ODEKAKE_H_*/
