/*
*   SAMT for Sonic Adventure 2 (PC, 2012) - '/arch.h'
*
*   Description:
*     Architecture specific functions and logic.
*/
#ifndef H_MT_ARCH
#define H_MT_ARCH

/********************************/
/*  Constants                   */
/********************************/
/****** Arch ************************************************************************************/
#define MT_ARCH_X86                 1

EXTERN_START

/********************************/
/*  Functions                   */
/********************************/
/****** Arch ************************************************************************************/
/*
*   Description:
*     Yield this processor thread.
*/
void    mtArcYield( void );

EXTERN_END

#endif/*H_MT_ARCH*/
