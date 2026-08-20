/********************************/
/*  Includes                    */
/********************************/
/****** SAMT ************************************************************************************/
#include <samt/core.h>              /* core                                                     */
#include <samt/writemem.h>          /* write memory                                             */
#include <samt/writeop.h>           /* write op                                                 */
#include <samt/funchook.h>          /* function hook                                            */

/****** Ninja ***********************************************************************************/
#include <samt/ninja/ninja.h>       /* ninja                                                    */

/****** Game ************************************************************************************/
#include <samt/sonic/task.h>        /* task                                                     */
#include <samt/sonic/njctrl.h>      /* ninja control funcs                                      */

/****** Render Fix ******************************************************************************/
#include <rf_core.h>                /* core                                                     */
#include <rf_ninja.h>               /* render fix ninja                                         */
#include <rf_njcnk.h>               /* ninja chunk draw                                         */
#include <rf_util.h>                /* switch displayer                                         */

/****** RF Util *********************************************************************************/
#include <rfu_draw.h>               /* animate motion                                           */

/****** Self ************************************************************************************/
#include <rf_shadow/chs_internal.h> /* parent & siblings                                        */

/********************************/
/*  Source                      */
/********************************/
/****** Displayers ******************************************************************************/
void
ObjectModModShadow(task* tp)
{
    taskwk* const twp = tp->twp;

    njPushMatrixEx();
    {
        njTranslateV( NULL, &twp->pos );
        njRotateX(    NULL, twp->ang.x );
        njRotateY(    NULL, twp->ang.y );
        njScale(      NULL, twp->scl.x + 1.0f, twp->scl.y + 1.0f, twp->scl.z + 1.0f );

        i32 ix = twp->wtimer;

        if ( ix == MODMOD_MODEL_HEX_DEBUG || ix == MODMOD_MODEL_BOX_DEBUG )
        {
            ix++;
        }

        njCnkModDrawModel( ModModModels[ix] );
    }
    njPopMatrixEx();
}

/****** Init ************************************************************************************/
void
CHS_ModModInit(void)
{
    SwitchDisplayer(0x005F55AA, DISP_SHAD);
    WriteJump(0x006C7B20, ObjectModModShadow);
}
