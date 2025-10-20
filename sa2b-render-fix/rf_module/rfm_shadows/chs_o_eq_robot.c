#include <samt/core.h>
#include <samt/writemem.h>
#include <samt/writeop.h>

/** Ninja **/
#include <samt/ninja/ninja.h>

/** Source **/
#include <samt/sonic/task.h>
#include <samt/sonic/debug.h>

/** Render Fix **/
#include <rf_ninja.h>

static const void* const ObjectRobotModifyVList_p = (void*)0x00693AC0;
void
ModModifyVList(Angle angz, Angle angx, Sint32* pVList)
{
    __asm
    {
        push [pVList]
        mov ecx, [angx]
        mov eax, [angz]

        call ObjectRobotModifyVList_p

        add esp, 4
    }
}

#define object_o_eq_robot_mod       DATA_ARY(NJS_CNK_OBJECT, 0x00C42144, [1])

static void
ObjectRobotDisplayerMod(task* tp)
{
    taskwk* const twp = tp->twp;
    anywk*  const awp = tp->awp;

    if (!awp[10].work.ul[3])
        return;

    njPushMatrixEx();

    NJS_MATRIX* p_mat = (NJS_MATRIX*)awp[5].work.ul[0];

    if (!p_mat)
        p_mat = _nj_curr_matrix_;

    njMultiMatrix(NULL, p_mat);

    njRotateZ(NULL, -twp->ang.z);
    njRotateX(NULL, -twp->ang.x);
    njRotateY(NULL, 0x8000);

    NJS_CNK_MODEL* p_model = object_o_eq_robot_mod->model;

    const float model_r = p_model->r;

    p_model->r *= 1.2f;

    njTranslate(NULL, 0.0f, -14.0f, 0.0f);
    njScale(NULL, 1.0f, 1.2f, 1.0f);

    if (*(uint16_t*)p_model->vlist == 34)
        ModModifyVList(twp->ang.z, twp->ang.x, p_model->vlist);

    njCnkModDrawObject(object_o_eq_robot_mod);

    p_model->r = model_r;

    njPopMatrixEx();
}

#define ObjectRobotInit     FUNC_PTR(void, __cdecl, (task*), 0x00691720)

static void
ObjectRobotInitHook(task* tp)
{
    ObjectRobotInit(tp);
    tp->disp_shad = ObjectRobotDisplayerMod;
}

void
CHS_EggQuatersRobotInit(void)
{
    KillCall(0x00691614); // og ObjectRobotModifyVList
    WriteCall(0x00690DB4, ObjectRobotInitHook);
}
