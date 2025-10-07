/************************/
/*  Includes            */
/************************/
/****** Core Toolkit ****************************************************************************/
#include <samt/core.h>              /* core                                                     */

/****** Ninja ***********************************************************************************/
#include <samt/ninja/ninja.h>       /* ninja                                                    */

/****** Render Fix ******************************************************************************/
#include <rf_core.h>                /* core                                                     */
#include <rf_light.h>               /* lights                                                   */

/****** Self ************************************************************************************/
#include <rf_ninja/rj_cnk/rjcnk_internal.h> /* parent & siblings                                */

/********************************/
/*  Macros                      */
/********************************/
/****** Static **********************************************************************************/
#define LIGHT_ON(_flag, _ix)        ((_flag)&(RJD_CNK_LIGHTSW_1<<(_ix)))

/********************************/
/*  Source                      */
/********************************/
/****** Static **********************************************************************************/
static inline Uint32
ArgbToUint(const NJS_ARGB* pArgb)
{
    NJS_COLOR col;

    col.argb.a = (Uint8)(CLAMP(pArgb->a, 0.f, 1.f) * 255.f);
    col.argb.r = (Uint8)(CLAMP(pArgb->r, 0.f, 1.f) * 255.f);
    col.argb.g = (Uint8)(CLAMP(pArgb->g, 0.f, 1.f) * 255.f);
    col.argb.b = (Uint8)(CLAMP(pArgb->b, 0.f, 1.f) * 255.f);

    return col.color;
}

static inline Uint32
ArgbToUintEx(const NJS_ARGB* pArgb)
{
    NJS_COLOR col;

    col.argb.a = (Uint8)(pArgb->a * 255.f);
    col.argb.r = (Uint8)(pArgb->r * 255.f);
    col.argb.g = (Uint8)(pArgb->g * 255.f);
    col.argb.b = (Uint8)(pArgb->b * 255.f);

    return col.color;
}

static inline Uint32
SpecToUint(const NJS_ARGB* pArgb)
{
    NJS_COLOR col;

    col.argb.a = 0x00;
    col.argb.r = (Uint8)(CLAMP(pArgb->r, 0.f, 1.f) * 255.f);
    col.argb.g = (Uint8)(CLAMP(pArgb->g, 0.f, 1.f) * 255.f);
    col.argb.b = (Uint8)(CLAMP(pArgb->b, 0.f, 1.f) * 255.f);

    return col.color;
}

static inline Uint32
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

/****** Vertex Color ****************************************************************************/
Uint32
rjCnkVertexColorMaterial(const RJS_VERTEX_BUF* restrict pVtx)
{
    return ArgbToUintEx( &_rj_cnk_diff_material_ );
}

Uint32
rjCnkVertexColorD8(const RJS_VERTEX_BUF* restrict pVtx)
{
    return ArgbToUint( &pVtx->col );
}

Uint32
rjCnkVertexColorLights(const RJS_VERTEX_BUF* restrict pVtx)
{
    /** Get constants **/

    const Float inten_mul = _rj_cnk_inten_multiply_;

    const u32 lightsw = _rj_cnk_light_switch_;

    /** Start **/

    NJS_ARGB argb = { _rj_cnk_diff_material_.a, _rj_cnk_ambi_material_.r, _rj_cnk_ambi_material_.g, _rj_cnk_ambi_material_.b };

    for ( int i = 0; i < RJD_CNK_LIGHT_NUM; ++i )
    {
        if ( !LIGHT_ON(lightsw, i) )
        {
            continue;
        }

        const Float inten = fmaxf(pVtx->inten[i] * inten_mul, 0.f);

        argb.r += (_rj_cnk_light_[i].r * inten);
        argb.g += (_rj_cnk_light_[i].g * inten);
        argb.b += (_rj_cnk_light_[i].b * inten);
    }

    argb.r *= _rj_cnk_diff_material_.r;
    argb.g *= _rj_cnk_diff_material_.g;
    argb.b *= _rj_cnk_diff_material_.b;

    return ArgbToUint(&argb);
}

Uint32
rjCnkVertexColorLightsD8(const RJS_VERTEX_BUF* restrict pVtx)
{
    /** Get constants **/

    const Float inten_mul = _rj_cnk_inten_multiply_;

    const u32 lightsw = _rj_cnk_light_switch_;

    /** Start **/

    NJS_ARGB argb = { _rj_cnk_diff_material_.a, _rj_cnk_ambi_material_.r, _rj_cnk_ambi_material_.g, _rj_cnk_ambi_material_.b };

    for ( int i = 0; i < RJD_CNK_LIGHT_NUM; ++i )
    {
        if ( !LIGHT_ON(lightsw, i) )
        {
            continue;
        }

        const Float inten = fmaxf(pVtx->inten[i] * inten_mul, 0.f);

        argb.r += (_rj_cnk_light_[i].r * inten);
        argb.g += (_rj_cnk_light_[i].g * inten);
        argb.b += (_rj_cnk_light_[i].b * inten);
    }

    argb.a *= pVtx->col.a;
    argb.r *= pVtx->col.r * _rj_cnk_diff_material_.r;
    argb.g *= pVtx->col.g * _rj_cnk_diff_material_.g;
    argb.b *= pVtx->col.b * _rj_cnk_diff_material_.b;

    return ArgbToUint(&argb);
}

/****** Specular ********************************************************************/
Uint32
rjCnkSpecularS8(const RJS_VERTEX_BUF* restrict pVtx)
{
    return SpecToUint( &pVtx->spc );
}

Uint32
rjCnkSpecularNone(const RJS_VERTEX_BUF* restrict pVtx)
{
    return 0x00000000;
}

Uint32
rjCnkSpecularNormal(const RJS_VERTEX_BUF* restrict pVtx)
{
    /** Get constants **/

    const Float inten_mul = _rj_cnk_inten_multiply_;

    const Float exp = _rj_cnk_spec_material_.a;

    const u32 lightsw = _rj_cnk_light_switch_;

    /** Start **/

    NJS_ARGB argb = {0};

    for ( int i = 0; i < RJD_CNK_LIGHT_NUM; ++i )
    {
        if ( !LIGHT_ON(lightsw, i) )
        {
            continue;
        }

        const Float inten = fmaxf(pVtx->inten[i] * inten_mul, 0.f);

        const Float spec = njPow(inten, exp);

        argb.r += (spec * _rj_cnk_light_[i].r);
        argb.g += (spec * _rj_cnk_light_[i].g);
        argb.b += (spec * _rj_cnk_light_[i].b);
    }

    argb.r *= _rj_cnk_spec_material_.r;
    argb.g *= _rj_cnk_spec_material_.g;
    argb.b *= _rj_cnk_spec_material_.b;

    return SpecToUint(&argb);
}

Uint32
rjCnkSpecularEasy(const RJS_VERTEX_BUF* restrict pVtx)
{
    /** Get constants **/

    const Float inten_mul = _rj_cnk_inten_multiply_;

    const Float ambi = _rj_cnk_light_ambient_.inten;

    const u32 lightsw = _rj_cnk_light_switch_;

    /** Start **/

    Float spec = 0.f;

    for ( int i = 0; i < RJD_CNK_LIGHT_NUM; ++i )
    {
        if ( !LIGHT_ON(lightsw, i) )
        {
            continue;
        }

        const Float inten = fmaxf(pVtx->inten[i] * inten_mul, 0.f);

        spec += (ambi + inten);
    }

    spec -= 1.f;

    return IntenToUint(spec);
}

Uint32
rjCnkSpecularSimple(const RJS_VERTEX_BUF* restrict pVtx)
{
    /** Get constants **/

    const Float inten_mul = _rj_cnk_inten_multiply_;

    const u32 lightsw = _rj_cnk_light_switch_;

    /** Start **/

    Float spec = 0.f;

    for ( int i = 0; i < RJD_CNK_LIGHT_NUM; ++i )
    {
        if ( !LIGHT_ON(lightsw, i) )
        {
            continue;
        }

        const Float inten = fmaxf(pVtx->inten[i] * inten_mul, 0.f);

        spec += njPow(inten, 17.f);
    }

    return IntenToUint(spec);
}

Uint32
rjCnkSpecularMulti(const RJS_VERTEX_BUF* restrict pVtx)
{
    /** Get constants **/

    const Float inten_mul = _rj_cnk_inten_multiply_;

    const u32 lightsw = _rj_cnk_light_switch_;

    /** Start **/

    NJS_ARGB argb = { 0.f, _rj_cnk_ambi_material_.r, _rj_cnk_ambi_material_.g, _rj_cnk_ambi_material_.b };

    for ( int i = 0; i < RJD_CNK_LIGHT_NUM; ++i )
    {
        if ( !LIGHT_ON(lightsw, i) )
        {
            continue;
        }

        const Float inten = fmaxf(pVtx->inten[i] * inten_mul, 0.f);

        argb.r += (_rj_cnk_light_[i].r * inten);
        argb.g += (_rj_cnk_light_[i].g * inten);
        argb.b += (_rj_cnk_light_[i].b * inten);
    }

    argb.r -= 1.f;
    argb.g -= 1.f;
    argb.b -= 1.f;

    return SpecToUint(&argb);
}
