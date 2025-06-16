/************************/
/*  Includes            */
/************************/
/****** Core Toolkit ****************************************************************/
#include <samt/core.h>          /* core                                             */
#include <samt/writeop.h>       /* writejump                                        */

/****** Render Fix ******************************************************************/
#include <rf_core.h>            /* core                                             */
#include <rf_config.h>          /* config get                                       */
#include <rf_util.h>            /* switch displayer                                 */

/****** Self ************************************************************************/
#include <rfm_event/ev_renderer/evr_internal.h> /* children                         */

/************************/
/*  Data                */
/************************/
/****** Event Settings **************************************************************/
bool            EventEquipmentEnable;
RFE_EV_43MODE   EventEnforce43;
RFE_EV_VSYNC    EventVsyncMode;
bool            EventDebugFlag;

/****** Feature *********************************************************************/
static bool     NewEventRenderer;

/************************/
/*  Source              */
/************************/
/****** Feature *********************************************************************/
bool
RFF_NewEventRenderer(void)
{
    return NewEventRenderer;
}

/****** Init ************************************************************************/
void
EV_RendererInit(void)
{
    EVR_TaskInit();
    EVR_VsyncInit();

    WriteJump(0x005FB4FD, 0x005FB5B9); // disable vanilla black bars

    SwitchDisplayer(0x005FB04D, DISP_SORT); // set screen effect to sorted displayer

    EventEquipmentEnable = RF_ConfigGetInt(CNF_EVENT_DRAWEQUIP);
    EventEnforce43       = RF_ConfigGetInt(CNF_EVENT_43MD);
    EventVsyncMode       = RF_ConfigGetInt(CNF_EVENT_VSYNC);

    EventDebugFlag       = RF_ConfigGetInt(CNF_DEBUG_EVENT);

    NewEventRenderer = true;
}
