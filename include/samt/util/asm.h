/*
*   SAMT for Sonic Adventure 2 (PC, 2012) - '/util/asm.h'
*
*   Description:
*     Macros for assembly programming, usually for __usercall and __userpurge functions.
*
*   Notes:
*     - EAX, ECX, & EDX are the only caller-saved registers, you must handle the other registers.
*     - For MSVC only, unreferenced parameter warnings are turned off.
*/
#ifndef H_UTIL_ASMUTIL
#define H_UTIL_ASMUTIL

EXTERN_START

/********************************/
/*  Macros                      */
/********************************/
/****** Macro Helper ****************************************************************************/
#define ASM__GETVAL(_v)             #_v

#if defined(MT_C_CLANG) || defined(MT_C_GCC) /* clang or gnuc                                   */

/****** Func Tag ********************************************************************************/
#define ASM_FUNC                    __attribute__((naked))

/****** Move ************************************************************************************/
#define ASM_MOVE(_r, _v)            __asm volatile ("mov "   #_r ", " ASM__GETVAL(_v))
#define ASM_MOVZX(_r, _v)           __asm volatile ("movzx " #_r ", " ASM__GETVAL(_v))
#define ASM_MOVSX(_r, _v)           __asm volatile ("movsx " #_r ", " ASM__GETVAL(_v))

/****** Math ************************************************************************************/
#define ASM_ADD(_t, _v)             __asm volatile ("add " #_t ", " ASM__GETVAL(_v))
#define ASM_SUB(_t, _v)             __asm volatile ("sub " #_t ", " ASM__GETVAL(_v))
#define ASM_MUL(_t, _v)             __asm volatile ("mul " #_t ", " ASM__GETVAL(_v))

/****** Push/Pop ********************************************************************************/
#define ASM_PUSH(_v)                __asm volatile ("push " ASM__GETVAL(_v))
#define ASM_POP(_t)                 __asm volatile ("pop "  ASM__GETVAL(_t))

/****** Stack Ptr *******************************************************************************/
#define ASM_ESP(_n)                 [esp + 4*(_n)]
#define ASM_ESP_ADD(_n)             __asm volatile ("add esp, 4*(" #_n ")")
#define ASM_ESP_SUB(_n)             __asm volatile ("sub esp, 4*(" #_n ")")

/****** Jump ************************************************************************************/
#define ASM_CALL(_t)                __asm volatile ("call " ASM__GETVAL(_t))
#define ASM_JUMP(_t)                __asm volatile ("jmp "  ASM__GETVAL(_t))
#define ASM_RET(_n)                 __asm volatile ("ret "  ASM__GETVAL(_n))

/****** Jump + Reg ******************************************************************************/
#define ASM_CALL_R(_r, _t)          __asm volatile ("mov " #_r ", " ASM__GETVAL(_t) "\n\tcall " #_r)
#define ASM_JUMP_R(_r, _t)          __asm volatile ("mov " #_r ", " ASM__GETVAL(_t) "\n\tcall " #_r)

#elif defined(MT_C_MSVC)            /* microsoft visual c                                       */

#pragma warning( disable : 4100 )   /* 'x': unreferenced parameter                              */

/****** Func Tag ********************************************************************************/
#define ASM_FUNC                    __declspec(naked)

/****** Move ************************************************************************************/
#define ASM_MOVE(_r, _v)            __asm { __asm mov       _r, _v }
#define ASM_MOVZX(_r, _v)           __asm { __asm movzx,    _r, _v }
#define ASM_MOVSX(_r, _v)           __asm { __asm movsx,    _r, _v }

/****** Math ************************************************************************************/
#define ASM_ADD(_t, _v)             __asm { __asm add       _t, _v }
#define ASM_SUB(_t, _v)             __asm { __asm sub       _t, _v }
#define ASM_MUL(_t, _v)             __asm { __asm mul       _t, _v }

/****** Push/Pop ********************************************************************************/
#define ASM_PUSH(_v)                __asm { __asm push      _v }
#define ASM_POP(_t)                 __asm { __asm pop       _t }

/****** Stack Ptr *******************************************************************************/
#define ASM_ESP(_n)                 [esp + 4*(_n)]
#define ASM_ESP_ADD(_n)             __asm { __asm add esp, 4*(_n) }
#define ASM_ESP_SUB(_n)             __asm { __asm sub esp, 4*(_n) }

/****** Jump ************************************************************************************/
#define ASM_CALL(_t)                __asm { __asm call _t }
#define ASM_JUMP(_t)                __asm { __asm jmp  _t }
#define ASM_RET(_n)                 __asm { __asm ret  _n }

/****** Jump + Reg ******************************************************************************/
#define ASM_CALL_R(_r, _t)          __asm { __asm mov _r, _t __asm call _r }
#define ASM_JUMP_R(_r, _t)          __asm { __asm mov _r, _t __asm jmp  _r }

#endif/*MT_C_CLANG, MT_C_GCC, MT_C_MSVC*/

EXTERN_END

#endif/*H_UTIL_ASMUTIL*/
