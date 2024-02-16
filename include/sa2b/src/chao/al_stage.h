/*
*   Sonic Adventure Mod Tools (SA2B) - '/src/chao/al_stage.h'
*
*   Contains enums, data, and functions related to Chao stages.
*
*   Contributors:
*   -   SEGA - Sonic Team,
*   -   Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC.
*/
#ifndef _SA2B_CHAO_STAGE_H_
#define _SA2B_CHAO_STAGE_H_

/************************/
/*  Enums               */
/************************/
typedef enum 
{    
    CHAO_STG_NONE,
    CHAO_STG_NEUT,
    CHAO_STG_HERO,
    CHAO_STG_DARK,
    CHAO_STG_RACE,
    CHAO_STG_ENTRANCE1P,
    CHAO_STG_KINDER,
    CHAO_STG_LOBBY,
    CHAO_STG_ENTRANCE2P,
    CHAO_STG_STADIUM,
    CHAO_STG_KARATE1P,
    CHAO_STG_KARATE2P,
    CHAO_STG_ODEKAKE,
}
eCHAO_STAGE_NUMBER;

/************************/
/*  Data                */
/************************/
#define ChaoOldStageNumber      DataRef(eCHAO_STAGE_NUMBER, 0x13402AC)
#define ChaoStageNumber         DataRef(eCHAO_STAGE_NUMBER, 0x134046C)
#define ChaoNextStageNumber     DataRef(eCHAO_STAGE_NUMBER, 0x134062C)

/************************/
/*  Functions           */
/************************/
EXTERN_START
void    AL_ChangeStage(eCHAO_STAGE_NUMBER NextStage);

eCHAO_STAGE_NUMBER  AL_GetLastStageNumber(void);
eCHAO_STAGE_NUMBER  AL_GetStageNumber(void);
eCHAO_STAGE_NUMBER  AL_GetNextStageNumber(void);

int32_t  AL_GetLocalChaoCount(int32_t stage);
int32_t  AL_GetCurrGardenChaoCount(void);

EXTERN_END

/************************/
/*  Macros              */
/************************/
#define AL_IsGarden()       (AL_GetStageNumber() >= CHAO_STG_NEUT && AL_GetStageNumber() <= CHAO_STG_DARK)
#define AL_IsLoaded()       (AL_GetStageNumber() == AL_GetNextStageNumber())

#define AL_IsGarden2(stg)   (stg >= CHAO_STG_NEUT && stg <= CHAO_STG_DARK)

/************************/
/*  Function Ptrs       */
/************************/
#ifdef SAMT_INCLUDE_FUNC_PTRS
/** Function ptrs **/
#define AL_ChangeStage_p        FuncPtr(void, __cdecl, (eCHAO_STAGE_NUMBER), 0x0052B5B0)

#endif /* SAMT_INCLUDE_FUNC_PTRS */

#endif /* _SA2B_CHAO_STAGE_H_ */
