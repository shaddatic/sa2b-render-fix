#include <samt/core.h>
#include <samt/writemem.h>
#include <samt/writeop.h>
#include <samt/funchook.h>

/** Ninja **/
#include <samt/ninja/ninja.h>

/** Source **/
#include <samt/sonic/task.h>
#include <samt/sonic/debug.h>

/** Render Fix **/
#include <rf_ninja.h>

/** RF Util **/
#include <rfu_draw.h>

#define ObjectSearchBox     FUNC_PTR(void, __cdecl, (task*), 0x006E7F60)

static void
ObjectSearchBoxDisplayerMod(task* tp)
{
    njPushMatrixEx();

    const float* sbwp = (const float*)tp->mwp;

    njTranslate(NULL, sbwp[3], sbwp[4] + 0.2f, sbwp[5]);
    njScale(NULL, 3.0f, 1.0f, 3.0f);

    DrawBasicShadow();

    njPopMatrixEx();
}

static mt_hookinfo HookInfoObjectSearchBox[1];

static void
ObjectSearchBoxHook(task* tp)
{
    mtHookInfoSwitch(HookInfoObjectSearchBox, OFF);
    ObjectSearchBox(tp);
    mtHookInfoSwitch(HookInfoObjectSearchBox, ON);

    if (tp->disp)
        tp->disp_shad = ObjectSearchBoxDisplayerMod;
}

void
CHS_SearchBoxInit(void)
{
    WriteRetn(0x006E7E90);
    FuncHook(HookInfoObjectSearchBox, ObjectSearchBox, ObjectSearchBoxHook);
}
