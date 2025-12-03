/********************************/
/*  Includes                    */
/********************************/
/****** Core Toolkit ****************************************************************************/
#include <samt/core.h>              /* core                                                     */

/****** Ninja ***********************************************************************************/
#include <samt/ninja/ninja.h>       /* ninja                                                    */

/****** Render Fix ******************************************************************************/
#include <rf_core.h>                /* core                                                     */
#include <rf_ninja.h>               /* rf ninja                                                 */

/****** Self ************************************************************************************/
#include <rf_njcnk.h>               /* self                                                     */

/************************/
/*  Source              */
/************************/
/****** Direct **********************************************************************************/
void
njCnkDirectDrawObject(NJS_CNK_OBJECT* object)
{
    rjCnkTransformObject(object, njCnkDirectDrawModel);
}

/****** Easy ************************************************************************************/
void
njCnkEasyDrawObject(NJS_CNK_OBJECT* object)
{
    rjCnkTransformObject(object, njCnkEasyDrawModel);
}

void
njCnkEasyDrawMotion(NJS_CNK_OBJECT* object, NJS_MOTION* motion, Float frame)
{
    rjCnkTransformMotion(object, motion, frame, njCnkEasyDrawModel);
}

void
njCnkEasyDrawMotionLink(NJS_CNK_OBJECT* object, NJS_MOTION_LINK* motion_link, Float frame)
{
    rjCnkTransformMotionLink(object, motion_link, frame, njCnkEasyDrawModel);
}

void
njCnkEasyDrawShapeMotion(NJS_CNK_OBJECT* object, NJS_MOTION* motion, NJS_MOTION* shape, Float frame)
{
    rjCnkTransformShapeMotion(object, motion, shape, frame, frame, njCnkEasyDrawModel);
}

void
njCnkEasyDrawShapeMotionBE(NJS_CNK_OBJECT* object, NJS_MOTION* motion, NJS_MOTION* shape, Float frame)
{
    rjCnkTransformShapeMotionBE(object, motion, shape, frame, frame, njCnkEasyDrawModel);
}

/****** Easy Multi ******************************************************************************/
void
njCnkEasyMultiDrawObject(NJS_CNK_OBJECT* object)
{
    rjCnkTransformObject(object, njCnkEasyMultiDrawModel);
}

void
njCnkEasyMultiDrawMotion(NJS_CNK_OBJECT* object, NJS_MOTION* motion, Float frame)
{
    rjCnkTransformMotion(object, motion, frame, njCnkEasyMultiDrawModel);
}

void
njCnkEasyMultiDrawMotionLink(NJS_CNK_OBJECT* object, NJS_MOTION_LINK* motion_link, Float frame)
{
    rjCnkTransformMotionLink(object, motion_link, frame, njCnkEasyMultiDrawModel);
}

void
njCnkEasyMultiDrawShapeMotion(NJS_CNK_OBJECT* object, NJS_MOTION* motion, NJS_MOTION* shape, Float frame)
{
    rjCnkTransformShapeMotion(object, motion, shape, frame, frame, njCnkEasyMultiDrawModel);
}

void
njCnkEasyMultiDrawShapeMotionBE(NJS_CNK_OBJECT* object, NJS_MOTION* motion, NJS_MOTION* shape, Float frame)
{
    rjCnkTransformShapeMotionBE(object, motion, shape, frame, frame, njCnkEasyMultiDrawModel);
}

/****** Simple **********************************************************************************/
void
njCnkSimpleDrawObject(NJS_CNK_OBJECT* object)
{
    rjCnkTransformObject(object, njCnkSimpleDrawModel);
}

void
njCnkSimpleDrawMotion(NJS_CNK_OBJECT* object, NJS_MOTION* motion, Float frame)
{
    rjCnkTransformMotion(object, motion, frame, njCnkSimpleDrawModel);
}

void
njCnkSimpleDrawMotionLink(NJS_CNK_OBJECT* object, NJS_MOTION_LINK* motion_link, Float frame)
{
    rjCnkTransformMotionLink(object, motion_link, frame, njCnkSimpleDrawModel);
}

void
njCnkSimpleDrawShapeMotion(NJS_CNK_OBJECT* object, NJS_MOTION* motion, NJS_MOTION* shape, Float frame)
{
    rjCnkTransformShapeMotion(object, motion, shape, frame, frame, njCnkSimpleDrawModel);
}

void
njCnkSimpleDrawShapeMotionBE(NJS_CNK_OBJECT* object, NJS_MOTION* motion, NJS_MOTION* shape, Float frame)
{
    rjCnkTransformShapeMotionBE(object, motion, shape, frame, frame, njCnkSimpleDrawModel);
}

/****** Simple Multi ****************************************************************************/
void
njCnkSimpleMultiDrawObject(NJS_CNK_OBJECT* object)
{
    rjCnkTransformObject(object, njCnkSimpleMultiDrawModel);
}

void
njCnkSimpleMultiDrawMotion(NJS_CNK_OBJECT* object, NJS_MOTION* motion, Float frame)
{
    rjCnkTransformMotion(object, motion, frame, njCnkSimpleMultiDrawModel);
}

void
njCnkSimpleMultiDrawMotionLink(NJS_CNK_OBJECT* object, NJS_MOTION_LINK* motion_link, Float frame)
{
    rjCnkTransformMotionLink(object, motion_link, frame, njCnkSimpleMultiDrawModel);
}

void
njCnkSimpleMultiDrawShapeMotion(NJS_CNK_OBJECT* object, NJS_MOTION* motion, NJS_MOTION* shape, Float frame)
{
    rjCnkTransformShapeMotion(object, motion, shape, frame, frame, njCnkSimpleMultiDrawModel);
}

void
njCnkSimpleMultiDrawShapeMotionBE(NJS_CNK_OBJECT* object, NJS_MOTION* motion, NJS_MOTION* shape, Float frame)
{
    rjCnkTransformShapeMotionBE(object, motion, shape, frame, frame, njCnkSimpleMultiDrawModel);
}

/****** Modifier ********************************************************************************/
void
njCnkModDrawObject(NJS_CNK_OBJECT* object)
{
    rjCnkTransformObject(object, njCnkModDrawModel);
}

void
njCnkModDrawMotion(NJS_CNK_OBJECT* object, NJS_MOTION* motion, Float frame)
{
    rjCnkTransformMotion(object, motion, frame, njCnkModDrawModel);
}
