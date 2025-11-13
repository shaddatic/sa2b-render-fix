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
#include <rf_api.h>
#include <rf_api/rfapi_internal.h>

/** Constants **/
#define CORE_API_VER    (1)

EXPORT_DLL
const RFAPI_CORE rfapi_core =
{
    .version = CORE_API_VER,

    .modver = { 1,5,0,0 },

    .pApiControl     = &rfapi_control,
    .pApiConfig      = &rfapi_config,
    .pApiFeature     = &rfapi_feature,
    .pApiDraw        = &rfapi_draw,
    .pApiRenderState = &rfapi_rstate,
    .pApiShader      = &rfapi_shader,

    .pApiFont = &rfapi_font,
};

typedef s32(__cdecl RF_INIT)(const RFAPI_CORE*, const c8*, const HelperFunctions*, size);

void
RFAPI_CallFuncs(RF_APIFUNC apifn)
{
    /****** Static **************************************************************************/

    static const c7* const FuncNames[RF_NB_APIFUNC] =
    {
        [RF_APIFUNC_INIT]  = "RFAPI_Init",
        [RF_APIFUNC_EARLY] = "RFAPI_Early",
        [RF_APIFUNC_LATE]  = "RFAPI_Late",

        [RF_APIFUNC_OLD_INIT]  = "RF_Init",
        [RF_APIFUNC_OLD_EARLY] = "RF_EarlyInit",
    };

    /****** Start ***************************************************************************/

    const c7* pc_apifn = FuncNames[apifn];

    const size nb_mod = miGetModCount();

    for ( size i = 0; i < nb_mod; ++i )
    {
        const ml_modinfo* p_mi = miGetInfoByIndex(i);

        RF_INIT* fn_init = miGetExport(p_mi, pc_apifn);

        if ( !fn_init )
        {
            continue;
        }

        const s32 val = fn_init(&rfapi_core, p_mi->puPath, mtGetHelperFunctions(), i);

        if ( apifn < RF_APIFUNC_OLD_INIT && val != 0 )
        {
            RF_MsgWarn(
                "[API] Unexpected Return Value",

                "Return value from user-exported function was != 0 (%i). "
                "The function is either malformed or made for a later version of Render Fix!", val
            );
        }
    }
}
