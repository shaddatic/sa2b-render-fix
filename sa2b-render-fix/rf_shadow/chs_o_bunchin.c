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

/****** Self ************************************************************************************/
#include <rf_shadow/chs_internal.h> /* parent & siblings                                        */

/********************************/
/*  Source                      */
/********************************/
/****** Displayers ******************************************************************************/
void
ObjectBunchinShadow(task* tp)
{
    taskwk*   const twp = tp->twp;
    motionwk* const mwp = tp->mwp;

    OnControl3D(NJD_CONTROL_3D_SHADOW|NJD_CONTROL_3D_TRANS_MODIFIER);

    njPushMatrixEx();
    {
        f32 scl_y = mwp->work.f * 0.5f;

        if (scl_y > 100.0f)
        {
            scl_y = 100.f;
        }

        f32 scl_y_add;

        if (twp->ang.z & 0x1000)
        {
            njTranslate( NULL, twp->pos.x, twp->pos.y + scl_y - 102.5f, twp->pos.z );
            njRotateY(   NULL, twp->ang.y );

            scl_y_add = 103.0f;
        }
        else
        {
            njTranslate( NULL, twp->pos.x, twp->pos.y + scl_y - 2.5f, twp->pos.z );
            njRotateY(   NULL, twp->ang.y );

            scl_y_add = 3.0f;
        }

        scl_y += scl_y_add;

        const f32 scl_x = (twp->scl.x + 1.0f) * 1.3333334f;
        const f32 scl_z = (twp->scl.z + 1.0f) * 1.3333334f;

        njScale( NULL, scl_x , scl_y * 0.06666667f, scl_z );

        njCnkModDrawModel(object_modmod_box->model);
    }
    njPopMatrixEx();

    OffControl3D(NJD_CONTROL_3D_SHADOW|NJD_CONTROL_3D_TRANS_MODIFIER);
}

/****** Init ************************************************************************************/
void
CHS_BunchinInit(void)
{
    WriteJump(0x006DCBE0, ObjectBunchinShadow);

    KillCall(0x006DBC9C); // Kill SetStencilInfo
}
