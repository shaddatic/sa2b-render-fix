/*
*   Sonic Adventure Mod Tools (SA2B) - '/src/object/o_messenger.h'
*
*   Contains functions for Omochao
*
*   Contributors:
*   -   SEGA - Sonic Team,
*   -   Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC.
*/
#pragma once

/************************/
/*  Task Functions      */
/************************/
TaskFuncPtr(ObjectMessengerCreate, 0x6C0780);
TaskFuncPtr(ObjectMessengerExec, 0x006BE2E0);
TaskFuncPtr(ObjectMessengerDestructor, 0x006C0970);

/************************/
/*  Function Pointers   */
/************************/
FuncPtr(int, __cdecl, FreeMessengerFile, (), 0x006BD5D0);

/************************/
/*  User Functions      */
/************************/
sint32	LoadMessengerFile(const char* f);

/************************/
/*  User Function Ptrs  */
/************************/
#ifdef SAMT_INCLUDE_USER_PTRS

extern const void* LoadMessengerFile_p;

#endif