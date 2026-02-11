/*
*   SAMT for Sonic Adventure 2 (PC, 2012) - '/sonic/task/anywk.h'
*
*   Description:
*     Task 'Any Work'.
*/
#ifndef H_SA2B_TASK_ANYWK
#define H_SA2B_TASK_ANYWK

EXTERN_START

/********************************/
/*  Structures                  */
/********************************/
/****** Work ************************************************************************************/
#define TO_ANYWK(p)         ((anywk*)(p))

typedef struct anywk
{
    union
    {
        uint8_t   ub[16];           /* unsigned bytes                                           */
        int8_t    sb[16];           /* signed bytes                                             */
        uint16_t  uw[8];            /* unsigned words                                           */
        int16_t   sw[8];            /* signed words                                             */
        uint32_t  ul[4];            /* unsigned longs                                           */
        int32_t   sl[4];            /* signed longs                                             */
        f32       f[4];             /* real numbers                                             */
        void*     ptr[4];           /* pointers                                                 */
    }
    work;                           /* inline work                                              */
}
anywk;

EXTERN_END

#endif/*H_SA2B_TASK_ANYWK*/
