#include <sa2b/core.h>
#include <sa2b/memtools.h>
#include <sa2b/config.h>

#include <sa2b/ninja/ninja.h>

#include <sa2b/src/task.h>
#include <sa2b/src/camera.h>
#include <sa2b/src/score.h>

DataRef(uint8, byte_174AFFD, 0x174AFFD);

DataPtr(NJS_TEXLIST, texlist_mist_w_jungle, 0xEAD30C);

DataPtr(NJS_CNK_MODEL, model_mist_w_jungle, 0xEADA7C);

DataAry(NJS_TEXNAME, TextureWJungleWaterList, 0xEACD58, [10]);

DataPtr(NJS_CNK_OBJECT, object_water_w_jungle, 0xEAD2BC);

static void
BgDispSort(TASK* tp)
{
    TASKWK* twp = tp->twp;

    if ((byte_174AFFD == 1 && cameraControlWorkIndex == 0) || 
        (byte_174AFFD == 2 && cameraControlWorkIndex == 1) ||
        (byte_174AFFD == 3))
        return;

    njFogDisable();

    njPushMatrixEx();
    NJS_POINT3* pcampos = &cameraControlWorkList[cameraControlWorkIndex]->campos;

    njTranslate(NULL, pcampos->x, 0.0f, pcampos->z);

    if (((1 << cameraControlWorkIndex) & twp->mode) != 0) // I'm not sure either
    {
        njTranslate(NULL, 0.0, -1317.0, 0.0);
    }

    NJS_TEXLIST tex;
    tex.nbTexture = 1;
    tex.textures = &TextureWJungleWaterList[(GameTimer >> 1) % 0xA];
    njSetTexture(&tex);
    njCnkDrawObject(object_water_w_jungle);

    if (((4 << cameraControlWorkIndex) & twp->mode) == 0)
    {
        njSetTexture(texlist_mist_w_jungle);

        njPushMatrixEx();

        njRotateY(NULL, twp->ang.x);
        njCnkDrawModel_Broken(model_mist_w_jungle);

        njPopMatrixEx();
    }

    njPopMatrixEx();

    njFogEnable();
}

void
FixWhiteJungleWater()
{
    WriteJump(0x0062F220, BgDispSort);
}