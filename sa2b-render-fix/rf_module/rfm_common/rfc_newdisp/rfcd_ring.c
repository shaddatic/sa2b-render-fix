/************************/
/*  Includes            */
/************************/
/****** Core Toolkit ****************************************************************/
#include <samt/core.h>          /* core                                             */
#include <samt/writeop.h>       /* writejump                                        */

/****** Ninja ***********************************************************************/
#include <samt/ninja/ninja.h>   /* ninja                                            */

/****** Game ************************************************************************/
#include <samt/sonic/task.h>    /* task                                             */

/****** Render Fix ******************************************************************/
#include <rf_core.h>            /* core                                             */
#include <rf_njcnk.h>           /* emulated njcnk draw functions                    */
#include <rf_mdlutil.h>         /* change strip flag                                */
#include <rf_config.h>          /* config                                           */

/****** Self ************************************************************************/
#include <rf_module/rfm_common/rfc_newdisp/rfcd_internal.h> /* parent & siblings    */

typedef struct
{
    NJS_CNK_OBJECT  object;
    Angle3          shadow_ang;
    f32             shadow_posy;
}
RING_OBJECT;

#define DrawThingBitMask        DATA_REF(s8 , 0x0174AFFD)
#define DisableObjectFog        DATA_REF(s32, 0x01AEFE64)

#define texlist_ring            DATA_ARY(NJS_TEXLIST, 0x00B56360, [1])
#define texlist_ringshadow      DATA_ARY(NJS_TEXLIST, 0x00B56374, [1])

#define RingObjects             DATA_REF(RING_OBJECT*, 0x01AEFD80)

#define object_ring0            DATA_ARY(NJS_CNK_OBJECT, 0x00B570FC, [1])
#define object_ring1            DATA_ARY(NJS_CNK_OBJECT, 0x00B56BEC, [1])
#define object_ring2            DATA_ARY(NJS_CNK_OBJECT, 0x00B56764, [1])

#define object_ringshadow       DATA_ARY(NJS_CNK_OBJECT, 0x00B58114, [1])

/************************/
/*  Source              */
/************************/
/****** Static **********************************************************************/
static void
CNK_RingModelDisp(const task* tp)
{
    if (DrawThingBitMask)
        return;

    if (DisableObjectFog)
        njFogDisable();

    njSetTexture(texlist_ring);

    for (RING_OBJECT* p_ring = RingObjects; p_ring; p_ring = (RING_OBJECT*)p_ring->object.sibling )
    {
        if (p_ring->object.evalflags & NJD_EVAL_HIDE)
            continue;

        NJS_POINT3 calc_pos;

        njCalcPoint(NULL, (NJS_POINT3*)p_ring->object.pos, &calc_pos);

        const f32 depth = -calc_pos.z;

        if (depth <= -10.f)
            continue;

        njPushMatrixEx();

        njTranslateV(NULL, (NJS_POINT3*)p_ring->object.pos);

        njRotateY(NULL, p_ring->object.ang[1]);

        NJS_CNK_MODEL* p_model;

        if (depth < 65.f)
            p_model = object_ring0->model;
        else if (depth < 130.f)
            p_model = object_ring1->model;
        else
            p_model = object_ring2->model;

        njCnkDirectDrawModel(p_model);

        njPopMatrixEx();
    }

    njSetTexture(texlist_ringshadow);

    for (RING_OBJECT* p_ring = RingObjects; p_ring; p_ring = (RING_OBJECT*)p_ring->object.sibling )
    {
        if (p_ring->shadow_posy == -1000000.f || p_ring->shadow_posy == 1000000.f)
            continue;

        njPushMatrixEx();

        njTranslate(NULL, p_ring->object.pos[0], p_ring->shadow_posy, p_ring->object.pos[2]);

        njRotateZ(NULL, p_ring->shadow_ang.z);
        njRotateX(NULL, p_ring->shadow_ang.x);
        njRotateY(NULL, p_ring->shadow_ang.y);

        njTranslate(NULL, 0.f, 0.5f, 0.f);

        njScale(NULL, 0.8f, 1.f, 0.4f);

        njCnkDirectDrawModel(object_ringshadow->model);

        njPopMatrixEx();
    }

    if (DisableObjectFog)
        njFogEnable();
}

static void
CNK_DrawRingShadow(void)
{
    njSetTexture(texlist_ringshadow);

    njPushMatrixEx();
    {
        njScale(NULL, 0.2f, 1.f, 0.2f);

        njCnkDirectDrawModel(object_ringshadow->model);
    }
    njPopMatrixEx();
}

/****** Init ************************************************************************/
void
RFCD_RingInit(void)
{
    WriteJump(0x006C2AF0, CNK_RingModelDisp);
    WriteRetn(0x006C2C70);            // disp_dely
    WriteNOP(0x006C2EA0, 0x006C2EA7); // tp->disp_dely = func;

    WriteJump(0x006BD500, CNK_DrawRingShadow);

    if ( RF_ConfigGetInt(CNF_MISC_DCRING) )
    {
        RF_CnkModelMaterialDiffuse(object_ringshadow->model, -1, 0xFF, 0xFF, 0xFF, 0xFF);
    }
}
