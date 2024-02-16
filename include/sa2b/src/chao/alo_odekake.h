/*
*   Sonic Adventure Mod Tools (SA2B) - '/src/chao/alo_odekake.h'
*
*   Contains enums and functions related to Odekake machine.
*
*   Contributors:
*   -   SEGA - Sonic Team,
*   -   Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC.
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
    float32_t CoverFrame;
    float32_t ButtonPos;
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
#define OdekakeTaskPointer      DataRef(TASK*, 0x01AED318)
#define EnteringOdekake         DataRef(bool32_t, 0x01AED31C)

/** Crappy, half-baked, replacement case model by SOC **/
#define pSOCOdekakeModel        DataRef(void*, 0x1AED320)

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
#ifdef SAMT_INCLUDE_FUNC_PTRS
/** Function ptrs **/
#define ALO_OdekakeMachine_p                    FuncPtr(void, __cdecl, (TASK*), 0x0057E460)
#define ALO_OdekakeMachineExecutor_p            FuncPtr(void, __cdecl, (TASK*), 0x0057D540)
#define ALO_OdekakeMachineDisplayerNeut_p       FuncPtr(void, __cdecl, (TASK*), 0x0057E060)
#define ALO_OdekakeMachineDestructor_p          FuncPtr(void, __cdecl, (TASK*), 0x0057E040)

/** User-Function ptrs **/
EXTERN const void* const ALO_OdekakeMachineCreate_p;

#endif /* SAMT_INCLUDE_FUNC_PTRS */

#endif /* _SA2B_CHAO_ODEKAKE_H_ */
