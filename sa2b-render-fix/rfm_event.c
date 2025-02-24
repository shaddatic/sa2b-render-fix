/************************/
/*  Includes            */
/************************/
/****** Core Toolkit ****************************************************************/
#include <samt/core.h>          /* core                                             */

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

/****** Init ************************************************************************/
void
RFM_EventInit(void)
{
    EV_ByteSwapInit();
    EV_CameraInit();

    if (RF_ConfigGetInt(CNF_EVENT_DISPREPLCE))
    {
        RF_ConfigGetInt(CNF_EXP_EVDRAW) ? EV_DrawInit() : EV_OldDrawInit();

        EventEquipmentEnable = RF_ConfigGetInt(CNF_EVENT_DRAWEQUIP);
        EventEnforce43       = RF_ConfigGetInt(CNF_EVENT_43MD);
    }

    if (RF_ConfigGetInt(CNF_EVENT_DRAWMOD))
    {
        EV_ModifierInit();
    }
}
