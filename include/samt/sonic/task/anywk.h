/*
*   SAMT for Sonic Adventure 2 (PC, 2012) - '/sonic/task/anywk.h'
*
*   Description:
*       Definitions and macros for the ANYWK struct type.
*/
#ifndef _SA2B_TASK_ANYWK_H_
#define _SA2B_TASK_ANYWK_H_

/************************/
/*  Structures          */
/************************/
#define TO_ANYWK(p) ((anywk*)p)

typedef struct anywk
{
    union {
        uint8_t   ub[16];
        int8_t    sb[16];
        uint16_t  uw[8];
        int16_t   sw[8];
        uint32_t  ul[4];
        int32_t   sl[4];
        f32       f[4];
        void*     ptr[4];
    } work;
}
anywk;

#endif/*_SA2B_TASK_ANYWK_H_*/
