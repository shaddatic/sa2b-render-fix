/********************************/
/*  Includes                    */
/********************************/
/****** SAMT ************************************************************************************/
#include <samt/core.h>              /* core                                                     */
#include <samt/init.h>              /* init                                                     */
#include <samt/modloader.h>         /* mod loader                                               */

/****** Render Fix ******************************************************************************/
#include <rf_core.h>                /* core                                                     */

/****** Self ************************************************************************************/
#include <rf_module/rfm_internal.h> /* children                                                 */

/********************************/
/*  Source                      */
/********************************/
/****** Init ************************************************************************************/
void
RF_ModuleInit(void)
{
    // core
    RFM_GlobalInit();
    RFM_ShadowsInit();
    RFM_CommonInit();
    RFM_PlayerInit();

    // game modes
    RFM_EventInit();
    RFM_MenusInit();
    RFM_EmblemGetInit();

    // stages
    RFM_WhiteJungleInit();
    RFM_CityEscapeInit();
    RFM_MissionStreetInit();
    RFM_CrazyGadgetInit();
    RFM_AquaticMineInit();
    RFM_CannonsCoreInit();
    RFM_BossBogyInit();
    RFM_CartInit();
    RFM_ChaoInit();
}
