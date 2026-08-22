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
#define ObjectSearchBox     FUNC_PTR(void, __cdecl, (task*), 0x006E7F60)

/********************************/
/*  Source                      */
/********************************/
/****** Displayers ******************************************************************************/
void
ObjectSearchBoxShadow(task* tp)
{
    OnControl3D(NJD_CONTROL_3D_SHADOW|NJD_CONTROL_3D_TRANS_MODIFIER);

    njPushMatrixEx();
    {
        const f32* sbwp = (const f32*)tp->mwp;

        njTranslate(NULL, sbwp[3], sbwp[4] + 0.2f, sbwp[5]);
        njScale(NULL, 3.0f, 1.0f, 3.0f);

        njCnkModDrawModel( object_shadow->model );
    }
    njPopMatrixEx();

    OffControl3D(NJD_CONTROL_3D_SHADOW|NJD_CONTROL_3D_TRANS_MODIFIER);
}

/****** Hooks ***********************************************************************************/
static mt_hookinfo HookInfoObjectSearchBox[1];
static void
ObjectSearchBoxHook(task* tp)
{
    mtHookInfoSwitch(HookInfoObjectSearchBox, OFF);
    ObjectSearchBox(tp);
    mtHookInfoSwitch(HookInfoObjectSearchBox, ON);

    if (tp->disp)
        tp->disp_shad = ObjectSearchBoxShadow;
}

/****** Init ************************************************************************************/
void
CHS_SearchBoxInit(void)
{
    WriteRetn(0x006E7E90);
    mtHookFunc(HookInfoObjectSearchBox, ObjectSearchBox, ObjectSearchBoxHook);
}
