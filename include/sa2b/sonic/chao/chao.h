/*
*   Sonic Adventure Mod Tools (SA2B) - '/sonic/chao/chao.h'
*
*   Description:
*       Contains typedefs, enums, structures, data, & functions related
*   directly with Chao themselves.
*
*   Contributors:
*     - SEGA - Sonic Team,
*     - Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC
*/
#ifndef _SA2B_CHAO_CHAO_H_
#define _SA2B_CHAO_CHAO_H_

/************************/
/*  Includes            */
/************************/
/** Ninja **/
#include <sa2b/ninja/ninja.h>

/** Source **/
#include <sa2b/sonic/motion.h>

/** Task Work **/
#include <sa2b/sonic/task.h>

/** Colli Info **/
#include <sa2b/sonic/c_colli/ccl_info.h>

/************************/
/*  Abstract Types      */
/************************/
typedef struct task                     task;
typedef struct chao_param_gc            CHAO_PARAM_GC;
typedef struct al_entry_work            ALW_ENTRY_WORK;
typedef struct al_object                AL_OBJECT;
typedef struct al_group_object_list     AL_GROUP_OBJECT_LIST;

/************************/
/*  Typedefs            */
/************************/
typedef int32_t(__cdecl* BHV_FUNC)(task*);

/************************/
/*  Enums               */
/************************/
typedef enum
{
    AL_COLOR_NORMAL,
    AL_COLOR_YELLOW,
    AL_COLOR_WHITE,
    AL_COLOR_BROWN,
    AL_COLOR_SKYBLUE,
    AL_COLOR_PINK,
    AL_COLOR_BLUE,
    AL_COLOR_GRAY,
    AL_COLOR_GREEN,
    AL_COLOR_RED,
    AL_COLOR_APPLEGREEN,
    AL_COLOR_PURPLE,
    AL_COLOR_ORANGE,
    AL_COLOR_BLACK,
    NB_AL_COLOR,
}
eAL_COLOR;

typedef enum
{
    MEDAL_NONE,
    MEDAL_AQU,
    MEDAL_TOP,
    MEDAL_PER,
    MEDAL_GAR,
    MEDAL_ONY,
    MEDAL_DIA,
    MEDAL_SILVER,
    MEDAL_GOLD,
    MEDAL_HERO,
    MEDAL_DARK,
    MEDAL_PERAL,
    MEDAL_AME,
    MEDAL_EME,
    MEDAL_RUB,
    MEDAL_SAP,
}
eMEDAL_PARTS;

typedef enum
{
    AL_ILLNESS_SEKI,
    AL_ILLNESS_KUSYAMI,
    AL_ILLNESS_KAYUI,
    AL_ILLNESS_HANAMIZU,
    AL_ILLNESS_SYAKKURI,
    AL_ILLNESS_HARAITA,
    NB_AL_ILLNESS,
}
eAL_ILLNESS;

enum
{
    TYPE_NONE,
    TYPE_EGG,
    TYPE_CHILD,
    TYPE_DUMMY1,
    TYPE_DUMMY2,
    TYPE_N_NORMAL,
    TYPE_H_NORMAL,
    TYPE_D_NORMAL,
    TYPE_N_SWIM,
    TYPE_H_SWIM,
    TYPE_D_SWIM,
    TYPE_N_FLY,
    TYPE_H_FLY,
    TYPE_D_FLY,
    TYPE_N_RUN,
    TYPE_H_RUN,
    TYPE_D_RUN,
    TYPE_N_POWER,
    TYPE_H_POWER,
    TYPE_D_POWER,
    TYPE_N_CHAOS,
    TYPE_H_CHAOS,
    TYPE_D_CHAOS,
    TYPE_TAILS,
    TYPE_KNUCKLES,
    TYPE_AMY,
    TYPE_MINIMAL,
    TYPE_OMOCHAO,
    TYPE_EGG_FOOT,
};

typedef enum /* Toolkit addition */
{
    CHAO_GARDEN_NONE,
    CHAO_GARDEN_NEUT,
    CHAO_GARDEN_HERO,
    CHAO_GARDEN_DARK,
    CHAO_GARDEN_SS,
    CHAO_GARDEN_EC,
    CHAO_GARDEN_MR,
}
eCHAO_GARDEN;

typedef enum
{
    HONBU_NORMAL,
    HONBU_FIRE_OBAKE,
}
eAL_HONBU_BASE;

enum
{
    MD_ICON_NORMAL,
    MD_ICON_BIKKURI,
    MD_ICON_HIRAMEKI,
    MD_ICON_HATENA,
    MD_ICON_HEART,
    MD_ICON_MOJYA,
};

enum
{
    ICON_TEX_NUM_TAMA,
    ICON_TEX_NUM_BIKKURI,
    ICON_TEX_NUM_HATENA,
    ICON_TEX_NUM_HEART,
    ICON_TEX_NUM_MOJYA,
    ICON_TEX_NUM_TOGE,
    ICON_TEX_NUM_TENSHI,
    ICON_TEX_NUM_MARU,
    ICON_TEX_NUM_BATSU,
    ICON_TEX_NUM_LIGHT,
    ICON_TEX_NUM_NONE,
};

enum
{
    AL_FORM_NORMAL,
    AL_FORM_EGG_FOOT,
    AL_FORM_OMOCHAO,
    AL_FORM_MINIMAL,
    AL_FORM_CHIBI,
};

typedef enum
{
    JewelColor_Normal,
    JewelColor_Gold,
    JewelColor_Silver,
    JewelColor_Ruby,
    JewelColor_Sapphire,
    JewelColor_Emerald,
    JewelColor_Amethyst,
    JewelColor_Aquamarine,
    JewelColor_Garnet,
    JewelColor_Onyx,
    JewelColor_Peridot,
    JewelColor_Topaz,
    JewelColor_Pearl,
    JewelColor_Env0,    // Metal_1
    JewelColor_Env1,    // Metal_2
    JewelColor_Env2,    // Glass
    JewelColor_Env3,    // Moon
    JewelColor_Env4,    // Rare Tex
}
JewelColor;

typedef enum
{
    BTL_AL_PL_SONIC = 0x0,
    BTL_AL_PL_SHADOW = 0x1,
    BTL_AL_PL_TAILS = 0x2,
    BTL_AL_PL_EGGMAN = 0x3,
    BTL_AL_PL_KNUCKLES = 0x4,
    BTL_AL_PL_ROUGE = 0x5,
    NB_BTL_AL_PLAYER = 0x6,
}
eAL_PLAYER_BTL;

typedef enum 
{
    DX_AL_PL_SONIC = 0x0,
    DX_AL_PL_TAILS = 0x1,
    DX_AL_PL_KNUCKLES = 0x2,
    DX_AL_PL_AMY = 0x3,
    DX_AL_PL_E102 = 0x4,
    DX_AL_PL_BIG = 0x5,
    NB_DX_AL_PLAYER = 0x6,
}
eAL_PLAYER_DX;

typedef enum
{
    OBAKE_BODY_PARTS_NONE = 0x0,
    OBAKE_BODY_PARTS_SPECTOR = 0x1,
    OBAKE_BODY_PARTS_END = 0x2,
}
eBODY_PARTS;

typedef enum
{
    KW_BHV_ART = 0x0,
    KW_BHV_DANCE = 0x1,
    KW_BHV_SING = 0x2,
    KW_BHV_MUSIC = 0x3,
    KW_BHV_MINI1 = 0x4,
    KW_BHV_MINI2 = 0x5,
    KW_BHV_MINI3 = 0x6,
    KW_BHV_MINI4 = 0x7,
    KW_BHV_MINI5 = 0x8,
    KW_BHV_MINI6 = 0x9,
    KW_BHV_MINI7 = 0xA,
    KW_BHV_MINI8 = 0xB,
    KW_BHV_MINI9 = 0xC,
    KW_BHV_MINI10 = 0xD,
    KW_BHV_MINI11 = 0xE,
    KW_BHV_MINI12 = 0xF,
    KW_BHV_MINI13 = 0x10,
    KW_BHV_MINI14 = 0x11,
    KW_BHV_MINI15 = 0x12,
    KW_BHV_MINI16 = 0x13,
    KW_BHV_MINI17 = 0x14,
    KW_BHV_MINI18 = 0x15,
    KW_BHV_TOY1 = 0x16,
    KW_BHV_TOY2 = 0x17,
    KW_BHV_TOY3 = 0x18,
    KW_BHV_TOY4 = 0x19,
    KW_BHV_TOY5 = 0x1A,
    KW_BHV_TOY6 = 0x1B,
    KW_BHV_TOY7 = 0x1C,
    KW_BHV_TOY8 = 0x1D,
    KW_BHV_TOY9 = 0x1E,
    KW_BHV_TOY10 = 0x1F,
    KW_BHV_TOY11 = 0x20,
    KW_BHV_FLY = 0x21,
    KW_BHV_SWIM = 0x22,
    KW_BHV_CLIMB_TREE = 0x23,
    KW_BHV_CLIMB_WALL = 0x24,
    KW_BHV_WATER = 0x25,
    KW_BHV_SWING = 0x26,
    KW_BHV_SIT = 0x27,
    KW_BHV_DENGURI = 0x28,
    KW_BHV_TOILET = 0x29,
    KW_BHV_PYON = 0x2A,
    KW_BHV_BOWLING = 0x2B,
    KW_BHV_FUKKIN = 0x2C,
    KW_BHV_SHIRIFURI = 0x2D,
    KW_BHV_OJIGI = 0x2E,
    KW_BHV_CHIWA = 0x2F,
    KW_BHV_NADERU = 0x30,
    KW_BHV_AGERU = 0x31,
    KW_BHV_TALK = 0x32,
    KW_BHV_PUNCH = 0x33,
    KW_BHV_OKOSU = 0x34,
    KW_BHV_TEFURI = 0x35,
    KW_BHV_HAKUSYU = 0x36,
    KW_BHV_SURIYORU = 0x37,
    KW_BHV_AKANBE = 0x38,
    KW_BHV_WA = 0x39,
    KW_BHV_NAGERU = 0x3A,
    KW_BHV_FIGHT = 0x3B,
    KW_BHV_IGAMI = 0x3C,
    KW_BHV_LISTEN = 0x3D,
    KW_BHV_WATCH = 0x3E,
}
eKW_BHV_KIND;

typedef enum /* Toolkit addition */
{
    CHAO_FLAGS_UseMove = 0x02,
    CHAO_FLAGS_UseMotionTable = 0x04,
    CHAO_FLAGS_HaveCollision = 0x08,
    CHAO_FLAGS_RunBehaviourHandler = 0x10,
    CHAO_FLAGS_CanJiggle = 0x20,
    CHAO_FLAGS_CanRender = 0x0200,
    CHAO_FLAGS_AnotherJiggleThing = 0x1000,
    CHAO_FLAGS_RunThinkController = 0x2000,
    CHAO_FLAGS_Timescale = 0x020000,
    CHAO_FLAGS_DrawIcon = 0x100000,
}
eCHAO_FLAGS;

enum
{
    INT_TIMER_PLAYER,
    INT_TIMER_CHAO,
    INT_TIMER_GREET,
    INT_TIMER_SING,
    INT_TIMER_MUSIC,
    INT_TIMER_DANCE,
    INT_TIMER_ART,
    INT_TIMER_TOY,
    INT_TIMER_LTOY,
    INT_TIMER_MINIMAL,
    INT_TIMER_TV,
    INT_TIMER_RADICASE,
    INT_TIMER_BOX,
    INT_TIMER_BALL,
    INT_TIMER_GOO,
    INT_TIMER_AKUBI,
    NB_INT_TIMER,
};

/************************/
/*  Structures          */
/************************/
typedef struct
{
    uint8_t  Exp[8];
    uint8_t  Abl[8];
    uint8_t  Lev[8];
    uint16_t Skills[8];
}
TMP_PARAM;

typedef struct
{
    int32_t bhv;
}
KW_BHV_ENTRY;

typedef struct 
{
    uint16_t     Flag;
    uint16_t     Mode;
    uint16_t     SubMode;
    uint16_t     MoveMode;
    int32_t      InterruptFlag;
    int32_t      Timer;
    int32_t      SubTimer;
    int32_t      LimitTimer;
//  sint32       BehaviorTimer; // SADX Only
    uint16_t     Intention;
    uint16_t     IntentionMode;
    uint16_t     IntentionSubMode;
    uint32_t     IntentionTimer[18]; 
    uint32_t     IntervalTimer[128];
    int32_t      FreeWork;
    f32          MoveRadius;
    NJS_POINT3   BasePos;
    BHV_FUNC     PrevFunc;
    int32_t      nbBhvFuncEntry;
    int32_t      CurrBhvFuncNum;
    BHV_FUNC     BhvFuncList[16];
    int32_t      ReserveTimerList[16];
    int32_t      CurrKwBhvNum;
    KW_BHV_ENTRY KwBhvList[4];
    uint32_t     dummy[16];
}
AL_BEHAVIOR;

typedef struct
{
    /** Shape object **/
    AL_OBJECT* pObject;
    AL_OBJECT* CurrObjectList[40];

    /** Shape object lists **/
    AL_GROUP_OBJECT_LIST* pObjectList;
    AL_GROUP_OBJECT_LIST* pObjectListH;
    AL_GROUP_OBJECT_LIST* pObjectListD;

    /** Positions **/
    NJS_POINT3 BodyPos;
    NJS_POINT3 HeadPos;
    NJS_POINT3 LeftHandPos;
    NJS_POINT3 RightHandPos;
    NJS_POINT3 LeftFootPos;
    NJS_POINT3 RightFootPos;
    NJS_POINT3 MouthPos;

    /** Vectors **/
    NJS_VECTOR MouthVec;
    NJS_VECTOR LeftEyePos;
    NJS_VECTOR LeftEyeVec;
    NJS_VECTOR RightEyePos;
    NJS_VECTOR RightEyeVec;

    /** Left hand item **/
    NJS_CNK_OBJECT* pLeftHandItemObject;
    NJS_TEXLIST*    pLeftHandItemTexlist;
    f32             LeftHandItemScale;
    f32             LeftHandItemActiveFlag;

    /** Right hand item **/
    NJS_CNK_OBJECT* pRightHandItemObject;
    NJS_TEXLIST*    pRightHandItemTexlist;
    f32             RightHandItemScale;
    f32             RightHandItemActiveFlag;

    /** Shape info **/
    int32_t   palette;
    int16_t   Flag;
    int16_t   ColorNum;
    int16_t   EnvNum;
    int32_t   IconColor;
    f32       SclH;
    f32       SclV;
    f32       CamDist;
}
AL_SHAPE;

typedef struct
{
    int32_t    EyeTimer;
    int16_t    EyeColorNum;
    int16_t    EyeCurrNum;
    int16_t    EyeDefaultNum;
    int32_t    MouthTimer;
    int16_t    MouthCurrNum;
    int16_t    MouthDefaultNum;
    f32        EyePosX;
    f32        EyePosY;
    f32        EyeSclX;
    f32        EyeSclY;
    uint32_t   Flag;
    AL_OBJECT* pEyeObject[2];
    AL_OBJECT* pMouthObject;
    int32_t    EyeLidBlinkMode;
    int32_t    EyeLidBlinkTimer;
    int32_t    EyeLidBlinkAng;
    int32_t    EyeLidExpressionMode;
    int32_t    EyeLidExpressionTimer;
    int32_t    EyeLidExpressionDefaultCloseAng;
    int32_t    EyeLidExpressionCurrCloseAng;
    int32_t    EyeLidExpressionAimCloseAng;
    int32_t    EyeLidExpressionDefaultSlopeAng;
    int32_t    EyeLidExpressionCurrSlopeAng;
    int32_t    EyeLidExpressionAimSlopeAng;
}
AL_FACE_CTRL;

typedef struct
{
    uint16_t Mode;
    uint16_t TexNum;
    uint16_t Timer;
    NJS_POINT3 Offset;
    NJS_POINT3 Pos;
    NJS_POINT3 Velo;
    NJS_POINT3 Scl;
    NJS_POINT3 SclSpd;
}
AL_ICON_INFO;

typedef struct
{
    int16_t CurrType;
    int16_t NextType;
    int32_t Timer;
    int32_t NextTimer;
    int32_t PuniPhase;
    int32_t PosPhase;
    uint32_t Color;
    uint16_t TexAnimNum;
    uint16_t TexAnimTimer;
    int32_t ang;
    NJS_POINT3 Up;
    NJS_POINT3 Pos;
    AL_ICON_INFO Upper;
    AL_ICON_INFO Lower;
}
AL_ICON;

typedef struct
{
    uint16_t  Flag;
    uint16_t  CurrNum;
    f32       Ratio;
    NJS_LINE  Plane;
}
AL_ZONE;

typedef struct al_perception_link
{
    int16_t         info[4];
    f32             tgtdist;
    int32_t         InSightFlag;
    int32_t         HearFlag;
    int32_t         SmellFlag;
    ALW_ENTRY_WORK* pEntry;
}
AL_PERCEPTION_LIST[32];

typedef struct
{
    uint16_t           nbPerception;
    int32_t            InSightFlag;
    int32_t            HeardFlag;
    int32_t            SmellFlag;
    f32                NearestDist;
    int16_t            NearestNum;
    AL_PERCEPTION_LIST list;
}
AL_PERCEPTION_INFO;

typedef struct
{
    f32                SightRange;
    int32_t            SightAngle;
    int32_t            SightAngleHalf;
    f32                HearRange;
    f32                SmellRange;
    AL_PERCEPTION_INFO Player;
    AL_PERCEPTION_INFO Chao;
    AL_PERCEPTION_INFO Fruit;
    AL_PERCEPTION_INFO Tree;
    AL_PERCEPTION_INFO Toy;
    AL_PERCEPTION_INFO Sound;
}
AL_PERCEPTION;

#define GET_CHAOWK(_tp)     ((chaowk*)(_tp)->twp)

typedef struct chaowk
{
    TASKWK;

    uint32_t       Timer;
    task*          pMayu;
    task*          pBooktask;
    int32_t        NestFlag;
    task*          pAnytask;
    task*          pAimtask;
    int32_t        AimNum;
    int32_t        RememberNum;
    int32_t        pitch;
    f32            ClimbFirstPos;
    b32            IsParamCopy;
    CHAO_PARAM_GC* pParamGC;
    TMP_PARAM      tmpParam;
    int32_t        Stamina;
    int32_t        AimStamina;
    task*          tp;
    Angle          pre_ang[3];
    uint32_t       ChaoFlag;
    uint16_t       ColliFormat;
    f32            CurrZone;
    MOTION_CTRL    MotionCtrl;
    MOTION_CTRL    MiniMotionCtrl;
    MOTION_TABLE   MiniMotionTable[4];
    AL_BEHAVIOR    Behavior;
    AL_SHAPE       Shape;
    AL_FACE_CTRL   Face;
    AL_ICON        Icon;
    AL_ZONE        Zone;
    AL_PERCEPTION  Perception;
    void*          pWork;
}
chaowk;

typedef struct al_shape_element
{
    uint8_t  type;
    uint8_t  DefaultEyeNum;
    uint8_t  DefaultMouthNum;
    uint8_t  HonbuNum;
    uint8_t  ObakeHead;
    uint8_t  ObakeBody;
    uint8_t  MedalNum;
    uint8_t  ColorNum;
    uint8_t  NonTex;
    uint8_t  JewelNum;
    uint8_t  MultiNum;
    int8_t   MinimalParts[8];
    int16_t  HPos;              // divided by 10'000 on copy
    int16_t  VPos;              // divided by 10'000 on copy
    int16_t  APos;              // divided by 10'000 on copy
    int16_t  Growth;            // divided by 10'000 on copy
    uint8_t  name[8];
    uint16_t Skill[8];
}
AL_SHAPE_ELEMENT;

/************************/
/*  Data                */
/************************/
/** Collision info **/
#define colli_info_chao     DATA_ARY(CCL_INFO, 0x013134D0, [5])

/************************/
/*  Functions           */
/************************/
EXTERN_START
/** 'pParamGC' can be NULL, and a new paramGC will be generated
    'IsParamCopy' copies given 'pParamGC' info and doesn't add it to the ALW entry save info
    'pElement' can be NULL, moves it's info into Chao's paramGC **/
task*   CreateChaoExtra(CHAO_PARAM_GC* pParamGC, b32 IsParamCopy, AL_SHAPE_ELEMENT* pElement, NJS_POINT3* pPos, Angle angy);

/** Task functions **/
void    ChaoExecutor(task* tp);
void    ChaoDestructor(task* tp);
void    ChaoDisplayer(task* tp);

EXTERN_END

/************************/
/*  Function Ptrs       */
/************************/
#ifdef  SAMT_INCL_FUNCPTRS
/** Function ptrs **/
#   define CreateChaoExtra_p        FUNC_PTR(task*, __cdecl, (CHAO_PARAM_GC*, b32, AL_SHAPE_ELEMENT*, NJS_POINT3*, Angle), 0x005501D0)
#   define ChaoExecutor_p           FUNC_PTR(void , __cdecl, (task*)                                                     , 0x0054FE20)
#   define ChaoDestructor_p         FUNC_PTR(void , __cdecl, (task*)                                                     , 0x0054FF30)
#   define ChaoDisplayer_p          FUNC_PTR(void , __cdecl, (task*)                                                     , 0x0054FF80)

#endif/*SAMT_INCL_FUNCPTRS*/

#endif/*_SA2B_CHAO_CHAO_H_*/
