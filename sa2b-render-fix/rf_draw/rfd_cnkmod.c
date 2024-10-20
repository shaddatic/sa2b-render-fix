/************************/
/*  Includes            */
/************************/
/****** Core Toolkit ****************************************************************/
#include <sa2b/core.h>          /* core                                             */
#include <sa2b/writeop.h>       /* WriteJump                                        */

/****** Ninja ***********************************************************************/
#include <sa2b/ninja/ninja.h>   /* ninja                                            */

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
int32_t
njCnkModDrawModel(const NJS_CNK_MODEL* const model)
{
    if (_nj_control_3d_flag_ & NJD_CONTROL_3D_MODEL_CLIP)
        if (model->r > 0 && njCnkModelClip(model))
            return 1;

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
njCnkModDrawMotion(const NJS_CNK_OBJECT* const object, const NJS_MOTION* const motion, const float frame)
{
    njDrawMotion(object, motion, frame, njCnkModDrawModel);
}

void
njCnkModDrawMotionLink(const NJS_CNK_OBJECT* const object, const NJS_MOTION_LINK* const motion_link, const float frame)
{
    njDrawMotionLink(object, motion_link, frame, njCnkModDrawModel);
}
