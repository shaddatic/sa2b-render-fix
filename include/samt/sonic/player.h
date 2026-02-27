/*
*   SAMT for Sonic Adventure 2 (PC, 2012) - '/sonic/player.h'
*
*   ~~ Under Construction ~~
*
*   Description:
*     Player functions and variables.
*/
#ifndef H_SA2B_PLAYER
#define H_SA2B_PLAYER

/********************************/
/*  Includes                    */
/********************************/
/****** Ninja ***********************************************************************************/
#include <samt/ninja/ninja.h>       /* ninja                                                    */

/****** Game ************************************************************************************/
#include <samt/sonic/shadow.h>      /* shadowwk                                                 */

/****** Task ************************************************************************************/
#include <samt/sonic/task/taskexec.h> /* task exec                                              */

/********************************/
/*  Opaque Types                */
/********************************/
/****** Task ************************************************************************************/
typedef struct task                 task;     /* task                                           */
typedef struct taskwk               taskwk;   /* task work                                      */
typedef struct motionwk             motionwk; /* motion work                                    */

/****** Path ************************************************************************************/
typedef struct pathtag              PATH_TAG; /* path tag                                       */

EXTERN_START

/********************************/
/*  Constants                   */
/********************************/
/************************************************************************************************/
/*
*   Equipment Flags
*/
/****** Sonic ***********************************************************************************/
#define EQUIP_SONIC_SHOES           (0x00000001) /* light dash shoes                            */
#define EQUIP_SONIC_SPARKLE         (0x00000002) /* ancient light                               */
#define EQUIP_SONIC_MAGICWRIST      (0x00000004) /* magic hands                                 */
#define EQUIP_SONIC_FLAMERING       (0x00000008) /* flame ring                                  */
#define EQUIP_SONIC_RUBBERUNIT      (0x00000010) /* bounce bracelet                             */
#define EQUIP_SONIC_MELODY          (0x00000020) /* mystic melody                               */

/****** Miles/Tornado ***************************************************************************/
#define EQUIP_MILES_BOOSTER         (0x00000040) /* hover jets                                  */
#define EQUIP_MILES_HYPERCANNON     (0x00000080) /* strong bullet                               */
#define EQUIP_MILES_LASERBALSTER    (0x00000100) /* strong homing                               */
#define EQUIP_MILES_MELODY          (0x00000200) /* mystic melody                               */

/****** Knuckles ********************************************************************************/
#define EQUIP_KNUCKLES_CLAW         (0x00000400) /* shovel claw                                 */
#define EQUIP_KNUCKLES_SUNGLASS     (0x00000800) /* sunglasses                                  */
#define EQUIP_KNUCKLES_GROVES       (0x00001000) /* hammer gloves                               */
#define EQUIP_KNUCKLES_AIR          (0x00002000) /* air necklace                                */
#define EQUIP_KNUCKLES_MELODY       (0x00004000) /* mystic melody                               */

/****** Super Sonic/Shadow **********************************************************************/
#define EQUIP_SUPER                 (0x00008000) /* super form                                  */

/****** Shadow **********************************************************************************/
#define EQUIP_SHADOW_SHOES          (0x00010000) /* flame ring                                  */
#define EQUIP_SHADOW_SPARKLE        (0x00020000) /* ancient light                               */
#define EQUIP_SHADOW_FLAMERING      (0x00040000) /* flame ring                                  */
#define EQUIP_SHADOW_MELODY         (0x00080000) /* mystic melody                               */

/****** Eggman/Egg Walker ***********************************************************************/
#define EQUIP_EGGMAN_JETENGINE      (0x00100000) /* hover jets                                  */
#define EQUIP_EGGMAN_BAZOOKA        (0x00200000) /* strong bullet                               */
#define EQUIP_EGGMAN_POWERGUN       (0x00400000) /* strong homing                               */
#define EQUIP_EGGMAN_EXTRASHIELD    (0x00800000) /* sheild                                      */
#define EQUIP_EGGMAN_MELODY         (0x01000000) /* mystic melody                               */

/****** Rouge ***********************************************************************************/
#define EQUIP_ROUGE_NAILS           (0x02000000) /* pick nails                                  */
#define EQUIP_ROUGE_SCOPE           (0x04000000) /* treasure scope                              */
#define EQUIP_ROUGE_BOOTS           (0x08000000) /* iron boots                                  */
#define EQUIP_ROUGE_MELODY          (0x10000000) /* mystic melody                               */

/************************************************************************************************/
/*
*   Killcolli Flags
*/
/****** Player flags ****************************************************************************/
#define KILLCOL_SONIC               (0x00000001) /* kill sonic                                  */
#define KILLCOL_SHADOW              (0x00000002) /* kill shadow                                 */
#define KILLCOL_MILES               (0x00000004) /* kill miles                                  */
#define KILLCOL_EGGMAN              (0x00000008) /* kill eggman                                 */
#define KILLCOL_KNUCKLES            (0x00000010) /* kill knuckles                               */
#define KILLCOL_ROUGE               (0x00000020) /* kill rouge                                  */
#define KILLCOL_TAILSWALKER         (0x00000040) /* kill tails walker                           */
#define KILLCOL_EGGWALKER           (0x00000080) /* kill egg Walker                             */
#define KILLCOL_WATER               (0x02000000) /* splash on impact                            */
#define KILLCOL_DRAW                (0x80000000) /* display collision as chunk object           */

/********************************/
/*  Enums                       */
/********************************/
/****** Player Number ***************************************************************************/
enum
{
    PLAYER_1,                       /* player 1                                                 */
    PLAYER_2,                       /* player 2                                                 */
    PLAYER_3,                       /* player 3                                                 */
    PLAYER_4,                       /* player 4                                                 */
    PLAYER_5,                       /* player 5                                                 */
    PLAYER_6,                       /* player 6                                                 */
    PLAYER_7,                       /* player 7                                                 */
    PLAYER_8,                       /* player 8                                                 */

    NB_PLAYER,                      /* enum count                                               */
};

/****** Player Character ************************************************************************/
enum
{
    PLNO_SONIC,                     /* sonic the hedgehog                                       */
    PLNO_SHADOW,                    /* shadow the hedgehog                                      */
    PLNO_MILES,                     /* miles "tails" prower                                     */
    PLNO_EGGMAN,                    /* eggman                                                   */
    PLNO_KNUCKLES,                  /* knuckles the echidna                                     */
    PLNO_ROUGE,                     /* rouge the bat                                            */
    PLNO_TAILS_WALKER,              /* tails walker                                             */
    PLNO_EGG_WALKER,                /* egg walker                                               */
    PLNO_AMY,                       /* amy rose         : basechar = sonic                      */
    PLNO_SUPER_SONIC,               /* super sonic                                              */
    PLNO_SUPER_SHADOW,              /* super shadow                                             */
    PLNO_DUMMY,                     /* dummy                                                    */
    PLNO_METAL_SONIC,               /* metal sonic      : basechar = shadow                     */
    PLNO_CHAO_WALKER,               /* chao walker      : basechar = tails walker               */
    PLNO_DARK_WALKER,               /* dark walker      : basechar = egg walker                 */
    PLNO_TICAL,                     /* tikal            : basechar = knuckles                   */
    PLNO_CHAOS0,                    /* chaos 0          : basechar = rouge                      */

    NB_PLNO,                        /* enum count                                               */
};

/****** Player Objects **************************************************************************/
enum
{
    PLOBJ_TABLE_END = -1,           /* end of table                                             */

    NUMBER_PLOBJ = 532,             /* enum count                                               */
};

/****** Player Motions **************************************************************************/
enum
{
    PLMOT_TABLE_END = -1,           /* end of table                                             */

    PLMOT_WAIT,
    PLMOT_WAIT1,
    PLMOT_WAIT2,
    PLMOT_WAIT3,
    PLMOT_WAITF,
    PLMOT_WAITB,
    PLMOT_WALK,
    PLMOT_JOG,
    PLMOT_RUN,
    PLMOT_RUSH,
    PLMOT_DASH,
    PLMOT_STARTSPIN,
    PLMOT_SPINDASH,
    PLMOT_LAUNCH,
    PLMOT_LAUNCH_FALL,
    PLMOT_FALL,
    PLMOT_LAND,
    PLMOT_LAND2,
    PLMOT_STOP,
    PLMOT_PUSH,
    PLMOT_PUSH2,
    PLMOT_DAMAGE,
    PLMOT_DAMAGE2,
    PLMOT_ROTATEFLY,
    PLMOT_CRASH,
    PLMOT_CRASH2,
    PLMOT_ENDSPIN,
    PLMOT_TURN,
    PLMOT_SLIDE,
    PLMOT_BACKSLIDE,
    PLMOT_BALL,
    PLMOT_PICK,
    PLMOT_HRUN,
    PLMOT_HSTOP,
    PLMOT_HTURN,
    PLMOT_HWAIT,
    PLMOT_HWAITF,
    PLMOT_HWAITB,
    PLMOT_HWALK,
    PLMOT_TUMAZUKI,
    PLMOT_PULL,
    PLMOT_SHAKE,
    PLMOT_EGGSHAKE,
    PLMOT_TOUCH,
    PLMOT_TOUCH1,
    PLMOT_HUP0,
    PLMOT_HUP1,
    PLMOT_HUP2,
    PLMOT_HUP3,
    PLMOT_THROW0,
    PLMOT_THROW1,
    PLMOT_JUMPTHROW0,
    PLMOT_JUMPTHROW1,
    PLMOT_PUT,
    PLMOT_FINISHPOSE,
    PLMOT_CAPTURED,
    PLMOT_BREATHE,
    PLMOT_DOZAEMON,
    PLMOT_DOZAEMON2,
    PLMOT_DIE,
    PLMOT_DIE2,
    PLMOT_OTTOTO,
    PLMOT_CATCHEDGE,
    PLMOT_CLIMBEDGE,
    PLMOT_CLIMBEDGE2,
    PLMOT_JUMP,
    PLMOT_JUMP1,
    PLMOT_JUMP2,
    PLMOT_JUMP3,
    PLMOT_MOTENAI0,
    PLMOT_MOTENAI1,
    PLMOT_MOTENAI2,
    PLMOT_WHISTLE,
    PLMOT_CHAOTHROW,
    PLMOT_STEPJUMP,
    PLMOT_HUNG,
    PLMOT_ROCKET,
    PLMOT_ROCKET2,
    PLMOT_CHAONADE,
    PLMOT_UPROOT,
    PLMOT_SURPRISE0,
    PLMOT_SURPRISE1,
    PLMOT_FLUTE,
    PLMOT_NORESPEDESTAL,
    PLMOT_LOOKPEDESTAL,
    PLMOT_LOSINGPOSE,
    PLMOT_GOTLEVELUPITEM,
    PLMOT_END,

    NUMBER_PLMOT = 300,             /* enum count                                               */
};

/****** Looking Mode ****************************************************************************/
enum
{
    LOOK_MODE_NORMAL,               /* looking forward                                          */
    LOOK_MODE_OBJECT,               /* looking at task                                          */
    LOOK_MODE_POINT,                /* looking at set point                                     */
    LOOK_MODE_ANGLE,                /* looking at relative angle                                */
};

/********************************/
/*  Structures                  */
/********************************/
/****** Killcolli *******************************************************************************/
typedef struct 
{
    i32         flag;       /* collision flag                                                   */
    NJS_OBJECT* object;     /* collision object                                                 */
}
PL_KILLCOLLI;

/****** Player Action ***************************************************************************/
typedef struct
{
    u16     actnum;
    u16     objnum;
    u16     mtnmode;
    u16     next;
    f32     frame;
    f32     racio;
}
PL_ACTION;

/****** Motion Work *****************************************************************************/
typedef struct mtnwk
{
    i16         mtnmode;
    u16         reqaction;
    u16         action;
    u16         lastaction;
    u16         nextaction;
    u16         acttimer;
    i16         flag;
    f32         nframe;
    f32         last_nframe;
    f32         start_frame;
    f32*        spdp;
    f32*        rspdp;
    PL_ACTION*  plactptr;
    NJS_MOTION* plmtnptr;
}
mtnwk;

/****** CSTS ************************************************************************************/
typedef struct csts
{
    f32         radius;
    NJS_POINT3  campos;
    NJS_POINT3  spd;
    NJS_POINT3  tnorm;
    u16         find_count;
    u16         selected_nmb;
    f32         yt;
    f32         yb;
    Angle       angx;
    Angle       angz;
    NJS_POINT3  normal;
    NJS_POINT3  normal2;
    NJS_POINT3  onpoly;
    NJS_POINT3  pshbk;
    NJS_POINT3  anaspdh;
    NJS_POINT3  anaspdv;
}
CSTS;

/****** Land Position ***************************************************************************/
typedef struct 
{
    f32     x;
    f32     y;
    f32     z;
    f32     r;
    f32     d;
    f32     h;
    Angle   angy_dif;
    Angle   angy_aim;
}
PL_LANDPOSI;

/****** Player Param ****************************************************************************/
typedef struct player_parameter
{
    i32     jump2_timer;
    f32     pos_error;
    f32     lim_h_spd;
    f32     lim_v_spd;
    f32     max_x_spd;
    f32     max_psh_spd;
    f32     jmp_y_spd;
    f32     nocon_speed;
    f32     slide_speed;
    f32     jog_speed;
    f32     run_speed;
    f32     rush_speed;
    f32     crash_speed;
    f32     dash_speed;
    f32     jmp_addit;
    f32     run_accel;
    f32     air_accel;
    f32     slow_down;
    f32     run_break;
    f32     air_break;
    f32     air_resist_air;
    f32     air_resist;
    f32     air_resist_y;
    f32     air_resist_z;
    f32     grd_frict;
    f32     grd_frict_z;
    f32     lim_frict;
    f32     rat_bound;
    f32     rad;
    f32     height;
    f32     weight;
    f32     eyes_height;
    f32     center_height;
}
player_parameter;

typedef struct // To be moved
{
    void*   texp;
    i32     address_u;
    i32     address_v;
    i32     tes5;
    i32     min_filter;
    i32     mag_filter;
    i32     bank;
    i32     unk;
}
TEXTURE_INFO;

/****** Player Work *****************************************************************************/
typedef struct lookwk
{
    i8          mode;               /* looking mode                                             */
    i32         timer;              /* looking time                                             */
    Angle3      ang;                /* look at angle                                            */
    NJS_POINT3  pos;                /* look at position or offset                               */
    NJS_VECTOR  vec;                /* look at vector, unused                                   */
    task*       obj;                /* look at task                                             */
}
lookwk;

typedef struct stencilwk
{
    TEXTURE_INFO texture;
    void*        texp;
    NJS_MATRIX   mat;
}
stencilwk;

#define GET_PLAYERWK(tp)    ((playerwk*)tp->awp)

typedef struct playerwk
{
    i8      player;                 // Player Number
    i8      basechar;               // Base Character Number
    i8      costume;                // Costume Number
    i8      character;              // Character Number

    i8      action_list[8];
    i8      action_num;
    i8      action_sel;             // Currently selected action index (with Y)
    i8      action_last;            // ? Set on pressing action

    i16     item;                   // Powerups
    i16     jumptimer;
    i16     nocontimer;             // No Control Timer
    i16     breathtimer;
    i16     waittimer;
    i16     confusetimer;
    i16     flag;
    i16     island_num;
    i16     path_point;             // ? More research needed
    i32     equipment;

    i32     unki_0;                 // ? Related to being grabbed
    Angle   lean;                   // Body lean angle
    f32     hpos;                   // 1D Position along a path
    f32     dotp;                   // Vertical dot product
    f32     unkf_1;                 // ? Animation speed related
    f32     unkf_2;                 // ? Seemingly random
    f32     unkf_3;                 // ? Changing at all breaks game
    f32     rspd;                   // Running speed

    f32     hp;                     // Health, used for walkers and bossfights

    NJS_VECTOR eff;
    NJS_VECTOR acc;
    NJS_VECTOR spd;
    NJS_VECTOR wall_normal;
    NJS_VECTOR floor_normal;

    u32     attr;
    u32     last_attr;

    CSTS*   cstsp;
    task*   htp;                    // Holding Task Pointer
    task*   nhtp;                   // Next Holding Task Pointer
    task*   ttp;                    // Target Task Pointer
    task*   mlotp;                  // Mobile Land Object Task Pointer 
    task*   sctp;                   // Stand Colli Task Pointer
    i32     unki_3;                 // Seemingly unused
    i32     unki_4;                 // ^

    NJS_OBJECT*  lclop;
    PL_LANDPOSI* island_list;

    PATH_TAG*    path_tag;

    NJS_MOTION** motion_list;

    player_parameter p;

    lookwk      look;
    mtnwk       m;

    shadowwk    shadow;
    shadowwk    front_shadow;

    NJS_POINT3  righthand_pos;
    NJS_POINT3  lefthand_pos;
    NJS_POINT3  rightfoot_pos;
    NJS_POINT3  leftfoot_pos;
    NJS_POINT3  user0_pos;          // Usually the head
    NJS_POINT3  user1_pos;          // ^
    NJS_POINT3  root_pos;
    NJS_POINT3  tails_pos;
    NJS_POINT3  bazooka_pos;
    NJS_POINT3  powergun_pos;
    NJS_POINT3  extrashield_pos;

    NJS_VECTOR  righthand_inv;
    NJS_VECTOR  lefthand_inv;

    NJS_VECTOR  righthand_vec;
    NJS_VECTOR  lefthand_vec;
    NJS_VECTOR  rightfoot_vec;
    NJS_VECTOR  leftfoot_vec;
    NJS_VECTOR  user0_vec;           // Usually the head
    NJS_VECTOR  user1_vec;           // ^
    NJS_VECTOR  root_vec;
    NJS_VECTOR  tails_vec;
    NJS_VECTOR  bazooka_vec;
    NJS_VECTOR  powergun_vec;
    NJS_VECTOR  extrashield_vec;

    stencilwk   stencil;
}
playerwk;

/****** Player Files ****************************************************************************/
typedef struct playerobj
{
    i32             idx;            /* list index                                               */
    NJS_CNK_OBJECT* obj;            /* object                                                   */
}
playerobj;

typedef struct playermot
{
    i16         idx;                /* list index                                               */
    i16         num;                /* node number                                              */
    NJS_MOTION* mot;                /* motion                                                   */
}
playermot;

/********************************/
/*  Variables                   */
/********************************/
/****** Player Character ************************************************************************/
#define ulPlayer1                   DATA_REF(u32        , 0x01934B80)
#define ulPlayer2                   DATA_REF(u32        , 0x01934BE4)

/****** Object/Motion List **********************************************************************/
#define plobjects                   DATA_ARY(playerobj  , 0x01DE9620, [NUMBER_PLOBJ])
#define plmotions                   DATA_ARY(playermot  , 0x01DEA700, [NUMBER_PLMOT])

/****** Player Work *****************************************************************************/
#define playermwp                   DATA_ARY(motionwk*  , 0x01DE95E0, [8])
#define playerpwp                   DATA_ARY(playerwk*  , 0x01DE9600, [8])
#define playertwp                   DATA_ARY(taskwk*    , 0x01DEA6C0, [8])
#define playertp                    DATA_ARY(task*      , 0x01DEA6E0, [8])

/****** Save Task Functions *********************************************************************/
#define pExecSave                   DATA_ARY(task_exec  , 0x019458F0, [8])
#define pDispSave                   DATA_ARY(task_exec  , 0x01945960, [8])
#define pDispDelySave               DATA_ARY(task_exec  , 0x01945920, [8])
#define pDispSortSave               DATA_ARY(task_exec  , 0x019458D0, [8])
#define pDispLateSave               DATA_ARY(task_exec  , 0x01945940, [8])
#define pDispLastSave               DATA_ARY(task_exec  , 0x019458B0, [8])
#define pDispShadSave               DATA_ARY(task_exec  , 0x01945980, [8])

/****** Position History ************************************************************************/
#define pos_frame                   DATA_ARY(u8         , 0x01945910, [8])
#define pos_history                 DATA_REF(NJS_POINT3*, 0x01A5A234) // [8][256]
#define ang_history                 DATA_REF(NJS_ANGLE3*, 0x01A5A238) // [8][256]

/********************************/
/*  Prototypes                  */
/********************************/
/****** Get Work ********************************************************************************/
/*
*   Description:
*     Get player work of a player.
*
*   Parameters:
*     - pno         : player number
*
*   Returns:
*     Player work of player numher; or 'nullptr' if player does not exist.
*/
playerwk* GetPlayerWorkPointer( i32 pno );

/****** Disable/Hide ****************************************************************************/
/*
*   Description:
*     Disable a player task by nulling their executor & displayer.
*
*   Parameters:
*     - pno         : player number
*/
void    PlayerDisable( i32 pno );
/*
*   Description:
*     Re-enable a player task by restoring their executor & displayer.
*
*   Parameters:
*     - pno         : player number
*/
void    PlayerEnable( i32 pno );

/****** Set Pos *********************************************************************************/
/*
*   Description:
*     Set player position.
*
*   Parameters:
*     - pno         : player number
*     - x,y,z       : position
*/
void    SetPositionP( i32 pno, f32 x, f32 y, f32 z );
/*
*   Description:
*     Set player velocity.
*
*   Parameters:
*     - pno         : player number
*     - x,y,z       : vector
*/
void    SetVelocityP( i32 pno, f32 x, f32 y, f32 z );
/*
*   Description:
*     Set player acceleration.
*
*   Parameters:
*     - pno         : player number
*     - x,y,z       : vector
*/
void    SetAccelerationP( i32 pno, f32 x, f32 y, f32 z );

/****** Powerup *********************************************************************************/
/*
*   Description:
*     Give a player the speed up powerup.
*
*   Parameters:
*     - pno         : player number
*/
void    GetSpeedUpP( i32 pno );
/*
*   Description:
*     Give a player the thunder barrier powerup
*
*   Parameters:
*     - pno         : player number
*/
void    GetThunderBarrierP( i32 pno );
/*
*   Description:
*     Give a player the damage barrier powerup
*
*   Parameters:
*     - pno         : player number
*/
void    GetBarrierP( i32 pno );
/*
*   Description:
*     Give a player the invincibility powerup
*
*   Parameters:
*     - pno         : player number
*/
void    GetInvincibleBodyForAMomentP( i32 pno );

/****** Holding *********************************************************************************/
/*
*   Description:
*     Set a player to hold a task object.
*
*   Parameters:
*     - pno         : player number
*     - htp         : holding task
*/
void    HoldTaskP( i32 pno, task* htp );
/*
*   Description:
*     Set player to drop currently held task.
*
*   Parameters:
*     - pno         : player number
*/
void    StopHoldingTaskP( i32 pno );

/****** Player Looking **************************************************************************/
/*
*   Description:
*     Set a player to look at a task object, with position offset.
*
*   Notes:
*     - In order for the player to look at a task, the task must also have taskwk data.
*
*   Parameters:
*     - pno         : player number
*     - ttp         : looking target task
*     - offset      : position offset
*     - tm          : number of frames to look for
*/
void    SetLookingTaskP( i32 pno, task* ttp, const NJS_POINT3* offset, i32 tm );
/*
*   Description:
*     Set a player to look at a set position.
*
*   Parameters:
*     - pno         : player number
*     - point       : looking target point
*     - tm          : number of frames to look for
*/
void    SetLookingPointP( i32 pno, const NJS_POINT3* point, i32 tm );
/*
*   Description:
*     Set a player to look at a relative angle.
*
*   Parameters:
*     - pno         : player number
*     - ang         : looking angle
*     - tm          : number of frames to look for
*/
void    SetLookingAngleP( i32 pno, const Angle ang[3], i32 tm );
/*
*   Description:
*     Stop looking for a player.
*
*   Parameters:
*     - pno         : player number
*/
void    CancelLookingAtP( i32 pno );

/****** Misc ************************************************************************************/
/*
*   Description:
*     Get the current number of active players.
*/
i32     CountCharacters( void );
/*
*   Description:
*     Get the player position from this frame, or any previous frame up to 255.
*
*   Parameters:
*     - pno         : player number
*     - frame       : history frame, 0 meaning this frame
*     - pos         : position output                                             [opt:nullptr]
*     - ang         : angle output                                                [opt:nullptr]
*
*   Returns:
*     'TRUE' if the player exists; or 'FALSE' if they do not.
*/
b32     GetPlayerPosition( i32 pno, u8 frame, NJS_POINT3* pos, NJS_ANGLE3* ang );
/*
*   Description:
*     Get player number of task.
*
*   Parameters:
*     - tp          : task
*
*   Returns:
*     Player number; or '-1' if task is not a player.
*/
i32     GetTaskPlayerNumber( task* tp );
/*
*   Description:
*     Get player number of task.
*/
b32     IsThisTaskPlayer( task* tp );
/*
*   Description:
*     Get the nearest player number to a point.
*
*   Parameters:
*     pos           : position
*
*   Returns:
*     Nearest player number to point.
*/
i32     GetTheNearestPlayerNumber( const NJS_POINT3* pos );
/*
*   Description:
*     Get player number of rival player.
*
*   Description:
*     - pno         : player number to get rival of
*
*   Returns:
*     Rival player number; or '-1' if no rival.
*/
i32     GetRivalPlayerNumber( i32 pno );

#ifdef SAMT_INCL_FUNCPTRS

/********************************/
/*  Function Pointers           */
/********************************/
/****** Function Pointers ***********************************************************************/
#define CountCharacters_p                   FUNC_PTR(i32, __cdecl, (void), 0x0046DD60)

/****** Usercall Pointers ***********************************************************************/
#define SetVelocityP_p                      ((void*)0x0046C020) /* ###(ECX, STK, STK, STK)      */
#define SetPositionP_p                      ((void*)0x0046C6D0) /* ###(EAX, STK, STK, STK)      */
#define SetAccelerationP_p                  ((void*)0x0046C6B0) /* ###(EAX, STK, STK, STK)      */
#define GetTaskPlayerNumber_p               ((void*)0x0046DCC0) /* EAX(EAX)                     */
#define GetTheNearestPlayerNumber_p         ((void*)0x0046DDC0) /* EAX(EDI)                     */
#define GetRivalPlayerNumber_p              ((void*)0x0046DE60) /* EAX(EDX)                     */
#define GetSpeedUpP_p                       ((void*)0x0046E120) /* ###(EAX)                     */
#define GetThunderBarrierP_p                ((void*)0x0046E180) /* ###(EAX)                     */
#define GetBarrierP_p                       ((void*)0x0046E2E0) /* ###(EAX)                     */
#define GetInvincibleBodyForAMomentP_p      ((void*)0x0046E440) /* ###(EAX)                     */
#define HoldTaskP_p                         ((void*)0x0046E5B0) /* ###(ECX, STK)                */

/****** Inlined Pointers ************************************************************************/
#define StopHoldingTaskP_inl_p              ((void*)0x0046E5E0) /* ###(EAX, EDX)                */

#endif/*SAMT_INCL_FUNCPTRS*/

EXTERN_END

#endif/*H_SA2B_PLAYER*/
