#pragma once

/*
*	Includes
*/

#include <sa2b/ninja/ninja.h>

/*
*	Abstracted Structs
*/

typedef struct task task;

/*
*	Enums
*/

enum
{
	ALW_CATEGORY_CHAO = 0x0,
	ALW_CATEGORY_EGG = 0x1,
	ALW_CATEGORY_MINIMAL = 0x2,
	ALW_CATEGORY_FRUIT = 0x3,
	ALW_CATEGORY_TREE = 0x4,
	ALW_CATEGORY_GROWTREE = 0x5,
	ALW_CATEGORY_TOY = 0x6,
	ALW_CATEGORY_SEED = 0x7,
	ALW_CATEGORY_SOUND = 0x8,
	ALW_CATEGORY_MASK = 0x9,
	ALW_CATEGORY_SPECIAL = 0xA,
	NB_CATEGORY = 0xB,
};

enum
{
	ALW_KIND_NONE = 0x0,
	ALW_KIND_CDR = 0x1,
	ALW_KIND_TV = 0x2,
	ALW_KIND_RADICASE = 0x3,
	ALW_KIND_BALL = 0x4,
	ALW_KIND_PIANO = 0x5,
	ALW_KIND_ORGAN = 0x6,
	ALW_KIND_HORSE = 0x7,
	ALW_KIND_BOX = 0x8,
};

/*
*	Structs
*/

struct GROW_PARAM
{
	sint16 mood;
	sint16 belly;
	sint16 addexp[8];
};

typedef struct al_entry_work
{
	uint16 category;
	uint16 num;
	uint16 kind;
	uint16 flag;
	void* pSaveInfo;
	sint32 CommuID;
	NJS_POINT3 pos;
	Angle3 ang;
	float32 radius;
	float32 offset;
	float32 CamDist;
	sint16 command;
	sint16 command_value;
	sint16 state;
	task* tp;
	struct al_entry_work* pCommu;
	struct al_entry_work* pLockOn;
}
AL_ENTRY_WORK;

/*
*	Data References
*/

DataRef(bool32,	ChaoWorldLoadFlag,	0x01A5AF0C);

DataRef(sint32,	Clock,				0x01DBED74);
DataRef(sint32,	gBusy_0,			0x019F6440);
DataRef(sint32,	gLoaded_0,			0x019F6444);
DataRef(uint16,	CommuID,			0x01A5B5EC);

/*
*	Data Arrays
*/

DataAry(AL_ENTRY_WORK,	WorldEntryList,		0x01DC0FC0, [11][64]);
DataAry(sint32,			nbWorldEntry,		0x01DC0F80, [11]);
DataAry(sint32,			nbMaxEntry,			0x008AB838, [11]);

/*
*	nbMaxEntry:
* 
*	CHAO	32,
*	EGG		16,
*	MINIMAL	10,
*	FRUIT	48,
*	TREE	10
*	GTREE	16,
*	TOY		32,
*	SEED	16,
*	SOUND	16,
*	MASK	32,
*	SPECIAL	00,
*/

DataAry(GROW_PARAM,		FruitGrowParam,		0x008A6448, [24]);
DataAry(GROW_PARAM,		MinimalGrowParam,	0x008A6240, [26]);

/*
*	Function Pointers
*/

FuncPtr(void, __cdecl, ALW_Create, (), 0x00530B80);

/*
*	User Functions
*/

sint32 ALW_Entry2(uint16 category, task* tp, uint16 kind, void* pSaveInfo);

/*
*	Recreated Functions
*/

sint32			AL_ConfirmLoadIsBusy();

sint32			ALW_Entry(uint16 category, task* tp, uint16 kind);
task*			ALW_GetTask(sint32 category, uint16 num);
sint32			ALW_GetCategory(task* tp);

sint32			ALW_AttentionOn(task* tp1, task* tp2);
sint32			ALW_AttentionOff(task* tp);
AL_ENTRY_WORK*	ALW_IsAttention(task* tp);
sint32			ALW_IsSheAttentionOtherOne(task* pMyTask, task* pHerTask);
sint32			ALW_CommunicationOn(task* tp1, task* tp2);
sint32			ALW_CommunicationOff(task* tp);
AL_ENTRY_WORK*	ALW_IsCommunication(task* tp);
AL_ENTRY_WORK*	ALW_IsCommunicationEx(task* tp, uint16 category);
sint32			ALW_RecieveCommand(task* tp);

uint16			ALW_GetKind(task* tp); // unofficial

/*
*	User Function Pointers
*/

#ifdef SAMT_INCLUDE_USER_PTRS

extern const void* ALW_Entry2_p;

#endif