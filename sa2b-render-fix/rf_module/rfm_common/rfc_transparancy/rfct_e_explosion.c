#include <samt/core.h>
#include <samt/writeop.h>

#include <samt/shinobi/sg_maloc.h>

#include <samt/sonic/task.h>

#include <rf_util.h>

#define EnemyExplosionExecutor      FUNC_PTR(void, __cdecl, (task*), 0x004F7020)
#define EnemyExplosionDisplayer     FUNC_PTR(void, __cdecl, (task*), 0x004F6350)

#define sub_4F70E0      FUNC_PTR(void, __cdecl, (), 0x4F70E0)

static task*
EnemyExplosionCreateTask(void)
{
    task* tp = CreateElementalTask(IM_TWK, LEV_3, EnemyExplosionExecutor, "exec");

    tp->awp = syCalloc(1, 80);

    return tp;
}

static void __cdecl
EnemyExplosionCreate(NJS_POINT3* pPos, char a2)
{
    task* tp = EnemyExplosionCreateTask();

    if (!tp)
        return;

    anywk* v3 = tp->awp;
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
__EnemyExplosionCreate(void)
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
RFCT_ExplosionInit(void)
{
    SwitchDisplayer(0x004F715C, DISP_SORT);
    WriteJump(0x004F7120, __EnemyExplosionCreate);

    SwitchDisplayer(0x004C6C2F, DISP_SORT); // Golem Explosion
}
