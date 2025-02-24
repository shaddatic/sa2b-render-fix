/*
*   SAMT for Sonic Adventure 2 (PC, 2012) - '/sonic/task/taskexec.h'
*
*   Description:
*     Defines the 'task_exec' function type.
*/
#ifndef H_SA2B_TASK_TASKEXEC
#define H_SA2B_TASK_TASKEXEC

EXTERN_START

/************************/
/*  Opaque Types        */
/************************/
/****** Task ************************************************************************/
typedef struct task             task;

/************************/
/*  Function Types      */
/************************/
/****** Task Exec *******************************************************************/
typedef void(__cdecl* task_exec)( task* );

EXTERN_END

#endif/*H_SA2B_TASK_TASKEXEC*/
