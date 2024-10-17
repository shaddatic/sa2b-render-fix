#include <sa2b/core.h>
#include <sa2b/memory.h>
#include <sa2b/writeop.h>
#include <sa2b/funchook.h>

/** Ninja **/
#include <sa2b/ninja/ninja.h>

/** Game **/
#include <sa2b/sonic/task.h>

/** Render Fix **/
#include <rf_core.h>
#include <rf_config.h>
#include <rf_util.h>
#include <rf_renderstate.h>

/** Self **/
#include <rfm_eget.h>

#define getEmblemDisplayer      FUNC_PTR(void, __cdecl, (task*), 0x007986A0)

static hook_info getEmblemDisplayerHookInfo[1];
static void
getEmblemDisplayerHook(task* const tp)
{
    RFRS_SetTransMode(RFRS_TRANSMD_AUTO_ATEST);

    FuncHookCall( getEmblemDisplayerHookInfo, getEmblemDisplayer(tp) );

    RFRS_SetTransMode(RFRS_TRANSMD_END);
}

void
RFM_EmblemGetInit(void)
{
    if (RF_ConfigGetInt(CNF_EGET_PTCLFIX))
    {
        SwitchDisplayer(0x0079860F, DISP);
        FuncHook(getEmblemDisplayerHookInfo, getEmblemDisplayer, getEmblemDisplayerHook);
    }

    if (RF_ConfigGetInt(CNF_EGET_FADEIN))
    {
        WriteNOP(0x006049A8, 0x006049AE); /* Stop FadeColor being set to 0 */
    }
}
