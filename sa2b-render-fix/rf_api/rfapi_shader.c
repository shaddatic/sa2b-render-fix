#include <samt/core.h>

#include <samt/ninja/ninja.h>

/** API (this is stupid) **/
#include <../api/renderfix_api.h>

/** Render Fix **/
#include <rf_core.h>
#include <rf_shader.h>

/** Constants **/
#define SHDR_API_VER    (0)

/** Exports **/
EXTERN
const RFAPI_SHADER rfapi_shader =
{
    .version = SHDR_API_VER,

    .LoadVtxShader = RF_DirectLoadVtxShader,
    .LoadPxlShader = RF_DirectLoadPxlShader,

    .ReplaceVtxShader = RF_ReplaceVtxShader,
    .ReplacePxlShader = RF_ReplacePxlShader,
};
