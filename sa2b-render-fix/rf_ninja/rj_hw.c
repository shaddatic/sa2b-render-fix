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
#include <rf_shader.h>              /* shader                                                   */
#include <rf_magic.h>               /* magiccache                                               */
#include <rf_graphics.h>            /* graphics                                                 */

/****** SOC *************************************************************************************/
#include <samt/soc/shader.h>        /* setshader                                                */

/****** Self ************************************************************************************/
#include <rf_ninja/rj_internal.h>           /* parent & siblings                                */
#include <rf_ninja/rj_cnk/rjcnk_internal.h> /* self                                             */

/********************************/
/*  Static Asserts              */
/********************************/
/****** Hw Param ********************************************************************************/
static_assert(RJ_HW_TEXADDR_REPEAT+1 == DX9_TEXADDR_WRAP  , "RJ and DX9 texaddr enum don't line up!");
static_assert(RJ_HW_TEXADDR_FLIP+1   == DX9_TEXADDR_MIRROR, "RJ and DX9 texaddr enum don't line up!");
static_assert(RJ_HW_TEXADDR_CLAMP+1  == DX9_TEXADDR_CLAMP , "RJ and DX9 texaddr enum don't line up!");
static_assert(RJ_HW_TEXADDR_CLIP+1   == DX9_TEXADDR_BORDER, "RJ and DX9 texaddr enum don't line up!");

/********************************/
/*  Data                        */
/********************************/
/****** Hw Param ********************************************************************************/
static RJ_SHADE _rj_polygon_shading_;

/****** Shader Constants ************************************************************************/
static dx9_float4 _rj_hw_polyattr_;
static dx9_float4 _rj_hw_texparam_;

/********************************/
/*  Source                      */
/********************************/
/****** Culling *********************************************************************************/
void
rjSetHwCulling(RJ_CULL mode)
{
    GX_SetCullMode(mode);
}

void
rjSetHwTexture(Int index, const RJS_HW_TEXTURE* tex)
{
    RF_MAGICTEXTURE* p_mtex = tex->surface;

    dx9_uint magfilter, minfilter, mipfilter;

    switch ( tex->filter )
    {
        case RJ_HW_FILTER_POINTSAMPLE: default:
        {
            magfilter = DX9_TEXFILTER_POINT;
            minfilter = DX9_TEXFILTER_POINT;
            mipfilter = DX9_TEXFILTER_POINT;
            break;
        }
        case RJ_HW_FILTER_BILINEAR:
        {
            magfilter = DX9_TEXFILTER_LINEAR;
            minfilter = DX9_TEXFILTER_LINEAR;
            mipfilter = DX9_TEXFILTER_POINT;
            break;
        }
        case RJ_HW_FILTER_TRILINEAR_A: case RJ_HW_FILTER_TRILINEAR_B:
        {
            magfilter = DX9_TEXFILTER_LINEAR;
            minfilter = DX9_TEXFILTER_LINEAR;
            mipfilter = DX9_TEXFILTER_LINEAR;
            break;
        }
    }

    if ( tex->supersample )
    {
        minfilter = DX9_TEXFILTER_ANISOTROPIC;
    }

    const dx9_uint miplodbias = RFGX_GetMipmapDepthAdjust(tex->mipdadjust);

    // set texture

    RF_MAGIC_STATECACHE* p_mcache = RF_MagicGetStateCache();

    if ( p_mcache->pstexs[index] != p_mtex->texture )
    {
        DX9_SetTexture(index, p_mtex->texture);
    
        p_mcache->pstexs[index] = p_mtex->texture;
    }

    RFGX_SetSamplerState(index, DX9_SAMPLER_ADDRESSU     , tex->uaddr + 1);
    RFGX_SetSamplerState(index, DX9_SAMPLER_ADDRESSV     , tex->vaddr + 1);
    RFGX_SetSamplerState(index, DX9_SAMPLER_ADDRESSW     , DX9_TEXADDR_CLAMP);
    RFGX_SetSamplerState(index, DX9_SAMPLER_BORDERCOLOR  , 0x00000000);
    RFGX_SetSamplerState(index, DX9_SAMPLER_MAGFILTER    , magfilter);
    RFGX_SetSamplerState(index, DX9_SAMPLER_MINFILTER    , minfilter);
    RFGX_SetSamplerState(index, DX9_SAMPLER_MIPFILTER    , mipfilter);
    RFGX_SetSamplerState(index, DX9_SAMPLER_MIPMAPLODBIAS, miplodbias);
    RFGX_SetSamplerState(index, DX9_SAMPLER_MAXANISOTROPY, 4);
}

/****** Polygon Attr ****************************************************************************/
void
rjSetHwPolygonAttr(Int nrm, Int tex, Int col, Int off)
{
    const dx9_float4 attr = (dx9_float4){ (f32)nrm, (f32)tex, (f32)col, (f32)off };

    if ( _rj_hw_polyattr_.x != attr.x
    ||   _rj_hw_polyattr_.y != attr.y
    ||   _rj_hw_polyattr_.z != attr.z
    ||   _rj_hw_polyattr_.w != attr.w )
    {
        _rj_hw_polyattr_ = attr;

        RF_ShaderSetConstantF(RF_SCFV_POLYATTR, &attr, 1);
        RF_ShaderSetConstantF(RF_SCFP_POLYATTR, &attr, 1);
    }
}

/****** Color ***********************************************************************************/
void
rjSetHwColor(Float a, Float r, Float g, Float b)
{
    if ( _nj_control_3d_flag_ & NJD_CONTROL_3D_CONSTANT_TEXTURE_MATERIAL )
    {
        RF_ShaderSetConstantF4(RF_SCFV_MATERIALREG_0, 1.f, 1.f, 1.f, a);
    }
    else
    {
        RF_ShaderSetConstantF4(RF_SCFV_MATERIALREG_0, r, g, b, a);
    }
}

void
rjSetHwColorEx(const NJS_ARGB* p)
{
    rjSetHwColor( p->a, p->r, p->g, p->b );
}

/****** Shading *********************************************************************************/
void
rjSetHwPolygonShading(RJ_SHADE mode)
{
    if ( _rj_polygon_shading_ != mode )
    {
        _rj_polygon_shading_ = mode;

        DX9_SetShadingMode( mode == RJ_SHADE_FLAT ? DX9_SHADE_FLAT : DX9_SHADE_GOURAUD );
    }
}

void
rjSetHwTextureParam(RJ_TEXSHADE shademd, Bool igntexalpha)
{
    const Float tsm = (Float) shademd;
    const Float ita = igntexalpha ? 1.f : 0.f;

    if ( _rj_hw_texparam_.x != tsm || _rj_hw_texparam_.y != ita )
    {
        _rj_hw_texparam_.x = tsm;
        _rj_hw_texparam_.y = ita;

        RF_ShaderSetConstantF(RF_SCFP_TEXPARAM, &_rj_hw_texparam_, 1);
    }
}

/****** Init ************************************************************************************/
void
RJ_HwInit(void)
{
    
}
