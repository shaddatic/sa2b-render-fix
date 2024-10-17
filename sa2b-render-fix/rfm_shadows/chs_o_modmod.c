#include <sa2b/core.h>
#include <sa2b/writemem.h>
#include <sa2b/writeop.h>

/** Ninja **/
#include <sa2b/ninja/ninja.h>

/** Source **/
#include <sa2b/sonic/task.h>
#include <sa2b/sonic/debug.h>

/** Render Fix **/
#include <rf_draw.h>
#include <rf_util.h>

#define ModModModelList     DATA_ARY(NJS_CNK_MODEL*, 0x00B4D830, [3])

static void
ObjectModModDisplayer(task* tp)
{
    taskwk* const twp = tp->twp;

    njPushMatrixEx();

    njTranslateEx(&twp->pos);
    njRotateX(NULL, twp->ang.x);
    njRotateY(NULL, twp->ang.y);
    njScale(NULL, twp->scl.x + 1.0f, twp->scl.y + 1.0f, twp->scl.z + 1.0f);
    njCnkModDrawModel(ModModModelList[twp->wtimer]);

    njPopMatrixEx();
}

void
CHS_ModModInit(void)
{
    SwitchDisplayer(0x005F55AA, DISP_SHAD);
    WriteJump(0x006C7B20, ObjectModModDisplayer);
}
