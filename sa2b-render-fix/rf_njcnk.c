/************************/
/*  Includes            */
/************************/
/****** Core Toolkit ****************************************************************/
#include <sa2b/core.h>          /* core                                             */

/****** Render Fix ******************************************************************/
#include <rf_core.h>            /* ninja                                            */
#include <rf_draw.h>            /* rf draw                                          */
#include <rf_renderstate.h>     /* render state                                     */

/************************/
/*  Source              */
/************************/
/****** Easy ************************************************************************/
void
njCnkEasyDrawModel(const NJS_CNK_MODEL* model)
{
    RFRS_SetCnkFuncMode(RFRS_CNKFUNCMD_EASY);

    rjCnkDrawModel(model);

    RFRS_SetCnkFuncMode(RFRS_CNKFUNCMD_END);
}

void
njCnkEasyDrawObject(const NJS_CNK_OBJECT* object)
{
    RFRS_SetCnkFuncMode(RFRS_CNKFUNCMD_EASY);

    rjCnkDrawObject(object);

    RFRS_SetCnkFuncMode(RFRS_CNKFUNCMD_END);
}

void
njCnkEasyMultiDrawObject(const NJS_CNK_OBJECT* object)
{
    RFRS_SetCnkFuncMode(RFRS_CNKFUNCMD_EASYMULTI);

    rjCnkDrawObject(object);

    RFRS_SetCnkFuncMode(RFRS_CNKFUNCMD_END);
}

void
njCnkEasyDrawMotion(const NJS_CNK_OBJECT* object, const NJS_MOTION* motion, Float frame)
{
    RFRS_SetCnkFuncMode(RFRS_CNKFUNCMD_EASY);

    rjCnkDrawMotion(object, motion, frame);

    RFRS_SetCnkFuncMode(RFRS_CNKFUNCMD_END);
}

void
njCnkEasyMultiDrawMotion(const NJS_CNK_OBJECT* object, const NJS_MOTION* motion, Float frame)
{
    RFRS_SetCnkFuncMode(RFRS_CNKFUNCMD_EASYMULTI);

    rjCnkDrawMotion(object, motion, frame);

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
njCnkEasyMultiDrawShapeMotion(const NJS_CNK_OBJECT* object, const NJS_MOTION* motion, const NJS_MOTION* shape, Float frame)
{
    RFRS_SetCnkFuncMode(RFRS_CNKFUNCMD_EASYMULTI);

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

void
njCnkEasyMultiDrawShapeMotionBE(const NJS_CNK_OBJECT* object, const NJS_MOTION* motion, const NJS_MOTION* shape, Float frame)
{
    RFRS_SetCnkFuncMode(RFRS_CNKFUNCMD_EASYMULTI);

    rjCnkDrawShapeMotionBE(object, motion, shape, frame);

    RFRS_SetCnkFuncMode(RFRS_CNKFUNCMD_END);
}

/****** Simple **********************************************************************/
void
njCnkSimpleDrawModel(const NJS_CNK_MODEL* model)
{
    RFRS_SetCnkFuncMode(RFRS_CNKFUNCMD_SIMPLE);

    rjCnkDrawModel(model);

    RFRS_SetCnkFuncMode(RFRS_CNKFUNCMD_END);
}

void
njCnkSimpleDrawObject(const NJS_CNK_OBJECT* object)
{
    RFRS_SetCnkFuncMode(RFRS_CNKFUNCMD_SIMPLE);

    rjCnkDrawObject(object);

    RFRS_SetCnkFuncMode(RFRS_CNKFUNCMD_END);
}

void
njCnkSimpleMultiDrawObject(const NJS_CNK_OBJECT* object)
{
    RFRS_SetCnkFuncMode(RFRS_CNKFUNCMD_SIMPLEMULTI);

    rjCnkDrawObject(object);

    RFRS_SetCnkFuncMode(RFRS_CNKFUNCMD_END);
}

void
njCnkSimpleDrawMotion(const NJS_CNK_OBJECT* object, const NJS_MOTION* motion, Float frame)
{
    RFRS_SetCnkFuncMode(RFRS_CNKFUNCMD_SIMPLE);

    rjCnkDrawMotion(object, motion, frame);

    RFRS_SetCnkFuncMode(RFRS_CNKFUNCMD_END);
}

void
njCnkSimpleMultiDrawMotion(const NJS_CNK_OBJECT* object, const NJS_MOTION* motion, Float frame)
{
    RFRS_SetCnkFuncMode(RFRS_CNKFUNCMD_SIMPLEMULTI);

    rjCnkDrawMotion(object, motion, frame);

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
njCnkSimpleMultiDrawShapeMotion(const NJS_CNK_OBJECT* object, const NJS_MOTION* motion, const NJS_MOTION* shape, Float frame)
{
    RFRS_SetCnkFuncMode(RFRS_CNKFUNCMD_SIMPLEMULTI);

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

void
njCnkSimpleMultiDrawShapeMotionBE(const NJS_CNK_OBJECT* object, const NJS_MOTION* motion, const NJS_MOTION* shape, Float frame)
{
    RFRS_SetCnkFuncMode(RFRS_CNKFUNCMD_SIMPLEMULTI);

    rjCnkDrawShapeMotionBE(object, motion, shape, frame);

    RFRS_SetCnkFuncMode(RFRS_CNKFUNCMD_END);
}