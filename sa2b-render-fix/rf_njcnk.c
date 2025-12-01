/************************/
/*  Includes            */
/************************/
/****** Core Toolkit ****************************************************************/
#include <samt/core.h>          /* core                                             */

/****** Render Fix ******************************************************************/
#include <rf_core.h>            /* ninja                                            */
#include <rf_ninja.h>           /* rf draw                                          */
#include <rf_renderstate.h>     /* render state                                     */

/************************/
/*  Source              */
/************************/
/****** Direct **********************************************************************/
void
njCnkDirectDrawObject(const NJS_CNK_OBJECT* object)
{
    rjCnkTransformObject(object, njCnkDirectDrawModel);
}

/****** Easy ************************************************************************/
void
njCnkEasyDrawObject(const NJS_CNK_OBJECT* object)
{
    rjCnkTransformObject(object, njCnkEasyDrawModel);
}

void
njCnkEasyDrawMotion(const NJS_CNK_OBJECT* object, const NJS_MOTION* motion, Float frame)
{
    RFRS_SetCnkFuncMode(RFRS_CNKFUNCMD_EASY);

    rjCnkDrawMotion(object, motion, frame);

    RFRS_SetCnkFuncMode(RFRS_CNKFUNCMD_END);
}

void
njCnkEasyDrawMotionLink(const NJS_CNK_OBJECT* object, const NJS_MOTION_LINK* motion_link, Float frame)
{
    RFRS_SetCnkFuncMode(RFRS_CNKFUNCMD_EASY);

    rjCnkDrawMotionLink(object, motion_link, frame);

    RFRS_SetCnkFuncMode(RFRS_CNKFUNCMD_END);
}

void
njCnkEasyDrawShapeMotion(const NJS_CNK_OBJECT* object, const NJS_MOTION* motion, const NJS_MOTION* shape, Float frame)
{
    RFRS_SetCnkFuncMode(RFRS_CNKFUNCMD_EASY);

    rjCnkDrawShapeMotion(object, motion, shape, frame);

    RFRS_SetCnkFuncMode(RFRS_CNKFUNCMD_END);
}
void
njCnkEasyDrawShapeMotionBE(const NJS_CNK_OBJECT* object, const NJS_MOTION* motion, const NJS_MOTION* shape, Float frame)
{
    RFRS_SetCnkFuncMode(RFRS_CNKFUNCMD_EASY);

    rjCnkDrawShapeMotionBE(object, motion, shape, frame);

    RFRS_SetCnkFuncMode(RFRS_CNKFUNCMD_END);
}

/****** Easy Multi ******************************************************************/
void
njCnkEasyMultiDrawObject(const NJS_CNK_OBJECT* object)
{
    rjCnkTransformObject(object, njCnkEasyMultiDrawModel);
}

void
njCnkEasyMultiDrawMotion(const NJS_CNK_OBJECT* object, const NJS_MOTION* motion, Float frame)
{
    RFRS_SetCnkFuncMode(RFRS_CNKFUNCMD_EASYMULTI);

    rjCnkDrawMotion(object, motion, frame);

    RFRS_SetCnkFuncMode(RFRS_CNKFUNCMD_END);
}

void
njCnkEasyMultiDrawMotionLink(const NJS_CNK_OBJECT* object, const NJS_MOTION_LINK* motion_link, Float frame)
{
    RFRS_SetCnkFuncMode(RFRS_CNKFUNCMD_EASYMULTI);

    rjCnkDrawMotionLink(object, motion_link, frame);

    RFRS_SetCnkFuncMode(RFRS_CNKFUNCMD_END);
}

void
njCnkEasyMultiDrawShapeMotion(const NJS_CNK_OBJECT* object, const NJS_MOTION* motion, const NJS_MOTION* shape, Float frame)
{
    RFRS_SetCnkFuncMode(RFRS_CNKFUNCMD_EASYMULTI);

    rjCnkDrawShapeMotion(object, motion, shape, frame);

    RFRS_SetCnkFuncMode(RFRS_CNKFUNCMD_END);
}

void
njCnkEasyMultiDrawShapeMotionBE(const NJS_CNK_OBJECT* object, const NJS_MOTION* motion, const NJS_MOTION* shape, Float frame)
{
    RFRS_SetCnkFuncMode(RFRS_CNKFUNCMD_EASYMULTI);

    rjCnkDrawShapeMotionBE(object, motion, shape, frame);

    RFRS_SetCnkFuncMode(RFRS_CNKFUNCMD_END);
}

/****** Simple **********************************************************************/
void
njCnkSimpleDrawObject(const NJS_CNK_OBJECT* object)
{
    rjCnkTransformObject(object, njCnkSimpleDrawModel);
}

void
njCnkSimpleDrawMotion(const NJS_CNK_OBJECT* object, const NJS_MOTION* motion, Float frame)
{
    RFRS_SetCnkFuncMode(RFRS_CNKFUNCMD_SIMPLE);

    rjCnkDrawMotion(object, motion, frame);

    RFRS_SetCnkFuncMode(RFRS_CNKFUNCMD_END);
}

void
njCnkSimpleDrawMotionLink(const NJS_CNK_OBJECT* object, const NJS_MOTION_LINK* motion_link, Float frame)
{
    RFRS_SetCnkFuncMode(RFRS_CNKFUNCMD_SIMPLE);

    rjCnkDrawMotionLink(object, motion_link, frame);

    RFRS_SetCnkFuncMode(RFRS_CNKFUNCMD_END);
}

void
njCnkSimpleDrawShapeMotion(const NJS_CNK_OBJECT* object, const NJS_MOTION* motion, const NJS_MOTION* shape, Float frame)
{
    RFRS_SetCnkFuncMode(RFRS_CNKFUNCMD_SIMPLE);

    rjCnkDrawShapeMotion(object, motion, shape, frame);

    RFRS_SetCnkFuncMode(RFRS_CNKFUNCMD_END);
}

void
njCnkSimpleDrawShapeMotionBE(const NJS_CNK_OBJECT* object, const NJS_MOTION* motion, const NJS_MOTION* shape, Float frame)
{
    RFRS_SetCnkFuncMode(RFRS_CNKFUNCMD_SIMPLE);

    rjCnkDrawShapeMotionBE(object, motion, shape, frame);

    RFRS_SetCnkFuncMode(RFRS_CNKFUNCMD_END);
}

/****** Simple Multi ****************************************************************/
void
njCnkSimpleMultiDrawObject(const NJS_CNK_OBJECT* object)
{
    rjCnkTransformObject(object, njCnkSimpleMultiDrawModel);
}

void
njCnkSimpleMultiDrawMotion(const NJS_CNK_OBJECT* object, const NJS_MOTION* motion, Float frame)
{
    RFRS_SetCnkFuncMode(RFRS_CNKFUNCMD_SIMPLEMULTI);

    rjCnkDrawMotion(object, motion, frame);

    RFRS_SetCnkFuncMode(RFRS_CNKFUNCMD_END);
}

void
njCnkSimpleMultiDrawMotionLink(const NJS_CNK_OBJECT* object, const NJS_MOTION_LINK* motion_link, Float frame)
{
    RFRS_SetCnkFuncMode(RFRS_CNKFUNCMD_SIMPLEMULTI);

    rjCnkDrawMotionLink(object, motion_link, frame);

    RFRS_SetCnkFuncMode(RFRS_CNKFUNCMD_END);
}

void
njCnkSimpleMultiDrawShapeMotion(const NJS_CNK_OBJECT* object, const NJS_MOTION* motion, const NJS_MOTION* shape, Float frame)
{
    RFRS_SetCnkFuncMode(RFRS_CNKFUNCMD_SIMPLEMULTI);

    rjCnkDrawShapeMotion(object, motion, shape, frame);

    RFRS_SetCnkFuncMode(RFRS_CNKFUNCMD_END);
}

void
njCnkSimpleMultiDrawShapeMotionBE(const NJS_CNK_OBJECT* object, const NJS_MOTION* motion, const NJS_MOTION* shape, Float frame)
{
    RFRS_SetCnkFuncMode(RFRS_CNKFUNCMD_SIMPLEMULTI);

    rjCnkDrawShapeMotionBE(object, motion, shape, frame);

    RFRS_SetCnkFuncMode(RFRS_CNKFUNCMD_END);
}
