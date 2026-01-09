/************************/
/*  Includes            */
/************************/
/****** Core Toolkit ****************************************************************/
#include <samt/core.h>          /* core                                             */
#include <samt/writemem.h>      /* writedata                                        */

/****** Render Fix ******************************************************************/
#include <rf_core.h>            /* core                                             */

/****** Config **********************************************************************/
#include <cnf.h>                /* config get                                       */

/****** Self ************************************************************************/
#include <rf_module/rfm_event/ev_internal.h> /* children                            */

/************************/
/*  Source              */
/************************/
/****** Init ************************************************************************/
void
RFM_EventInit(void)
{
    EV_ByteSwapInit();
    EV_FileInit();

    WriteData(0x00458A18, 350, i32); // force play E0350

    EV_RendererInit();
}
