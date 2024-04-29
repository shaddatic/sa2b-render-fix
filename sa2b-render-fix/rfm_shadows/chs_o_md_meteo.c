#include <sa2b/core.h>
#include <sa2b/memutil.h>
#include <sa2b/funchook.h>

/** Ninja **/
#include <sa2b/ninja/ninja.h>

/** Source **/
#include <sa2b/src/task.h>
#include <sa2b/src/debug.h>

/** Render Fix **/
#include <rf_file.h>
#include <rf_draw.h>

static NJS_CNK_OBJECT* object_o_md_meteo_mod;

static void
ObjectMDFireBallDisplayerMod(TASK* tp)
{
    TASKWK* const twp = tp->twp;

    njPushMatrixEx();

    njTranslateEx(&twp->pos);
    njRotateY(NULL, twp->ang.y);

    njCnkModDrawObject(object_o_md_meteo_mod);

    njPopMatrixEx();
}

#define ObjectMDFireBall    FuncPtr(void, __cdecl, (TASK*), 0x005C1280)

static hook_info* HookInfoObjectMDFireBall;
static void
ObjectMDFireBallHook(TASK* tp)
{
    FuncHookCall(HookInfoObjectMDFireBall, ObjectMDFireBall(tp));

    tp->disp_shad = ObjectMDFireBallDisplayerMod;
}

static void
ObjectMeteoBigDisplayerMod(TASK* tp)
{
    TASKWK* const twp = tp->twp;

    njPushMatrixEx();

    njTranslateEx(&twp->pos);
    njCnkModDrawObject(object_o_md_meteo_mod);

    njPopMatrixEx();
}

void
CHS_MeteoBigInit(void)
{
    HookInfoObjectMDFireBall = FuncHook(ObjectMDFireBall, ObjectMDFireBallHook);

    WriteJump(0x005C5120, ObjectMeteoBigDisplayerMod);
    KillCall(0x005C4E04); // Kill SetStencilInfo

    object_o_md_meteo_mod = RF_ChunkLoadObjectFile("o_md_meteo_mod");
}
