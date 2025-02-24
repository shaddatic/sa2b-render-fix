#include <samt/core.h>

#include <samt/ninja/ninja.h>

/** API (this is stupid) **/
#include <../api/renderfix_api.h>

/** Render Fix **/
#include <rf_core.h>
#include <rf_ctrl.h>

/** Constants **/
#define CTRL_API_VER    (1)

/** Exports **/
EXTERN
const RFAPI_CONTROL rfapi_control =
{
    .version = CTRL_API_VER,

    .SetModBufferSize            = RFCTRL_SetModBufferSize,
    .CheapShadowChaoWorldDisable = RFCTRL_CheapShadowChaoWorldDisable,

    /** Ver 1 **/
    .EventApplyModelDiffuse      = RFCTRL_EventApplyModelDiffuse,
};
