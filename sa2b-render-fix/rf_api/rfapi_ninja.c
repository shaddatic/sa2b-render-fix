/********************************/
/*  Includes                    */
/********************************/
/****** SAMT ************************************************************************************/
#include <samt/core.h>              /* core                                                     */

/****** Render Fix ******************************************************************************/
#include <rf_core.h>                /* core                                                     */

/****** Self ************************************************************************************/
#include <rf_api/rfapi_internal.h>  /* parent & siblings                                        */
#include <rf_ninja.h>               /* rf ninja                                                 */

/********************************/
/*  Export Data                 */
/********************************/
/****** Font API ********************************************************************************/
EXTERN
const RFAPI_NINJA rfapi_ninja =
{
    .version = RFAPI_NINJA_VER,

    .SetCurrentContext = njSetCurrentContext,

    .GetSystemAttr = njGetSystemAttr,
    .SetSystemAttr = njSetSystemAttr,

    .SetBackColor   = rjSetBackColor,
    .SetBackTexture = rjSetBackTexture,

    .SpecularMode   = njSpecularMode,

    .PolygonCullingMode = njPolygonCullingMode,
    .ZBufferMode        = njZBufferMode,
    .ZWriteMode         = njZWriteMode,

    .TextureShadingMode     = njTextureShadingMode,
    .SuperSampleMode        = njSuperSampleMode,
    .MipmapAdjust           = njMipmapAdjust,
    .IgnoreTextureAlphaMode = njIgnoreTextureAlphaMode,
    .TextureFilterMode      = njTextureFilterMode,
    .TextureClampMode       = njTextureClampMode,
    .TextureFlipMode        = njTextureFlipMode,
    .ColorClampMode         = njColorClampMode,
    .ColorBlendingMode      = njColorBlendingMode,

    .ModifierMode   = njModifierMode,

    .SetCheapShadowMode = rjSetCheapShadowMode,
};
