/************************/
/*  Includes            */
/************************/
/****** Core Toolkit ****************************************************************/
#include <samt/core.h>      /* core                                                 */

/****** Ninja ***********************************************************************/
#include <samt/ninja/ninja.h> /* ninja                                              */

/****** Render Fix ******************************************************************/
#include <rf_core.h>        /* core                                                 */
#include <rf_light.h>       /* lights                                               */

/****** Self ************************************************************************/
#include <rf_draw/rfd_cnkmdl/rfdcnk_internal.h> /* parent & siblings                */

/************************/
/*  Source              */
/************************/
/****** Static **********************************************************************/
static Uint32
ArgbToUint(const NJS_ARGB* pArgb)
{
    NJS_COLOR col;

    col.argb.a = (u8)(CLAMP(pArgb->a, 0.f, 1.f) * 255.f);
    col.argb.r = (u8)(CLAMP(pArgb->r, 0.f, 1.f) * 255.f);
    col.argb.g = (u8)(CLAMP(pArgb->g, 0.f, 1.f) * 255.f);
    col.argb.b = (u8)(CLAMP(pArgb->b, 0.f, 1.f) * 255.f);

    return col.color;
}

static Uint32
ArgbToUintEx(const NJS_ARGB* pArgb)
{
    NJS_COLOR col;

    col.argb.a = (u8)(pArgb->a * 255.f);
    col.argb.r = (u8)(pArgb->r * 255.f);
    col.argb.g = (u8)(pArgb->g * 255.f);
    col.argb.b = (u8)(pArgb->b * 255.f);

    return col.color;
}

/****** Vertex Color ****************************************************************/
Uint32
rjCnkVertexColorMaterial(const CNK_VERTEX_BUFFER* restrict pVtx)
{
    return ArgbToUintEx( &_rj_cnk_diff_material_ );
}

Uint32
rjCnkVertexColorD8(const CNK_VERTEX_BUFFER* restrict pVtx)
{
    return ArgbToUint( &pVtx->col );
}

Uint32
rjCnkVertexColorLights(const CNK_VERTEX_BUFFER* restrict pVtx)
{
    /** Get constants **/

    const Float inten_mul = _rj_cnk_inten_multiply_;

    const u32 lightsw = _rj_cnk_light_switch_;

    /** Start **/

    NJS_ARGB argb = { _rj_cnk_diff_material_.a, _rj_cnk_ambi_material_.r, _rj_cnk_ambi_material_.g, _rj_cnk_ambi_material_.b };

    if ( lightsw & RJD_CNK_LIGHTSW_1 )
    {
        const Float inten = fmaxf(pVtx->inten[0] * inten_mul, 0.f);

        argb.r += (_rj_cnk_light_[0].r * inten);
        argb.g += (_rj_cnk_light_[0].g * inten);
        argb.b += (_rj_cnk_light_[0].b * inten);
    }

    if ( lightsw & RJD_CNK_LIGHTSW_2 )
    {
        const Float inten = fmaxf(pVtx->inten[1] * inten_mul, 0.f);

        argb.r += (_rj_cnk_light_[1].r * inten);
        argb.g += (_rj_cnk_light_[1].g * inten);
        argb.b += (_rj_cnk_light_[1].b * inten);
    }

    if ( lightsw & RJD_CNK_LIGHTSW_3 )
    {
        const Float inten = fmaxf(pVtx->inten[2] * inten_mul, 0.f);

        argb.r += (_rj_cnk_light_[2].r * inten);
        argb.g += (_rj_cnk_light_[2].g * inten);
        argb.b += (_rj_cnk_light_[2].b * inten);
    }

    if ( lightsw & RJD_CNK_LIGHTSW_4 )
    {
        const Float inten = fmaxf(pVtx->inten[3] * inten_mul, 0.f);

        argb.r += (_rj_cnk_light_[3].r * inten);
        argb.g += (_rj_cnk_light_[3].g * inten);
        argb.b += (_rj_cnk_light_[3].b * inten);
    }

    if ( lightsw & RJD_CNK_LIGHTSW_5 )
    {
        const Float inten = fmaxf(pVtx->inten[4] * inten_mul, 0.f);

        argb.r += (_rj_cnk_light_[4].r * inten);
        argb.g += (_rj_cnk_light_[4].g * inten);
        argb.b += (_rj_cnk_light_[4].b * inten);
    }

    if ( lightsw & RJD_CNK_LIGHTSW_6 )
    {
        const Float inten = fmaxf(pVtx->inten[5] * inten_mul, 0.f);

        argb.r += (_rj_cnk_light_[5].r * inten);
        argb.g += (_rj_cnk_light_[5].g * inten);
        argb.b += (_rj_cnk_light_[5].b * inten);
    }

    argb.r *= _rj_cnk_diff_material_.r;
    argb.g *= _rj_cnk_diff_material_.g;
    argb.b *= _rj_cnk_diff_material_.b;

    return ArgbToUint(&argb);
}

Uint32
rjCnkVertexColorLightsD8(const CNK_VERTEX_BUFFER* restrict pVtx)
{
    /** Get constants **/

    const Float inten_mul = _rj_cnk_inten_multiply_;

    const u32 lightsw = _rj_cnk_light_switch_;

    /** Start **/

    NJS_ARGB argb = { _rj_cnk_diff_material_.a, _rj_cnk_ambi_material_.r, _rj_cnk_ambi_material_.g, _rj_cnk_ambi_material_.b };

    if ( lightsw & RJD_CNK_LIGHTSW_1 )
    {
        const Float inten = fmaxf(pVtx->inten[0] * inten_mul, 0.f);

        argb.r += (_rj_cnk_light_[0].r * inten);
        argb.g += (_rj_cnk_light_[0].g * inten);
        argb.b += (_rj_cnk_light_[0].b * inten);
    }

    if ( lightsw & RJD_CNK_LIGHTSW_2 )
    {
        const Float inten = fmaxf(pVtx->inten[1] * inten_mul, 0.f);

        argb.r += (_rj_cnk_light_[1].r * inten);
        argb.g += (_rj_cnk_light_[1].g * inten);
        argb.b += (_rj_cnk_light_[1].b * inten);
    }

    if ( lightsw & RJD_CNK_LIGHTSW_3 )
    {
        const Float inten = fmaxf(pVtx->inten[2] * inten_mul, 0.f);

        argb.r += (_rj_cnk_light_[2].r * inten);
        argb.g += (_rj_cnk_light_[2].g * inten);
        argb.b += (_rj_cnk_light_[2].b * inten);
    }

    if ( lightsw & RJD_CNK_LIGHTSW_4 )
    {
        const Float inten = fmaxf(pVtx->inten[3] * inten_mul, 0.f);

        argb.r += (_rj_cnk_light_[3].r * inten);
        argb.g += (_rj_cnk_light_[3].g * inten);
        argb.b += (_rj_cnk_light_[3].b * inten);
    }

    if ( lightsw & RJD_CNK_LIGHTSW_5 )
    {
        const Float inten = fmaxf(pVtx->inten[4] * inten_mul, 0.f);

        argb.r += (_rj_cnk_light_[4].r * inten);
        argb.g += (_rj_cnk_light_[4].g * inten);
        argb.b += (_rj_cnk_light_[4].b * inten);
    }

    if ( lightsw & RJD_CNK_LIGHTSW_6 )
    {
        const Float inten = fmaxf(pVtx->inten[5] * inten_mul, 0.f);

        argb.r += (_rj_cnk_light_[5].r * inten);
        argb.g += (_rj_cnk_light_[5].g * inten);
        argb.b += (_rj_cnk_light_[5].b * inten);
    }

    argb.a *= pVtx->col.a;
    argb.r *= pVtx->col.r * _rj_cnk_diff_material_.r;
    argb.g *= pVtx->col.g * _rj_cnk_diff_material_.g;
    argb.b *= pVtx->col.b * _rj_cnk_diff_material_.b;

    return ArgbToUint(&argb);
}
