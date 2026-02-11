/*
*   SAMT for Sonic Adventure 2 (PC, 2012) - '/sonic/figure/knuckles.h'
*
*   ~~ Under Construction ~~
*
*   Description:
*     Knuckles the Echidna player, and base header for treasure hunters.
*/
#ifndef H_SA2B_FIGURE_KNUCKLES
#define H_SA2B_FIGURE_KNUCKLES

/********************************/
/*  Includes                    */
/********************************/
/****** Ninja ***********************************************************************************/
#include <samt/ninja/njcommon.h>    /* ninja common                                             */

/****** Game ************************************************************************************/
#include <samt/sonic/player.h>      /* core player                                              */
#include <samt/sonic/reform.h>      /* reform object                                            */

EXTERN_START

/********************************/
/*  Structures                  */
/********************************/
/****** Player Work *****************************************************************************/
#define GET_KNUCKLESWK(_tp)         ((knuckleswk*)tp->awp)

typedef struct knuckleswk
{
    playerwk        pw;             /* player work                                          */

    i8              walltimer;      // increments when scraping against walls when gliding
    i8              colsomething;   // changes when punching into a colision
    i8              field_35E[70];
    i16             timer;          // increments with a player flag set
    i16             jumptimer;      // increments while holding jump
    i16             someAng2;
    i16             someAng0;
    i16             someAng1;
    i16             texid;          // texture id for chaos0
    i32             wing_actnum;    // wing action number for something
    i8              field_3B4[4];
    f32             wing_frame;     // rouge wings shape frame
    Angle           sunglass_ang;   // sunglass/treasurescope angle
    NJS_POINT3      somePos;
    NJS_POINT3      rootpos;
    NJS_POINT3      setpos;
    reformwk*       rw_head;        // head reform
    reformwk*       rw_body;        // rouge's body
    reformwk*       rw_back;        // rouge's back, battle only
    NJS_TEXLIST*    tlist;          /* texlist                                              */
    NJS_TEXLIST*    tlist_efftex;   /* texlist, efftex                                      */
    playerobj*      freeobj;        /* free object list                                     */
    playermot*      freemtn;        /* free motion list                                     */
    NJS_MOTION_LINK slink;          // rouge wings shape link
    NJS_MOTION_LINK mlink;          // rouge wings motion link
}
knuckleswk;

/********************************/
/*  Variables                   */
/********************************/
/****** Player Work *****************************************************************************/
#define KnucklesWorkPointer         DATA_REF(knuckleswk*, 0x01A51C88)

/****** Matrix **********************************************************************************/
#define mtx_KnucklesBase            DATA_REF(NJS_MATRIX, 0x01A51BEC)
#define mtx_KnucklesHead            DATA_REF(NJS_MATRIX, 0x01A51CBC)
#define mtx_KnucklesBody            DATA_REF(NJS_MATRIX, 0x01A51B3C)
#define mtx_KnucklesHandL           DATA_REF(NJS_MATRIX, 0x01A51C58)
#define mtx_KnucklesHandR           DATA_REF(NJS_MATRIX, 0x01A51C8C)

/********************************/
/*  Prototypes                  */
/********************************/
/****** Motion Callback *************************************************************************/
/*
*   Description:
*     Knuckles' main motion callback function.
*
*   Parameters:
*     - cnkobj      : motion object
*/
void    KnucklesMotionCallBack( NJS_CNK_OBJECT* cnkobj );

#ifdef SAMT_INCL_FUNCPTRS

/********************************/
/*  Function Pointers           */
/********************************/
/****** Function Pointers ***********************************************************************/
#define KnucklesMotionCallBack_p            FUNC_PTR(void, __cdecl, (NJS_CNK_OBJECT*), 0x0072EAA0)

#endif/*SAMT_INCL_FUNCPTRS*/

EXTERN_END

#endif/*H_SA2B_FIGURE_KNUCKLES*/
