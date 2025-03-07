#include <samt/core.h>
#include <samt/modinfo.h>
#include <samt/modloader.h>

/** Utility **/
#include <samt/util/ml_type.h>
#include <samt/util/dllexport.h>

/** Ninja **/
#include <samt/ninja/ninja.h>

/** API **/
#include <../api/renderfix_api.h>

/** Render Fix **/
#include <rf_core.h>
#include <rf_config.h>
#include <rf_draw.h>
#include <rf_renderstate.h>
#include <rf_shader.h>
#include <rf_feature.h>
#include <rf_ctrl.h>

/** Internal **/
#include <rf_api/rfapi_internal.h>

/** Constants **/
#define CORE_API_VER    (1)

EXPORT_DLL
const RFAPI_CORE rfapi_core =
{
    .version = CORE_API_VER,

    .modver = { 1,4,0,2 },

    .pApiControl     = &rfapi_control,
    .pApiConfig      = &rfapi_config,
    .pApiFeature     = &rfapi_feature,
    .pApiDraw        = &rfapi_draw,
    .pApiRenderState = &rfapi_rstate,
    .pApiShader      = &rfapi_shader,

    .pApiFont = &rfapi_font,
};

typedef void(__cdecl RF_INIT)(const RFAPI_CORE*, const char*, const HelperFunctions*);

static void
ApiCallByFuncName(const char* name)
{
    const size_t nb_mod = MI_GetTotalNumber();

    for (size_t i = 0; i < nb_mod; ++i)
    {
        const mod_info* p_mi = MI_GetInfoByPosition(i);

        RF_INIT* const init = MI_GetExport(p_mi, name);

        if (init)
            init(&rfapi_core, p_mi->cPath, ML_GetHelperFunctions());
    }
}

void
RFAPI_Init(void)
{
    ApiCallByFuncName("RF_EarlyInit");
}

void
RFAPI_End(void)
{
    ApiCallByFuncName("RF_Init");
}
