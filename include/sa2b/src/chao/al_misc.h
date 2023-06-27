#pragma once

/*
*	Abstracted Structs
*/

typedef struct task		task;

/*
*	Includes
*/

#include <sa2b/ninja/ninja.h>

/*
*	Enums
*/

enum : sint32
{
	CI_KIND_AL_CHAO = 0x81,
	CI_KIND_AL_CHAO_FIELD = 0x82,
	CI_KIND_AL_FRUIT = 0x83,
	CI_KIND_AL_FRUIT_FIELD = 0x84,
	CI_KIND_AL_SEED = 0x85,
	CI_KIND_AL_SEED_FIELD = 0x86,
	CI_KIND_AL_MINIMAL = 0x87,
	CI_KIND_AL_MINIMAL_FIELD = 0x88,
	CI_KIND_AL_TREE = 0x89,
	CI_KIND_AL_TREE_FIELD = 0x8A,
	CI_KIND_AL_TOY = 0x8B,
	CI_KIND_AL_TOY_FIELD = 0x8C,
	CI_KIND_AL_EGG = 0x8D,
	CI_KIND_AL_EGG_FIELD = 0x8E,
	CI_KIND_AL_TRASH = 0x8F,
	CI_KIND_AL_TRASH_FIELD = 0x90,
	CI_KIND_AL_DAKKO_FIELD = 0x91,
	CI_KIND_AL_NADE_FIELD = 0x92,
	CI_KIND_AL_OBAKE_HEAD = 0x93,
	CI_KIND_AL_CDR = 0x94,
	CI_KIND_AL_PUNCH = 0x95,
	CI_KIND_AL_SHADOW = 0x96,
	CI_KIND_AL_ONARA = 0x97,
	CI_KIND_AL_SOUND = 0x98,
	CI_KIND_AL_HELLO = 0x99,
	CI_KIND_AL_TOBIKOMI = 0x9A,
	CI_KIND_AL_REQUEST_WATER = 0x9B,
	CI_KIND_AL_NOISE = 0x9C,
	CI_KIND_AL_CONTACT = 0x9D,
	CI_KIND_AL_ACTION = 0x9E,
	CI_KIND_AL_SONG = 0x9F,
	CI_KIND_AL_BALL = 0xA0,
	CI_KIND_AL_FIRE = 0xA1,
	CI_KIND_AL_BIKKURI = 0xA2,
	CI_KIND_AL_BOX = 0xA3,
	CI_KIND_AL_WALL = 0xA4,
	CI_KIND_AL_RANDOM_MUSIC = 0xA5,
	CI_KIND_AL_DANCE = 0xA6,
	CI_KIND_AL_SING = 0xA7,
	CI_KIND_AL_SING_ONCHI = 0xA8,
	CI_KIND_AL_RAKUGAKI = 0xA9,
	CI_KIND_AL_FINISH = 0xAA,
	CI_KIND_AL_NEST = 0xAB,
	CI_KIND_AL_PLANT_POS = 0xAC,
	CI_KIND_AL_WATER = 0xAD,
	CI_KIND_AL_THIRSTY = 0xAE,
	CI_KIND_AL_TOUCH = 0xAF,
	CI_KIND_AL_SWITCH = 0xB0,
	CI_KIND_AL_CHANGE = 0xB1,
	CI_KIND_AL_SET_RACE_TREE = 0xB2,
	CI_KIND_AL_SET_RACE_GLIDE = 0xB3,
	CI_KIND_AL_SET_RACE_JUMP = 0xB4,
	CI_KIND_AL_SET_RACE_LAKE = 0xB5,
	CI_KIND_AL_SET_RACE_KARIMONO = 0xB6,
	CI_KIND_AL_SET_RACE_KOWAI = 0xB7,
	CI_KIND_AL_SET_RACE_GOAL = 0xB8,
	CI_KIND_AL_SET_RACE_ENABLE_TURN = 0xB9,
	CI_KIND_AL_SET_RACE_ALONG_LANE = 0xBA,
	CI_KIND_AL_SET_RACE_REMEMBER_POS = 0xBB,
	CI_KIND_AL_SET_RACE_THINK_POS = 0xBC,
	CI_KIND_AL_SET_RACE_PARALLEL = 0xBD,
	CI_KIND_AL_SET_RACE_GOAL_BANZAI = 0xBE,
	CI_KIND_AL_SET_RACE_PATHCOLLI = 0xBF,
	CI_KIND_AL_SET_RACE_POLYCOLLI = 0xC0,
	CI_KIND_AL_SET_RACE_EACHCOLLI = 0xC1,
	CI_KIND_AL_LOG = 0xC2,
	CI_KIND_AL_ROCK = 0xC3,
	CI_KIND_AL_HOLL = 0xC4,
	CI_KIND_AL_KANI = 0xC5,
	CI_KIND_AL_ANSWER_POS = 0xC6,
	CI_KIND_AL_ANSWER_OBJ = 0xC7,
	CI_KIND_AL_GOOD = 0xC8,
	CI_KIND_AL_TV = 0xC9,
	CI_KIND_AL_RADICASE = 0xCA,
	CI_KIND_AL_CLIMB = 0xCB,
	CI_KIND_AL_FURIMUKI = 0xCC,
	CI_KIND_AL_STAGE_CHANGER = 0xCD,
	CI_KIND_END = 0xFF,
};

/*
*	Structs
*/

struct SAngle3
{
	uint16 x, y, z;
};

/*
*	Function Pointers
*/

FuncPtr(void, __cdecl, AL_InterpolateObject, (NJS_CNK_OBJECT* pObj1, NJS_CNK_OBJECT* pObj2, NJS_CNK_OBJECT* pAnswer, float ratio), 0x0054AEB0); // no official name yet

/*
*	Data References
*/

/*
*	Data Pointers
*/

/*
*	Data Arrays
*/

/*
*	User Functions
*/

float32 ___njUnitVector(NJS_POINT3* p);

bool32	AL_IsOnScreen3(task* tp, float radius, float HalfHeight, float OffsetY);

sint32	AL_IsHitKindWithNum(task* tp, int info_num, uint8 kind);

void	AL_InterpolateAngle(Angle3* pAng1, Angle3* pAng2, Angle3* pAnswer, float ratio);
void	AL_InterpolateSAngle(SAngle3* pAng1, SAngle3* pAng2, SAngle3* pAnswer, float ratio);

/*
*	Remade Functions
*/

bool32	AL_IsOnScreen2(task* tp, float radius, float OffsetY);

/*
*	User Function Pointers
*/

#ifdef SAMT_INCLUDE_USER_PTRS

extern const void* ___njUnitVector_p;

extern const void* AL_IsOnScreen3_p;

extern const void* AL_IsHitKindWithNum_p;

extern const void* AL_InterpolateAngle_p;
extern const void* AL_InterpolateSAngle_p;

#endif