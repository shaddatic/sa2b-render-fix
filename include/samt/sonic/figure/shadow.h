/*
*   SAMT for Sonic Adventure 2 (PC, 2012) - '/sonic/figure/shadow.h'
*
*   ~~ Under Construction ~~
*
*   Description:
*     Shadow the Hedgehog player.
*/
#ifndef H_SA2B_FIGURE_SHADOW
#define H_SA2B_FIGURE_SHADOW

/********************************/
/*  Includes                    */
/********************************/
/****** Ninja ***********************************************************************************/
#include <samt/ninja/njcommon.h>    /* ninja common                                             */

/****** Game ************************************************************************************/
#include <samt/sonic/player.h>      /* core player                                              */
#include <samt/sonic/reform.h>      /* reform object                                            */

/****** Figure **********************************************************************************/
#include <samt/sonic/figure/sonic.h> /* sonic                                                   */

EXTERN_START

/********************************/
/*  Variables                   */
/********************************/
/****** Matrix **********************************************************************************/
#define mtx_ShadowFootR             DATA_REF(NJS_MATRIX, 0x01A51894)

/********************************/
/*  Prototypes                  */
/********************************/
/****** Motion Callback *************************************************************************/
/*
*   Description:
*     Shadow's main motion callback function.
*
*   Parameters:
*     - cnkobj      : motion object
*/
void    ShadowMotionCallBack( NJS_CNK_OBJECT* cnkobj );

#ifdef SAMT_INCL_FUNCPTRS

/********************************/
/*  Function Pointers           */
/********************************/
/****** Function Pointers ***********************************************************************/
#define ShadowMotionCallBack_p              FUNC_PTR(void, __cdecl, (NJS_CNK_OBJECT*), 0x0071F5E0)

#endif/*SAMT_INCL_FUNCPTRS*/

EXTERN_END

#endif/*H_SA2B_FIGURE_SHADOW*/

