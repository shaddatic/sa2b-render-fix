#pragma once

/* 
*	Abstracted Structs
*/

typedef struct task		task;
typedef struct zxsdwstr	zxsdwstr;

/*
*	Defines
*/

/* Non-standard defines */
#define LANDATTR_SOLID				0x00000001
#define LANDATTR_WATER				0x00000002
#define LANDATTR_DIGGABLE			0x00000020
#define LANDATTR_NOCLIMB			0x00000080
#define LANDATTR_STAIRS				0x00000100
#define LANDATTR_HURT				0x00000400
#define LANDATTR_FOOTSTEPS			0x00000800
#define LANDATTR_NOLANDING			0x00001000
#define LANDATTR_NOALPHA			0x00002000
#define LANDATTR_NOSHADOW			0x00008000
#define LANDATTR_ACCELERATE			0x00100000
#define LANDATTR_NOFOG				0x00400000
#define LANDATTR_DYNAMIC			0x08000000
#define LANDATTR_UNK1				0x20000000 // Usually medium-sized collisions
#define LANDATTR_UNK2				0x40000000 // Usually small-sized collisions
#define LANDATTR_VISIBLE			0x80000000

/*
*	Includes
*/

#include <sa2b/ninja/ninja.h>

/*
*	Structs
*/

typedef struct _OBJ_LANDENTRY
{
	float32 CenterX;
	float32 CenterY;
	float32 CenterZ;
	float32 Radius;
	anyobj_p pObj;
	int field_14;
	int Chunks;
	int slAttribute;
}
OBJ_LANDENTRY;

typedef struct _OBJ_MOTLANDENTRY
{
	float fFrame;
	float fStep;
	float fMaxFrame;
	anyobj_p pObject;
	NJS_MOTION* pMotion;
}
OBJ_MOTLANDENTRY;

typedef struct _OBJ_LANDTABLE
{
	sint16 ssCount;
	sint16 ssVisibleCount;
	sint16 ssUnkown;		// I assume
	sint16 ssMotCount;
	sint16 ssAttribute;
	sint16 ssLoadFlag;
	float32 fFarClipping;
	OBJ_LANDENTRY* pLandEntry;
	OBJ_MOTLANDENTRY* pMotLandEntry;
	char* TexName;
	NJS_TEXLIST* TexList;
}
OBJ_LANDTABLE;

typedef struct _OBJ_LANDCOLL
{
	int slAttribute;
	NJS_OBJECT* pObject;
	task* pTask;
}
OBJ_LANDCOLL;

/*
*	Data References
*/

DataRef(task*, pLandTask, 0x01945A04);

DataRef(bool32, boolLandTableGinja, 0x1A5A2D8);
DataRef(float32, mleriRangeRad, 0x171CAA4); // LandColRadius
DataRef(OBJ_LANDTABLE*, pObjLandTable, 0x019459DC);

DataRef(bool32, boolLandDisplay, 0x0171CAA8);
DataRef(bool32, boolLandCollision, 0x0171CAAC);

DataRef(OBJ_LANDENTRY*, ri_landentry_buf, 0x01A5A2D4);
DataRef(sint32, ri_landentry_nmb, 0x01A5A2CC);

DataRef(sint16, numLandCollList, 0x01DE9484);
DataRef(sint32, ri_landcoll_nmb, 0x01A5A2C8);

DataRef(OBJ_LANDCOLL*, LandCollList, 0x01A5A2DC);

DataRef(OBJ_LANDCOLL*, MobileEntry, 0x01A5A2E0);
DataRef(sint16, numMobileEntry, 0x019459D4);

/*
*	Function Pointers
*/

FuncPtr(void, __cdecl, ListGroundForCollision, (float xPosition, float yPosition, float zPosition, float fRadius), 0x0047CD60);
FuncPtr(sint32, __cdecl, LandChangeLandTable, (OBJ_LANDTABLE* land), 0x47BD30);

/*
*	User Functions
*/

sint32 LandChangeGinjaLandTable(OBJ_LANDTABLE* land);

sint32 CL_ColPolCheckZxShadow(zxsdwstr* zssp, NJS_OBJECT* obp);

/*
*	Custom Functions
*/

sint32 LandChangeChunkLandTable(OBJ_LANDTABLE* land);

/*
*	User Function Pointers
*/

#ifdef SAMT_INCLUDE_USER_PTRS

extern const void* LandChangeGinjaLandTable_p;

extern const void* CL_ColPolCheckZxShadow_p;

#endif