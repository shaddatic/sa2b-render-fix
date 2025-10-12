/********************************/
/*  Includes                    */
/********************************/
/****** SAMT ************************************************************************************/
#include <samt/core.h>              /* core                                                     */
#include <samt/init.h>              /* init                                                     */
#include <samt/modloader.h>         /* mod loader                                               */

/****** Render Fix ******************************************************************************/
#include <rf_core.h>                /* core                                                     */
#include <rf_init.h>                /* module inits                                             */
#include <rf_usermsg.h>             /* fatal error                                              */

/****** DX9 Control *****************************************************************************/
#include <dx9ctrl/dx9ctrl.h>        /* directx control                                          */

/********************************/
/*  Constants                   */
/********************************/
/****** Mod Loader ******************************************************************************/
#define MLVER_MIN   (9)             /* minimum mod loader version                               */

/********************************/
/*  Source                      */
/********************************/
/****** Mod Init ********************************************************************************/
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
    RF_UserMessageInit();
    RF_RenderStateInit();
    RF_NinjaInit();
    RF_FontInit();
    RF_GxInit();
    RF_LightInit();
    RF_ShaderInit();

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

/****** On Scene X ******************************************************************************/
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
    RF_SysCtrlIdleFade();

    RF_FrameSkipSceneEnd();
}
