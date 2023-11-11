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
    uint8 mLev;
    uint8 mExpNum;
    uint16 mSkill;
    sint32 mLevelUpCount;
    sint32 mLevelUpLocation;
    sint16 mSkillDiff;
}
SEachWork;

#define GET_PARAMFUKIDASI_WORK(tp) ((SParamFukidasiWork*)tp->awp)

typedef struct // ANYWK
{
    sint8 mode;
    sint8 smode;
    sint32 timer;
    sint32 timer2;
    sint8 countV;
    uint8 flag;
    float32 posX;
    float32 posY;
    float32 aimX;
    float32 aimY;
    float32 alpha;
    float32 size;
    sint32 phase;
    sint32 phase2;
    sint32 location;
    sint32 loc_timer;
    TASK* pChaoTask;
    CHAO_PARAM_GC* pParamGC;
    sint32 mExpUpdating;
    sint32 mExpUpdateWait;
    sint32 mLevelUpJingle;
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
EXTERN const void* AL_OpenParameterFukidasi_p;

#endif /* SAMT_INCLUDE_FUNC_PTRS */

#endif /* _SA2B_CHAO_PARAMFUKIDASI_H_ */