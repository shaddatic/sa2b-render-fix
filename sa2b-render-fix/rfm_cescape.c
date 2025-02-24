#include <samt/core.h>

/** Ninja **/
#include <samt/ninja/ninja.h>

/** Source **/
#include <samt/sonic/set.h>

/** Object **/
#include <samt/sonic/object/o_light.h>

/** Render Fix **/
#include <rf_core.h>
#include <rf_config.h>

/** Self **/
#include <rfm_cescape.h>
#include <rfm_cescape/ce_internal.h>

#define ReplaceObjectFunction(plist, idx, pfunc)    ((OBJ_ITEMENTRY*)plist)[idx].fnExec = (EDIT_FUNC)pfunc

static void
LightModRestore(void)
{
    ReplaceObjectFunction(0x0109E830, 58, ObjectLightSW);     // Light SW          (City Escape)
    ReplaceObjectFunction(0x0109E830, 69, ObjectTreeShadows); // ObjectTreeShadows (City Escape)
}

#define SECT "c_escape"

void
RFM_CityEscapeInit(void)
{
    if (RF_ConfigGetInt(CNF_CE_LITEMOD))
    {
        LightModRestore();
    }
}
