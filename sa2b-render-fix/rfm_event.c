/************************/
/*  Includes            */
/************************/
/****** Core Toolkit ****************************************************************/
#include <samt/core.h>          /* core                                             */
#include <samt/writemem.h>      /* writedata                                        */

/****** Render Fix ******************************************************************/
#include <rf_core.h>            /* core                                             */
#include <rf_config.h>          /* config                                           */

/****** Self ************************************************************************/
#include <rfm_event/ev_internal.h> /* children                                      */

/************************/
/*  Source              */
/************************/
/****** Init ************************************************************************/
void
RFM_EventInit(void)
{
    EV_ByteSwapInit();
    EV_FileInit();

    WriteData(0x00458A18, 350, s32); // force play E0350

    if ( RF_ConfigGetInt(CNF_EVENT_RFDISP) )
    {
        EV_RendererInit();
    }
}
