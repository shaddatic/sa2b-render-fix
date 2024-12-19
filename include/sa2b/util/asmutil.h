/*
*   Sonic Adventure Mod Tools (SA2B) - '/util/c_constexpr.h'
*
*   Description:
*     Useful macros for inline assembly programming.
*
*   Contributors:
*     - Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC
*/
#ifndef H_UTIL_ASMUTIL
#define H_UTIL_ASMUTIL

/************************/
/*  Macros              */
/************************/
/****** Stack Util ******************************************************************/
/*
*   Description:
*     Calculates the number of bytes to add to the 'esp' register based on the
*   number of 32bit 'push' instructions used.
*
*   Examples:
*     - push eax // 1
*       push ebx // 2
*       push ecx // 3
*       push edx // 4
*       call ptr
*       add esp, ADDESP(4) // 4 'push' instructions, so add 4*4 bytes to
*                          // the 'esp' register
*
*   Returns:
*     The number of bytes needed to reset the stack after 'nb' 32bit pushes.
*/
#define ADDESP(nb)              (4*(nb))
/*
*   Description:
*     Calculates the number of bytes to add to the 'esp' register based on the
*   number of 16bit 'push' instructions used.
*
*   Examples:
*     - push ax // 1
*       push bx // 2
*       push cx // 3
*       push dx // 4
*       call ptr
*       add esp, ADDESP_16(4) // 4 'push' instructions, so add 4*2 bytes to
*                             // the 'esp' register
*
*   Returns:
*     The number of bytes needed to reset the stack after 'nb' 16bit pushes.
*/
#define ADDESP_16(nb)           (2*(nb))

#endif/*H_UTIL_ASMUTIL*/
