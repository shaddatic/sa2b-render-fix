/*
*   Sonic Adventure Mod Tools (SA2B) - '/src/memalloc.h'
*
*   Contains pointers to the game's stdlib memory functions
*
*   Contributors:
*   -   Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC.
*/
#pragma once

/************************/
/*  Function Pointers   */
/************************/
FuncPtr(void*, __cdecl, _new, (size_t Size), 0x007A5DA1);
FuncPtr(void, __cdecl, _delete, (void* _Block), 0x007A5974);

FuncPtr(void*, __cdecl, _malloc, (size_t Size), 0x007A84A5);
FuncPtr(void, __cdecl, _free, (void* _Block), 0x07A80DD);
