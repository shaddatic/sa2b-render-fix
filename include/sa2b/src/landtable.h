/*
*   Sonic Adventure Mod Tools (SA2B) - '/src/landtable.h'
*
*   Description:
*       Contains functions and structs related to LandTables.
*
*   Contributors:
*   -   SEGA - Sonic Team,
*   -   Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC.
*/
#ifndef _SA2B_LANDTABLE_H_
#define _SA2B_LANDTABLE_H_

/************************/
/*  Abstract types      */
/************************/
typedef struct task        TASK;
typedef struct zxsdwstr    ZXSDWSTR;

/************************/
/*  Includes            */
/************************/
#include <sa2b/ninja/ninja.h>

#include <sa2b/util/anyobj.h>

/************************/
/*  Land Entry Flags    */
/************************/
#define LANDATTR_SOLID          (0x00000001)
#define LANDATTR_WATER          (0x00000002)
#define LANDATTR_DIGGABLE       (0x00000020)
#define LANDATTR_NOCLIMB        (0x00000080)
#define LANDATTR_STAIRS         (0x00000100)
#define LANDATTR_HURT           (0x00000400)
#define LANDATTR_FOOTSTEPS      (0x00000800)
#define LANDATTR_NOLANDING      (0x00001000)
#define LANDATTR_NOALPHA        (0x00002000)
#define LANDATTR_NOSHADOW       (0x00008000)
#define LANDATTR_ACCELERATE     (0x00100000)
#define LANDATTR_NOFOG          (0x00400000)
#define LANDATTR_DYNAMIC        (0x08000000)
#define LANDATTR_UNK1           (0x20000000) // Usually medium-sized collisions
#define LANDATTR_UNK2           (0x40000000) // Usually small-sized collisions
#define LANDATTR_VISIBLE        (0x80000000)

/************************/
/*  Structures          */
/************************/
typedef struct _OBJ_LANDENTRY
{
    float32_t   CenterX;
    float32_t   CenterY;
    float32_t   CenterZ;
    float32_t   Radius;
    ANY_OBJECT* pObject;
    int32_t     field_14;
    int32_t     Chunks;
    int32_t     slAttribute;
}
OBJ_LANDENTRY;

typedef struct _OBJ_MOTLANDENTRY
{
    float32_t   fFrame;
    float32_t   fStep;
    float32_t   fMaxFrame;
    ANY_OBJECT* pObject;
    NJS_MOTION* pMotion;
}
OBJ_MOTLANDENTRY;

typedef struct _OBJ_LANDTABLE
{
    int16_t             ssCount;            /* land entry count     */
    int16_t             ssVisibleCount;     /* visible entry count  */
    int16_t             ssUnknown;          /* ??????               */
    int16_t             ssMotCount;         /* motion entry count   */
    int16_t             ssAttribute;        /* attribute            */
    int16_t             ssLoadFlag;         /* is loaded            */
    float32_t           fFarClipping;       /* clip distance        */
    OBJ_LANDENTRY*      pLandEntry;         /* land entry list      */
    OBJ_MOTLANDENTRY*   pMotLandEntry;      /* motion entry list    */
    char*               TexName;            /* texture file name    */
    NJS_TEXLIST*        TexList;            /* texlist              */
}
OBJ_LANDTABLE;

typedef struct _OBJ_LANDCOLL
{
    int         slAttribute;
    NJS_OBJECT* pObject;
    TASK*       pTask;
}
OBJ_LANDCOLL;

/************************/
/*  Data                */
/************************/
#define pLandTask               DataRef(TASK*         , 0x01945A04)

#define boolLandTableGinja      DataRef(bool32_t      , 0x01A5A2D8)
#define mleriRangeRad           DataRef(float32_t     , 0x0171CAA4)
#define pObjLandTable           DataRef(OBJ_LANDTABLE*, 0x019459DC)

#define boolLandDisplay         DataRef(bool32_t      , 0x0171CAA8)
#define boolLandCollision       DataRef(bool32_t      , 0x0171CAAC)

#define ri_landentry_buf        DataRef(OBJ_LANDENTRY*, 0x01A5A2D4)
#define ri_landentry_nmb        DataRef(int32_t       , 0x01A5A2CC)

#define numLandCollList         DataRef(int16_t       , 0x01DE9484)
#define ri_landcoll_nmb         DataRef(int32_t       , 0x01A5A2C8)

#define LandCollList            DataRef(OBJ_LANDCOLL* , 0x01A5A2DC)

#define MobileEntry             DataRef(OBJ_LANDCOLL* , 0x01A5A2E0)
#define numMobileEntry          DataRef(int16_t       , 0x019459D4)

/************************/
/*  Functions           */
/************************/
EXTERN_START
int32_t LandChangeLandTable(OBJ_LANDTABLE* land);

int32_t LandChangeGinjaLandTable(OBJ_LANDTABLE* land);
int32_t LandChangeChunkLandTable(OBJ_LANDTABLE* land);

void    ListGroundForCollision(float32_t xPosition, float32_t yPosition, float32_t zPosition, float32_t fRadius);

int32_t CL_ColPolCheckZxShadow(ZXSDWSTR* zssp, NJS_OBJECT* obp);

EXTERN_END

/************************/
/*  Function Ptrs       */
/************************/
#ifdef SAMT_INCLUDE_FUNC_PTRS
/** Function ptrs **/
#   define ListGroundForCollision_p    FuncPtr(void   , __cdecl, (float32_t, float32_t, float32_t, float32_t), 0x0047CD60)
#   define LandChangeLandTable_p       FuncPtr(int32_t, __cdecl, (OBJ_LANDTABLE*)                            , 0x0047BD30)

/** User-Function ptrs **/
#   define LandChangeGinjaLandTable_p  ((void*)0x0047BE10)
#   define CL_ColPolCheckZxShadow_p    ((void*)0x0048C290)

#endif/*SAMT_INCLUDE_FUNC_PTRS*/

#endif/*_SA2B_LANDTABLE_H_*/
