/*
*   SAMT for Sonic Adventure 2 (PC, 2012) - '/sonic/figure/rouge.h'
*
*   ~~ Under Construction ~~
*
*   Description:
*     Rouge the Bat player.
*/
#ifndef H_SA2B_FIGURE_ROUGE
#define H_SA2B_FIGURE_ROUGE

/********************************/
/*  Includes                    */
/********************************/
/****** Ninja ***********************************************************************************/
#include <samt/ninja/njcommon.h>    /* ninja common                                             */

/****** Game ************************************************************************************/
#include <samt/sonic/player.h>      /* core player                                              */
#include <samt/sonic/reform.h>      /* reform object                                            */

/****** Figure **********************************************************************************/
#include <samt/sonic/figure/knuckles.h> /* knuckles                                             */

EXTERN_START

/********************************/
/*  Variables                   */
/********************************/
/****** Matrix **********************************************************************************/
#define mtx_RougeBootL              DATA_REF(NJS_MATRIX, 0x01A51BBC)
#define mtx_RougeBootR              DATA_REF(NJS_MATRIX, 0x01A51C1C)

/********************************/
/*  Prototypes                  */
/********************************/
/****** Motion Callback *************************************************************************/
/*
*   Description:
*     Rouge's main motion callback function.
*
*   Parameters:
*     - cnkobj      : motion object
*/
void    RougeMotionCallBack( NJS_CNK_OBJECT* cnkobj );

#ifdef SAMT_INCL_FUNCPTRS

/********************************/
/*  Function Pointers           */
/********************************/
/****** Function Pointers ***********************************************************************/
#define RougeMotionCallBack_p               FUNC_PTR(void, __cdecl, (NJS_CNK_OBJECT*), 0x007304D0)

#endif/*SAMT_INCL_FUNCPTRS*/

EXTERN_END

#endif/*H_SA2B_FIGURE_ROUGE*/
