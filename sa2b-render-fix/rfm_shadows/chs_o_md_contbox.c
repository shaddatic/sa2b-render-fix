#include <samt/core.h>
#include <samt/writemem.h>
#include <samt/funchook.h>

/** Ninja **/
#include <samt/ninja/ninja.h>

/** Source **/
#include <samt/sonic/task.h>
#include <samt/sonic/debug.h>

/** Render Fix **/
#include <rf_file.h>
#include <rf_ninja.h>

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

static mt_hookinfo HookInfoObjectMDContainerBox[1];
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
