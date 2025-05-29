/************************/
/*  Includes            */
/************************/
/****** Core Toolkit ****************************************************************/
#include <samt/core.h>      /* core                                                 */

/****** Ninja ***********************************************************************/
#include <samt/ninja/ninja.h> /* ninja                                              */

/****** GX **************************************************************************/
#include <samt/gx/gx.h>     /* GX                                                   */

/****** Render Fix ******************************************************************/
#include <rf_core.h>        /* core                                                 */
#include <rf_renderstate.h> /* render state                                         */
#include <rf_util.h>        /* utility                                              */
#include <rf_gx.h>          /* rf gx                                                */
#include <rf_light.h>

/****** Self ************************************************************************/
#include <rf_draw/rfd_cnkmdl/rfdcnk_internal.h> /* parent & siblings                */

Float _rj_cnk_inten_multiply_ = 1.f;

/************************/
/*  Source              */
/************************/
/****** Chunk Lighting  *************************************************************/
static void
rjCnkInvertLightDirection(Sint32 inv)
{
    _rj_cnk_inten_multiply_ = inv ? -1.f : 1.f;
}

void
rjCnkBeginLighting(const CNK_CTX* restrict pCtx)
{
    if ( !(pCtx->flag & CTXF_CTL_BACKFACECULL) || pCtx->flag & CTXF_DRAW_NORMAL )
    {
        rjCnkInvertLightDirection( FALSE );
    }
    else
    {
        rjCnkInvertLightDirection( TRUE );
    }
}

bool
rjCnkBeginTwoPassLighting(const CNK_CTX* restrict pCtx)
{
    if ( !(pCtx->flag & CTXF_CTL_BACKFACECULL) || !(pCtx->fst & NJD_FST_DB) )
    {
        return false;
    }

    if ( (pCtx->flag & (CTXF_DRAW_NORMAL|CTXF_DRAW_INVERSE)) == (CTXF_DRAW_NORMAL|CTXF_DRAW_INVERSE) )
    {
        _rj_invert_polygons_ = TRUE;

        rjCnkInvertLightDirection( TRUE );
        return true;
    }

    return false;
}

/****** Specular ********************************************************************/
static Sint32
___rjCnkGetAutoSpecMode(void)
{
    switch ( RFRS_GetCnkFuncMode() )
    {
        case RFRS_CNKFUNCMD_NORMAL:
        {
            return RJE_CNK_SPECFUNC_NORMAL;
        }
        case RFRS_CNKFUNCMD_EASY:
        case RFRS_CNKFUNCMD_DIRECT:
        {
            return RJE_CNK_SPECFUNC_EASY;
        }
        case RFRS_CNKFUNCMD_SIMPLE:
        {
            return RJE_CNK_SPECFUNC_SIMPLE;
        }
        case RFRS_CNKFUNCMD_EASYMULTI:
        case RFRS_CNKFUNCMD_SIMPLEMULTI:
        {
            return RJE_CNK_SPECFUNC_MULTI;
        }
    }

    return RJE_CNK_SPECFUNC_EASY; // this is unreachable
}

void
rjCnkBeginDraw(void)
{
    ___NOTE("This will read a global renderstate eventually");
    switch ( 1 ) 
    {
        case 0:
        {
            _rj_cnk_spec_mode_ = RJE_CNK_SPECFUNC_NONE;
            break;
        }
        case 1:
        {
            _rj_cnk_spec_mode_ = ___rjCnkGetAutoSpecMode();
            break;
        }
        case 2:
        {
            _rj_cnk_spec_mode_ = RJE_CNK_SPECFUNC_NORMAL;
            break;
        }
        case 3:
        {
            _rj_cnk_spec_mode_ = RJE_CNK_SPECFUNC_EASY;
            break;
        }
        case 4:
        {
            _rj_cnk_spec_mode_ = RJE_CNK_SPECFUNC_SIMPLE;
            break;
        }
        case 5:
        {
            _rj_cnk_spec_mode_ = RJE_CNK_SPECFUNC_MULTI;
            break;
        }
    }
}

void
rjCnkEndDraw(void)
{
    GX_SetCullMode(GXD_CULLMODE_NONE);
}
