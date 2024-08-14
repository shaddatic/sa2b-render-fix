/************************/
/*  Includes            */
/************************/
/****** Core Toolkit ****************************************************************/
#include <sa2b/core.h>      /* core                                                 */
#include <sa2b/writeop.h>   /* WriteJump                                            */

/****** Ninja ***********************************************************************/
#include <sa2b/ninja/ninja.h> /* ninja                                              */

/****** GX **************************************************************************/
#include <sa2b/gx/gx.h>     /* GX                                                   */

/****** Render Fix ******************************************************************/
#include <rf_core.h>        /* core                                                 */

/****** Self ************************************************************************/
#include <rf_renderstate/rfrs_internal.h> /* parent & siblings                      */

/************************/
/*  Source Structures   */
/************************/
/****** Vertex Decl *****************************************************************/
typedef struct
{
    float gap0;
    int field_4;
    float field_8;
    int field_C;
    int field_10;
    int field_14;
    int field_18;
    void* D3DVertexDeclaration;
    int field_20;
    uint32_t StrideSize;
    int field_28;
    int field_2C;
    int field_30;
}
VertexDeclarationInfo;

/************************/
/*  Source Data         */
/************************/
/****** Vertex Decl *****************************************************************/
#define VertexDeclInfo              DATA_REF(VertexDeclarationInfo*, 0x0174F7E8)

/************************/
/*  Source              */
/************************/
/****** Static **********************************************************************/
static void
CopyLastVertex(void)
{
    const int stride = VertexDeclInfo->StrideSize;
    const int vtxbuf = _gx_vtx_buf_base_;
    const int lastvtx = _gx_vtx_buf_offset_ - stride;

    memcpy((char*)vtxbuf + _gx_vtx_buf_offset_, (char*)vtxbuf + lastvtx, stride);
    ++_gx_nb_vtx_;
    _gx_vtx_buf_offset_ += stride;
}

static void
SetCull(int16_t vtxCount)
{
    bool ccw = false;

    if (vtxCount < 0)
    {
        vtxCount = -vtxCount;
        ccw = true;
    }

    const int stride = VertexDeclInfo->StrideSize;

    if (!_gx_nb_vtx_)
    {
        _gx_vtx_buf_offset_cpy_ = 0;
        _gx_prim_type_ = 0x98;
        _gx_vtx_buf_start_ = _gx_vtx_buf_offset_;
        _gx_cull_ = ccw;
        _gx_nb_vtx_ += vtxCount;

        if (ccw)
        {
            _gx_vtx_buf_offset_cpy_ = _gx_vtx_buf_offset_;
            ++_gx_nb_vtx_;
            _gx_vtx_buf_offset_ += stride;
        }

        return;
    }

    if (((_gx_nb_vtx_ - 2) & 0x80000001) == 0)
    {
        if (ccw)
        {
            CopyLastVertex();
            CopyLastVertex();
            _gx_vtx_buf_offset_cpy_ = _gx_vtx_buf_offset_;
            _gx_cull_ = ccw;
            _gx_vtx_buf_offset_ += stride;
            _gx_nb_vtx_ += vtxCount + 1;
            return;
        }
    }
    else
    {
        if (!ccw)
        {
            CopyLastVertex();
            CopyLastVertex();
            _gx_vtx_buf_offset_cpy_ = _gx_vtx_buf_offset_;
            _gx_cull_ = ccw;
            _gx_vtx_buf_offset_ += stride;
            _gx_nb_vtx_ += vtxCount + 1;
            return;
        }
    }

    CopyLastVertex();

    _gx_vtx_buf_offset_cpy_ = _gx_vtx_buf_offset_;
    _gx_cull_ = ccw;
    _gx_vtx_buf_offset_ += stride;
    _gx_nb_vtx_ += vtxCount + 1;
}

__declspec(naked)
static void
___SetGXCull(void)
{
    __asm
    {
        push eax
        call SetCull
        add esp, 4
        retn
    }
}

/****** Init ************************************************************************/
void
RFRS_BackFaceCullingInit(void)
{
    WriteCall(0x0042E22D, ___SetGXCull);
    WriteCall(0x0042E388, ___SetGXCull);
    WriteCall(0x0042E59D, ___SetGXCull);
    WriteCall(0x0042E7B1, ___SetGXCull);
    WriteCall(0x0042E9EE, ___SetGXCull);
    WriteCall(0x0042F0FB, ___SetGXCull);
    WriteCall(0x0042F1ED, ___SetGXCull);
    WriteCall(0x0042F2FB, ___SetGXCull);
    WriteCall(0x0042F40D, ___SetGXCull);
    WriteCall(0x0077F908, ___SetGXCull);
}
