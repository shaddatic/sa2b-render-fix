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
/*  Game Refs                   */
/********************************/
/****** Item Func *******************************************************************************/
#define ObjectContainerBox          FUNC_PTR(void, __cdecl, (task*), 0x005C3B50)

/********************************/
/*  Source                      */
/********************************/
/****** Displayers ******************************************************************************/
void
ObjectContainerBoxShadow(task* tp)
{
    taskwk* const twp = tp->twp;

    OnControl3D(NJD_CONTROL_3D_SHADOW|NJD_CONTROL_3D_TRANS_MODIFIER);

    njPushMatrixEx();
    {
        njTranslateV( NULL, &twp->pos );
        njRotateY(    NULL, twp->ang.y );

        njCnkModDrawObject( object_md_contbox_mod );
    }
    njPopMatrixEx();

    OffControl3D(NJD_CONTROL_3D_SHADOW|NJD_CONTROL_3D_TRANS_MODIFIER);
}

/****** Hooks ***********************************************************************************/
static mt_hookinfo HookInfoObjectMDContainerBox[1];
static void
ObjectContainerBoxHook(task* tp)
{
    mtHookInfoCall( HookInfoObjectMDContainerBox, ObjectContainerBox(tp) );

    if (tp->disp)
        tp->disp_shad = ObjectContainerBoxShadow;
}

/****** Init ************************************************************************************/
void
CHS_MDContainerBoxInit(void)
{
    mtHookFunc(HookInfoObjectMDContainerBox, ObjectContainerBox, ObjectContainerBoxHook);
}
