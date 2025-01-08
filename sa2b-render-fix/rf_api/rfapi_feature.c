#include <sa2b/core.h>

#include <sa2b/ninja/ninja.h>

/** API (this is stupid) **/
#include <../api/renderfix_api.h>

/** Render Fix **/
#include <rf_core.h>
#include <rf_feature.h>

/** Constants **/
#define FEAT_API_VER    (1)

static bool
RFF_Depricated_True(void)
{
    return true;
}

static bool
RFF_Depricated_False(void)
{
    return false;
}

/** Exports **/
EXTERN
const RFAPI_FEATURE rfapi_feature =
{
    .version = FEAT_API_VER,

    .BackColorDraw   = RFF_BackColorDraw,
    .SpotLightFix    = RFF_SpotLightFix,
    .EnvMapFlip      = RFF_Depricated_True,
    .BackFaceCulling = RFF_BackFaceCulling,
    .FixModelTint    = RFF_Depricated_True,

    .ShadowOpacityGlobal = RFF_ShadowOpacityGlobal,
    .ShadowOpacityChao   = RFF_ShadowOpacityChao,

    .CheapShadow                 = RFF_CheapShadow,
    .CheapShadowPerformance      = RFF_CheapShadowPerformance,
    .CheapShadowUltraPerformance = RFF_Depricated_False,
    .CheapShadowPlayer           = RFF_CheapShadowPlayer,

    /** Ver 1 **/
    .NewEventRenderer  = RFF_NewEventRenderer,

    .Chaos0TexAnim          = RFF_Chaos0TexAnim,
    .DreamcastPlayerModel   = RFF_DreamcastPlayerModel,
    .DisablePlayerShadowing = RFF_DisablePlayerShadowing,
};
