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
/****** Item Funcs ******************************************************************************/
#define ObjectBlock2            FUNC_PTR(void, __cdecl, (task*), 0x004CF370)
#define ObjectBlock             FUNC_PTR(void, __cdecl, (task*), 0x004CE240)

/********************************/
/*  Source                      */
/********************************/
/****** Displayers ******************************************************************************/
void
ObjectBlock2Shadow(task* tp)
{
    taskwk* const twp = tp->twp;
    anywk*  const awp = tp->awp;

    if ((twp->ang.z & 1) == 0)
    {
        return;
    }

    OnControl3D(NJD_CONTROL_3D_SHADOW|NJD_CONTROL_3D_TRANS_MODIFIER);

    njPushMatrixEx();
    {
        njTranslateEx(&twp->pos);
        njRotateY(NULL, twp->ang.y & 0xFF00);

        const f32 scl = twp->scl.x + 1.0f;

        njScale(NULL, scl, scl, scl);

        njCnkModDrawObject(object_modmod_box);
    }
    njPopMatrixEx();

    OffControl3D(NJD_CONTROL_3D_SHADOW|NJD_CONTROL_3D_TRANS_MODIFIER);
}

void
ObjectBlockShadow(task* tp)
{
    taskwk* const twp = tp->twp;
    anywk* const awp = tp->awp;

    if ((twp->ang.z & 2) == 0)
    {
        return;
    }

    OnControl3D(NJD_CONTROL_3D_SHADOW|NJD_CONTROL_3D_TRANS_MODIFIER);

    njPushMatrixEx();
    {
        njTranslateEx(&twp->pos);
        njRotateY(NULL, twp->ang.y & 0xFF00);

        const f32 scl = twp->scl.x + 1.0f;

        njScale(NULL, scl, scl, scl);

        njCnkModDrawObject(object_modmod_box);
    }
    njPopMatrixEx();

    OffControl3D(NJD_CONTROL_3D_SHADOW|NJD_CONTROL_3D_TRANS_MODIFIER);
}

/****** Hooks ***********************************************************************************/
static mt_hookinfo HookInfoObjectBlock2[1];
static void
ObjectBlock2Hook(task* tp)
{
    mtHookInfoCall( HookInfoObjectBlock2, ObjectBlock2(tp) );

    if (tp->disp)
        tp->disp_shad = ObjectBlock2Shadow;
}


static mt_hookinfo HookInfoObjectBlock[1];
static void
ObjectBlockHook(task* tp)
{
    mtHookInfoCall( HookInfoObjectBlock, ObjectBlock(tp) );

    if (tp->disp)
        tp->disp_shad = ObjectBlockShadow;
}

/****** Init ************************************************************************************/
void
CHS_CCBlockInit(void)
{
    mtHookFunc(HookInfoObjectBlock2, ObjectBlock2, ObjectBlock2Hook);
    mtHookFunc(HookInfoObjectBlock , ObjectBlock , ObjectBlockHook);
}
