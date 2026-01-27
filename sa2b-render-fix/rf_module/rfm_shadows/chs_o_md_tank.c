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
#include <rf_samdl.h>
#include <rf_ninja.h>
#include <rf_njcnk.h>               /* ninja chunk draw                                         */

static NJS_CNK_OBJECT* object_o_md_contbox_mod;

static void
ObjectMDContainerBoxDisplayerMod(task* tp)
{
    taskwk* const twp = tp->twp;

    if (twp->smode)
        return;

    njPushMatrixEx();

    njTranslateEx(&twp->pos);
    njRotateY(NULL, twp->ang.y);

    njCnkModDrawObject(object_o_md_contbox_mod);

    njPopMatrixEx();
}

#define ObjectTank      FUNC_PTR(void, __cdecl, (task*), 0x005C37A0)

static mt_hookinfo HookInfoObjectTank[1];
static void
ObjectTankHook(task* tp)
{
    mtHookInfoCall( HookInfoObjectTank, ObjectTank(tp) );

    if (tp->disp)
        tp->disp_shad = ObjectMDContainerBoxDisplayerMod;
}

void
CHS_TankInit(void)
{
    mtHookFunc(HookInfoObjectTank, ObjectTank, ObjectTankHook);

    object_o_md_contbox_mod = RF_GetCnkObject("object/md_tank_mod.sa2mdl");
}
