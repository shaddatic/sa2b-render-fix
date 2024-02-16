#include <sa2b/core.h>
#include <sa2b/memory.h>
#include <sa2b/memutil.h>

/** Ninja **/
#include <sa2b/ninja/ninja.h>

/** Render Fix **/
#include <rf_core.h>
#include <rf_config.h>
#include <rf_util.h>

/** Self **/
#include <rfm_eget.h>

EXTERN NJS_CNK_OBJECT object_eget[];

void
RFM_EmblemGetInit(void)
{
    if (RF_ConfigGetInt(CNF_EGET_FADEIN))
    {
        SwitchDisplayer(0x0079860F, DISP_SORT);
        MemCopy((void*)0x0096DE1C, object_eget, sizeof(NJS_CNK_OBJECT));
    }

    if (RF_ConfigGetInt(CNF_EGET_PTCLFIX))
    {
        WriteNoOP(0x006049A8, 0x006049AE); /* Stop FadeColor being set to 0 */
    }
}
