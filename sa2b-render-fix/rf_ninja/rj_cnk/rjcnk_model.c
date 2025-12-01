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
