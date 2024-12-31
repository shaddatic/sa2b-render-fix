/*
*   Sonic Adventure Mod Tools (SA2B) - '/funchook.h'
*
*   Description:
*     Functions for non-destructively hooking game code and functions, allowing
*   hooks to be reversed and the original code to be called as normal.
*
*   Contributors:
*     - Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC
*/
#ifndef H_SAMT_FUNCHOOK
#define H_SAMT_FUNCHOOK

EXTERN_START

/************************/
/*  Structures          */
/************************/
/****** Hook Info *******************************************************************/
typedef struct hook_info
{
    int d[4];               /* opaque data                                          */
}
hook_info;

/************************/
/*  Prototypes          */
/************************/
/****** Hook Info *******************************************************************/
/*
*   Description:
*     Reverse a hook by restoring original code using a populated hook info.
*
*   Parameters:
*     - info    : hook info pointer
*/
void    HookInfoUnhook( const hook_info* info );
/*
*   Description:
*     Rehook a function using a populated hook info.
*
*   Parameters:
*     - info    : hook info pointer
*/
void    HookInfoRehook( const hook_info* info );
/*
*   Description:
*     Check if a hook is currently active and is the first function hook in the call
*   chain. If either of those cases aren't true, this function will return 'false'.
*
*   Parameters:
*     - info    : hook info pointer
*
*   Returns:
*     'true' if hook info matches code hook; or 'false' if not.
*/
bool    HookInfoCheck( const hook_info* info );
/*
*   Description:
*     Restore the original code and clear the hook info
*
*   Parameters:
*     - info    : hook info pointer
*/
void    HookInfoFree( hook_info* info );

/****** Function Hook ***************************************************************/
/*
*   Description:
*     Hook a function with optional hook info, allowing for the original
*   function be called normally by unhooking the code before calling.
*     Hook pointer should point to the top of the function. Calling methods and
*   function arguments must be handled by the user.
*     
*   Notes:
*     - If no hook info is given, operates the same as 'WriteJump'.
* 
*   Parameters:
*     - info    : hook info to populate                                  [optional]
*     - addr    : address of function to hook
*     - func    : function to call from hook
*/
void    FuncHookCreate( hook_info* info, void* addr, const void* func );

/****** Call Hook *******************************************************************/
/*
*   Description:
*     Hook a call instruction with optional hook info, allowing for the original
*   code be called normally by unhooking it before calling.
*     Hook pointer should point to a valid call instruction, or a clear space in
*   memory where a call instruction can be placed. Calling methods and function
*   arguments must be handled by the user.
*
*   Notes:
*     - If no hook info is given, operates the same as 'WriteCall'.
*
*   Parameters:
*     - info    : hook info to populate                                  [optional]
*     - addr    : address of call instruction to hook
*     - func    : function to call from hook
*/
void    CallHookCreate( hook_info* info, void* addr, const void* func );

/****** Trampoline Hook *************************************************************/
/*
*   # Trampoline
*
*       A 'Trampoline' is a special CallHook that automatically
*   jumps to the original call address after your inserted
*   function has been called.
*       It is your job to handle arguments & to ensure they're
*   still applicable to the original function, & therefore any
*   previous hooks.
*       If you leave arguments untouched, the first argument on
*   the left will be the return address. Take this into account
*   & use it if you wish.
*/
/** Hook with trampoline **/
void    TrampolineCreate( void* pDst, const void* pCall );

/************************/
/*  Macro               */
/************************/
/** Create hook **/
#define FuncHook(info, addr, func)           FuncHookCreate(info, (void*)(addr), (const void*)(func))
#define CallHook(info, addr, func)           CallHookCreate(info, (void*)(addr), (const void*)(func))

/** Call original hooked function **/
#define FuncHookCall(info, code)                HookInfoUnhook(info); \
                                                code; \
                                                HookInfoRehook(info)

/** Create trampoline **/
#define Trampoline(_pdst, _pcall)               TrampolineCreate((void*)(_pdst), (void*)(_pcall))

EXTERN_END

#endif/*H_SAMT_FUNCHOOK*/
