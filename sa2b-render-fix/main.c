/************************/
/*  Includes            */
/************************/
/****** Core Toolkit ****************************************************************/
#include <samt/core.h>
#include <samt/init.h>
#include <samt/modloader.h>

/****** Render Fix ******************************************************************/
#include <rf_core.h>
#include <rf_config.h>
#include <rf_usermsg.h>
#include <rf_objpak.h>
#include <rf_dxvk.h>
#include <rf_api.h>
#include <rf_renderstate.h>
#include <rf_modchk.h>
#include <rf_ninja.h>
#include <rf_font.h>
#include <rf_gx.h>
#include <rf_light.h>
#include <rf_shader.h>

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
#include <rfm_player.h>

#include <rf_init.h>

/****** DX9 Control *****************************************************************/
#include <dx9ctrl/dx9ctrl.h>

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
Init(const c8* puPath, const ml_helpfuncs* pHelpFuncs, usize ixMod)
{
    // samt init
    mtSystemInit(puPath, pHelpFuncs, ixMod);

    DX9_Init();

    /** Mod Loader Check **/
    if ( mlGetVersion() < MLVER_MIN )
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
    RF_DrawInit();
    RF_FontInit();
    RF_GxInit();
    RF_LightInit();
    RF_ShaderInit();

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
    RFM_PlayerInit();

    /** Check mod conflicts **/
    RF_ModCheckInit();

    /** End **/
    RFAPI_End();
    RF_ConfigEnd();
}

EXPORT_DLL
void __cdecl
OnRenderSceneStart(void)
{
    RF_FrameSkipSceneStart();
}


EXPORT_DLL
void __cdecl
OnRenderSceneEnd(void)
{
    RF_FrameSkipSceneEnd();
}
