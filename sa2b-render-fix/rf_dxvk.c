#include <sa2b/core.h>
#include <sa2b/file.h>

/** Std **/
#include <stdlib.h>

/** Render Fix **/
#include <rf_core.h>
#include <rf_config.h>
#include <rf_usermsg.h>

/** Self **/
#include <rf_dxvk.h>

#define DXVK_DLL_PATH       "./d3d9.dll"
#define DXVK_CONF_PATH      "./dxvk.conf"
#define DXVK_WEB_PATH       "https://github.com/doitsujin/dxvk"
#define DXVK_LEGACY_WEB     "https://github.com/doitsujin/dxvk/releases/tag/v1.10.3"

static void
DXVK_CheckAndInstall(void)
{
    if (RF_ConfigGetInt(CNF_HIDDEN_DXVK_CHK) || uFileExists(DXVK_DLL_PATH))
        return;

    const bool yes = RF_Query("DXVK not installed", 

        "It is recommended to use DXVK for SA2, as it increases performance, increases stability, & allows for graphical enhancements.\n"
        "If you encounter any issues, ensure your graphics drivers are up to date.\n"
        "If you are running legacy hardware, DXVK version 1.10.3 has relaxed driver requirements and can be downloaded from" DXVK_LEGACY_WEB ".\n"
        "Would you like to install it now?\n\n"

        "If you are running Linux, you can ignore this alert!"
    );

    if (yes)
    {
        char buf[260];

        snprintf(buf, sizeof(buf), "%s/install/dxvk.dll", GetModPath());

        if (!uFileExists(buf))
        {
            RF_Alert("DXVK Not Found",
                "'dxvk.dll' couldn't be located in the 'install' folder. Aborting...");
            return;
        }

        uFileCopy(buf, DXVK_DLL_PATH);

        RF_Alert("Restart Required",
            "DXVK was successfully installed! The game must now be restarted for changes to apply.");
    }

    RF_ConfigSetInt(CNF_SECT_HIDDEN, "dxvk_chk", 1);
}

static void
DXVK_CheckAndCreateConfig(void)
{
    if (uFileExists(DXVK_CONF_PATH))
        return;

    FILE* const f = uFileOpen(DXVK_CONF_PATH, FMODE_WB);

    fprintf(f, "d3d9.samplerAnisotropy = 16\n");

    fclose(f);
}

void
RF_DXVK_Init(void)
{
    DXVK_CheckAndInstall();
    DXVK_CheckAndCreateConfig();
}
