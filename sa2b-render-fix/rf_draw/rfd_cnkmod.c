/************************/
/*  Includes            */
/************************/
/****** Core Toolkit ****************************************************************/
#include <samt/core.h>          /* core                                             */
#include <samt/writeop.h>       /* WriteJump                                        */

/****** Ninja ***********************************************************************/
#include <samt/ninja/ninja.h>   /* ninja                                            */

/****** Render Fix ******************************************************************/
#include <rf_core.h>            /* core                                             */
#include <rf_renderstate.h>     /* render state                                     */
#include <rf_mod.h>

/****** Self ************************************************************************/
#include <rf_draw/rfd_internal.h>               /* parent & siblings                */
#include <rf_draw/rfd_cnkmod/rfdmod_internal.h> /* self                             */

/************************/
/*  Includes            */
/************************/
/****** Extern **********************************************************************/
Sint32
njCnkModDrawModel(const NJS_CNK_MODEL* model)
{
    if (_nj_control_3d_flag_ & NJD_CONTROL_3D_MODEL_CLIP)
        if (model->r > 0 && njCnkModelClip(model))
            return -1;

    if (model->vlist)
        rjCnkModVList(model->vlist, _nj_vertex_buf_);

    if (model->plist)
        rjCnkModPList(model->plist, _nj_vertex_buf_);

    return 0;
}

void
njCnkModDrawObject(const NJS_CNK_OBJECT* const object)
{
    njCnkTransformObject(object, njCnkModDrawModel);
}

void
njCnkModDrawMotion(const NJS_CNK_OBJECT* const object, const NJS_MOTION* const motion, const Float frame)
{
    njDrawMotion(object, motion, frame, njCnkModDrawModel);
}

void
njCnkModDrawMotionLink(const NJS_CNK_OBJECT* const object, const NJS_MOTION_LINK* const motion_link, const Float frame)
{
    njDrawMotionLink(object, motion_link, frame, njCnkModDrawModel);
}

void
rjCnkModDrawShapeMotion(const NJS_CNK_OBJECT* object, const NJS_MOTION* motion, const NJS_MOTION* shape, Float frame)
{
    njDrawShapeMotion(object, motion, shape, frame, frame, njCnkModDrawModel);
}

void
rjCnkModDrawShapeMotionLink(const NJS_CNK_OBJECT* object, const NJS_MOTION_LINK* motion_link, const NJS_MOTION_LINK* shape_link, Float rate)
{
    njDrawShapeLink(object, motion_link, shape_link, rate, njCnkModDrawModel);
}

void
rjCnkModDrawShapeMotionBE(const NJS_CNK_OBJECT* object, const NJS_MOTION* motion, const NJS_MOTION* shape, Float frame)
{
    njDrawShapeMotionBE(object, motion, shape, frame, frame, njCnkModDrawModel);
}

void
rjCnkModDrawShapeMotionLinkBE(const NJS_CNK_OBJECT* object, const NJS_MOTION_LINK* motion_link, const NJS_MOTION_LINK* shape_link, Float rate)
{
    njDrawShapeLinkBE(object, motion_link, shape_link, rate, njCnkModDrawModel);
}
