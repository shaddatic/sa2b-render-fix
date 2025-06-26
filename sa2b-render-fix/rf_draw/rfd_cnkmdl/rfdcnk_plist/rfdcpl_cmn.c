/************************/
/*  Includes            */
/************************/
/****** Core Toolkit ****************************************************************/
#include <samt/core.h>      /* core                                                 */
#include <samt/memory.h>    /* MemCopy                                              */

/****** Ninja ***********************************************************************/
#include <samt/ninja/ninja.h> /* ninja                                              */

/****** GX **************************************************************************/
#include <samt/gx/gx.h>     /* GX                                                   */

/****** Render Fix ******************************************************************/
#include <rf_core.h>        /* core                                                 */
#include <rf_renderstate.h> /* render state                                         */
#include <rf_util.h>        /* utility                                              */
#include <rf_magic.h>       /* magic                                                */

/****** Self ************************************************************************/
#include <rf_draw/rfd_cnkmdl/rfdcnk_plist/rfdcpl_internal.h> /* parent & siblings   */
#include <rf_draw/rfd_cnkmdl/rfdcnk_plist/rfdcpl_cmn.h>      /* common              */

/************************/
/*  Source              */
/************************/
/****** Start/End Vertex ************************************************************/
void
rjCnkStartVertexNonTex(CNK_CTX* const pCtx)
{
    rjStartVertex3D(RJE_VERTEX_PCS); // pos,col,spec

    /** Magic: Shadow Tex **/
    const f32 smf = _rj_cnk_shadow_tex_ ? (f32)_rj_cnk_shadow_tex_ : 0.f;

    RF_MagicSetShaderConstantFloat(MAGIC_SHADER_VERTEX, 155, smf, 1);

    /** Cnk Context **/
    pCtx->flag |= CTXF_STATE_NONTEX;

    rjCnkExecContext(pCtx);
}

void
rjCnkStartVertexTex(CNK_CTX* const pCtx)
{
    rjStartVertex3D(RJE_VERTEX_PTCS); // pos,tex,col,spec

    /** Magic: Shadow Tex **/
    const f32 smf = _rj_cnk_shadow_tex_ ? (f32)_rj_cnk_shadow_tex_ : 1.f;

    RF_MagicSetShaderConstantFloat(MAGIC_SHADER_VERTEX, 155, smf, 1);

    /** Cnk Context **/
    pCtx->flag &= ~CTXF_STATE_NONTEX;

    rjCnkExecContext(pCtx);
}

void
rjCnkEndVertex(void)
{
    rjEndVertex();

    /** Polygon inversion reset **/
    _rj_invert_polygons_ = FALSE;
}
