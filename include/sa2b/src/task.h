/*
*   Sonic Adventure Mod Tools (SA2B) - '/src/task.h'
*
*   Contains defines, structs, functions, and enums related to the TASK system
*
*   Contributors:
*   -   SEGA - Sonic Team,
*   -   Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC.
*/
#ifndef _SA2B_TASK_H_
#define _SA2B_TASK_H_

/************************/
/*  Includes            */
/************************/
/** Ninja **/
#include <sa2b/ninja/njcommon.h>

/** Task Work **/
#include <sa2b/src/task/taskwk.h>
#include <sa2b/src/task/motionwk.h>
#include <sa2b/src/task/forcewk.h>
#include <sa2b/src/task/anywk.h>

/************************/
/*  Abstract Types      */
/************************/
typedef struct _OBJ_CONDITION   OBJ_CONDITION;

/************************/
/*  Typedefs            */
/************************/
typedef void(__cdecl* task_exec)(TASK*);

/************************/
/*  Enums               */
/************************/
typedef enum tasklevel
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
TASKLEVEL;

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
    task_exec       disp_shad;  /* Shadow Displayer */

    /** Task Work Pointers **/
    OBJ_CONDITION*  ocp;        /* Set Data                         */
    TASKWK*         twp;        /* Task Work                        */
    MOTIONWK*       mwp;        /* Motion Work                      */
    FORCEWK*        fwp;        /* Force Work          (Array of 2) */
    ANYWK*          awp;        /* Any Work                         */
    char*           name;       /* Task Name                        */
    char*           name2;      /* Task Name       (Copy of 'name') */

    union {
        int8_t    b[4];
        int16_t   w[2];
        int32_t   l;
        float32_t f;
        void* ptr;
    } thp;                      /* Needs more research              */
}
TASK;

/************************/
/*  Data                */
/************************/
#define btp     DataAry(TASK*, 0x01A5A254, [8]) /* Task lists */

/************************/
/*  Task Element Flags  */
/************************/
#define TELE_NUL    (0)
#define TELE_MWK    (1<<0)
#define TELE_TWK    (1<<1)
#define TELE_FWK    (1<<2)
#define TELE_AWK    (1<<3)

/************************/
/*  Functions           */
/************************/
EXTERN_START
/** Create new TASK **/
TASK*   CreateElementalTask(uint8_t im, int32_t level, task_exec exec, const char* name);
/** Create new task as a child of another TASK **/
TASK*   CreateChildTask(int16_t im, task_exec exec, TASK* tp);

/** Queue TASK for freeing **/
void    FreeTask(TASK* tp);

/** Generic TASK_EXEC **/
void    no_op(TASK* tp);

/** Internal functions **/
void    DestroyTask(TASK* tp);

EXTERN_END

/************************/
/*  Function Ptrs       */
/************************/
#ifdef SAMT_INCLUDE_FUNC_PTRS
/** Function ptr **/
#define CreateChildTask_p   FuncPtr(TASK*, __cdecl, (int16_t, task_exec, TASK*), 0x0470C00)
#define DestroyTask_p       FuncPtr(void , __cdecl, (TASK*)                   , 0x046F720)

/** User-Function ptr **/
EXTERN const void* const CreateElementalTask_p;

#endif/*SAMT_INCLUDE_FUNC_PTRS*/

#endif/*_SA2B_TASK_H_*/
