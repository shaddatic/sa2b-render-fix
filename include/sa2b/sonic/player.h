/*
*   Sonic Adventure Mod Tools (SA2B) - '/sonic/player.h'
*
*   ~~ Under Construction ~~
*   Contains structs and functions related to player and characters data
*
*   Contributors:
*     - SEGA - Sonic Team,
*     - Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC
*/
#ifndef _SA2B_PLAYER_H_
#define _SA2B_PLAYER_H_

/************************/
/*  Includes            */
/************************/
/** Ninja **/
#include <sa2b/ninja/ninja.h>

/** Utility **/
#include <sa2b/util/anyobj.h>

/** Source **/
#include <sa2b/sonic/shadow.h>

/************************/
/*  Abstract Types      */
/************************/
/** Task **/
typedef struct task         task;
typedef struct taskwk       taskwk;
typedef struct motionwk     motionwk;

/** Path **/
typedef struct pathtag      PATH_TAG;

/************************/
/*  Typedefs            */
/************************/
typedef void(__cdecl* task_exec)(task*);

/************************/
/*  Constants           */
/************************/
/****** Equipment Flags *****************************************************/
/** Sonic **/
#define EQUIP_SONIC_SHOES           (0x00000001)
#define EQUIP_SONIC_SPARKLE         (0x00000002)
#define EQUIP_SONIC_MAGICWRIST      (0x00000004)
#define EQUIP_SONIC_FLAMERING       (0x00000008)
#define EQUIP_SONIC_RUBBERUNIT      (0x00000010)
#define EQUIP_SONIC_MELODY          (0x00000020)

/** Miles/Tornado **/
#define EQUIP_MILES_BOOSTER         (0x00000040)
#define EQUIP_MILES_HYPERCANNON     (0x00000080)
#define EQUIP_MILES_LASERBALSTER    (0x00000100)
#define EQUIP_MILES_MELODY          (0x00000200)

/** Knuckles **/
#define EQUIP_KNUCKLES_CLAW         (0x00000400)
#define EQUIP_KNUCKLES_SUNGLASS     (0x00000800)
#define EQUIP_KNUCKLES_GROVES       (0x00001000)
#define EQUIP_KNUCKLES_AIR          (0x00002000)
#define EQUIP_KNUCKLES_MELODY       (0x00004000)

/** ???? **/
#define EQUIP_SUPERSONIC            (0x00008000)

/** Shadow **/
#define EQUIP_SHADOW_SHOES          (0x00010000)
#define EQUIP_SHADOW_SPARKLE        (0x00020000)
#define EQUIP_SHADOW_FLAMERING      (0x00040000)
#define EQUIP_SHADOW_MELODY         (0x00080000)

/** Eggman/Eggwalker **/
#define EQUIP_EGGMAN_JETENGINE      (0x00100000)
#define EQUIP_EGGMAN_BAZOOKA        (0x00200000)
#define EQUIP_EGGMAN_POWERGUN       (0x00400000)
#define EQUIP_EGGMAN_EXTRASHIELD    (0x00800000)
#define EQUIP_EGGMAN_MELODY         (0x01000000)

/** Rouge **/
#define EQUIP_ROUGE_NAILS           (0x02000000)
#define EQUIP_ROUGE_SCOPE           (0x04000000)
#define EQUIP_ROUGE_BOOTS           (0x08000000)
#define EQUIP_ROUGE_MELODY          (0x10000000)

/****** Killcolli Flags *****************************************************/
/** Player flags **/
#define KILLCOL_PL_SONIC            (0x00000001) /* Kill Sonic              */
#define KILLCOL_PL_SHADOW           (0x00000002) /* Kill Shadow             */
#define KILLCOL_PL_MILES            (0x00000004) /* Kill Miles              */
#define KILLCOL_PL_EGGMAN           (0x00000008) /* Kill Eggman             */
#define KILLCOL_PL_KNUCKLES         (0x00000010) /* Kill Knuckles           */
#define KILLCOL_PL_ROUGE            (0x00000020) /* Kill Rouge              */
#define KILLCOL_PL_TORNADO          (0x00000040) /* Kill Tornado Walker     */
#define KILLCOL_PL_EGGWALKER        (0x00000080) /* Kill Egg Walker         */

/** Debug **/
#define KILLCOL_DEBUG_DISPLAY       (0x80000000) /* Chunk format & display  */

/************************/
/*  Enums               */
/************************/
enum
{
    PLAYER_1,
    PLAYER_2
};

enum
{
    PLNO_SONIC,
    PLNO_SHADOW,
    PLNO_MILES,
    PLNO_EGGMAN,
    PLNO_KNUCKLES,
    PLNO_ROUGE,
    PLNO_TAILS_WALKER,
    PLNO_EGG_WALKER,
    PLNO_AMY,
    PLNO_SUPER_SONIC,
    PLNO_SUPER_SHADOW,
    PLNO_DUMMY,
    PLNO_METAL_SONIC,
    PLNO_CHAO_WALKER,
    PLNO_DARK_WALKER,
    PLNO_TICAL,
    PLNO_CHAOS0,
    NB_PLNO,
};

/************************/
/*  Structures          */
/************************/
typedef struct 
{
    int32_t     flag;
    ANY_OBJECT* object;
}
PL_KILLCOLLI;

typedef struct
{
    int16_t   actnum;
    uint16_t  objnum;
    int16_t   mtnmode;
    int16_t   next;
    f32       frame;
    f32       racio;
}
PL_ACTION;

typedef struct mtnjvwk
{
    __int16 mtnmode;
    __int16 Next;
    __int16 mtnnum;
    __int16 Animation3;
    __int16 field_8;
    __int16 acttimer;
    __int16 field_C;
    char field_E;
    char field_F;
    float nframe;
    float field_14;
    float field_18;
    char field_1C;
    char field_1D;
    char field_1E;
    char field_1F;
    char field_20;
    char field_21;
    char field_22;
    char field_23;
    PL_ACTION* plactptr;
    NJS_MOTION* plmtnptr;
}
MOTION_JVWK;

typedef struct csts
{
    f32        radius;
    NJS_POINT3 campos;
    NJS_POINT3 spd;
    NJS_POINT3 tnorm;
    uint16_t   find_count;
    uint16_t   selected_nmb;
    f32        yt;
    f32        yb;
    int32_t    angx;
    int32_t    angz;
    NJS_POINT3 normal;
    NJS_POINT3 normal2;
    NJS_POINT3 onpoly;
    NJS_POINT3 pshbk;
    NJS_POINT3 anaspdh;
    NJS_POINT3 anaspdv;
}
CSTS;

typedef struct 
{
    f32       x;
    f32       y;
    f32       z;
    f32       r;
    f32       d;
    f32       h;
    int32_t   angy_dif;
    int32_t   angy_aim;
}
PL_LANDPOSI;

typedef struct player_parameter
{
    int32_t   jump2_timer;
    f32       pos_error;
    f32       lim_h_spd;
    f32       lim_v_spd;
    f32       max_x_spd;
    f32       max_psh_spd;
    f32       jmp_y_spd;
    f32       nocon_speed;
    f32       slide_speed;
    f32       jog_speed;
    f32       run_speed;
    f32       rush_speed;
    f32       crash_speed;
    f32       dash_speed;
    f32       jmp_addit;
    f32       run_accel;
    f32       air_accel;
    f32       slow_down;
    f32       run_break;
    f32       air_break;
    f32       air_resist_air;
    f32       air_resist;
    f32       air_resist_y;
    f32       air_resist_z;
    f32       grd_frict;
    f32       grd_frict_z;
    f32       lim_frict;
    f32       rat_bound;
    f32       rad;
    f32       height;
    f32       weight;
    f32       eyes_height;
    f32       center_height;
}
PL_PARAMETER;

typedef struct // To be moved
{
    void*   texp;
    int32_t address_u;
    int32_t address_v;
    int32_t tes5;
    int32_t min_filter;
    int32_t mag_filter;
    int32_t bank;
    int32_t unk;
}
TEXTURE_INFO;

typedef struct player_stencil
{
    TEXTURE_INFO texture;
    void*        texp;
    NJS_MATRIX   mat;
}
PL_STENCIL;

#define GET_PLAYERWK(tp)    ((playerwk*)tp->awp)

typedef struct playerwk
{
    int8_t pl_num;          // Player Number
    int8_t ch_num;          // Base Character Number
    int8_t costume;         // Costume Number
    int8_t ch_num_multi;    // Characer Number + 2P Alts

    int8_t action_list[8];
    int8_t action_num;
    int8_t action_sel;      // Currently selected action index (with Y)
    int8_t action_last;     // ? Set on pressing action

    int16_t item;           // Powerups
    int16_t jumptimer;
    int16_t nocontimer;     // No Control Timer
    int16_t breathtimer;
    int16_t waittimer;
    int16_t confusetimer;
    int16_t flag;
    int16_t island_num;
    int16_t path_point;     // ? More research needed
    int32_t equipment;

    f32       unkf_0;       // ? Related to being grabbed
    Angle     lean;         // Body lean angle
    f32       hpos;         // 1D Position along a path
    f32       dotp;         // Vertical dot product
    f32       unkf_1;       // ? Animation speed related
    f32       unkf_2;       // ? Seemingly random
    f32       unkf_3;       // ? Changing at all breaks game
    f32       rspd;         // Running speed

    f32       hp;        // Health, used for walkers and bossfights

    NJS_VECTOR eff;
    NJS_VECTOR acc;
    NJS_VECTOR spd;
    NJS_VECTOR wall_normal;
    NJS_VECTOR floor_normal;

    uint32_t attr;
    uint32_t last_attr;

    CSTS*   cstsp;
    task*   htp;              // Holding Task Pointer
    task*   nhtp;             // Next Holding Task Pointer
    task*   ttp;              // Target Task Pointer
    task*   mlotp;            // Mobile Land Object Task Pointer 
    task*   sctp;             // Stand Colli Task Pointer
    int32_t unki_3;         // Seemingly unused
    int32_t unki_4;         // ^

    NJS_OBJECT*  lclop;
    PL_LANDPOSI* island_list;

    PATH_TAG*    path_tag;

    NJS_MOTION** motion_list;

    PL_PARAMETER p;

    int8_t     unkc_2;
    uint8_t    gap_144[3];     // ? Possibly an alignment boundary
    int32_t    unki_1;
    uint8_t    gap_14C[4];
    int32_t    unki_2;
    f32        unkf_5;
    NJS_POINT3 unkp3_0;
    uint8_t    gap_164[12];
    task*      unktp_1;

    MOTION_JVWK mj;

    shadowwk shadow;
    shadowwk front_shadow;

    NJS_POINT3 righthand_pos;
    NJS_POINT3 lefthand_pos;
    NJS_POINT3 rightfoot_pos;
    NJS_POINT3 leftfoot_pos;
    NJS_POINT3 user0_pos;       // Usually the head
    NJS_POINT3 user1_pos;       // ^
    NJS_POINT3 root_pos;
    NJS_POINT3 tails_pos;
    NJS_POINT3 bazooka_pos;
    NJS_POINT3 powergun_pos;
    NJS_POINT3 extrashield_pos;

    NJS_VECTOR righthand_inv;
    NJS_VECTOR lefthand_inv;

    NJS_VECTOR righthand_vec;
    NJS_VECTOR lefthand_vec;
    NJS_VECTOR rightfoot_vec;
    NJS_VECTOR leftfoot_vec;
    NJS_VECTOR user0_vec;       // Usually the head
    NJS_VECTOR user1_vec;       // ^
    NJS_VECTOR root_vec;
    NJS_VECTOR tails_vec;
    NJS_VECTOR bazooka_vec;
    NJS_VECTOR powergun_vec;
    NJS_VECTOR extrashield_vec;

    PL_STENCIL stencil;
}
playerwk;

typedef struct player_motion
{
    int16_t     index;
    int16_t     nbMotion;
    NJS_MOTION* pMotion;
}
PL_MOTION;

typedef struct player_objdata
{
    char data0[2];
    __int16 vlistSize;
    float someFlt;
    int someInt0;
    int someInt1;
    int someInt2;
    NJS_CNK_OBJECT* pObj0;
    NJS_CNK_OBJECT* pObj1;
    NJS_CNK_OBJECT* pObj2;
    NJS_CNK_OBJECT* pObj3;
    char data2[16];
    char data3[84];
    int intAry[45];
}
PLAYER_OBJECT;

typedef struct player_object
{
    int32_t index;
    NJS_CNK_OBJECT* pObject;
}
PL_OBJECT;

/************************/
/*  Data                */
/************************/
#define CHAR_OBJECTS        DATA_ARY(PL_OBJECT  , 0x01DE9620, [532])
#define CHAR_MOTIONS        DATA_ARY(PL_MOTION  , 0x01DEA700, [300])

#define usPlayer            DATA_REF(int32_t    , 0x01934B80)
#define usPlayer2           DATA_REF(int32_t    , 0x01934BE4)

/** Player Work Pointers **/
#define playermwp           DATA_ARY(motionwk*  , 0x01DE95E0, [8])
#define playerpwp           DATA_ARY(playerwk*  , 0x01DE9600, [8])
#define playertwp           DATA_ARY(taskwk*    , 0x01DEA6C0, [8])
#define playertp            DATA_ARY(task*      , 0x01DEA6E0, [8])

/** Backup Task Functions For When Player Disabled **/
#define pExecSave           DATA_ARY(task_exec  , 0x019458F0, [8])
#define pDispSave           DATA_ARY(task_exec  , 0x01945960, [8])
#define pDispDelySave       DATA_ARY(task_exec  , 0x01945920, [8])
#define pDispSortSave       DATA_ARY(task_exec  , 0x019458D0, [8])
#define pDispLateSave       DATA_ARY(task_exec  , 0x01945940, [8])
#define pDispLastSave       DATA_ARY(task_exec  , 0x019458B0, [8])
#define pDispShadSave       DATA_ARY(task_exec  , 0x01945980, [8])

/** Other **/
typedef NJS_POINT3          pos_history_t[8][256];

#define pos_history         DATA_REF(pos_history_t*, 0x01A5A234)

/************************/
/*  Functions           */
/************************/
EXTERN_START
/** Enable/Disable the player Task **/
void    PlayerEnable(  uint8_t pno );
void    PlayerDisable( uint8_t pno );

/** Get Player Number from Task 
    if not a player, returns -1 **/
int32_t GetTaskPlayerNumber( task* tp );

/** Get the closest player to a point **/
int32_t GetTheNearestPlayerNumber( NJS_POINT3* pos );

/** Get rival of a player 
    returns -1 if no rival **/
int32_t GetRivalPlayerNumber( int32_t pno );

/** Give player powerup item **/
void    GetSpeedUpP(int32_t pno);
void    GetThunderBarrierP(int32_t pno);
void    GetBarrierP(int32_t pno);
void    GetInvincibleBodyForAMomentP(int32_t pno);

/** Held task functions **/
void    HoldTaskP(int32_t pno, task* htp);
void    StopHoldingTaskP(int32_t pno);

/** Get total number of players/characters **/
int32_t CountCharacters( void );

/************************/
/*  Inline Functions    */
/************************/
#ifdef  SAMT_INCL_INLINED

void    StopHoldingTaskP_inl(int32_t pno, taskwk* ptwp);

#endif/*SAMT_INCL_INLINED*/

EXTERN_END

/************************/
/*  Function Ptrs       */
/************************/
#ifdef  SAMT_INCL_FUNCPTRS
/** Function ptrs **/
#   define CountCharacters_p                FUNC_PTR(int32_t, __cdecl, (void), 0x0046DD60)

/** User-Function ptrs **/
#   define GetTaskPlayerNumber_p            ((void*)0x0046DCC0)
#   define GetTheNearestPlayerNumber_p      ((void*)0x0046DDC0)
#   define GetRivalPlayerNumber_p           ((void*)0x0046DE60)
#   define GetSpeedUpP_p                    ((void*)0x0046E120)
#   define GetThunderBarrierP_p             ((void*)0x0046E180)
#   define GetBarrierP_p                    ((void*)0x0046E2E0)
#   define GetInvincibleBodyForAMomentP_p   ((void*)0x0046E440)
#   define HoldTaskP_p                      ((void*)0x0046E5B0)

/** Inlined Function ptrs **/
#   define StopHoldingTaskP_inl_p           ((void*)0x0046E5E0)

#endif/*SAMT_INCL_FUNCPTRS*/

#endif/*_SA2B_PLAYER_H_*/
