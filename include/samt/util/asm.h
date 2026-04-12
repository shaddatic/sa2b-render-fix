/*
*   SAMT for Sonic Adventure 2 (PC, 2012) - '/util/asm.h'
*
*   Description:
*     Macros for assembly programming, usually for __usercall and __userpurge functions.
*/
#ifndef H_UTIL_ASMUTIL
#define H_UTIL_ASMUTIL

EXTERN_START

/********************************/
/*  Macros                      */
/********************************/
/************************************************************************************************/
/*
*   
*/
/****** Func Tags *******************************************************************************/
/*
*   Description:
*     Mark assembly function. Only required for definitions, not declarations. 
*/
#define ASM_FUNC                    __declspec(naked)

/************************************************************************************************/
/*
*   Util
*/
/****** Get Value *******************************************************************************/
/*
*   Description:
*     Get the value of an address, with an offset.
*
*   Parameters:
*     - t           : value target
*     - o           : offset
*/
#define ASM_VAL(_t, _o)             [_t + _o]

/************************************************************************************************/
/*
*   Basic
*/
/****** Move ************************************************************************************/
/*
*   Description:
*     Move value into register.
*
*   Parameters:
*     - r           : register
*     - v           : value
*/
#define ASM_MOVE(_r, _v)            __asm { __asm mov       _r, _v }
/*
*   Description:
*     Move value into register, with zero extension (unsigned).
*
*   Parameters:
*     - r           : register
*     - v           : value
*/
#define ASM_MOVZX(_r, _v)           __asm { __asm movzx,    _r, _v }
/*
*   Description:
*     Move value into register, with signed extension (signed).
*
*   Parameters:
*     - r           : register
*     - v           : value
*/
#define ASM_MOVSX(_r, _v)           __asm { __asm movsx,    _r, _v }

/****** Math ************************************************************************************/
/*
*   Description:
*     Add/Subtract/Multiply a target value and another value, and put the result into target.
*
*   Parameters:
*     - t           : target + value1
*     - v           : value2
*/
#define ASM_ADD(_t, _v)             __asm { __asm add       _t, _v }
#define ASM_SUB(_t, _v)             __asm { __asm sub       _t, _v }
#define ASM_MUL(_t, _v)             __asm { __asm mul       _t, _v }

/************************************************************************************************/
/*
*   Stack
*/
/****** Push/Pop ********************************************************************************/
/*
*   Description:
*     Push a value onto the stack (esp -= 4|2).
*
*   Notes:
*     - The size of the push is dependant on the size of the value, but single byte pushes are
*       not valid.
*
*   Parameters:
*     - v           : value to push onto the stack
*/
#define ASM_PUSH(_v)                __asm { __asm push      _v }
/*
*   Description:
*     Pop a value onto the stack (esp -= 4|2).
*
*   Notes:
*     - The size of the push is dependant on the size of the target register, but single byte
*       pops are not valid.
*
*   Parameters:
*     - t           : register to pop into
*/
#define ASM_POP(_t)                 __asm { __asm pop       _t }

/****** Stack Ptr *******************************************************************************/
/*
*   Description:
*     Get a 4 byte value stored on the stack.
*
*   Parameters:
*     - n           : 4 byte aligned offset
*/
#define ASM_ESP(_n)                 [esp + 4*(_n)]
/*
*   Description:
*     Add a 4 byte offset to the stack, to pop without reading.
*
*   Parameters:
*     - n           : 4 byte aligned offset
*/
#define ASM_ESP_ADD(_n)             __asm { __asm add esp, 4*(_n) }
/*
*   Description:
*     Subtract a 4 byte offset from the stack, to push without setting.
*
*   Parameters:
*     - n           : 4 byte aligned offset
*/
#define ASM_ESP_SUB(_n)             __asm { __asm sub esp, 4*(_n) }

/************************************************************************************************/
/*
*   Sub-routines
*/
/****** Jump ************************************************************************************/
/*
*   Description:
*     Jump to a label, and push the return address to the stack.
*
*   Parameters:
*     - t           : target label
*/
#define ASM_CALL(_t)                __asm { __asm call _t }
/*
*   Description:
*     Jump to a label.
*
*   Parameters:
*     - t           : target label
*/
#define ASM_JUMP(_t)                __asm { __asm jmp _t }
/*
*   Description:
*     Return from sub-routine.
*
*   Parameters:
*     - ...         : pop count, for callee cleanup
*/
#define ASM_RETN(...)               __asm { __asm retn __VA_ARGS__ }

/****** Jump + Reg ******************************************************************************/
/*
*   Description:
*     Jump to an arbitrary address, using a spare register.
*
*   Parameters:
*     - r           : tmp register
*     - t           : target address
*/
#define ASM_CALL_R(_r, _t)          __asm { __asm mov _r, _t __asm call _r }
#define ASM_JUMP_R(_r, _t)          __asm { __asm mov _r, _t __asm jmp _r }

EXTERN_END

#endif/*H_UTIL_ASMUTIL*/
