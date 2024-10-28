/************************/
/*  Includes            */
/************************/
/****** Core Toolkit ****************************************************************/
#include <sa2b/core.h>          /* core                                             */
#include <sa2b/writeop.h>       /* WriteJump                                        */

/****** Ninja ***********************************************************************/
#include <sa2b/ninja/ninja.h>   /* ninja                                            */

/****** Game ************************************************************************/
#include <sa2b/sonic/shaders.h> /* setshaders                                       */

/****** Render Fix ******************************************************************/
#include <rf_core.h>            /* core                                             */
#include <rf_renderstate.h>     /* render state                                     */
#include <rf_magic.h>           /* rf_magic                                         */

/****** Self ************************************************************************/
#include <rf_draw/rfd_internal.h>               /* parent & siblings                */
#include <rf_draw/rfd_cnkmdl/rfdcnk_internal.h> /* self                             */

/************************/
/*  Game References     */
/************************/
/****** Shadow Map ******************************************************************/
#define _gj_shadmtx_callback_       FUNC_REF(void, __cdecl, (s32), 0x01A55828)

/************************/
/*  Source              */
/************************/
/****** Static **********************************************************************/
static void
rjCnkBeginEnv(const NJS_MATRIX* pMtx)
{
    NJS_MATRIX m0 = { .m =
    {
        {  0.5f,  0.0f,  0.0f,  0.f },
        {  0.0f, -0.5f,  0.0f,  0.f },
        {  0.0f,  0.0f,  0.0f,  0.f },
    }};

    NJS_MATRIX m1 = { .m =
    {
        {  1.0f,  0.0f,  0.0f,  0.5f },
        {  0.0f,  1.0f,  0.0f,  0.5f },
        {  0.0f,  0.0f,  1.0f,  1.0f },
    }};

    njMultiMatrix(    &m0, pMtx);
    njPostMultiMatrix(&m0, &m1);

    njGetMatrix44(&_env_matrix_44_, &m0);
}

/****** Extern **********************************************************************/
void
rjCnkBeginDrawModel(void)
{
    _nj_cnk_last_strip_flags_ =  0;
    _nj_cnk_strip_flags_      = -1;

    if ( (_nj_control_3d_flag_ & 0x80000) )
    {
        gjStartVertex3D(_nj_curr_matrix_, 0);
        rjCnkBeginEnv(_nj_curr_matrix_);

        if (_gj_shadmtx_callback_)
            _gj_shadmtx_callback_(1);

        _nj_control_3d_flag_ &= ~0x100000u;
    }
    else 
    {
        gjStartVertex3D(&_nj_unit_matrix_, 0);

        if ( !(_nj_control_3d_flag_ & 0x100000) )
        {
            rjCnkBeginEnv(&_nj_unit_matrix_);

            _nj_control_3d_flag_ |= 0x100000u;
        }
    }

    SetShaders(1);
}

void
rjCnkDrawModelSub(const NJS_CNK_MODEL* const model)
{
    if (ShadowCnkDraw)
    {
        if (model->vlist)
            CnkVListShadow_Ext(model->vlist, _nj_vertex_buf_, true);

        if (model->plist)
            CnkPListShadow_Ext(model->plist, _nj_vertex_buf_);
    }
    else if (_nj_control_3d_flag_ & 0x80000) // Shadow map is setup
    {
        if (model->vlist)
            rjCnkVListSM(model->vlist, _nj_vertex_buf_);

        if (model->plist)
            rjCnkPList(model->plist, _nj_vertex_buf_);
    }
    else
    {
        if (model->vlist)
            rjCnkVList(model->vlist, _nj_vertex_buf_);

        if (model->plist)
            rjCnkPList(model->plist, _nj_vertex_buf_);
    }
}

Sint32
_rjCnkDrawModel(const NJS_CNK_MODEL* model)
{
    if ( !(_nj_control_3d_flag_ & NJD_CONTROL_3D_MODEL_CLIP) || model->r <= 0.0f || !njCnkModelClip(model) ) 
    {
        rjCnkDrawModelSub(model);
        return 0;
    }

    return -1;
}

Sint32
rjCnkDrawModel(const NJS_CNK_MODEL* model)
{
    if ( !(_nj_control_3d_flag_ & NJD_CONTROL_3D_MODEL_CLIP) || model->r <= 0.0f || !njCnkModelClip(model) ) 
    {
        rjCnkBeginDrawModel();
        rjCnkDrawModelSub(model);
    }

    return 0;
}

void
rjCnkDrawObject(const NJS_CNK_OBJECT* object)
{
    rjCnkBeginDrawModel();
    njCnkTransformObject(object, _rjCnkDrawModel);
}

void
rjCnkDrawMotion(const NJS_CNK_OBJECT* object, const NJS_MOTION* motion, Float frame)
{
    rjCnkBeginDrawModel();
    njDrawMotion(object, motion, frame, _rjCnkDrawModel);
}

void
rjCnkDrawMotionLink(const NJS_CNK_OBJECT* object, const NJS_MOTION_LINK* motion_link, Float rate)
{
    rjCnkBeginDrawModel();
    njDrawMotionLink(object, motion_link, rate, _rjCnkDrawModel);
}

void
rjCnkDrawShapeMotion(const NJS_CNK_OBJECT* object, const NJS_MOTION* motion, const NJS_MOTION* shape, Float frame)
{
    rjCnkBeginDrawModel();
    njDrawShapeMotion(object, motion, shape, frame, frame, _rjCnkDrawModel);
}

void
rjCnkDrawShapeMotionLink(const NJS_CNK_OBJECT* object, const NJS_MOTION_LINK* motion_link, const NJS_MOTION_LINK* shape_link, Float rate)
{
    rjCnkBeginDrawModel();
    njDrawShapeLink(object, motion_link, shape_link, rate, _rjCnkDrawModel);
}

void
rjCnkDrawShapeMotionBE(const NJS_CNK_OBJECT* object, const NJS_MOTION* motion, const NJS_MOTION* shape, Float frame)
{
    rjCnkBeginDrawModel();
    njDrawShapeMotionBE(object, motion, shape, frame, frame, _rjCnkDrawModel);
}

void
rjCnkDrawShapeMotionLinkBE(const NJS_CNK_OBJECT* object, const NJS_MOTION_LINK* motion_link, const NJS_MOTION_LINK* shape_link, Float rate)
{
    rjCnkBeginDrawModel();
    njDrawShapeLinkBE(object, motion_link, shape_link, rate, _rjCnkDrawModel);
}
