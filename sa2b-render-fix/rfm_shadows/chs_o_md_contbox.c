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

static NJS_CNK_OBJECT* object_o_md_contbox_mod;

static void
ObjectMDContainerBoxDisplayerMod(TASK* tp)
{
    TASKWK* const twp = tp->twp;

    njPushMatrixEx();

    njTranslateEx(&twp->pos);
    njRotateY(NULL, twp->ang.y);

    njCnkModDrawObject(object_o_md_contbox_mod);

    njPopMatrixEx();
}

#define ObjectMDContainerBox    FuncPtr(void, __cdecl, (TASK*), 0x005C3B50)

static hook_info* HookInfoObjectMDContainerBox;
static void
ObjectMDContainerBoxHook(TASK* tp)
{
    FuncHookCall( HookInfoObjectMDContainerBox, ObjectMDContainerBox(tp) );

    if (tp->disp)
        tp->disp_shad = ObjectMDContainerBoxDisplayerMod;
}

void
CHS_MDContainerBoxInit(void)
{
    HookInfoObjectMDContainerBox = FuncHook(ObjectMDContainerBox, ObjectMDContainerBoxHook);

    object_o_md_contbox_mod = RF_ChunkLoadObjectFile("o_md_contbox_mod");
}
