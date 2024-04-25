/*
*   Sonic Adventure Mod Tools (SA2B) - '/funchook.h'
*
*   Description:
*       Contains functions for non-destructively hooking into
*   game code so it can be reversed, allowing the original 
*   function (or any previous hook) to be called as normal.
*
*   Contributors:
*     - Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC
*/
#ifndef _SAMT_FUNCHOOK_H_
#define _SAMT_FUNCHOOK_H_

/************************/
/*  Abstract Types      */
/************************/
typedef struct _hook_info           hook_info;
typedef struct _trampoline_info     trampoline_info;

/************************/
/*  Functions           */
/************************/
EXTERN_START
/*
*   # Func Hook
* 
*       A hook that applies to whole functions. This can be
*   used to replace functions outright, or more commonly to
*   allow calling of the original function by restoring it
*   first.
*/
/** Hook & create a new 'hook_info' **/
hook_info*  
        FuncHookCreate( void* pDst, const void* pJump );

/** Restore original code for calling, &
    rehook code once call is complete **/
void    FuncHookRestore( const hook_info* pHookInfo );
void    FuncHookRehook(  const hook_info* pHookInfo );

/** Release hook and 'hook_info' **/
void    FuncHookFree( hook_info* pHookInfo );

/*
*   # Call Hook
* 
*       A hook that applies only to function call instructions.
*   This can be used to only replace certain instances of a
*   function, or to allow calling of the original function 
*   without the use of a FuncHook.
*/
/** Hook & create a new 'hook_info' **/
hook_info*  
        CallHookCreate( void* pDst, const void* pCall );

/** Restore original code & rehook **/
void    CallHookRestore( const hook_info* pHookInfo );
void    CallHookRehook(  const hook_info* pHookInfo );

/** Release hook and 'hook_info' **/
void    CallHookFree( hook_info* pHookInfo );

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

EXTERN_END

/************************/
/*  Macro               */
/************************/
/** Create hook **/
#define FuncHook(_pdst, _pjump)                 FuncHookCreate((void*)(_pdst), (void*)(_pjump))
#define CallHook(_pdst, _pcall)                 CallHookCreate((void*)(_pdst), (void*)(_pcall))

/** Call original hooked function **/
#define FuncHookCall(_hook_info, _hook_call)    FuncHookRestore(_hook_info); \
                                                _hook_call; \
                                                FuncHookRehook(_hook_info)

/** Create trampoline **/
#define Trampoline(_pdst, _pcall)               TrampolineCreate((void*)(_pdst), (void*)(_pcall))

#endif/*_SAMT_FUNCHOOK_H_*/
