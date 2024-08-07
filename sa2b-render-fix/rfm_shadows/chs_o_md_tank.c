#include <sa2b/core.h>
#include <sa2b/writemem.h>
#include <sa2b/funchook.h>

/** Ninja **/
#include <sa2b/ninja/ninja.h>

/** Source **/
#include <sa2b/sonic/task.h>
#include <sa2b/sonic/debug.h>

/** Render Fix **/
#include <rf_file.h>
#include <rf_draw.h>

static NJS_CNK_OBJECT* object_o_md_contbox_mod;

static void
ObjectMDContainerBoxDisplayerMod(TASK* tp)
{
    TASKWK* const twp = tp->twp;

    if (twp->smode)
        return;

    njPushMatrixEx();

    njTranslateEx(&twp->pos);
    njRotateY(NULL, twp->ang.y);

    njCnkModDrawObject(object_o_md_contbox_mod);

    njPopMatrixEx();
}

#define ObjectTank      FUNC_PTR(void, __cdecl, (TASK*), 0x005C37A0)

static hook_info* HookInfoObjectTank;
static void
ObjectTankHook(TASK* tp)
{
    FuncHookCall( HookInfoObjectTank, ObjectTank(tp) );

    if (tp->disp)
        tp->disp_shad = ObjectMDContainerBoxDisplayerMod;
}

void
CHS_TankInit(void)
{
    HookInfoObjectTank = FuncHook(ObjectTank, ObjectTankHook);

    object_o_md_contbox_mod = RF_ChunkLoadObjectFile("o_md_tank_mod");
}
