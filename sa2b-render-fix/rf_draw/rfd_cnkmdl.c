/************************/
/*  Includes            */
/************************/
/****** Core Toolkit ****************************************************************/
#include <samt/core.h>          /* core                                             */
#include <samt/writeop.h>       /* WriteJump                                        */

/****** Ninja ***********************************************************************/
#include <samt/ninja/ninja.h>   /* ninja                                            */

/****** Game ************************************************************************/
#include <samt/sonic/shaders.h> /* setshaders                                       */

/****** Render Fix ******************************************************************/
#include <rf_core.h>            /* core                                             */
#include <rf_renderstate.h>     /* render state                                     */
#include <rf_magic.h>           /* rf_magic                                         */
#include <rf_light.h>

/****** Self ************************************************************************/
#include <rf_draw/rfd_internal.h>               /* parent & siblings                */
#include <rf_draw/rfd_cnkmdl/rfdcnk_internal.h> /* self                             */

/************************/
/*  Game References     */
/************************/
/****** Shadow Map ******************************************************************/
#define _gj_shadow_tex_callback_    FUNC_REF(void, __cdecl, (s32), 0x01A55828)

#define _gj_shadow_tex_num_         DATA_REF(u8, 0x01934758)

/************************/
/*  Export Data         */
/************************/
/****** Chunk Draw ******************************************************************/
Uint32   _rj_cnk_vertex_attr_;  /* vertex attributes                                */

Uint32   _rj_cnk_blend_mode_;    /* alpha blend                                     */

NJS_ARGB _rj_cnk_diff_material_; /* diffuse material                                */
NJS_ARGB _rj_cnk_ambi_material_; /* ambient material                    (a == noop) */
NJS_ARGB _rj_cnk_spec_material_; /* specular material               (a == exponent) */

Sint32 _rj_cnk_shadow_tex_;

Sint32 _rj_cnk_spec_mode_;

Sint32 _rj_cnk_depth_queue_;

RJF_CNK_VCOLFUNC* _rj_cnk_vcol_funcs_[NB_RJE_CNK_VCOLFUNC] =
{
    [RJE_CNK_VCOLFUNC_MATERIAL] = rjCnkVertexColorMaterial,
    [RJE_CNK_VCOLFUNC_D8]       = rjCnkVertexColorD8,
    [RJE_CNK_VCOLFUNC_LIGHT]    = rjCnkVertexColorLights,
    [RJE_CNK_VCOLFUNC_LIGHTD8]  = rjCnkVertexColorLightsD8,
};

RJF_CNK_SPECFUNC* _rj_cnk_spec_funcs_[NB_RJE_CNK_SPECFUNC] =
{
    [RJE_CNK_SPECFUNC_NONE]   = rjCnkSpecularNone,
    [RJE_CNK_SPECFUNC_NORMAL] = rjCnkSpecularNormal,
    [RJE_CNK_SPECFUNC_EASY]   = rjCnkSpecularEasy,
    [RJE_CNK_SPECFUNC_SIMPLE] = rjCnkSpecularSimple,
    [RJE_CNK_SPECFUNC_MULTI]  = rjCnkSpecularMulti,
    [RJE_CNK_SPECFUNC_S8]     = rjCnkSpecularS8,
};

RJF_CNK_VLIST_POS* _rj_cnk_vlistfunc_pos_ = rjCnkCalcVlistPosition;
RJF_CNK_VLIST_NRM* _rj_cnk_vlistfunc_nrm_ = rjCnkCalcVlistNormal;
RJF_CNK_VLIST_COL* _rj_cnk_vlistfunc_col_ = rjCnkCalcVlistColor;
RJF_CNK_VLIST_SPC* _rj_cnk_vlistfunc_spc_ = rjCnkCalcVlistSpecular;

/****** UV Offset *******************************************************************/
RJS_UV _rj_cnk_uv_scroll_;
RJS_UV _rj_cnk_env_scroll_;

/****** Obj/Mdl Callback ************************************************************/
void(*_rj_cnk_object_callback_)(NJS_CNK_OBJECT*);
void(*_rj_cnk_model_callback_)(NJS_CNK_MODEL*);

/****** Texture Callback ************************************************************/
Sint16 (__cdecl* _rj_cnk_texture_callback_)(Sint16 texid);

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

    /** Draw **/

    if ( ShadowCnkDraw )
    {
        /** Draw model in 1 pass without texture or lighting for shadow texture. I
            haven't implimented this, so it's still using the original code **/

        if ( CnkDrawShadow_Ext(model, _nj_vertex_buf_) == -1 )
        {
            return CNK_RETN_CLIP;
        }
    }
    else // normal draw
    {
        /** Depth queue **/
        rjCnkBeginDepthQueue( model );

        if ( model->vlist )
        {
            if ( rjCnkVList(model->vlist, _nj_vertex_buf_) == -1 )
            {
                return CNK_RETN_CLIP;
            }
        }

        if ( model->plist )
        {
            rjCnkPList(model->plist, _nj_vertex_buf_);
        }
    }

    /** Drawing completed successfully **/
    return CNK_RETN_OK;
}

#define _nj_cnk_rotbase_matrix_             DATA_REF(NJS_MATRIX, 0x01934AC0)

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

/****** Cnk Modify ******************************************************************/
void
rjCnkSetUvScroll(Float u, Float v)
{
    _rj_cnk_uv_scroll_.u = u;
    _rj_cnk_uv_scroll_.v = v;
}

void
rjCnkSetEnvUvScroll(Float u, Float v)
{
    _rj_cnk_env_scroll_.u = u;
    _rj_cnk_env_scroll_.v = v;
}

void
rjCnkSetTextureCallback(Sint16(__cdecl* callback)(Sint16 texid))
{
    _rj_cnk_texture_callback_ = callback;
}

void
rjCnkSetObjectCallback(void(__cdecl* callback)(NJS_CNK_OBJECT* object))
{
    _rj_cnk_object_callback_ = callback;
}

void
rjCnkSetModelCallback(void(__cdecl* callback)(NJS_CNK_MODEL* model))
{
    _rj_cnk_model_callback_ = callback;
}

void
rjCnkSetVListPositionFunc(void(__cdecl* func)(const NJS_POINT3* in, NJS_POINT3* out))
{
    _rj_cnk_vlistfunc_pos_ = ( func ) ? ( func ) : ( rjCnkCalcVlistPosition );
}

/****** Model With No Clip **********************************************************/
static Sint32
CnkDrawModel_NoClip(const NJS_CNK_MODEL* model)
{
    NJS_CNK_MODEL mdl = *model;

    mdl.r = -1.f;

    return rjCnkDrawModel( &mdl );
}

/****** Cnk Init ********************************************************************/
void
RFD_ChunkInit(void)
{
    /** RF Chunk draw functions **/
    WriteRetn(0x0042D340); // begin draw


    WriteJump(0x0042D500, CnkDrawModel_NoClip); // CnkDrawModelSub

    WriteJump(0x0042EB30, rjCnkTransformObject);

    // fix shape motion not calling motion callback
    WriteJump(0x00784890, rjCnkPushPopShape);
    WriteJump(0x00784E70, rjCnkPushPopShapeLink);
}
