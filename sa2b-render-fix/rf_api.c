#include <samt/core.h>
#include <samt/modinfo.h>
#include <samt/modloader.h>

/** Utility **/
#include <samt/util/dllexport.h>

/** Ninja **/
#include <samt/ninja/ninja.h>

/** Render Fix **/
#include <rf_core.h>
#include <rf_ninja.h>
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

    .modver = { 1,4,1,0 },

    .pApiControl     = &rfapi_control,
    .pApiConfig      = &rfapi_config,
    .pApiFeature     = &rfapi_feature,
    .pApiDraw        = &rfapi_draw,
    .pApiRenderState = &rfapi_rstate,
    .pApiShader      = &rfapi_shader,

    .pApiFont = &rfapi_font,
};

typedef void(__cdecl RF_INIT)(const RFAPI_CORE*, const c8*, const HelperFunctions*);

static void
ApiCallByFuncName(const char* name)
{
    const size_t nb_mod = miGetModCount();

    for (size_t i = 0; i < nb_mod; ++i)
    {
        const ml_modinfo* p_mi = miGetInfoByIndex(i);

        RF_INIT* const init = miGetExport(p_mi, name);

        if (init)
            init( &rfapi_core, p_mi->puPath, mtGetHelperFunctions() );
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
