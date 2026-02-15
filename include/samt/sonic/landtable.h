/*
*   SAMT for Sonic Adventure 2 (PC, 2012) - '/sonic/landtable.h'
*
*   Description:
*     Land header.
*/
#ifndef H_SA2B_LANDTABLE
#define H_SA2B_LANDTABLE

/********************************/
/*  Includes                    */
/********************************/
/****** Task ************************************************************************************/
#include <samt/ninja/ninja.h>       /* ninja                                                    */

/****** Task ************************************************************************************/
#include <samt/util/anyobj.h>       /* any object                                               */

EXTERN_START

/********************************/
/*  Opaque Types                */
/********************************/
/****** Task ************************************************************************************/
typedef struct task                 task;     /* task                                           */

/****** Zx Shadow *******************************************************************************/
typedef struct zxsdwstr             zxsdwstr; /* zx shadow structure                            */

/********************************/
/*  Constants                   */
/********************************/
/****** Land Collision Flags ********************************************************************/
#define LANDCOLL_GROUND         (1<< 0) /* solid                                                */
#define LANDCOLL_WATER          (1<< 1) /* water, swimable                                      */
#define LANDCOLL_LOWFRICT       (1<< 2) /* low friction, icy                                    */
#define LANDCOLL_HIGHFRICT      (1<< 3) /* high friction, sticky                                */
#define LANDCOLL_MEDFRICT       (1<< 4) /* medium friction, slow                                */
#define LANDCOLL_DIGGABLE       (1<< 5) /* can be dug by hunters                                */
#define LANDCOLL_UNK_06         (1<< 6)
#define LANDCOLL_NOCLIMB        (1<< 7) /* can't be climbed on by hunters                       */
#define LANDCOLL_STAIRS         (1<< 8) /* player stands straight, always                       */
#define LANDCOLL_UNK_09         (1<< 9)
#define LANDCOLL_HURT           (1<<10) /* hurts player on contact                              */
#define LANDCOLL_FOOTSTEPS      (1<<11) /* produce footprints                                   */
#define LANDCOLL_NOSTAND        (1<<12) /* player cannot stand on surface                       */
#define LANDCOLL_WATERSLOW      (1<<13) /* water, slow movement                                 */
#define LANDCOLL_UNK_14         (1<<14)
#define LANDCOLL_UNK_16         (1<<16)
#define LANDCOLL_UNK_17         (1<<17)
#define LANDCOLL_UNK_18         (1<<18)
#define LANDCOLL_UNK_19         (1<<19)
#define LANDCOLL_HIGHSPEED      (1<<20) /* top speed increased, faster accel                    */
#define LANDCOLL_HIGHACCEL      (1<<21) /* faster accel, same top speed                         */
#define LANDCOLL_HIGHGRAV       (1<<22) /* increased gravity                                    */
#define LANDCOLL_UNK_24         (1<<24) /* ??? easy to pass through                             */
#define LANDCOLL_MOBILE         (1<<27) /* collision entry moves                                */
#define LANDCOLL_UNITROT        (1<<28) /* don't rotate collisions                              */
#define LANDCOLL_SMALLRAD       (1<<29) /* small coll radius                                    */
#define LANDCOLL_TINYRAD        (1<<30) /* tiny coll radius                                     */

#define LANDATTR_MINIRAD    (LANDATTR_SMALLRAD|LANDATTR_TINYRAD) /* mini coll rad               */

/****** Land Draw Flags *************************************************************************/
#define LANDDRAW_NOSHADOW       (1<<15) /* no shadow maps                                       */
#define LANDDRAW_NOFOG          (1<<22) /* disable fog for land entry                           */
#define LANDDRAW_MAXCLIP        (1<<23) /* ignore LT far clip and use nj clip                   */
#define LANDDRAW_SIMPLEDRAW     (1<<24) /* use SimpleDraw, else EasyDraw                        */
#define LANDDRAW_DIRECTDRAW     (1<<25) /* use DirectDraw                            [internal] */
#define LANDDRAW_NOCOMPILE      (1<<26) /* don't compile model, use other draw                  */
#define LANDDRAW_DRAW           (1<<31) /* land entry is to be drawn                            */

/********************************/
/*  Structures                  */
/********************************/
/****** Land Entry ******************************************************************************/
typedef struct _OBJ_LANDENTRY
{
    f32              xCenter;       /* center, x                                                */
    f32              yCenter;       /* center, y                                                */
    f32              zCenter;       /* center, z                                                */
    f32              radius;        /* radius                                                   */

    ANY_OBJECT*      pObject;       /* object: basic, chunk, or ginja                           */
    NJS_DIRECT_HEAD* pDirectObject; /* direct compiled object                                   */

    i32              blockbit;      /* draw model bitmask, 0 ignores it                         */
                     
    i32              slAttribute;   /* land attributes                                          */
}
OBJ_LANDENTRY;

/****** Land Motion Entry ***********************************************************************/
typedef struct _OBJ_MOTLANDENTRY
{
    f32             fFrame;         /* motion frame                                             */
    f32             fStep;          /* motion frame step                                        */
    f32             fMaxFrame;      /* motion frame max                                         */

    NJS_CNK_OBJECT* pObject;        /* object                                                   */
    NJS_MOTION*     pMotion;        /* motion                                                   */
}
OBJ_MOTLANDENTRY;

/****** Land Table ******************************************************************************/
typedef struct _OBJ_LANDTABLE
{
    i16                 ssCount;           /* total land entry count                            */

    i16                 ssDispCount;       /* Chunk/Ginja land entry count           [optional] */
    i16                 ssDirectDispCount; /* direct land entry count                 [dc only] */

    i16                 ssMotCount;        /* motion entry count                                */

    i16                 ssAttribute;       /* attribute                                         */
    i16                 ssLoadFlag;        /* is loaded                                         */

    f32                 fFarClipping;      /* clip distance                                     */

    OBJ_LANDENTRY*      pLandEntry;        /* land entry list                                   */
    OBJ_MOTLANDENTRY*   pMotLandEntry;     /* motion entry list                                 */

    char*               pPvmFileName;      /* texture file name                                 */
    NJS_TEXLIST*        pTexList;          /* texlist                                           */
}
OBJ_LANDTABLE;

/****** Land Collision **************************************************************************/
typedef struct _OBJ_LANDCOLL
{
    i32                 slAttribute; /* attributes                                              */
    NJS_OBJECT*         pObject;     /* collision object                                        */
    task*               ptask;       /* task pointer                                 [optional] */
}
OBJ_LANDCOLL;

/********************************/
/*  Data                        */
/********************************/
/****** Task ************************************************************************************/
#define LandTaskP               DATA_REF(task*         , 0x01945A04)

/****** Land Flags ******************************************************************************/
#define boolLandDisplay         DATA_REF(b32           , 0x0171CAA8)
#define boolLandCollision       DATA_REF(b32           , 0x0171CAAC)
#define boolLandGjmdl           DATA_REF(b32           , 0x01A5A2D8)

/****** Land Clip Range *************************************************************************/
#define mleriRangeRad           DATA_REF(f32           , 0x0171CAA4)

/****** Land Table ******************************************************************************/
#define pObjLandTable           DATA_REF(OBJ_LANDTABLE*, 0x019459DC)

/****** Land Entries ****************************************************************************/
#define  pObjLandEntry          DATA_REF(OBJ_LANDENTRY**, 0x01A5A2E4)
#define nbObjLandEntry          DATA_REF(i16            , 0x01945A00)

/****** Land Mobile Entries *********************************************************************/
#define MobileEntry             DATA_REF(OBJ_LANDCOLL* , 0x01A5A2E0)
#define numMobileEntry          DATA_REF(int16_t       , 0x019459D4)

/****** Land Entry Work *************************************************************************/
#define ri_landentry_buf        DATA_REF(OBJ_LANDENTRY*, 0x01A5A2D4)
#define ri_landentry_nmb        DATA_REF(int32_t       , 0x01A5A2CC)

/****** Land Collision **************************************************************************/
#define numLandCollList         DATA_REF(int16_t       , 0x01DE9484)
#define ri_landcoll_nmb         DATA_REF(int32_t       , 0x01A5A2C8)

/****** Land Collision Work *********************************************************************/
#define LandCollList            DATA_REF(OBJ_LANDCOLL* , 0x01A5A2DC)

/********************************/
/*  Prototypes                  */
/********************************/
/****** Land Manager ****************************************************************************/
/*
*   Description:
*     Create/re-create land manager task and set active landtable structure.
*
*   Notes:
*     - If Render Fix isn't installed, the 'boolLandTableGinja' must be set manually.
*
*   Parameters:
*     - land        : landtable
*
*   Returns:
*     'TRUE' if the landtable was changed/set; or 'FALSE' on failure.
*/
b32     LandChangeLandTable( OBJ_LANDTABLE* land );
/*
*   Description:
*     Create/re-create land manager task and set active landtable structure of a specific
*   format.
*
*   Notes:
*     - Same as regular function, except also sets 'boolLandTableGinja' variable.
*
*   Parameters:
*     - land        : landtable
*
*   Returns:
*     'TRUE' if the landtable was changed/set; or 'FALSE' on failure.
*/
b32     LandChangeGinjaLandTable( OBJ_LANDTABLE* land );
b32     LandChangeChunkLandTable( OBJ_LANDTABLE* land );
/*
*   Description:
*     Free the LandManager task, and by extension the active landtable.
*/
void    LandFree( void );

/****** Collision *******************************************************************************/
/*
*   Description:
*     Populate 'LandCollList' with land collisions in a radius around a given point.
*
*   Parameters:
*     - xyzPosition : position coordinates
*     - fRadius     : collision area radius
*/
void    ListGroundForCollision( f32 xPosition, f32 yPosition, f32 zPosition, f32 fRadius );

/****** Shadow **********************************************************************************/
/*
*   Description:
*     Get collision shadow info from collision object.
*
*   Parameters:
*     - zssp        : zx shadow; 'pos' must be populated, rest is for return           [in/out]
*     - obp         : object
*
*   Returns:
*     'TRUE' if the landtable was changed/set; or 'FALSE' on failure.
*/
b32     CL_ColPolCheckZxShadow( zxsdwstr* zssp, NJS_OBJECT* obp );

#ifdef SAMT_INCL_FUNCPTRS

/********************************/
/*  Function Pointers           */
/********************************/
/****** Function Pointers ***********************************************************************/
#define ListGroundForCollision_p        FUNC_PTR(void, __cdecl, (f32, f32, f32, f32), 0x0047CD60)
#define LandChangeLandTable_p           FUNC_PTR(i32 , __cdecl, (OBJ_LANDTABLE*)    , 0x0047BD30)

/****** Usercall Pointers ***********************************************************************/
#define LandChangeGinjaLandTable_p      ((void*)0x0047BE10) /* EAX(EAX)                         */
#define CL_ColPolCheckZxShadow_p        ((void*)0x0048C290) /* EAX(EDI,ECX)                     */

#endif/*SAMT_INCL_FUNCPTRS*/

EXTERN_END

#endif/*H_SA2B_LANDTABLE*/
