#include <sa2b/core.h>
#include <sa2b/memory.h>
#include <sa2b/writemem.h>
#include <sa2b/writeop.h>

/** Util **/
#include <sa2b/util/endian.h>

/** Ninja **/
#include <sa2b/ninja/ninja.h>

/** Source **/
#include <sa2b/sonic/task.h>
#include <sa2b/sonic/njctrl.h>
#include <sa2b/sonic/display.h>

/** Render Fix **/
#include <rf_core.h>
#include <rf_config.h>
#include <rf_eventinfo.h>
#include <rf_renderstate.h>

/** Self **/
#include <rfm_event.h>
#include <rfm_event/ev_internal.h>

static bool          EventEquipmentEnable;
static RFE_EV_43MODE EventEnforce43;

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
