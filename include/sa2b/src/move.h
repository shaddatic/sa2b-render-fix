/*
*   Sonic Adventure Mod Tools (SA2B) - '/src/move.h'
*
*   Contains structs and functions related to MOVE_WORK
*
*   Contributors:
*   -   SEGA - Sonic Team,
*   -   Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC.
*/
#pragma once

/************************/
/*  Abstracted Types    */
/************************/
typedef struct task		TASK;

/************************/
/*  Includes            */
/************************/
#include <sa2b/src/shadow.h>

/************************/
/*  Structures          */
/************************/
struct XYZ_SHADOW_WORK
{
	NJS_POINT3 pos;
	xssunit hit[6];
	xssunit pre_hit[6];
};

#define GET_MOVE_WORK(tp) (MOVE_WORK*)(tp->mwp)

struct MOVE_WORK
{
	NJS_VECTOR  Velo;
	NJS_VECTOR  Acc;
	Angle3      AimAng;
	Angle3      RotSpd;
	sint32      unk;
	float32     rad;
	float32     height;
	float32     weight;
	uint16      Flag;
	uint16      Timer;
	float32     Spd;
	float32     Gravity;
	sint32      ViewAngle;
	float32     ViewRange;
	NJS_POINT3  AimPos;
	NJS_POINT3  PrePos;
	NJS_POINT3  HomePos;
	Angle3      HomeAng;
	Angle3      Phase;
	NJS_LINE    FrontWall;
	NJS_POINT3  Offset;
	float32     Top;
	float32     Side;
	float32     Bottom;
	float32     CliffHeight;
	float32     BoundSide;
	float32     BoundFloor;
	float32     BoundCeiling;
	float32     BoundFriction;
	float32     TopY;
	float32     BottomY;
	float32     WaterY;
	XYZ_SHADOW_WORK Shadow;
};

/************************/
/*  Function Pointers   */
/************************/
FuncPtr(MOVE_WORK*, __cdecl, MOV_Init, (TASK* tp), 0x007966D0);

FuncPtr(Angle, __fastcall, MOV_CalcPlayerAngle, (TASK* tp, int player_num), 0x007969B0);

/************************/
/*  User Functions      */
/************************/
sint32	MOV_GetShadowPosXYZ(TASK* tp);

void	MOV_CheckFloor(TASK* tp);
void	MOV_CheckWall(TASK* tp);

sint32	MOV_TurnToPlayer2(TASK* tp, Angle rot_spd, int player_num);

/************************/
/*  Functions           */
/************************/
void	MOV_ClearVelo(TASK* tp);
void	MOV_ClearAcc(TASK* tp);

sint32	MOV_DetectCollision(TASK* tp);

/************************/
/*  User Functions Ptrs */
/************************/
#ifdef SAMT_INCLUDE_USER_PTRS

extern const void* MOV_GetShadowPosXYZ_p;

extern const void* MOV_CheckFloor_p;
extern const void* MOV_CheckWall_p;

extern const void* MOV_TurnToPlayer2_p;

#endif