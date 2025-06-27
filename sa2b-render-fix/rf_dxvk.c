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
    return;
}

#define StrSizeOf(str_)     (str_), sizeof(str_)

static void
DXVK_CheckAndCreateConfig(void)
{
    return;
}

void
RF_DXVK_Init(void)
{
    DXVK_CheckAndInstall();
    DXVK_CheckAndCreateConfig();
}
