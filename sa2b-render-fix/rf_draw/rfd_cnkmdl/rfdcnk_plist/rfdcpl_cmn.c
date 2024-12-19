/************************/
/*  Includes            */
/************************/
/****** Core Toolkit ****************************************************************/
#include <sa2b/core.h>      /* core                                                 */
#include <sa2b/memory.h>    /* MemCopy                                              */

/****** Ninja ***********************************************************************/
#include <sa2b/ninja/ninja.h> /* ninja                                              */

/****** GX **************************************************************************/
#include <sa2b/gx/gx.h>     /* GX                                                   */

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
/****** Start Triangle Strip ********************************************************/
void
CnkStartTriStrip(int16_t nbVtx)
{
    int  nb_vertex;
    bool str_inv;

    /** If the vertex count is negative, that means the incomming strip is inverted
    and needs to be flipped back. So, invert the count and set the inverted flag **/
    if ( nbVtx < 0 )
    {
        nb_vertex = -nbVtx;
        str_inv   =  true;
    }
    else
    {
        nb_vertex = nbVtx;
        str_inv   = false;
    }

    const int stride = VertexDeclInfo->StrideSize;
    const int nb_buf = _gx_nb_vtx_;

    /** If no verteces are currently in the buffer, then the buffer is empty. So,
    setup buffer attributes for drawing a triangle strip **/
    if ( !nb_buf )
    {
        _gx_prim_type_     = GXD_PRIM_TRISTRIP;
        _gx_vtx_buf_start_ = _gx_vtx_buf_offset_;
        _gx_cull_          = str_inv;

        /** If the first strip is inverted, then save the position of the buffer so
        the next vertex can be copied into it; creating a degen triangle **/
        if (str_inv)
        {
            _gx_vtx_buf_offset_cpy_ = _gx_vtx_buf_offset_;
            _gx_vtx_buf_offset_    += stride;
            _gx_nb_vtx_             = nb_vertex + 1; // +1 for copy
        }
        else
        {
            _gx_vtx_buf_offset_cpy_ = 0;
            _gx_nb_vtx_             = nb_vertex;
        }

        return;
    }

    /** If the number of verteces in the buffer is odd & the current strip isn't
    itself inverted, copy an additional vertex onto the buffer **/
    if ( (bool)(nb_buf & 0x01) != str_inv )
    {
        CopyLastVertex(stride);
        ++nb_vertex;
    }

    CopyLastVertex(stride);
    ++nb_vertex;

    /** Set the copy pointer for degen creation and update buffer variables **/
    _gx_vtx_buf_offset_cpy_ = _gx_vtx_buf_offset_;
    _gx_cull_               = str_inv;
    _gx_vtx_buf_offset_    += stride;
    _gx_nb_vtx_             = nb_buf + nb_vertex + 1; // +1 for copy
}

void
CnkStartTriStripInverse(int16_t nbVtx)
{
    CnkStartTriStrip(-nbVtx);
}

void
CnkStartTriList(int16_t nbVtx)
{
    int  nb_vertex;
    bool str_inv;

    /** If the vertex count is negative, that means the incomming strip is inverted
    and needs to be flipped back. So, invert the count and set the inverted flag **/
    if ( nbVtx < 0 )
    {
        nb_vertex = (-nbVtx - 2) * 3;
        str_inv   =  true;
    }
    else
    {
        nb_vertex = (nbVtx - 2) * 3;
        str_inv   = false;
    }

    const int stride = VertexDeclInfo->StrideSize;
    const int nb_buf = _gx_nb_vtx_;

    /** If no verteces are currently in the buffer, then the buffer is empty. So,
    setup buffer attributes for drawing a triangle strip **/
    if ( !nb_buf )
    {
        _gx_prim_type_          = GXD_PRIM_TRIANGLE;
        _gx_vtx_buf_start_      = _gx_vtx_buf_offset_;
        _gx_cull_               = str_inv;
        _gx_vtx_buf_offset_cpy_ = 0;
        _gx_nb_vtx_             = nb_vertex;

        return;
    }

    /** Update buffer variables **/
    _gx_cull_            = str_inv;
    _gx_nb_vtx_          = nb_buf + nb_vertex;
}

void
CnkStartTriListInverse(int16_t nbVtx)
{
    CnkStartTriList(-nbVtx);
}

void
CnkSetupNoTexStrip(CNK_CTX* const pCtx)
{
    const f32 smf = ShadowMapDrawCount ? (f32)(ShadowMapDrawCount + 1) : 0.f;

    RF_MagicSetShaderConstantFloat(MAGIC_SHADER_VERTEX, 155, smf, 1);
    RF_MagicSetShaderConstantFloat(MAGIC_SHADER_PIXEL ,   0, 4.f, 1);

    /** Cnk Context **/

    /** No texture to draw. So, add notex flag **/
    pCtx->flag |= CTXFLG_STRIP_NOTEX;

    rjCnkContext(pCtx);
}

void
CnkSetupTexStrip(CNK_CTX* const pCtx)
{
    const f32 smf = ShadowMapDrawCount ? (f32)(ShadowMapDrawCount + 1) : 1.f;

    RF_MagicSetShaderConstantFloat(MAGIC_SHADER_VERTEX, 155, smf, 1);
    RF_MagicSetShaderConstantFloat(MAGIC_SHADER_PIXEL ,   0, 0.f, 1);

    f32* str36 = *(float**)(0x01A557BC);

    str36[378] = 0.f;

    RF_MagicSetShaderConstantMatrix(MAGIC_SHADER_VERTEX, 160, &str36[250]);

    GX_SetTexMtx(&_unit_matrix_44_, GXD_TEXMTX0, GXD_TG_TEXCOORD0);

    /** Cnk Context **/
    pCtx->flag &= ~CTXFLG_STRIP_NOTEX;

    rjCnkContext(pCtx);
}

void
CnkSetupEnvStrip(CNK_CTX* const pCtx)
{
    const f32 smf = ShadowMapDrawCount ? (f32)(ShadowMapDrawCount + 1) : 1.f;

    RF_MagicSetShaderConstantFloat(MAGIC_SHADER_VERTEX, 155, smf, 1);
    RF_MagicSetShaderConstantFloat(MAGIC_SHADER_PIXEL ,   0, 0.f, 1);

    f32* str36 = *(float**)(0x01A557BC);

    str36[378] = 0.f;

    RF_MagicSetShaderConstantMatrix(MAGIC_SHADER_VERTEX, 160, &str36[250]);

    GX_SetTexMtx(&_env_matrix_44_, GXD_TEXMTX0, GXD_TG_NRM);

    /** Cnk Context **/
    pCtx->flag &= ~CTXFLG_STRIP_NOTEX;

    rjCnkContext(pCtx);
}
