#pragma once

struct task;

#include <orca/sa2b/Chao/al_chao_info.h>

enum GBAManMode : __int32
{
	MD_GBAMAN_SLEEP = 0x0,
	MD_GBAMAN_ACTIVE = 0x1,
	MD_GBAMAN_ERROR = 0x2,
};

enum GBAPortMode : __int32
{
	MD_PORT_CHECK = 0x0,
	MD_PORT_LOAD = 0x1,
	MD_PORT_ODEKAKE = 0x2,
	MD_PORT_ODEKAKE_JOYBOOT = 0x3,
	MD_PORT_TORIDASU = 0x4,
	MD_PORT_FILE_SAVE = 0x5,
};

enum GBAPortKind : __int32
{
	GBA_PORT_KIND_NONE = 0x0,
	GBA_PORT_KIND_NOTCHAO = 0x1,
	GBA_PORT_KIND_WAITRES = 0x2,
	GBA_PORT_KIND_CHAO = 0x3,
};

enum EGbaCheck : __int32
{
	eGbaCheck_NotGba = 0x0,
	eGbaCheck_NotChao = 0x1,
	eGbaCheck_WaitRes = 0x2,
	eGbaCheck_Ready = 0x3,
	eGbaCheck__end = 0x4,
};

enum EGbaStatus : __int32
{
	eGbaStatus_Busy = 0x0,
	eGbaStatus_Succ = 0x1,
	eGbaStatus_Fail = 0x2,
	eGbaStatus__end = 0x3,
};

struct GBA_PORT_INFO
{
	EGbaCheck check;
	int NotGbaTimer;
	unsigned __int16 kind;
	GBAPortMode mode;
	int IsROM;
	int KinderFlag;
	int ToridasuFlag[11];
	int ExistFlag[11];
	CHAO_PARAM_GC* pToridasuChaoParam;
	int ToridasuEggColor;
	int ToridasuRing;
	unsigned __int8 ToridasuFruit[8];
	chao_save_info data;
	chao_save_info dataEgg;
};

struct GBA_MANAGER_WORK
{
	GBAManMode mode;
	int debugDisp;
	int IsBusy;
	task* tp;
	int IsOdekake;
	CHAO_PARAM_GC* pChaoParam;
	GBA_PORT_INFO PortInfo[4];
};
