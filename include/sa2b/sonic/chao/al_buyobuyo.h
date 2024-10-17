/*
*   Sonic Adventure Mod Tools (SA2B) - '/sonic/chao/al_buyobuyo.h'
*
*   Description:
*       Contains functions and data related to the Chao jiggle
*   engine.
*
*   Contributors:
*     - SEGA - Sonic Team,
*     - Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC
*/
#ifndef _SA2B_CHAO_BUYOBUYO_H_
#define _SA2B_CHAO_BUYOBUYO_H_

/************************/
/*  Includes            */
/************************/
#include <sa2b/ninja/njcommon.h>

/************************/
/*  Abstract Types      */
/************************/
typedef struct task         task;
typedef struct al_object    AL_OBJECT;

/************************/
/*  Structures          */
/************************/
typedef struct 
{
    void*     mdata;
    f32       CurrFrame;
    uint32_t  nbFrame;
    void*     mdataLink;
    f32       CurrFrameLink;
    uint32_t  nbFrameLink;
    f32       LinkRatio;
}
AL_MOTION_INFO;

/************************/
/*  Data                */
/************************/
#define tree_counter    DATA_REF(int16_t       , 0x01AED2D4)
#define MtnInfo         DATA_REF(AL_MOTION_INFO, 0x01A276A8)

#define VertexVelo      DATA_ARY(NJS_VECTOR    , 0x01DBD960, [256])

/************************/
/*  Functions           */
/************************/
EXTERN_START
void    AL_InitCalcMotionMatrix(task* tp);
void    AL_CalcMotionMatrixTranslate(AL_OBJECT* pObject);
void    AL_CalcMotionMatrixRotation(AL_OBJECT* pObject);
void    AL_CalcMotionMartix(AL_OBJECT* pObject); /* Not a typo */
void    AL_SetCurrMatrixSub(AL_OBJECT* pObject);
void    AL_SetCurrMatrix(task* tp);
void    AL_CalcShadowPos(task* tp);
void    AL_BuyoBuyoObject(task* tp, AL_OBJECT* pObject);
void    AL_BuyoBuyoControl(task* tp);

EXTERN_END

/************************/
/*  Function Ptrs       */
/************************/
#ifdef  SAMT_INCL_FUNCPTRS
/** Function ptrs **/
#   define AL_SetCurrMatrixSub_p            FUNC_PTR(void, __cdecl, (AL_OBJECT*)       , 0x0056F010)
#   define AL_BuyoBuyoObject_p              FUNC_PTR(void, __cdecl, (task*, AL_OBJECT*), 0x0056F5C0)
#   define AL_BuyoBuyoControl_p             FUNC_PTR(void, __cdecl, (task*)            , 0x0056FC20)

/** User-Function ptrs **/
#   define AL_InitCalcMotionMatrix_p        ((void*)0x0056E9C0);
#   define AL_CalcMotionMartix_p            ((void*)0x0056EF80);
#   define AL_CalcMotionMatrixTranslate_p   ((void*)0x0056EA30);
#   define AL_CalcMotionMatrixRotation_p    ((void*)0x0056ED40);
#   define AL_SetCurrMatrix_p               ((void*)0x0056F0E0);
#   define AL_CalcShadowPos_p               ((void*)0x0056F180);

#endif/*SAMT_INCL_FUNCPTRS*/

#endif/*_SA2B_CHAO_BUYOBUYO_H_*/
