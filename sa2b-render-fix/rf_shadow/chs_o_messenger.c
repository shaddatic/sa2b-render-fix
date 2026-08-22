/********************************/
/*  Includes                    */
/********************************/
/****** SAMT ************************************************************************************/
#include <samt/core.h>              /* core                                                     */
#include <samt/writemem.h>          /* write memory                                             */
#include <samt/writeop.h>           /* write op                                                 */
#include <samt/funchook.h>          /* function hook                                            */

/****** Utl *************************************************************************************/
#include <samt/util/asm.h>          /* asm helper                                               */

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

/****** Self ************************************************************************************/
#include <rf_shadow/chs_internal.h> /* parent & siblings                                        */

/********************************/
/*  Source                      */
/********************************/
/****** Displayers ******************************************************************************/
void
ObjectMessengerShadow(task* tp)
{
    taskwk* const twp = tp->twp;

    NJS_POINT3 point;

    njCalcPoint(NULL, &twp->pos, &point);

    // if range out
    if ( -point.z < -100.f )
    {
        return;
    }

    OnControl3D(NJD_CONTROL_3D_SHADOW|NJD_CONTROL_3D_TRANS_MODIFIER);

    const f32 y_thing = njSin(tp->awp[2].work.sl[1]) * 2.3f;

    njPushMatrixEx();
    {
        njTranslate(NULL, twp->pos.x, twp->pos.y + y_thing + 0.1f, twp->pos.z);
        njScale(NULL, 3.0f, 1.0f, 3.0f);

        njCnkModDrawModel( object_shadow->model );
    }
    njPopMatrixEx();

    OffControl3D(NJD_CONTROL_3D_SHADOW|NJD_CONTROL_3D_TRANS_MODIFIER);
}

/****** Init ************************************************************************************/
void
CHS_MessengerInit(void)
{
    WriteJump(0x006C0CE0, ObjectMessengerShadow);

    KillCall(0x006C0815); // Kill SetStencilInfo
}
