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

static NJS_CNK_OBJECT* object_o_md_contbox_mod;

static void
ObjectMDContainerBoxDisplayerMod(task* tp)
{
    taskwk* const twp = tp->twp;

    njPushMatrixEx();

    njTranslateEx(&twp->pos);
    njRotateY(NULL, twp->ang.y);

    njCnkModDrawObject(object_o_md_contbox_mod);

    njPopMatrixEx();
}

#define ObjectMDContainerBox    FUNC_PTR(void, __cdecl, (task*), 0x005C3B50)

static hook_info HookInfoObjectMDContainerBox[1];
static void
ObjectMDContainerBoxHook(task* tp)
{
    FuncHookCall( HookInfoObjectMDContainerBox, ObjectMDContainerBox(tp) );

    if (tp->disp)
        tp->disp_shad = ObjectMDContainerBoxDisplayerMod;
}

void
CHS_MDContainerBoxInit(void)
{
    FuncHook(HookInfoObjectMDContainerBox, ObjectMDContainerBox, ObjectMDContainerBoxHook);

    object_o_md_contbox_mod = RF_ChunkLoadObjectFile("object/md_contbox_mod");
}
