#include <sa2b/core.h>
#include <sa2b/memutil.h>
#include <sa2b/config.h>

#include <sa2b/ninja/ninja.h>

#include <sa2b/src/task.h>
#include <sa2b/src/camera.h>
#include <sa2b/src/score.h>

/** Render Fix **/
#include <rf_core.h>
#include <rf_config.h>

#define byte_174AFFD                DataRef(uint8_t, 0x174AFFD)

#define texlist_mist_w_jungle       DataAry(NJS_TEXLIST, 0xEAD30C, [1])

#define model_mist_w_jungle         DataAry(NJS_CNK_MODEL, 0xEADA7C, [1])

#define TextureWJungleWaterList     DataAry(NJS_TEXNAME, 0xEACD58, [10])

#define object_water_w_jungle       DataAry(NJS_CNK_OBJECT, 0xEAD2BC, [1])

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
    NJS_POINT3* pcampos = &cameraControlWork[cameraControlWorkIndex]->campos;

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
RFM_WhiteJungleInit(void)
{
    if (RF_ConfigGetInt(CNF_FG_WATERFOG))
    {
        WriteJump(0x0062F220, BgDispSort);
    }
}
