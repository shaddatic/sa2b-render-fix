/*
*   SAMT for Sonic Adventure 2 (PC, 2012) - '/sonic/camera.h'
* 
*   Description:
*     The game's core camera system.
*/
#ifndef H_SA2B_CAMERA
#define H_SA2B_CAMERA

/********************************/
/*  Includes                    */
/********************************/
/****** Ninja ***********************************************************************************/
#include <samt/ninja/njcommon.h>    /* ninja common                                             */
#include <samt/ninja/njcamera.h>    /* ninja camera                                             */

EXTERN_START

/********************************/
/*  Opaque Types                */
/********************************/
/****** Task ************************************************************************************/
typedef struct task                 task;   /* task                                             */
typedef struct taskwk               taskwk; /* task work                                        */

/****** Camera **********************************************************************************/
typedef struct _CameraSystemWork    CameraSystemWork; /* camera system work                     */
typedef struct _OBJ_CAMERAPARAM     OBJ_CAMERAPARAM;  /* camera mode param                      */
typedef struct _OBJ_CAMERAPARAM     OBJ_ADJUSTPARAM;  /* camera adjust param                    */ 

/********************************/
/*  Types                       */
/********************************/
/****** Camera Funcs ****************************************************************************/
typedef void (*FN_CAMERA)(CameraSystemWork*, OBJ_CAMERAPARAM*); /* camera function              */
typedef void (*FN_ADJUST)(CameraSystemWork*, OBJ_ADJUSTPARAM*); /* adjust function              */

/********************************/
/*  Enums                       */
/********************************/
/****** Camera Number ***************************************************************************/
enum
{
    CAMERA_1,                       /* player 1                                                 */
    CAMERA_2,                       /* player 2                                                 */
    CAMERA_3,                       /* player 3                                                 */
    CAMERA_4,                       /* player 4                                                 */

    CAMERA_NUM,                     /* enum count                                               */
};

/****** Camera Level ****************************************************************************/
enum
{
    CAMLEV_NUM = 16,                /* enum count                                               */
};

/****** Camera Mode *****************************************************************************/
enum
{
    CAMMD_NONE,                     /* camera not active                                        */
    CAMMD_USER,                     /* camera using user function                               */
    CAMMD_FOLLOW,
    CAMMD_KNUKLES,
    CAMMD_EDITOR,
    CAMMD_EDITOR2,
    CAMMD_SNAPSHOT,
    CAMMD_KLAMATH,
    CAMMD_POINT,
    CAMMD_ASHLAND,
    CAMMD_FIX,
    CAMMD_LEAVE,
    CAMMD_SPACE,
    CAMMD_CARMEL,
    CAMMD_MOTION,
    CAMMD_BOSSINIT,
    CAMMD_BOSSPOINT,
    CAMMD_COLLISION,
    CAMMD_PSTONE,
    CAMMD_INIT,
    CAMMD_EASYSET,
    CAMMD_BOSSKLAMATH,
    CAMMD_GAKUGAKU,
    CAMMD_KNUCKLES_L,
    CAMMD_FIX2,
    CAMMD_PSTONE2,
    CAMMD_SS,
    CAMMD_COLLI_LR,

    CAMMD_NUM,                      /* enum count                                               */
};

/****** Camera Adjust ***************************************************************************/
enum
{
    CAMADJ_NONE,                    /* adjust not active                                        */
    CAMADJ_USER,                    /* adjust using user function                               */
    CAMADJ_HALF,
    CAMADJ_THREE1,
    CAMADJ_THREE2,
    CAMADJ_THREE3,
    CAMADJ_THREE4,
    CAMADJ_THREE5,
    CAMADJ_RELATIVE1,
    CAMADJ_RELATIVE2,
    CAMADJ_RELATIVE3,
    CAMADJ_RELATIVE4,
    CAMADJ_RELATIVE5,
    CAMADJ_RELATIVE6,

    CAMADJ_NUM,                     /* enum count                                               */
};

/****** Camera Target ***************************************************************************/
enum
{
    CAMTGT_NORMAL,                  /* vec = tgt - pos;     ang = vec                           */
    CAMTGT_ANGLE,                   /* dir = ang * dist;    tgt = pos + vec                     */
    CAMTGT_VECTOR,                  /* ang = vec;           tgt = pos + vec                     */
    CAMTGT_ANGLE2,                  /* dir = ang * dist;    pos = tgt - vec                     */
    CAMTGT_VECTOR2,                 /* ang = vec;           pos = tgt - vec                     */

    CAMTGT_NUM,                     /* enum count                                               */
};

/****** Camera Collision ************************************************************************/
enum
{
    CAMCOL_NONE,                    /* no collision calculations                                */
    CAMCOL_SPHERE,                  /* calculate as sphere                                      */
    CAMCOL_PLANE,                   /* calculate as plane, not implemented                      */
    CAMCOL_BLOCK,                   /* calculate as block                                       */

    CAMCOL_NUM,                     /* enum count                                               */
};

/****** Camera Entries **************************************************************************/
enum
{
    CAMENT_SET,                     /* entry set                                                */
    CAMENT_SET_1P,                  /* entry set, for player 1                                  */
    CAMENT_SET_2P,                  /* entry set, for player 2                                  */
    CAMENT_END,                     /* end of entry set buffer                                  */

    CAMENT_NUM,                     /* enum count                                               */
};

/********************************/
/*  Structures                  */
/********************************/
/****** Position Work **************************************************************************/
typedef struct _camposwk
{
    NJS_POINT3 pos;                 /* postion                                                  */
    NJS_ANGLE3 ang;                 /* angle                                                    */
    NJS_VECTOR vec;                 /* direction                                                */
    NJS_POINT3 tgt;                 /* target position                                          */
    NJS_VECTOR off;                 /* target offset from camera position                       */
    f32        dist;                /* target distance                                          */
}
camposwk;

/****** Control Work ****************************************************************************/
typedef struct _camcontwk
{
    i32         tgtmode;            /* targeting mode                                           */
    b32         colflag;            /* land collision flag                                      */
    i32         timer;              /* timer                                                    */
    NJS_POINT3  pos;                /* position                                                 */
    NJS_ANGLE3  ang;                /* angle                                                    */
    NJS_VECTOR  vec;                /* direction                                                */
    NJS_POINT3  tgt;                /* target position                                          */
    f32         dist;               /* target distance                                          */
}
camcontwk;

/****** Land Collision Work *********************************************************************/
typedef struct 
{
    NJS_POINT3  pos_curr;           /* last position                                            */
    NJS_POINT3  pos_next;           /* new position                                             */
    i32         attrmask;           /* land attribute mask                                      */
    f32         dist_max;           /* max distance                                             */
    NJS_POINT3  pos_hit;            /* land hit position (?)                                    */

    i8 gap2C[40];
    NJS_POINT3 field_54[2][5];
    i8 gapCC[58];
    NJS_POINT3 dir;
    i32 gap114[36];
    i32 field_138;
}
camcolwk;

/****** Land Collision Data *********************************************************************/
typedef struct
{
    NJS_POINT3* pos;                /* position                                                 */
    NJS_POINT3* scl;                /* scale                                                    */
    NJS_ANGLE3* ang;                /* angle                                                    */
    NJS_POINT3* tgt;                /* target position                                          */
}
camcoldata;

/****** Set Camera Entry ************************************************************************/
typedef struct _OBJ_CAMERAENTRY
{
    i32         mode;               /* camera mode                                              */
    i32         adjust;             /* camera adjust mode                                       */
    i32         priority;           /* priority level                                           */

    i32         coltype;            /* collision type                                           */
    NJS_POINT3  colpos;             /* collision position                                       */
    NJS_ANGLE3  colang;             /* collision angle                                          */
    NJS_POINT3  colscl;             /* collision scale                                          */

    NJS_POINT3  campos;             /* camera position                                          */
    NJS_ANGLE3  camang;             /* camera angle                                             */
    NJS_VECTOR  camvec;             /* camera direction                                         */

    Angle       ang;                /* perspective angle                                        */
    Angle       ang_spd;            /* perspective angle change                                 */

    i8 unk60[24];
    f32         distance;           /* distance from target                                     */
    f32         height;             /* height from ground (?)                                   */
    i8 unk80[24];
}
OBJ_CAMERAENTRY;

/****** Camera Param ****************************************************************************/
typedef struct _OBJ_CAMERAPARAM
{
    i32              mode;          /* camera or adjust mode                                    */
    i32              col;           /* collision type                                           */
    u32              timer;         /* timer                                                    */
    FN_CAMERA        fn;            /* camera or adjust function                                */
    OBJ_CAMERAENTRY* pEntry;        /* camera entry                                             */
    i8               work[256];     /* any work data                                            */
}
OBJ_CAMERAPARAM, OBJ_ADJUSTPARAM;

/****** Camera System ***************************************************************************/
typedef struct _CameraSystemWork
{
    Angle       ang;                /* current fov                                              */
    Angle       ang_tgt;            /* target fov                                               */
    Angle       ang_spd;            /* fov change speed                                         */

    b32         lr_flag;            /* free look flag                                           */
    b32         stop_flag;          /* player stop flag                                         */

    i32         padding;            /* unknown or unused                                        */
    camcolwk    colwk;              /* land collision work                                      */

    NJS_VECTOR  shake_vec;          /* shake vector                                             */
    b32         shake_flag;         /* shake on flag                                            */
    i32         shake_timer;        /* shake timer                                              */
    f32         shake_inten;        /* shake intensity                                          */

    NJS_CAMERA  njcam;              /* ninja camera                                             */

    camposwk    campos[3];          /* position + position history                              */

    i32             level;              /* current priority level                               */
    OBJ_CAMERAPARAM Camera[CAMLEV_NUM]; /* camera mode list                                     */
    OBJ_ADJUSTPARAM Adjust[CAMLEV_NUM]; /* camera adjust list                                   */
}
CameraSystemWork;

/****** Camera Functions ************************************************************************/
typedef struct _OBJ_CAMERAMODE
{
    c7*         name;               /* camera mode name                                         */
    FN_CAMERA   fnCamera;           /* camera function                                          */
    b32         unkflag;            /* unknown flag                                             */
}
OBJ_CAMERAMODE;

typedef struct _OBJ_CAMERAADJUST
{
    c7*         name;               /* camera adjust mode name                                  */
    FN_ADJUST   fnAdjust;           /* camera adjust function                                   */
}
OBJ_CAMERAADJUST;

/********************************/
/*  Variables                   */
/********************************/
/****** Camera Work *****************************************************************************/
#define cameraSystemWork            DATA_ARY(CameraSystemWork, 0x01DCFF40, [CAMERA_NUM])
#define cameraControlWork           DATA_REF(camcontwk       , 0x01DCFF00)

/****** Camera Data *****************************************************************************/
#define CameraMode                  DATA_ARY(OBJ_CAMERAMODE  , 0x008ABD38, [CAMMD_NUM])
#define CameraAdjust                DATA_ARY(OBJ_CAMERAADJUST, 0x008ABE88, [CAMADJ_NUM])
#define CameraEntry                 DATA_ARY(OBJ_CAMERAENTRY*, 0x015224E8, [CAMENT_NUM])

/****** Camera Info *****************************************************************************/
#define camera_tp                   DATA_REF(task*           , 0x01A5A77C)
#define camera_twp                  DATA_REF(taskwk*         , 0x01A5A784)
#define camera_count                DATA_REF(i32             , 0x01DD946C)
#define camera_num                  DATA_REF(i32             , 0x01DD92A0)
#define camera_pos                  DATA_ARY(camposwk*       , 0x01DD92B0, [CAMERA_NUM])

/********************************/
/*  Prototypes                  */
/********************************/
/************************************************************************************************/
/*
*   Camera Priority Level
*/
/****** Get *************************************************************************************/
/*
*   Description:
*     Get the current priority level of a player camera.
*
*   Parameters:
*     - pno         : player number
*
*   Returns:
*     Current camera priority level.
*/
i32     GetCameraLevel( i32 pno );
/*
*   Description:
*     Get the last active priority level of a player camera.
*
*   Parameters:
*     - pno         : player number
*
*   Returns:
*     The last active priority level of camera.
*/
i32     GetCameraLastLevel( i32 pno );
/*
*   Description:
*     Get an active camera level by searching backwards from a given level.
*
*   Parameters:
*     - pno         : player number
*     - lev         : priority level to search backward from
*
*   Returns:
*     Active camera level; or '-1' if given level is below '0'.
*/
i32     GetCameraActiveLevel( i32 pno, i32 lev );

/************************************************************************************************/
/*
*   Camera Perspective
*/
/****** Get *************************************************************************************/
/*
*   Description:
*     Get the current perspective angle of a player camera.
*
*   Parameters:
*     - pno         : player number
*
*   Returns:
*     Perspective angle of camera.
*/
Angle   GetCameraAngle( i32 pno );

/****** Set *************************************************************************************/
/*
*   Description:
*     Set a new target perspective angle of a player camera.
*
*   Notes:
*     - If a speed isn't given, it defaults to 90 degrees.
*
*   Parameters:
*     - pno         : player number
*     - ang         : perspective angle
*     - spd         : change speed                                                     [opt:0]
*/
void    SetCameraAngle( i32 pno, Angle ang, Angle spd );

/************************************************************************************************/
/*
*   Camera Mode
*/
/****** Get *************************************************************************************/
/*
*   Description:
*     Get the set camera mode at a given priority level.
*
*   Parameters:
*     - pno         : player number
*     - lev         : priority level
*
*   Returns:
*     Camera mode at priority level.
*/
i32     GetCameraMode( i32 pno, i32 lev );

/****** Set *************************************************************************************/
/*
*   Description:
*     Set a new camera mode at a set priority level.
*
*   Parameters:
*     - pno         : player number
*     - lev         : priority level
*     - mode        : camera mode                                                     [CAMMD_#]
*
*   Returns:
*     Camera parameter entry of new mode; or 'nullptr' on failure.
*/
OBJ_CAMERAPARAM* SetCameraMode( i32 pno, i32 lev, i32 mode );
/*
*   Description:
*     Set a new user camera mode at a set priority level.
*
*   Parameters:
*     - pno         : player number
*     - lev         : priority level
*     - fnCamera    : user camera function
* 
*   Returns:
*     Camera parameter entry of new mode; or 'nullptr' on failure.
*/
OBJ_CAMERAPARAM* SetCameraUserMode( i32 pno, i32 lev, void(*fnCamera)(CameraSystemWork*, OBJ_CAMERAPARAM*) );

/****** Set Next ********************************************************************************/
/*
*   Description:
*     Set a new camera mode, and increment the priority level by 1.
*
*   Parameters:
*     - pno         : player number
*     - mode        : camera mode                                                     [CAMMD_#]
*
*   Returns:
*     Camera parameter entry of new mode; or 'nullptr' on failure.
*/
OBJ_CAMERAPARAM* SetCameraNextMode( i32 pno, i32 mode );
/*
*   Description:
*     Set a new user camera mode, and increment the priority level by 1.
*
*   Parameters:
*     - pno         : player number
*     - fnCamera    : user camera function
* 
*   Returns:
*     Camera parameter entry of new mode; or 'nullptr' on failure.
*/
OBJ_CAMERAPARAM* SetCameraNextUserMode( i32 pno, void(*fnCamera)(CameraSystemWork*, OBJ_CAMERAPARAM*) );

/****** Set Collision ***************************************************************************/
/*
*   Description:
*     Set a new camera mode at a set priority level.
*
*   Parameters:
*     - pno         : player number
*     - lev         : priority level
*     - mode        : camera mode                                                     [CAMMD_#]
*     - col         : collision mode                                                 [CAMCOL_#]
*
*   Returns:
*     Camera parameter entry of new mode; or 'nullptr' on failure.
*/
OBJ_CAMERAPARAM* SetCameraModeAndCol( i32 pno, i32 lev, i32 mode, i32 col );

/****** Release *********************************************************************************/
/*
*   Description:
*     Release camera priority level slot, allowing another camera mode to take its place.
*
*   Parameters:
*     - pno         : player number
*     - lev         : priority level
*/
void    ReleaseCameraMode( i32 pno, i32 lev );

/************************************************************************************************/
/*
*   Camera Adjust Mode
*/
/****** Get *************************************************************************************/
/*
*   Description:
*     Get the set camera adjust mode at a given priority level.
*
*   Parameters:
*     - pno         : player number
*     - lev         : priority level
*
*   Returns:
*     Camera adjust mode at priority level.
*/
i32     GetAdjustMode( i32 pno, i32 lev );

/****** Set *************************************************************************************/
/*
*   Description:
*     Set a new camera adjust mode over the current priority level.
*
*   Parameters:
*     - pno         : player number
*     - lev         : priority level
*     - adjust      : camera adjust mode                                             [CAMADJ_#]
*
*   Returns:
*     'TRUE' on success; or 'FALSE' if level is higher than current camera priority level.
*/
b32     SetAdjustMode( i32 pno, i32 lev, i32 adjust );
/*
*   Description:
*     Set a new user camera adjust mode over the current priority level.
*
*   Parameters:
*     - pno         : player number
      - lev         : priority level
*     - fnAdjust    : user camera adjust function
*
*   Returns:
*     'TRUE' on success; or 'FALSE' if level is higher than current camera priority level.
*/
b32     SetAdjustUserMode( i32 pno, i32 lev, void(*fnAdjust)(CameraSystemWork*, OBJ_ADJUSTPARAM*) );

/************************************************************************************************/
/*
*   Camera Collision
*/
/****** Get *************************************************************************************/
/*
*   Description:
*     Get a camera collision mode.
*
*   Parameters:
*     - pno         : player number
*     - lev         : priority level
*
*   Returns:
*     Camera collision mode.
*/
i32     GetCameraCol( i32 pno, i32 lev );

/****** Set *************************************************************************************/
/*
*   Description:
*     Set a camera collision mode.
*
*   Parameters:
*     - pno         : player number
*     - lev         : priority level
*     - col         : collision mode
*/
void    SetCameraCol( i32 pno, i32 lev, i32 col );

/************************************************************************************************/
/*
*   Camera Entry
*/
/****** Get *************************************************************************************/
/*
*   Description:
*     Get a camera entry structure.
*
*   Parameters:
*     - pno         : player number
*     - lev         : priority level
*
*   Returns:
*     Camera entry; or 'nullptr' if none is set.
*/
OBJ_CAMERAENTRY* GetCameraEntry( i32 pno, i32 lev );

/****** Set *************************************************************************************/
/*
*   Description:
*     Set a camera entry structure.
*
*   Parameters:
*     - pno         : player number
*     - lev         : priority level
*     - pEntry      : camera entry                                                [opt:nullptr]
*/
void    SetCameraEntry( i32 pno, i32 lev, OBJ_CAMERAENTRY* pEntry );

/************************************************************************************************/
/*
*   Camera Shake
*/
/****** Set *************************************************************************************/
/*
*   Description:
*     Set the camera shake vector.
*
*   Parameters:
*     - pno         : player number
*     - v           : vector
*/
void    SetCameraShakeVec( i32 pno, const NJS_VECTOR* v );
/*
*   Description:
*     Set the camera shake effect, with intensity and timer.
*
*   Parameters:
*     - pno         : player number
*     - inten       : shake intensity
*     - timer       : shake timer
*/
void    SetCameraShake( i32 pno, f32 inten, i32 timer );

/****** Stop ************************************************************************************/
/*
*   Description:
*     Stop the camera shake effect.
*
*   Notes:
*     - Also resets the shake vector.
*
*   Parameters:
*     - pno         : player number
*/
void    StopCameraShake( i32 pno );

#ifdef SAMT_INCL_FUNCPTRS

/********************************/
/*  Function Pointers           */
/********************************/
/****** Usercall Pointers ***********************************************************************/
#define SetCameraMode_p                     ((void*)0x004EBB40) /* EAX(EAX, STK, STK)           */
#define SetCameraUserMode_p                 ((void*)0x004EBC50) /* EAX(EAX, ESI, STK)           */
#define SetCameraNextMode_p                 ((void*)0x004EBBE0) /* EAX(EAX, EDX)                */
#define SetCameraNextUserMode_p             ((void*)0x004EBCB0) /* EAX(EAX, EDX)                */
#define ReleaseCameraMode_p                 ((void*)0x004EBD30) /* ###(ECX, EAX)                */
#define SetAdjustMode_p                     ((void*)0x004EBCD0) /* EAX(ECX, EAX, EDI)           */

#endif/*SAMT_INCL_FUNCPTRS*/

EXTERN_END

#endif/*H_SA2B_CAMERA*/
