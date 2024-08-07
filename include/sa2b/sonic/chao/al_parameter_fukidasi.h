/*
*   Sonic Adventure Mod Tools (SA2B) - '/sonic/chao/al_parameter_fukidasi.h'
*
*   Description:
*       Contains structures, data, and functions related to the
*   Chao stat panel. Fukidasi means "speech bubble".
*
*   Contributors:
*     - SEGA - Sonic Team,
*     - Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC
*/
#ifndef _SA2B_CHAO_PARAMFUKIDASI_H_
#define _SA2B_CHAO_PARAMFUKIDASI_H_

/************************/
/*  Abstract Types      */
/************************/
typedef struct task             TASK;
typedef struct chao_param_gc    CHAO_PARAM_GC;

/************************/
/*  Structures          */
/************************/
typedef struct
{
    uint8_t mLev;
    uint8_t mExpNum;
    uint16_t mSkill;
    int32_t mLevelUpCount;
    int32_t mLevelUpLocation;
    int16_t mSkillDiff;
}
SEachWork;

#define GET_PARAMFUKIDASI_WORK(tp) ((SParamFukidasiWork*)tp->awp)

typedef struct // ANYWK
{
    int8_t mode;
    int8_t smode;
    int32_t timer;
    int32_t timer2;
    int8_t countV;
    uint8_t flag;
    f32       posX;
    f32       posY;
    f32       aimX;
    f32       aimY;
    f32       alpha;
    f32       size;
    int32_t phase;
    int32_t phase2;
    int32_t location;
    int32_t loc_timer;
    TASK* pChaoTask;
    CHAO_PARAM_GC* pParamGC;
    int32_t mExpUpdating;
    int32_t mExpUpdateWait;
    int32_t mLevelUpJingle;
    SEachWork mEach[5];
}
SParamFukidasiWork;

/************************/
/*  Data                */
/************************/
#define pChaoParamFukidasiTask      DATA_REF(TASK*, 0x01AED28C)

/************************/
/*  Functions           */
/************************/
EXTERN_START
/** Open parameter window with linked Chao **/
void    AL_OpenParameterFukidasi(TASK* pChaoTask);
/** Close parameter window if 'pChaoTask' matches or is NULL **/
void    AL_CloseParameterFukidasi(TASK* pChaoTask);

/** Task functions **/
void    ParamFukidasiExecutor(TASK* tp);
void    ParamFukidasiDisplayer(TASK* tp);
void    ParamFukidasiDestructor(TASK* tp);

EXTERN_END

/************************/
/*  Function Ptrs       */
/************************/
#ifdef SAMT_INCL_FUNCPTRS
/** Function ptrs **/
#   define AL_CloseParameterFukidasi_p      FUNC_PTR(void, __fastcall, (TASK*), 0x00565B90)
#   define ParamFukidasiExecutor_p          FUNC_PTR(void, __cdecl   , (TASK*), 0x00564C80)
#   define ParamFukidasiDisplayer_p         FUNC_PTR(void, __cdecl   , (TASK*), 0x00565200)
#   define ParamFukidasiDestructor_p        FUNC_PTR(void, __cdecl   , (TASK*), 0x005659C0)

/** User-Function ptrs **/
#   define AL_OpenParameterFukidasi_p       ((void*)0x005659E0)

#endif/*SAMT_INCL_FUNCPTRS*/

#endif/*_SA2B_CHAO_PARAMFUKIDASI_H_*/
