/*
*   SAMT for Sonic Adventure 2 (PC, 2012) - '/util/std_land.h'
*
*   Description:
*     Standard structures for the SA1 and SA2 LandTable formats.
*/
#ifndef H_SAMT_UTIL_STDLAND
#define H_SAMT_UTIL_STDLAND

/************************/
/*  External Headers    */
/************************/
/****** Game ************************************************************************/
#include <samt/sonic/landtable.h> /* landtable                                      */

EXTERN_START

/************************/
/*  Structures          */
/************************/
/************************************************************************************/
/*
*   Sonic Adventure 1
*/
/****** Land Entry ******************************************************************/
typedef struct
{
    f32         xCenter;        /* center, x                                        */
    f32         yCenter;        /* center, y                                        */
    f32         zCenter;        /* center, z                                        */

    f32         xWidth;         /* width, x                                         */
    f32         yWidth;         /* width, y                                         */
    f32         zWidth;         /* width, z                                         */

    NJS_OBJECT* pObject;        /* object                                           */

    s32         blockbit;       /* draw model bitmask, 0 ignores it                 */

    s32         slAttribute;    /* land attributes                                  */
}
SA1_LANDENTRY;

/****** Motion Entry ****************************************************************/
typedef struct
{
    f32          fFrame;        /* motion frame                                     */
    f32          fStep;         /* motion frame step                                */
    f32          fMaxFrame;     /* motion frame max                                 */

    NJS_OBJECT*  pObject;       /* object                                           */
    NJS_MOTION*  pMotion;       /* motion                                           */
    NJS_TEXLIST* pTexList;      /* texlist                                          */
}
SA1_MOTLANDENTRY;

/****** Land Table ******************************************************************/
typedef struct
{
    s16               ssCount;          /* land entry count                         */

    s16               ssMotCount;       /* motion entry count                       */

    s16               ssAttribute;      /* attribute                                */
    s16               ssLoadFlag;       /* is loaded                                */

    f32               fFarClipping;     /* clip distance                            */

    SA1_LANDENTRY*    pLandEntry;       /* land entry list                          */
    SA1_MOTLANDENTRY* pMotLandEntry;    /* motion entry list                        */

    char*             pPvmFileName;     /* texture file name                        */
    NJS_TEXLIST*      pTexList;         /* texlist                                  */

    char*             pBinaryFileName;  /* binary file name                         */
    void*             pLoadBinary;      /* binary                                   */
}
SA1_LANDTABLE;

/************************************************************************************/
/*
*   Sonic Adventure 2
*/
/****** Land Table ******************************************************************/
typedef struct _OBJ_LANDENTRY       SA2_LANDENTRY;    /* land entry                 */
typedef struct _OBJ_MOTLANDENTRY    SA2_MOTLANDENTRY; /* motion entry               */
typedef struct _OBJ_LANDTABLE       SA2_LANDTABLE;    /* land table                 */

EXTERN_END

#endif
