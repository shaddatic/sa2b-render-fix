/*
*   Sonic Adventure Mod Tools (SA2B) - '/util/ml_macro.h'
*
*   Description:
*       SAMT utility header defining Mod-Loader macros for
*   compatibility with legacy code-bases.
*
*   Contributors:
*   -   Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC.
*/
#ifndef _UTIL_MLMACRO_H_
#define _UTIL_MLMACRO_H_

/************************/
/*  Macro               */
/************************/
#ifdef  __cplusplus

/** Data declarations **/
#   define DataPointer(type, name, address)                            static auto& name = DataRef(type, address)
#   define DataArray(type, name, address, len)                         static auto& name = DataAry(type, address, [len])

/** Function declarations **/
#   define FunctionPointer(return_type, name, args, address)           static auto* name = FuncPtr(return_type, __cdecl   , args  , address)
#   define StdcallFunctionPointer(return_type, name, args, address)    static auto* name = FuncPtr(return_type, __stdcall , args  , address)
#   define FastcallFunctionPointer(return_type, name, args, address)   static auto* name = FuncPtr(return_type, __fastcall, args  , address)
#   define ThiscallFunctionPointer(return_type, name, args, address)   static auto* name = FuncPtr(return_type, __thiscall, args  , address)
#   define VoidFunc(name, address)                                     static auto* name = FuncPtr(void       , __cdecl   , (void), address)

#endif/*__cplusplus*/

#endif/*_UTIL_MLMACRO_H_*/
