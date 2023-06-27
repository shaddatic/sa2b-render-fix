#pragma once

#define PlayerPos playertwp[0]->campos
#define pHeldTask playerpwp[0]->HeldObject

#include <sa2b/ninja/ninja.h>

#include <sa2b/src/task.h>
#include <sa2b/src/shadow.h>

#define PL_EQUIP_SONIC_SHOES				0x00000001
#define PL_EQUIP_SONIC_SPARKLE				0x00000002
#define PL_EQUIP_SONIC_MAGICWRIST			0x00000004
#define PL_EQUIP_SONIC_FLAMERING			0x00000008
#define PL_EQUIP_SONIC_RUBBERUNIT			0x00000010
#define PL_EQUIP_SONIC_MELODY				0x00000020

#define PL_EQUIP_MILES_BOOSTER				0x00000040
#define PL_EQUIP_MILES_HYPERCANNON			0x00000080
#define PL_EQUIP_MILES_LASERBALSTER			0x00000100
#define PL_EQUIP_MILES_MELODY				0x00000200

#define PL_EQUIP_KNUCKLES_CLAW				0x00000400
#define PL_EQUIP_KNUCKLES_SUNGLASS			0x00000800
#define PL_EQUIP_KNUCKLES_GROVES			0x00001000
#define PL_EQUIP_KNUCKLES_AIR				0x00002000
#define PL_EQUIP_KNUCKLES_MELODY			0x00004000

#define PL_EQUIP_SUPERSONIC					0x00008000

#define PL_EQUIP_SHADOW_SHOES				0x00010000
#define PL_EQUIP_SHADOW_SPARKLE				0x00020000
#define PL_EQUIP_SHADOW_FLAMERING			0x00040000
#define PL_EQUIP_SHADOW_MELODY				0x00080000

#define PL_EQUIP_EGGMAN_JETENGINE			0x00100000
#define PL_EQUIP_EGGMAN_BAZOOKA				0x00200000
#define PL_EQUIP_EGGMAN_POWERGUN			0x00400000
#define PL_EQUIP_EGGMAN_EXTRASHIELD			0x00800000
#define PL_EQUIP_EGGMAN_MELODY				0x01000000

#define PL_EQUIP_ROUGE_NAILS				0x02000000
#define PL_EQUIP_ROUGE_SCOPE				0x04000000
#define PL_EQUIP_ROUGE_BOOTS				0x08000000
#define PL_EQUIP_ROUGE_MELODY				0x10000000

enum : sint32
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

struct PL_ACTION
{
	__int16 actnum;
	__int16 objnum;
	__int16 mtnmode;
	__int16 next;
	float frame;
	float racio;
};

struct mtnnjvwk
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
};

// Contains input (first 4 variables) and output information for the dynamic collision system.
struct csts
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
};

struct player_parameter
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
};


struct LoopPoint
{
	__int16 XRot;
	__int16 YRot;
	float Distance;
	NJS_POINT3 Position;
};

struct LoopHead
{
	__int16 anonymous_0;
	__int16 Count;
	float TotalDistance;
	LoopPoint* Points;
	void(__cdecl* Object)(task* tp);
};

struct PL_FACE
{

};

struct PL_LANDPOSI
{
	float x;
	float y;
	float z;
	float r;
	float d;
	float h;
	int angy_dif;
	int angy_aim;
};

#pragma pack(push, 1)
struct playerwk
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
	task* HeldObject;
	char gap_98[4];
	task* HoldTarget;
	char gap_A0[28];
	NJS_MOTION** Animation;
	player_parameter p;
	int field_144[12];
	mtnnjvwk mj;
	int field_1A0[7];
};
#pragma pack(pop)

struct player_mot
{
	sint16 index;
	sint16 count;
	NJS_MOTION* motion;
};

struct player_objdata
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
};

struct CHAR_OBJECT
{
	int index;
	NJS_CNK_OBJECT* pObject;
};

DataAry(CHAR_OBJECT, CHAR_OBJECTS, 0x01DE9620, [532]);

DataRef(sint32, usPlayer, 0x01934B80);
DataRef(sint32, usPlayer2, 0x01934BE4);

DataAry(motionwk*,	playermwp,	0x1DE95E0, [8]);
DataAry(playerwk*,	playerpwp,	0x1DE9600, [8]);
DataAry(taskwk*,	playertwp,	0x1DEA6C0, [8]);
DataAry(task*,		playertp,	0x1DEA6E0, [8]);

DataAry(task_exec, pExecSave,	0x019458F0, [8]);
DataAry(task_exec, pDispSave,	0x01945960, [8]);
DataAry(task_exec, pDisp1Save,	0x01945920, [8]);
DataAry(task_exec, pDisp2Save,	0x019458D0, [8]);
DataAry(task_exec, pDisp3Save,	0x01945940, [8]);
DataAry(task_exec, pDisp4Save,	0x019458B0, [8]);
DataAry(task_exec, pShadSave,	0x01945980, [8]);

void PlayerDisable(int pno);
void PlayerEnable(int pno);