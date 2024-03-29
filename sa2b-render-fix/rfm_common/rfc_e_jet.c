#include <sa2b/core.h>
#include <sa2b/memutil.h>

/** Ninja **/
#include <sa2b/ninja/ninja.h>

/** Source **/
#include <sa2b/src/task.h>
#include <sa2b/src/njctrl.h>

/** Render Fix **/
#include <rf_core.h>

typedef struct 
{
    Uint32 otherflag;
    Uint32 zflag;
    int texparplus4;
    Uint32 flag;
    int unknown2;
    int texparbuf;
    int unknown3;
    int unknown4;
    NJS_TEXLIST* tlist;
    int unknown5;
    int tnum;
}
NJS_CTX;

#define _nj_current_ctx_    DataRef(NJS_CTX*   , 0x02670544)

#define texlist_e_jet1      DataAry(NJS_TEXLIST, 0x0145F5D4, [1])

#define EnemyJetDisplayer   FuncPtr(void, __cdecl, (TASK*), 0x00511230)

static void
EnemyJetDisplayer_(TASK* tp)
{
    TASK* const ptp = tp->ptp;

    if (!ptp || ptp->ctp == tp || tp->last->disp != EnemyJetDisplayer)
    {
        _nj_current_ctx_->flag &= 0x3FFFFFF | 0x84000000;

        njSetTexture(texlist_e_jet1);
        njFogDisable();
    }

    TASKWK* const twp = tp->twp;

    NJS_TEXANIM texanim = {
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

    NJS_SPRITE sprite = {
        .p = twp->pos,
        .sx = twp->scl.z,
        .sy = twp->scl.z,
        .ang = 0,
        .tlist = texlist_e_jet1,
        .tanim = &texanim,
    };

    const float col = twp->scl.x;

    SetConstantMaterial(col, col, col, col);

    njDrawSprite3D(&sprite, 0, NJD_SPRITE_COLOR | NJD_SPRITE_SCALE | NJD_SPRITE_ALPHA);

    SetConstantMaterial(0.0f, 0.0f, 0.0f, 0.0f);

    if (!ptp || ptp->ctp == tp->next || tp->next->disp != EnemyJetDisplayer)
    {
        _nj_current_ctx_->flag &= 0x3FFFFFF | 0x94000000;

        njFogEnable();
    }
}

void
RFC_EnemyJet()
{
    WriteJump(EnemyJetDisplayer, EnemyJetDisplayer_);
}
