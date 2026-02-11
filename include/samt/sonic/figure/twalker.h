/*
*   SAMT for Sonic Adventure 2 (PC, 2012) - '/sonic/figure/twalker.h'
*
*   ~~ Under Construction ~~
* 
*   Description:
*     Tails Walker player.
*/
#ifndef H_SA2B_FIGURE_TWALKER
#define H_SA2B_FIGURE_TWALKER

/********************************/
/*  Includes                    */
/********************************/
/****** Ninja ***********************************************************************************/
#include <samt/ninja/njcommon.h>    /* ninja common                                             */

/****** Game ************************************************************************************/
#include <samt/sonic/player.h>      /* core player                                              */
#include <samt/sonic/reform.h>      /* reform object                                            */

/****** Figure **********************************************************************************/
#include <samt/sonic/figure/ewalker.h> /* egg walker                                            */

EXTERN_START

/********************************/
/*  Variables                   */
/********************************/
/****** Matrix **********************************************************************************/
#define mtx_TornadoBazooka          DATA_REF(NJS_MATRIX, 0x01A52030)
#define mtx_TornadoBoosterL         DATA_REF(NJS_MATRIX, 0x01A51EDC)
#define mtx_TornadoBoosterR         DATA_REF(NJS_MATRIX, 0x01A51E4C)

/********************************/
/*  Prototypes                  */
/********************************/
/****** Motion Callback *************************************************************************/
/*
*   Description:
*     The Tails Walker's main motion callback function.
*
*   Parameters:
*     - cnkobj      : motion object
*/
void    TailsWalkerMotionCallBack( NJS_CNK_OBJECT* cnkobj );

#ifdef SAMT_INCL_FUNCPTRS

/********************************/
/*  Function Pointers           */
/********************************/
/****** Function Pointers ***********************************************************************/
#define TailsWalkerMotionCallBack_p         FUNC_PTR(void, __cdecl, (NJS_CNK_OBJECT*), 0x00747940)

#endif/*SAMT_INCL_FUNCPTRS*/

EXTERN_END

#endif/*H_SA2B_FIGURE_TWALKER*/
