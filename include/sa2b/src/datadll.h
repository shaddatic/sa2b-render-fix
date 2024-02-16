/*
*   Sonic Adventure Mod Tools (SA2B) - '/src/datadll.h'
*
*   Description:
*       Contains a function and macro for interfacing with
*   Data.dll.
*
*   Contributors:
*   -   SEGA - Sonic Team,
*   -   Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC.
*/
#ifndef _SA2B_DATADLL_H_
#define _SA2B_DATADLL_H_

/************************/
/*  Functions           */
/************************/
EXTERN_START
/** Get process address from the Data_DLL.dll HMODULE **/
void*   GetDataDllProcAddr( const char* lpProcName );

EXTERN_END

/************************/
/*  Macro               */
/************************/
#define GetDataDllAddr(type, name)  ((type*)GetDataDllProcAddr(name))

/************************/
/*  Function Ptrs       */
/************************/
#ifdef SAMT_INCLUDE_FUNC_PTRS
/** Function ptrs **/
#   define GetDataDllProcAddr_p        FuncPtr(void*, __cdecl, (const char*), 0x0077DEF0)

#endif/*SAMT_INCLUDE_FUNC_PTRS*/

#endif/*_SA2B_DATADLL_H_*/
