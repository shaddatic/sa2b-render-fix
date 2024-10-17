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

static NJS_CNK_OBJECT* object_o_cc_block_mod;

static void
ObjectBlock2DisplayerMod(task* tp)
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

    njCnkModDrawObject(object_o_cc_block_mod);

    njPopMatrixEx();
}

#define ObjectBlock2    FUNC_PTR(void, __cdecl, (task*), 0x004CF370)

static hook_info HookInfoObjectBlock2[1];
static void
ObjectBlock2Hook(task* tp)
{
    FuncHookCall( HookInfoObjectBlock2, ObjectBlock2(tp) );

    if (tp->disp)
        tp->disp_shad = ObjectBlock2DisplayerMod;
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

    njCnkModDrawObject(object_o_cc_block_mod);

    njPopMatrixEx();
}

#define ObjectBlock    FUNC_PTR(void, __cdecl, (task*), 0x004CE240)
static hook_info HookInfoObjectBlock[1];
static void
ObjectBlockHook(task* tp)
{
    FuncHookCall( HookInfoObjectBlock, ObjectBlock(tp) );

    if (tp->disp)
        tp->disp_shad = ObjectBlockDisplayerMod;
}

void
CHS_CCBlockInit(void)
{
    FuncHook(HookInfoObjectBlock2, ObjectBlock2, ObjectBlock2Hook);
    FuncHook(HookInfoObjectBlock , ObjectBlock , ObjectBlockHook);

    object_o_cc_block_mod = RF_ChunkLoadObjectFile("o_cc_block_mod");
}
