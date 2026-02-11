/*
*   SAMT for Sonic Adventure 2 (PC, 2012) - '/sonic/task/taskexec.h'
*
*   Description:
*     Task 'task_exec'.
*/
#ifndef H_SA2B_TASK_TASKEXEC
#define H_SA2B_TASK_TASKEXEC

EXTERN_START

/********************************/
/*  Opaque Types                */
/********************************/
/****** Task ************************************************************************************/
typedef struct task             task;

/********************************/
/*  Types                       */
/********************************/
/****** Task Exec *******************************************************************************/
typedef void(__cdecl* task_exec)( task* );

EXTERN_END

#endif/*H_SA2B_TASK_TASKEXEC*/
