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
#include <rf_draw.h>

#define ObjectSearchBox     FUNC_PTR(void, __cdecl, (TASK*), 0x006E7F60)

static void
ObjectSearchBoxDisplayerMod(TASK* tp)
{
    njPushMatrixEx();

    const float* sbwp = (const float*)tp->mwp;

    njTranslate(NULL, sbwp[3], sbwp[4] + 0.2f, sbwp[5]);
    njScale(NULL, 3.0f, 1.0f, 3.0f);

    DrawBasicShadow();

    njPopMatrixEx();
}

static hook_info* HookInfoObjectSearchBox;

static void
ObjectSearchBoxHook(TASK* tp)
{
    FuncHookRestore(HookInfoObjectSearchBox);
    ObjectSearchBox(tp);
    FuncHookRehook(HookInfoObjectSearchBox);

    if (tp->disp)
        tp->disp_shad = ObjectSearchBoxDisplayerMod;
}

void
CHS_SearchBoxInit(void)
{
    WriteRetn(0x006E7E90);
    HookInfoObjectSearchBox = FuncHook(ObjectSearchBox, ObjectSearchBoxHook);
}
