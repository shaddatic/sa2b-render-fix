/********************************/
/*  Includes                    */
/********************************/
/****** Core Toolkit ****************************************************************************/
#include <samt/core.h>              /* core                                                     */
#include <samt/writeop.h>           /* writejump                                                */
#include <samt/memory.h>            /* memcopy                                                  */

/****** Ninja ***********************************************************************************/
#include <samt/ninja/ninja.h>       /* ninja                                                    */
#include <samt/ninja/njcontext.h>   /* ninja context                                            */

/****** GX **************************************************************************************/
#include <samt/gx/gx.h>             /* gx                                                       */

/****** Dx9ctrl *********************************************************************************/
#include <dx9ctrl/dx9ctrl.h>        /* dx9ctrl                                                  */

/****** Render Fix ******************************************************************************/
#include <rf_core.h>                /* core                                                     */
#include <rf_gx.h>                  /* rfgx                                                     */
#include <rf_shader.h>              /* shader                                                   */
#include <rf_magic.h>               /* magiccache                                               */

/****** SOC *************************************************************************************/
#include <samt/soc/shader.h>        /* setshader                                                */

/****** Self ************************************************************************************/
#include <rf_ninja/rj_internal.h>           /* parent & siblings                                */
#include <rf_ninja/rj_cnk/rjcnk_internal.h> /* self                                             */

/********************************/
/*  Constants                   */
/********************************/
/************************************************************************************************/
/*
*   Shader File Names
*/
/****** Normal Draw *****************************************************************************/
#define SHADER_NAME_VS              "rjvs"
#define SHADER_NAME_PS              "rjps"

/****** Modifier Draw ***************************************************************************/
#define SHADER_NAME_MODVS           "rjmvs"
#define SHADER_NAME_MODPS           "rjmps"

/************************************************************************************************/
/*
*   Shader Macros
*/
/****** Vertex **********************************************************************************/
#define SM_VTX_3D                   (RFS_MACRO){ "VTX_3D" , "1" };
#define SM_VTX_TEX                  (RFS_MACRO){ "VTX_TEX", "1" };
#define SM_VTX_COL                  (RFS_MACRO){ "VTX_COL", "1" };
#define SM_VTX_OFF                  (RFS_MACRO){ "VTX_OFF", "1" };

/****** Pixel ***********************************************************************************/
#define SM_PXL_TEX                  (RFS_MACRO){ "PXL_TEX", "1" };
#define SM_PXL_PALETTE              (RFS_MACRO){ "PXL_TEX", "2" };
#define SM_PXL_FOG                  (RFS_MACRO){ "PXL_FOG", "1" };

/****** Shadow Tex ******************************************************************************/
#define SM_VTX_SHTEX                (RFS_MACRO){ "VTX_SHTEX", "1" };
#define SM_PXL_SHTEX                (RFS_MACRO){ "PXL_SHTEX", "1" };

/****** End Macro *******************************************************************************/
#define SM_END                      (RFS_MACRO){ 0 };

/************************************************************************************************/
/*
*   Vertex Buffer
*/
/****** Buffer Size *****************************************************************************/
#define RJD_VBUF_SIZE               (0x1C000 * 4)

/************************************************************************************************/
/*
*   Vertex Buffer
*/
/****** Buffer Size *****************************************************************************/
#define RJD_SHADEREFF_TEX           (1)
#define RJD_SHADEREFF_FOG           (2)
#define RJD_SHADEREFF_PALLETE       (4)

/********************************/
/*  Enums                       */
/********************************/
/****** Pixel Effects ***************************************************************************/
typedef enum
{
    RJE_PIXEL_N,                    /* no pixel effect                                          */

    RJE_PIXEL_T,                    /* use texture                                              */
    RJE_PIXEL_F,                    /* use fog                                                  */
    RJE_PIXEL_TF,                   /* use tex+fog                                              */

    NB_RJE_PIXEL,
}
RJE_PIXEL;

/****** Draw Modes ******************************************************************************/
typedef enum
{
    RJ_DRAW_2D,                    /* draw 2d space                                            */
    RJ_DRAW_3D,                    /* draw 3d space, with perspective                          */

    RJ_NB_DRAW,
}
RJE_DRAW;

/********************************/
/*  Game Defs                   */
/********************************/
/****** Texture Info ****************************************************************************/
#define TexInfo2D                   DATA_REF(TEXTURE_INFO, 0x019341A0)

/********************************/
/*  Data                        */
/********************************/
/****** Invert Polygons *************************************************************************/
static Sint32 _rj_invert_polygons_;

/****** Available States ************************************************************************/
static dx9_vtx_decl* _rj_vtx_decls_[RJ_NB_VERTEX];

static dx9_vtx_buff* _rj_vertex_buffer_;

static RFS_VSHADER* _rj_vtx_shaders_[RJ_NB_VERTEX][RJ_NB_DRAW];
static RFS_PSHADER* _rj_pxl_shaders_[NB_RJE_PIXEL];

static RFS_VSHADER* _rj_mvtx_shader_;
static RFS_PSHADER* _rj_mpxl_shader_;

/****** Current State ***************************************************************************/
static Uint32 _rj_polygon_format_;

static byte* _rj_vertex_buffer_base_;
static byte* _rj_vertex_buffer_top_;
static byte* _rj_vertex_buffer_cpy_;

static Uint32 _rj_vertex_buffer_num_;
static Uint32 _rj_vertex_buffer_stride_;

static dx9_vtx_decl* _rj_curr_vtx_decl_;

static RFS_VSHADER* _rj_curr_vtx_shader_;
static RFS_PSHADER* _rj_curr_pxl_shader_;

/****** Modifier ********************************************************************************/
static dx9_vtx_buff* _rj_mod_vertex_buffer_;

/************************/
/*  Source              */
/************************/
/****** Culling *********************************************************************************/
void
rjSetPolygonCulling(RJ_CULL mode)
{
    GX_SetCullMode(mode);
}

void
rjInvertPolygons(Bool mode)
{
    _rj_invert_polygons_ = mode;
}

/****** Shading *********************************************************************************/
void
rjSetPolygonShading(RJ_SHADE mode)
{
    static RJ_SHADE _rj_polygon_shading_;

    if ( mode != _rj_polygon_shading_ )
    {
        _rj_polygon_shading_ = mode;

        DX9_SetShadingMode( mode == RJ_SHADE_FLAT ? DX9_SHADE_FLAT : DX9_SHADE_GOURAUD );
    }
}

void
rjSetTextureParam(RJ_TEXSHADE shademd, Bool igntexalpha)
{
    static dx9_float4 _rj_texparam_;

    const Float tsm = (Float) shademd;
    const Float ita = igntexalpha ? 1.f : 0.f;

    if ( _rj_texparam_.x != tsm || _rj_texparam_.y != ita )
    {
        _rj_texparam_.x = tsm;
        _rj_texparam_.y = ita;

        RF_ShaderSetConstantF(RF_SCFP_TEXPARAM, &_rj_texparam_, 1);
    }
}

/****** Extern **********************************************************************************/
void
rjSetBlend2D(Int trans)
{
    RJ_ALPHA alphamd;

    if ( trans )
    {
        if ( _nj_control_3d_flag_ & NJD_CONTROL_3D_USE_PUNCHTHROUGH )
        {
            alphamd = RJ_ALPHA_PUNCHTHROUGH;
        }
        else
        {
            alphamd = RJ_ALPHA_TRANSLUCENT;
        }
    }
    else
    {
        alphamd = RJ_ALPHA_OPAQUE;
    }

    const Uint32 tspparam = _nj_curr_ctx_->tspparam;

    const Sint32 src = (tspparam & NJD_COLORBLEND_MASK_SRC) >> NJD_COLORBLEND_SHIFT_SRC;
    const Sint32 dst = (tspparam & NJD_COLORBLEND_MASK_DST) >> NJD_COLORBLEND_SHIFT_DST;

    rjSetAlphaMode(src, dst, alphamd);
}

void
rjSetTexture2D(Int clamp)
{
    rjSetTextureParamCtx();

    const Uint32 tspparam = _nj_curr_ctx_->tspparam;

    const NJS_TEXSURFACE* p_texsrf = _nj_curr_ctx_->texture;

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

    switch ( (tspparam & NJD_TEXTUREFILTER_MASK) >> NJD_TEXTUREFILTER_SHIFT )
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

    /** texture wrapping **/

    if ( clamp )
    {
        p_tinfo->address_u = p_tinfo->address_v = 0;
    }
    else
    {
        if ( tspparam & NJD_TEXTURECLAMP_U )
        {
            p_tinfo->address_u = 0;
        }
        else if ( tspparam & NJD_TEXTUREFLIP_U )
        {
            p_tinfo->address_u = 2;
        }
        else // repeat
        {
            p_tinfo->address_u = 1;
        }

        if ( tspparam & NJD_TEXTURECLAMP_V )
        {
            p_tinfo->address_v = 0;
        }
        else if ( tspparam & NJD_TEXTUREFLIP_V )
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

static NJS_TEXSURFACE*
___rjGetTextureSurface(const NJS_TEXLIST* tls, Int n)
{
    const NJS_TEXMANAGE* p_texman = (NJS_TEXMANAGE*) tls->textures[0].texaddr;
    const NJS_TEXSYSTEM* p_texsys = p_texman->texsys;

    return (NJS_TEXSURFACE*) p_texsys->texsurface.pSurface;
}

NJS_TEXSURFACE*
rjGetTextureSurface(Int n)
{
    const NJS_TEXLIST* p_tls = _nj_curr_ctx_->texlist;

    if ( !p_tls || p_tls->nbTexture <= (Uint32) n )
    {
    TEXX_ERROR:
        return ___rjGetTextureSurface(texlist_rf_texerr, 0);
    }

    NJS_TEXSURFACE* p_tsf = ___rjGetTextureSurface(p_tls, n);

    if ( !p_tsf )
    {
        goto TEXX_ERROR;
    }

    return p_tsf;
}

NJS_TEXSURFACE*
rjGetTextureSurfaceG(Int gbix)
{
    const Int nb_texman = _nj_texmanagesize;

    if ( nb_texman <= 0 )
    {
        return ___rjGetTextureSurface(texlist_rf_texerr, 0);
    }

    const NJS_TEXMANAGE* p_texman = _nj_texmanage;

    for ( int i = 0; i < nb_texman; ++i, ++p_texman )
    {
        const NJS_TEXSYSTEM* p_texsys = p_texman->texsys;

        if ( p_texsys && p_texsys->globalIndex == gbix )
        {
            return (NJS_TEXSURFACE*) &p_texsys->texsurface;
        }
    }

    return ___rjGetTextureSurface(texlist_rf_texerr, 0);
}

Float
rjGetDepth2D(f32 pri)
{
    return ( pri > -1.f ) ? ( 1.f ) : ( -1.f / pri );
}

/****** Context *********************************************************************************/
void
rjSetPolygonCullingCtx(void)
{
    const Uint32 ispparam = _nj_curr_ctx_->ispparam;

    RJ_CULL cull;

    switch ( (ispparam & NJD_POLYGONCULL_MASK) >> NJD_POLYGONCULL_SHIFT )
    {
        case 0: case 1: default: // OFF, SMALL
        {
            cull = RJ_CULL_NONE;
            break;
        }
        case 2: // ACW
        {
            cull = RJ_CULL_ACW;
            break;
        }
        case 3: // CW
        {
            cull = RJ_CULL_CW;
            break;
        }
    }

    rjSetPolygonCulling( cull );
}

void
rjSetTextureParamCtx(void)
{
    const Uint32 tspparam = _nj_curr_ctx_->tspparam;

    const RJ_TEXSHADE tsp = (tspparam & NJD_TEXSHADING_MASK) >> NJD_TEXSHADING_SHIFT;
    const Bool        ita = (tspparam & NJD_IGNORETEXALPHA_ON);

    rjSetTextureParam( tsp, ita );
}

/****** Draw ************************************************************************************/
static void
___rjStartVertex(RJ_VERTEX_TYPE vtxdecl, Sint32 use3d)
{
    _rj_vertex_buffer_base_ = (byte*) _gx_vtx_buf_base_;
    _rj_vertex_buffer_top_  = _rj_vertex_buffer_base_;

    _rj_vertex_buffer_cpy_ = NULL;

    bool tex = false;

    switch ( vtxdecl )
    {
        case RJ_VERTEX_P:
        {
            _rj_vertex_buffer_stride_ = sizeof(RJS_VERTEX_P);
            break;
        }
        case RJ_VERTEX_PT:
        {
            tex = true;

            _rj_vertex_buffer_stride_ = sizeof(RJS_VERTEX_PT);
            break;
        }
        case RJ_VERTEX_PC:
        {
            _rj_vertex_buffer_stride_ = sizeof(RJS_VERTEX_PC);
            break;
        }
        case RJ_VERTEX_PTC:
        {
            tex = true;

            _rj_vertex_buffer_stride_ = sizeof(RJS_VERTEX_PTC);
            break;
        }
        case RJ_VERTEX_PCS:
        {
            _rj_vertex_buffer_stride_ = sizeof(RJS_VERTEX_PCS);
            break;
        }
        case RJ_VERTEX_PTCS:
        {
            tex = true;

            _rj_vertex_buffer_stride_ = sizeof(RJS_VERTEX_PTCS);
            break;
        }
    }

    RJE_PIXEL effect = tex ? RJD_SHADEREFF_TEX : 0;

    if ( ShaderModelMode & SHADERMDL_FLAG_FOG )
    {
        effect |= RJD_SHADEREFF_FOG;
    }

    _rj_curr_vtx_decl_   = _rj_vtx_decls_[vtxdecl];
    _rj_curr_vtx_shader_ = _rj_vtx_shaders_[vtxdecl][use3d];
    _rj_curr_pxl_shader_ = _rj_pxl_shaders_[effect];
}

void
rjStartVertex2D(RJ_VERTEX_TYPE vtxdecl)
{
    ___rjStartVertex(vtxdecl, RJ_DRAW_2D);
}

void
rjStartVertex3D(RJ_VERTEX_TYPE vtxdecl)
{
    ___rjStartVertex(vtxdecl, RJ_DRAW_3D);
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
rjSetShaders(RFS_VSHADER* vshader, RFS_PSHADER* pshader)
{
    RF_DirectSetVShader(vshader);
    RF_DirectSetPShader(pshader);
}

void*
rjGetVertexBuffer(void)
{
    return (void*)(_rj_vertex_buffer_top_);
}

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
        const s32 i = rjCheapShadowEffectStart();

        DX9_DrawPrimitiveUP(pri_type, pri_num, _rj_vertex_buffer_base_, _rj_vertex_buffer_stride_);

        rjCheapShadowEffectEnd(i);

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

    const s32 i = rjCheapShadowEffectStart();

    DX9_DrawPrimitive(pri_type, 0, pri_num);

    rjCheapShadowEffectEnd(i);

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
        RF_DbgInfo("Modifier vertex buffer is full!");

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
rjModifierDrawBuffer(void)
{
    if ( !_rj_mod_vertex_buffer_num_ )
    {
        return;
    }

    rjSetVertexDecl( _rj_vtx_decls_[ RJ_VERTEX_M ] );
    rjSetShaders( _rj_mvtx_shader_, _rj_mpxl_shader_ );

    rjSetVertexBuffer( _rj_mod_vertex_buffer_, 0, sizeof(RJS_VERTEX_M) );

    DX9_DrawPrimitive( DX9_PRITYPE_TRIANGLELIST, 0, _rj_mod_vertex_buffer_num_ / 3 );
}

void
rjModifierResetBuffer(void)
{
    _rj_mod_vertex_buffer_num_ = 0;
}

void
rjInitModVertexBuffer(Sint32 size)
{
    ___TODO("This function is temporary, remove later");

    if ( size <= 0 )
    {
        return;
    }

    _rj_mod_vertex_buffer_max_ = (size * 4) / sizeof(RJS_VERTEX_M);

    _rj_mod_vertex_buffer_ = DX9_CreateVertexBuffer(size * 4, DX9_USAGE_DYNAMIC|DX9_USAGE_WRITEONLY, DX9_POOL_DEFAULT);
}

static bool UseShadowTex = true;

static RFS_MACRO*
InitShaderMacroVertex(RFS_MACRO* pMacroAry, const RFS_MACRO** ppOutMacro2D, const RFS_MACRO** ppOutMacro3D)
{
    int ix_base = 0;

    pMacroAry[ix_base++] = SM_VTX_3D;

    if ( UseShadowTex )
    {
        pMacroAry[ix_base++] = SM_VTX_SHTEX;
    }

    *ppOutMacro2D = &pMacroAry[1]; // exclude 3D macro
    *ppOutMacro3D = &pMacroAry[0]; // opposite ^^

    return &pMacroAry[ix_base];
}

static RFS_MACRO*
InitShaderMacroPixel(RFS_MACRO* pMacroAry, const RFS_MACRO** ppOutMacro)
{
    int ix_base = 0;

    if ( UseShadowTex )
    {
        pMacroAry[ix_base++] = SM_PXL_SHTEX;
    }

    *ppOutMacro = &pMacroAry[0];

    return &pMacroAry[ix_base];
}

void
RFCTRL_SetModBufferSize(s32 nbTri, s32 nbTriList)
{
    ___TODO("This function must be restored before release");

    //SetIfGreater(ModBufferInitTriNum, nbTri);
}

/****** Init ************************************************************************/
void
RFD_CoreInit(void)
{
    // compile shaders
    {
        RFS_MACRO macrolist[10];

        /** Vertex Shaders **/
        {
            const RFS_MACRO* p_vmacro_2d;
            const RFS_MACRO* p_vmacro_3d;

            RFS_MACRO* p_setmacro = InitShaderMacroVertex(macrolist, &p_vmacro_2d, &p_vmacro_3d);

            // compile

            p_setmacro[0] = SM_END;

            _rj_vtx_shaders_[RJ_VERTEX_P][RJ_DRAW_2D] = RF_CompileVShader(SHADER_NAME_VS, p_vmacro_2d);
            _rj_vtx_shaders_[RJ_VERTEX_P][RJ_DRAW_3D] = RF_CompileVShader(SHADER_NAME_VS, p_vmacro_3d);

            p_setmacro[0] = SM_VTX_COL;
            p_setmacro[1] = SM_END;

            _rj_vtx_shaders_[RJ_VERTEX_PC][RJ_DRAW_2D] = RF_CompileVShader(SHADER_NAME_VS, p_vmacro_2d);
            _rj_vtx_shaders_[RJ_VERTEX_PC][RJ_DRAW_3D] = RF_CompileVShader(SHADER_NAME_VS, p_vmacro_3d);

            p_setmacro[0] = SM_VTX_COL;
            p_setmacro[1] = SM_VTX_OFF;
            p_setmacro[2] = SM_END;

            _rj_vtx_shaders_[RJ_VERTEX_PCS][RJ_DRAW_2D] = RF_CompileVShader(SHADER_NAME_VS, p_vmacro_2d);
            _rj_vtx_shaders_[RJ_VERTEX_PCS][RJ_DRAW_3D] = RF_CompileVShader(SHADER_NAME_VS, p_vmacro_3d);

            p_setmacro[0] = SM_VTX_TEX;
            p_setmacro[1] = SM_VTX_COL;
            p_setmacro[2] = SM_END;

            _rj_vtx_shaders_[RJ_VERTEX_PTC][RJ_DRAW_2D] = RF_CompileVShader(SHADER_NAME_VS, p_vmacro_2d);
            _rj_vtx_shaders_[RJ_VERTEX_PTC][RJ_DRAW_3D] = RF_CompileVShader(SHADER_NAME_VS, p_vmacro_3d);

            p_setmacro[0] = SM_VTX_TEX;
            p_setmacro[1] = SM_VTX_COL;
            p_setmacro[2] = SM_VTX_OFF;
            p_setmacro[3] = SM_END;

            _rj_vtx_shaders_[RJ_VERTEX_PTCS][RJ_DRAW_2D] = RF_CompileVShader(SHADER_NAME_VS, p_vmacro_2d);
            _rj_vtx_shaders_[RJ_VERTEX_PTCS][RJ_DRAW_3D] = RF_CompileVShader(SHADER_NAME_VS, p_vmacro_3d);
        }

        /** Pixel Shaders **/
        {
            const RFS_MACRO* p_pmacro;

            RFS_MACRO* p_setmacro = InitShaderMacroPixel(macrolist, &p_pmacro);

            // compile

            p_setmacro[0] = SM_END;

            _rj_pxl_shaders_[RJE_PIXEL_N]  = RF_CompilePShader(SHADER_NAME_PS, p_pmacro);

            p_setmacro[0] = SM_PXL_TEX;
            p_setmacro[1] = SM_END;

            _rj_pxl_shaders_[RJE_PIXEL_T]  = RF_CompilePShader(SHADER_NAME_PS, p_pmacro);

            p_setmacro[0] = SM_PXL_FOG;
            p_setmacro[1] = SM_END;

            _rj_pxl_shaders_[RJE_PIXEL_F]  = RF_CompilePShader(SHADER_NAME_PS, p_pmacro);

            p_setmacro[0] = SM_PXL_TEX;
            p_setmacro[1] = SM_PXL_FOG;
            p_setmacro[2] = SM_END;

            _rj_pxl_shaders_[RJE_PIXEL_TF]  = RF_CompilePShader(SHADER_NAME_PS, p_pmacro);
        }

        /** Modifier Shaders **/

        _rj_mvtx_shader_ = RF_CompileVShader(SHADER_NAME_MODVS, nullptr);
        _rj_mpxl_shader_ = RF_CompilePShader(SHADER_NAME_MODPS, nullptr);
    }

    /** Vertex Buffers **/

    rjInitModVertexBuffer(0x8000);

    _rj_vertex_buffer_ = DX9_CreateVertexBuffer(RJD_VBUF_SIZE, DX9_USAGE_DYNAMIC|DX9_USAGE_WRITEONLY, DX9_POOL_DEFAULT);

    /** Vertex Declarations **/

    dx9_vtx_elem vtx_elems[5];

    // position

    vtx_elems[0] = (dx9_vtx_elem){ 0, 0 , DX9_VTXTYPE_FLOAT3, DX9_VTXMETH_DEFAULT, DX9_VTXUSE_POSITION, 0 };
    vtx_elems[1] = (dx9_vtx_elem)DX9_VTX_ELEM_END();
    vtx_elems[2] = vtx_elems[1];
    vtx_elems[3] = vtx_elems[1];
    vtx_elems[4] = vtx_elems[1];

    _rj_vtx_decls_[RJ_VERTEX_P] = DX9_CreateVtxDecl(vtx_elems);

    // pos + color

//  vtx_elems[0] = (dx9_vtx_elem){ 0, 0 , DX9_VTXTYPE_FLOAT3, DX9_VTXMETH_DEFAULT, DX9_VTXUSE_POSITION, 0 };
    vtx_elems[1] = (dx9_vtx_elem){ 0, 12, DX9_VTXTYPE_COLOR , DX9_VTXMETH_DEFAULT, DX9_VTXUSE_COLOR   , 0 };

    _rj_vtx_decls_[RJ_VERTEX_PC] = DX9_CreateVtxDecl(vtx_elems);

    // pos + color + specular

//  vtx_elems[0] = (dx9_vtx_elem){ 0, 0 , DX9_VTXTYPE_FLOAT3, DX9_VTXMETH_DEFAULT, DX9_VTXUSE_POSITION, 0 };
//  vtx_elems[1] = (dx9_vtx_elem){ 0, 12, DX9_VTXTYPE_COLOR , DX9_VTXMETH_DEFAULT, DX9_VTXUSE_COLOR   , 0 };
    vtx_elems[2] = (dx9_vtx_elem){ 0, 16, DX9_VTXTYPE_COLOR , DX9_VTXMETH_DEFAULT, DX9_VTXUSE_COLOR   , 1 };

    _rj_vtx_decls_[RJ_VERTEX_PCS] = DX9_CreateVtxDecl(vtx_elems);

    vtx_elems[2] = (dx9_vtx_elem)DX9_VTX_ELEM_END();

    // pos + texture (uv)

//  vtx_elems[0] = (dx9_vtx_elem){ 0, 0 , DX9_VTXTYPE_FLOAT3, DX9_VTXMETH_DEFAULT, DX9_VTXUSE_POSITION, 0 };
    vtx_elems[1] = (dx9_vtx_elem){ 0, 12, DX9_VTXTYPE_FLOAT2, DX9_VTXMETH_DEFAULT, DX9_VTXUSE_TEXCOORD, 0 };

    _rj_vtx_decls_[RJ_VERTEX_PT] = DX9_CreateVtxDecl(vtx_elems);

    // pos + tex + color

//  vtx_elems[0] = (dx9_vtx_elem){ 0, 0 , DX9_VTXTYPE_FLOAT3, DX9_VTXMETH_DEFAULT, DX9_VTXUSE_POSITION, 0 };
//  vtx_elems[1] = (dx9_vtx_elem){ 0, 12, DX9_VTXTYPE_FLOAT2, DX9_VTXMETH_DEFAULT, DX9_VTXUSE_TEXCOORD, 0 };
    vtx_elems[2] = (dx9_vtx_elem){ 0, 20, DX9_VTXTYPE_COLOR , DX9_VTXMETH_DEFAULT, DX9_VTXUSE_COLOR   , 0 };

    _rj_vtx_decls_[RJ_VERTEX_PTC] = DX9_CreateVtxDecl(vtx_elems);

    // pos + tex + color + spec

//  vtx_elems[0] = (dx9_vtx_elem){ 0, 0 , DX9_VTXTYPE_FLOAT3, DX9_VTXMETH_DEFAULT, DX9_VTXUSE_POSITION, 0 };
//  vtx_elems[1] = (dx9_vtx_elem){ 0, 12, DX9_VTXTYPE_FLOAT2, DX9_VTXMETH_DEFAULT, DX9_VTXUSE_TEXCOORD, 0 };
//  vtx_elems[2] = (dx9_vtx_elem){ 0, 20, DX9_VTXTYPE_COLOR , DX9_VTXMETH_DEFAULT, DX9_VTXUSE_COLOR   , 0 };
    vtx_elems[3] = (dx9_vtx_elem){ 0, 24, DX9_VTXTYPE_COLOR , DX9_VTXMETH_DEFAULT, DX9_VTXUSE_COLOR   , 1 };

    _rj_vtx_decls_[RJ_VERTEX_PTCS] = DX9_CreateVtxDecl(vtx_elems);
}
