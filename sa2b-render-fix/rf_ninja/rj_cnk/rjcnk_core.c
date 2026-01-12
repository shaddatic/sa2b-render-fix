/********************************/
/*  Includes                    */
/********************************/
/****** Core Toolkit ****************************************************************************/
#include <samt/core.h>              /* core                                                     */

/****** Ninja ***********************************************************************************/
#include <samt/ninja/ninja.h>       /* ninja                                                    */

/****** Render Fix ******************************************************************************/
#include <rf_core.h>                /* core                                                     */
#include <rf_renderstate.h>         /* render state                                             */
#include <rf_shader.h>              /* shader constants                                         */

/****** Self ************************************************************************************/
#include <rf_ninja/rj_cnk/rjcnk_internal.h> /* parent & siblings                                */

/********************************/
/*  Extern Data                 */
/********************************/
/****** Self ************************************************************************************/
RJS_CNK_CTX _rj_cnk_context_;

NJS_BGRA _rj_cnk_default_material_[RJ_NB_CMC] =
{
    { 178, 178, 178, 255 }, // diffuse  : BGRA
    { 127, 127, 127, 255 }, // ambient  : BGR#
    { 255, 255, 255, 11  }, // specular : BGRE
};

NJS_ARGB    _rj_cnk_diff_material_; /* diffuse material                                         */
NJS_ARGB    _rj_cnk_ambi_material_; /* ambient material                             (a == noop) */
NJS_ARGB    _rj_cnk_spec_material_; /* specular material                        (a == exponent) */

Sint32      _rj_cnk_shadow_tex_;

Float _rj_cnk_inten_multiply_ = 1.f;

RJF_CNK_VCOLFUNC* _rj_cnk_vcol_funcs_[NB_RJE_CNK_VCOLFUNC] =
{
    [RJE_CNK_VCOLFUNC_MATERIAL] = rjCnkVertexColorMaterial,
    [RJE_CNK_VCOLFUNC_D8]       = rjCnkVertexColorD8,
    [RJE_CNK_VCOLFUNC_LIGHT]    = rjCnkVertexColorLights,
    [RJE_CNK_VCOLFUNC_LIGHTD8]  = rjCnkVertexColorLightsD8,
};

RJF_CNK_SPECFUNC* _rj_cnk_spec_funcs_[NB_RJE_CNK_SPECFUNC] =
{
    [RJE_CNK_SPECFUNC_NONE]   = rjCnkSpecularNone,
    [RJE_CNK_SPECFUNC_NORMAL] = rjCnkSpecularNormal,
    [RJE_CNK_SPECFUNC_EASY]   = rjCnkSpecularEasy,
    [RJE_CNK_SPECFUNC_SIMPLE] = rjCnkSpecularSimple,
    [RJE_CNK_SPECFUNC_MULTI]  = rjCnkSpecularMulti,
    [RJE_CNK_SPECFUNC_S8]     = rjCnkSpecularS8,
};

/********************************/
/*  Source                      */
/********************************/
/****** Specular ********************************************************************************/
static Sint32
___rjCnkGetAutoSpecMode(void)
{
    switch ( _rj_cnk_context_.func )
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

/****** Chunk Polygon ***************************************************************************/
void
rjCnkInvertLightDirection(Bool sw)
{
    _rj_cnk_inten_multiply_ = sw ? -1.f : 1.f;
}

/****** Get UV Scroll ***************************************************************************/
RJS_UV
rjCnkGetUvScroll(void)
{
    return _rj_cnk_uv_scroll_;
}

RJS_UV
rjCnkGetEnvUvScroll(void)
{
    return (_nj_control_3d_flag_ & NJD_CONTROL_3D_ENV_UV_SCROLL) ? _rj_cnk_env_scroll_ : (RJS_UV){0};
}

/****** Culling *********************************************************************************/
void
rjCnkPolygonCulling(RJ_CULL cullmd)
{
    if ( _rj_cnk_context_.cull == cullmd )
    {
        return;
    }

    rjSetHwCulling(cullmd);

    _rj_cnk_context_.cull = cullmd;
}

/****** Start/End Vertex ************************************************************************/
void
rjCnkStartVertexNonTex(void)
{
    rjStartVertex3D(RJ_VERTEX_PCO); // pos,col,spec

    /** Magic: Shadow Tex **/
    const f32 smf = _rj_cnk_shadow_tex_ ? (f32)_rj_cnk_shadow_tex_ : 0.f;

    RF_ShaderSetConstantF4(RF_SCFV_NUMTEXGENS, smf, 0.f, 0.f, 0.f);
}

void
rjCnkStartVertexTex(void)
{
    if ( _rj_cnk_ctrl_flag_ & RJD_CNK_CTRL_TEXTURE )
    {
        rjSetPolyAttrMask( ON, ON, ON, ON );
    }
    else // texture off
    {
        rjSetPolyAttrMask( ON, OFF, ON, ON );
    }

    rjStartVertex3D(RJ_VERTEX_PTCO); // pos,tex,col,spec

    /** Magic: Shadow Tex **/
    const f32 smf = _rj_cnk_shadow_tex_ ? (f32)_rj_cnk_shadow_tex_ : 1.f;

    RF_ShaderSetConstantF4(RF_SCFV_NUMTEXGENS, smf, 0.f, 0.f, 0.f);
}

void
rjCnkEndVertex(void)
{
    rjEndVertex();
}

/****** Begin/End Draw **************************************************************************/
void
rjCnkStartPlist(RJS_CNK_STRIP* restrict basest)
{
    // set default strip materials
    basest->mats[RJ_CMC_DIFF] = _rj_cnk_default_material_[RJ_CMC_DIFF];
    basest->mats[RJ_CMC_AMBI] = _rj_cnk_default_material_[RJ_CMC_AMBI];
    basest->mats[RJ_CMC_SPEC] = _rj_cnk_default_material_[RJ_CMC_SPEC];

    // set context control flags
    {
        const RFRS_CNKFUNCMD funcmd = _rj_cnk_context_.func;
        const bool           all_on = (funcmd == RFRS_CNKFUNCMD_NORMAL);

        Uint32 new_flag = 0;

        if ( all_on || (funcmd & RFRS_CNKFUNCMD_SIMPLEBIT) )
        {
            new_flag |= RJD_CXF_BACKFACECULL;
            
            if ( _rj_cnk_ctrl_flag_ & RJD_CNK_CTRL_DBLIGHT )
            {
                new_flag |= RJD_CXF_TWOPASSLIGHT;
            }
        }

        if ( all_on || (funcmd & RFRS_CNKFUNCMD_MULTIBIT) )
        {
            new_flag |= (RJD_CXF_AMBIMATERIAL|RJD_CXF_VND8);
        }

        if ( all_on ) 
        {
            new_flag |= RJD_CXF_NONTEXSPEC;
        }

        _rj_cnk_context_.flag = new_flag;
    }

    _rj_cnk_context_.cull  = -1;
    _rj_cnk_context_.texid = -1;
    _rj_cnk_context_.tiny  = (CNK_TINY_HEAD){ 0 };

    switch ( RFRS_GetCnkSpecMode() ) 
    {
        case RFRS_CNKSPECMD_NONE:
        {
            _rj_cnk_context_.spec = RJE_CNK_SPECFUNC_NONE;
            break;
        }
        case RFRS_CNKSPECMD_AUTO:
        {
            _rj_cnk_context_.spec = ___rjCnkGetAutoSpecMode();
            break;
        }
        case RFRS_CNKSPECMD_NORMAL:
        {
            _rj_cnk_context_.spec = RJE_CNK_SPECFUNC_NORMAL;
            break;
        }
        case RFRS_CNKSPECMD_EASY:
        {
            _rj_cnk_context_.spec = RJE_CNK_SPECFUNC_EASY;
            break;
        }
        case RFRS_CNKSPECMD_SIMPLE:
        {
            _rj_cnk_context_.spec = RJE_CNK_SPECFUNC_SIMPLE;
            break;
        }
        case RFRS_CNKSPECMD_MULTI:
        {
            _rj_cnk_context_.spec = RJE_CNK_SPECFUNC_MULTI;
            break;
        }
    }
}

void
rjCnkEndPlist(void)
{
    rjSetHwPolygonShading( RJ_SHADE_GOURAUD );
    rjSetHwCulling( RJ_CULL_NONE );
    rjInvertPolygons( OFF );

    rjSetPolyAttrMask( ON, ON, ON, ON );
}
