/************************/
/*  Includes            */
/************************/
/****** Core Toolkit ****************************************************************/
#include <samt/core.h>          /* core                                             */
#include <samt/writeop.h>       /* writejump                                        */

/****** Ninja ***********************************************************************/
#include <samt/ninja/ninja.h>   /* ninja                                            */

/****** Game ************************************************************************/
#include <samt/sonic/task.h>    /* task                                             */
#include <samt/sonic/njctrl.h>  /* ninja control                                    */
#include <samt/sonic/display.h> /* screen display                                   */

/****** Render Fix ******************************************************************/
#include <rf_core.h>            /* core                                             */
#include <rf_eventinfo.h>       /* event data                                       */
#include <rf_renderstate.h>     /* render state                                     */
#include <rf_draw.h>            /* emulated njcnk draw functions                    */

/****** Self ************************************************************************/
#include <rfm_event/ev_draw/evd_internal.h> /* parent & siblings                    */

/************************/
/*  Source              */
/************************/
/****** Extern **********************************************************************/
void
Draw43Bars(void)
{
    const f32 disp_ratio = GetDisplayRatio();

    if ( EV_Get43Mode() == EV_43MD_ALWAYS && disp_ratio > 1.f )
    {
        NJS_POLYGON_VTX poly[4];

        /** Init polyvtx **/
        {
            poly[0].y   = 0.0f;
            poly[0].z   = 1.0f;
            poly[0].col = 0xFF000000;
            poly[1].y   = 481.0f;
            poly[1].z   = 1.0f;
            poly[1].col = 0xFF000000;
            poly[2].y   = 0.0f;
            poly[2].z   = 1.0f;
            poly[2].col = 0xFF000000;
            poly[3].y   = 481.0f;
            poly[3].z   = 1.0f;
            poly[3].col = 0xFF000000;
        }

        const f32 scrnshft = (disp_ratio - 1.0f) * (320.0f) + 1.0f;

        {
            const f32 scrnpos = 0.f - scrnshft;

            poly[0].x = scrnpos;
            poly[1].x = scrnpos;
            poly[2].x = 0.f;
            poly[3].x = 0.f;

            njDrawPolygon(poly, ARYLEN(poly), false);
        }

        {
            const f32 scrnpos = 640.f + scrnshft;

            poly[0].x = scrnpos;
            poly[1].x = scrnpos;
            poly[2].x = 640.f;
            poly[3].x = 640.f;

            njDrawPolygon(poly, ARYLEN(poly), false);
        }
    }
}
