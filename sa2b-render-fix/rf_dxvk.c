#include <sa2b/core.h>
#include <sa2b/file.h>

#include <stdlib.h>

#include <rf_usermsg.h>

#define DXVK_DLL_PATH       "./d3d9.dll"
#define DXVK_CONF_PATH      "./dxvk.conf"
#define DXVK_WEB_PATH       "https://github.com/doitsujin/dxvk/releases"

void
RF_DXVKCheckInstall()
{
    if (uFileExists(DXVK_DLL_PATH))
        return;

    bool yes = RF_Query("DXVK not installed", 

        "It is recommended to use DXVK for SA2, as it increases performance, increases stability, & allows for graphical enhancements.\n"
        "Head to '" DXVK_WEB_PATH "' to download the latest DXVK version (file: dxvk-#.#.tar.gz).\n"
        "Simply open the archive & copy the x32 version of 'd3d9.dll' next to 'sonic2app.exe' to install it.\n"
        "If you are running Linux, you can ignore this alert!\n"
        "Would you like to open the download page now?"
    );

    if (yes)
        system("start " DXVK_WEB_PATH);
}

void
RF_DXVKCreateConfigFile()
{
    if (uFileExists(DXVK_CONF_PATH))
        return;

    FILE* const f = uFileOpen(DXVK_CONF_PATH, FMODE_WB);

    fprintf(f, "d3d9.samplerAnisotropy = 16\n");

    fclose(f);
}
