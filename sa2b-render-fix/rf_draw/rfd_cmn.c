/************************/
/*  Includes            */
/************************/
/****** Core Toolkit ****************************************************************/
#include <samt/core.h>          /* core                                             */
#include <samt/writeop.h>       /* writejump                                        */
#include <samt/memory.h>        /* memcopy                                          */

#define SAMT_INCL_INTERNAL

/****** Ninja ***********************************************************************/
#include <samt/ninja/ninja.h>   /* ninja                                            */

#undef SAMT_INCL_INTERNAL

/****** GX **************************************************************************/
#include <samt/gx/gx.h>         /* gx                                               */

/****** Render Fix ******************************************************************/
#include <rf_core.h>            /* core                                             */
#include <rf_gx.h>              /* rfgx                                             */
#include <rf_shader.h>          /* shader                                           */
#include <rf_magic.h>           /* magiccache                                       */

/****** Game ************************************************************************/
#include <samt/sonic/shaders.h> /* shadermode                                       */

/****** Self ************************************************************************/
#include <rf_draw/rfd_internal.h>               /* parent & siblings                */
#include <rf_draw/rfd_cnkmdl/rfdcnk_internal.h> /* self                             */

#include <dx9ctrl/dx9ctrl.h>

typedef enum
{
    RJE_PIXEL_N,

    RJE_PIXEL_T,         // texture
    RJE_PIXEL_F,         // fog
    RJE_PIXEL_TF,
//  RJE_PIXEL_S,
//  RJE_PIXEL_TS,
//  RJE_PIXEL_FS,
//  RJE_PIXEL_TFS,

//  RJE_SHADEREFF_S,        // shadowtex
//  RJE_SHADEREFF_FS,       // fog + st
//  RJE_SHADEREFF_P,        // pallete

    NB_RJE_PIXEL,
}
RJE_PIXEL;

typedef enum
{
    RJE_DRAW_2D,            /* draw 2d space                                        */
    RJE_DRAW_3D,            /* draw 3d space, with perspective                      */

    NB_DRAW_MD,
}
RJE_DRAW;

typedef struct
{
    Sint32          drawmd;
    
    Uint32          vstride;
    RJE_VERTEX_TYPE vtype;
    RJE_PIXEL       effect;
}
RJS_CTX;

RJS_CTX     _rj_context_;

Sint32      _rj_invert_polygons_;

static dx9_vtx_buff* _rj_mod_vertex_buffer_;

#define RJD_VBUF_TOOBIG         (-1)

#define RJD_VBUF_SIZE_0         (0x0800)
#define RJD_VBUF_SIZE_1         (0x1000)
#define RJD_VBUF_SIZE_2         (0x2000)
#define RJD_VBUF_SIZE_3         (0x4000)
#define RJD_VBUF_SIZE_4         (0x8000)

#define RJD_VBUF_SIZE           (0x1C000 * 4)

static dx9_vtx_buff* _rj_vertex_buffer_;

static byte* _rj_vertex_buffer_base_;
static byte* _rj_vertex_buffer_top_;
static byte* _rj_vertex_buffer_cpy_;

static Uint32 _rj_vertex_buffer_num_;
static Uint32 _rj_vertex_buffer_stride_;

static Uint32 _rj_polygon_format_;

static dx9_vtx_decl* _rj_curr_vtx_decl_;

static dx9_vtx_decl* _rj_vtx_decls_[NB_RJE_VERTEX];

#define RJD_SHADEREFF_TEX           (1)
#define RJD_SHADEREFF_FOG           (2)
#define RJD_SHADEREFF_STEX          (4)
#define RJD_SHADEREFF_PALLETE       (8)

static dx9_vtx_shader* _rj_curr_vtx_shader_;
static dx9_pxl_shader* _rj_curr_pxl_shader_;

static dx9_vtx_shader* _rj_vtx_shaders_[NB_RJE_VERTEX][NB_DRAW_MD];

static dx9_pxl_shader* _rj_pxl_shaders_[NB_RJE_PIXEL];

/************************/
/*  Source              */
/************************/
/****** Extern **********************************************************************/
void
rjSetBlend2D(Int trans)
{
    trans ? SetTransparentDraw() : SetOpaqueDraw();

    const Uint32 texmode = _nj_curr_ctx_->texmode;

    const s32 src = (texmode >> 29) & 7;
    const s32 dst = (texmode >> 26) & 7;

    GX_SetBlendMode(src, dst, !!trans);
}

#define TexInfo2D           DATA_REF(TEXTURE_INFO, 0x019341A0)

void
rjSetTexture2D(Int clamp)
{
    const Uint32 texmode = _nj_curr_ctx_->texmode;

    const NJS_TEXSURFACE* p_texsrf = _nj_curr_ctx_->texsurface;

    /** texture info start **/

    TEXTURE_INFO* p_tinfo = &TexInfo2D;

    p_tinfo->surface = p_texsrf->pSurface;

    /** texture pointer and palette **/

    const Uint32 sflag = p_texsrf->fSurfaceFlags;

    if ( sflag & NJD_SURFACEFLAGS_PALETTIZED )
    {
        p_tinfo->palette = _nj_curr_ctx_->bank;
    }
    else
    {
        p_tinfo->palette = -1;
    }

    /** texture filtering **/

    switch ( (texmode & NJD_TEXTUREFILTER_TRILINEAR_B) >> 13 )
    {
        case 0: // point
        {
            p_tinfo->min_filter = 0;
            p_tinfo->mag_filter = 0;
            break;
        }
        case 1: case 2: case 3: // bilinear (default) // trilinear B // trilinear A
        {
            p_tinfo->min_filter = 1;
            p_tinfo->mag_filter = 1;
            break;
        }
    }

    ___TODO("finish UI filtering feature");

    if ( false ) // don't filter on magnify
    {
        p_tinfo->mag_filter = 0;
    }

    /** texture wrapping **/

    if ( clamp )
    {
        p_tinfo->address_u = p_tinfo->address_u = 0;
    }
    else
    {
        if ( texmode & NJD_TEXTURECLAMP_CLAMP_U )
        {
            p_tinfo->address_u = 0;
        }
        else if ( texmode & NJD_TEXTUREFLIP_FLIP_U )
        {
            p_tinfo->address_u = 2;
        }
        else // repeat
        {
            p_tinfo->address_u = 1;
        }

        if ( texmode & NJD_TEXTURECLAMP_CLAMP_V )
        {
            p_tinfo->address_v = 0;
        }
        else if ( texmode & NJD_TEXTUREFLIP_FLIP_V )
        {
            p_tinfo->address_v = 2;
        }
        else // repeat
        {
            p_tinfo->address_u = 1;
        }
    }

    /** tes5 **/

    p_tinfo->mip_level = (bool)( sflag & NJD_SURFACEFLAGS_MIPMAPED );

    /** set texture **/

    RX_SetTexture(p_tinfo, 0);
}

static void
___rjStartVertex(RJE_VERTEX_TYPE vtxdecl, Sint32 use3d)
{
    _rj_vertex_buffer_base_ = (byte*) _gx_vtx_buf_base_;
    _rj_vertex_buffer_top_  = _rj_vertex_buffer_base_;

    _rj_vertex_buffer_cpy_ = NULL;

    bool tex = false;

    switch ( vtxdecl )
    {
        case RJE_VERTEX_P:
        {
            _rj_vertex_buffer_stride_ = sizeof(RJS_VERTEX_P);
            break;
        }
        case RJE_VERTEX_PT:
        {
            tex = true;

            _rj_vertex_buffer_stride_ = sizeof(RJS_VERTEX_PT);
            break;
        }
        case RJE_VERTEX_PC:
        {
            _rj_vertex_buffer_stride_ = sizeof(RJS_VERTEX_PC);
            break;
        }
        case RJE_VERTEX_PTC:
        {
            tex = true;

            _rj_vertex_buffer_stride_ = sizeof(RJS_VERTEX_PTC);
            break;
        }
        case RJE_VERTEX_PCS:
        {
            _rj_vertex_buffer_stride_ = sizeof(RJS_VERTEX_PCS);
            break;
        }
        case RJE_VERTEX_PTCS:
        {
            tex = true;

            _rj_vertex_buffer_stride_ = sizeof(RJS_VERTEX_PTCS);
            break;
        }
    }

    RJE_PIXEL effect = tex ? RJD_SHADEREFF_TEX : 0;

    if ( ShaderMode & SHADERMODE_FOG )
    {
        effect |= RJD_SHADEREFF_FOG;
    }

    _rj_curr_vtx_decl_   = _rj_vtx_decls_[vtxdecl];
    _rj_curr_vtx_shader_ = _rj_vtx_shaders_[vtxdecl][use3d];
    _rj_curr_pxl_shader_ = _rj_pxl_shaders_[effect];
}

void
rjStartVertex2D(RJE_VERTEX_TYPE vtxdecl)
{
    ___rjStartVertex(vtxdecl, RJE_DRAW_2D);
}

void
rjStartVertex3D(RJE_VERTEX_TYPE vtxdecl)
{
    ___rjStartVertex(vtxdecl, RJE_DRAW_3D);
}

void
rjSetVertexBuffer(dx9_vtx_buff* pVBuf, size_t offset, size_t szStride)
{
    RF_MAGIC_STATECACHE* p_cache = RF_MagicGetStateCache();

    DX9_SetStreamSource(0, pVBuf, offset, szStride);

    if ( p_cache->vbufs[0] != pVBuf )
    {
        p_cache->vbufs[0] = pVBuf;
    }
}

void
rjSetVertexDecl(dx9_vtx_decl* pVDecl)
{
    RF_MAGIC_STATECACHE* p_cache = RF_MagicGetStateCache();

    if ( p_cache->vdecl != pVDecl )
    {
        DX9_SetVtxDecl(pVDecl);

        p_cache->vdecl = pVDecl;
    }
}

void
rjSetShaders(dx9_vtx_shader* vshader, dx9_pxl_shader* pshader)
{
    RF_MAGIC_SHADERCACHE* p_cache = RF_MagicGetStateCache()->shader;

    if ( p_cache->vshader != vshader )
    {
        DX9_SetVtxShader(vshader);

        p_cache->vshader = vshader;
    }

    if ( p_cache->pshader != pshader )
    {
        DX9_SetPxlShader(pshader);

        p_cache->pshader = pshader;
    }
}

void*
rjGetVertexBuffer(void)
{
    return (void*)(_rj_vertex_buffer_top_);
}

s32     ModifierStart(void);
void    ModifierEnd(const s32 i);

static Uint32 _rj_vertex_buffer_offset_;

void
rjEndVertex(void)
{
    if ( !_rj_vertex_buffer_num_ )
    {
        return;
    }

    const u32 pri_type = _rj_polygon_format_;

    u32 pri_num;

    switch ( pri_type )
    {
        case DX9_PRITYPE_TRIANGLELIST:
        {
            pri_num = _rj_vertex_buffer_num_ / 3;
            break;
        }
        case DX9_PRITYPE_TRIANGLESTRIP:
        {
            pri_num = _rj_vertex_buffer_num_ - 2;
            break;
        }
        case DX9_PRITYPE_TRIANGLEFAN:
        {
            pri_num = _rj_vertex_buffer_num_ - 2;
            break;
        }
        case DX9_PRITYPE_LINELIST:
        {
            pri_num = _rj_vertex_buffer_num_ / 2;
            break;
        }
        case DX9_PRITYPE_LINESTRIP:
        {
            pri_num = _rj_vertex_buffer_num_ - 1;
            break;
        }
        case DX9_PRITYPE_POINTLIST:
        {
            pri_num = _rj_vertex_buffer_num_;
            break;
        }
        default:
        {
            return;
        }
    }

    rjSetVertexDecl(_rj_curr_vtx_decl_);
    rjSetShaders(_rj_curr_vtx_shader_, _rj_curr_pxl_shader_);

    const size_t sz = (_rj_vertex_buffer_num_ * _rj_vertex_buffer_stride_);

    /** If the size of this vertex list is larger than the whole buffer,
        delegate it to DrawPrimitiveUP. Better than nothing drawing **/

    if ( sz > RJD_VBUF_SIZE )
    {
        const s32 i = ModifierStart();

        DX9_DrawPrimitiveUP(pri_type, pri_num, _rj_vertex_buffer_base_, _rj_vertex_buffer_stride_);

        ModifierEnd(i);

        _rj_vertex_buffer_num_ = 0;
        return;
    }

    /** Vertex buffer is large enough for incoming data **/

    dx9_vtx_buff* const p_dx9_vbuf = _rj_vertex_buffer_;

    Uint32   offset = _rj_vertex_buffer_offset_;
    dx9_lock lock   = DX9_LOCK_NOOVERWRITE;

    /** If this vertex list will breach the vertex buffer limit, reset the offset
        back around to 0, discard contents, and fill it from the bottom again **/

    if ( (offset + sz) > RJD_VBUF_SIZE )
    {
        offset = _rj_vertex_buffer_offset_ = 0;
        lock   = DX9_LOCK_DISCARD;
    }

    /** Lock the vertex buffer, and fill it with the vertex list to be drawn **/

    void* const p_vbuf = DX9_VertexBufferLock( p_dx9_vbuf, offset, sz, lock );

    mtMemCopy32( p_vbuf, _rj_vertex_buffer_base_, sz / 4 );

    DX9_VertexBufferUnlock( p_dx9_vbuf );

    /** Set the vertex buffer source to draw, at the current offset **/

    rjSetVertexBuffer(p_dx9_vbuf, offset, _rj_vertex_buffer_stride_);

    /** Draw the vertex buffer **/

    const s32 i = ModifierStart();

    DX9_DrawPrimitive(pri_type, 0, pri_num);

    ModifierEnd(i);

    /** Increment offset and reset count **/

    _rj_vertex_buffer_offset_ += sz;

    _rj_vertex_buffer_num_ = 0;
}

static void
___rjCreateTriStripDegen(const size_t stride)
{
    const byte* lastvtx = _rj_vertex_buffer_top_ - stride;

    mtMemCopy(_rj_vertex_buffer_top_, lastvtx, stride);

    _rj_vertex_buffer_top_ += stride;

    _rj_vertex_buffer_num_++;
}

Sint32
rjStartTriStrip(Sint32 len)
{
    if ( _rj_invert_polygons_ )
    {
        len = -len;
    }

    Uint32 nb_vertex;
    bool   str_inv;

    /** If the vertex count is negative, that means this strip is inverted and
        needs to be flipped back. So, invert the count and set the inverted flag **/
    if ( len < 0 )
    {
        nb_vertex = -len;
        str_inv   =  true;
    }
    else
    {
        nb_vertex = len;
        str_inv   = false;
    }

    const Uint32 stride = _rj_vertex_buffer_stride_;
    const Uint32 nb_buf = _rj_vertex_buffer_num_;

    /** If no verteces are currently in the buffer, then the buffer is empty. So,
        setup buffer attributes for drawing a triangle strip **/
    if ( !nb_buf )
    {
        _rj_polygon_format_ = DX9_PRITYPE_TRIANGLESTRIP;

        /** If the first strip is inverted, then save the position of the buffer so
            the next vertex can be copied into it; creating a degen triangle **/
        if (str_inv)
        {
            _rj_vertex_buffer_cpy_  = _rj_vertex_buffer_top_;
            _rj_vertex_buffer_top_ += stride;
            _rj_vertex_buffer_num_  = nb_vertex + 1; // +1 for degen
        }
        else
        {
            _rj_vertex_buffer_cpy_ = nullptr;
            _rj_vertex_buffer_num_ = nb_vertex;
        }

        return nb_vertex;
    }

    /** If the number of verteces in the buffer is odd - meaning the buffer winding
        is inverted - & this strip isn't itself inverted, or vice versa, create an
        additional degen triangle to switch the triangle winding direction. If we
        don't, this strip will be facing the wrong way **/
    if ( (bool)(nb_buf & 0x01) != str_inv )
    {
        ___rjCreateTriStripDegen(stride);
    }

    /** Copy the previous vertex, creating a degen triangle, to link this strip
        onto the end of the buffer **/
    ___rjCreateTriStripDegen(stride);

    /** Set the copy pointer for degen creation and update buffer variables **/
    _rj_vertex_buffer_cpy_  = _rj_vertex_buffer_top_;
    _rj_vertex_buffer_top_ += stride;
    _rj_vertex_buffer_num_ += nb_vertex + 1; // +1 for degen

    return nb_vertex;
}

void
rjEndTriStrip(Sint32 count)
{
    const Uint32 stride = _rj_vertex_buffer_stride_;

    _rj_vertex_buffer_top_ += (stride * count);

    byte* const p_cpy = _rj_vertex_buffer_cpy_;

    /** If there's a copy pointer queued, copy it now. We need to copy the vertex
        +1 from the copy pointer back onto the copy pointer. Or 'p + len' onto 'p' **/
    if ( p_cpy )
    {
        mtMemCopy(p_cpy, p_cpy + stride, stride);
    }
}

Sint32
rjStartTriDestrip(Sint32 count, Bool* invst)
{
    if ( _rj_invert_polygons_ )
    {
        count = -count;
    }

    /** If the vertex count is negative, that means the incomming strip is inverted
        and needs to be flipped back. So, invert the count and set the inverted flag **/
    if ( count < 0 )
    {
        count = -count;

        *invst = TRUE;
    }
    else
    {
        *invst = FALSE;
    }

    const Sint32 nb_vertex = (count - 2) * 3;

    const Uint32 stride = _rj_vertex_buffer_stride_;
    const Uint32 nb_buf = _rj_vertex_buffer_num_;

    /** If no verteces are currently in the buffer, then the buffer is empty. So,
        setup buffer attributes for drawing a triangle strip **/
    if ( !nb_buf )
    {
        _rj_polygon_format_ = DX9_PRITYPE_TRIANGLELIST;

        _rj_vertex_buffer_cpy_ = nullptr;
        _rj_vertex_buffer_num_ = nb_vertex;

        return nb_vertex;
    }

    /** Update buffer variables **/
    _rj_vertex_buffer_num_ = nb_buf + nb_vertex;

    return nb_vertex;
}

void
rjEndTriDestrip(Sint32 count)
{
    _rj_vertex_buffer_top_ += _rj_vertex_buffer_stride_ * count;
}

static Uint32 _rj_mod_vertex_buffer_max_;
Uint32        _rj_mod_vertex_buffer_num_;

static RJS_VERTEX_M* _rj_mod_vertex_buffer_top_;

Sint32
rjStartModTriList(Sint32 nbPoly)
{
    const Sint32 vtx_num = (nbPoly * 3);

    const Uint32 mod_num = _rj_mod_vertex_buffer_num_;

    if ( mod_num + vtx_num >= _rj_mod_vertex_buffer_max_ )
    {
        OutputString("RFDBG: Modifier vertex buffer is full!");

        return FALSE;
    }

    const dx9_size indx = mod_num * sizeof(RJS_VERTEX_M);
    const dx9_size size = vtx_num * sizeof(RJS_VERTEX_M);
    const dx9_lock lock = mod_num ? DX9_LOCK_NOOVERWRITE : DX9_LOCK_DISCARD;

    _rj_mod_vertex_buffer_top_ = DX9_VertexBufferLock(_rj_mod_vertex_buffer_, indx, size, lock);

    return vtx_num;
}

void
rjEndModTriList(Sint32 count)
{
    _rj_mod_vertex_buffer_num_ += count;

    DX9_VertexBufferUnlock(_rj_mod_vertex_buffer_);
}

Sint32
rjStartModTriDestrip(Sint32 count, Bool* invst)
{
    if ( _nj_control_3d_flag_ & NJD_CONTROL_3D_MIRROR_MODEL )
    {
        count = -count;
    }

    if ( count < 0 )
    {
        count = -count;

        *invst = TRUE;
    }
    else
    {
        *invst = FALSE;
    }

    const Sint32 vtx_num = (count - 2) * 3;

    const Uint32 mod_num = _rj_mod_vertex_buffer_num_;

    if ( mod_num + vtx_num >= _rj_mod_vertex_buffer_max_ )
    {
        OutputString("RFDBG: Modifier vertex buffer is full!");

        return FALSE;
    }

    const dx9_size indx = mod_num * sizeof(RJS_VERTEX_M);
    const dx9_size size = vtx_num * sizeof(RJS_VERTEX_M);
    const dx9_lock lock = mod_num ? DX9_LOCK_NOOVERWRITE : DX9_LOCK_DISCARD;

    _rj_mod_vertex_buffer_top_ = DX9_VertexBufferLock(_rj_mod_vertex_buffer_, indx, size, lock);

    return vtx_num;
}

void
rjEndModTriDestrip(Sint32 count)
{
    rjEndModTriList(count);
}

RJS_VERTEX_M*
rjGetModVertexBuffer(void)
{
    return _rj_mod_vertex_buffer_top_;
}

void
rjRenderModVertexBuffer(void)
{
    if ( !_rj_mod_vertex_buffer_num_ )
    {
        return;
    }

    rjSetVertexBuffer( _rj_mod_vertex_buffer_, 0, sizeof(RJS_VERTEX_M) );

    DX9_DrawPrimitive(DX9_PRITYPE_TRIANGLELIST, 0, _rj_mod_vertex_buffer_num_ / 3);
}

void
rjClearModVertexBuffer(void)
{
    _rj_mod_vertex_buffer_num_ = 0;
}

void
rjInitModVertexBuffer(Sint32 size)
{
    ___NOTE("This function is temporary, remove later");

    if ( size <= 0 )
    {
        return;
    }

    _rj_mod_vertex_buffer_max_ = (size * 4) / sizeof(RJS_VERTEX_M);

    _rj_mod_vertex_buffer_ = DX9_CreateVertexBuffer(size * 4, DX9_USAGE_DYNAMIC|DX9_USAGE_WRITEONLY, DX9_POOL_DEFAULT);
}

#define SHADER_VS_NAME      "rjvs"
#define SHADER_PS_NAME      "rjps"
#define SHADERMOD_VS_NAME   "rjmvs"
#define SHADERMOD_PS_NAME   "rjmps"

/****** Init ************************************************************************/
void
RFD_CoreInit(void)
{
    // compile shaders
    {
        dx9_macro macros[5];

        macros[0] = (dx9_macro){ "VTX_3D", "1" };

        /** Vertex Shaders **/

        macros[1] = (dx9_macro){ 0 };

        _rj_vtx_shaders_[RJE_VERTEX_P][RJE_DRAW_2D] = RF_CompileVtxShader(SHADER_VS_NAME, macros+1);
        _rj_vtx_shaders_[RJE_VERTEX_P][RJE_DRAW_3D] = RF_CompileVtxShader(SHADER_VS_NAME, macros);

        macros[1] = (dx9_macro){ "VTX_C", "1" };
        macros[2] = (dx9_macro){ 0 };

        _rj_vtx_shaders_[RJE_VERTEX_PC][RJE_DRAW_2D] = RF_CompileVtxShader(SHADER_VS_NAME, macros+1);
        _rj_vtx_shaders_[RJE_VERTEX_PC][RJE_DRAW_3D] = RF_CompileVtxShader(SHADER_VS_NAME, macros);

        macros[1] = (dx9_macro){ "VTX_C", "1" };
        macros[2] = (dx9_macro){ "VTX_S", "1" };
        macros[3] = (dx9_macro){ 0 };

        _rj_vtx_shaders_[RJE_VERTEX_PCS][RJE_DRAW_2D] = RF_CompileVtxShader(SHADER_VS_NAME, macros+1);
        _rj_vtx_shaders_[RJE_VERTEX_PCS][RJE_DRAW_3D] = RF_CompileVtxShader(SHADER_VS_NAME, macros);

        macros[1] = (dx9_macro){ "VTX_T", "1" };
        macros[2] = (dx9_macro){ "VTX_C", "1" };
        macros[3] = (dx9_macro){ 0 };

        _rj_vtx_shaders_[RJE_VERTEX_PTC][RJE_DRAW_2D] = RF_CompileVtxShader(SHADER_VS_NAME, macros+1);
        _rj_vtx_shaders_[RJE_VERTEX_PTC][RJE_DRAW_3D] = RF_CompileVtxShader(SHADER_VS_NAME, macros);

        macros[1] = (dx9_macro){ "VTX_T", "1" };
        macros[2] = (dx9_macro){ "VTX_C", "1" };
        macros[3] = (dx9_macro){ "VTX_S", "1" };
        macros[4] = (dx9_macro){ 0 };

        _rj_vtx_shaders_[RJE_VERTEX_PTCS][RJE_DRAW_2D] = RF_CompileVtxShader(SHADER_VS_NAME, macros+1);
        _rj_vtx_shaders_[RJE_VERTEX_PTCS][RJE_DRAW_3D] = RF_CompileVtxShader(SHADER_VS_NAME, macros);

        /** Pixel Shaders **/

        macros[0] = (dx9_macro){ 0 };

        _rj_pxl_shaders_[RJE_PIXEL_N]  = RF_CompilePxlShader(SHADER_PS_NAME, macros);

        macros[0] = (dx9_macro){ "PXL_T", "1" };
        macros[1] = (dx9_macro){ 0 };

        _rj_pxl_shaders_[RJE_PIXEL_T]  = RF_CompilePxlShader(SHADER_PS_NAME, macros);

        macros[0] = (dx9_macro){ "PXL_F", "1" };
        macros[1] = (dx9_macro){ 0 };

        _rj_pxl_shaders_[RJE_PIXEL_F]  = RF_CompilePxlShader(SHADER_PS_NAME, macros);

        macros[0] = (dx9_macro){ "PXL_T", "1" };
        macros[1] = (dx9_macro){ "PXL_F", "1" };
        macros[2] = (dx9_macro){ 0 };

        _rj_pxl_shaders_[RJE_PIXEL_TF]  = RF_CompilePxlShader(SHADER_PS_NAME, macros);
    }

    /** Vertex Buffers **/

    _rj_vertex_buffer_ = DX9_CreateVertexBuffer(RJD_VBUF_SIZE, DX9_USAGE_DYNAMIC|DX9_USAGE_WRITEONLY, DX9_POOL_DEFAULT);

    /** Vertex Declarations **/

    dx9_vtx_elem vtx_elems[5];

    // position

    vtx_elems[0] = (dx9_vtx_elem){ 0, 0 , DX9_VTXTYPE_FLOAT3, DX9_VTXMETH_DEFAULT, DX9_VTXUSE_POSITION, 0 };
    vtx_elems[1] = (dx9_vtx_elem)DX9_VTX_ELEM_END();
    vtx_elems[2] = vtx_elems[1];
    vtx_elems[3] = vtx_elems[1];
    vtx_elems[4] = vtx_elems[1];

    _rj_vtx_decls_[RJE_VERTEX_P] = DX9_CreateVtxDecl(vtx_elems);

    // pos + color

//  vtx_elems[0] = (dx9_vtx_elem){ 0, 0 , DX9_VTXTYPE_FLOAT3, DX9_VTXMETH_DEFAULT, DX9_VTXUSE_POSITION, 0 };
    vtx_elems[1] = (dx9_vtx_elem){ 0, 12, DX9_VTXTYPE_COLOR , DX9_VTXMETH_DEFAULT, DX9_VTXUSE_COLOR   , 0 };

    _rj_vtx_decls_[RJE_VERTEX_PC] = DX9_CreateVtxDecl(vtx_elems);

    // pos + color + specular

//  vtx_elems[0] = (dx9_vtx_elem){ 0, 0 , DX9_VTXTYPE_FLOAT3, DX9_VTXMETH_DEFAULT, DX9_VTXUSE_POSITION, 0 };
//  vtx_elems[1] = (dx9_vtx_elem){ 0, 12, DX9_VTXTYPE_COLOR , DX9_VTXMETH_DEFAULT, DX9_VTXUSE_COLOR   , 0 };
    vtx_elems[2] = (dx9_vtx_elem){ 0, 16, DX9_VTXTYPE_COLOR , DX9_VTXMETH_DEFAULT, DX9_VTXUSE_COLOR   , 1 };

    _rj_vtx_decls_[RJE_VERTEX_PCS] = DX9_CreateVtxDecl(vtx_elems);

    vtx_elems[2] = (dx9_vtx_elem)DX9_VTX_ELEM_END();

    // pos + texture (uv)

//  vtx_elems[0] = (dx9_vtx_elem){ 0, 0 , DX9_VTXTYPE_FLOAT3, DX9_VTXMETH_DEFAULT, DX9_VTXUSE_POSITION, 0 };
    vtx_elems[1] = (dx9_vtx_elem){ 0, 12, DX9_VTXTYPE_FLOAT2, DX9_VTXMETH_DEFAULT, DX9_VTXUSE_TEXCOORD, 0 };

    _rj_vtx_decls_[RJE_VERTEX_PT] = DX9_CreateVtxDecl(vtx_elems);

    // pos + tex + color

//  vtx_elems[0] = (dx9_vtx_elem){ 0, 0 , DX9_VTXTYPE_FLOAT3, DX9_VTXMETH_DEFAULT, DX9_VTXUSE_POSITION, 0 };
//  vtx_elems[1] = (dx9_vtx_elem){ 0, 12, DX9_VTXTYPE_FLOAT2, DX9_VTXMETH_DEFAULT, DX9_VTXUSE_TEXCOORD, 0 };
    vtx_elems[2] = (dx9_vtx_elem){ 0, 20, DX9_VTXTYPE_COLOR , DX9_VTXMETH_DEFAULT, DX9_VTXUSE_COLOR   , 0 };

    _rj_vtx_decls_[RJE_VERTEX_PTC] = DX9_CreateVtxDecl(vtx_elems);

    // pos + tex + color + spec

//  vtx_elems[0] = (dx9_vtx_elem){ 0, 0 , DX9_VTXTYPE_FLOAT3, DX9_VTXMETH_DEFAULT, DX9_VTXUSE_POSITION, 0 };
//  vtx_elems[1] = (dx9_vtx_elem){ 0, 12, DX9_VTXTYPE_FLOAT2, DX9_VTXMETH_DEFAULT, DX9_VTXUSE_TEXCOORD, 0 };
//  vtx_elems[2] = (dx9_vtx_elem){ 0, 20, DX9_VTXTYPE_COLOR , DX9_VTXMETH_DEFAULT, DX9_VTXUSE_COLOR   , 0 };
    vtx_elems[3] = (dx9_vtx_elem){ 0, 24, DX9_VTXTYPE_COLOR , DX9_VTXMETH_DEFAULT, DX9_VTXUSE_COLOR   , 1 };

    _rj_vtx_decls_[RJE_VERTEX_PTCS] = DX9_CreateVtxDecl(vtx_elems);
}
