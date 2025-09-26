/*
*   SAMT for Sonic Adventure 2 (PC, 2012) - '/sonic/uvcng.h'
*
*   Description:
*     UV scrolling/texture animation utilities for Chunk and Ginja.
*/
#ifndef H_SA2B_UVCHG
#define H_SA2B_UVCHG

/********************************/
/*  Includes                    */
/********************************/
/****** Ninja ***********************************************************************************/
#include <samt/ninja/njcommon.h>    /* ninja common                                             */

EXTERN_START

/********************************/
/*  Structures                  */
/********************************/
/****** SAMT Structs ****************************************************************************/
typedef struct // SAMT Addition
{
    s16             plistoff;       /* chunk plist offset for strip                             */
    s16             adduvnum;       /* add uv number                                            */
    NJS_TEX         adduvs;         /* add uv value list                                        */
}
UVCHANGESTRIP;

typedef struct // SAMT Addition
{
    s16             stripnum;       /* strip count                                              */
    s16             stride;         /* strip stride in shorts, excluding uvs        [usually 1] */
    UVCHANGESTRIP   strips;         /* strip list                                               */
}
UVCHANGEATTR;

/****** UV Change Info **************************************************************************/
typedef struct
{
    u32             flag;               /* uv change flags                                      */
    u32             framecycle;         /* frame range                                          */
    u32             framepitch;         /* frame division value                                 */
    f32*            frameordertop;      /* frame order list                                     */
    s16*            ppattrnlisttop;     /* uv change attribute list              [UVCHANGEATTR] */
    s16*            ptexpattrnlisttop;  /* tex pointer attribute list                           */
    s16*            ptexanimlisttop;    /* tex animation list                                   */
    NJS_CNK_MODEL*  plastusedmodel;     /* last model pointer                                   */
    s16             lastaddu;           /* last u value                                         */
    s16             lastaddv;           /* last v value                                         */
}
UVCHANGEINFO;

/********************************/
/*  Prototypes                  */
/********************************/
/****** UV Change *******************************************************************************/
/*
*   Description:
*     Apply UV/texture animations to a Chunk model via a Uvc info.
*
*   Parameters:
*     - pModel      : chunk model
*     - pUvcInfo    : uv change info
*     - frame       : animation frame
*/
void    UvChangeCnk( NJS_CNK_MODEL* pModel, UVCHANGEINFO* pUvcInfo, s32 frame );

#ifdef SAMT_INCL_FUNCPTRS

/********************************/
/*  Function Pointers           */
/********************************/
/****** Usercall Pointers ***********************************************************************/
#define UvChangeCnk_p               ((void*)0x00795790) /* ###(STK, ESI, STK)                   */

#endif/*SAMT_INCL_FUNCPTRS*/

EXTERN_END

#endif/*H_SA2B_UVCHG*/
