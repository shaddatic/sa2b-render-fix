#pragma once

#include <sa2b/src/Chao/al_behavior.h>

// CreateEggSucceed
// ALBHV_BornPon
// ALBHV_BornKyoro
// DecideNextType
// MayuExecutor
// MayuDisplayerSub
// MayuDestructor
// AL_CanISucceed
TaskFuncPtr(MayuDisplayer, 0x568A70);

void	CreateMayu(task* tp, char kind);

BhavFuncPtr(ALBHV_Mayu, 0x00568D30);
BhavFuncPtr(ALBHV_Dead, 0x00568F60);