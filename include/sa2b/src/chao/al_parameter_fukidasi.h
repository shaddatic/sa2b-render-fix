#pragma once

/*
*	Abstracted Types
*/

typedef struct task TASK;

/*
*	Structs
*/

const struct StatUIStats
{
	int field_0;
	int timer;
	uint8 StatLevelsOriginal;
	uint8 StatFractionOriginal;
	uint8 StatPointsOriginal;
	uint8 StatLevels;
	uint8 StatFraction;
	uint8 StatPoints;
};

const struct AL_PARAMFUKIDASI_WORK
{
	sint8 mode;
	sint8 smode;
	sint32 timer;
	sint32 timer2;
	sint8 countV;
	uint8 flag;
	float32 posX;
	float32 posY;
	float32 aimX;
	float32 aimY;
	float32 alpha;
	float32 size;
	sint32 phase;
	sint32 phase2;
	sint32 location;
	sint32 loc_timer;
	task* pChaoTask;
	struct CHAO_PARAM_GC* pParamGC;
	int mExpUpdating;
	StatUIStats Stats[5];
	int mLevelUpJingle;
	void* mEach;
};

/*
*	Data References
*/

DataRef(TASK*, pChaoParamFukidasiTask, 0x01AED28C);

/*
*	Function Pointers
*/

FuncPtr(void, __thiscall, AL_CloseParameterFukidasi, (TASK* pChaoTask), 0x00565B90);

/*
*	Task Function Pointers
*/

TaskFuncPtr(ParamFukidasiExecutor, 0x00564C80);
TaskFuncPtr(ParamFukidasiDisplayer, 0x00565200);
TaskFuncPtr(ParamFukidasiDestructor, 0x005659C0);

/*
*	User Functions
*/

void AL_OpenParameterFukidasi(TASK* tp);

/*
*	User Function Pointers
*/

#ifdef SAMT_INCLUDE_USER_PTRS

extern const void* AL_OpenParameterFukidasi_p;

#endif