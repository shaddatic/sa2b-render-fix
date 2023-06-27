#pragma once

struct task;
struct CCL_INFO;

struct AL_CAMERA_WORK
{
	char mode; // Action
	char smode; // Next Action
	char id;
	char btimer; // Index
	__int16 flag;
	__int16 wtimer;
	Angle3 ang;
	NJS_POINT3 pos;
	NJS_POINT3 scl;
	colliwk* cwp;
	uint16 type;
	uint8 UNDEF0;
	uint8 UNDEF1;
	NJS_POINT3 spd;
	NJS_POINT3 AimPos;
	Angle3 AngSpd;
	NJS_POINT3 tgtpos;
	NJS_POINT3 AimTarget;
	float tgtdist;
	sint32 ViewAngle;
	float TargetNormalOffsetY;
	float TargetTreeOffsetY;
	float PosOffsetY;
	float PosItpRatio;
	sint32 StopFlag;
};

DataRef(task*, AL_NormalCameraTaskPointer, 0x01AED2E8);

TaskFuncPtr(AL_NormalCameraExecutor, 0x0057CD50);
TaskFuncPtr(AL_NormalCameraDestructor, 0x0057D2D0);
FuncPtr(task*, __cdecl, AL_CreateNormalCameraTask, (), 0x0057D2E0);

DataPtr(CCL_INFO, AL_NormalCamColInfo, 0x008A57B0);

FuncPtr(void, __cdecl, ALCAM_CreateCameraManager, (), 0x0057D4C0);