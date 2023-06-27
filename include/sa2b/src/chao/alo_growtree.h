#pragma once

struct TREE_SAVE_INFO;
struct cnkobj;
struct task;

enum eTREE_KIND : sint32
{
	TREE_NONE = 0x0,
	TREE_MORIMORI = 0x1,
	TREE_PAKUPAKU = 0x2,
	TREE_HERO = 0x3,
	TREE_DARK = 0x4,
	TREE_MARU = 0x5,
	TREE_SANKAKU = 0x6,
	TREE_SIKAKU = 0x7,
	TREE_LOCAL = 0x8,
	TREE_END = 0x9,
};

enum eTREE_STATE : sint32
{
	TREE_ST_PLANT = 0x0,
	TREE_ST_SEED = 0x1,
	TREE_ST_SAPLING = 0x2,
	TREE_ST_ADULT = 0x3,
	TREE_ST_DEAD = 0x4,
	TREE_ST_LOCAL = 0x5,
};

struct FRUIT_INFO
{
	float32 growth;
	float32 AimGrowth;
	sint32 SwingCounter;
	NJS_POINT3 pos;
	sint32 angx;
	sint32 angy;
};

struct TREE_WORK
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
	colliwk* cwp;
	uint8 type;
	uint8 state;
	uint8 UNDEF0;
	uint8 UNDEF1;
	float32 growth;
	sint32 life;
	sint32 water;
	uint8 pos_num;
	uint8 UNDEF2;
	uint8 UNDEF3;
	uint8 UNDEF4;
	FRUIT_INFO fruit[3];
	float32 scale;
	float32 scaleSpd;
	sint32 ThirstyFlag;
	sint32 WaterFlag;
	sint32 LeafRotAng;
	float32 LeafWidth;
	sint32 LeafDispNum;
	Angle FruitRotAng;
	float32 FruitWidth;
	sint32 FruitDisplayNum;
	sint32 SwingFlag;
	sint32 SwingCountFlag;
	float32 SwingDist;
	Angle RollAngle;
	Angle TouchAngle;				// The angle it is being touched from
	sint32 ChaoSwingPhase;
	sint32 RollPhase;
	sint32 garden;
	TREE_SAVE_INFO* pMySaveInfo;
	NJS_TEXLIST* texlist;
	cnkobj* pLocalObject;
	cnkobj* pShadowObject;
	cnkobj* pCopyObject;
};

DataAry(Angle, LeafPhaseList, 0x12E8AEC, [11]);
DataAry(Angle, FruitPhaseList, 0x013291B4, [4]);

DataAry(NJS_VECTOR, ALO_GrowTreePositions, 0x01366B30, [3][10]);

FuncPtr(void, __cdecl, CalcFruitPosSub, (NJS_POINT3* pPos, TREE_WORK* pTree, cnkobj* pObject, sint32 FruitNum), 0x00546530);
FuncPtr(void, __cdecl, CalcFruitPos, (NJS_POINT3* pPos, TREE_WORK* pTree, int FruitNum), 0x00546670);

TaskFuncPtr(ALO_GrowTreeDisplayer, 0x00547E70);
TaskFuncPtr(ALO_GrowTreeDestructor, 0x005481E0);
TaskFuncPtr(ALO_GrowTreeExecutor, 0x00546810);

FuncPtr(task*, __cdecl, ALO_GrowTreeCreate, (NJS_POINT3* pPos, TREE_SAVE_INFO* info), 0x00548210);

