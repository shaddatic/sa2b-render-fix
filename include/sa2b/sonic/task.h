/*
*   Sonic Adventure Mod Tools (SA2B) - '/sonic/task.h'
*
*   Contains defines, structs, functions, and enums related to the Task system
*
*   Contributors:
*     - SEGA - Sonic Team,
*     - Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC
*/
#ifndef _SA2B_TASK_H_
#define _SA2B_TASK_H_

/************************/
/*  Includes            */
/************************/
/** Ninja **/
#include <sa2b/ninja/njcommon.h>

/** Task Work **/
#include <sa2b/sonic/task/taskwk.h>
#include <sa2b/sonic/task/motionwk.h>
#include <sa2b/sonic/task/forcewk.h>
#include <sa2b/sonic/task/anywk.h>

#include <sa2b/sonic/task/taskexec.h>

/************************/
/*  Abstract Types      */
/************************/
typedef struct _OBJ_CONDITION   OBJ_CONDITION;

/************************/
/*  Enums               */
/************************/
typedef enum
{
    LEV_0,
    LEV_1,
    LEV_2,
    LEV_3,
    LEV_4,
    LEV_5,
    LEV_6,
    LEV_C,
    LEV_M
}
tasklevel;

/************************/
/*  Structures          */
/************************/
typedef struct task
{
    struct task*    next;       /* Next Task                        */
    struct task*    last;       /* Last Task                        */
    struct task*    ptp;        /* Parent Task                      */
    struct task*    ctp;        /* Child Task                       */

    /** Task Executors **/
    task_exec       exec;       /* Executor                         */
    task_exec       disp;       /* Displayer            (Drawn 1st) */
    task_exec       dest;       /* Destructor                       */
    task_exec       disp_dely;  /* Delayed Displayer    (Drawn 3rd) */
    task_exec       disp_sort;  /* Sorted Displayer     (Drawn 2nd) */
    task_exec       disp_late;  /* Late Displayer       (Drawn 4th) */
    task_exec       disp_last;  /* Last Displayer       (Drawn 5th) */
    task_exec       disp_shad;  /* Shadow Displayer                 */

    /** Set Pointers **/
    OBJ_CONDITION*  ocp;        /* Set Data                         */

    /** Task Work Pointers **/
    struct taskwk*   twp;       /* Task Work                        */
    struct motionwk* mwp;       /* Motion Work                      */
    struct forcewk*  fwp;       /* Force Work          (Array of 2) */
    struct anywk*    awp;       /* Any Work                         */

    char*            name;      /* Task Name                        */
    u32                id;      /* Task ID    (unused & unfinished) */

    union {
        s8      b[4];
        s16     w[2];
        s32     l;
        f32     f;
        void*   ptr;
    } thp;                      /* Needs more research              */
}
task;

/************************/
/*  Data                */
/************************/
#define btp                 DATA_ARY(task*, 0x01A5A254, [8]) /* Task lists */

/************************/
/*  Task Element Flags  */
/************************/
#define TELE_NUL            (0)     /* No Elements                  */
#define TELE_MWK            (1<<0)  /* Motion Work                  */
#define TELE_TWK            (1<<1)  /* Task Work                    */
#define TELE_FWK            (1<<2)  /* Force Work                   */
#define TELE_AWK            (1<<3)  /* Any Work                     */

/************************/
/*  Functions           */
/************************/
EXTERN_START
/****** Create Task *****************************************************************/
/** Create new Task **/
task*   CreateElementalTask(u8 im, tasklevel level, task_exec exec, const char* name);
/** Create new task as a child of another Task **/
task*   CreateChildTask(int16_t im, task_exec exec, task* tp);

/****** Free Task *******************************************************************/
/** Queue Task for freeing **/
void    FreeTask(task* tp);

/****** Task Exec *******************************************************************/
/** Generic Task_EXEC **/
void    no_op(task* tp);

/****** Task Destructor Exec ********************************************************/
void    DestroyTask(task* tp);

EXTERN_END

/************************/
/*  Function Ptrs       */
/************************/
#ifdef SAMT_INCL_FUNCPTRS
/** Function ptr **/
#   define CreateChildTask_p        FUNC_PTR(task*, __cdecl, (s16, task_exec, task*), 0x00470C00)
#   define DestroyTask_p            FUNC_PTR(void , __cdecl, (task*)                , 0x0046F720)

/** User-Function ptr **/
#   define CreateElementalTask_p    ((void*)0x0046F610);

#endif/*SAMT_INCL_FUNCPTRS*/

#endif/*_SA2B_TASK_H_*/
