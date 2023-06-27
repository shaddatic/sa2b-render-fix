#pragma once

/*
*	Abstracted Structs
*/

typedef struct task		TASK;
typedef struct taskwk	TASKWK;

/*
*	Structs
*/

struct ODAKAKE_WORK // anywk
{
	sint32 ButtonState;
	sint32 CoverMode;
	float32 CoverFrame;
	float32 ButtonPos;
	struct task* pChaoTask;
	sint32 FileFlag;
	sint32 BuyoFlag;
	sint32 BuyoPhase;
	sint32 MonitorMode;
	sint32 MonitorCount;
	sint32 MonitorTimer;
	sint32 ring;
};

/*
*	Data References
*/

DataRef(struct task*, OdekakeTaskPointer, 0x01AED318);

DataRef(sint32, CrappyReplacementDepartureMachine, 0x1AED320);
DataRef(sint32, EnteringOdekake, 0x01AED31C);

/*
*	Task Functions
*/

TaskFuncPtr(ALO_OdekakeMachine, 0x0057E460);
TaskFuncPtr(ALO_OdekakeMachineExecutor, 0x0057D540);
TaskFuncPtr(ALO_OdekakeMachineDestructor, 0x0057E040);
TaskFuncPtr(ALO_OdekakeMachineDisplayerNeut, 0x0057E060);

/*
*	User Functions
*/

TASKWK* ALO_OdekakeMachineCreate(NJS_POINT3* pPos, Angle angy);

/*
*	User Function Pointers
*/