/*
*   Sonic Adventure Mod Tools (SA2B) - '/src/chao/al_shape.h'
*
*   Contains structs, data, and functions related to Chao models.
*
*   Contributors:
*   -   SEGA - Sonic Team,
*   -   Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC.
*/
#ifndef _SA2B_CHAO_SHAPE_H_
#define _SA2B_CHAO_SHAPE_H_

/************************/
/*  Includes            */
/************************/
#include <sa2b/ninja/ninja.h>

/************************/
/*  Abstract Types      */
/************************/
typedef struct task        TASK;

/************************/
/*  Structures          */
/************************/
typedef struct
{
    NJS_POINT3 Pos;
    NJS_POINT3 Normal;
}
CNK_VN_VERTEX;

typedef struct
{
    NJS_POINT3 Velo;
    float Weight;
    float Spring;
    float Friction;
}
AL_VERTEX_INFO;

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

typedef struct
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
}
AL_BUYO_PARAM;

typedef struct al_object
{
    uint32_t EvalFlags;
    AL_MODEL* pModel;
    float Pos[3];
    int32_t Ang[3];
    float Scl[3];
    struct al_object* pChild;
    struct al_object* pSibling;
    struct al_object* pParent;
    NJS_POINT3 diff;
    NJS_POINT3 GlobalAimPos;
    NJS_POINT3 OrgPos;
    NJS_POINT3 Velo;
    NJS_POINT3 OrgAng;
    NJS_POINT3 AngSpd;
    float Weight;
    float Spring;
    float Friction;
    int32_t NoBuyoFlag;
    int32_t CalcBuyoPosFlag;
    NJS_CNK_OBJECT* pPartsObject;
    NJS_CNK_OBJECT* pItemObject;
    NJS_TEXLIST* pItemTexlist;
    float ItemScale;
    int32_t ItemActiveFlag;
    int32_t ItemOffsetFlag;
    NJS_POINT3 ItemOffsetPos;
    Angle3 ItemOffsetAng;
    float(*pOldMatrix)[16];
    AL_BUYO_PARAM* pBuyoParam;
    void* DisplayList;
}
AL_OBJECT;

typedef struct al_group_object_list
{
    NJS_CNK_OBJECT* child[40];
    NJS_CNK_OBJECT* normal[40];
    NJS_CNK_OBJECT* swim[40];
    NJS_CNK_OBJECT* fly[40];
    NJS_CNK_OBJECT* run[40];
    NJS_CNK_OBJECT* power[40];
}
AL_GROUP_OBJECT_LIST;

/************************/
/*  Data                */
/************************/
typedef NJS_CNK_OBJECT*         AL_RootObject_t[144];

/** Chao root models - points into 'Data.dll' **/
#define AL_RootObject           DataRef(AL_RootObject_t*, 0x01AED294)

/** Internal data **/
#define ratio_h                 DataRef(float32_t       , 0x01DB1068)
#define inv_ratio_h             DataRef(float32_t       , 0x01DB1088)

#define ratio_v                 DataRef(float32_t       , 0x01DB1084)
#define inv_ratio_v             DataRef(float32_t       , 0x01DB1070)

#define ratio_g                 DataRef(float32_t       , 0x01DB102C)
#define inv_ratio_g             DataRef(float32_t       , 0x01DB1028)

#define div_ratio_h             DataRef(float32_t       , 0x01DB109C)
#define div_ratio_v             DataRef(float32_t       , 0x01DB108C)

#define col_ratio_h             DataRef(float32_t       , 0x01DB1038)
#define col_ratio_v             DataRef(float32_t       , 0x01DB1060)
#define col_ratio_g             DataRef(float32_t       , 0x01DB1054)

#define col_inv_ratio_h         DataRef(float32_t       , 0x01DB1098)
#define col_inv_ratio_v         DataRef(float32_t       , 0x01DB106C)
#define col_inv_ratio_g         DataRef(float32_t       , 0x01DB1078)

#define col_div_ratio_h         DataRef(float32_t       , 0x01DB1034)
#define col_div_ratio_v         DataRef(float32_t       , 0x01DB1030)

/** Object lists **/
#define CurrObjectList          DataRef(AL_OBJECT**     , 0x01DB1074)

#define ZeroObjectList          DataRef(NJS_CNK_OBJECT**, 0x01DB1050)
#define NormalObjectList        DataRef(NJS_CNK_OBJECT**, 0x01DB105C)
#define HorizonObjectList       DataRef(NJS_CNK_OBJECT**, 0x01DB107C)
#define VerticalObjectList      DataRef(NJS_CNK_OBJECT**, 0x01DB1064)

#define ZeroObjectListH         DataRef(NJS_CNK_OBJECT**, 0x01DB1048)
#define NormalObjectListH       DataRef(NJS_CNK_OBJECT**, 0x01DB1058)
#define HorizonObjectListH      DataRef(NJS_CNK_OBJECT**, 0x01DB103C)
#define VerticalObjectListH     DataRef(NJS_CNK_OBJECT**, 0x01DB1090)

#define ZeroObjectListD         DataRef(NJS_CNK_OBJECT**, 0x01DB1080)
#define NormalObjectListD       DataRef(NJS_CNK_OBJECT**, 0x01DB1044)
#define HorizonObjectListD      DataRef(NJS_CNK_OBJECT**, 0x01DB1094)
#define VerticalObjectListD     DataRef(NJS_CNK_OBJECT**, 0x01DB104C)

/************************/
/*  Functions           */
/************************/
EXTERN_START
/** Initialize Chao shape data **/
int32_t  AL_ShapeInit(TASK* tp);

/** Copy and free chao object **/
AL_OBJECT*  AL_CopyChaoObject(NJS_CNK_OBJECT* pSrcObject, NJS_CNK_OBJECT* pChildObject, AL_OBJECT* pParentObject);
void        AL_FreeChaoObject(AL_OBJECT* pObject);

/** Internal functions **/
int32_t  AL_CreateOrgVertexList(AL_OBJECT* pObject);
int32_t  GetList(AL_OBJECT* pSrcObject, AL_OBJECT** List, int32_t num);
void    AL_GetObjectList(AL_OBJECT* pSrcObject, AL_OBJECT** List);

EXTERN_END

/************************/
/*  Function Ptrs       */
/************************/
#ifdef SAMT_INCLUDE_FUNC_PTRS
/** Function ptrs **/
#define AL_ShapeInit_p              FuncPtr(int32_t    , __cdecl, (TASK*)                                       , 0x0056C9D0)
#define AL_CopyChaoObject_p         FuncPtr(AL_OBJECT*, __cdecl, (NJS_CNK_OBJECT*, NJS_CNK_OBJECT*, AL_OBJECT*), 0x0056BED0)
#define AL_FreeChaoObject_p         FuncPtr(void      , __cdecl, (AL_OBJECT*)                                  , 0x0056BD40)
#define AL_CreateOrgVertexList_p    FuncPtr(int32_t    , __cdecl, (AL_OBJECT*)                                  , 0x0056C800)
#define GetList_p                   FuncPtr(int32_t    , __cdecl, (AL_OBJECT*, AL_OBJECT**, int32_t)             , 0x0056BC90)

/** User-Function ptrs **/
EXTERN const void* const AL_GetObjectList_p;

#endif /* SAMT_INCLUDE_FUNC_PTRS */

#endif /* _SA2B_CHAO_SHAPE_H_ */
