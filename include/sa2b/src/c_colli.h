/*
*   Sonic Adventure Mod Tools (SA2B) - '/src/c_colli.h'
*
*   Contains structs, enums, and functions related to the game's collision engine
*
*   Contributors:
*   -   SEGA - Sonic Team,
*   -   Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC.
*/
#pragma once

/************************/
/*  Abstracted Types    */
/************************/
typedef task    TASK;
typedef taskwk  TASKWK;

/************************/
/*  Enums               */
/************************/
enum
{
	CI_FORM_SPHERE,
	CI_FORM_CYLINDER,
	CI_FORM_CYLINDER2,
	CI_FORM_RECTANGLE,
	CI_FORM_RECTANGLE2,
	CI_FORM_RECTANGLE3,
	CI_FORM_CAPSULE,
	CI_FORM_PERSON,
	CI_FORM_LINE,
	CI_FORM_WALL_PLANE,
	CI_FORM_WALL_CIRCLE
};

enum
{
	CID_PLAYER,
	CID_BULLET,
	CID_ENEMY,
	CID_ENEMY2,
	CID_OBJECT,
	CID_OBJECT2,
	CID_ITEM,
	CID_ITEM2,
	CID_WALL,
	CID_CHAO,
};

/************************/
/*  Structures          */
/************************/
typedef struct
{
	sint8		kind;
	uint8		form;
	sint8		push;
	sint8		damage;
	uint32		attr;
	NJS_POINT3	center;
	float32		a;
	float32		b;
	float32		c;
	float32		d;
	sint32		angx;
	sint32		angy;
	sint32		angz;
}
CCL_INFO;

typedef struct c_colli_hit_info
{
	sint8	my_num;
	sint8	hit_num;
	uint16	flag;
    TASKWK* hit_twp;
}
CCL_HIT_INFO;

typedef struct colliwk
{
	uint16 id;
	sint16 nbHit;
	uint16 flag;
	uint16 nbInfo;
	float32 colli_range;
	CCL_INFO* info;
	CCL_HIT_INFO hit_info[16];
	NJS_POINT3 normal;
	TASK* mytask;
	sint16 my_num;
	sint16 hit_num;
	struct colliwk* hit_cwp;
}
COLLIWK;

/************************/
/*  Function Pointers   */
/************************/
FuncPtr(CCL_HIT_INFO*, __cdecl, CCL_IsHitKindEx, (TASK* tp, uint8 kind), 0x486760);

/************************/
/*  User Functions      */
/************************/
sint32	CCL_Init(TASK* tp, CCL_INFO* info, sint32 nbInfo, uint8 id);
void	CCL_Entry(TASK* tp);

/************************/
/*  Functions           */
/************************/
TASKWK* CCL_IsHitKind(TASK* tp, uint8 kind);
TASK*	CCL_IsHitKind2(TASK* tp, uint8 kind);

bool32	CCL_IsPushed(TASKWK* twp);

/************************/
/*  User Function Ptrs  */
/************************/
#ifdef SAMT_INCLUDE_USER_PTRS

extern const void* CCL_Init_p;
extern const void* CCL_Entry_p;

#endif