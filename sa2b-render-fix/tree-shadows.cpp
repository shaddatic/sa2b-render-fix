#include <sa2b/core.h>
#include <sa2b/memtools.h>

#include <sa2b/ninja/ninja.h>

#include <sa2b/src/task.h>
#include <sa2b/src/set.h>
#include <sa2b/src/c_colli.h>

#include <sa2b/src/object/o_light.h>

OBJ_CONDITION objcondition_lightsw;

static void
CreateNewLightSW(TASK* tp, float posX, float posY, float posZ)
{
	NJS_POINT3 point = {};

	TASK* ctp = CreateChildTask(TELE_TWK, ObjectLightSW, tp);

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

	ctp->ocp = &objcondition_lightsw;

	njPopMatrixEx();
}

void
ObjectTreeShadows(TASK* tp)
{
	if (CheckRangeOut(tp))
		return;

	tp->exec = ObjectGenericExec;

	TASKWK* twp = tp->twp;

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
