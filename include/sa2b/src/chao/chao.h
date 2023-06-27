#pragma once

#include <sa2b/ninja/ninja.h>

#include <sa2b/src/task.h>
#include <sa2b/src/motion.h>

#define CHAOWK(TP) ((chaowk*)TP->twp)

struct CHAO_PARAM_GC;

struct colliwk;

struct al_entry_work;

struct al_object;

struct CCL_INFO;

typedef sint32(__cdecl* BHV_FUNC)(task*);

enum : sint32
{
	SKILL_SWIM = 0x0,
	SKILL_FLY = 0x1,
	SKILL_RUN = 0x2,
	SKILL_POWER = 0x3,
	SKILL_STAMINA = 0x4,
	SKILL_GUTS = 0x5,
	SKILL_INTELLECT = 0x6,
	SKILL_EMPTY = 0x7,
	NB_SKILL = 0x8,
};

enum eAL_COLOR : sint32
{
	AL_COLOR_NORMAL = 0x0,
	AL_COLOR_YELLOW = 0x1,
	AL_COLOR_WHITE = 0x2,
	AL_COLOR_BROWN = 0x3,
	AL_COLOR_SKYBLUE = 0x4,
	AL_COLOR_PINK = 0x5,
	AL_COLOR_BLUE = 0x6,
	AL_COLOR_GRAY = 0x7,
	AL_COLOR_GREEN = 0x8,
	AL_COLOR_RED = 0x9,
	AL_COLOR_APPLEGREEN = 0xA,
	AL_COLOR_PURPLE = 0xB,
	AL_COLOR_ORANGE = 0xC,
	AL_COLOR_BLACK = 0xD,
	NB_AL_COLOR = 0xE,
};

enum eMEDAL_PARTS : sint32
{
	MEDAL_NONE = 0x0,
	MEDAL_AQU = 0x1,
	MEDAL_TOP = 0x2,
	MEDAL_PER = 0x3,
	MEDAL_GAR = 0x4,
	MEDAL_ONY = 0x5,
	MEDAL_DIA = 0x6,
	MEDAL_SILVER = 0x7,
	MEDAL_GOLD = 0x8,
	MEDAL_HERO = 0x9,
	MEDAL_DARK = 0xA,
	MEDAL_PERAL = 0xB,
	MEDAL_AME = 0xC,
	MEDAL_EME = 0xD,
	MEDAL_RUB = 0xE,
	MEDAL_SAP = 0xF,
};

enum eAL_ILLNESS : sint32
{
	AL_ILLNESS_SEKI = 0x0,
	AL_ILLNESS_KUSYAMI = 0x1,
	AL_ILLNESS_KAYUI = 0x2,
	AL_ILLNESS_HANAMIZU = 0x3,
	AL_ILLNESS_SYAKKURI = 0x4,
	AL_ILLNESS_HARAITA = 0x5,
	NB_AL_ILLNESS = 0x6,
};

enum : sint32
{
	TYPE_NONE = 0x0,
	TYPE_EGG = 0x1,
	TYPE_CHILD = 0x2,
	TYPE_DUMMY1 = 0x3,
	TYPE_DUMMY2 = 0x4,
	TYPE_N_NORMAL = 0x5,
	TYPE_H_NORMAL = 0x6,
	TYPE_D_NORMAL = 0x7,
	TYPE_N_SWIM = 0x8,
	TYPE_H_SWIM = 0x9,
	TYPE_D_SWIM = 0xA,
	TYPE_N_FLY = 0xB,
	TYPE_H_FLY = 0xC,
	TYPE_D_FLY = 0xD,
	TYPE_N_RUN = 0xE,
	TYPE_H_RUN = 0xF,
	TYPE_D_RUN = 0x10,
	TYPE_N_POWER = 0x11,
	TYPE_H_POWER = 0x12,
	TYPE_D_POWER = 0x13,
	TYPE_N_CHAOS = 0x14,
	TYPE_H_CHAOS = 0x15,
	TYPE_D_CHAOS = 0x16,
	TYPE_TAILS = 0x17,
	TYPE_KNUCKLES = 0x18,
	TYPE_AMY = 0x19,
	TYPE_MINIMAL = 0x1A,
	TYPE_OMOCHAO = 0x1B,
	TYPE_EGG_FOOT = 0x1C,
};

enum eAL_GARDEN // Non-standard
{
	GARDEN_NEUT = 1,
	GARDEN_HERO = 2,
	GARDEN_DARK = 3,
	GARDEN_SS = 4,
	GARDEN_EC = 5,
	GARDEN_MR = 6
};

enum eAL_HONBU_BASE : sint32
{
	HONBU_NORMAL = 0x0,
	HONBU_FIRE_OBAKE = 0x1,
};

enum : sint32
{
	MD_ICON_NORMAL = 0x0,
	MD_ICON_BIKKURI = 0x1,
	MD_ICON_HIRAMEKI = 0x2,
	MD_ICON_HATENA = 0x3,
	MD_ICON_HEART = 0x4,
	MD_ICON_MOJYA = 0x5,
};

enum : sint32
{
	ICON_TEX_NUM_TAMA = 0x0,
	ICON_TEX_NUM_BIKKURI = 0x1,
	ICON_TEX_NUM_HATENA = 0x2,
	ICON_TEX_NUM_HEART = 0x3,
	ICON_TEX_NUM_MOJYA = 0x4,
	ICON_TEX_NUM_TOGE = 0x5,
	ICON_TEX_NUM_TENSHI = 0x6,
	ICON_TEX_NUM_MARU = 0x7,
	ICON_TEX_NUM_BATSU = 0x8,
	ICON_TEX_NUM_LIGHT = 0x9,
	ICON_TEX_NUM_NONE = 0xA,
};

enum : sint32
{
	AL_FORM_NORMAL = 0x0,
	AL_FORM_EGG_FOOT = 0x1,
	AL_FORM_OMOCHAO = 0x2,
	AL_FORM_MINIMAL = 0x3,
	AL_FORM_CHIBI = 0x4,
};

enum JewelColor : sint32
{
	JewelColor_Normal = 0x0,
	JewelColor_Gold = 0x1,
	JewelColor_Silver = 0x2,
	JewelColor_Ruby = 0x3,
	JewelColor_Sapphire = 0x4,
	JewelColor_Emerald = 0x5,
	JewelColor_Amethyst = 0x6,
	JewelColor_Aquamarine = 0x7,
	JewelColor_Garnet = 0x8,
	JewelColor_Onyx = 0x9,
	JewelColor_Peridot = 0xA,
	JewelColor_Topaz = 0xB,
	JewelColor_Pearl = 0xC,
	JewelColor_Env0 = 0xD,	// Metal_1
	JewelColor_Env1 = 0xE,	// Metal_2
	JewelColor_Env2 = 0xF,	// Glass
	JewelColor_Env3 = 0x10,	// Moon
	JewelColor_Env4 = 0x11,	// Rare Tex
};

enum eAL_PLAYER_BTL : sint32
{
	BTL_AL_PL_SONIC = 0x0,
	BTL_AL_PL_SHADOW = 0x1,
	BTL_AL_PL_TAILS = 0x2,
	BTL_AL_PL_EGGMAN = 0x3,
	BTL_AL_PL_KNUCKLES = 0x4,
	BTL_AL_PL_ROUGE = 0x5,
	NB_BTL_AL_PLAYER = 0x6,
};

enum eAL_PLAYER_DX : sint32
{
	DX_AL_PL_SONIC = 0x0,
	DX_AL_PL_TAILS = 0x1,
	DX_AL_PL_KNUCKLES = 0x2,
	DX_AL_PL_AMY = 0x3,
	DX_AL_PL_E102 = 0x4,
	DX_AL_PL_BIG = 0x5,
	NB_DX_AL_PLAYER = 0x6,
};

enum eBODY_PARTS : sint32
{
	OBAKE_BODY_PARTS_NONE = 0x0,
	OBAKE_BODY_PARTS_SPECTOR = 0x1,
	OBAKE_BODY_PARTS_END = 0x2,
};

enum : sint32
{
	PARTS_KIND_ARM = 0x0,
	PARTS_KIND_EAR = 0x1,
	PARTS_KIND_FOREHEAD = 0x2,
	PARTS_KIND_HORN = 0x3,
	PARTS_KIND_REG = 0x4,
	PARTS_KIND_TAIL = 0x5,
	PARTS_KIND_WING = 0x6,
	PARTS_KIND_TONGUE = 0x7,
	NB_PARTS_KIND = 0x8,
};

enum eKW_BHV_KIND : sint32
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
};

enum eAL_MOUTH_NUM_EX : sint32 // Non-standard
{
	AL_MOUTH_NUM_HIGI_1 = 13,	// "STACHE 1" 
	AL_MOUTH_NUM_HIGI_2 = 14,	// "STACHE 2" 
	AL_MOUTH_NUM_HIGI_3 = 15	// "STACHE 3" 
};

enum eCHAO_FLAGS // Non-standard
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
};

enum : sint32
{
	INT_TIMER_PLAYER = 0x0,
	INT_TIMER_CHAO = 0x1,
	INT_TIMER_GREET = 0x2,
	INT_TIMER_SING = 0x3,
	INT_TIMER_MUSIC = 0x4,
	INT_TIMER_DANCE = 0x5,
	INT_TIMER_ART = 0x6,
	INT_TIMER_TOY = 0x7,
	INT_TIMER_LTOY = 0x8,
	INT_TIMER_MINIMAL = 0x9,
	INT_TIMER_TV = 0xA,
	INT_TIMER_RADICASE = 0xB,
	INT_TIMER_BOX = 0xC,
	INT_TIMER_BALL = 0xD,
	INT_TIMER_GOO = 0xE,
	INT_TIMER_AKUBI = 0xF,
	NB_INT_TIMER = 0x10,
};

struct TMP_PARAM
{
	uint8 Exp[8];
	uint8 Abl[8];
	uint8 Lev[8];
	uint16 Skills[8];
};

struct KW_BHV_ENTRY
{
	int bhv;
};

struct AL_BEHAVIOR
{
	uint16 Flag;
	uint16 Mode;
	uint16 SubMode;
	uint16 MoveMode;
	sint32 InterruptFlag;
	sint32 Timer;
	sint32 SubTimer;
	sint32 LimitTimer;
	//sint32 BehaviorTimer;		// SADX Only
	uint16 Intention;
	uint16 IntentionMode;
	uint16 IntentionSubMode;
	uint32 IntentionTimer[18]; 
	uint32 IntervalTimer[128];
	sint32 FreeWork;
	float32 MoveRadius;
	NJS_POINT3 BasePos;
	BHV_FUNC PrevFunc;
	sint32 nbBhvFuncEntry;
	sint32 CurrBhvFuncNum;
	BHV_FUNC BhvFuncList[16];
	sint32 ReserveTimerList[16];
	sint32 CurrKwBhvNum;
	KW_BHV_ENTRY KwBhvList[4];
	uint32 dummy[16];
};

struct AL_GROUP_OBJECT_LIST;

struct AL_SHAPE
{
	al_object* pObject;
	al_object* CurrObjectList[40];
	AL_GROUP_OBJECT_LIST* pObjectList;
	AL_GROUP_OBJECT_LIST* pObjectListH;
	AL_GROUP_OBJECT_LIST* pObjectListD;
	NJS_POINT3 BodyPos;
	NJS_POINT3 HeadPos;
	NJS_POINT3 LeftHandPos;
	NJS_POINT3 RightHandPos;
	NJS_POINT3 LeftFootPos;
	NJS_POINT3 RightFootPos;
	NJS_POINT3 MouthPos;
	NJS_POINT3 MouthVec;
	NJS_POINT3 LeftEyePos;
	NJS_POINT3 LeftEyeVec;
	NJS_POINT3 RightEyePos;
	NJS_POINT3 RightEyeVec;
	cnkobj* pLeftHandItemObject;
	NJS_TEXLIST* pLeftHandItemTexlist;
	float LeftHandItemScale;
	float LeftHandItemActiveFlag;
	cnkobj* pRightHandItemObject;
	NJS_TEXLIST* pRightHandItemTexlist;
	float RightHandItemScale;
	float RightHandItemActiveFlag;
	int palette;
	short Flag;
	short ColorNum;
	short EnvNum;
	int IconColor;
	float SclH;
	float SclV;
	float CamDist;
};

struct AL_FACE_CTRL
{
	sint32 EyeTimer;
	sint16 EyeColorNum;
	sint16 EyeCurrNum;
	sint16 EyeDefaultNum;
	sint32 MouthTimer;
	sint16 MouthCurrNum;
	sint16 MouthDefaultNum;
	float EyePosX;
	float EyePosY;
	float EyeSclX;
	float EyeSclY;
	uint32 Flag;
	al_object* pEyeObject[2];
	al_object* pMouthObject;
	sint32 EyeLidBlinkMode;
	sint32 EyeLidBlinkTimer;
	sint32 EyeLidBlinkAng;
	sint32 EyeLidExpressionMode;
	sint32 EyeLidExpressionTimer;
	sint32 EyeLidExpressionDefaultCloseAng;
	sint32 EyeLidExpressionCurrCloseAng;
	sint32 EyeLidExpressionAimCloseAng;
	sint32 EyeLidExpressionDefaultSlopeAng;
	sint32 EyeLidExpressionCurrSlopeAng;
	sint32 EyeLidExpressionAimSlopeAng;
};

struct AL_ICON_INFO
{
	uint16 Mode;
	uint16 TexNum;
	uint16 Timer;
	NJS_POINT3 Offset;
	NJS_POINT3 Pos;
	NJS_POINT3 Velo;
	NJS_POINT3 Scl;
	NJS_POINT3 SclSpd;
};

struct AL_ICON
{
	sint16 CurrType;
	sint16 NextType;
	sint32 Timer;
	sint32 NextTimer;
	sint32 PuniPhase;
	sint32 PosPhase;
	uint32 Color;
	uint16 TexAnimNum;
	uint16 TexAnimTimer;
	sint32 ang;
	NJS_POINT3 Up;
	NJS_POINT3 Pos;
	AL_ICON_INFO Upper;
	AL_ICON_INFO Lower;
};

struct AL_ZONE
{
	uint16 Flag;
	uint16 CurrNum;
	float Ratio;
	NJS_LINE Plane;
};

struct al_perception_link
{
	sint16 info[4];
	float tgtdist;
	sint32 InSightFlag;
	sint32 HearFlag;
	sint32 SmellFlag;
	al_entry_work* pEntry;
};

struct AL_PERCEPTION_INFO
{
	uint16 nbPerception;
	sint32 InSightFlag;
	sint32 HeardFlag;
	sint32 SmellFlag;
	float NearestDist;
	sint16 NearestNum;
	al_perception_link list[32];
};

struct AL_PERCEPTION
{
	float SightRange;
	sint32 SightAngle;
	sint32 SightAngleHalf;
	float HearRange;
	float SmellRange;
	AL_PERCEPTION_INFO Player;
	AL_PERCEPTION_INFO Chao;
	AL_PERCEPTION_INFO Fruit;
	AL_PERCEPTION_INFO Tree;
	AL_PERCEPTION_INFO Toy;
	AL_PERCEPTION_INFO Sound;
};

struct chaowk
{
	char mode;
	char smode;
	char id;
	char btimer;
	__int16 flag;
	__int16 wtimer;
	Angle3 ang;
	NJS_POINT3 pos;
	NJS_POINT3 scl;
	colliwk* cwp;
	uint32 Timer;
	task* pMayu;
	task* pBookTask;
	int NestFlag;
	task* pAnyTask;
	task* pAimTask;
	int AimNum;
	int RememberNum;
	int pitch;
	float ClimbFirstPos;
	int IsParamCopy;
	CHAO_PARAM_GC* pParamGC;
	TMP_PARAM tmpParam;
	sint32 Stamina;
	sint32 AimStamina;
	task* tp;
	Angle pre_ang[3];
	uint32 ChaoFlag;
	uint16 ColliFormat;
	float CurrZone;
	MOTION_CTRL MotionCtrl;
	MOTION_CTRL MiniMotionCtrl;
	MOTION_TABLE MiniMotionTable[4];
	AL_BEHAVIOR Behavior;
	AL_SHAPE Shape;
	AL_FACE_CTRL Face;
	AL_ICON Icon;
	AL_ZONE Zone;
	AL_PERCEPTION Perception;
	void* pWork;
};

struct AL_SHAPE_ELEMENT
{
	uint8 type;
	uint8 DefaultEyeNum;
	uint8 DefaultMouthNum;
	uint8 HonbuNum;
	uint8 ObakeHead;
	uint8 ObakeBody;
	uint8 MedalNum;
	uint8 ColorNum;
	uint8 NonTex;
	uint8 JewelNum;
	uint8 MultiNum;
	sint8 MinimalParts[8];
	sint16 HPos;
	sint16 VPos;
	sint16 APos;
	sint16 Growth;
	uint8 name[8];
	uint16 Skill[8];
};

DataAry(CCL_INFO, chao_colli_info, 0x013134D0, [5]);

FuncPtr(task*, __cdecl, CreateChaoExtra, (CHAO_PARAM_GC* pParamGC, int IsParamCopy, AL_SHAPE_ELEMENT* pElement, NJS_POINT3* pPos, Angle angy), 0x005501D0);

TaskFuncPtr(ChaoExecutor, 0x54FE20);
TaskFuncPtr(ChaoDestructor, 0x54FF30);
TaskFuncPtr(ChaoDisplayer, 0x54FF80);