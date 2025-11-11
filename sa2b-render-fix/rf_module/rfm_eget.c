#include <samt/core.h>
#include <samt/memory.h>
#include <samt/writeop.h>
#include <samt/funchook.h>

/** Ninja **/
#include <samt/ninja/ninja.h>

/** Game **/
#include <samt/sonic/task.h>

/** Render Fix **/
#include <rf_core.h>
#include <rf_util.h>
#include <rf_renderstate.h>

/****** Config **********************************************************************/
#include <cnf.h>                /* config get                                       */

#define getEmblemDisplayer      FUNC_PTR(void, __cdecl, (task*), 0x007986A0)

static mt_hookinfo getEmblemDisplayerHookInfo[1];
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
    // fix kiran
    SwitchDisplayer(0x0079860F, DISP);
    FuncHook(getEmblemDisplayerHookInfo, getEmblemDisplayer, getEmblemDisplayerHook);

    // allow fade-in
    WriteNOP(0x006049A8, 0x006049AE); /* Stop FadeColor being set to 0 */
}
