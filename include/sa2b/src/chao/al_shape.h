#pragma once

/*
*	Includes
*/

#include <sa2b/ninja/ninja.h>

/*
*	Abstracted Types
*/

typedef struct task task;

/*
*	Structs
*/

struct CNK_VN_VERTEX
{
	NJS_POINT3 Pos;
	NJS_POINT3 Normal;
};

struct AL_VERTEX_INFO
{
	NJS_POINT3 Velo;
	float Weight;
	float Spring;
	float Friction;
};

typedef struct al_model
{
	int* VList;
	__int16* PList;
	NJS_POINT3 Center;
	float Radius;
	__int16 OrgTexId[4];
	int PListSize;
	int nbVertex;
	CNK_VN_VERTEX* pVertex;
	NJS_POINT3* pOrgVertexPos;
	NJS_POINT3* pOrgVertexNormal;
	AL_VERTEX_INFO* pVertexInfo;
}
AL_MODEL;

struct AL_BUYO_PARAM
{
	float Spring1;
	float Spring2;
	float Friction1;
	float Friction2;
	float MaxDiff;
	float MaxSpd;
	float Weight1;
	float Weight2;
	float Weight3;
	NJS_POINT3 Center;
};

typedef struct al_object
{
	uint32 EvalFlags;
	al_model* pModel;
	float Pos[3];
	sint32 Ang[3];
	float Scl[3];
	al_object* pChild;
	al_object* pSibling;
	al_object* pParent;
	NJS_POINT3 diff;
	NJS_POINT3 GlobalAimPos;
	NJS_POINT3 OrgPos;
	NJS_POINT3 Velo;
	NJS_POINT3 OrgAng;
	NJS_POINT3 AngSpd;
	float Weight;
	float Spring;
	float Friction;
	sint32 NoBuyoFlag;
	sint32 CalcBuyoPosFlag;
	cnkobj* pPartsObject;
	cnkobj* pItemObject;
	NJS_TEXLIST* pItemTexlist;
	float ItemScale;
	sint32 ItemActiveFlag;
	sint32 ItemOffsetFlag;
	NJS_POINT3 ItemOffsetPos;
	Angle3 ItemOffsetAng;
	float(*pOldMatrix)[16];
	AL_BUYO_PARAM* pBuyoParam;
	void* DisplayList;
}
AL_OBJECT;

struct AL_GROUP_OBJECT_LIST
{
	cnkobj* child[40];
	cnkobj* normal[40];
	cnkobj* swim[40];
	cnkobj* fly[40];
	cnkobj* run[40];
	cnkobj* power[40];
};

/*
*	Data References
*/

DataRef(float32, ratio_h, 0x01DB1068);
DataRef(float32, inv_ratio_h, 0x01DB1088);

DataRef(float32, ratio_v, 0x01DB1084);
DataRef(float32, inv_ratio_v, 0x01DB1070);

DataRef(float32, ratio_g, 0x01DB102C);
DataRef(float32, inv_ratio_g, 0x01DB1028);

DataRef(float32, div_ratio_h, 0x01DB109C);
DataRef(float32, div_ratio_v, 0x01DB108C);

DataRef(float32, col_ratio_h, 0x01DB1038);
DataRef(float32, col_ratio_v, 0x01DB1060);
DataRef(float32, col_ratio_g, 0x01DB1054);

DataRef(float32, col_inv_ratio_h, 0x01DB1098);
DataRef(float32, col_inv_ratio_v, 0x01DB106C);
DataRef(float32, col_inv_ratio_g, 0x01DB1078);

DataRef(float32, col_div_ratio_h, 0x01DB1034);
DataRef(float32, col_div_ratio_v, 0x01DB1030);

DataRef(AL_OBJECT**, CurrObjectList, 0x01DB1074);

DataRef(NJS_CNK_OBJECT**, ZeroObjectList, 0x01DB1050);
DataRef(NJS_CNK_OBJECT**, NormalObjectList, 0x01DB105C);
DataRef(NJS_CNK_OBJECT**, HorizonObjectList, 0x01DB107C);
DataRef(NJS_CNK_OBJECT**, VerticalObjectList, 0x01DB1064);

DataRef(NJS_CNK_OBJECT**, ZeroObjectListH, 0x01DB1048);
DataRef(NJS_CNK_OBJECT**, NormalObjectListH, 0x01DB1058);
DataRef(NJS_CNK_OBJECT**, HorizonObjectListH, 0x01DB103C);
DataRef(NJS_CNK_OBJECT**, VerticalObjectListH, 0x01DB1090);

DataRef(NJS_CNK_OBJECT**, ZeroObjectListD, 0x01DB1080);
DataRef(NJS_CNK_OBJECT**, NormalObjectListD, 0x01DB1044);
DataRef(NJS_CNK_OBJECT**, HorizonObjectListD, 0x01DB1094);
DataRef(NJS_CNK_OBJECT**, VerticalObjectListD, 0x01DB104C);

/*
*	Function Pointers
*/

FuncPtr(sint32,	__cdecl, GetList, (AL_OBJECT* pSrcObject, AL_OBJECT** List, int num), 0x0056BC90);

FuncPtr(AL_OBJECT*, __cdecl, AL_CopyChaoObject, (NJS_CNK_OBJECT* pSrcObject, NJS_CNK_OBJECT* pChildObject, AL_OBJECT* pParentObject), 0x0056BED0);
FuncPtr(sint32,		__cdecl, AL_CreateOrgVertexList, (AL_OBJECT* pObject), 0x0056C800);

FuncPtr(sint32,	__cdecl, AL_ShapeInit, (task* tp), 0x0056C9D0);

/* 
*	User Functions 
*/

void	AL_GetObjectList(AL_OBJECT* pSrcObject, AL_OBJECT** List);

/*
*	User Function Pointers
*/

#ifdef SAMT_INCLUDE_USER_PTRS

extern const void* AL_GetObjectList_p;

#endif