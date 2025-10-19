/********************************/
/*  Includes                    */
/********************************/
/****** Core Toolkit ****************************************************************************/
#include <samt/core.h>              /* core                                                     */
#include <samt/writeop.h>           /* WriteJump                                                */

#define SAMT_INCL_INTERNAL

/****** Ninja ***********************************************************************************/
#include <samt/ninja/ninja.h>       /* ninja                                                    */

#undef SAMT_INCL_INTERNAL

/****** Render Fix ******************************************************************************/
#include <rf_core.h>                /* core                                                     */
#include <rf_util.h>                /* utility                                                  */

/****** Self ************************************************************************************/
#include <rf_ninja/rj_internal.h>   /* parent & siblings                                        */

/********************************/
/*  Constants                   */
/********************************/
/****** Half Screen Values **********************************************************************/
#define SCREEN_HW                   (640.f*0.5f)
#define SCREEN_HH                   (480.f*0.5f)

/********************************/
/*  Source                      */
/********************************/
/****** Sprite Color ****************************************************************************/
static Uint32
GetSpriteColor(Uint32 attr)
{
    if ( attr & NJD_SPRITE_COLOR )
    {
        NJS_COLOR color;

        color.argb.b = (Uint8) ( _nj_constant_material_.b * 255.f );
        color.argb.g = (Uint8) ( _nj_constant_material_.g * 255.f );
        color.argb.r = (Uint8) ( _nj_constant_material_.r * 255.f );
        color.argb.a = (Uint8) ( _nj_constant_material_.a * 255.f );

        return color.color;
    }
    else
    {
        return 0xFFFFFFFF;
    }
}

/****** Sprite 2D *******************************************************************************/
static Bool
___rjGetSpritePoints2D(NJS_POINT3* restrict pOutPt, const NJS_SPRITE* restrict sp, Int n, Float pri, Uint32 attr)
{
    const NJS_TEXANIM* restrict tanim = &sp->tanim[n];

    /**** Constants *************************************************************************/

    const Float scrn_hw = SCREEN_HW;
    const Float scrn_hh = SCREEN_HH;

    /** Calc Points and Angle ***************************************************************/

    const f32 x1 = sp->sx * _nj_screen_.ax * (f32)(-tanim->cx);
    const f32 y1 = sp->sy * _nj_screen_.ay * (f32)(-tanim->cy);

    const f32 x2 = sp->sx * _nj_screen_.ax * (f32)(tanim->sx - tanim->cx);
    const f32 y2 = sp->sy * _nj_screen_.ay * (f32)(tanim->sy - tanim->cy);

    if ( attr & NJD_SPRITE_ANGLE && sp->ang )
    {
        const f32 a_sin = njSin( sp->ang );
        const f32 a_cos = njCos( sp->ang );

        pOutPt[0].x = ( (x1 * a_cos) - (y1 * a_sin) );
        pOutPt[0].y = ( (y1 * a_cos) + (x1 * a_sin) );

        pOutPt[1].x = ( (x1 * a_cos) - (y2 * a_sin) );
        pOutPt[1].y = ( (y2 * a_cos) + (x1 * a_sin) );

        pOutPt[2].x = ( (x2 * a_cos) - (y1 * a_sin) );
        pOutPt[2].y = ( (y1 * a_cos) + (x2 * a_sin) );

        pOutPt[3].x = ( (x2 * a_cos) - (y2 * a_sin) );
        pOutPt[3].y = ( (y2 * a_cos) + (x2 * a_sin) );
    }
    else // no angle
    {
        pOutPt[0].x = x1;
        pOutPt[0].y = y1;

        pOutPt[1].x = x1;
        pOutPt[1].y = y2;

        pOutPt[2].x = x2;
        pOutPt[2].y = y1;

        pOutPt[3].x = x2;
        pOutPt[3].y = y2;
    }

    /** Move Points to Sprite Pos ***********************************************************/

    const f32 z = rjGetDepth2D(pri);

    for ( int i = 0; i < 4; ++i )
    {
        pOutPt[i].x = ( ((pOutPt[i].x + sp->p.x) - scrn_hw) / scrn_hw );
        pOutPt[i].y = ( ((pOutPt[i].y + sp->p.y) - scrn_hh) / scrn_hh );
        pOutPt[i].z = z;
    }

    return FALSE; // no clip
}

void
rjDrawSprite2D(const NJS_SPRITE* restrict sp, Int n, Float pri, Uint32 attr)
{
    NJS_POINT3 p[4]; // vertex points

    const NJS_TEXANIM* restrict tap = &sp->tanim[n];

    /** Calc Points *************************************************************************/

    ___rjGetSpritePoints2D(p, sp, n, pri, attr);

    /** Setup Draw State ********************************************************************/

    Int uv_clamp = TRUE;

    if ( tap->u1 < 0 || tap->u1 > 256 ||
         tap->u2 < 0 || tap->u2 > 256 ||
         tap->v1 < 0 || tap->v1 > 256 ||
         tap->v2 < 0 || tap->v2 > 256 )
    {
        uv_clamp = FALSE;
    }

    rjSetPolygonCullingCtx();

    njSetTexture( sp->tlist );
    njSetTextureNum( tap->texid );

    rjSetBlend2D( attr & (NJD_SPRITE_ALPHA|0x40) );
    rjSetTexture2D( uv_clamp );

    /** Calc UVs ****************************************************************************/

    const f32 uv_mul = (1.f/256.f);

    f32 u1, u2;

    if ( attr & NJD_SPRITE_HFLIP )
    {
        u1 = (f32) tap->u2 * uv_mul;
        u2 = (f32) tap->u1 * uv_mul;
    }
    else // no flip
    {
        u1 = (f32) tap->u1 * uv_mul;
        u2 = (f32) tap->u2 * uv_mul;
    }

    f32 v1, v2;

    if ( attr & NJD_SPRITE_VFLIP )
    {
        v1 = (f32) tap->v2 * uv_mul;
        v2 = (f32) tap->v1 * uv_mul;
    }
    else // no flip
    {
        v1 = (f32) tap->v1 * uv_mul;
        v2 = (f32) tap->v2 * uv_mul;
    }

    /** Sprite Color ************************************************************************/

    const Uint32 color = GetSpriteColor(attr);

    /** Set Vertex Buffer *******************************************************************/

    rjStartVertex2D(RJ_VERTEX_PTC);

    const Sint32 nbv = rjStartTriStrip(4);

    RJS_VERTEX_PTC* p_buf = rjGetVertexBuffer();

    p_buf[0].pos = p[0];
    p_buf[0].u   = u1;
    p_buf[0].v   = v1;
    p_buf[0].col = color;

    p_buf[1].pos = p[1];
    p_buf[1].u   = u1;
    p_buf[1].v   = v2;
    p_buf[1].col = color;

    p_buf[2].pos = p[2];
    p_buf[2].u   = u2;
    p_buf[2].v   = v1;
    p_buf[2].col = color;

    p_buf[3].pos = p[3];
    p_buf[3].u   = u2;
    p_buf[3].v   = v2;
    p_buf[3].col = color;

    rjEndTriStrip(nbv);

    rjEndVertex();

    rjSetPolygonCulling( RJ_CULL_NONE );
}

/****** Sprite 3D *******************************************************************************/
static Bool
___rjGetSpritePoints3D_ScaleOnly(NJS_POINT3* restrict pOutPt, const NJS_SPRITE* restrict sp, Int n, Uint32 attr)
{
    const NJS_TEXANIM* restrict tap = &sp->tanim[n];

    /** Calc Pos and Clip *******************************************************************/

    NJS_POINT3 pos;
    njCalcPoint(NULL, &sp->p, &pos);

    if ( pos.z < -_nj_clip_.f_clip ||
         pos.z > -_nj_clip_.n_clip )
    {
        return TRUE; // clip
    }

    /** Calc Points and Angle ***************************************************************/

    const f32 x1 = sp->sx * (f32)(-tap->cx);
    const f32 y1 = sp->sy * (f32)(-tap->cy);

    const f32 x2 = sp->sx * (f32)(tap->sx - tap->cx);
    const f32 y2 = sp->sy * (f32)(tap->sy - tap->cy);

    if ( attr & NJD_SPRITE_ANGLE )
    {
        const f32 a_sin = njSin( sp->ang );
        const f32 a_cos = njCos( sp->ang );

        pOutPt[0].x = ( (x1 * a_cos) - (y1 * a_sin) );
        pOutPt[0].y = ( (y1 * a_cos) + (x1 * a_sin) );

        pOutPt[1].x = ( (x1 * a_cos) - (y2 * a_sin) );
        pOutPt[1].y = ( (y2 * a_cos) + (x1 * a_sin) );

        pOutPt[2].x = ( (x2 * a_cos) - (y1 * a_sin) );
        pOutPt[2].y = ( (y1 * a_cos) + (x2 * a_sin) );

        pOutPt[3].x = ( (x2 * a_cos) - (y2 * a_sin) );
        pOutPt[3].y = ( (y2 * a_cos) + (x2 * a_sin) );
    }
    else // no angle
    {
        pOutPt[0].x = x1;
        pOutPt[0].y = y1;

        pOutPt[1].x = x1;
        pOutPt[1].y = y2;

        pOutPt[2].x = x2;
        pOutPt[2].y = y1;

        pOutPt[3].x = x2;
        pOutPt[3].y = y2;
    }

    /** Move Points to Sprite Pos ***********************************************************/

    for ( int i = 0; i < 4; ++i )
    {
        pOutPt[i].x += pos.x;
        pOutPt[i].y += pos.y;
        pOutPt[i].z  = pos.z;
    }

    return FALSE; // no clip
}

static Bool
___rjGetSpritePoints3D_Normal(NJS_POINT3* restrict pOutPt, const NJS_SPRITE* restrict sp, Int n, Uint32 attr)
{
    const NJS_TEXANIM* restrict tanim = &sp->tanim[n];

    /** Calc Points and Angle ***************************************************************/

    const f32 x1 = sp->sx * (f32)(-tanim->cx);
    const f32 y1 = sp->sy * (f32)(-tanim->cy);

    const f32 x2 = sp->sx * (f32)(tanim->sx - tanim->cx);
    const f32 y2 = sp->sy * (f32)(tanim->sy - tanim->cy);

    if ( attr & NJD_SPRITE_ANGLE && sp->ang )
    {
        const f32 a_sin = njSin( sp->ang );
        const f32 a_cos = njCos( sp->ang );

        pOutPt[0].x = ( (x1 * a_cos) - (y1 * a_sin) );
        pOutPt[0].y = ( (y1 * a_cos) + (x1 * a_sin) );

        pOutPt[1].x = ( (x1 * a_cos) - (y2 * a_sin) );
        pOutPt[1].y = ( (y2 * a_cos) + (x1 * a_sin) );

        pOutPt[2].x = ( (x2 * a_cos) - (y1 * a_sin) );
        pOutPt[2].y = ( (y1 * a_cos) + (x2 * a_sin) );

        pOutPt[3].x = ( (x2 * a_cos) - (y2 * a_sin) );
        pOutPt[3].y = ( (y2 * a_cos) + (x2 * a_sin) );
    }
    else // no angle
    {
        pOutPt[0].x = x1;
        pOutPt[0].y = y1;

        pOutPt[1].x = x1;
        pOutPt[1].y = y2;

        pOutPt[2].x = x2;
        pOutPt[2].y = y1;

        pOutPt[3].x = x2;
        pOutPt[3].y = y2;
    }

    /** Move Points to Sprite Pos ***********************************************************/

    for ( int i = 0; i < 4; ++i )
    {
        pOutPt[i].x += sp->p.x;
        pOutPt[i].y += sp->p.y;
        pOutPt[i].z  = sp->p.z;
    }

    /** Calc Points and Clip ****************************************************************/

    njCalcPoints(NULL, pOutPt, pOutPt, 4);

    const f32 f_clip = -_nj_clip_.f_clip;
    const f32 n_clip = -_nj_clip_.n_clip;

    if ( (pOutPt[0].z < f_clip && pOutPt[1].z < f_clip && pOutPt[2].z < f_clip && pOutPt[3].z < f_clip) || // far clip
         (pOutPt[0].z > n_clip && pOutPt[1].z > n_clip && pOutPt[2].z > n_clip && pOutPt[3].z > n_clip) )  // near clip
    {
        return TRUE; // clipped
    }
    
    return FALSE; // no clip
}

void
rjDrawSprite3D(const NJS_SPRITE* restrict sp, Int n, Uint32 attr)
{
    NJS_POINT3 p[4]; // vertex points

    /** Calc Points and Clip ****************************************************************/

    Int clip;

    if ( attr & NJD_SPRITE_SCALE )
    {
        clip = ___rjGetSpritePoints3D_ScaleOnly(p, sp, n, attr);
    }
    else // normal sprite
    {
        clip = ___rjGetSpritePoints3D_Normal(p, sp, n, attr);
    }

    if ( clip )
    {
        return;
    }

    /** Setup Draw State ********************************************************************/

    const NJS_TEXANIM* restrict tap = &sp->tanim[n];

    Int uv_clamp = TRUE;

    if ( tap->u1 < 0 || tap->u1 > 256 ||
         tap->u2 < 0 || tap->u2 > 256 ||
         tap->v1 < 0 || tap->v1 > 256 ||
         tap->v2 < 0 || tap->v2 > 256 )
    {
        uv_clamp = FALSE;
    }

    rjSetPolygonCullingCtx();

    njSetTexture( sp->tlist );
    njSetTextureNum( tap->texid );

    rjSetBlend2D( attr & NJD_SPRITE_ALPHA );
    rjSetTexture2D( uv_clamp );

    /** Calc UVs ****************************************************************************/

    const f32 uv_mul = (1.f/256.f);

    f32 u1, u2;

    if ( attr & NJD_SPRITE_HFLIP )
    {
        u1 = (f32) tap->u2 * uv_mul;
        u2 = (f32) tap->u1 * uv_mul;
    }
    else // no flip
    {
        u1 = (f32) tap->u1 * uv_mul;
        u2 = (f32) tap->u2 * uv_mul;
    }

    f32 v1, v2;

    if ( attr & NJD_SPRITE_VFLIP )
    {
        v1 = (f32) tap->v2 * uv_mul;
        v2 = (f32) tap->v1 * uv_mul;
    }
    else // no flip
    {
        v1 = (f32) tap->v1 * uv_mul;
        v2 = (f32) tap->v2 * uv_mul;
    }

    /** Sprite Color ************************************************************************/

    const Uint32 color = GetSpriteColor(attr);

    /** Set Vertex Buffer *******************************************************************/

    rjStartVertex3D(RJ_VERTEX_PTC);

    const Sint32 nbv = rjStartTriStrip(4);

    RJS_VERTEX_PTC* p_buf = rjGetVertexBuffer();

    p_buf[0].pos = p[0];
    p_buf[0].u   = u1;
    p_buf[0].v   = v1;
    p_buf[0].col = color;

    p_buf[1].pos = p[1];
    p_buf[1].u   = u1;
    p_buf[1].v   = v2;
    p_buf[1].col = color;

    p_buf[2].pos = p[2];
    p_buf[2].u   = u2;
    p_buf[2].v   = v1;
    p_buf[2].col = color;

    p_buf[3].pos = p[3];
    p_buf[3].u   = u2;
    p_buf[3].v   = v2;
    p_buf[3].col = color;

    rjEndTriStrip(nbv);

    rjEndVertex();

    rjSetPolygonCulling( RJ_CULL_NONE );
}

/****** Assembly ********************************************************************************/
__declspec(naked)
static void
___DrawSprite2D(void)
{
    __asm
    {
        push        [esp+12]    // attr
        push        [esp+12]    // pri
        push        eax         // n
        push        [esp+16]    // sp

        call        rjDrawSprite2D

        add esp,    16
        retn
    }
}

__declspec(naked)
static void
___DrawSprite3D(void)
{
    __asm
    {
        push        [esp+8]     // attr
        push        eax         // n
        push        [esp+12]    // sp

        call        rjDrawSprite3D

        add esp,    12
        retn
    }
}

/****** Init ************************************************************************************/
void
RFD_SpriteInit(void)
{
    WriteJump(0x0077D0B0, ___DrawSprite2D);
    WriteJump(0x0077D690, ___DrawSprite3D);
}
