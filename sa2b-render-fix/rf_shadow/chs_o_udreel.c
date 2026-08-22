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
/*  Game Refs                   */
/********************************/
/****** Item Func *******************************************************************************/
#define ObjectGolemUdreel       FUNC_PTR(void, __cdecl, (task*), 0x004BB5D0)

/********************************/
/*  Source                      */
/********************************/
/****** Displayers ******************************************************************************/
void
ObjectUdreelShadow(task* tp)
{
    taskwk* const twp = tp->twp;

    OnControl3D(NJD_CONTROL_3D_SHADOW|NJD_CONTROL_3D_TRANS_MODIFIER);

    njPushMatrixEx();
    {
        njTranslate(NULL, twp->pos.x, twp->pos.y + tp->mwp[1].work.f, twp->pos.z);
        njScale(NULL, 3.6f, 1.0f, 3.6f);

        njCnkModDrawModel( object_shadow->model );
    }
    njPopMatrixEx();

    OffControl3D(NJD_CONTROL_3D_SHADOW|NJD_CONTROL_3D_TRANS_MODIFIER);
}

void
ObjectGolemUdreelShadow(task* tp)
{
    taskwk* const twp = tp->twp;

    OnControl3D(NJD_CONTROL_3D_SHADOW|NJD_CONTROL_3D_TRANS_MODIFIER);

    njPushMatrixEx();
    {
        njTranslate(NULL, twp->pos.x, twp->pos.y + tp->mwp[1].work.f, twp->pos.z);
        njScale(NULL, 4.0f, 1.0f, 4.0f);

        njCnkModDrawModel( object_shadow->model );
    }
    njPopMatrixEx();

    OffControl3D(NJD_CONTROL_3D_SHADOW|NJD_CONTROL_3D_TRANS_MODIFIER);
}

/****** Hooks ***********************************************************************************/
static mt_hookinfo HookInfoGolemUdreel[1];
static void
ObjectGolemUdreelHook(task* tp)
{
    mtHookInfoCall(HookInfoGolemUdreel, ObjectGolemUdreel(tp));

    if (tp->disp)
        tp->disp_shad = ObjectGolemUdreelShadow;
}

/****** Init ************************************************************************************/
void
CHS_UdreelInit(void)
{
    WriteJump(0x006E6320, ObjectUdreelShadow);
    SwitchDisplayer(0x006E56A2, DISP_SHAD);

    mtHookFunc(HookInfoGolemUdreel, ObjectGolemUdreel, ObjectGolemUdreelHook);
    KillCall(0x004BC47C);
    KillCall(0x004BC6FE);
}
