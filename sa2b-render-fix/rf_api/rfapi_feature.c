/********************************/
/*  Includes                    */
/********************************/
/****** SAMT ************************************************************************************/
#include <samt/core.h>              /* core                                                     */

/****** Render Fix ******************************************************************************/
#include <rf_core.h>                /* core                                                     */

/****** Self ************************************************************************************/
#include <rf_api/rfapi_internal.h>  /* parent & siblings                                        */
#include <rf_feature.h>             /* rf feature                                               */

/********************************/
/*  Source                      */
/********************************/
/****** Static **********************************************************************************/
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

/********************************/
/*  Extern Variables            */
/********************************/
/****** SAMT ************************************************************************************/
EXTERN
const RFAPI_FEATURE rfapi_feature =
{
    .version = RFAPI_FEATURE_VER,

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
