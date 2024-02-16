/*
*   Sonic Adventure Mod Tools (SA2B) - '/src/chao/al_parameter.h'
*
*   Contains functions related to the Chao parameters.
*
*   Contributors:
*   -   SEGA - Sonic Team,
*   -   Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC.
*/
#ifndef _SA2B_CHAO_PARAMETER_H_
#define _SA2B_CHAO_PARAMETER_H_

/************************/
/*  Abstract Types      */
/************************/
typedef struct task     TASK;

/************************/
/*  Enums               */
/************************/
enum
{
    SKILL_SWIM,
    SKILL_FLY,
    SKILL_RUN,
    SKILL_POWER,
    SKILL_STAMINA,
    SKILL_GUTS,
    SKILL_INTELLECT,
    SKILL_EMPTY,
    NB_SKILL,
};

/************************/
/*  Functions           */
/************************/
EXTERN_START
/** Check alignment **/
bool32_t  AL_IsHero(uint8_t type);
bool32_t  AL_IsHero2(TASK* pChaoTask);
bool32_t  AL_IsDark(uint8_t type);
bool32_t  AL_IsDark2(TASK* pChaoTask);

/** Get Chao skill points adjusted by stage **/
uint32_t  AL_ParameterGetSkill(TASK* tp, uint16_t SkillKind);

/** Set param control timers to 0 **/
void    AL_ParameterControlInit(void);

EXTERN_END

#endif /* _SA2B_CHAO_PARAMETER_H_ */
