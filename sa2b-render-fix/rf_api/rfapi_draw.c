#include <sa2b/core.h>

#include <sa2b/ninja/ninja.h>

/** API (this is stupid) **/
#include <../api/renderfix_api.h>

/** Render Fix **/
#include <rf_core.h>
#include <rf_draw.h>

/** Constants **/
#define DRAW_API_VER    (2)

/** Exports **/
EXTERN
const RFAPI_DRAW rfapi_draw =
{
    .version = DRAW_API_VER,

    .CnkNullDrawModel     = njCnkNullDrawModel,
    .CnkNullDrawObject    = njCnkNullDrawObject,

    .CnkAnimateMotion     = njCnkAnimateMotion,
    .CnkAnimateMotionLink = njCnkAnimateMotionLink,

    .CnkModDrawModel      = njCnkModDrawModel,
    .CnkModDrawObject     = njCnkModDrawObject,

    .CnkModDrawMotion     = njCnkModDrawMotion,
    .CnkModDrawMotionLink = njCnkModDrawMotionLink,

    .DrawBasicShadow      = DrawBasicShadow,
    .AL_ShadowDraw        = AL_ShadowDraw,

    /** Ver 1 **/
    .DrawTextureEx        = rjDrawTextureEx,
    .DrawPolygon2D        = rjDrawPolygon2D,

    /** Ver 2 **/
    .DrawLineStrip3D      = rjDrawLineStrip3D,
    .DrawLineList3D       = rjDrawLineList3D,
    .DrawLineStrip2D      = rjDrawLineStrip2D,
    .DrawLineList2D       = rjDrawLineList2D,
};
