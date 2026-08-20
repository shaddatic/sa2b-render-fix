#include <samt/core.h>
#include <samt/writemem.h>
#include <samt/funchook.h>

/** Ninja **/
#include <samt/ninja/ninja.h>

/** Source **/
#include <samt/sonic/task.h>
#include <samt/sonic/debug.h>

/** Render Fix **/
#include <rf_core.h>                /* core                                                     */
#include <rf_model.h>
#include <rf_ninja.h>
#include <rf_njcnk.h>               /* ninja chunk draw                                         */
#include <rf_shadow.h>

void
ObjectTankShadow(task* tp)
{
    taskwk* const twp = tp->twp;

    if (twp->smode)
        return;

    njPushMatrixEx();

    njTranslateEx(&twp->pos);
    njRotateY(NULL, twp->ang.y);

    njCnkModDrawObject(object_md_tank_mod);

    njPopMatrixEx();
}

#define ObjectTank      FUNC_PTR(void, __cdecl, (task*), 0x005C37A0)

static mt_hookinfo HookInfoObjectTank[1];
static void
ObjectTankHook(task* tp)
{
    mtHookInfoCall( HookInfoObjectTank, ObjectTank(tp) );

    if (tp->disp)
        tp->disp_shad = ObjectTankShadow;
}

void
CHS_TankInit(void)
{
    mtHookFunc(HookInfoObjectTank, ObjectTank, ObjectTankHook);
}
