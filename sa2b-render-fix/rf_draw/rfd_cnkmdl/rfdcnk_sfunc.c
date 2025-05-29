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
SpecToUint(const NJS_ARGB* pArgb)
{
    NJS_COLOR col;

    col.argb.a = 0x00;
    col.argb.r = (Uint8)(CLAMP(pArgb->r, 0.f, 1.f) * 255.f);
    col.argb.g = (Uint8)(CLAMP(pArgb->g, 0.f, 1.f) * 255.f);
    col.argb.b = (Uint8)(CLAMP(pArgb->b, 0.f, 1.f) * 255.f);

    return col.color;
}

static Uint32
IntenToUint(const Float inten)
{
    NJS_COLOR col;

    const f32 inten_c = CLAMP(inten, 0.f, 1.f);

    col.argb.a = 0x00;
    col.argb.r = (Uint8)((_rj_cnk_spec_material_.r * inten_c) * 255.f);
    col.argb.g = (Uint8)((_rj_cnk_spec_material_.g * inten_c) * 255.f);
    col.argb.b = (Uint8)((_rj_cnk_spec_material_.b * inten_c) * 255.f);

    return col.color;
}

/****** Specular ********************************************************************/
Uint32
rjCnkSpecularS8(const CNK_VERTEX_BUFFER* restrict pVtx)
{
    return SpecToUint( &pVtx->spc );
}

Uint32
rjCnkSpecularNone(const CNK_VERTEX_BUFFER* restrict pVtx)
{
    return 0x00000000;
}

Uint32
rjCnkSpecularNormal(const CNK_VERTEX_BUFFER* restrict pVtx)
{
    /** Get constants **/

    const Float inten_mul = _rj_cnk_inten_multiply_;

    const Float exp = _rj_cnk_spec_material_.a;

    const u32 lightsw = _rj_cnk_light_switch_;

    /** Start **/

    NJS_ARGB argb = {0};

    if ( lightsw & RJD_CNK_LIGHTSW_1 )
    {
        const Float inten = fmaxf(pVtx->inten[0] * inten_mul, 0.f);

        const Float spec = njPow(inten, exp);

        argb.r += spec * _rj_cnk_light_[0].r;
        argb.g += spec * _rj_cnk_light_[0].g;
        argb.b += spec * _rj_cnk_light_[0].b;
    }

    if ( lightsw & RJD_CNK_LIGHTSW_2 )
    {
        const Float inten = fmaxf(pVtx->inten[1] * inten_mul, 0.f);

        const Float spec = njPow(inten, exp);

        argb.r += spec * _rj_cnk_light_[1].r;
        argb.g += spec * _rj_cnk_light_[1].g;
        argb.b += spec * _rj_cnk_light_[1].b;
    }

    if ( lightsw & RJD_CNK_LIGHTSW_3 )
    {
        const Float inten = fmaxf(pVtx->inten[2] * inten_mul, 0.f);

        const Float spec = njPow(inten, exp);

        argb.r += spec * _rj_cnk_light_[2].r;
        argb.g += spec * _rj_cnk_light_[2].g;
        argb.b += spec * _rj_cnk_light_[2].b;
    }

    if ( lightsw & RJD_CNK_LIGHTSW_4 )
    {
        const Float inten = fmaxf(pVtx->inten[3] * inten_mul, 0.f);

        const Float spec = njPow(inten, exp);

        argb.r += spec * _rj_cnk_light_[3].r;
        argb.g += spec * _rj_cnk_light_[3].g;
        argb.b += spec * _rj_cnk_light_[3].b;
    }

    if ( lightsw & RJD_CNK_LIGHTSW_5 )
    {
        const Float inten = fmaxf(pVtx->inten[4] * inten_mul, 0.f);

        const Float spec = njPow(inten, exp);

        argb.r += spec * _rj_cnk_light_[4].r;
        argb.g += spec * _rj_cnk_light_[4].g;
        argb.b += spec * _rj_cnk_light_[4].b;
    }

    if ( lightsw & RJD_CNK_LIGHTSW_6 )
    {
        const Float inten = fmaxf(pVtx->inten[5] * inten_mul, 0.f);

        const Float spec = njPow(inten, exp);

        argb.r += spec * _rj_cnk_light_[5].r;
        argb.g += spec * _rj_cnk_light_[5].g;
        argb.b += spec * _rj_cnk_light_[5].b;
    }

    argb.r *= _rj_cnk_spec_material_.r;
    argb.g *= _rj_cnk_spec_material_.g;
    argb.b *= _rj_cnk_spec_material_.b;

    return SpecToUint(&argb);
}

Uint32
rjCnkSpecularEasy(const CNK_VERTEX_BUFFER* restrict pVtx)
{
    /** Get constants **/

    const Float inten_mul = _rj_cnk_inten_multiply_;

    const Float ambi = _rj_cnk_light_ambient_.inten;

    const u32 lightsw = _rj_cnk_light_switch_;

    /** Start **/

    Float spec = 0.f;

    if ( lightsw & RJD_CNK_LIGHTSW_1 )
    {
        const Float inten = fmaxf(pVtx->inten[0] * inten_mul, 0.f);

        spec += (ambi + inten) - 1.f;
    }

    if ( lightsw & RJD_CNK_LIGHTSW_2 )
    {
        const Float inten = fmaxf(pVtx->inten[1] * inten_mul, 0.f);

        spec += (ambi + inten) - 1.f;
    }

    if ( lightsw & RJD_CNK_LIGHTSW_3 )
    {
        const Float inten = fmaxf(pVtx->inten[2] * inten_mul, 0.f);

        spec += (ambi + inten) - 1.f;
    }

    if ( lightsw & RJD_CNK_LIGHTSW_4 )
    {
        const Float inten = fmaxf(pVtx->inten[3] * inten_mul, 0.f);

        spec += (ambi + inten) - 1.f;
    }

    if ( lightsw & RJD_CNK_LIGHTSW_5 )
    {
        const Float inten = fmaxf(pVtx->inten[4] * inten_mul, 0.f);

        spec += (ambi + inten) - 1.f;
    }

    if ( lightsw & RJD_CNK_LIGHTSW_6 )
    {
        const Float inten = fmaxf(pVtx->inten[5] * inten_mul, 0.f);

        spec += (ambi + inten) - 1.f;
    }

    return IntenToUint(spec);
}

Uint32
rjCnkSpecularSimple(const CNK_VERTEX_BUFFER* restrict pVtx)
{
    /** Get constants **/

    const Float inten_mul = _rj_cnk_inten_multiply_;

    const u32 lightsw = _rj_cnk_light_switch_;

    /** Start **/

    Float spec = 0.f;

    if ( lightsw & RJD_CNK_LIGHTSW_1 )
    {
        const Float inten = fmaxf(pVtx->inten[0] * inten_mul, 0.f);

        spec += njPow(inten, 17.f);
    }

    if ( lightsw & RJD_CNK_LIGHTSW_2 )
    {
        const Float inten = fmaxf(pVtx->inten[1] * inten_mul, 0.f);

        spec += njPow(inten, 17.f);
    }

    if ( lightsw & RJD_CNK_LIGHTSW_3 )
    {
        const Float inten = fmaxf(pVtx->inten[2] * inten_mul, 0.f);

        spec += njPow(inten, 17.f);
    }

    if ( lightsw & RJD_CNK_LIGHTSW_4 )
    {
        const Float inten = fmaxf(pVtx->inten[3] * inten_mul, 0.f);

        spec += njPow(inten, 17.f);
    }

    if ( lightsw & RJD_CNK_LIGHTSW_5 )
    {
        const Float inten = fmaxf(pVtx->inten[4] * inten_mul, 0.f);

        spec += njPow(inten, 17.f);
    }

    if ( lightsw & RJD_CNK_LIGHTSW_6 )
    {
        const Float inten = fmaxf(pVtx->inten[5] * inten_mul, 0.f);

        spec += njPow(inten, 17.f);
    }

    return IntenToUint(spec);
}

#include <stdio.h>

Uint32
rjCnkSpecularMulti(const CNK_VERTEX_BUFFER* restrict pVtx)
{
    /** Get constants **/

    const Float inten_mul = _rj_cnk_inten_multiply_;

    const u32 lightsw = _rj_cnk_light_switch_;

    /** Start **/

    NJS_ARGB argb = { 0.f, _rj_cnk_ambi_material_.r, _rj_cnk_ambi_material_.g, _rj_cnk_ambi_material_.b };

    if ( lightsw & RJD_CNK_LIGHTSW_1 )
    {
        const Float inten = fmaxf(pVtx->inten[0] * inten_mul, 0.f);

        argb.r += _rj_cnk_light_[0].r * inten;
        argb.g += _rj_cnk_light_[0].g * inten;
        argb.b += _rj_cnk_light_[0].b * inten;
    }

    if ( lightsw & RJD_CNK_LIGHTSW_2 )
    {
        const Float inten = fmaxf(pVtx->inten[1] * inten_mul, 0.f);

        argb.r += _rj_cnk_light_[1].r * inten;
        argb.g += _rj_cnk_light_[1].g * inten;
        argb.b += _rj_cnk_light_[1].b * inten;
    }

    if ( lightsw & RJD_CNK_LIGHTSW_3 )
    {
        const Float inten = fmaxf(pVtx->inten[2] * inten_mul, 0.f);

        argb.r += _rj_cnk_light_[2].r * inten;
        argb.g += _rj_cnk_light_[2].g * inten;
        argb.b += _rj_cnk_light_[2].b * inten;
    }

    if ( lightsw & RJD_CNK_LIGHTSW_4 )
    {
        const Float inten = fmaxf(pVtx->inten[3] * inten_mul, 0.f);

        argb.r += _rj_cnk_light_[3].r * inten;
        argb.g += _rj_cnk_light_[3].g * inten;
        argb.b += _rj_cnk_light_[3].b * inten;
    }

    if ( lightsw & RJD_CNK_LIGHTSW_5 )
    {
        const Float inten = fmaxf(pVtx->inten[4] * inten_mul, 0.f);

        argb.r += _rj_cnk_light_[4].r * inten;
        argb.g += _rj_cnk_light_[4].g * inten;
        argb.b += _rj_cnk_light_[4].b * inten;
    }

    if ( lightsw & RJD_CNK_LIGHTSW_5 )
    {
        const Float inten = fmaxf(pVtx->inten[5] * inten_mul, 0.f);

        argb.r += _rj_cnk_light_[5].r * inten;
        argb.g += _rj_cnk_light_[5].g * inten;
        argb.b += _rj_cnk_light_[5].b * inten;
    }

    argb.r -= 1.f;
    argb.g -= 1.f;
    argb.b -= 1.f;

    return SpecToUint(&argb);
}
