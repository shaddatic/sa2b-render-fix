#pragma once

/*
*	Enums
*/

enum EChaoModuleEntry
{
	CHAO_MODULE_HEAD,
	CHAO_MODULE_STAGE,
	CHAO_MODULE_LAND,
	CHAO_MODULE_ETC,
	MAX_CHAO_MODULE
};

/*
*	Structs
*/

struct CHAO_MODULE
{
	char* name;
	void(__cdecl* prolog)();
	void(__cdecl* epilog)();
};

/*
*	Data References
*/

DataRef(CHAO_MODULE, ModuleCtrl, 0x01A0F950);

/*
*	Data Arrays
*/

DataAry(CHAO_MODULE, ChaoModules, 0x1366580, [48]);

/*
*	Function Pointers
*/

FuncPtr(void, __cdecl, AL_LoadModule, (const char* name, EChaoModuleEntry kind), 0x00530C20);