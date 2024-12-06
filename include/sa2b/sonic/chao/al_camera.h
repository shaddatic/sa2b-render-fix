/*
*   Sonic Adventure Mod Tools (SA2B) - '/sonic/chao/al_buyobuyo.h'
*
*   Description:
*       Definitions for the main Camera used in Chao World.
*
*   Contributors:
*     - SEGA - Sonic Team,
*     - Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC
*/
#ifndef _SA2B_CHAO_CAMERA_H_
#define _SA2B_CHAO_CAMERA_H_

/************************/
/*  Includes            */
/************************/
/** Ninja **/
#include <sa2b/ninja/njcommon.h>

/** Task Work **/
#include <sa2b/sonic/task/taskwk.h>

/** Colli Info **/
#include <sa2b/sonic/c_colli/ccl_info.h>

/************************/
/*  Abstract Types      */
/************************/
typedef struct task         task;

/************************/
/*  Structures          */
/************************/
#define GET_AL_CAMERA_WORK(tp)  ((AL_CAMERA_WORK*)tp->twp)

typedef struct
{
    TASKWK;

    uint16_t type;
    NJS_POINT3 spd;
    NJS_POINT3 AimPos;
    Angle3 AngSpd;
    NJS_POINT3 tgtpos;
    NJS_POINT3 AimTarget;
    f32       tgtdist;
    int32_t ViewAngle;
    f32       TargetNormalOffsetY;
    f32       TargetTreeOffsetY;
    f32       PosOffsetY;
    f32       PosItpRatio;
    int32_t StopFlag;
}
AL_CAMERA_WORK;

/************************/
/*  Data                */
/************************/
#define AL_NormalCameraTaskPointer      DATA_REF(task*   , 0x01AED2E8)

/** Collision info **/
#define colli_info_alcam                DATA_ARY(CCL_INFO, 0x008A57B0, [2])

/************************/
/*  Functions           */
/************************/
EXTERN_START
/*
*   AL Camera Manager 
*/
void    ALCAM_CreateCameraManager(void);

/** Task functions **/
void    ALCAM_CameraManagerExecutor(task* tp);
void    ALCAM_CameraManagerDestructor(task* tp);

/*
*   AL Camera Task
*/
task*   AL_CreateNormalCameraTask(void);

/** Task functions **/
void    AL_NormalCameraExecutor(task* tp);
void    AL_NormalCameraDestructor(task* tp);

EXTERN_END

/************************/
/*  Function Ptrs       */
/************************/
#ifdef  SAMT_INCL_FUNCPTRS
/** Function ptrs **/
#   define ALCAM_CreateCameraManager_p          FUNC_PTR(void , __cdecl, (void) , 0x0057D4C0)
#   define ALCAM_CameraManagerExecutor_p        FUNC_PTR(void , __cdecl, (task*), 0x0057D400)
#   define ALCAM_CameraManagerDestructor_p      FUNC_PTR(void , __cdecl, (task*), 0x0057D410)
#   define AL_CreateNormalCameraTask_p          FUNC_PTR(task*, __cdecl, (void) , 0x0057D2E0)
#   define AL_NormalCameraExecutor_p            FUNC_PTR(void , __cdecl, (task*), 0x0057CD50)
#   define AL_NormalCameraDestructor_p          FUNC_PTR(void , __cdecl, (task*), 0x0057D2D0)

#endif/*SAMT_INCL_FUNCPTRS*/

#endif/*_SA2B_CHAO_CAMERA_H_*/
