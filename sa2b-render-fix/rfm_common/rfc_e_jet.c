#include <sa2b/core.h>
#include <sa2b/writemem.h>
#include <sa2b/writeop.h>

/** Ninja **/
#include <sa2b/ninja/ninja.h>

/** Source **/
#include <sa2b/sonic/task.h>
#include <sa2b/sonic/njctrl.h>

/** Render Fix **/
#include <rf_core.h>
#include <rf_util.h>

#define texlist_e_jet1      DATA_ARY(NJS_TEXLIST, 0x0145F5D4, [1])

#define EnemyJetDisplayer   FUNC_PTR(void, __cdecl, (task*), 0x00511230)

static NJS_TEXANIM texanim = {
    .sx = 32,
    .sy = 32,
    .cx = 16,
    .cy = 16,
    .sx = 32,
    .sy = 32,
    .cx = 16,
    .cy = 16,
    .u1 = 0,
    .v1 = 0,
    .u2 = 256,
    .v2 = 256,
    .texid = 0,
    .attr = 0,
};

static void
EnemyJetDisplayer_(task* tp)
{
    task* const ptp = tp->ptp;

    if (!ptp || ptp->ctp == tp || tp->last->disp != EnemyJetDisplayer)
    {
        njColorBlendingMode(NJD_SOURCE_COLOR     , NJD_COLOR_BLENDING_SRCALPHA);
        njColorBlendingMode(NJD_DESTINATION_COLOR, NJD_COLOR_BLENDING_ONE);

        njSetTexture(texlist_e_jet1);
        njFogDisable();
    }

    taskwk* const twp = tp->twp;

    NJS_SPRITE sprite = {
        .p     = twp->pos,
        .sx    = twp->scl.z,
        .sy    = twp->scl.z,
        .ang   = 0,
        .tlist = texlist_e_jet1,
        .tanim = &texanim,
    };

    const float col = twp->scl.x;

    SetConstantMaterial(col, col, col, col);

    njDrawSprite3D(&sprite, 0, NJD_SPRITE_COLOR | NJD_SPRITE_SCALE | NJD_SPRITE_ALPHA);

    ResetConstantMaterial();

    if (!ptp || ptp->ctp == tp->next || tp->next->disp != EnemyJetDisplayer)
    {
        njColorBlendingMode(NJD_SOURCE_COLOR     , NJD_COLOR_BLENDING_SRCALPHA);
        njColorBlendingMode(NJD_DESTINATION_COLOR, NJD_COLOR_BLENDING_INVSRCALPHA);

        njFogEnable();
    }
}

void
RFC_EnemyJet()
{
    WriteJump(EnemyJetDisplayer, EnemyJetDisplayer_);

    /** Fix Shouko jet displaying inside its model **/
    static const double sub_velo = 7.2;
    ReplaceFloat(0x004F9B37, &sub_velo);
}
