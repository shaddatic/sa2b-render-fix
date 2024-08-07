/*
*   Sonic Adventure Mod Tools (SA2B) - '/sonic/camera.h'
*
*   ~~ Under Construction ~~
* 
*   Description:
*       Contains structs and data related to the camera.
*
*   Contributors:
*     - SEGA - Sonic Team,
*     - Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC
*/
#ifndef _SA2B_CAMERA_H_
#define _SA2B_CAMERA_H_

/************************/
/*  Includes            */
/************************/
#include <sa2b/ninja/njcommon.h>

#include <sa2b/sonic/task/taskwk.h>

/************************/
/*  Header Types        */
/************************/
typedef struct _CameraSystemWork    CAMSYSWK;

/************************/
/*  Defines             */
/************************/
#define cameraCurrentWork           cameraControlWork[cameraNumber]

/************************/
/*  Structures          */
/************************/
typedef struct _camcontwk
{
    NJS_POINT3 pos;
    Angle3     ang;
    NJS_VECTOR dir;
    NJS_POINT3 tgt;
    NJS_POINT3 diff;
    f32        spd;
}
CAMCONTWK;

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

typedef struct 
{
    NJS_POINT3 pos;
    NJS_POINT3 dir;
    Angle roll;
    Angle fov;
    float unknown;
}
CAMVIEW;

typedef struct _CAMERALEVEL
{
    int mode;
    int field_4;
    uint32_t counter;
    void (__cdecl * pfnCamera)(CAMSYSWK*, struct _CAMERALEVEL*);
    int field_10;
    char work[256];
}
CAMERALEVEL;

typedef struct _ADJUSTLEVEL
{
    int adjust;
    int field_4;
    uint32_t counter;
    void (__cdecl * pfnAdjust)(CAMSYSWK*, struct _ADJUSTLEVEL*);
    int field_10;
    char work[256];
}
ADJUSTLEVEL;

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

    CAMVIEW ViewInfo;

    int32_t unk_1;

    CAMCONTWK ControlWork;
    CAMCONTWK ControlWorkOld;
    CAMCONTWK ControlWorkOlder;

    int32_t level;
    CAMERALEVEL ModeLevel[16];
    ADJUSTLEVEL AdjustLevel[16];
}
CAMSYSWK;

typedef struct _OBJ_CAMERAMODE
{
    const char* name;
    void (__cdecl* fnCamera)(CAMSYSWK*, CAMERALEVEL*);
    int unk;
}
OBJ_CAMERAMODE;

typedef struct _OBJ_CAMERAADJUST
{
    const char* name;
    void (__cdecl* fnAdjust)(CAMSYSWK*, ADJUSTLEVEL*);
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

#define cameraSystemWork            DATA_ARY(CAMSYSWK        , 0x01DCFF40, [4])

#define cameraControlWork           DATA_ARY(CAMCONTWK*      , 0x01DD92B0, [4])

#define CameraMode                  DATA_ARY(OBJ_CAMERAMODE  , 0x008ABD38, [28])
#define CameraAdjust                DATA_ARY(OBJ_CAMERAADJUST, 0x008ABE88, [14])

#define camera_twp                  DATA_REF(TASKWK*         , 0x01A5A784)

/************************/
/*  Prototypes          */
/************************/
int     SetAdjustMode( int num, int adjust );

#endif/*_SA2B_CAMERA_H_*/
