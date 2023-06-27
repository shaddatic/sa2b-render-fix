#pragma once

struct task;
struct ITEM_SAVE_INFO;

enum eFRUIT_KIND : sint32
{
	FRUIT_NEUT_LOCAL = 0x0,
	FRUIT_HERO_LOCAL = 0x1,
	FRUIT_DARK_LOCAL = 0x2,
	FRUIT_MORIMORI = 0x3,
	FRUIT_PAKUPAKU = 0x4,
	FRUIT_HERO = 0x5,
	FRUIT_DARK = 0x6,
	FRUIT_MARU = 0x7,
	FRUIT_SANKAKU = 0x8,
	FRUIT_SIKAKU = 0x9,
	FRUIT_HEART = 0xA,
	FRUIT_CHAO = 0xB,
	FRUIT_ORIKOU = 0xC,
	FRUIT_GBA_A = 0xD,
	FRUIT_GBA_B = 0xE,
	FRUIT_GBA_C = 0xF,
	FRUIT_GBA_D = 0x10,
	FRUIT_GBA_E = 0x11,
	FRUIT_GBA_F = 0x12,
	FRUIT_GBA_G = 0x13,
	FRUIT_KINOKO_A = 0x14,
	FRUIT_KINOKO_B = 0x15,
	FRUIT_MINTCANDY = 0x16,
	FRUIT_GRAPE = 0x17,
	FRUIT_DX_DEFAULT = 0x18,
	FRUIT_END = 0x19,
};

TaskFuncPtr(ALO_FruitExecutor, 0x545E40);
TaskFuncPtr(ALO_FruitDisplayer, 0x545EE0);
TaskFuncPtr(ALO_FruitDestructor, 0x0057B9B0); // Same function as many other ALO objects

FuncPtr(task*, __cdecl, ALO_FruitCreate, (eFRUIT_KIND kind, NJS_POINT3* pPos, sint32 AngY, NJS_VECTOR* pVelo, ITEM_SAVE_INFO* pSaveInfo), 0x546180);