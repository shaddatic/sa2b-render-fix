#include <samt/core.h>

#include <samt/ninja/ninja.h>

/** API (this is stupid) **/
#include <../api/renderfix_api.h>

/** Render Fix **/
#include <rf_core.h>
#include <rf_renderstate.h>

/** Constants **/
#define STATE_API_VER    (3)

/** Exports **/
EXTERN
const RFAPI_RENDERSTATE rfapi_rstate =
{
    .version = STATE_API_VER,

    .SetCullMode      = RFRS_SetCullMode,
    .SetTransMode     = RFRS_SetTransMode,
    .SetAlphaTestFunc = RFRS_SetAlphaTestFunc,
    .SetAlphaTestRef  = RFRS_SetAlphaTestRef,

    /** Ver 1 **/
    .SetModifierMode  = RFRS_SetModifierMode,
    .SetCnkDrawMode   = RFRS_SetCnkDrawMode,

    /** Ver 2 **/
    .SetCnkFuncMode = RFRS_SetCnkFuncMode,
    .SetCnkPassMode = RFRS_SetCnkPassMode,

    .GetCullMode      = RFRS_GetCullMode,
    .GetTransMode     = RFRS_GetTransMode,
    .GetAlphaTestFunc = RFRS_GetAlphaTestFunc,
    .GetAlphaTestRef  = RFRS_GetAlphaTestRef,
    .GetModifierMode  = RFRS_GetModifierMode,
    .GetCnkDrawMode   = RFRS_GetCnkDrawMode,
    .GetCnkFuncMode   = RFRS_GetCnkFuncMode,
    .GetCnkPassMode   = RFRS_GetCnkPassMode,

    /** Ver 3 **/
    .SetSocTexHackMode = RFRS_SetSocTexHackMode,
    .GetSocTexHackMode = RFRS_GetSocTexHackMode,
};
