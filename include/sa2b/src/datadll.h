/*
*   Sonic Adventure Mod Tools (SA2B) - '/src/datadll.h'
*
*   Contains a function and macro for interfacing with Data.dll
*
*   Contributors:
*   -   SEGA - Sonic Team,
*   -   Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC.
*/
#pragma once

FuncPtr(void*, __cdecl, __GetDataDllAddr, (const char* lpProcName), 0x0077DEF0);

#define GetDataDllAddr(type, name) ((type*)__GetDataDllAddr(name))
