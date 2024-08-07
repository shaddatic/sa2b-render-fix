/*
*   Sonic Adventure Mod Tools (SA2B) - '/sonic/motion.h'
*
*   Contains structs and functions related to object motion data
*
*   Contributors:
*     - SEGA - Sonic Team,
*     - Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC
*/
#ifndef _SA2B_MOTION_H_
#define _SA2B_MOTION_H_

/************************/
/*  Includes            */
/************************/
#include <sa2b/ninja/ninja.h>

/************************/
/*  Enums               */
/************************/
enum
{
    MD_MTN_LOOP,
    MD_MTN_ADLP,
    MD_MTN_LKLP,
    MD_MTN_STOP,
    MD_MTN_LINK,
    MD_MTN_SKIP,
    MD_MTN_CHNG,
    MD_MTN_BACK,
};

/************************/
/*  Structures          */
/************************/
typedef struct
{
    NJS_MOTION* pMotion;
    int16_t     mode;
    int16_t     posture;
    int32_t     next;
    int32_t     link_step;
    f32         start;
    f32         end;
    f32         spd;
}
MOTION_TABLE;

typedef struct
{
    uint16_t    mode;
    f32         frame;
    f32         start;
    f32         end;
    f32         spd;
    NJS_MOTION* pMotion;
}
MOTION_INFO;

typedef struct 
{
    uint16_t      flag;
    uint16_t      posture;
    int32_t       curr_num;
    int32_t       next_num;
    f32           multi_spd;
    f32           link_spd;
    f32           ratio;
    MOTION_INFO   minfo[2];
    MOTION_TABLE* table;
}
MOTION_CTRL;

/************************/
/*  Functions           */
/************************/
EXTERN_START
void        MotionInit( MOTION_CTRL* pMtnCtrl, MOTION_TABLE* pTable );

void        MotionControl( MOTION_CTRL* pMtnCtrl );

b32         IsMotionEnd(  MOTION_CTRL* pMtnCtrl );
b32         IsMotionStop( MOTION_CTRL* pMtnCtrl );

void        SetMotionFrame( MOTION_CTRL* pMtnCtrl, f32 frame );
void        SetMotionSpd(   MOTION_CTRL* pMtnCtrl, f32 spd   );

void        SetMotionNum( MOTION_CTRL* pMtnCtrl, int32_t MtnNum );

void        SetMotionNext( MOTION_CTRL* pMtnCtrl );

int32_t     GetMotionNum( MOTION_CTRL* pMtnCtrl );

f32         GetMotionFrame(   MOTION_CTRL* pMtnCtrl );
int32_t     GetMotionPosture( MOTION_CTRL* pMtnCtrl );

void        SetMotionChange( MOTION_CTRL* pMtnCtrl, int32_t MtnNum );
void        SetMotionSkip(   MOTION_CTRL* pMtnCtrl, int32_t MtnNum );

void        SetMotionLink(     MOTION_CTRL* pMtnCtrl, int32_t MtnNum );
void        SetMotionLinkSync( MOTION_CTRL* pMtnCtrl, int32_t MtnNum );
void        SetMotionLinkStep( MOTION_CTRL* pMtnCtrl, int32_t MtnNum, uint16_t step );

void        DrawMotion(  NJS_CNK_OBJECT* pObject, MOTION_CTRL* pMtnCtrl );
void        DrawGinjaMotion( GJS_OBJECT* pObject, MOTION_CTRL* pMtnCtrl );

EXTERN_END

/************************/
/*  Function Ptrs       */
/************************/
#ifdef SAMT_INCL_FUNCPTRS
/** User-Function ptrs **/
#   define MotionInit_p             ((void*)0x00793880)
#   define MotionControl_p          ((void*)0x007938D0)
#   define SetMotionLink_p          ((void*)0x00793C40)
#   define SetMotionLinkStep_p      ((void*)0x00793D30)
#   define DrawMotion_p             ((void*)0x00793F90)
#   define DrawGinjaMotion_p        ((void*)0x00794010)

#   define IsMotionEnd_p            ((void*)0x00793F70)
#   define IsMotionStop_p           ((void*)0x00793F80)

#   define SetMotionLinkSync_p      ((void*)0x00793D90)

#   define SetMotionChange_p        ((void*)0x00793EA0)
#   define SetMotionSkip_p          ((void*)0x00793E40)

#   define SetMotionNext_p          ((void*)0x00793CB0)

#   define SetMotionNum_p           ((void*)0x00793F10)

#endif/*SAMT_INCL_FUNCPTRS*/

#endif/*_SA2B_MOTION_H_*/
