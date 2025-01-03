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
/*  Export Data         */
/************************/
/****** UV Offset *******************************************************************/
Float _rj_cnk_uv_scroll_u_;
Float _rj_cnk_uv_scroll_v_;

/****** Env Scroll ******************************************************************/
Float _rj_cnk_env_scroll_u_;
Float _rj_cnk_env_scroll_v_;

/****** Texture Callback ************************************************************/
Sint16 (__cdecl* _rj_cnk_texture_callback_)(Sint16 texid);

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

Sint32
rjCnkDrawModelSub(const NJS_CNK_MODEL* const model)
{
    /** The VList functions have the unique ability to halt drawing by returning
        '-1', used when it encounters a vertex format it can't parse. For example,
        'MultiDraw' can't parse non-normal vertex formats and so halts. **/

    if ( ShadowCnkDraw )
    {
        /** Draw entire model in 1 pass without texture or lighting for shadow
            stencil texture drawing. I haven't implimented this, so it's still
            using the original code ('ext' means EXTernal to Render Fix) **/

        if ( model->vlist )
            if ( CnkVListShadow_Ext(model->vlist, _nj_vertex_buf_, true) == -1 )
                return -1;

        if ( model->plist )
            CnkPListShadow_Ext(model->plist, _nj_vertex_buf_);
    }
    else if ( _nj_control_3d_flag_ & 0x80000 ) // shadow map is setup
    {
        /** Draw model with shadow texture.
            The shader uses the current matrix, as sent by 'gjStartVertex3D', to
            position the texture correctly on the model. This is a problem, as
            Chunk usually uses a unit matrix as all transforms are done on the CPU,
            causing the shadows to become 'floaty'. We can't just move everything
            to the GPU due to model weight calculations - although in the future it
            may be possible - so the fix for now is to use a different vertex
            pipeline that doesn't transform that supports a limited number of
            vertex formats. It's basically only used on Landtables anyway, so this
            is fine. :)
            'SM' means shadow mapped. **/

        if ( model->vlist )
            if ( rjCnkVListSM(model->vlist, _nj_vertex_buf_) == -1 )
                return -1;

        if ( model->plist )
            rjCnkPList(model->plist, _nj_vertex_buf_);
    }
    else
    {
        /** Draw model normally. **/

        if ( model->vlist )
            if ( rjCnkVList(model->vlist, _nj_vertex_buf_) == -1 )
                return -1;

        if ( model->plist )
            rjCnkPList(model->plist, _nj_vertex_buf_);
    }

    /** Drawing completed successfully **/
    return 0;
}

Sint32
_rjCnkDrawModel(const NJS_CNK_MODEL* model)
{
    /** This is an internal variant of 'DrawModel' that doesn't call
        'CnkBeginDrawModel'. It's used for object drawing and motions, where it's
        pointless and a lot slower to constantly call 'BeginDrawModel' for every
        model in the object tree **/

    /** Model clip **/
    if (_nj_control_3d_flag_ & NJD_CONTROL_3D_MODEL_CLIP)
        if (model->r > 0.f && njCnkModelClip(model))
            return -1;

    return rjCnkDrawModelSub(model);
}

Sint32
rjCnkDrawModel(const NJS_CNK_MODEL* model)
{
    /** Model clip **/
    if (_nj_control_3d_flag_ & NJD_CONTROL_3D_MODEL_CLIP)
        if (model->r > 0.f && njCnkModelClip(model))
            return -1;

    rjCnkBeginDrawModel();
    return rjCnkDrawModelSub(model);
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
    /** Big endian shape motion draw **/

    rjCnkBeginDrawModel();
    njDrawShapeMotionBE(object, motion, shape, frame, frame, _rjCnkDrawModel);
}

void
rjCnkDrawShapeMotionLinkBE(const NJS_CNK_OBJECT* object, const NJS_MOTION_LINK* motion_link, const NJS_MOTION_LINK* shape_link, Float rate)
{
    /** Big endian shape link draw **/
    
    rjCnkBeginDrawModel();
    njDrawShapeLinkBE(object, motion_link, shape_link, rate, _rjCnkDrawModel);
}

/****** Cnk Modify ******************************************************************/
void
rjCnkSetUvScroll(Float u, Float v)
{
    _rj_cnk_uv_scroll_u_ = u;
    _rj_cnk_uv_scroll_v_ = v;
}

void
rjCnkSetEnvUvScroll(Float u, Float v)
{
    _rj_cnk_env_scroll_u_ = u;
    _rj_cnk_env_scroll_v_ = v;
}

void
rjCnkSetTextureCallback(Sint16(__cdecl* callback)(Sint16 texid))
{
    _rj_cnk_texture_callback_ = callback;
}
