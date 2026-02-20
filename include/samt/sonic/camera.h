/*
*   SAMT for Sonic Adventure 2 (PC, 2012) - '/sonic/camera.h'
*
*   ~~ Under Construction ~~
* 
*   Description:
*       Contains structs and data related to the camera.
*/
#ifndef _SA2B_CAMERA_H_
#define _SA2B_CAMERA_H_

/************************/
/*  Includes            */
/************************/
#include <samt/ninja/njcommon.h>
#include <samt/ninja/njcamera.h>

#include <samt/sonic/task/taskwk.h>

/************************/
/*  Header Types        */
/************************/
typedef struct _CameraSystemWork    CameraSystemWork;

/************************/
/*  Defines             */
/************************/
#define camera_curpos               camera_pos[cameraNumber]

/************************/
/*  Structures          */
/************************/
typedef struct _camposwk
{
    NJS_POINT3 pos;
    NJS_ANGLE3 ang;
    NJS_VECTOR dir;
    NJS_POINT3 tgt;
    NJS_POINT3 diff;
    f32        tgtdist;
}
camposwk;

typedef struct _camcontwk
{
    i32         cammode;
    b32         colliflag;
    i32         timer;
    NJS_POINT3  pos;
    NJS_ANGLE3  ang;
    NJS_VECTOR  dir;
    NJS_POINT3  tgt;
    f32         tgtdist;
}
camcontwk;

typedef struct 
{
    NJS_POINT3 current_pos;
    NJS_POINT3 next_pos;
    int flag_mask;
    float float_1C;
    NJS_POINT3 output_pos;
    char gap2C[220];
    NJS_POINT3 dir;
    char gap114[36];
    int field_138;
}
CAMCOLLI;

typedef struct _OBJ_CAMERAPARAM
{
    int mode;
    int field_4;
    uint32_t counter;
    void (__cdecl * pfnCamera)(CameraSystemWork*, struct _OBJ_CAMERAPARAM*);
    int field_10;
    char work[256];
}
OBJ_CAMERAPARAM;

typedef struct _OBJ_ADJUSTPARAM
{
    int adjust;
    int field_4;
    uint32_t counter;
    void (__cdecl * pfnAdjust)(CameraSystemWork*, struct _OBJ_ADJUSTPARAM*);
    int field_10;
    char work[256];
}
OBJ_ADJUSTPARAM;

typedef struct _CameraSystemWork
{
    Angle fov;                              /* current fov                          */
    Angle fov_tgt;                          /* target fov                           */
    Angle fov_spd;                          /* fov change speed                     */

    b32   LR_flag;                          /* free look flag                       */
    b32   player_stop_flag;   

    int32_t unk_0;
    CAMCOLLI ColliInfo;

    NJS_VECTOR shake_offset;
    int32_t shake_mode;
    int32_t shake_timer;
    f32     shake_mag;

    NJS_CAMERA camera;

    camposwk posCamera[3];                  /* position + position history          */

    int32_t level;
    OBJ_CAMERAPARAM Camera[16];
    OBJ_ADJUSTPARAM Adjust[16];
}
CameraSystemWork;

typedef struct _OBJ_CAMERAMODE
{
    const char* name;
    void (__cdecl* fnCamera)(CameraSystemWork*, OBJ_CAMERAPARAM*);
    int unk;
}
OBJ_CAMERAMODE;

typedef struct _OBJ_CAMERAADJUST
{
    const char* name;
    void (__cdecl* fnAdjust)(CameraSystemWork*, OBJ_ADJUSTPARAM*);
}
OBJ_CAMERAADJUST;

typedef struct // Under Construction
{
    Angle turn_ang;
    bool bTurning;
    char padding[251];
}
CAMADJUSTWK_KNUCKLES;

/************************/
/*  Data                */
/************************/
#define cameraCount                 DATA_REF(int32_t         , 0x01DD946C)
#define cameraNumber                DATA_REF(int32_t         , 0x01DD92A0)

#define cameraSystemWork            DATA_ARY(CameraSystemWork, 0x01DCFF40, [4])
#define cameraControlWork           DATA_REF(camcontwk       , 0x01DCFF00)

#define CameraMode                  DATA_ARY(OBJ_CAMERAMODE  , 0x008ABD38, [28])
#define CameraAdjust                DATA_ARY(OBJ_CAMERAADJUST, 0x008ABE88, [14])

#define camera_twp                  DATA_REF(taskwk*         , 0x01A5A784)
#define camera_pos                  DATA_ARY(camposwk*       , 0x01DD92B0, [4])

#endif/*_SA2B_CAMERA_H_*/
