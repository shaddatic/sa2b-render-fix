/*
*   Sonic Adventure Mod Tools (SA2B) - '/src/chao/al_buyobuyo.h'
*
*   Contains functions and data related to the Chao jiggle engine.
*
*   Contributors:
*   -   SEGA - Sonic Team,
*   -   Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC.
*/
#ifndef _SA2B_CHAO_CAMERA_H_
#define _SA2B_CHAO_CAMERA_H_

/************************/
/*  Includes            */
/************************/
#include <sa2b/ninja/njcommon.h>

/************************/
/*  Abstract Types      */
/************************/
typedef struct task         TASK;
typedef struct ccl_info     CCL_INFO;
typedef struct colliwk      COLLIWK;

/************************/
/*  Structures          */
/************************/
#define GET_AL_CAMERA_WORK(tp)  ((AL_CAMERA_WORK*)tp->twp)

typedef struct // TASKWK
{
    sint8 mode; // Action
    sint8 smode; // Next Action
    sint8 id;
    sint8 btimer; // Index
    sint16 flag;
    sint16 wtimer;
    Angle3 ang;
    NJS_POINT3 pos;
    NJS_POINT3 scl;
    COLLIWK* cwp;
    uint16 type;
    uint8 UNDEF0;
    uint8 UNDEF1;
    NJS_POINT3 spd;
    NJS_POINT3 AimPos;
    Angle3 AngSpd;
    NJS_POINT3 tgtpos;
    NJS_POINT3 AimTarget;
    float32 tgtdist;
    sint32 ViewAngle;
    float32 TargetNormalOffsetY;
    float32 TargetTreeOffsetY;
    float32 PosOffsetY;
    float32 PosItpRatio;
    sint32 StopFlag;
}
AL_CAMERA_WORK;

/************************/
/*  Data                */
/************************/
#define AL_NormalCameraTaskPointer      DataRef(TASK*   , 0x01AED2E8)

/** Collision info **/
#define colli_info_alcam                DataAry(CCL_INFO, 0x008A57B0, [2])

/************************/
/*  Functions           */
/************************/
EXTERN_START
/*
*   AL Camera Manager 
*/
void    ALCAM_CreateCameraManager(void);

/** Task functions **/
void    ALCAM_CameraManagerExecutor(TASK* tp);
void    ALCAM_CameraManagerDestructor(TASK* tp);

/*
*   AL Camera Task
*/
TASK*   AL_CreateNormalCameraTask(void);

/** Task functions **/
void    AL_NormalCameraExecutor(TASK* tp);
void    AL_NormalCameraDestructor(TASK* tp);

EXTERN_END

/************************/
/*  Function Ptrs       */
/************************/
#ifdef SAMT_INCLUDE_FUNC_PTRS
/** Function ptrs **/
#define ALCAM_CreateCameraManager_p         FuncPtr(void , __cdecl, (void) , 0x0057D4C0)
#define ALCAM_CameraManagerExecutor_p       FuncPtr(void , __cdecl, (TASK*), 0x0057D400)
#define ALCAM_CameraManagerDestructor_p     FuncPtr(void , __cdecl, (TASK*), 0x0057D410)
#define AL_CreateNormalCameraTask_p         FuncPtr(TASK*, __cdecl, (void) , 0x0057D2E0)
#define AL_NormalCameraExecutor_p           FuncPtr(void , __cdecl, (TASK*), 0x0057CD50)
#define AL_NormalCameraDestructor_p         FuncPtr(void , __cdecl, (TASK*), 0x0057D2D0)

#endif /* SAMT_INCLUDE_FUNC_PTRS */

#endif /* _SA2B_CHAO_CAMERA_H_ */