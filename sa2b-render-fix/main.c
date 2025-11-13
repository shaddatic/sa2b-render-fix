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
#define MLVER_MIN   (9)             /* minimum mod loader version                               */

/********************************/
/*  Source                      */
/********************************/
/****** Mod Init ********************************************************************************/
EXPORT_DLL
void __cdecl
Init(const c8* puPath, const ml_helpfuncs* pHelpFuncs, usize ixMod)
{
    RF_DbgExtraInfo("Start Init");

    // samt init
    mtSystemInit(puPath, pHelpFuncs, ixMod);

    DX9_Init();

    /** Mod Loader Check **/
    if ( mlGetVersion() < MLVER_MIN )
    {
        RF_MsgError("Mod Loader Version",
            "Render Fix can't operate safely on the currently installed version of the SA2 Mod Loader.\n"
            "Please update the Mod Loader to a newer version!\n\n"
            "Render Fix will now abort the init process."
        );

        return;
    }

    // config file init
    CNF_Init();

    /** Render Fix init **/
    RF_MsgInit();
    RF_RenderStateInit();
    RF_NinjaInit();
    RF_FontInit();
    RFGX_Init();
    RF_LightInit();
    RF_ShaderInit();
    RF_SysInit();

    RFF_Init();
    RFAPI_Init();

    /** RF Module Init **/
    RF_ModuleInit();

    /** Check mod conflicts **/
    RF_ModCheckInit();

    /** End **/
    RFAPI_End();

    // config file close
    CNF_End();

    RF_DbgExtraInfo("End Init");
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
