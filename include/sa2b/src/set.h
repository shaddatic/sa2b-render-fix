#pragma once

/*
*	Abstracted Types
*/

typedef struct task		TASK;
typedef struct taskwk	TASKWK;

/*
*	Typedefs
*/

typedef void(__cdecl* task_exec)(TASK*);

/*
*	Structs
*/

typedef union _UNION_STATUS
{
	float32 fRangeOut;
	sint32 pObjSleepCondition;
}
UNION_STATUS;

typedef struct _OBJ_EDITENTRY
{
	uint16 usID;
	sint16 rotx;
	sint16 roty;
	sint16 rotz;
	float32 xpos;
	float32 ypos;
	float32 zpos;
	float32 xscl;
	float32 yscl;
	float32 zscl;
}
OBJ_EDITENTRY;

typedef struct OBJ_CONDITION
{
	uint8 scCount;
	uint8 scUserFlag;
	sint16 ssCondition;
	task* pTask;
	OBJ_EDITENTRY* pObjEditEntry;
	UNION_STATUS unionStatus;
}
OBJ_CONDITION;

typedef struct _OBJ_ITEMENTRY
{
	uint8 ucInitMode;
	uint8 ucLevel;
	sint16 ssAttribute;
	float32 fRange;
	task_exec fnExec;
	char* strObjName;
}
OBJ_ITEMENTRY;

typedef struct _OBJ_ITEMTABLE
{
	sint32 slCount;
	OBJ_ITEMENTRY* pObjItemEntry;
}
OBJ_ITEMTABLE;

/*
*	Task Functions
*/

TaskFuncPtr(ObjectGenericExec, 0x005B4250);

/*
*	User Functions
*/

sint32	CheckRangeOut(TASK* tp);
sint32	CheckRangeOutWithR(TASK* tp, float fRange);

/*
*	User Function Pointers
*/

#ifdef SAMT_INCLUDE_USER_PTRS

extern const void* CheckRangeOut_p;
extern const void* CheckRangeOutWithR_p;

#endif