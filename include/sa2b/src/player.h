/*
*   Sonic Adventure Mod Tools (SA2B) - '/src/player.h'
*
*   ~~ Under Construction ~~
*   Contains structs and functions related to player and characters data
*
*   Contributors:
*   -   SEGA - Sonic Team,
*   -   Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC.
*/
#ifndef _SA2B_PLAYER_H_
#define _SA2B_PLAYER_H_

/************************/
/*  Abstracted Types    */
/************************/
typedef struct task     TASK;
typedef struct taskwk   TASKWK;
typedef struct motionwk MOTIONWK;

/************************/
/*  Typedefs            */
/************************/
typedef void(__cdecl* task_exec)(TASK*);

/************************/
/*  Includes            */
/************************/
#include <sa2b/ninja/ninja.h>

#include <sa2b/src/shadow.h>

/************************/
/*  Equipment Flags     */
/************************/
#define EQUIP_SONIC_SHOES           (0x00000001)
#define EQUIP_SONIC_SPARKLE         (0x00000002)
#define EQUIP_SONIC_MAGICWRIST      (0x00000004)
#define EQUIP_SONIC_FLAMERING       (0x00000008)
#define EQUIP_SONIC_RUBBERUNIT      (0x00000010)
#define EQUIP_SONIC_MELODY          (0x00000020)

#define EQUIP_MILES_BOOSTER         (0x00000040)
#define EQUIP_MILES_HYPERCANNON     (0x00000080)
#define EQUIP_MILES_LASERBALSTER    (0x00000100)
#define EQUIP_MILES_MELODY          (0x00000200)

#define EQUIP_KNUCKLES_CLAW         (0x00000400)
#define EQUIP_KNUCKLES_SUNGLASS     (0x00000800)
#define EQUIP_KNUCKLES_GROVES       (0x00001000)
#define EQUIP_KNUCKLES_AIR          (0x00002000)
#define EQUIP_KNUCKLES_MELODY       (0x00004000)

#define EQUIP_SUPERSONIC            (0x00008000)

#define EQUIP_SHADOW_SHOES          (0x00010000)
#define EQUIP_SHADOW_SPARKLE        (0x00020000)
#define EQUIP_SHADOW_FLAMERING      (0x00040000)
#define EQUIP_SHADOW_MELODY         (0x00080000)

#define EQUIP_EGGMAN_JETENGINE      (0x00100000)
#define EQUIP_EGGMAN_BAZOOKA        (0x00200000)
#define EQUIP_EGGMAN_POWERGUN       (0x00400000)
#define EQUIP_EGGMAN_EXTRASHIELD    (0x00800000)
#define EQUIP_EGGMAN_MELODY         (0x01000000)

#define EQUIP_ROUGE_NAILS           (0x02000000)
#define EQUIP_ROUGE_SCOPE           (0x04000000)
#define EQUIP_ROUGE_BOOTS           (0x08000000)
#define EQUIP_ROUGE_MELODY          (0x10000000)

/************************/
/*  Enums               */
/************************/
enum
{
    ADV2_PLNO_SONIC,
    ADV2_PLNO_SHADOW,
    ADV2_PLNO_TAILS,
    ADV2_PLNO_EGGMAN,
    ADV2_PLNO_KNUCKLES,
    ADV2_PLNO_ROUGE,
    ADV2_PLNO_TORNADO,
    ADV2_PLNO_EGGWALKER,
    ADV2_PLNO_AMY,
    ADV2_PLNO_SUPER_SONIC,
    ADV2_PLNO_SUPER_SHADOW,
    ADV2_PLNO_DUMMY,
    ADV2_PLNO_METAL_SONIC,
    ADV2_PLNO_CHAO_WALKER,
    ADV2_PLNO_DARK_CHAO_WALKER,
    ADV2_PLNO_TIKAL,
    ADV2_PLNO_CHAOS,
    NB_ADV2_PLNO,
};

/************************/
/*  Structures          */
/************************/
typedef struct
{
    __int16 actnum;
    __int16 objnum;
    __int16 mtnmode;
    __int16 next;
    float frame;
    float racio;
}
PL_ACTION;

typedef struct mtnnjvwk
{
    __int16 mtnmode;
    __int16 Next;
    __int16 Current;
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
MOTION_NJV_WORK;

// Contains input (first 4 variables) and output information for the dynamic collision system.
typedef struct csts
{
    float radius;
    NJS_POINT3 campos;
    NJS_POINT3 spd;
    NJS_POINT3 tnorm;
    unsigned __int16 find_count;
    unsigned __int16 selected_nmb;
    float yt;
    float yb;
    int angx;
    int angz;
    NJS_POINT3 normal;
    NJS_POINT3 normal2;
    NJS_POINT3 onpoly;
    NJS_POINT3 pshbk;
    NJS_POINT3 anaspdh;
    NJS_POINT3 anaspdv;
}
CSTS;

typedef struct player_parameter
{
    int jump2_timer;
    float pos_error;
    float lim_h_spd;
    float lim_v_spd;
    float max_x_spd;
    float max_psh_spd;
    float jmp_y_spd;
    float nocon_speed;
    float slide_speed;
    float jog_speed;
    float run_speed;
    float rush_speed;
    float crash_speed;
    float dash_speed;
    float jmp_addit;
    float run_accel;
    float air_accel;
    float slow_down;
    float run_break;
    float air_break;
    float air_resist_air;
    float air_resist;
    float air_resist_y;
    float air_resist_z;
    float grd_frict;
    float grd_frict_z;
    float lim_frict;
    float rat_bound;
    float rad;
    float height;
    float weight;
    float eyes_height;
    float center_height;
}
PLAYER_PARAM;

typedef struct 
{
    __int16 XRot;
    __int16 YRot;
    float Distance;
    NJS_POINT3 Position;
}
LoopPoint;

typedef struct
{
    __int16 anonymous_0;
    __int16 Count;
    float TotalDistance;
    LoopPoint* Points;
    task_exec Object;
}
LoopHead;

/*
typedef struct 
{

}
PL_FACE;
*/

typedef struct 
{
    float x;
    float y;
    float z;
    float r;
    float d;
    float h;
    int angy_dif;
    int angy_aim;
}
PL_LANDPOSI;

#pragma pack(push, 1)
typedef struct playerwk
{
    sint8 pl_num;
    sint8 ch_num0;
    char Costume;
    char ch_num;
    char ActionWindowItems[8];
    char ActionWindowItemCount;
    char field_D[3];
    sint16 item;
    int field_12;
    sint16 breathtimer;
    sint16 waittimer;
    char gap_1A[10];
    int equipment;
    float field_28;
    char field_2C[28];
    float walker_health;
    int field_4C[6];
    NJS_VECTOR Speed;
    char gap_70[36];
    TASK* HeldObject;
    char gap_98[4];
    TASK* HoldTarget;
    char gap_A0[28];
    NJS_MOTION** Animation;
    PLAYER_PARAM p;
    int field_144[12];
    MOTION_NJV_WORK mj;
    int field_1A0[7];
}
PLAYERWK;
#pragma pack(pop)

typedef struct player_mot
{
    sint16 index;
    sint16 count;
    NJS_MOTION* motion;
}
PLAYER_MOTION;

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

typedef struct
{
    sint32 index;
    NJS_CNK_OBJECT* pObject;
}
CHAR_OBJECT;

/************************/
/*  Data                */
/************************/
#define CHAR_OBJECTS    DataAry(CHAR_OBJECT, 0x01DE9620, [532])

#define usPlayer        DataRef(sint32     , 0x01934B80)
#define usPlayer2       DataRef(sint32     , 0x01934BE4)

/** Player Work Pointers **/
#define playermwp       DataAry(MOTIONWK*  , 0x01DE95E0, [8])
#define playerpwp       DataAry(PLAYERWK*  , 0x01DE9600, [8])
#define playertwp       DataAry(TASKWK*    , 0x01DEA6C0, [8])
#define playertp        DataAry(TASK*      , 0x01DEA6E0, [8])

/** Backup Task Functions For When Player Disabled **/
#define pExecSave       DataAry(task_exec  , 0x019458F0, [8])
#define pDispSave       DataAry(task_exec  , 0x01945960, [8])
#define pDisp1Save      DataAry(task_exec  , 0x01945920, [8])
#define pDisp2Save      DataAry(task_exec  , 0x019458D0, [8])
#define pDisp3Save      DataAry(task_exec  , 0x01945940, [8])
#define pDisp4Save      DataAry(task_exec  , 0x019458B0, [8])
#define pShadSave       DataAry(task_exec  , 0x01945980, [8])

/************************/
/*  Functions           */
/************************/
EXTERN_START
/* Enable/Disable the player TASK */
void    PlayerEnable(uint8 pno);
void    PlayerDisable(uint8 pno);

EXTERN_END

#endif /* _SA2B_MOVE_H_ */
