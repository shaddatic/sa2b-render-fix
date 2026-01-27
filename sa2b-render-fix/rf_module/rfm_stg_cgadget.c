#include <samt/core.h>
#include <samt/funchook.h>

/** Ninja **/
#include <samt/ninja/ninja.h>

/** Game **/
#include <samt/sonic/task.h>

/** Render Fix **/
#include <rf_core.h>

static mt_hookinfo BgDispCGHookInfo[1];

#define BgDispCG    FUNC_PTR(void, __cdecl, (task*), 0x00771DD0)

static void
BgDispCGHook(task* tp)
{
    mtHookInfoCall( BgDispCGHookInfo, BgDispCG(tp) );

    njFogEnable();
}

void
RFM_CrazyGadgetInit(void)
{
    mtHookFunc(BgDispCGHookInfo, BgDispCG, BgDispCGHook);
}
