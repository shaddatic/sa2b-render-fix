/*
*   SAMT for Sonic Adventure 2 (PC, 2012) - '/sonic/task/motionwk.h'
*
*   Description:
*     Task 'Motion Work'.
*/
#ifndef H_SA2B_TASK_MOTIONWK
#define H_SA2B_TASK_MOTIONWK

/********************************/
/*  Includes                    */
/********************************/
/****** Ninja ***********************************************************************************/
#include <samt/ninja/njcommon.h>    /* ninja common                                             */

EXTERN_START

/********************************/
/*  Structures                  */
/********************************/
/****** Work Macro ******************************************************************************/
#define MOTIONWK struct { \
    NJS_VECTOR  spd;                /* speed                                                    */ \
    NJS_VECTOR  acc;                /* acceleration                                             */ \
    NJS_ANGLE3  ang_aim;            /* angle aim                                                */ \
    NJS_ANGLE3  ang_spd;            /* angle speed                                              */ \
    f32         force;              /* force                                                    */ \
    f32         accel;              /* forward acceleration                                     */ \
    f32         frict;              /* friction                                                 */ \
                          \
    union {               \
        i8      b[4];               /* bytes                                                    */ \
        i16     w[2];               /* words                                                    */ \
        i32     l;                  /* long                                                     */ \
        f32     f;                  /* real                                                     */ \
        void*   ptr;                /* pointer                                                  */ \
    }                     \
    work;                           /* inline work                                              */ \
}

/****** Work ************************************************************************************/
#define TO_MOTIONWK(p)              ((motionwk*)(p))

typedef struct motionwk
{
    MOTIONWK;
}
motionwk;

EXTERN_END

#endif/*H_SA2B_TASK_MOTIONWK*/
