#include <sa2b/core.h>
#include <sa2b/memutil.h>
#include <sa2b/funchook.h>

/** Ninja **/
#include <sa2b/ninja/ninja.h>

/** Source **/
#include <sa2b/src/task.h>
#include <sa2b/src/debug.h>

/** Render Fix **/
#include <rf_draw.h>

#define dword_1945E08   DataRef(int, 0x1945E08)

static void
MinimalDisplayerMod(TASK* tp)
{
    TASKWK* const twp = tp->twp;
    ANYWK*  const awp = tp->awp;

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

#define ObjectMinimal       FuncPtr(void, __cdecl, (TASK*), 0x0048ADE0)

static hook_info* HookInfoObjectMinimal;
static void
ObjectMinimalHook(TASK* tp)
{
    FuncHookCall( HookInfoObjectMinimal, ObjectMinimal(tp) );

    tp->disp_shad = MinimalDisplayerMod;
}

#define MinimalCreate       FuncPtr(TASK*, __cdecl, (float32_t, float32_t, float32_t, int, uint32_t), 0x0048AAD0)

static hook_info* HookInfoMinimalCreate;
static TASK*
MinimalCreateHook(float32_t posX, float32_t posY, float32_t posZ, int num, uint32_t flag)
{
    TASK* minitp;

    FuncHookCall( HookInfoMinimalCreate, minitp = MinimalCreate(posX, posY, posZ, num, flag) );

    minitp->disp_shad = MinimalDisplayerMod;

    return minitp;
}

void
CHS_MinimalInit(void)
{
    HookInfoObjectMinimal = FuncHook(ObjectMinimal, ObjectMinimalHook);
    HookInfoMinimalCreate = FuncHook(MinimalCreate, MinimalCreateHook);
}
