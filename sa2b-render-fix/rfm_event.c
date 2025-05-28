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
#include <rfm_event.h>             /* self                                          */
#include <rfm_event/ev_internal.h> /* children                                      */

/************************/
/*  Data                */
/************************/
/****** Event Settings **************************************************************/
static bool          EventEquipmentEnable;
static RFE_EV_43MODE EventEnforce43;
static bool          NewEventRenderer;

/************************/
/*  Source              */
/************************/
/****** Extern **********************************************************************/
bool
EV_GetEquipmentMode(void)
{
    return EventEquipmentEnable;
}

RFE_EV_43MODE
EV_Get43Mode(void)
{
    return EventEnforce43;
}

/****** Feature *********************************************************************/
bool
RFF_NewEventRenderer(void)
{
    return NewEventRenderer;
}

/****** Init ************************************************************************/
void
RFM_EventInit(void)
{
    EV_ByteSwapInit();

    if (RF_ConfigGetInt(CNF_EVENT_DISPREPLCE))
    {
        EV_DrawInit();

        EventEquipmentEnable = RF_ConfigGetInt(CNF_EVENT_DRAWEQUIP);
        EventEnforce43       = RF_ConfigGetInt(CNF_EVENT_43MD);

        NewEventRenderer = true;
    }

    WriteData(0x00458A18, 350, s32); // force play E0350
}
