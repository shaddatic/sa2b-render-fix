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
/****** Chunk Model API *************************************************************************/
EXTERN
const RFAPI_CHUNK rfapi_chunk =
{
    .version = RFAPI_CHUNK_VER,

    .CnkSetControl = rjCnkSetControl,
    .CnkGetControl = rjCnkGetControl,

    .CnkSetModelCallback  = rjCnkSetModelCallback,
    .CnkSetObjectCallback = rjCnkSetObjectCallback,
    .CnkSetMotionCallback = rjCnkSetMotionCallback,

    .CnkSetTextureCallback  = rjCnkSetTextureCallback,
    .CnkSetMaterialCallback = rjCnkSetMaterialCallback,

    .CnkSetUvScroll    = rjCnkSetUvScroll,
    .CnkSetEnvUvScroll = rjCnkSetEnvUvScroll,

    .CnkNormalDrawModel      = rjCnkNormalDrawModel,
    .CnkEasyDrawModel        = njCnkEasyDrawModel,
    .CnkSimpleDrawModel      = njCnkSimpleDrawModel,
    .CnkEasyMultiDrawModel   = njCnkEasyMultiDrawModel,
    .CnkSimpleMultiDrawModel = njCnkSimpleMultiDrawModel,
    .CnkDirectDrawModel      = njCnkDirectDrawModel,
    .CnkModDrawModel         = njCnkModDrawModel,

    .CnkTransformObject          = rjCnkTransformObject,
    .CnkTransformMotion          = rjCnkTransformMotion,
    .CnkTransformMotionLink      = rjCnkTransformMotionLink,
    .CnkTransformShapeMotion     = rjCnkTransformShapeMotion,
    .CnkTransformShapeMotionLink = rjCnkTransformShapeMotionLink,
};
