#pragma once

/*
*	Abstracted Structs
*/

typedef struct task	TASK;

/*
*	Includes
*/

#include <sa2b/ninja/ninja.h>

/*
*	Data References
*/

DataRef(task*, ManagerTp, 0x01A5D144);

/*
*	Function Pointers
*/

FuncPtr(void, __cdecl, AL_CreateShadowTex, (), 0x00540F70);
FuncPtr(NJS_CNK_OBJECT*, __cdecl, AL_AllocateShadowTex, (), 0x00541020); // Be careful of this one...

/*
*	Task Function Pointers
*/

TaskFuncPtr(AL_ExecShadowTex, 0x005412E0);
TaskFuncPtr(AL_DisplayShadowTex, 0x00541370);
TaskFuncPtr(AL_DestructShadowTex, 0x00541250);

/*
*	User Functions
*/

void AL_EntryShadowTex(NJS_POINT3* pos, float scl);

/*
*	User Function Pointers
*/

#ifdef SAMT_INCLUDE_USER_PTRS

extern const void* AL_EntryShadowTex_p;

#endif