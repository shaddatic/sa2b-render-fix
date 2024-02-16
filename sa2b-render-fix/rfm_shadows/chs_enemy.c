#include <sa2b/core.h>
#include <sa2b/memutil.h>

/** Ninja **/
#include <sa2b/ninja/ninja.h>

/** Source **/
#include <sa2b/src/task.h>
#include <sa2b/src/debug.h>
#include <sa2b/src/njctrl.h>

/** Render Fix **/
#include <rf_draw.h>
#include <rf_file.h>
#include <rf_enemywk.h>

static void
DrawEnemyMod(ENEMYWK* ewp, TASKWK* twp)
{
    const float mod_scl   = ewp->shadow_scl;
    const float mod_scl_z = ewp->shadow_scl_ratio * mod_scl;

    OnControl3D(NJD_CONTROL_3D_SHADOW | NJD_CONTROL_3D_TRANS_MODIFIER);
    njPushMatrixEx();

    njTranslate(NULL, twp->pos.x, twp->pos.y + 0.01f, twp->pos.z);
    njRotateY(NULL, twp->ang.y);
    njScale(NULL, mod_scl, 1.0f, mod_scl_z);

    DrawBasicShadow();

    njPopMatrixEx();

    OffControl3D(NJD_CONTROL_3D_SHADOW | NJD_CONTROL_3D_TRANS_MODIFIER);
}

static void
EnemyGenericDisplayerMod(TASK* tp)
{
    TASKWK*  const twp = tp->twp;
    ENEMYWK* const ewp = GET_ENEMYWK(tp);

    DrawEnemyMod(ewp, twp);
}

static void
EnemyGenericModInit(TASK* tp)
{
    tp->disp_shad = EnemyGenericDisplayerMod;
}

#define EnemyAIInit     FuncPtr(void, __cdecl, (TASK*, TASKWK*), 0x004FE050)

static void
EnemyAIInitHook(TASK* tp, TASKWK* twp)
{
    EnemyAIInit(tp, twp);
    EnemyGenericModInit(tp);
}

static const void* const ObjectBigTheCatInit_p = (void*)0x004F5EF0;
__declspec(naked)
static void
__ObjectBigTheCatInitHook()
{
    __asm
    {
        push eax
        push [esp + 8]

        call ObjectBigTheCatInit_p

        add esp, 4

        call EnemyGenericModInit
        pop eax
        retn
    }
}

static void
EnemyGoldDisplayerMod(TASK* tp)
{
    TASKWK*  const twp = tp->twp;
    ENEMYWK* const ewp = GET_ENEMYWK(tp);

    if (twp->mode != 2)
    {
        const float sclchk = twp->scl.x - (float)(int)twp->scl.x;

        if (sclchk == 0.0f && ewp->shadow_scl > 0.0f)
            DrawEnemyMod(ewp, twp);
    }
}

static void
EnemyGoldModInit(TASK* tp)
{
    tp->disp_shad = EnemyGoldDisplayerMod;
}

static const void* const EnemyGoldInit_p = (void*)0x00505D40;
__declspec(naked)
static void
__EnemyGoldInitHook()
{
    __asm
    {
        push[esp + 4]
        call EnemyGoldInit_p
        call EnemyGoldModInit
        add esp, 4
        retn
    }
}

static void
EnemyNamieDisplayerMod(TASK* tp)
{
    TASKWK*  const twp = tp->twp;
    ENEMYWK* const ewp = GET_ENEMYWK(tp);

    if (twp->btimer)
        DrawEnemyMod(ewp, twp);
}

static void
EnemyNamieModInit(TASK* tp)
{
    tp->disp_shad = EnemyNamieDisplayerMod;
}

static const void* const EnemyNamieInit_p = (void*)0x004F7F40;
__declspec(naked)
static void
__EnemyNamieInitHook()
{
    __asm
    {
        push[esp + 4]
        call EnemyNamieInit_p
        call EnemyNamieModInit
        add esp, 4
        retn
    }
}

static void
EnemyNamieRocketDisplayerMod(TASK* tp)
{
    TASKWK*  const twp = tp->twp;
    ENEMYWK* const ewp = GET_ENEMYWK(tp);

    if (tp->ptp->twp->btimer == 1)
        DrawEnemyMod(ewp, twp);
}

static void
EnemyNamieRocketModInit(TASK* tp)
{
    tp->disp_shad = EnemyNamieRocketDisplayerMod;
}

static const void* const EnemyNamieRocketInit_p = (void*)0x004F7DB0;
__declspec(naked)
static void
__EnemyNamieRocketInitHook()
{
    __asm
    {
        push eax
        call EnemyNamieRocketInit_p
        call EnemyNamieRocketModInit
        pop eax
        retn
    }
}

static void
EnemyPathDisplayerMod(TASK* tp)
{
    TASKWK*  const twp = tp->twp;
    ENEMYWK* const ewp = GET_ENEMYWK(tp);

    if ((twp->btimer & 2) && (twp->smode == 0 || twp->smode == 1))
        DrawEnemyMod(ewp, twp);
}

static void
EnemyPathModInit(TASK* tp)
{
    tp->disp_shad = EnemyPathDisplayerMod;
}

#define EnemyPathInit       FuncPtr(void, __cdecl, (TASK*, TASKWK*), 0x00504610)
static void
EnemyPathInitHook(TASK* tp, TASKWK* twp)
{
    EnemyPathInit(tp, twp);
    EnemyPathModInit(tp);
}


static void
EnemyChaosPathDisplayerMod(TASK* tp)
{
    TASKWK*  const twp = tp->twp;
    ENEMYWK* const ewp = GET_ENEMYWK(tp);

    if (twp->mode != 1 && twp->btimer & 2)
        DrawEnemyMod(ewp, twp);
}

static void
EnemyChaosPathModInit(TASK* tp)
{
    tp->disp_shad = EnemyChaosPathDisplayerMod;
}

static const void* const EnemyChaosPathInit_p = (void*)0x0050B680;
__declspec(naked)
static void
__EnemyChaosPathInitHook()
{
    __asm
    {
        push[esp + 4]
        call EnemyChaosPathInit_p
        call EnemyChaosPathModInit
        add esp, 4
        retn
    }
}


#define EnemyE1000Init      FuncPtr(void, __cdecl, (TASK*, TASKWK*), 0x0050C510)
static void
EnemyE1000InitHook(TASK* tp, TASKWK* twp)
{
    EnemyE1000Init(tp, twp);
    EnemyGenericModInit(tp);
}



static const void* const EnemySaruInit_p = (void*)0x0050D8A0;
__declspec(naked)
static void
__EnemySaruInitHook()
{
    __asm
    {
        push ebx
        call EnemySaruInit_p
        call EnemyGenericModInit
        pop ebx
        retn
    }
}


#define EnemyGhoraInit      FuncPtr(void, __cdecl, (TASK*), 0x0050E750)

static void
EnemyGhoraInitHook(TASK* tp)
{
    EnemyGhoraInit(tp);
    EnemyGenericModInit(tp);
}


static const void* const EnemySpikeOrbiterInit_p = (void*)0x0050F560;
__declspec(naked)
static void
__EnemySpikeOrbiterInitHook()
{
    __asm
    {
        push eax
        call EnemySpikeOrbiterInit_p
        call EnemyGenericModInit
        pop eax
        retn
    }
}

static const void* const EnemyFireballOrbiterInit_p = (void*)0x0050FBC0;
__declspec(naked)
static void
__EnemyFireballOrbiterInitHook()
{
    __asm
    {
        push eax
        call EnemyFireballOrbiterInit_p
        call EnemyGenericModInit
        pop eax
        retn
    }
}

static void
EnemyAkahigeRocketDisplayerMod(TASK* tp)
{
    TASKWK* const twp = tp->twp;
    ENEMYWK* const ewp = GET_ENEMYWK(tp);

    if (tp->ptp->twp->btimer == 1)
        DrawEnemyMod(ewp, twp);
}

static void
EnemyAkahigeRocketModInit(TASK* tp)
{
    tp->disp_shad = EnemyAkahigeRocketDisplayerMod;
}

static const void* const EnemyAkahigeRocketInit_p = (void*)0x007A0020;
__declspec(naked)
static void
__EnemyAkahigeRocketInitHook()
{
    __asm
    {
        push eax
        call EnemyAkahigeRocketInit_p
        call EnemyAkahigeRocketModInit
        pop eax
        retn
    }
}


static void
EnemyAkahigeDisplayerMod(TASK* tp)
{
    TASKWK* const twp = tp->twp;
    ENEMYWK* const ewp = GET_ENEMYWK(tp);

    if (twp->btimer)
        DrawEnemyMod(ewp, twp);
}

static void
EnemyAkahigeModInit(TASK* tp)
{
    tp->disp_shad = EnemyAkahigeDisplayerMod;
}

static const void* const EnemyAkahigeInit_p = (void*)0x007A01B0;
__declspec(naked)
static void
__EnemyAkahigeInitHook()
{
    __asm
    {
        push[esp + 4]
        call EnemyAkahigeInit_p
        call EnemyAkahigeModInit
        add esp, 4
        retn
    }
}


static void
EnemyBataBeeDisplayerMod(TASK* tp)
{
    TASKWK* const twp = tp->twp;
    ENEMYWK* const ewp = GET_ENEMYWK(tp);

    if (twp->mode != 1)
        DrawEnemyMod(ewp, twp);
}

static void
EnemyBataBeeModInit(TASK* tp)
{
    tp->disp_shad = EnemyBataBeeDisplayerMod;
}

static const void* const EnemyBatabataInit_p = (void*)0x007A0EE0;
__declspec(naked)
static void
__EnemyBatabataInitHook()
{
    __asm
    {
        push ebx
        call EnemyBatabataInit_p
        call EnemyBataBeeModInit
        pop ebx
        retn
    }
}

static const void* const EnemyBeetonInit_p = (void*)0x007A1710;
__declspec(naked)
static void
__EnemyBeetonInitHook()
{
    __asm
    {
        push ebx
        call EnemyBeetonInit_p
        call EnemyBataBeeModInit
        pop ebx
        retn
    }
}

static void
EnemyKumiDisplayerMod(TASK* tp)
{
    TASKWK*  const twp = tp->twp;
    ENEMYWK* const ewp = GET_ENEMYWK(tp);

    if (twp->mode != 2)
        DrawEnemyMod(ewp, twp);
}

static void
EnemyKumiModInit(TASK* tp)
{
    tp->disp_shad = EnemyKumiDisplayerMod;
}

static const void* const EnemyKumiInit_p = (void*)0x004FFCF0;
__declspec(naked)
static void
__EnemyKumiInitHook()
{
    __asm
    {
        push[esp + 4]
        call EnemyKumiInit_p
        call EnemyKumiModInit
        add esp, 4
        retn
    }
}

#define OutOfRange      FuncPtr(int32_t, __cdecl, (NJS_POINT3*, float32_t), 0x007983F0)

static void
EnemyKyokoDisplayerMod(TASK* tp)
{
    TASKWK* const twp = tp->twp;

    if (OutOfRange(&twp->pos, 40.0f))
        return;

    OnControl3D(NJD_CONTROL_3D_SHADOW | NJD_CONTROL_3D_TRANS_MODIFIER);

    njPushMatrixEx();

    njTranslate(NULL, twp->pos.x, twp->pos.y + 0.01f, twp->pos.z);
    njRotateY(NULL, twp->ang.y);

    njPushMatrixEx();

    njTranslate(NULL, -13.0f, 0.0f, 0.0f);
    njScale(NULL, 20.0f, 1.0f, 20.0f);
    DrawBasicShadow();

    njPopMatrixEx();
    njPushMatrixEx();

    njTranslate(NULL, 0.0f, 0.0f, -13.0f);
    njScale(NULL, 8.0f, 1.0f, 8.0f);
    DrawBasicShadow();

    njPopMatrixEx();
    njPushMatrixEx();

    njTranslate(NULL, 0.0f, 0.0f, 13.0f);
    njScale(NULL, 8.0f, 1.0f, 8.0f);
    DrawBasicShadow();

    njPopMatrixEx();

    njPopMatrixEx();

    OffControl3D(NJD_CONTROL_3D_SHADOW | NJD_CONTROL_3D_TRANS_MODIFIER);

}

#define EnemyKyokoInit      FuncPtr(void, __cdecl, (TASK*), 0x004FAE40)

static void
EnemyKyokoInitHook(TASK* tp)
{
    EnemyKyokoInit(tp);
    tp->disp_shad = EnemyKyokoDisplayerMod;
}

static NJS_CNK_OBJECT* object_e_shouko_mod;

static void
EnemyShoukoDisplayerMod(TASK* tp)
{
    TASKWK* const twp = tp->twp;

    if (twp->mode == 1)
        return;

    OnControl3D(NJD_CONTROL_3D_SHADOW | NJD_CONTROL_3D_TRANS_MODIFIER);

    njPushMatrixEx();

    njTranslateEx(&twp->pos);
    njRotateY(NULL, twp->ang.y + 0x4000);
    njCnkModDrawObject(object_e_shouko_mod);

    njPopMatrixEx();

    OffControl3D(NJD_CONTROL_3D_SHADOW | NJD_CONTROL_3D_TRANS_MODIFIER);
}

static void
EnemyShoukoModInit(TASK* tp)
{
    tp->disp_shad = EnemyShoukoDisplayerMod;
}

static const void* const EnemyShoukoInit_p = (void*)0x004F9150;
__declspec(naked)
static void
__EnemyShoukoInitHook()
{
    __asm
    {
        push eax
        push[esp + 8]
        call EnemyShoukoInit_p
        add esp, 4
        call EnemyShoukoModInit
        add esp, 4
        retn
    }
}

void
CHS_EnemyInit()
{
    WriteCall(0x004FF9FC, EnemyAIInitHook);                 // AI
    WriteCall(0x004F623C, __ObjectBigTheCatInitHook);       // BigTheCat
    WriteCall(0x00506562, __EnemyGoldInitHook);             // Gold Kumi
    WriteCall(0x004F8FE8, __EnemyNamieInitHook);            // Namie
    WriteCall(0x004F7F0E, __EnemyNamieRocketInitHook);      // Namie Rocket
    WriteCall(0x00505C72, EnemyPathInitHook);               // Path
    WriteCall(0x0050C42E, __EnemyChaosPathInitHook);        // Chaos Path
    WriteCall(0x0050D7D8, EnemyE1000InitHook);              // e1000
    WriteCall(0x0050E525, __EnemySaruInitHook);             // Saru
    WriteCall(0x0050F19B, EnemyGhoraInitHook);              // Ghora 
    WriteCall(0x0050F664, __EnemySpikeOrbiterInitHook);     // Enemy Spike Orbiter
    WriteCall(0x0050FCF2, __EnemyFireballOrbiterInitHook);  // Enemy Fireball Orbiter
    WriteCall(0x007A016F, __EnemyAkahigeRocketInitHook);    // Akahige (Phoenix) Rocket
    WriteCall(0x007A0D70, __EnemyAkahigeInitHook);          // Akahige (Phoenix)
    WriteCall(0x007A164F, __EnemyBatabataInitHook);         // Batabata
    WriteCall(0x007A221A, __EnemyBeetonInitHook);           // Beeton

    WriteRetn(0x004799E0); // EnemyDrawMod

    WriteCall(0x00501586, __EnemyKumiInitHook);             // Kumi (Beetle)
    WriteCall(0x004FC750, EnemyKyokoInitHook);              // Kyoko
    WriteCall(0x004F9F46, __EnemyShoukoInitHook);           // Shouko (Jets)

    object_e_shouko_mod = RF_ChunkLoadObjectFile("e_shouko_mod");
}
