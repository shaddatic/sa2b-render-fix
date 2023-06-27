#pragma once

typedef struct task task;

bool32	AL_IsHero(uint8 type);
bool32	AL_IsHero2(task* pChaoTask);
bool32	AL_IsDark(uint8 type);
bool32	AL_IsDark2(task* pChaoTask);

void	AL_ParameterControlInit();

uint32	AL_ParameterGetSkill(task* tp, uint16 SkillKind);