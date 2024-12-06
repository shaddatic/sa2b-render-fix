/*
*   Sonic Adventure Mod Tools (SA2B) - '/sonic/task/taskwk.h'
*
*   Description:
*     Defines the 'taskwk' structure type and inheritance macro.
*
*   Contributors:
*     - SEGA - Sonic Team,
*     - Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC
*/
#ifndef H_SA2B_TASK_TASKWK
#define H_SA2B_TASK_TASKWK

/************************/
/*  External Includes   */
/************************/
/****** Ninja ***********************************************************************/
#include <sa2b/ninja/njcommon.h> /* ninja common                                    */

/************************/
/*  External Opaques    */
/************************/
/****** CCL Core ********************************************************************/
typedef struct colliwk          colliwk; /* collision work                          */

EXTERN_START

/************************/
/*  Structures          */
/************************/
/****** Set File ********************************************************************/
#define TO_TASKWK(_p)           ((taskwk*)(_p))

#define TASKWK                                                                         \
struct {                                                                               \
    s8              mode;       /* task mode                                        */ \
    s8              smode;      /* task secondary mode                              */ \
    s8              id;         /* task id                                          */ \
    s8              btimer;     /* byte timer                                       */ \
    s16             flag;       /* task flags                                       */ \
    s16             wtimer;     /* word timer                                       */ \
    Angle3          ang;        /* task angle                                       */ \
    NJS_POINT3      pos;        /* task position                                    */ \
    NJS_VECTOR      scl;        /* task scale                                       */ \
    colliwk*        cwp;        /* collision work pointer                           */ \
}

typedef struct taskwk
{
    TASKWK;
}
taskwk;

EXTERN_END

#endif/*H_SA2B_TASK_TASKWK*/
