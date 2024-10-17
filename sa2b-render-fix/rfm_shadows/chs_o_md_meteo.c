#include <sa2b/core.h>
#include <sa2b/writemem.h>
#include <sa2b/writeop.h>
#include <sa2b/funchook.h>

/** Ninja **/
#include <sa2b/ninja/ninja.h>

/** Source **/
#include <sa2b/sonic/task.h>
#include <sa2b/sonic/debug.h>

/** Render Fix **/
#include <rf_file.h>
#include <rf_draw.h>

static NJS_CNK_OBJECT* object_o_md_meteo_mod;

static void
ObjectMDFireBallDisplayerMod(task* tp)
{
    taskwk* const twp = tp->twp;

    njPushMatrixEx();

    njTranslateEx(&twp->pos);
    njRotateY(NULL, twp->ang.y);

    njCnkModDrawObject(object_o_md_meteo_mod);

    njPopMatrixEx();
}

#define ObjectMDFireBall    FUNC_PTR(void, __cdecl, (task*), 0x005C1280)

static hook_info HookInfoObjectMDFireBall[1];
static void
ObjectMDFireBallHook(task* tp)
{
    FuncHookCall(HookInfoObjectMDFireBall, ObjectMDFireBall(tp));

    tp->disp_shad = ObjectMDFireBallDisplayerMod;
}

static void
ObjectMeteoBigDisplayerMod(task* tp)
{
    taskwk* const twp = tp->twp;

    njPushMatrixEx();

    njTranslateEx(&twp->pos);
    njCnkModDrawObject(object_o_md_meteo_mod);

    njPopMatrixEx();
}

void
CHS_MeteoBigInit(void)
{
    FuncHook(HookInfoObjectMDFireBall, ObjectMDFireBall, ObjectMDFireBallHook);

    WriteJump(0x005C5120, ObjectMeteoBigDisplayerMod);
    KillCall(0x005C4E04); // Kill SetStencilInfo

    object_o_md_meteo_mod = RF_ChunkLoadObjectFile("o_md_meteo_mod");
}
