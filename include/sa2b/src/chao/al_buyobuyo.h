/*
*   Sonic Adventure Mod Tools (SA2B) - '/src/chao/al_buyobuyo.h'
*
*   Contains functions and data related to the Chao jiggle engine.
*
*   Contributors:
*   -   SEGA - Sonic Team,
*   -   Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC.
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
typedef struct task         TASK;
typedef struct al_object    AL_OBJECT;

/************************/
/*  Structures          */
/************************/
typedef struct 
{
    void*    mdata;
    float32_t CurrFrame;
    uint32_t    nbFrame;
    void*    mdataLink;
    float32_t CurrFrameLink;
    uint32_t    nbFrameLink;
    float32_t LinkRatio;
}
AL_MOTION_INFO;

/************************/
/*  Data                */
/************************/
#define tree_counter    DataRef(int16_t        , 0x01AED2D4)
#define MtnInfo         DataRef(AL_MOTION_INFO, 0x01A276A8)

#define VertexVelo      DataAry(NJS_VECTOR    , 0x01DBD960, [256])

/************************/
/*  Functions           */
/************************/
EXTERN_START
void    AL_InitCalcMotionMatrix(TASK* tp);
void    AL_CalcMotionMatrixTranslate(AL_OBJECT* pObject);
void    AL_CalcMotionMatrixRotation(AL_OBJECT* pObject);
void    AL_CalcMotionMartix(AL_OBJECT* pObject); /* Not a typo */
void    AL_SetCurrMatrixSub(AL_OBJECT* pObject);
void    AL_SetCurrMatrix(TASK* tp);
void    AL_CalcShadowPos(TASK* tp);
void    AL_BuyoBuyoObject(TASK* tp, AL_OBJECT* pObject);
void    AL_BuyoBuyoControl(TASK* tp);

EXTERN_END

/************************/
/*  Function Ptrs       */
/************************/
#ifdef SAMT_INCLUDE_FUNC_PTRS
/** Function ptrs **/
#define AL_SetCurrMatrixSub_p       FuncPtr(void, __cdecl, (AL_OBJECT*)       , 0x0056F010)
#define AL_BuyoBuyoObject_p         FuncPtr(void, __cdecl, (TASK*, AL_OBJECT*), 0x0056F5C0)
#define AL_BuyoBuyoControl_p        FuncPtr(void, __cdecl, (TASK*)            , 0x0056FC20)

/** User-Function ptrs **/
EXTERN const void* const AL_InitCalcMotionMatrix_p;
EXTERN const void* const AL_CalcMotionMartix_p;
EXTERN const void* const AL_CalcMotionMartixTranslate_p;
EXTERN const void* const AL_CalcMotionMartixRotation_p;
EXTERN const void* const AL_SetCurrMatrix_p;
EXTERN const void* const AL_CalcShadowPos_p;

#endif /* SAMT_INCLUDE_FUNC_PTRS */

#endif /* _SA2B_CHAO_BUYOBUYO_H_ */
