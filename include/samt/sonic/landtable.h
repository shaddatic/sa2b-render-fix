/*
*   SAMT for Sonic Adventure 2 (PC, 2012) - '/sonic/landtable.h'
*
*   Description:
*       Contains functions and structs related to LandTables.
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
#include <samt/ninja/ninja.h>

#include <samt/util/anyobj.h>

/************************/
/*  Land Entry Flags    */
/************************/
/****** Land Collision Flags ********************************************************/
#define LANDCOLL_GROUND         (1<< 0) /* solid                                    */
#define LANDCOLL_WATER          (1<< 1) /* water, swimable                          */
#define LANDCOLL_LOWFRICT       (1<< 2) /* low friction, icy                        */
#define LANDCOLL_HIGHFRICT      (1<< 3) /* high friction, sticky                    */
#define LANDCOLL_MEDFRICT       (1<< 4) /* medium friction, slow                    */
#define LANDCOLL_DIGGABLE       (1<< 5) /* can be dug by hunters                    */
#define LANDCOLL_UNK_06         (1<< 6)
#define LANDCOLL_NOCLIMB        (1<< 7) /* can't be climbed on by hunters           */
#define LANDCOLL_STAIRS         (1<< 8) /* player stands straight, always           */
#define LANDCOLL_UNK_09         (1<< 9)
#define LANDCOLL_HURT           (1<<10) /* hurts player on contact                  */
#define LANDCOLL_FOOTSTEPS      (1<<11) /* produce footprints                       */
#define LANDCOLL_NOSTAND        (1<<12) /* player cannot stand on surface           */
#define LANDCOLL_WATERSLOW      (1<<13) /* water, slow movement                     */
#define LANDCOLL_UNK_14         (1<<14)
#define LANDCOLL_UNK_16         (1<<16)
#define LANDCOLL_UNK_17         (1<<17)
#define LANDCOLL_UNK_18         (1<<18)
#define LANDCOLL_UNK_19         (1<<19)
#define LANDCOLL_HIGHSPEED      (1<<20) /* top speed increased, faster accel        */
#define LANDCOLL_HIGHACCEL      (1<<21) /* faster accel, same top speed             */
#define LANDCOLL_HIGHGRAV       (1<<22) /* increased gravity                        */
#define LANDCOLL_UNK_24         (1<<24) /* ??? easy to pass through                 */
#define LANDCOLL_MOBILE         (1<<27) /* collision entry moves                    */
#define LANDCOLL_UNITROT        (1<<28) /* don't rotate collisions                  */
#define LANDCOLL_SMALLRAD       (1<<29) /* small coll radius                        */
#define LANDCOLL_TINYRAD        (1<<30) /* tiny coll radius                         */

#define LANDATTR_MINIRAD    (LANDATTR_SMALLRAD|LANDATTR_TINYRAD) /* mini coll rad   */

/****** Land Draw Flags *************************************************************/
#define LANDDRAW_NOSHADOW       (1<<15) /* no shadow maps                           */
#define LANDDRAW_NOFOG          (1<<22) /* disable fog for land entry               */
#define LANDDRAW_MAXCLIP        (1<<23) /* ignore LT far clip and use nj clip       */
#define LANDDRAW_SIMPLEDRAW     (1<<24) /* use SimpleDraw, else EasyDraw            */
#define LANDDRAW_DIRECTDRAW     (1<<25) /* use DirectDraw                (internal) */
#define LANDDRAW_NOCOMPILE      (1<<26) /* don't compile model, use other draw      */
#define LANDDRAW_DRAW           (1<<31) /* land entry is to be drawn                */

/************************/
/*  Structures          */
/************************/
typedef struct _OBJ_LANDENTRY
{
    f32         xCenter;        /* center, x                                        */
    f32         yCenter;        /* center, y                                        */
    f32         zCenter;        /* center, z                                        */
    f32         r;              /* radius                                           */

    ANY_OBJECT* pObject;        /* object: basic, chunk, or ginja                   */
    void*       pDirect;        /* direct compiled object pointer                   */

    s32         blockbit;       /* draw model bitmask, 0 ignores it                 */

    s32         slAttribute;    /* land attributes                                  */
}
OBJ_LANDENTRY;

typedef struct _OBJ_MOTLANDENTRY
{
    f32             fFrame;     /* motion frame                                     */
    f32             fStep;      /* motion frame step                                */
    f32             fMaxFrame;  /* motion frame max                                 */

    NJS_CNK_OBJECT* pObject;    /* object                                           */
    NJS_MOTION*     pMotion;    /* motion                                           */
}
OBJ_MOTLANDENTRY;

typedef struct _OBJ_LANDTABLE
{
    s16                 ssCount;        /* total land entry count                   */

    s16                 ssCnkCount;     /* Chunk/Ginja land entry count  (optional) */
    s16                 ssUnkCount;     /* Unknown land entry count        (unused) */

    s16                 ssMotCount;     /* motion entry count                       */

    s16                 ssAttribute;    /* attribute                                */
    s16                 ssLoadFlag;     /* is loaded                                */

    f32                 fFarClipping;   /* clip distance                            */

    OBJ_LANDENTRY*      pLandEntry;     /* land entry list                          */
    OBJ_MOTLANDENTRY*   pMotLandEntry;  /* motion entry list                        */

    char*               pPvmFileName;   /* texture file name                        */
    NJS_TEXLIST*        pTexList;       /* texlist                                  */
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

#define  pObjLandEntry          DATA_REF(OBJ_LANDENTRY**, 0x01A5A2E4)
#define nbObjLandEntry          DATA_REF(s16            , 0x01945A00)

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
