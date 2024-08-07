/*
*   Sonic Adventure Mod Tools (SA2B) - '/sonic/move.h'
*
*   Contains structs and functions related to MOVE_WORK
*
*   Contributors:
*     - SEGA - Sonic Team,
*     - Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC
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
#include <sa2b/sonic/shadow.h>

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
    int32_t     unk;
    f32         rad;
    f32         height;
    f32         weight;
    uint16_t    Flag;
    uint16_t    Timer;
    f32         Spd;
    f32         Gravity;
    int32_t     ViewAngle;
    f32         ViewRange;
    NJS_POINT3  AimPos;
    NJS_POINT3  PrePos;
    NJS_POINT3  HomePos;
    Angle3      HomeAng;
    Angle3      Phase;
    NJS_LINE    FrontWall;
    NJS_POINT3  Offset;
    f32         Top;
    f32         Side;
    f32         Bottom;
    f32         CliffHeight;
    f32         BoundSide;
    f32         BoundFloor;
    f32         BoundCeiling;
    f32         BoundFriction;
    f32         TopY;
    f32         BottomY;
    f32         WaterY;
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
int32_t MOV_TurnToPlayer2(TASK* tp, Angle rot_spd, int player_num);

/** Clear MOVE_WORK parameters **/
void    MOV_ClearVelo(TASK* tp);
void    MOV_ClearAcc(TASK* tp);

/** Update and calculate collisions **/
int32_t MOV_DetectCollision(TASK* tp);

/** Internal detect collision code **/
int32_t MOV_GetShadowPosXYZ(TASK* tp);
void    MOV_CheckFloor(TASK* tp);
void    MOV_CheckWall(TASK* tp);

EXTERN_END

/************************/
/*  Function Ptrs       */
/************************/
#ifdef SAMT_INCL_FUNCPTRS
/** Function ptrs **/
#   define MOV_Init_p                   FUNC_PTR(MOVE_WORK*, __cdecl, (TASK*), 0x007966D0)
#   define MOV_CalcPlayerAngle_p        FUNC_PTR(Angle, __fastcall, (TASK*, int), 0x007969B0)

/** User-Function ptrs **/
#   define MOV_GetShadowPosXYZ_p        ((void*)0x00797E10)
#   define MOV_CheckFloor_p             ((void*)0x00796B20)
#   define MOV_CheckWall_p              ((void*)0x00796CA0)
#   define MOV_TurnToPlayer2_p          ((void*)0x00796CA0)

#endif /* SAMT_INCL_FUNCPTRS */

#endif /* _SA2B_MOVE_H_ */
