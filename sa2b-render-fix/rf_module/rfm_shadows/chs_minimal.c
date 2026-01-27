#include <samt/core.h>
#include <samt/writemem.h>
#include <samt/funchook.h>

/** Ninja **/
#include <samt/ninja/ninja.h>

/** Source **/
#include <samt/sonic/task.h>
#include <samt/sonic/debug.h>

/** Render Fix **/
#include <rf_ninja.h>

/** RF Util **/
#include <rfu_draw.h>

#define dword_1945E08   DATA_REF(int, 0x1945E08)

static void
MinimalDisplayerMod(task* tp)
{
    taskwk* const twp = tp->twp;
    anywk*  const awp = tp->awp;

    const uint32_t mode = awp->work.ul[0];

    if (mode == 0)
    {
        njPushMatrixEx();

        const Angle mot_ang = awp->work.sl[3];

        float trns_x = njSin(mot_ang) * twp->scl.x + twp->pos.x;
        float trns_z = njCos(mot_ang) * twp->scl.x + twp->pos.z;

        njTranslate(NULL, trns_x, twp->pos.y, trns_z);
        njRotateY(NULL, awp->work.ul[3] + 0x4000);
    }
    else
    {
        if (mode == 2 || awp[1].work.ub[4] & 1)
            return;

        njPushMatrixEx();

        njTranslateEx(&twp->pos);
        njRotateY(NULL, twp->ang.y);
    }

    njScale(NULL, 1.4f, 1.4f, 1.4f);

    if (dword_1945E08 != 3)
        njRotateZ(NULL, 0x8000);

    njTranslate(NULL, 0.0f, 2.0f, 0.0f);
    njScale(NULL, 1.2f, 0.5f, 1.8f);
    DrawBasicShadow();

    njPopMatrixEx();
}

#define ObjectMinimal       FUNC_PTR(void, __cdecl, (task*), 0x0048ADE0)

static mt_hookinfo HookInfoObjectMinimal[1];
static void
ObjectMinimalHook(task* tp)
{
    mtHookInfoCall( HookInfoObjectMinimal, ObjectMinimal(tp) );

    tp->disp_shad = MinimalDisplayerMod;
}

#define MinimalCreate       FUNC_PTR(task*, __cdecl, (f32, f32, f32, int, uint32_t), 0x0048AAD0)

static mt_hookinfo HookInfoMinimalCreate[1];
static task*
MinimalCreateHook(f32 posX, f32 posY, f32 posZ, int num, uint32_t flag)
{
    task* minitp;

    mtHookInfoCall( HookInfoMinimalCreate, minitp = MinimalCreate(posX, posY, posZ, num, flag) );

    minitp->disp_shad = MinimalDisplayerMod;

    return minitp;
}

void
CHS_MinimalInit(void)
{
    mtHookFunc(HookInfoObjectMinimal, ObjectMinimal, ObjectMinimalHook);
    mtHookFunc(HookInfoMinimalCreate, MinimalCreate, MinimalCreateHook);
}
