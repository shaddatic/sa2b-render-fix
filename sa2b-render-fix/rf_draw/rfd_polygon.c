/************************/
/*  Includes            */
/************************/
/****** Core Toolkit ****************************************************************/
#include <samt/core.h>          /* core                                             */
#include <samt/writeop.h>       /* WriteJump                                        */

#define SAMT_INCL_INTERNAL

/****** Ninja ***********************************************************************/
#include <samt/ninja/ninja.h>   /* ninja                                            */

#undef SAMT_INCL_INTERNAL

/****** Render Fix ******************************************************************/
#include <rf_core.h>            /* core                                             */

/****** Self ************************************************************************/
#include <rf_draw/rfd_internal.h>               /* parent & siblings                */
#include <rf_draw/rfd_cnkmdl/rfdcnk_internal.h> /* self                             */

/********************************/
/*  Source                      */
/********************************/
/****** Raw *************************************************************************************/
void
rjDrawPolygon(const NJS_POLYGON_VTX* polygon, Int count, Int trans)
{
    rjSetBlend2D(trans);

    rjStartVertex2D(RJE_VERTEX_PC);

    const Sint32 nbv = rjStartTriStrip(count);

    RJS_VERTEX_PC* p_buf = rjGetVertexBuffer();

    for ( int i = 0; i < count; ++i, ++polygon, ++p_buf )
    {
        p_buf->pos.x = polygon->x;
        p_buf->pos.y = polygon->y;
        p_buf->pos.z = polygon->z;
        p_buf->col   = polygon->col;
    }

    rjEndTriStrip(nbv);

    rjEndVertex();
}

void
rjDrawTextureEx(const NJS_TEXTURE_VTX* polygon, Int count, Int trans)
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

    RJS_VERTEX_PTC* p_buf = rjGetVertexBuffer();

    for ( int i = 0; i < count; ++i, ++polygon, ++p_buf )
    {
        p_buf->pos.x = polygon->x;
        p_buf->pos.y = polygon->y;
        p_buf->pos.z = polygon->z;
        p_buf->u     = polygon->u;
        p_buf->v     = polygon->v;
        p_buf->col   = polygon->col;
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

void
rjDrawPolygon2D(const NJS_POINT2COL* p, Sint32 n, Float pri, Uint32 attr)
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

        RJS_VERTEX_PTC* p_buf = rjGetVertexBuffer();

        for ( int i = 0; i < n; ++i, ++p, ++p_buf )
        {
            p_buf->pos.x = p_pos[i].x;
            p_buf->pos.y = p_pos[i].y;
            p_buf->pos.z = z;

            p_buf->u     = (f32)p_tex[i].u * uv_mul;
            p_buf->v     = (f32)p_tex[i].v * uv_mul;

            p_buf->col   = p_col[i];
        }

        rjEndTriStrip(nbv);

        rjEndVertex();
    }
    else // non-tex
    {
        rjStartVertex2D(RJE_VERTEX_PC);

        const Sint32 nbv = rjStartTriStrip(n);

        RJS_VERTEX_PC* p_buf = rjGetVertexBuffer();

        for ( int i = 0; i < n; ++i, ++p, ++p_buf )
        {
            p_buf->pos.x = p_pos[i].x;
            p_buf->pos.y = p_pos[i].y;
            p_buf->pos.z = z;

            p_buf->col   = p_col[i];
        }

        rjEndTriStrip(nbv);

        rjEndVertex();
    }
}

/****** ASM *************************************************************************/
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

/****** Init ************************************************************************/
void
RFD_PolygonInit(void)
{
    WriteJump(0x0077F7F0, ___DrawPolygon);
    WriteJump(0x0077F510, ___DrawTexture);
    WriteJump(0x0077F6B0, ___DrawTextureEx);
    WriteJump(0x00490FA0, ___DrawPolygon2D);
}
