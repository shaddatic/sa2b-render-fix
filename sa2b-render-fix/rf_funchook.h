/*
*   SA2 Render Fix - '/rf_funchook.h'
*
*   Description:
*       Headers and macros for quickly making function hooks
*   within Render Fix. The hook and hook info must be correctly
*   postfixed, eg. FuncName##Hook & FuncName##HookInfo, for the
*   macro to function.
*
*   Contributors:
*   -   Shaddatic
*/
#ifndef _RF_FUNCHOOK_H_
#define _RF_FUNCHOOK_H_

/************************/
/*  Includes            */
/************************/
/** SAMT **/
#include <sa2b/funchook.h>

/************************/
/*  Macros              */
/************************/
/** Regular function hook macro **/
#define RF_FuncHook(func_name)          func_name##HookInfo = FuncHookCreate(func_name    , func_name##Hook)

/** Function hook macro for usercalls, eg. '_p' postfix **/
#define RF_FuncHookUsr(func_name)       func_name##HookInfo = FuncHookCreate(func_name##_p, func_name##Hook)

#endif/*_RF_FUNCHOOK_H_*/
