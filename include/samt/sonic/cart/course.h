/*
*   SAMT for Sonic Adventure 2 (PC, 2012) - '/sonic/cart/course.h'
*
*   Description:
*     Cart course info for the cart racing minigame/story stages.
*/
#ifndef H_SA2B_CART_COURSE
#define H_SA2B_CART_COURSE

/********************************/
/*  Includes                    */
/********************************/
/****** Ninja ***********************************************************************************/
#include <samt/ninja/njcommon.h>    /* ninja common                                             */

/****** Game ************************************************************************************/
#include <samt/sonic/datadll.h>     /* data_dll                                                 */

EXTERN_START

/********************************/
/*  Structures                  */
/********************************/
/****** Course Info *****************************************************************************/
typedef struct
{
    NJS_POINT3          pos;              /* position                                           */
    Angle               AngY;             /* rotation                                           */
}
KANBAN_BASE;

typedef struct
{
    GJS_OBJECT*         forDisplay;       /* display object                         [cnk on dc] */
    NJS_OBJECT*         forCollision;     /* collision object                                   */
    NJS_POINT3          moveOffset;       /* position                                           */
    Angle               moveAngle;        /* angle                                              */
    u32                 point1[9];
    u32                 point2[9];
    NJS_DIRECT_HEAD*    forDirectDisplay; /* direct compiled display object           [dc only] */
    KANBAN_BASE*        kanbanBase;       /* poster list                                        */
    s32                 nbKanban;         /* poster number                                      */
}
CART_COURSE_MODEL;

/********************************/
/*  Data                        */
/********************************/
/****** DataDll *********************************************************************************/
#define CartCourseModels            ( (CART_COURSE_MODEL*)GetDataDllProcAddr("CartCourseModels") )

EXTERN_END

#endif/*H_SA2B_CART_COURSE*/
