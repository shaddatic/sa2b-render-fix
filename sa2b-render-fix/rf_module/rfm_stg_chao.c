/********************************/
/*  Includes                    */
/********************************/
/****** SAMT ************************************************************************************/
#include <samt/core.h>              /* core                                                     */
#include <samt/funchook.h>          /* funchook                                                 */
#include <samt/modinfo.h>           /* mod info                                                 */

/****** Ninja ***********************************************************************************/
#include <samt/ninja/ninja.h>       /* ninja                                                    */

/****** Game ************************************************************************************/
#include <samt/sonic/task.h>        /* task                                                     */
#include <samt/sonic/njctrl.h>      /* oncontrol                                                */

/****** Render Fix ******************************************************************************/
#include <rf_core.h>                /* core                                                     */
#include <rf_renderstate.h>         /* easysimpledirect                                         */
#include <rf_ninja.h>               /* rf ninja                                                 */

/****** Self ************************************************************************************/
#include <rf_module/rfm_internal.h> /* parent & siblings                                        */

/********************************/
/*  Game Defs                   */
/********************************/
/****** Task ************************************************************************************/
#define OdekakeMachineDisplayer_p       FUNC_PTR(void, __cdecl, (task*), 0x0057E060)

/********************************/
/*  Source                      */
/********************************/
/****** Task ************************************************************************************/
static mt_hookinfo OdekakeMachineDisplayerHookInfo[1];

static void
OdekakeMachineDisplayerHook(task* tp)
{
    OnControl3D( NJD_CONTROL_3D_CNK_CONSTANT_ATTR );

    // double sided lighting, off
    rjCnkSetControl( RJD_CNK_CTRL_DOUBLESIDEDLIGHT, 0 );

    SaveConstantAttr();

    _nj_constant_attr_and_ = NJD_FST_MASK;
    _nj_constant_attr_or_  = NJD_FST_DB;

    mtHookInfoCall( OdekakeMachineDisplayerHookInfo, OdekakeMachineDisplayer_p(tp) );

    LoadConstantAttr();

    // double sided lighting, restore
    rjCnkSetControl( 0, RJD_CNK_CTRL_DOUBLESIDEDLIGHT );

    OffControl3D( NJD_CONTROL_3D_CNK_CONSTANT_ATTR );
}

/****** Init ************************************************************************************/
void
RFM_ChaoInit(void)
{
    const ml_modinfo* p_miecw_dll = miGetInfoByDllName("ecwp.dll");       // ecw dll
    const ml_modinfo* p_miecw_id  = miGetInfoByID("enhanced-chao-world"); // new ecw mod id

    // ecw installed && 1.4+ mod ID not found
    if ( p_miecw_dll && !p_miecw_id )
    {
        RF_DbgInfo("ECW v1.4 or below was detected! Enabling temporary Odekake Machine fix.");

        mtHookFunc( OdekakeMachineDisplayerHookInfo, OdekakeMachineDisplayer_p, OdekakeMachineDisplayerHook );
    }
}
