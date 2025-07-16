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

/****** Self ************************************************************************************/
#include <rf_draw/rfd_internal.h>   /* parent & siblings                                        */

/********************************/
/*  Source                      */
/********************************/
/****** Raw *************************************************************************************/
void
rjDrawPolygon(const NJS_POLYGON_VTX* restrict polygon, Int count, Int trans)
{
    rjSetBlend2D(trans);

    rjStartVertex2D(RJE_VERTEX_PC);

    const Sint32 nbv = rjStartTriStrip(count);

    RJS_VERTEX_PC* restrict p_buf = rjGetVertexBuffer();

    for ( int i = 0; i < count; ++i )
    {
        p_buf[i].pos.x = polygon[i].x;
        p_buf[i].pos.y = polygon[i].y;
        p_buf[i].pos.z = polygon[i].z;
        p_buf[i].col   = polygon[i].col;
    }

    rjEndTriStrip(nbv);

    rjEndVertex();
}

void
rjDrawTextureEx(const NJS_TEXTURE_VTX* restrict polygon, Int count, Int trans)
{
    Int uv_clamp = TRUE;

    for ( int i = 0; i < count; ++i )
    {
        if ( polygon[i].u > 1.f || polygon[i].u < 0.f ||
             polygon[i].v > 1.f || polygon[i].v < 0.f )
        {
            uv_clamp = FALSE;
            break;
        }
    }

    rjSetBlend2D(trans);
    rjSetTexture2D(uv_clamp);

    rjStartVertex2D(RJE_VERTEX_PTC);

    const Sint32 nbv = rjStartTriStrip(count);

    RJS_VERTEX_PTC* restrict p_buf = rjGetVertexBuffer();

    for ( int i = 0; i < count; ++i )
    {
        p_buf[i].pos.x = polygon[i].x;
        p_buf[i].pos.y = polygon[i].y;
        p_buf[i].pos.z = polygon[i].z;
        p_buf[i].u     = polygon[i].u;
        p_buf[i].v     = polygon[i].v;
        p_buf[i].col   = polygon[i].col;
    }

    rjEndTriStrip(nbv);

    rjEndVertex();
}

void
rjDrawTexture(const NJS_TEXTURE_VTX* polygon, Int count, Int tex, Int flag)
{
    _nj_curr_ctx_->texsurface = rjGetTextureSurfaceG(tex);

    rjDrawTextureEx(polygon, count, flag);
}

/****** Draw 2D *********************************************************************************/
void
rjDrawPolygon2D(const NJS_POINT2COL* restrict p, Sint32 n, Float pri, Uint32 attr)
{
    const f32 uv_mul = (1.f/256.f);

    const NJS_POINT2* p_pos = p->p;
    const NJS_TEX*    p_tex = &p->tex->tex;
    const Uint32*     p_col = &p->col->color;

    const f32 z = rjGetDepth2D( pri );

    rjSetBlend2D( attr & NJD_TRANSPARENT );

    if ( attr & NJD_USE_TEXTURE )
    {
        rjSetTexture2D(FALSE);

        rjStartVertex2D(RJE_VERTEX_PTC);

        const Sint32 nbv = rjStartTriStrip(n);

        RJS_VERTEX_PTC* restrict p_buf = rjGetVertexBuffer();

        for ( int i = 0; i < n; ++i )
        {
            p_buf[i].pos.x = p_pos[i].x;
            p_buf[i].pos.y = p_pos[i].y;
            p_buf[i].pos.z = z;

            p_buf[i].u     = (f32)p_tex[i].u * uv_mul;
            p_buf[i].v     = (f32)p_tex[i].v * uv_mul;

            p_buf[i].col   = p_col[i];
        }

        rjEndTriStrip(nbv);

        rjEndVertex();
    }
    else // non-tex
    {
        rjStartVertex2D(RJE_VERTEX_PC);

        const Sint32 nbv = rjStartTriStrip(n);

        RJS_VERTEX_PC* restrict p_buf = rjGetVertexBuffer();

        for ( int i = 0; i < n; ++i )
        {
            p_buf[i].pos.x = p_pos[i].x;
            p_buf[i].pos.y = p_pos[i].y;
            p_buf[i].pos.z = z;

            p_buf[i].col   = p_col[i];
        }

        rjEndTriStrip(nbv);

        rjEndVertex();
    }
}

/****** Sub 3D **********************************************************************************/
void
rjDrawPolygon3DExStart(Int trans)
{
    rjSetBlend2D(trans);
}

void
rjDrawPolygon3DExSetData(const NJS_POLYGON_VTX* restrict p, Int count)
{
    rjStartVertex3D(RJE_VERTEX_PC);

    const Sint32 nbv = rjStartTriStrip(count);

    RJS_VERTEX_PC* restrict p_buf = rjGetVertexBuffer();

    for ( int i = 0; i < count; ++i )
    {
        NJS_POINT3 pos = { 0 };
        njCalcPoint(NULL, (NJS_POINT3*)&p[i].x, &pos);

        p_buf[i].pos.x = pos.x;
        p_buf[i].pos.y = pos.y;
        p_buf[i].pos.z = pos.z;

        p_buf[i].col   = p[i].col;
    }

    rjEndTriStrip(nbv);

    rjEndVertex();
}

void
rjDrawTexture3DExStart(Int trans)
{
    rjSetBlend2D(trans);
    rjSetTexture2D(FALSE);
}

void
rjDrawTexture3DExSetData(const NJS_TEXTURE_VTX* restrict p, Int count)
{
    rjStartVertex3D(RJE_VERTEX_PTC);

    const Sint32 nbv = rjStartTriStrip(count);

    RJS_VERTEX_PTC* restrict p_buf = rjGetVertexBuffer();

    for ( int i = 0; i < count; ++i )
    {
        NJS_POINT3 pos = { 0 };
        njCalcPoint(NULL, (NJS_POINT3*)&p[i].x, &pos);

        p_buf[i].pos.x = pos.x;
        p_buf[i].pos.y = pos.y;
        p_buf[i].pos.z = pos.z;

        p_buf[i].u     = p[i].u;
        p_buf[i].v     = p[i].v;
        p_buf[i].col   = p[i].col;
    }

    rjEndTriStrip(nbv);

    rjEndVertex();
}

/****** Draw 3D *********************************************************************************/
void
rjDrawTexture3DEx(const NJS_TEXTURE_VTX* restrict p, const Int count, Int trans)
{
    rjDrawTexture3DExStart(trans);
    rjDrawTexture3DExSetData(p, count);
}

void
rjDrawPolygon3DEx(const NJS_POLYGON_VTX* restrict p, const Int count, Int trans)
{
    rjDrawPolygon3DExStart(trans);
    rjDrawPolygon3DExSetData(p, count);
}

/****** ASM *************************************************************************************/
__declspec(naked)
static void
___DrawPolygon(void)
{
    __asm
    {
        push        eax
        push        ecx
        push        [esp+12]

        call        rjDrawPolygon

        add esp,    12
        retn
    }
}

__declspec(naked)
static void
___DrawTexture(void)
{
    __asm
    {
        push        [esp+4]
        push        edx
        push        eax
        push        ecx

        call        rjDrawTexture

        add esp,    16
        retn
    }
}

__declspec(naked)
static void
___DrawTextureEx(void)
{
    __asm
    {
        push        [esp+4]
        push        4
        push        eax

        call        rjDrawTextureEx

        add esp,    12
        retn
    }
}

__declspec(naked)
static void
___DrawPolygon2D(void)
{
    __asm
    {
        push        [esp+8]
        push        [esp+8]
        push        4
        push        eax

        call        rjDrawPolygon2D

        add esp,    16
        retn
    }
}

__declspec(naked)
static void
___DrawPolygon3DSetData(void)
{
    __asm
    {
        push        ecx
        push        eax

        call        rjDrawPolygon3DExSetData

        add esp,    8
        retn
    }
}

__declspec(naked)
static void
___DrawTexture3DSetData(void)
{
    __asm
    {
        push        ecx
        push        eax

        call        rjDrawTexture3DExSetData

        add esp,    8
        retn
    }
}

/****** Init ************************************************************************************/
void
RFD_PolygonInit(void)
{
    WriteJump(0x0077F7F0, ___DrawPolygon);
    WriteJump(0x0077F510, ___DrawTexture);
    WriteJump(0x0077F6B0, ___DrawTextureEx);
    WriteJump(0x00490FA0, ___DrawPolygon2D);
    WriteJump(0x00780F60, rjDrawPolygon3DExStart);
    WriteJump(0x00781090, ___DrawPolygon3DSetData);
    WriteJump(0x00781370, ___DrawTexture3DSetData);
}
