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
/*  Source              */
/************************/
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
