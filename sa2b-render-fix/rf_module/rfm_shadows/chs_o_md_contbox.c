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
ObjectContainerBoxShadow(task* tp)
{
    taskwk* const twp = tp->twp;

    njPushMatrixEx();

    njTranslateEx(&twp->pos);
    njRotateY(NULL, twp->ang.y);

    njCnkModDrawObject(object_md_contbox_mod);

    njPopMatrixEx();
}

#define ObjectMDContainerBox    FUNC_PTR(void, __cdecl, (task*), 0x005C3B50)

static mt_hookinfo HookInfoObjectMDContainerBox[1];
static void
ObjectMDContainerBoxHook(task* tp)
{
    mtHookInfoCall( HookInfoObjectMDContainerBox, ObjectMDContainerBox(tp) );

    if (tp->disp)
        tp->disp_shad = ObjectContainerBoxShadow;
}

void
CHS_MDContainerBoxInit(void)
{
    mtHookFunc(HookInfoObjectMDContainerBox, ObjectMDContainerBox, ObjectMDContainerBoxHook);
}
