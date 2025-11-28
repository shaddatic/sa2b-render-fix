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
#include <rf_magic.h>           /* rf_magic                                         */
#include <rf_light.h>           /* chunk light                                      */

/****** Self ************************************************************************/
#include <rf_ninja/rj_internal.h>           /* parent & siblings                    */
#include <rf_ninja/rj_cnk/rjcnk_internal.h> /* self                                 */

/************************/
/*  Game References     */
/************************/
/****** Shadow Map ******************************************************************/
#define _gj_shadow_tex_callback_    FUNC_REF(void, __cdecl, (s32), 0x01A55828)

#define _gj_shadow_tex_num_         DATA_REF(u8, 0x01934758)

#define _nj_cnk_rotbase_matrix_     DATA_REF(NJS_MATRIX, 0x01934AC0)

/************************/
/*  Source              */
/************************/
/****** Extern **********************************************************************/
void
rjCnkBeginShadowTex(void)
{
    if ( _nj_control_3d_flag_ & 0x80000 )
    {
        NJS_MATRIX m = *_nj_curr_matrix_;

        njInvertMatrix(&m);

        gjStartVertex3D(&m, 0);

        if (_gj_shadow_tex_callback_) _gj_shadow_tex_callback_(1);

        _rj_cnk_shadow_tex_ = _gj_shadow_tex_num_ + 1;
    }
    else
    {
        _rj_cnk_shadow_tex_ = 0;
    }
}

void
rjCnkEndShadowTex(void)
{
    _rj_cnk_shadow_tex_ = 0;
}

Sint32
rjCnkDrawModel(const NJS_CNK_MODEL* model)
{
    if ( ShadowCnkDraw ) return CnkDrawShadow_Ext(model, _nj_vertex_buf_);

    /** Model clip **/
    if ( _nj_control_3d_flag_ & NJD_CONTROL_3D_MODEL_CLIP )
    {
        if ( model->r > 0.f && njCnkModelClip(model) )
        {
            return CNK_RETN_CLIP;
        }
    }

    /** Model callback **/
    if ( _rj_cnk_model_callback_ )
    {
        _rj_cnk_model_callback_( (NJS_CNK_MODEL*) model );
    }

    const Uint32 cnkctrl = _rj_cnk_ctrl_flag_;

    if ( model->vlist && (cnkctrl & RJD_CNK_CTRL_VLIST) )
    {
        rjCnkBeginDepthQueue( model );

        if ( rjCnkVList(model->vlist, _nj_vertex_buf_) )
        {
            return CNK_RETN_CLIP;
        }
    }
    
    if ( model->plist && (cnkctrl & RJD_CNK_CTRL_PLIST) )
    {
        rjCnkPList(model->plist, _nj_vertex_buf_);
    }

    /** Drawing completed successfully **/
    return CNK_RETN_OK;
}

static inline void
___rjCnkObjectRotateBase(void)
{
    njGetMatrix(&_nj_cnk_rotbase_matrix_);
}

static inline void
___rjCnkObjectRotateSet(void)
{
    NJS_MATRIX* m = _nj_curr_matrix_;

    m->m[0][0] = _nj_cnk_rotbase_matrix_.m[0][0];
    m->m[0][1] = _nj_cnk_rotbase_matrix_.m[0][1];
    m->m[0][2] = _nj_cnk_rotbase_matrix_.m[0][2];
    m->m[1][0] = _nj_cnk_rotbase_matrix_.m[1][0];
    m->m[1][1] = _nj_cnk_rotbase_matrix_.m[1][1];
    m->m[1][2] = _nj_cnk_rotbase_matrix_.m[1][2];
    m->m[2][0] = _nj_cnk_rotbase_matrix_.m[2][0];
    m->m[2][1] = _nj_cnk_rotbase_matrix_.m[2][1];
    m->m[2][2] = _nj_cnk_rotbase_matrix_.m[2][2];
}

void
rjCnkTransformObject( const NJS_CNK_OBJECT* object, Sint32(*callback)(NJS_CNK_MODEL*) )
{
    NJS_CNK_OBJECT* p_obj = (NJS_CNK_OBJECT*) object; // scary, but safe!

    do
    {
        const Uint32 evals = p_obj->evalflags;

        if ( evals & NJD_EVAL_ROTATE_BASE )
        {
            ___rjCnkObjectRotateBase();
        }

        Sint32 mdlret = CNK_RETN_OK;

        if ( ( evals & (NJD_EVAL_UNIT_POS|NJD_EVAL_UNIT_ANG|NJD_EVAL_UNIT_SCL) ) == (NJD_EVAL_UNIT_POS|NJD_EVAL_UNIT_ANG|NJD_EVAL_UNIT_SCL) )
        {
            if ( _rj_cnk_object_callback_ )
            {
                _rj_cnk_object_callback_( p_obj );
            }

            if ( !(evals & NJD_EVAL_HIDE) )
            {
                mdlret = callback( p_obj->model );
            }

            if ( !(evals & NJD_EVAL_BREAK) && (!(evals & NJD_EVAL_CLIP) || mdlret == CNK_RETN_OK) )
            {
                rjCnkTransformObject( p_obj->child, callback );
            }
        }
        else // not all unit flags
        {
            njPushMatrixEx();

            if ( !(evals & NJD_EVAL_UNIT_POS) )
            {
                njTranslateEx2( p_obj->pos );
            }

            if ( !(evals & NJD_EVAL_UNIT_ANG) )
            {
                if ( evals & NJD_EVAL_ROTATE_SET )
                {
                    ___rjCnkObjectRotateSet();
                }
                else if ( evals & NJD_EVAL_QUATERNION )
                {
                    njQuaternionEx2( p_obj->re_quat, (Float*) p_obj->ang );
                }
                else
                {
                    njRotateEx( p_obj->ang, evals & NJD_EVAL_ZXY_ANG );
                }
            }

            if ( !(evals & NJD_EVAL_UNIT_SCL) )
            {
                njScaleEx2( p_obj->scl );
            }

            if ( _rj_cnk_object_callback_ )
            {
                _rj_cnk_object_callback_( p_obj );
            }

            if ( p_obj->model && !(evals & NJD_EVAL_HIDE) )
            {
                mdlret = callback( p_obj->model );
            }

            if ( !(evals & NJD_EVAL_BREAK) && (!(evals & NJD_EVAL_CLIP) || mdlret == CNK_RETN_OK) )
            {
                rjCnkTransformObject( p_obj->child, callback );
            }

            njPopMatrixEx();
        }

        p_obj = p_obj->sibling;
    }
    while ( p_obj );
}

void
rjCnkDrawObject(const NJS_CNK_OBJECT* object)
{
    rjCnkTransformObject(object, rjCnkDrawModel);
}

void
rjCnkDrawMotion(const NJS_CNK_OBJECT* object, const NJS_MOTION* motion, Float frame)
{
    njDrawMotion(object, motion, frame, rjCnkDrawModel);
}

void
rjCnkDrawMotionLink(const NJS_CNK_OBJECT* object, const NJS_MOTION_LINK* motion_link, Float rate)
{
    njDrawMotionLink(object, motion_link, rate, rjCnkDrawModel);
}

void
rjCnkDrawShapeMotion(const NJS_CNK_OBJECT* object, const NJS_MOTION* motion, const NJS_MOTION* shape, Float frame)
{
    njDrawShapeMotion(object, motion, shape, frame, frame, rjCnkDrawModel);
}

void
rjCnkDrawShapeMotionLink(const NJS_CNK_OBJECT* object, const NJS_MOTION_LINK* motion_link, const NJS_MOTION_LINK* shape_link, Float rate)
{
    njDrawShapeLink(object, motion_link, shape_link, rate, rjCnkDrawModel);
}

void
rjCnkDrawShapeMotionBE(const NJS_CNK_OBJECT* object, const NJS_MOTION* motion, const NJS_MOTION* shape, Float frame)
{
    /** Big endian shape motion draw **/

    njDrawShapeMotionBE(object, motion, shape, frame, frame, rjCnkDrawModel);
}

void
rjCnkDrawShapeMotionLinkBE(const NJS_CNK_OBJECT* object, const NJS_MOTION_LINK* motion_link, const NJS_MOTION_LINK* shape_link, Float rate)
{
    /** Big endian shape link draw **/
    
    njDrawShapeLinkBE(object, motion_link, shape_link, rate, rjCnkDrawModel);
}

/****** Other Draws *****************************************************************/
static Sint32
CnkDrawModel_NoClip(const NJS_CNK_MODEL* model)
{
    NJS_CNK_MODEL mdl = *model;

    mdl.r = -1.f;

    return rjCnkDrawModel( &mdl );
}

#if 0

#define chAttrEnable                    DATA_REF(Bool, 0x01AED2CC)

static void
CalcVlistColorCh(NJS_BGRA* dst, const NJS_BGRA* src)
{
    // RGBA (Chao) -> ARGB (Cnk)
    dst->a = src->b;
    dst->r = src->a;
    dst->g = src->r;
    dst->b = src->g;
}

static Sint32
CnkDrawModel_ChDraw(const NJS_CNK_MODEL* model)
{
    if ( !chAttrEnable )
    {
        rjCnkSetVListColCallback( CalcVlistColorCh );

        const Sint32 ret = rjCnkDrawModel( model );

        rjCnkSetVListColCallback( nullptr );

        return ret;
    }
    else
    {
        return CNK_RETN_OK;
    }
}

#endif

/****** Cnk Init ********************************************************************/
void
RFD_ChunkInit(void)
{
    /** RF Chunk draw functions **/
    WriteRetn(0x0042D340); // begin draw

    WriteJump(0x0042D500, CnkDrawModel_NoClip); // CnkDrawModelSub
//  WriteJump(0x0056DDD0, CnkDrawModel_ChDraw);

    WriteJump(0x0042EB30, rjCnkTransformObject);

    // fix shape motion not calling motion callback
    WriteJump(0x00784890, rjCnkPushPopShape);
    WriteJump(0x00784E70, rjCnkPushPopShapeLink);
}
