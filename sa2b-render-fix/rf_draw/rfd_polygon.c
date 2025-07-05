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

/************************/
/*  Source              */
/************************/
/****** Extern **********************************************************************/
static NJS_TEXSURFACE*
rjGetTextureSurfaceG(Int gbix)
{
    const Int nb_texman = _nj_texmanagesize;

    if ( nb_texman <= 0 )
    {
        return nullptr;
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

    return nullptr;
}

/****** Extern **********************************************************************/
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
rjDrawTexture(const NJS_TEXTURE_VTX* polygon, Int count, Int tex, Int flag)
{
    _nj_curr_ctx_->texsurface = rjGetTextureSurfaceG(tex);

    rjSetBlend2D(flag);
    rjSetTexture2D();

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

/****** Init ************************************************************************/
void
RFD_PolygonInit(void)
{
    WriteJump(0x0077F7F0, ___DrawPolygon);
    WriteJump(0x0077F510, ___DrawTexture);
}
