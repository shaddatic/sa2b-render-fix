/*
*   SAMT for Sonic Adventure 2 (PC, 2012) - '/sonic/task.h'
*
*   Description:
*     SA2's game object system.
*/
#ifndef H_SA2B_TASK
#define H_SA2B_TASK

/********************************/
/*  Includes                    */
/********************************/
/****** Ninja ***********************************************************************************/
#include <samt/ninja/njcommon.h>    /* ninja common                                             */

/****** Task ************************************************************************************/
#include <samt/sonic/task/taskwk.h>   /* task work                                              */
#include <samt/sonic/task/motionwk.h> /* motion work                                            */
#include <samt/sonic/task/forcewk.h>  /* motion work                                            */
#include <samt/sonic/task/anywk.h>    /* any work                                               */
#include <samt/sonic/task/taskexec.h> /* task executor                                          */

EXTERN_START

/********************************/
/*  Opaque Types                */
/********************************/
/****** Set Condition ***************************************************************************/
typedef struct _OBJ_CONDITION       OBJ_CONDITION;

/********************************/
/*  Constants                   */
/********************************/
/****** Task Flags ******************************************************************************/
#define IM_NONE                     (0)     /* no work                                          */
#define IM_MWK                      (1<<0)  /* motion work                                      */
#define IM_TWK                      (1<<1)  /* task work                                        */
#define IM_FWK                      (1<<2)  /* force work                                       */
#define IM_AWK                      (1<<3)  /* any work                                         */

/********************************/
/*  Enums                       */
/********************************/
/****** Task Level ******************************************************************************/
typedef enum
{
    LEV_0,                          /* level 0, high priority                                   */
    LEV_1,                          /* level 1, high priority                                   */
    LEV_2,                          /* level 2                                                  */
    LEV_3,                          /* level 3                                                  */
    LEV_4,                          /* level 4                                                  */
    LEV_5,                          /* level 5                                                  */
    LEV_6,                          /* level 6                                                  */
    LEV_C,                          /* create only, task not added to btp list                  */

    LEV_M                           /* task level max                                           */
}
tasklevel;

anywk;

/********************************/
/*  Structures                  */
/********************************/
/****** Task ************************************************************************************/
typedef struct task
{
    struct task*    next;           /* next                                                     */
    struct task*    last;           /* last                                                     */
    struct task*    ptp;            /* parent                                                   */
    struct task*    ctp;            /* child                                                    */

    task_exec       exec;           /* executor                                                 */
    task_exec       disp;           /* displayer                                          [1st] */
    task_exec       dest;           /* destructor                                               */
    task_exec       disp_dely;      /* delayed displayer                                  [3rd] */
    task_exec       disp_sort;      /* sorted displayer                                   [2nd] */
    task_exec       disp_late;      /* late displayer                                     [4th] */
    task_exec       disp_last;      /* last displayer                                     [5th] */
    task_exec       disp_shad;      /* shadow displayer                                         */

    OBJ_CONDITION*  ocp;            /* object/set data                                          */

    struct taskwk*   twp;           /* task work                                                */
    struct motionwk* mwp;           /* motion work                                              */
    struct forcewk*  fwp;           /* force work                                  [array of 2] */
    struct anywk*    awp;           /* any work                                                 */

    char*            name;          /* name                                                     */
    u32              id;            /* id                                 [unused & unfinished] */

    union {
        i8      b[4];               /* bytes                                                    */
        i16     w[2];               /* words                                                    */
        i32     l;                  /* long                                                     */
        f32     f;                  /* real                                                     */
        void*   ptr;                /* pointer                                                  */
    }
    work;                           /* inline work                                              */
}
task;

/********************************/
/*  Variables                   */
/********************************/
/****** Task List *******************************************************************************/
#define btp                         DATA_ARY(task*    , 0x01A5A254, [LEV_M])

/********************************/
/*  Prototypes                  */
/********************************/
/****** Create Task *****************************************************************************/
/*
*   Description:
*     Create a new task.
*
*   Notes:
*     - 'Elemental' means 'foundational', as in 'not a child task'.
*
*   Parameters:
*     - im          : init mask                                                          [IM_#]
*     - level       : task level
*     - exec        : task executor                                               [opt:nullptr]
*     - name        : task name
*/
task*   CreateElementalTask( u16 im, tasklevel level, task_exec exec, const c7* name );
/*
*   Description:
*     Create a new task as a child of another task.
*
*   Parameters:
*     - im          : init mask                                                          [IM_#]
*     - exec        : task executor
*     - tp          : task parent
*/
task*   CreateChildTask( u16 im, task_exec exec, task* tp );

/****** Free Task *******************************************************************************/
/*
*   Description:
*     Queue a task for freeing.
*
*   Notes:
*     - Members 'ocp', 'twp', 'mwp', 'fwp', & 'awp' are freed automatically.
*
*   Parameters:
*     - tp          : task
*/
void    FreeTask( task* tp );
/*
*   Description:
*     Queue all tasks for freeing, except 'LEV_0' and 'LEV_1'.
*/
void    PurgeTask( void );
/*
*   Description:
*     Queue all tasks for freeing.
*/
void    GenocideTask( void );

/****** Destroy Task ****************************************************************************/
/*
*   Description:
*     Frees all task data, and task pointers.
*
*   Parameters:
*     - tp          : task
*/
void    DestroyTask( task* tp );

#ifdef SAMT_INCL_FUNCPTRS

/********************************/
/*  Function Pointers           */
/********************************/
/****** Function Pointers ***********************************************************************/
#define CreateChildTask_p                   FUNC_PTR(task*, __cdecl, (u16, task_exec, task*), 0x00470C00)
#define PurgeTask_p                         FUNC_PTR(void , __cdecl, (void)                 , 0x00470AE0)
#define GenocideTask_p                      FUNC_PTR(void , __cdecl, (void)                 , 0x00470B10)
#define DestroyTask_p                       FUNC_PTR(void , __cdecl, (task*)                , 0x0046F720)

/****** Usercall Pointers ***********************************************************************/
#define CreateElementalTask_p               ((void*)0x0046F610)

#endif/*SAMT_INCL_FUNCPTRS*/

EXTERN_END

#endif/*H_SA2B_TASK*/
