/********************************/
/*  Includes                    */
/********************************/
/****** SAMT ************************************************************************************/
#include <samt/core.h>              /* core                                                     */

/****** Ninja ***********************************************************************************/
#include <samt/ninja/ninja.h>       /* ninja                                                    */

/****** Game ************************************************************************************/
#include <samt/sonic/task.h>        /* task                                                     */
#include <samt/sonic/set.h>         /* object                                                   */

/****** Object **********************************************************************************/
#include <samt/sonic/object/o_light.h> /* light/shadow object                                   */

/****** Render Fix ******************************************************************************/
#include <rf_core.h>                /* core                                                     */

/****** Config **********************************************************************************/
#include <cnf.h>                    /* config get                                               */

/****** Self ************************************************************************************/
#include <rf_module/rfm_internal.h> /* parent & siblings                                        */

/********************************/
/*  Macro                       */
/********************************/
/****** Replace Object **************************************************************************/
#define REPL_OBJFUNC(iel, ix, fn)       ((OBJ_ITEMENTRY*)(iel))[(ix)].fnExec = (EDIT_FUNC)(fn)

/********************************/
/*  Data                        */
/********************************/
/****** Object Condition ************************************************************************/
static OBJ_CONDITION objcond_treelightsw;

/********************************/
/*  Source                      */
/********************************/
/****** Task ************************************************************************************/
static void
CreateNewLightSW(task* tp, float posX, float posY, float posZ)
{
    NJS_POINT3 point = {
        .x = 0.0f,
        .y = 0.0f,
        .z = 0.0f
    };

    task* ctp = CreateChildTask(TELE_TWK, ObjectLightSW, tp);

    njPushMatrixEx();

    njTranslate(NULL, posX, posY, posZ);

    njCalcPointEx(&point, &point);

    ctp->twp->pos.x = point.x;
    ctp->twp->pos.y = point.y + 24.0f;
    ctp->twp->pos.z = point.z;

    ctp->twp->scl.x = 24.0f;
    ctp->twp->scl.y = 32.0f;
    ctp->twp->scl.z = 24.0f;

    ctp->twp->smode = 1;

    ctp->ocp = &objcond_treelightsw;

    njPopMatrixEx();
}

static void
ObjectTreeShadows(task* tp)
{
    if (CheckRangeOut(tp))
        return;

    tp->exec = ObjectGenericExec;

    taskwk* twp = tp->twp;

    njPushMatrix(&_nj_unit_matrix_);

    njTranslateEx(&twp->pos);
    njRotateY(0, twp->ang.y);

    CreateNewLightSW(tp, 70.0f, -165.0f, 240.0f);
    CreateNewLightSW(tp, 70.0f, 0.0f, 0.0f);
    CreateNewLightSW(tp, 70.0f, 165.0f, -240.0f);
    CreateNewLightSW(tp, -70.0f, -165.0f, 240.0f);
    CreateNewLightSW(tp, -70.0f, 0.0f, 0.0f);
    CreateNewLightSW(tp, -70.0f, 165.0f, -240.0f);

    njPopMatrixEx();
}

/****** Init ************************************************************************************/
void
RFM_CityEscapeInit(void)
{
    // restore shadow areas
    REPL_OBJFUNC(0x0109E830, 58, ObjectLightSW);     // Light SW          (City Escape)
    REPL_OBJFUNC(0x0109E830, 69, ObjectTreeShadows); // ObjectTreeShadows (City Escape)
}
