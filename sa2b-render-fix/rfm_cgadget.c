#include <sa2b/core.h>
#include <sa2b/funchook.h>

/** Ninja **/
#include <sa2b/ninja/ninja.h>

/** Game **/
#include <sa2b/sonic/task.h>

/** Render Fix **/
#include <rf_core.h>
#include <rf_config.h>

static hook_info BgDispCGHookInfo[1];

#define BgDispCG    FUNC_PTR(void, __cdecl, (task*), 0x00771DD0)

static void
BgDispCGHook(task* tp)
{
    FuncHookCall( BgDispCGHookInfo, BgDispCG(tp) );

    njFogEnable();
}

void
RFM_CrazyGadgetInit(void)
{
     FuncHook(BgDispCGHookInfo, BgDispCG, BgDispCGHook);
}
