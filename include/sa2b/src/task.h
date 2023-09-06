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
#pragma once

/************************/
/*  Abstracted Types    */
/************************/
typedef struct colliwk			COLLIWK;
typedef struct OBJ_CONDITION	OBJ_CONDITION;

/************************/
/*  Includes            */
/************************/
#include <sa2b/ninja/njcommon.h>

/************************/
/*  Header Types        */
/************************/
typedef struct task		TASK;
typedef struct taskwk	TASKWK;
typedef struct motionwk	MOTIONWK;
typedef struct forcewk	FORCEWK;
typedef struct anywk	ANYWK;

/************************/
/*  Typedefs            */
/************************/
typedef void(__cdecl* task_exec)(TASK*);

/************************/
/*  Enums               */
/************************/
enum tasklevel
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
;

/************************/
/*  Structures          */
/************************/
typedef struct taskwk
{
	sint8 mode;
	sint8 smode;
	sint8 id;
	sint8 btimer;
	sint16 flag;
	sint16 wtimer;
	Angle3 ang;
	NJS_POINT3 pos;
	NJS_POINT3 scl;
	COLLIWK* cwp;
}
TASKWK;

typedef struct motionwk
{
	NJS_POINT3 spd;
	NJS_POINT3 acc;
	Angle3 ang_aim;
	Angle3 ang_spd;
	float32 force;
	float32 accel;
	float32 frict;
}
MOTIONWK;

typedef struct forcewk
{
	void(__cdecl* call_back)(TASK*, TASKWK*, FORCEWK*);
	Angle3 ang_spd;
	NJS_POINT3 pos_spd;
}
FORCEWK;

typedef struct anywk
{
	union {
		uint8 ub[16];
		sint8 sb[16];
		uint16 uw[8];
		sint16 sw[8];
		uint32 ul[4];
		sint32 sl[4];
		float32 f[4];
		void* ptr[4];
	}
	work;
}
ANYWK;

typedef struct task
{
	struct task*	next;		/* Next Task */
	struct task*	last;		/* Last Task */
	struct task*	ptp;		/* Parent Task */
	struct task*	ctp;		/* Child Task */
	task_exec		exec;		/* Executor */
	task_exec		disp;		/* Displayer (Drawn 1st) */
	task_exec		dest;		/* Destructor */
    task_exec       disp_dely;  /* Delayed Displayer (Drawn 3rd) */
    task_exec       disp_sort;  /* Sorted Displayer (Drawn 2nd) */
    task_exec       disp_late;  /* Late Displayer (Drawn 4th) */
    task_exec       disp_last;  /* Last Displayer (Drawn 5th) */
	task_exec		disp_shad;  /* Shadow Displayer */
	OBJ_CONDITION*	ocp;        /* Set Data */
	TASKWK*			twp;		/* Task Work */
	MOTIONWK*		mwp;		/* Motion Work */
	FORCEWK*		fwp;		/* Force Work */
	ANYWK*			awp;		/* Any Work */
	char*			name;
	char*			name2;
	void*			sdp;		/* Shadow Work */
}
TASK;

/************************/
/*  Data                */
/************************/
DataAry(TASK*, btp, 0x1A5A254, [8]); /* Task lists */

/************************/
/*  Function Pointers   */
/************************/
FuncPtr(TASK*,	__cdecl, CreateChildTask,	(sint16 im, task_exec exec, TASK* tp),	0x470C00);

FuncPtr(void,	__cdecl, DestroyTask,		(TASK* tp),								0x046F720);

/************************/
/*  Task Element Flags  */
/************************/
#define TELE_NUL	(0)
#define TELE_MWK	(1<<0)
#define TELE_TWK	(1<<1)
#define TELE_FWK	(1<<2)
#define TELE_AWK	(1<<3)

/************************/
/*  User Functions      */
/************************/
TASK*	CreateElementalTask(uint8 im, sint32 level, task_exec exec, const char* name);

/************************/
/*  Functions           */
/************************/
void	FreeTask(TASK* tp);

void	no_op(TASK* tp);

/************************/
/*  User Function Ptrs  */
/************************/
#ifdef SAMT_INCLUDE_USER_PTRS

extern const void* CreateElementalTask_p;

#endif