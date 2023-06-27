#pragma once

#include <sa2b/src/task.h>
#include <sa2b/src/Chao/al_garden_info.h>

struct ALO_ChaosDriveWork
{
	taskwk twk;
	char kind;
	char gap_31[3];
	int field_34;
	char gap_38[4];
	int field_3C;
	int field_40;
	char gap_44[4];
	int field_48;
	int field_4C;
	int field_50;
};

enum eAL_DRIVES : sint32 // Non-standard
{
	AL_DRIVE_YELLOW = 0x15,
	AL_DRIVE_GREEN = 0x16,
	AL_DRIVE_RED = 0x17,
	AL_DRIVE_PURPLE = 0x18
};

TaskFuncPtr(ALO_ChaosDriveExecutor, 0x005450C0);
TaskFuncPtr(ALO_ChaosDriveDestructor, 0x005455B0);
TaskFuncPtr(ALO_ChaosDriveDisplayer, 0x00545150);
TaskFuncPtr(ALO_ChaosDriveDisp1, 0x00545430);

FuncPtr(task*, __cdecl, ALO_ChaosDriveCreate, (uint8 kind, NJS_POINT3* pPos, NJS_VECTOR* idkvector, ITEM_SAVE_INFO* a4), 0x00545600);