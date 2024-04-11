#include <sa2b/core.h>

#include <sa2b/ninja/ninja.h>

/** API (this is stupid) **/
#include <../api/renderfix_api.h>

/** Render Fix **/
#include <rf_core.h>
#include <rf_config.h>

/** Constants **/
#define CNFG_API_VER    (0)

/** Exports **/
EXTERN
const RFAPI_CONFIG rfapi_config =
{
    .version = CNFG_API_VER,

    .ConfigGetInt    = RF_ConfigDirectGetInt,
    .ConfigGetBool   = RF_ConfigDirectGetBool,
    .ConfigGetString = RF_ConfigDirectGetString,
};
