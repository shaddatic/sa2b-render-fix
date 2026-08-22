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
ObjectIronBall2Shadow(task* tp)
{
    taskwk* const twp = tp->twp;

    OnControl3D(NJD_CONTROL_3D_SHADOW|NJD_CONTROL_3D_TRANS_MODIFIER);

    njPushMatrixEx();
    {
        const f32 trans_x = (twp->scl.x + 1) * 20.0f;

        njTranslate(NULL, twp->pos.x, twp->pos.y + 0.1f, twp->pos.z);
        njRotateY(NULL, twp->ang.y);

        njPushMatrixEx();
        {
            njScale(NULL, 5.0f, 1.0f, 5.0f);

            njCnkModDrawModel( object_shadow->model );
        }
        njFastPopPushMatrix();
        {
            njTranslate(NULL, trans_x, 0.0f, 0.0f);
            njScale(NULL, 10.0f, 1.0f, 10.0f);

            njCnkModDrawModel( object_shadow->model );
        }
        njFastPopPushMatrix();
        {
            njTranslate(NULL, -trans_x, 0.0f, 0.0f);
            njScale(NULL, 10.0f, 1.0f, 10.0f);

            njCnkModDrawModel( object_shadow->model );
        }
        njPopMatrixEx();
    }
    njPopMatrixEx();

    OffControl3D(NJD_CONTROL_3D_SHADOW|NJD_CONTROL_3D_TRANS_MODIFIER);
}

/****** Init ************************************************************************************/
void
CHS_IronBall2Init(void)
{
    WriteNOP(0x006D3C7C, 0x006D3C82);
    SwitchDisplayer(0x006D3C82, DISP_SHAD);
    WriteJump(0x006D4340, ObjectIronBall2Shadow);
}
