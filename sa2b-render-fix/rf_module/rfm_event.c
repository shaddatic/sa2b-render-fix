/************************/
/*  Includes            */
/************************/
/****** Core Toolkit ****************************************************************/
#include <samt/core.h>          /* core                                             */
#include <samt/writemem.h>      /* writedata                                        */
#include <samt/writeop.h>       /* write nop                                        */

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

    // set game intro
    switch ( CNF_GetInt(CNF_EVENT_INTRO) )
    {
        case CNFE_EVENT_INTRO_AUTO:
        {
            WriteData(0x00458A18, 350, i32); // force play E0350
            break;
        }
        case CNFE_EVENT_INTRO_BATTLE:
        {
            WriteShortJump(0x004589F5, 0x00458A28); // force Battle intro
            break;
        }
        case CNFE_EVENT_INTRO_DREAMCAST:
        {
            WriteData(0x00458A18, 350, i32); // force play E0350

//          [[fallthrough]];
        }
        case CNFE_EVENT_INTRO_FMV:
        {
            WriteShortJump(0x004589F5, 0x00458A12); // force Dreamcast intro
            break;
        }
    }

    EV_RendererInit();
}
