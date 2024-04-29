#include <sa2b/core.h>
#include <sa2b/memutil.h>

/** Ninja **/
#include <sa2b/ninja/ninja.h>

/** Source **/
#include <sa2b/src/task.h>
#include <sa2b/src/debug.h>

/** Render Fix **/
#include <rf_draw.h>

static void
ObjectGoalringDisplayerMod(TASK* tp)
{
    TASKWK* const twp = tp->twp;

    /** Is not a Chao **/
    if (twp->ang.x % 3 != 1)
    {
        njPushMatrixEx();

        njTranslateEx(&twp->pos);
        njRotateY(NULL, twp->ang.y);
        njScale(NULL, 30.0f, 5.0f, 10.0f);

        DrawBasicShadow();

        njPopMatrixEx();
    }
}

void
CHS_GoalRingInit(void)
{
    WriteJump(0x006C7280, ObjectGoalringDisplayerMod);

    /** disp_sort func also handles lost Chao sprites, so
        should be left on. Has no impact on Goal Ring due
        to code returning if disp_shad isn't NULL **/
//  WriteRetn(0x006C6F10);             // Kill disp_sort

    /** Ensure modifier displayer is awlays active **/
    WriteNoOP(0x006C653A, 0x006C653E); // Force disp_shad
    WriteNoOP(0x006C6543, 0x006C6545); // ^
    WriteNoOP(0x006C6546, 0x006C655D); // ^

    KillCall(0x006C6519); // Kill SetStencilInfo
}
