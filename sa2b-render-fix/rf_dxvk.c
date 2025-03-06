#include <samt/core.h>
#include <samt/file.h>

/** Std **/
#include <stdio.h>

/** Render Fix **/
#include <rf_core.h>
#include <rf_config.h>
#include <rf_usermsg.h>

/** Self **/
#include <rf_dxvk.h>

#define DXVK_DLL_PATH       "./d3d9.dll"
#define DXVK_CONF_PATH      "./dxvk.conf"
#define DXVK_WEB_PATH       "https://github.com/doitsujin/dxvk/releases"

static void
DXVK_CheckAndInstall(void)
{
    if (RF_ConfigGetInt(CNF_HIDDEN_DXVK_CHK) || mtFileExists(DXVK_DLL_PATH))
        return;

    const bool yes = RF_Query("DXVK not installed", 

        "It is recommended to use DXVK for SA2 as it increases performance, increases stability, & allows for graphical enhancements.\n"
        "Would you like Render Fix to install it now?\n\n"

        "If you are running Linux, you can ignore this alert!"
    );

    if (yes)
    {
        char buf[260];

        snprintf(buf, sizeof(buf), "%s/install/dxvk.dll", mtGetModPath());

        if (!mtFileExists(buf))
        {
            RF_Alert("DXVK Not Found",
                "'dxvk.dll' couldn't be located in the 'install' folder. Aborting...");
            return;
        }

        mtFileCopy(buf, DXVK_DLL_PATH);

        RF_Alert("Restart Required",

            "DXVK v1.10.3 was successfully installed! The game must now be restarted for changes to apply.\n"
            "If you encounter any issues, ensure your graphics drivers are up to date! If you continue to encounter issues, you can uninstall DXVK by deleting the d3d9.dll file in the game's main directory.\n\n"

            "If you're running newer hardware, it's recommended to install the newest DXVK build from " DXVK_WEB_PATH " to get the best performance!\n"
            "To do so, download the latest release and place the x32 version of d3d9.dll into SA2's main directory, next to the executable."
        );
    }

    RF_ConfigSetInt(CNF_HIDDEN_DXVK_CHK, 1);
}

#define StrSizeOf(str_)     (str_), sizeof(str_)

static void
DXVK_CheckAndCreateConfig(void)
{
    /** if (!DXVK_INSTALLED || DXVK_CONF_EXISTS) **/
    if (!mtFileExists(DXVK_DLL_PATH) || mtFileExists(DXVK_CONF_PATH))
        return;

    mtFileWriteEx(DXVK_CONF_PATH, StrSizeOf("d3d9.samplerAnisotropy = 16\n"));
}

void
RF_DXVK_Init(void)
{
    DXVK_CheckAndInstall();
    DXVK_CheckAndCreateConfig();
}
