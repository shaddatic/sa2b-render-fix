#pragma once

/*
*	Abstracted Structs
*/

typedef struct task		TASK;
typedef struct taskwk	TASKWK;

/*
*	Includes
*/

#include <sa2b/ninja/ninja.h>

/*
*	Task Function Pointers
*/

TaskFuncPtr(ALO_HorseExecutor, 0x00580BC0);

/*
*	User Functions
*/

TASKWK*		ALO_HorseCreateTask(NJS_POINT3* pPos);

/*
*	User Function Pointers
*/

#ifdef SAMT_INCLUDE_USER_PTRS

extern const void* ALO_HorseCreateTask_p;

#endif