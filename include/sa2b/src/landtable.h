/*
*   Sonic Adventure Mod Tools (SA2B) - '/src/landtable.h'
*
*   Contains functions and structs related to LandTables
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
    float32         CenterX;
    float32         CenterY;
    float32         CenterZ;
    float32         Radius;
    ANY_OBJECT      pObject;
    sint32          field_14;
    sint32          Chunks;
    sint32          slAttribute;
}
OBJ_LANDENTRY;

typedef struct _OBJ_MOTLANDENTRY
{
    float32         fFrame;
    float32         fStep;
    float32         fMaxFrame;
    ANY_OBJECT      pObject;
    NJS_MOTION*     pMotion;
}
OBJ_MOTLANDENTRY;

typedef struct _OBJ_LANDTABLE
{
    sint16              ssCount;
    sint16              ssVisibleCount;
    sint16              ssUnkown; // ??
    sint16              ssMotCount;
    sint16              ssAttribute;
    sint16              ssLoadFlag;
    float32             fFarClipping;
    OBJ_LANDENTRY*      pLandEntry;
    OBJ_MOTLANDENTRY*   pMotLandEntry;
    char*               TexName;
    NJS_TEXLIST*        TexList;
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

#define boolLandTableGinja      DataRef(bool32        , 0x01A5A2D8)
#define mleriRangeRad           DataRef(float32       , 0x0171CAA4)
#define pObjLandTable           DataRef(OBJ_LANDTABLE*, 0x019459DC)

#define boolLandDisplay         DataRef(bool32        , 0x0171CAA8)
#define boolLandCollision       DataRef(bool32        , 0x0171CAAC)

#define ri_landentry_buf        DataRef(OBJ_LANDENTRY*, 0x01A5A2D4)
#define ri_landentry_nmb        DataRef(sint32        , 0x01A5A2CC)

#define numLandCollList         DataRef(sint16        , 0x01DE9484)
#define ri_landcoll_nmb         DataRef(sint32        , 0x01A5A2C8)

#define LandCollList            DataRef(OBJ_LANDCOLL* , 0x01A5A2DC)

#define MobileEntry             DataRef(OBJ_LANDCOLL* , 0x01A5A2E0)
#define numMobileEntry          DataRef(sint16        , 0x019459D4)

/************************/
/*  Functions           */
/************************/
EXTERN_START
sint32  LandChangeLandTable(OBJ_LANDTABLE* land);

sint32  LandChangeGinjaLandTable(OBJ_LANDTABLE* land);
sint32  LandChangeChunkLandTable(OBJ_LANDTABLE* land);

void    ListGroundForCollision(float32 xPosition, float32 yPosition, float32 zPosition, float32 fRadius);

sint32  CL_ColPolCheckZxShadow(ZXSDWSTR* zssp, NJS_OBJECT* obp);

EXTERN_END

/************************/
/*  Function Ptrs       */
/************************/
#ifdef SAMT_INCLUDE_FUNC_PTRS

/** Function ptrs **/
#define ListGroundForCollision_p    FuncPtr(void,   __cdecl, (float32, float32, float32, float32), 0x0047CD60)
#define LandChangeLandTable_p       FuncPtr(sint32, __cdecl, (OBJ_LANDTABLE*)                    , 0x0047BD30)

/** User-Function ptrs **/
EXTERN const void* const LandChangeGinjaLandTable_p;
EXTERN const void* const CL_ColPolCheckZxShadow_p;

#endif /* SAMT_INCLUDE_FUNC_PTRS */

#endif /* _SA2B_LANDTABLE_H_ */
