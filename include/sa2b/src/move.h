#pragma once

/*
*	Abstracted Structs
*/

typedef struct task		task;

/*
*	Includes
*/

#include <sa2b/src/shadow.h>

/*
*	Structs
*/

struct XYZ_SHADOW_WORK
{
	NJS_POINT3 pos;
	xssunit hit[6];
	xssunit pre_hit[6];
};

#define GET_MOVEWORK(TP) (MOVE_WORK*)TP->mwp

struct MOVE_WORK
{
	NJS_POINT3 Velo;
	NJS_POINT3 Acc;
	Angle3 AimAng;
	Angle3 RotSpd;
	int btlonlygap; // Not sure what this is, but this is what I called it
	float rad;
	float height;
	float weight;
	unsigned __int16 Flag;
	unsigned __int16 Timer;
	float Spd;
	float Gravity;
	int ViewAngle;
	float ViewRange;
	NJS_POINT3 AimPos;
	NJS_POINT3 PrePos;
	NJS_POINT3 HomePos;
	Angle3 HomeAng;
	Angle3 Phase;
	NJS_LINE FrontWall;
	NJS_POINT3 Offset;
	float Top;
	float Side;
	float Bottom;
	float CliffHeight;
	float BoundSide;
	float BoundFloor;
	float BoundCeiling;
	float BoundFriction;
	float TopY;
	float BottomY;
	float WaterY;
	XYZ_SHADOW_WORK Shadow;
};

/*
*	Function Pointers
*/

FuncPtr(MOVE_WORK*, __cdecl, MOV_Init, (task* tp), 0x007966D0);

FuncPtr(Angle, __fastcall, MOV_CalcPlayerAngle, (task* tp, int player_num), 0x007969B0);

/*
*	User Functions
*/

sint32	MOV_GetShadowPosXYZ(task* tp);

void	MOV_CheckFloor(task* tp);
void	MOV_CheckWall(task* tp);

sint32	MOV_TurnToPlayer2(task* tp, Angle rot_spd, int player_num);

/*
*	Remade Functions
*/

void	MOV_ClearVelo(task* tp);
void	MOV_ClearAcc(task* tp);

sint32	MOV_DetectCollision(task* tp);

/*
*	User Function Pointers
*/

#ifdef SAMT_INCLUDE_USER_PTRS

extern const void* MOV_GetShadowPosXYZ_p;

extern const void* MOV_CheckFloor_p;
extern const void* MOV_CheckWall_p;

extern const void* MOV_TurnToPlayer2_p;

#endif