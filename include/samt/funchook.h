/*
*   SAMT for Sonic Adventure 2 (PC, 2012) - '/funchook.h'
*
*   Description:
*     Functions for non-destructively hooking game code and functions, allowing
*   hooks to be reversed and the original code to be called as normal.
*/
#ifndef H_SAMT_FUNCHOOK
#define H_SAMT_FUNCHOOK

EXTERN_START

/********************************/
/*  Enums                       */
/********************************/
/****** Hook Info *******************************************************************************/
typedef enum mt_hooktype
{
    HOOK_TYPE_NONE,                 /* hook info not initialized                                */

    HOOK_TYPE_FUNC,                 /* is a function hook                                       */
    HOOK_TYPE_CALL,                 /* is a call hook                                           */
}
mt_hooktype;

/********************************/
/*  Structures                  */
/********************************/
/****** Hook Info *******************************************************************************/
typedef struct mt_hookinfo
{
    u32 d[5];                       /* opaque data                                              */
}
mt_hookinfo;

/********************************/
/*  Prototypes                  */
/********************************/
/****** Hook Info *******************************************************************************/
/*
*   Description:
*     Enable and disable a hook.
*
*   Parameters:
*     - pHookInfo   : hook info
*     - state       : hook state to set                                                [ON/OFF]
*/
void    mtHookInfoSwitch( const mt_hookinfo* pHookInfo, s32 state );
/*
*   Description:
*     Get hook info type.
*
*   Parameters:
*     - pHookInfo   : hook info
*
*   Returns:
*     Type of hook used in the hook info.
*/
mt_hooktype mtHookInfoGetType( const mt_hookinfo* pHookInfo );
/*
*   Description:
*     Check if a hook info will be called next when the original function is called. This says
*   nothing about if your hook *can* be called, only about it being called first/next in the
*   hook chain.
*
*   Parameters:
*     - pHookInfo   : hook info
*
*   Returns:
*     'true' if hook is enabled and first/next; or 'false' if not.
*/
bool    mtHookInfoIsNext( const mt_hookinfo* pHookInfo );
/*
*   Description:
*     Disable the hook and clear the hook info for reuse.
*
*   Parameters:
*     - pHookInfo   : hook info
*/
void    mtHookInfoClear( mt_hookinfo* pHookInfo );

/****** Create Hook *****************************************************************************/
/*
*   Description:
*     Hook into a game function, allowing your own functions to be ran instead of the original
*   code. Paired with an optional hook info, you can disable your hook on the fly and call the
*   original function alongside your own code.
*
*   Examples:
*     - mtHookFunction( &hinfo, (void*)0x00456780, MyFunction );
*
*   Notes:
*     - Address should point to the top of the hooked function to operate correctly.
*     - Calling methods and function arguments must be handled by the user.
*     - If no hook info is given, operates the same as 'WriteJump'.
* 
*   Parameters:
*     - pHookInfo   : hook info                                                  [opt: nullptr]
*     - pHookAddr   : address of function to hook
*     - pFunc       : user function to call from hook
*/
void    mtHookFunction( mt_hookinfo* RESTRICT pHookInfo, void* RESTRICT pHookAddr, const void* RESTRICT pFunc );
/*
*   Description:
*     Hook a game function call, allowing your own functions to be ran instead of the original
*   path. Paired with an optional hook info, you can disable your hook on the fly and allow the
*   original call path to run normally.
*
*   Examples:
*     - mtHookFuncCall( &hinfo, (void*)0x00456780, MyFunction );
*
*   Notes:
*     - Address should point to a call instruction, or a clear space in memory where a call can
*       be placed, to operate correctly.
*     - Calling methods and function arguments must be handled by the user.
*     - If no hook info is given, operates the same as 'WriteCall'.
*
*   Parameters:
*     - pHookInfo   : hook info                                                  [opt: nullptr]
*     - pHookAddr   : address of call instruction to hook
*     - pFunc       : user function to call from hook
*/
void    mtHookFuncCall( mt_hookinfo* RESTRICT pHookInfo, void* RESTRICT pHookAddr, const void* RESTRICT pFunc );

/********************************/
/*  Macro                       */
/********************************/
/****** Create Hook *****************************************************************************/
/*
*   Description:
*     Helper macros for creating a function or function call hook.
*
*   Parameters:
*     - hinfo       : hook info                                                  [opt: nullptr]
*     - haddr       : address to hook
*     - pFunc       : user function to call from hook
*/
#define mtHookFunc(hinfo, haddr, func)      mtHookFunction((hinfo), (void*)(haddr), (const void*)(func))
#define mtHookCall(hinfo, haddr, func)      mtHookFuncCall((hinfo), (void*)(haddr), (const void*)(func))

/****** Call Original ***************************************************************************/
/*
*   Description:
*     Helper macro for calling a function that has been hooked by temporarily disabling the
*   hook, allowing for a call instruction, then immedietly re-enabling the hook right after.
*
*   Examples:
*     - mtHookInfoCall( FuncHookInfo, var = Func(1, 2, 3) );
*
*   Parameters:
*     - hinfo       : hook info
*     - call        : function call, including arguments and return value
*/
#define mtHookInfoCall(hinfo, call)         mtHookInfoSwitch(hinfo, OFF); \
                                            call;                         \
                                            mtHookInfoSwitch(hinfo,  ON)

/************************************************************************************************/
/*
*   Depricated Macros
*/
/****** Create Hook *****************************************************************************/
#define FuncHook(info, pHookAddr, pFunc)              mtHookFunction(info, (void*)(pHookAddr), (const void*)(pFunc))
#define CallHook(info, pHookAddr, pFunc)              mtHookFuncCall(info, (void*)(pHookAddr), (const void*)(pFunc))

/****** Call Original ***************************************************************************/
#define FuncHookCall(info, code)                mtHookInfoSwitch(info, OFF); \
                                                code; \
                                                mtHookInfoSwitch(info,  ON)

EXTERN_END

#endif/*H_SAMT_FUNCHOOK*/
