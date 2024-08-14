#include <sa2b/core.h>
#include <sa2b/modinfo.h>
#include <sa2b/modloader.h>

/** Utility **/
#include <sa2b/util/ml_type.h>
#include <sa2b/util/dllexport.h>

/** Ninja **/
#include <sa2b/ninja/ninja.h>

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
RFAPI_CORE rfapi_core =
{
    .version = CORE_API_VER,

    .rf_version = { 1,3,2,0 },
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
    /** Enable usable APIs **/
    rfapi_core.pApiControl     = &rfapi_control;
    rfapi_core.pApiConfig      = &rfapi_config;
    rfapi_core.pApiRenderState = &rfapi_rstate;
    rfapi_core.pApiShader      = &rfapi_shader;
    rfapi_core.pApiFont        = &rfapi_font;

    ApiCallByFuncName("RF_EarlyInit");

    /** Disable Control API, as it can't be
        used past this point **/
    rfapi_core.pApiControl = nullptr;
}

void
RFAPI_End(void)
{
    /** Enable newly Init'd APIs **/
    rfapi_core.pApiFeature     = &rfapi_feature;
    rfapi_core.pApiDraw        = &rfapi_draw;

    ApiCallByFuncName("RF_Init");

    /** Disable Config API, as it can't be
        used past this point **/
    rfapi_core.pApiConfig = nullptr;
}
