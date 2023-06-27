#pragma once

/*
*	Abstracted Structs
*/

typedef struct task TASK;

/*
*	Task Functions
*/

TaskFuncPtr(ObjectMessengerCreate, 0x6C0780);
TaskFuncPtr(ObjectMessengerExec, 0x006BE2E0);
TaskFuncPtr(ObjectMessengerDestructor, 0x006C0970);

/*
*	Function Pointers
*/

FuncPtr(int, __cdecl, UnloadMsgFile_Omochao, (), 0x006BD5D0);

/*
*	User Functions
*/

sint32	LoadMsgFile_Omochao(const char* a1);

/*
*	User Function Pointers
*/

#ifdef SAMT_INCLUDE_USER_PTRS

extern const void* LoadMsgFile_Omochao_p;

#endif