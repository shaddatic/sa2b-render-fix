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
#include <rf_api.h>                 /* call api functions                                       */

/****** DX9 Control *****************************************************************************/
#include <dx9ctrl/dx9ctrl.h>        /* directx control                                          */

/********************************/
/*  Constants                   */
/********************************/
/****** Mod Loader ******************************************************************************/
#define MLVER_HARD_MIN             ML_MINVER_MODINFO   /* absolute minimum mod loader version   */
#define MLVER_SOFT_MIN             ML_MINVER_FILEMODIX /* soft minimum mod loader version       */

/********************************/
/*  Source                      */
/********************************/
/****** Mod Init ********************************************************************************/
EXPORT_DLL
void __cdecl
Init(const c8* puPath, const ml_helpfuncs* pHelpFuncs, usize ixMod)
{
    RF_DbgExtra("Start Init");

    // samt init
    mtSystemInit(puPath, pHelpFuncs, ixMod);

    DX9_Init();

    /** Mod Loader Check **/
    {
        const i32 ml_ver = mlGetVersion();

        if ( ml_ver < MLVER_HARD_MIN )
        {
            RF_MsgError("Mod Loader Version",
                        "Render Fix requires Mod Loader versions newer than v%i, but your version is only v%i.\n\n"

                        "Update the Mod Loader to a newer version! You can do this from the Mod Manager.\n\n"

                        "Render Fix will now abort the init process.",

                        MLVER_HARD_MIN-1, ml_ver
            );

            return;
        }
        else if ( ml_ver < MLVER_SOFT_MIN )
        {
            RF_MsgWarn("Mod Loader Version",
                       "Render Fix is designed for Mod Loader versions v%i and newer, but your version is only %i.\n\n"

                       "Please update the Mod Loader to a newer version. You can do this from the Mod Manager.\n\n"

                       "Some features have been disabled.",

                       MLVER_SOFT_MIN, ml_ver
            );
        }
    }


    RFAPI_CallFuncs( RF_APIFUNC_EARLY );

    // config file init
    CNF_Init();

    /** Render Fix init **/
    RFGX_Init();
    RF_MsgInit();
    RF_RenderStateInit();
    RF_NinjaInit();
    RF_FontInit();
    RF_LightInit();
    RF_ShaderInit();
    RF_SysInit();

    RFF_Init();

    RFAPI_CallFuncs( RF_APIFUNC_INIT );
    RFAPI_CallFuncs( RF_APIFUNC_OLD_EARLY );

    /** RF Module Init **/
    RF_ModuleInit();

    /** Check mod conflicts **/
    RF_ModCheckInit();

    RFAPI_CallFuncs( RF_APIFUNC_OLD_INIT );

    // config file close
    CNF_End();

    RFAPI_CallFuncs( RF_APIFUNC_LATE );

    RF_DbgExtra("End Init");
}

/****** On Device X *****************************************************************************/
EXPORT_DLL
void __cdecl
OnRenderDeviceLost(void)
{
    RJ_OnDeviceLost();
}

EXPORT_DLL
void __cdecl
OnRenderDeviceReset(void)
{
    RJ_OnDeviceReset();
}

/****** On Scene X ******************************************************************************/
EXPORT_DLL
void __cdecl
OnRenderSceneStart(void)
{
    RF_SysVsyncSceneStart();
}

EXPORT_DLL
void __cdecl
OnRenderSceneEnd(void)
{
    RF_SysCtrlIdleFade();

    RF_SysVsyncSceneEnd();
}
