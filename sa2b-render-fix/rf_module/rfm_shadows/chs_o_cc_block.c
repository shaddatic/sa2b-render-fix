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
ObjectBlock2Shadow(task* tp)
{
    taskwk* const twp = tp->twp;
    anywk*  const awp = tp->awp;

    if ((twp->ang.z & 1) == 0)
        return;

    njPushMatrixEx();

    njTranslateEx(&twp->pos);
    njRotateY(NULL, twp->ang.y & 0xFF00);

    const float scl = twp->scl.x + 1.0f;

    njScale(NULL, scl, scl, scl);

    njCnkModDrawObject(object_cc_block_mod);

    njPopMatrixEx();
}

#define ObjectBlock2    FUNC_PTR(void, __cdecl, (task*), 0x004CF370)

static mt_hookinfo HookInfoObjectBlock2[1];
static void
ObjectBlock2Hook(task* tp)
{
    mtHookInfoCall( HookInfoObjectBlock2, ObjectBlock2(tp) );

    if (tp->disp)
        tp->disp_shad = ObjectBlock2Shadow;
}

static void
ObjectBlockDisplayerMod(task* tp)
{
    taskwk* const twp = tp->twp;
    anywk* const awp = tp->awp;

    if ((twp->ang.z & 2) == 0)
        return;

    njPushMatrixEx();

    njTranslateEx(&twp->pos);
    njRotateY(NULL, twp->ang.y & 0xFF00);

    const float scl = twp->scl.x + 1.0f;

    njScale(NULL, scl, scl, scl);

    njCnkModDrawObject(object_cc_block_mod);

    njPopMatrixEx();
}

#define ObjectBlock    FUNC_PTR(void, __cdecl, (task*), 0x004CE240)
static mt_hookinfo HookInfoObjectBlock[1];
static void
ObjectBlockHook(task* tp)
{
    mtHookInfoCall( HookInfoObjectBlock, ObjectBlock(tp) );

    if (tp->disp)
        tp->disp_shad = ObjectBlockDisplayerMod;
}

void
CHS_CCBlockInit(void)
{
    mtHookFunc(HookInfoObjectBlock2, ObjectBlock2, ObjectBlock2Hook);
    mtHookFunc(HookInfoObjectBlock , ObjectBlock , ObjectBlockHook);
}
