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

#define BackupScreen            FUNC_PTR(void, __cdecl, (void), 0x00458EA0)
#define RestoreScreen           FUNC_PTR(void, __cdecl, (void), 0x00458EE0)

static mt_hookinfo getEmblemDisplayerHookInfo[1];
static void
getEmblemDisplayerHook(task* const tp)
{
    NJS_MATRIX m;
    njSetMatrix( &m, _nj_curr_matrix_ );

    BackupScreen();

    RFRS_SetTransMode(RFRS_TRANSMD_AUTO_ATEST);

    mtHookInfoCall( getEmblemDisplayerHookInfo, getEmblemDisplayer(tp) );

    RFRS_SetTransMode(RFRS_TRANSMD_END);

    RestoreScreen();

    njSetMatrix( NULL, &m );
}

void
RFM_EmblemGetInit(void)
{
    // fix kiran
    SwitchDisplayer(0x0079860F, DISP);
    mtHookFunc(getEmblemDisplayerHookInfo, getEmblemDisplayer, getEmblemDisplayerHook);

    // allow fade-in
    WriteNOP(0x006049A8, 0x006049AE); /* Stop FadeColor being set to 0 */
}
