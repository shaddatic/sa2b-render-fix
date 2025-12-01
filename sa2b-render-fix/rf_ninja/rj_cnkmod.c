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

/****** Self ************************************************************************/
#include <rf_ninja/rj_internal.h>               /* parent & siblings                */
#include <rf_ninja/rj_cnkmod/rfdmod_internal.h> /* self                             */

/************************/
/*  Includes            */
/************************/
/****** Extern **********************************************************************/
Sint32
njCnkModDrawModel(NJS_CNK_MODEL* model)
{
    if ( _nj_control_3d_flag_ & NJD_CONTROL_3D_MODEL_CLIP )
    {
        if ( model->r > 0.f && njCnkModelClip(model) )
        {
            return CNK_RETN_CLIP;
        }
    }

    if ( model->vlist )
    {
        if ( rjCnkModVList(model->vlist, _nj_vertex_buf_) == CNK_RETN_CLIP )
        {
            return CNK_RETN_CLIP;
        }
    }

    if ( model->plist )
    {
        rjCnkModPList(model->plist, _nj_vertex_buf_);
    }

    return CNK_RETN_OK;
}
