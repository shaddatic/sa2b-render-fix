#include <sa2b/core.h>

#include <sa2b/ninja/ninja.h>

/** API (this is stupid) **/
#include <../api/renderfix_api.h>

/** Render Fix **/
#include <rf_core.h>
#include <rf_ctrl.h>

/** Constants **/
#define CTRL_API_VER    (0)

/** Exports **/
EXTERN
const RFAPI_CONTROL rfapi_control =
{
    .version = CTRL_API_VER,

    .CheapShadowChaoWorldDisable = RFCTRL_CheapShadowChaoWorldDisable,
};
