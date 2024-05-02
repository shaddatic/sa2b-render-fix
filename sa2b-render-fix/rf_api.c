#include <sa2b/core.h>
#include <sa2b/mods.h>
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
#define CORE_API_VER    (0)

EXPORT_DLL
RFAPI_CORE rfapi_core =
{
    .version = CORE_API_VER,

    .rf_version = { 1,3,0,1 },
};

typedef void(__cdecl RF_INIT)(const RFAPI_CORE*, const char*, const HelperFunctions*);

static void
ApiCallByFuncName(const char* name)
{
    const size_t nb_mod = ModGetTotalNumber();

    for (size_t i = 0; i < nb_mod; ++i)
    {
        const mod_handle* mhp = ModGetHandlePosition(i);

        RF_INIT* const init = ModGetExport(mhp, name);

        if (init)
            init(&rfapi_core, ModGetPath(mhp), ML_GetHelperFunctions());
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
