#pragma once

typedef struct task		task;

typedef struct 
{
	float inv_radius;
	sint32 HeldAng;
	sint32 RotSpd;
	NJS_POINT3 axis;
	NJS_MATRIX mat;
}
BALL_WORK;

#define GET_BALL_WORK(tp) (BALL_WORK*)(tp->awp)

DataRef(sint32, BallUsable, 0x01DBE574);
DataRef(task*, ALO_BallTaskPointer, 0x01DBE570);

TaskFuncPtr(ALO_BallExecutor, 0x0055D310);
TaskFuncPtr(ALO_BallDestructor, 0x0057B9B0); // Same function as many other ALO objects
TaskFuncPtr(ALO_BallDisplayer, 0x0055D3B0);
TaskFuncPtr(ALO_BallCreate, 0x0055D640);

FuncPtr(NJS_POINT3*, __cdecl, ALO_BallCreateTask, (NJS_POINT3* pPos, NJS_VECTOR* pVelo), 0x0055D6B0);