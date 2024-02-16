/*
*   Sonic Adventure Mod Tools (SA2B) - '/src/chao/al_parameter_fukidasi.h'
*
*   Contains structures, data, and functions related to the Chao stat panel.
*   Fukidasi means "speech bubble".
*
*   Contributors:
*   -   SEGA - Sonic Team,
*   -   Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC.
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
    float32_t posX;
    float32_t posY;
    float32_t aimX;
    float32_t aimY;
    float32_t alpha;
    float32_t size;
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
#define pChaoParamFukidasiTask      DataRef(TASK*, 0x01AED28C)

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
#ifdef SAMT_INCLUDE_FUNC_PTRS
/** Function ptrs **/
#define AL_CloseParameterFukidasi_p     FuncPtr(void, __fastcall, (TASK*), 0x00565B90)
#define ParamFukidasiExecutor_p         FuncPtr(void, __cdecl   , (TASK*), 0x00564C80)
#define ParamFukidasiDisplayer_p        FuncPtr(void, __cdecl   , (TASK*), 0x00565200)
#define ParamFukidasiDestructor_p       FuncPtr(void, __cdecl   , (TASK*), 0x005659C0)

/** User-Function ptrs **/
EXTERN const void* const AL_OpenParameterFukidasi_p;

#endif /* SAMT_INCLUDE_FUNC_PTRS */

#endif /* _SA2B_CHAO_PARAMFUKIDASI_H_ */
