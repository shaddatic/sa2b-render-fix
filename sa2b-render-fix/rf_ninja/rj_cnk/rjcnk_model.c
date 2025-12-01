/********************************/
/*  Includes                    */
/********************************/
/****** SAMT ************************************************************************************/
#include <samt/core.h>              /* core                                                     */

/****** Ninja ***********************************************************************************/
#include <samt/ninja/ninja.h>       /* ninja                                                    */

/****** Render Fix ******************************************************************************/
#include <rf_core.h>                /* core                                                     */
#include <rf_renderstate.h>         /* render state                                             */

/****** Self ************************************************************************************/
#include <rf_ninja/rj_cnk/rjcnk_internal.h> /* parent & siblings                                */

/********************************/
/*  Source                      */
/********************************/
/****** Draw ************************************************************************************/
static Sint32
___rjCnkDrawModel(NJS_CNK_MODEL* model)
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
        _rj_cnk_model_callback_( model );
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

static inline Sint32
___CnkDrawModelFunc(NJS_CNK_MODEL* model, RFRS_CNKFUNCMD func)
{
    _rj_cnk_context_.func = func;

    return ___rjCnkDrawModel(model);
}

/****** Ninja Draw ******************************************************************************/
Sint32
rjCnkDrawModel(NJS_CNK_MODEL* model)
{
    return ___CnkDrawModelFunc(model, RFRS_GetCnkFuncMode());
}

Sint32
rjCnkNormalDrawModel(NJS_CNK_MODEL* model)
{
    return ___CnkDrawModelFunc(model, RFRS_CNKFUNCMD_NORMAL);
}

Sint32
njCnkEasyDrawModel(NJS_CNK_MODEL* model)
{
    return ___CnkDrawModelFunc(model, RFRS_CNKFUNCMD_EASY);
}

Sint32
njCnkSimpleDrawModel(NJS_CNK_MODEL* model)
{
    return ___CnkDrawModelFunc(model, RFRS_CNKFUNCMD_SIMPLE);
}

Sint32
njCnkEasyMultiDrawModel(NJS_CNK_MODEL* model)
{
    return ___CnkDrawModelFunc(model, RFRS_CNKFUNCMD_EASYMULTI);
}

Sint32
njCnkSimpleMultiDrawModel(NJS_CNK_MODEL* model)
{
    return ___CnkDrawModelFunc(model, RFRS_CNKFUNCMD_SIMPLEMULTI);
}

Sint32
njCnkDirectDrawModel(NJS_CNK_MODEL* model)
{
    return ___CnkDrawModelFunc(model, RFRS_CNKFUNCMD_DIRECT);
}
