/*
*   Sonic Adventure Mod Tools (SA2B) - '/sonic/landtable.h'
*
*   Description:
*       Contains functions and structs related to LandTables.
*
*   Contributors:
*     - SEGA - Sonic Team,
*     - Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC
*/
#ifndef _SA2B_LANDTABLE_H_
#define _SA2B_LANDTABLE_H_

/************************/
/*  Abstract types      */
/************************/
typedef struct task        task;
typedef struct zxsdwstr    zxsdwstr;

/************************/
/*  Includes            */
/************************/
#include <sa2b/ninja/ninja.h>

#include <sa2b/util/anyobj.h>

/************************/
/*  Land Entry Flags    */
/************************/
#define LANDATTR_GROUND         (0x00000001) /* collision: ground                   */
#define LANDATTR_WATER          (0x00000002) /* collision: water, swimable          */
#define LANDATTR_DIGGABLE       (0x00000020)
#define LANDATTR_NOCLIMB        (0x00000080)
#define LANDATTR_STAIRS         (0x00000100)
#define LANDATTR_HURT           (0x00000400)
#define LANDATTR_FOOTSTEPS      (0x00000800)
#define LANDATTR_NOLANDING      (0x00001000)
#define LANDATTR_WATER_SLOW     (0x00002000) /* collision: water, slow movement     */
#define LANDATTR_NOSHADOW       (0x00008000) /* no shadow maps                      */
#define LANDATTR_ACCELERATE     (0x00100000)
#define LANDATTR_NOFOG          (0x00400000) /* disable fog for land entry          */
#define LANDATTR_MAXCLIP        (0x00800000) /* ignore LT far clip and use nj clip  */
#define LANDATTR_COMPILED       (0x02000000) /* compiled with DirectCompile         */
#define LANDATTR_NOCOMPILE      (0x04000000) /* don't compile model                 */
#define LANDATTR_DYNAMIC        (0x08000000)
#define LANDATTR_UNK1           (0x20000000) // Usually medium-sized collisions
#define LANDATTR_UNK2           (0x40000000) // Usually small-sized collisions
#define LANDATTR_DRAW           (0x80000000) /* land entry is to be drawn           */

/************************/
/*  Structures          */
/************************/
typedef struct _OBJ_LANDENTRY
{
    f32         xCenter;        /* center, x                                        */
    f32         yCenter;        /* center, y                                        */
    f32         zCenter;        /* center, z                                        */
    f32         r;              /* radius                                           */
    ANY_OBJECT* pObject;        /* object pointer, chunk or ginja                   */
    void*       pDirect;        /* direct compiled model pointer                    */
    s32         blockbit;       /* draw model bitmask, 0 ignores it                 */
    s32         slAttribute;    /* land attributes                                  */
}
OBJ_LANDENTRY;

typedef struct _OBJ_MOTLANDENTRY
{
    f32             fFrame;
    f32             fStep;
    f32             fMaxFrame;
    NJS_CNK_OBJECT* pObject;
    NJS_MOTION*     pMotion;
}
OBJ_MOTLANDENTRY;

typedef struct _OBJ_LANDTABLE
{
    s16                 ssCount;            /* land entry count     */
    s16                 ssVisibleCount;     /* visible entry count  */
    s16                 ssUnknown;          /* ??????               */
    s16                 ssMotCount;         /* motion entry count   */
    s16                 ssAttribute;        /* attribute            */
    s16                 ssLoadFlag;         /* is loaded            */
    f32                 fFarClipping;       /* clip distance        */
    OBJ_LANDENTRY*      pLandEntry;         /* land entry list      */
    OBJ_MOTLANDENTRY*   pMotLandEntry;      /* motion entry list    */
    char*               TexName;            /* texture file name    */
    NJS_TEXLIST*        TexList;            /* texlist              */
}
OBJ_LANDTABLE;

typedef struct _OBJ_LANDCOLL
{
    s32         slAttribute;
    NJS_OBJECT* pObject;
    task*       ptask;
}
OBJ_LANDCOLL;

/************************/
/*  Data                */
/************************/
#define LandTaskP               DATA_REF(task*         , 0x01945A04)

#define boolLandTableGinja      DATA_REF(b32           , 0x01A5A2D8)
#define mleriRangeRad           DATA_REF(f32           , 0x0171CAA4)
#define pObjLandTable           DATA_REF(OBJ_LANDTABLE*, 0x019459DC)

#define boolLandDisplay         DATA_REF(b32           , 0x0171CAA8)
#define boolLandCollision       DATA_REF(b32           , 0x0171CAAC)

#define ri_landentry_buf        DATA_REF(OBJ_LANDENTRY*, 0x01A5A2D4)
#define ri_landentry_nmb        DATA_REF(int32_t       , 0x01A5A2CC)

#define numLandCollList         DATA_REF(int16_t       , 0x01DE9484)
#define ri_landcoll_nmb         DATA_REF(int32_t       , 0x01A5A2C8)

#define LandCollList            DATA_REF(OBJ_LANDCOLL* , 0x01A5A2DC)

#define MobileEntry             DATA_REF(OBJ_LANDCOLL* , 0x01A5A2E0)
#define numMobileEntry          DATA_REF(int16_t       , 0x019459D4)

/************************/
/*  Functions           */
/************************/
EXTERN_START
int32_t LandChangeLandTable(OBJ_LANDTABLE* land);

/*
*   Description:
*     Free the LandManager task
*/
void    LandFree(void);

int32_t LandChangeGinjaLandTable(OBJ_LANDTABLE* land);
int32_t LandChangeChunkLandTable(OBJ_LANDTABLE* land);

void    ListGroundForCollision(f32 xPosition, f32 yPosition, f32 zPosition, f32 fRadius);

int32_t CL_ColPolCheckZxShadow(zxsdwstr* zssp, NJS_OBJECT* obp);

EXTERN_END

/************************/
/*  Function Ptrs       */
/************************/
#ifdef SAMT_INCL_FUNCPTRS
/** Function ptrs **/
#   define ListGroundForCollision_p    FUNC_PTR(void   , __cdecl, (f32, f32, f32, f32), 0x0047CD60)
#   define LandChangeLandTable_p       FUNC_PTR(int32_t, __cdecl, (OBJ_LANDTABLE*)    , 0x0047BD30)

/** User-Function ptrs **/
#   define LandChangeGinjaLandTable_p  ((void*)0x0047BE10)
#   define CL_ColPolCheckZxShadow_p    ((void*)0x0048C290)

#endif/*SAMT_INCL_FUNCPTRS*/

#endif/*_SA2B_LANDTABLE_H_*/
