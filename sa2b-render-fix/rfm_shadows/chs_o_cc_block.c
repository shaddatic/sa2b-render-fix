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

static NJS_CNK_OBJECT* object_o_cc_block_mod;

static void
ObjectBlock2DisplayerMod(TASK* tp)
{
    TASKWK* const twp = tp->twp;
    ANYWK*  const awp = tp->awp;

    if ((twp->ang.z & 1) == 0)
        return;

    njPushMatrixEx();

    njTranslateEx(&twp->pos);
    njRotateY(NULL, twp->ang.y & 0xFF00);

    const float scl = twp->scl.x + 1.0f;

    njScale(NULL, scl, scl, scl);

    njCnkModDrawObject(object_o_cc_block_mod);

    njPopMatrixEx();
}

#define ObjectBlock2    FuncPtr(void, __cdecl, (TASK*), 0x004CF370)

static hook_info* HookInfoObjectBlock2;
static void
ObjectBlock2Hook(TASK* tp)
{
    FuncHookCall( HookInfoObjectBlock2, ObjectBlock2(tp) );

    if (tp->disp)
        tp->disp_shad = ObjectBlock2DisplayerMod;
}

static void
ObjectBlockDisplayerMod(TASK* tp)
{
    TASKWK* const twp = tp->twp;
    ANYWK* const awp = tp->awp;

    if ((twp->ang.z & 2) == 0)
        return;

    njPushMatrixEx();

    njTranslateEx(&twp->pos);
    njRotateY(NULL, twp->ang.y & 0xFF00);

    const float scl = twp->scl.x + 1.0f;

    njScale(NULL, scl, scl, scl);

    njCnkModDrawObject(object_o_cc_block_mod);

    njPopMatrixEx();
}

#define ObjectBlock    FuncPtr(void, __cdecl, (TASK*), 0x004CE240)
static hook_info* HookInfoObjectBlock;
static void
ObjectBlockHook(TASK* tp)
{
    FuncHookCall( HookInfoObjectBlock, ObjectBlock(tp) );

    if (tp->disp)
        tp->disp_shad = ObjectBlockDisplayerMod;
}

void
CHS_CCBlockInit()
{
    HookInfoObjectBlock2 = FuncHook(ObjectBlock2, ObjectBlock2Hook);
    HookInfoObjectBlock  = FuncHook(ObjectBlock , ObjectBlockHook);

    object_o_cc_block_mod = RF_ChunkLoadObjectFile("o_cc_block_mod");
}
