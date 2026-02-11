/*
*   SAMT for Sonic Adventure 2 (PC, 2012) - '/sonic/figure/eggman.h'
*
*   ~~ Under Construction ~~
* 
*   Description:
*     Eggman player.
*/
#ifndef H_SA2B_FIGURE_EGGMAN
#define H_SA2B_FIGURE_EGGMAN

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
#define GET_EGGMANWK(_tp)           ((eggmanwk*)(_tp)->awp)

typedef struct eggmanwk
{
    playerwk        pw;             /* player work                                              */

    i16             timer;          /* timer, unused                                            */
    NJS_TEXLIST*    tlist;          /* texlist                                                  */
    playerobj*      freeobj;        /* free object list                                         */
    playermot*      freemtn;        /* free motion list                                         */
}
eggmanwk;

/********************************/
/*  Variables                   */
/********************************/
/****** Player Work *****************************************************************************/
#define EggmanWorkPointer       DATA_REF(eggmanwk* , 0x01A51D28)

/****** Matrix **********************************************************************************/
#define mtx_EggmanBase          DATA_REF(NJS_MATRIX, 0x01A51CF8)

/********************************/
/*  Prototypes                  */
/********************************/
/****** Motion Callback *************************************************************************/
/*
*   Description:
*     Eggmans' main motion callback function.
*
*   Parameters:
*     - cnkobj      : motion object
*/
void    EggmanMotionCallBack( NJS_CNK_OBJECT* cnkobj );

#ifdef SAMT_INCL_FUNCPTRS

/********************************/
/*  Function Pointers           */
/********************************/
/****** Function Pointers ***********************************************************************/
#define EggmanMotionCallBack_p              FUNC_PTR(void, __cdecl, (NJS_CNK_OBJECT*), 0x0073EAD0)

#endif/*SAMT_INCL_FUNCPTRS*/

EXTERN_END

#endif/*H_SA2B_FIGURE_EGGMAN*/
