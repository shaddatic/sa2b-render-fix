/*
*   SAMT for Sonic Adventure 2 (PC, 2012) - '/sonic/task/taskwk.h'
*
*   Description:
*     Task 'Task Work'.
*/
#ifndef H_SA2B_TASK_TASKWK
#define H_SA2B_TASK_TASKWK

/********************************/
/*  Includes                    */
/********************************/
/****** Ninja ***********************************************************************************/
#include <samt/ninja/njcommon.h>    /* ninja common                                             */

EXTERN_START

/********************************/
/*  Opaque Types                */
/********************************/
/****** Colliwk *********************************************************************************/
typedef struct colliwk              colliwk; /* collision work                                  */

/********************************/
/*  Structures                  */
/********************************/
/****** Work Macro ******************************************************************************/
#define TASKWK struct { \
    i8          mode;               /* task mode                                                */ \
    i8          smode;              /* task secondary mode                                      */ \
    u8          id;                 /* task id                                                  */ \
    u8          btimer;             /* byte timer                                               */ \
    i16         flag;               /* task flags                                               */ \
    u16         wtimer;             /* word timer                                               */ \
    Angle3      ang;                /* task angle                                               */ \
    NJS_POINT3  pos;                /* task position                                            */ \
    NJS_VECTOR  scl;                /* task scale                                               */ \
    colliwk*    cwp;                /* collision work pointer                                   */ \
}

/****** Work ************************************************************************************/
#define TO_TASKWK(p)                ((taskwk*)(p))

typedef struct taskwk
{
    TASKWK;                         /* task work                                                */
}
taskwk;

EXTERN_END

#endif/*H_SA2B_TASK_TASKWK*/
