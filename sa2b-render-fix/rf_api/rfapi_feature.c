#include <sa2b/core.h>

#include <sa2b/ninja/ninja.h>

/** API (this is stupid) **/
#include <../api/renderfix_api.h>

/** Render Fix **/
#include <rf_core.h>
#include <rf_feature.h>

/** Constants **/
#define FEAT_API_VER    (0)

/** Exports **/
EXTERN
const RFAPI_FEATURE rfapi_feature =
{
    .version = FEAT_API_VER,

    .BackColorDraw   = RFF_BackColorDraw,
    .SpotLightFix    = RFF_SpotLightFix,
    .EnvMapFlip      = RFF_EnvMapFlip,
    .BackFaceCulling = RFF_BackFaceCulling,
    .FixModelTint    = RFF_FixModelTint,

    .ShadowOpacityGlobal = RFF_ShadowOpacityGlobal,
    .ShadowOpacityChao   = RFF_ShadowOpacityChao,

    .CheapShadow                 = RFF_CheapShadow,
    .CheapShadowPerformance      = RFF_CheapShadowPerformance,
    .CheapShadowUltraPerformance = RFF_CheapShadowUltraPerformance,
    .CheapShadowPlayer           = RFF_CheapShadowPlayer,
};
