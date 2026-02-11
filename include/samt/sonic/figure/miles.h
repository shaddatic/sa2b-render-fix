/*
*   SAMT for Sonic Adventure 2 (PC, 2012) - '/sonic/figure/miles.h'
*
*   ~~ Under Construction ~~
*
*   Description:
*     Miles 'Tails' Prower player.
*/
#ifndef H_SA2B_FIGURE_MILES
#define H_SA2B_FIGURE_MILES

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
#define GET_MILESWK(_tp)    ((mileswk*)tp->awp)

typedef struct mileswk
{
    playerwk        pw;             /* player work                                          */

    i8              field_38A[16];
    Angle           TailsAngX;
    Angle           TailsAngZ;
    Angle3          SomeAng;
    i8              field_3AC[40];
    reformwk*       rw_rtail;
    reformwk*       rw_ltail;
    NJS_TEXLIST*    tlist;          /* texlist                                                  */
    playerobj*      freeobj;        /* free object list                                         */
    playermot*      freemtn;        /* free motion list                                         */
    shadowwk        shadow_tails;
}
mileswk;

/********************************/
/*  Variables                   */
/********************************/
/****** Player Work *****************************************************************************/
#define MilesWorkPointer            DATA_REF(mileswk*, 0x01A521EC)

/****** Matrix **********************************************************************************/
#define mtx_MilesBase               DATA_REF(NJS_MATRIX, 0x01A521BC)
#define mtx_MilesTails              DATA_REF(NJS_MATRIX, 0x01A5215C)
#define mtx_MilesShaderTails        DATA_REF(NJS_MATRIX, 0x01A5218C)

/********************************/
/*  Prototypes                  */
/********************************/
/****** Motion Callback *************************************************************************/
/*
*   Description:
*     Miles' main motion callback function.
*
*   Parameters:
*     - cnkobj      : motion object
*/
void    MilesMotionCallBack( NJS_CNK_OBJECT* cnkobj );
/*
*   Description:
*     Miles' shadow motion callback function.
*
*   Parameters:
*     - cnkobj      : motion object
*/
void    MilesShadowMotionCallBack( NJS_CNK_OBJECT* cnkobj );

#ifdef SAMT_INCL_FUNCPTRS

/********************************/
/*  Function Pointers           */
/********************************/
/****** Function Pointers ***********************************************************************/
#define MilesMotionCallBack_p               FUNC_PTR(void, __cdecl, (NJS_CNK_OBJECT*), 0x00750320)
#define MilesShadowMotionCallBack_p         FUNC_PTR(void, __cdecl, (NJS_CNK_OBJECT*), 0x0074FEF0)

#endif/*SAMT_INCL_FUNCPTRS*/

EXTERN_END

#endif/*H_SA2B_FIGURE_MILES*/
