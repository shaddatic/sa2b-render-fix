#include <sa2b/core.h>
#include <sa2b/memtools.h>

#include <sa2b/ninja/ninja.h>

#include <sa2b/src/task.h>

DataPtr(NJS_TEXLIST, texlist_e_jet1, 0x0145F5D4);

NJS_TEXANIM texanim_e_jet1[] = { 30, 30, 15, 15, 0, 0, 0xFF, 0xFF, 0, 0 };
NJS_SPRITE sprite_e_jet1[] = { { { 0.0f, 0.0f, 0.0f }, 1.0f, 1.0f, 0, texlist_e_jet1, texanim_e_jet1 } };

static void 
EnemyJetDraw(TASK* tp)
{
    TASKWK* twp = tp->twp;

    SetConstantMaterial(twp->scl.x, 1.0f, 1.0f, 1.0f);

    sprite_e_jet1->sx = twp->scl.z;
    sprite_e_jet1->sy = twp->scl.z;
    sprite_e_jet1->p = twp->pos;

    njDrawSprite3D(sprite_e_jet1, 0, NJD_SPRITE_COLOR | NJD_SPRITE_SCALE | NJD_SPRITE_ALPHA);

    SetConstantMaterial(0.0f, 0.0f, 0.0f, 0.0f);
}

DataRef(char, EnableFog, 0x025EFFCC);
FuncPtr(void, __cdecl, UpdateFog, (), 0x0042A870);

static void
EnemyJetSetup()
{
    EnableFog = 0;
    UpdateFog();
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