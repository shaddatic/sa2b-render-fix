#include <sa2b/core.h>

#include <sa2b/shinobi/sg_maloc.h>
#include <sa2b/src/task.h>

#include <tools.h>

TaskFuncPtr(EnemyExplosionExecutor, 0x004F7020);
TaskFuncPtr(EnemyExplosionDisplayer, 0x004F6350);

FuncPtr(void, __cdecl, sub_4F70E0, (), 0x4F70E0);

static TASK*
EnemyExplosionCreateTask()
{
    TASK* tp = CreateElementalTask(TELE_TWK, LEV_3, EnemyExplosionExecutor, "exec");

    tp->awp = (anywk*)syCalloc(1, 80);

    return tp;
}

static void __cdecl
EnemyExplosionCreate(NJS_POINT3* pPos, char a2)
{
    TASK* tp = EnemyExplosionCreateTask();

    if (!tp)
        return;

    ANYWK* v3 = tp->awp;
    v3->work.ub[1] = a2;
    v3->work.f[1] = pPos->x;
    v3->work.f[2] = pPos->y;
    v3->work.f[3] = pPos->z;

    float* v4 = tp->awp->work.f;
    v4[14] = 1.0f;
    v4[4] = 0.0f;
    v4[9] = 0.34f;

    tp->disp_sort = EnemyExplosionDisplayer;

    tp->twp->pos = *pPos;

    sub_4F70E0();
}

__declspec(naked)
static void
__EnemyExplosionCreate()
{
    __asm
    {
        push[esp + 4]
        push esi
        call EnemyExplosionCreate
        pop esi
        add esp, 4
        retn
    }
}

void
FixExplosionSorting()
{
    SwitchDisplayer(0x004F715C, DISP_SORT);
    WriteJump(0x004F7120, __EnemyExplosionCreate);

    SwitchDisplayer(0x004C6C2F, DISP_SORT); // Golem Explosion
}