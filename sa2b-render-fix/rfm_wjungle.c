#include <samt/core.h>
#include <samt/writeop.h>
#include <samt/config.h>

#include <samt/ninja/ninja.h>

#include <samt/sonic/task.h>
#include <samt/sonic/camera.h>
#include <samt/sonic/score.h>

/** Render Fix **/
#include <rf_core.h>
#include <rf_config.h>

#define byte_174AFFD                DATA_REF(uint8_t, 0x174AFFD)

#define texlist_mist_w_jungle       DATA_ARY(NJS_TEXLIST, 0xEAD30C, [1])

#define model_mist_w_jungle         DATA_ARY(NJS_CNK_MODEL, 0xEADA7C, [1])

#define TextureWJungleWaterList     DATA_ARY(NJS_TEXNAME, 0xEACD58, [10])

#define object_water_w_jungle       DATA_ARY(NJS_CNK_OBJECT, 0xEAD2BC, [1])

static void
BgDispSort(task* tp)
{
    taskwk* twp = tp->twp;

    if ((byte_174AFFD == 1 && cameraNumber == 0) || 
        (byte_174AFFD == 2 && cameraNumber == 1) ||
        (byte_174AFFD == 3))
        return;

    njFogDisable();

    njPushMatrixEx();
    NJS_POINT3* pcampos = &cameraControlWork[cameraNumber]->pos;

    njTranslate(NULL, pcampos->x, 0.0f, pcampos->z);

    if (((1 << cameraNumber) & twp->mode) != 0) // I'm not sure either
    {
        njTranslate(NULL, 0.0, -1317.0, 0.0);
    }

    NJS_TEXLIST tex;
    tex.nbTexture = 1;
    tex.textures = &TextureWJungleWaterList[(GameTimer >> 1) % 0xA];
    njSetTexture(&tex);
    njCnkDrawObject(object_water_w_jungle);

    if (((4 << cameraNumber) & twp->mode) == 0)
    {
        njSetTexture(texlist_mist_w_jungle);

        njPushMatrixEx();

        njRotateY(NULL, twp->ang.x);
        njCnkCacheDrawModel(model_mist_w_jungle);

        njPopMatrixEx();
    }

    njPopMatrixEx();

    njFogEnable();
}

void
RFM_WhiteJungleInit(void)
{
    if (RF_ConfigGetInt(CNF_FG_WATERFOG))
    {
        WriteJump(0x0062F220, BgDispSort);
    }
}
