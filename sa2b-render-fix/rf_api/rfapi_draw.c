#include <samt/core.h>

#include <samt/ninja/ninja.h>

/** API (this is stupid) **/
#include <../api/renderfix_api.h>

/** Render Fix **/
#include <rf_core.h>
#include <rf_draw.h>

/** Constants **/
#define DRAW_API_VER    (3)

/** Exports **/
EXTERN
const RFAPI_DRAW rfapi_draw =
{
    .version = DRAW_API_VER,

    .CnkNullDrawModel       = njCnkNullDrawModel,
    .CnkNullDrawObject      = njCnkNullDrawObject,

    .CnkAnimateMotion       = njCnkAnimateMotion,
    .CnkAnimateMotionLink   = njCnkAnimateMotionLink,

    .CnkModDrawModel        = njCnkModDrawModel,
    .CnkModDrawObject       = njCnkModDrawObject,

    .CnkModDrawMotion       = njCnkModDrawMotion,
    .CnkModDrawMotionLink   = njCnkModDrawMotionLink,

    .DrawBasicShadow        = DrawBasicShadow,
    .AL_ShadowDraw          = AL_ShadowDraw,

    /** Ver 1 **/
    .DrawTextureEx          = rjDrawTextureEx,
    .DrawPolygon2D          = rjDrawPolygon2D,

    /** Ver 2 **/
    .DrawLineStrip3D        = rjDrawLineStrip3D,
    .DrawLineList3D         = rjDrawLineList3D,
    .DrawLineStrip2D        = rjDrawLineStrip2D,
    .DrawLineList2D         = rjDrawLineList2D,

    /** Ver 3 **/
    .CnkModDrawShapeMotion       = rjCnkModDrawShapeMotion,
    .CnkModDrawShapeMotionLink   = rjCnkModDrawShapeMotionLink,
    .CnkModDrawShapeMotionBE     = rjCnkModDrawShapeMotionBE,
    .CnkModDrawShapeMotionLinkBE = rjCnkModDrawShapeMotionLinkBE,

    .CnkDrawModel           = rjCnkDrawModel,
    .CnkDrawObject          = rjCnkDrawObject,
    .CnkDrawMotion          = rjCnkDrawMotion,
    .CnkDrawMotionLink      = rjCnkDrawMotionLink,

    .CnkDrawShapeMotion       = rjCnkDrawShapeMotion,
    .CnkDrawShapeMotionLink   = rjCnkDrawShapeMotionLink,
    .CnkDrawShapeMotionBE     = rjCnkDrawShapeMotionBE,
    .CnkDrawShapeMotionLinkBE = rjCnkDrawShapeMotionLinkBE,

    .CnkSetUvScroll        = rjCnkSetUvScroll,
    .CnkSetEnvUvScroll     = rjCnkSetEnvUvScroll,
    .CnkSetTextureCallback = rjCnkSetTextureCallback,

    .SetCheapShadowMode = rjSetCheapShadowMode,
};
