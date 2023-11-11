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
#ifndef _SA2B_MOVE_H_
#define _SA2B_MOVE_H_

/************************/
/*  Abstracted Types    */
/************************/
typedef struct task     TASK;

/************************/
/*  Includes            */
/************************/
#include <sa2b/src/shadow.h>

/************************/
/*  Structures          */
/************************/
typedef struct
{
    NJS_POINT3 pos;
    XSSUNIT hit[6];
    XSSUNIT pre_hit[6];
}
XYZ_SHADOW_WORK;

#define GET_MOVE_WORK(tp)   ((MOVE_WORK*)(tp->mwp))

typedef struct move_work
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
}
MOVE_WORK;

/************************/
/*  Functions           */
/************************/
EXTERN_START
/** Initiate MOVE_WORK and put pointer in 'tp->mwp' **/
MOVE_WORK* MOV_Init(TASK* tp);

/** Calculate Angle to player from TASK **/
Angle   MOV_CalcPlayerAngle(TASK* tp, int player_num);
/** Turn TASK toward player by `rot_spd` **/
sint32  MOV_TurnToPlayer2(TASK* tp, Angle rot_spd, int player_num);

/** Clear MOVE_WORK parameters **/
void    MOV_ClearVelo(TASK* tp);
void    MOV_ClearAcc(TASK* tp);

/** Update and calculate collisions **/
sint32  MOV_DetectCollision(TASK* tp);

/** Internal detect collision code **/
sint32  MOV_GetShadowPosXYZ(TASK* tp);
void    MOV_CheckFloor(TASK* tp);
void    MOV_CheckWall(TASK* tp);

EXTERN_END

/************************/
/*  Function Ptrs       */
/************************/
#ifdef SAMT_INCLUDE_FUNC_PTRS
/** Function ptrs **/
#define MOV_Init_p                  FuncPtr(MOVE_WORK*, __cdecl, (TASK*), 0x007966D0)
#define MOV_CalcPlayerAngle_p       FuncPtr(Angle, __fastcall, (TASK*, int), 0x007969B0)

/** User-Function ptrs **/
extern const void* MOV_GetShadowPosXYZ_p;
extern const void* MOV_CheckFloor_p;
extern const void* MOV_CheckWall_p;
extern const void* MOV_TurnToPlayer2_p;

#endif /* SAMT_INCLUDE_FUNC_PTRS */

#endif /* _SA2B_MOVE_H_ */
