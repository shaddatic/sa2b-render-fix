/*
*   SAMT for Sonic Adventure 2 (PC, 2012) - '/sonic/task/forcewk.h'
*
*   Description:
*     Task 'Force Work'.
*/
#ifndef H_SA2B_TASK_FORCEWK
#define H_SA2B_TASK_FORCEWK

/********************************/
/*  Includes                    */
/********************************/
/****** Ninja ***********************************************************************************/
#include <samt/ninja/njcommon.h>    /* ninja common                                             */

EXTERN_START

/********************************/
/*  Opaque Types                */
/********************************/
/****** Task ************************************************************************************/
typedef struct task                 task;    /* task                                            */
typedef struct taskwk               taskwk;  /* task work                                       */
typedef struct forcewk              forcewk; /* force work                                      */

/********************************/
/*  Structures                  */
/********************************/
/****** Work ************************************************************************************/
#define TO_FORCEWK(p)               ((forcewk*)(p))

typedef struct forcewk
{
    void(__cdecl* call_back)(task*, taskwk*, forcewk*); /* callback                             */
    NJS_ANGLE3    ang_spd;                              /* angle speed                          */
    NJS_POINT3    pos_spd;                              /* position speed                       */
}
forcewk;

EXTERN_END

#endif/*H_SA2B_TASK_FORCEWK*/
