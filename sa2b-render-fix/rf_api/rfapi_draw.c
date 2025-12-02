/********************************/
/*  Includes                    */
/********************************/
/****** SAMT ************************************************************************************/
#include <samt/core.h>              /* core                                                     */

/****** Render Fix ******************************************************************************/
#include <rf_core.h>                /* core                                                     */
#include <rf_ninja.h>               /* draw                                                     */
#include <rf_njcnk.h>               /* ninja chunk draw                                         */

/****** Self ************************************************************************************/
#include <rf_api/rfapi_internal.h>  /* parent & siblings                                        */

/********************************/
/*  Constants                   */
/********************************/
/****** API Module Version **********************************************************************/
#define DRAW_API_VER                (4) /* draw api version                                     */

/********************************/
/*  Source                      */
/********************************/
/****** Functions *******************************************************************************/
static void
Obsolete(void)
{
    ;
}

static void
___CnkDrawObject(NJS_CNK_OBJECT* object)
{
    rjCnkTransformObject(object, rjCnkDrawModel);
}

static void
___CnkDrawMotion(NJS_CNK_OBJECT* object, NJS_MOTION* motion, Float frame)
{
    rjCnkDrawMotion(object, motion, frame, rjCnkDrawModel);
}

static void
___CnkDrawMotionLink(NJS_CNK_OBJECT* object, NJS_MOTION_LINK* motion_link, Float rate)
{
    rjCnkDrawMotionLink(object, motion_link, rate, rjCnkDrawModel);
}

static void
___CnkDrawShapeMotion(NJS_CNK_OBJECT* object, NJS_MOTION* motion, NJS_MOTION* shape, Float frame)
{
    rjCnkDrawShapeMotion(object, motion, shape, frame, frame, rjCnkDrawModel);
}

static void
___CnkDrawShapeMotionLink(NJS_CNK_OBJECT* object, NJS_MOTION_LINK* motion_link, NJS_MOTION_LINK* shape_link, Float rate)
{
    rjCnkDrawShapeMotionLink(object, motion_link, shape_link, rate, rjCnkDrawModel);
}

static void
___CnkDrawShapeMotionBE(NJS_CNK_OBJECT* object, NJS_MOTION* motion, NJS_MOTION* shape, Float frame)
{
    rjCnkDrawShapeMotionBE(object, motion, shape, frame, frame, rjCnkDrawModel);
}

static void
___CnkDrawShapeMotionLinkBE(NJS_CNK_OBJECT* object, NJS_MOTION_LINK* motion_link, NJS_MOTION_LINK* shape_link, Float rate)
{
    rjCnkDrawShapeMotionLinkBE(object, motion_link, shape_link, rate, rjCnkDrawModel);
}

/********************************/
/*  Export Data                 */
/********************************/
/****** Draw API ********************************************************************************/
EXTERN
const RFAPI_DRAW rfapi_draw =
{
    .version = DRAW_API_VER,

    .CnkNullDrawModel       = (void*) Obsolete,
    .CnkNullDrawObject      = (void*) Obsolete,

    .CnkAnimateMotion       = (void*) Obsolete,
    .CnkAnimateMotionLink   = (void*) Obsolete,

    .CnkModDrawModel        = njCnkModDrawModel,
    .CnkModDrawObject       = njCnkModDrawObject,

    .CnkModDrawMotion       = (void*) Obsolete,
    .CnkModDrawMotionLink   = (void*) Obsolete,

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
    .CnkModDrawShapeMotion       = (void*) Obsolete,
    .CnkModDrawShapeMotionLink   = (void*) Obsolete,
    .CnkModDrawShapeMotionBE     = (void*) Obsolete,
    .CnkModDrawShapeMotionLinkBE = (void*) Obsolete,

    .CnkDrawModel           = rjCnkDrawModel,
    .CnkDrawObject          = ___CnkDrawObject,
    .CnkDrawMotion          = ___CnkDrawMotion,
    .CnkDrawMotionLink      = ___CnkDrawMotionLink,

    .CnkDrawShapeMotion       = ___CnkDrawShapeMotion,
    .CnkDrawShapeMotionLink   = ___CnkDrawShapeMotionLink,
    .CnkDrawShapeMotionBE     = ___CnkDrawShapeMotionBE,
    .CnkDrawShapeMotionLinkBE = ___CnkDrawShapeMotionLinkBE,

    .CnkSetUvScroll        = rjCnkSetUvScroll,
    .CnkSetEnvUvScroll     = rjCnkSetEnvUvScroll,
    .CnkSetTextureCallback = rjCnkSetTextureCallback,

    .SetCheapShadowMode = rjSetCheapShadowMode,

    /** Ver 4 **/
    .SetCheapShadowColor = rjSetCheapShadowColor,
};
