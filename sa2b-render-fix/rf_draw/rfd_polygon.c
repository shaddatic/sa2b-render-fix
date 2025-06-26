/************************/
/*  Includes            */
/************************/
/****** Core Toolkit ****************************************************************/
#include <samt/core.h>          /* core                                             */
#include <samt/writeop.h>       /* WriteJump                                        */

/****** Ninja ***********************************************************************/
#include <samt/ninja/ninja.h>   /* ninja                                            */

/****** Render Fix ******************************************************************/
#include <rf_core.h>            /* core                                             */

/****** Self ************************************************************************/
#include <rf_draw/rfd_internal.h>               /* parent & siblings                */
#include <rf_draw/rfd_cnkmdl/rfdcnk_internal.h> /* self                             */

/************************/
/*  Game Defs           */
/************************/
/****** Sprite HScale ***************************************************************/
#define _gj_sprite_scale_               DATA_REF(f32, 0x025EFF54)

/************************/
/*  Source              */
/************************/
/****** Extern **********************************************************************/
void
rjDrawPolygon(const NJS_POLYGON_VTX* polygon, Int count, Int trans)
{
    njDrawPolygon(polygon, count, trans);

    return; ___TODO("Currently unfinished, needs 2D shader still");

    const Float xscl = _gj_sprite_scale_;

    rjSetBlend2D(trans);

    rjStartVertex2D(RJE_VERTEX_PC);

    const Sint32 nbv = rjStartTriStrip(count);

    RJS_VERTEX_PC* p_buf = rjGetVertexBuffer();

    for ( int i = 0; i < count; ++i, ++polygon, ++p_buf )
    {
        const Float ooz = -1.f / polygon->z;

        p_buf->pos.x = (polygon->x - 320.f) * (1.f/640.f) * xscl;
        p_buf->pos.y = (polygon->y - 240.f) * (1.f/480.f);
        p_buf->pos.z = ooz;

        p_buf->col = polygon->col;
    }

    rjEndTriStrip(nbv);

    rjEndVertex();
}
