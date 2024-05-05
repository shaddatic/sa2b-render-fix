/************************/
/*  Includes            */
/************************/
/****** Core Toolkit ****************************************************************/
#include <sa2b/core.h>
#include <sa2b/init.h>

/****** Render Fix ******************************************************************/
#include <rf_core.h>
#include <rf_config.h>
#include <rf_usermsg.h>
#include <rf_objpak.h>
#include <rf_dxvk.h>
#include <rf_api.h>
#include <rf_renderstate.h>
#include <rf_modchk.h>

/****** Render Fix Modules **********************************************************/
#include <rfm_global.h>
#include <rfm_shadows.h>
#include <rfm_common.h>
#include <rfm_wjungle.h>
#include <rfm_cescape.h>
#include <rfm_mstreet.h>
#include <rfm_cgadget.h>
#include <rfm_amine.h>
#include <rfm_ccore.h>
#include <rfm_menus.h>
#include <rfm_eget.h>
#include <rfm_b_bigbogy.h>
#include <rfm_event.h>
#include <rfm_cart.h>

/************************/
/*  Constants           */
/************************/
/** Minimum mod loader version **/
#define MLVER_MIN   (9)

/************************/
/*  DLL Exports         */
/************************/
EXPORT_DLL
void __cdecl
Init(const char* path, const HelperFunctions* pHelperFunctions)
{
    /** SAModToolkit init **/
    SAMT_Init(path, pHelperFunctions);
    DX9_Init();

    /** Mod Loader Check **/
    if (ML_GetVersion() < MLVER_MIN)
    {
        RF_FatalError("Mod Loader Version",
            "Render Fix can't operate safely on the currently installed version of the SA2 Mod Loader.\n"
            "Please update the Mod Loader to a newer version!\n\n"
            "Render Fix will now abort the init process."
        );

        return;
    }

    /** Render Fix init **/
    RF_ConfigInit();
    RF_ObjPakInit();
    RF_UserMessageInit();
    RF_RenderStateInit();

    /** DXVK init **/
    RF_DXVK_Init();

    /** API **/
    RFAPI_Init();

    /** RF Module Init **/
    RFM_GlobalInit();
    RFM_ShadowsInit();
    RFM_CommonInit();
    RFM_EmblemGetInit();
    RFM_MenusInit();
    RFM_WhiteJungleInit();
    RFM_CityEscapeInit();
    RFM_MissionStreetInit();
    RFM_CrazyGadgetInit();
    RFM_AquaticMineInit();
    RFM_CannonsCoreInit();
    RFM_BossBogyInit();
    RFM_CartInit();
    RFM_EventInit();

    /** Check mod conflicts **/
    RF_ModCheckInit();

    /** End **/
    RFAPI_End();
    RF_ObjPakWriteChangesToFile();
    RF_ConfigEnd();
}

EXPORT_DLL
ModInfo SA2ModInfo = { ML_VERSION };
