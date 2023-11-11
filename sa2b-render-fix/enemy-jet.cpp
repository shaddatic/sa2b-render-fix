#include <sa2b/core.h>
#include <sa2b/memtools.h>

#include <sa2b/ninja/ninja.h>

#include <sa2b/src/task.h>
#include <sa2b/src/njctrl.h>

#define texlist_e_jet1      DataPtr(NJS_TEXLIST, 0x0145F5D4)

static void 
EnemyJetDraw(TASK* tp)
{
    TASKWK* twp = tp->twp;

    NJS_TEXANIM texanim;

    texanim.sx = 32;
    texanim.sy = 32;
    texanim.cx = 16;
    texanim.cy = 16;
    texanim.u1 = 0;
    texanim.v1 = 0;
    texanim.u2 = 256;
    texanim.v2 = 256;
    texanim.texid = 0;
    texanim.attr = 0;

    NJS_SPRITE sprite;

    sprite.p = twp->pos;
    sprite.sx = twp->scl.z;
    sprite.sy = twp->scl.z;
    sprite.ang = 0;
    sprite.tlist = texlist_e_jet1;
    sprite.tanim = &texanim;

    SetConstantMaterial(twp->scl.x, 1.0f, 1.0f, 1.0f);

    njDrawSprite3D(&sprite, 0, NJD_SPRITE_COLOR | NJD_SPRITE_SCALE | NJD_SPRITE_ALPHA);

    SetConstantMaterial(0.0f, 0.0f, 0.0f, 0.0f);
}

static void
EnemyJetSetup()
{
    gjDisableFog();
    gjUpdateFog();
}

static void __declspec(naked)
__EnemyJetDraw()
{
    __asm
    {
        push esi
        call EnemyJetDraw
        pop esi
        retn
    }
}

void
EnemyJetDisplayerFix()
{
    WriteNoOP(0x00511271, 0x00511278);      // NOP EnableFog = 0;
    WriteCall(0x00511271, EnemyJetSetup);   // Replace with call
    WriteData(0x00511252, 0x25, uint8);     // Jump 5 bytes shorter
    WriteCall(0x00511278, __EnemyJetDraw);  // ... to call this
}