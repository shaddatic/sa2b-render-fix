/*
*   Sonic Adventure Mod Tools (SA2B) - '/sonic/chao/al_shape.h'
*
*   Description:
*       Contains structs, data, and functions related to Chao
*   models.
*
*   Contributors:
*     - SEGA - Sonic Team,
*     - Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC
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
typedef struct task        task;

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
#define AL_RootObject           DATA_REF(AL_RootObject_t*, 0x01AED294)

/** Internal data **/
#define ratio_h                 DATA_REF(f32             , 0x01DB1068)
#define inv_ratio_h             DATA_REF(f32             , 0x01DB1088)

#define ratio_v                 DATA_REF(f32             , 0x01DB1084)
#define inv_ratio_v             DATA_REF(f32             , 0x01DB1070)

#define ratio_g                 DATA_REF(f32             , 0x01DB102C)
#define inv_ratio_g             DATA_REF(f32             , 0x01DB1028)

#define div_ratio_h             DATA_REF(f32             , 0x01DB109C)
#define div_ratio_v             DATA_REF(f32             , 0x01DB108C)

#define col_ratio_h             DATA_REF(f32             , 0x01DB1038)
#define col_ratio_v             DATA_REF(f32             , 0x01DB1060)
#define col_ratio_g             DATA_REF(f32             , 0x01DB1054)

#define col_inv_ratio_h         DATA_REF(f32             , 0x01DB1098)
#define col_inv_ratio_v         DATA_REF(f32             , 0x01DB106C)
#define col_inv_ratio_g         DATA_REF(f32             , 0x01DB1078)

#define col_div_ratio_h         DATA_REF(f32             , 0x01DB1034)
#define col_div_ratio_v         DATA_REF(f32             , 0x01DB1030)

/** Object lists **/
#define CurrObjectList          DATA_REF(AL_OBJECT**     , 0x01DB1074)

#define ZeroObjectList          DATA_REF(NJS_CNK_OBJECT**, 0x01DB1050)
#define NormalObjectList        DATA_REF(NJS_CNK_OBJECT**, 0x01DB105C)
#define HorizonObjectList       DATA_REF(NJS_CNK_OBJECT**, 0x01DB107C)
#define VerticalObjectList      DATA_REF(NJS_CNK_OBJECT**, 0x01DB1064)

#define ZeroObjectListH         DATA_REF(NJS_CNK_OBJECT**, 0x01DB1048)
#define NormalObjectListH       DATA_REF(NJS_CNK_OBJECT**, 0x01DB1058)
#define HorizonObjectListH      DATA_REF(NJS_CNK_OBJECT**, 0x01DB103C)
#define VerticalObjectListH     DATA_REF(NJS_CNK_OBJECT**, 0x01DB1090)

#define ZeroObjectListD         DATA_REF(NJS_CNK_OBJECT**, 0x01DB1080)
#define NormalObjectListD       DATA_REF(NJS_CNK_OBJECT**, 0x01DB1044)
#define HorizonObjectListD      DATA_REF(NJS_CNK_OBJECT**, 0x01DB1094)
#define VerticalObjectListD     DATA_REF(NJS_CNK_OBJECT**, 0x01DB104C)

/************************/
/*  Functions           */
/************************/
EXTERN_START
/** Initialize Chao shape data **/
int32_t AL_ShapeInit( task* tp );

/** Copy and free chao object **/
AL_OBJECT*  AL_CopyChaoObject( NJS_CNK_OBJECT* pSrcObject, NJS_CNK_OBJECT* pChildObject, AL_OBJECT* pParentObject );
void        AL_FreeChaoObject( AL_OBJECT* pObject );

/** Internal functions **/
int32_t AL_CreateOrgVertexList( AL_OBJECT* pObject );
int32_t GetList( AL_OBJECT* pSrcObject, AL_OBJECT** List, int32_t num );
void    AL_GetObjectList( AL_OBJECT* pSrcObject, AL_OBJECT** List );

EXTERN_END

/************************/
/*  Function Ptrs       */
/************************/
#ifdef  SAMT_INCL_FUNCPTRS
/** Function ptrs **/
#   define AL_ShapeInit_p               FUNC_PTR(int32_t    , __cdecl, (task*)                                       , 0x0056C9D0)
#   define AL_CopyChaoObject_p          FUNC_PTR(AL_OBJECT*, __cdecl, (NJS_CNK_OBJECT*, NJS_CNK_OBJECT*, AL_OBJECT*), 0x0056BED0)
#   define AL_FreeChaoObject_p          FUNC_PTR(void      , __cdecl, (AL_OBJECT*)                                  , 0x0056BD40)
#   define AL_CreateOrgVertexList_p     FUNC_PTR(int32_t    , __cdecl, (AL_OBJECT*)                                  , 0x0056C800)
#   define GetList_p                    FUNC_PTR(int32_t    , __cdecl, (AL_OBJECT*, AL_OBJECT**, int32_t)             , 0x0056BC90)

/** User-Function ptrs **/
#   define AL_GetObjectList_p           ((void*)0x0056BCD0)

#endif/*SAMT_INCL_FUNCPTRS*/

#endif/*_SA2B_CHAO_SHAPE_H_*/
