/********************************/
/*  Includes                    */
/********************************/
/****** SAMT ************************************************************************************/
#include <samt/core.h>              /* core                                                     */
#include <samt/writemem.h>          /* write memory                                             */
#include <samt/writeop.h>           /* write op                                                 */
#include <samt/funchook.h>          /* function hook                                            */

/****** Ninja ***********************************************************************************/
#include <samt/ninja/ninja.h>       /* ninja                                                    */

/****** Game ************************************************************************************/
#include <samt/sonic/task.h>        /* task                                                     */
#include <samt/sonic/njctrl.h>      /* ninja control funcs                                      */

/****** Render Fix ******************************************************************************/
#include <rf_core.h>                /* core                                                     */
#include <rf_ninja.h>               /* render fix ninja                                         */
#include <rf_njcnk.h>               /* ninja chunk draw                                         */
#include <rf_util.h>                /* switch displayer                                         */
#include <rf_enemywk.h>             /* enemy work                                               */

/****** RF Util *********************************************************************************/
#include <rfu_draw.h>               /* animate motion                                           */

/****** Self ************************************************************************************/
#include <rf_shadow/chs_internal.h> /* parent & siblings                                        */

/********************************/
/*  Game Refs                   */
/********************************/
/****** Range Out *******************************************************************************/
#define OutOfRange                  FUNC_PTR(i32, __cdecl, (NJS_POINT3*, f32), 0x007983F0)

/****** Enemy Init *****************************************************************************/
#define EnemyAIInit                 FUNC_PTR(void, __cdecl, (task*, taskwk*), 0x004FE050)
#define EnemyPathInit               FUNC_PTR(void, __cdecl, (task*, taskwk*), 0x00504610)
#define EnemyE1000Init              FUNC_PTR(void, __cdecl, (task*, taskwk*), 0x0050C510)
#define EnemyGhoraInit              FUNC_PTR(void, __cdecl, (task*)         , 0x0050E750)
#define EnemyKyokoInit              FUNC_PTR(void, __cdecl, (task*)         , 0x004FAE40)

/********************************/
/*  Source                      */
/********************************/
/****** Draw Shadow *****************************************************************************/
static void
EnemyShadowDraw(taskwk* twp, enemywk* ewp)
{
    const f32 mod_scl   = ewp->shadow_scl;
    const f32 mod_scl_z = ewp->shadow_scl_ratio * mod_scl;

    OnControl3D(NJD_CONTROL_3D_SHADOW|NJD_CONTROL_3D_TRANS_MODIFIER);

    njPushMatrixEx();
    {
        njTranslate( NULL, twp->pos.x, twp->pos.y + 0.01f, twp->pos.z );
        njRotateY(   NULL, twp->ang.y );
        njScale(     NULL, mod_scl, 1.0f, mod_scl_z );

        njCnkModDrawObject( object_shadow );
    }
    njPopMatrixEx();

    OffControl3D(NJD_CONTROL_3D_SHADOW|NJD_CONTROL_3D_TRANS_MODIFIER);
}

/****** Displayers ******************************************************************************/
void
EnemyShadow(task* tp)
{
    taskwk*  const twp = tp->twp;
    enemywk* const ewp = GET_ENEMYWK(tp);

    EnemyShadowDraw(twp, ewp);
}

void
EnemyGoldShadow(task* tp)
{
    taskwk*  const twp = tp->twp;
    enemywk* const ewp = GET_ENEMYWK(tp);

    if ( twp->mode != 2 )
    {
        const f32 sclchk = twp->scl.x - floorf(twp->scl.x);

        if ( sclchk == 0.f && ewp->shadow_scl > 0.f )
        {
            EnemyShadowDraw(twp, ewp);
        }
    }
}

void
EnemyNamieShadow(task* tp)
{
    taskwk*  const twp = tp->twp;
    enemywk* const ewp = GET_ENEMYWK(tp);

    if ( twp->btimer )
    {
        EnemyShadowDraw(twp, ewp);
    }
}

void
EnemyNamieRocketShadow(task* tp)
{
    taskwk*  const twp = tp->twp;
    enemywk* const ewp = GET_ENEMYWK(tp);

    if ( tp->ptp->twp->btimer == 1 )
    {
        EnemyShadowDraw(twp, ewp);
    }
}

void
EnemyPathShadow(task* tp)
{
    taskwk*  const twp = tp->twp;
    enemywk* const ewp = GET_ENEMYWK(tp);

    if ((twp->btimer & 2) && (twp->smode == 0 || twp->smode == 1))
    {
        EnemyShadowDraw(twp, ewp);
    }
}


void
EnemyChaosPathShadow(task* tp)
{
    taskwk*  const twp = tp->twp;
    enemywk* const ewp = GET_ENEMYWK(tp);

    if (twp->mode != 1 && twp->btimer & 2)
    {
        EnemyShadowDraw(twp, ewp);
    }
}

void
EnemyAkahigeRocketShadow(task* tp)
{
    taskwk* const twp = tp->twp;
    enemywk* const ewp = GET_ENEMYWK(tp);

    if (tp->ptp->twp->btimer == 1)
    {
        EnemyShadowDraw(twp, ewp);
    }
}

void
EnemyAkahigeShadow(task* tp)
{
    taskwk* const twp = tp->twp;
    enemywk* const ewp = GET_ENEMYWK(tp);

    if ( twp->btimer )
    {
        EnemyShadowDraw(twp, ewp);
    }
}

void
EnemyBataBeeShadow(task* tp)
{
    taskwk* const twp = tp->twp;
    enemywk* const ewp = GET_ENEMYWK(tp);

    if ( twp->mode != 1 )
    {
        EnemyShadowDraw(twp, ewp);
    }
}

void
EnemyKumiShadow(task* tp)
{
    taskwk*  const twp = tp->twp;
    enemywk* const ewp = GET_ENEMYWK(tp);

    if ( twp->mode != 2 )
    {
        EnemyShadowDraw(twp, ewp);
    }
}

void
EnemyKyokoShadow(task* tp)
{
    taskwk* const twp = tp->twp;

    if ( OutOfRange(&twp->pos, 40.0f) )
    {
        return;
    }

    OnControl3D(NJD_CONTROL_3D_SHADOW|NJD_CONTROL_3D_TRANS_MODIFIER);

    njPushMatrixEx();
    {
        njTranslate(NULL, twp->pos.x, twp->pos.y + 0.01f, twp->pos.z);
        njRotateY(NULL, twp->ang.y);

        njPushMatrixEx();
        {
            njTranslate(NULL, -13.0f, 0.0f, 0.0f);
            njScale(NULL, 20.0f, 1.0f, 20.0f);

            njCnkModDrawObject( object_shadow );
        }
        njFastPopPushMatrix();
        {
            njTranslate(NULL, 0.0f, 0.0f, -13.0f);
            njScale(NULL, 8.0f, 1.0f, 8.0f);

            njCnkModDrawObject( object_shadow );
        }
        njFastPopPushMatrix();
        {
            njTranslate(NULL, 0.0f, 0.0f, 13.0f);
            njScale(NULL, 8.0f, 1.0f, 8.0f);

            njCnkModDrawObject( object_shadow );
        }
        njPopMatrixEx();
    }
    njPopMatrixEx();

    OffControl3D(NJD_CONTROL_3D_SHADOW|NJD_CONTROL_3D_TRANS_MODIFIER);
}

void
EnemyShoukoShadow(task* tp)
{
    taskwk* const twp = tp->twp;

    if (twp->mode == 1)
        return;

    /** The shouko's modifier model is inverted by default, was on Dreamcast too.
        So, set the mirror model 3D flag. **/
    OnControl3D(NJD_CONTROL_3D_SHADOW|NJD_CONTROL_3D_TRANS_MODIFIER|NJD_CONTROL_3D_MIRROR_MODEL);

    njPushMatrixEx();
    {
        njTranslateV( NULL, &twp->pos );
        njRotateY(    NULL, twp->ang.y + NJM_DEG_ANG(90.f) );

        njCnkModDrawObject( object_e_shouko_mod );
    }
    njPopMatrixEx();

    OffControl3D(NJD_CONTROL_3D_SHADOW|NJD_CONTROL_3D_TRANS_MODIFIER|NJD_CONTROL_3D_MIRROR_MODEL);
}

/****** Hooks ***********************************************************************************/
static void
EnemyGenericModInit(task* tp)
{
    tp->disp_shad = EnemyShadow;
}

static void
EnemyAIInitHook(task* tp, taskwk* twp)
{
    EnemyAIInit(tp, twp);
    EnemyGenericModInit(tp);
}

static const void* const ObjectBigTheCatInit_p = (void*)0x004F5EF0;
__declspec(naked)
static void
__ObjectBigTheCatInitHook(void)
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
EnemyGoldModInit(task* tp)
{
    tp->disp_shad = EnemyGoldShadow;
}

static const void* const EnemyGoldInit_p = (void*)0x00505D40;
__declspec(naked)
static void
__EnemyGoldInitHook(void)
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
EnemyNamieModInit(task* tp)
{
    tp->disp_shad = EnemyNamieShadow;
}

static const void* const EnemyNamieInit_p = (void*)0x004F7F40;
__declspec(naked)
static void
__EnemyNamieInitHook(void)
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
EnemyNamieRocketModInit(task* tp)
{
    tp->disp_shad = EnemyNamieRocketShadow;
}

static const void* const EnemyNamieRocketInit_p = (void*)0x004F7DB0;
__declspec(naked)
static void
__EnemyNamieRocketInitHook(void)
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
EnemyPathModInit(task* tp)
{
    tp->disp_shad = EnemyPathShadow;
}


static void
EnemyPathInitHook(task* tp, taskwk* twp)
{
    EnemyPathInit(tp, twp);
    EnemyPathModInit(tp);
}

static void
EnemyChaosPathModInit(task* tp)
{
    tp->disp_shad = EnemyChaosPathShadow;
}

static const void* const EnemyChaosPathInit_p = (void*)0x0050B680;
__declspec(naked)
static void
__EnemyChaosPathInitHook(void)
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

static void
EnemyE1000InitHook(task* tp, taskwk* twp)
{
    EnemyE1000Init(tp, twp);
    EnemyGenericModInit(tp);
}

static const void* const EnemySaruInit_p = (void*)0x0050D8A0;
__declspec(naked)
static void
__EnemySaruInitHook(void)
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

static void
EnemyGhoraInitHook(task* tp)
{
    EnemyGhoraInit(tp);
    EnemyGenericModInit(tp);
}

static const void* const EnemySpikeOrbiterInit_p = (void*)0x0050F560;
__declspec(naked)
static void
__EnemySpikeOrbiterInitHook(void)
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
__EnemyFireballOrbiterInitHook(void)
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
EnemyAkahigeRocketModInit(task* tp)
{
    tp->disp_shad = EnemyAkahigeRocketShadow;
}

static const void* const EnemyAkahigeRocketInit_p = (void*)0x007A0020;
__declspec(naked)
static void
__EnemyAkahigeRocketInitHook(void)
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
EnemyAkahigeModInit(task* tp)
{
    tp->disp_shad = EnemyAkahigeShadow;
}

static const void* const EnemyAkahigeInit_p = (void*)0x007A01B0;
__declspec(naked)
static void
__EnemyAkahigeInitHook(void)
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
EnemyBataBeeModInit(task* tp)
{
    tp->disp_shad = EnemyBataBeeShadow;
}

static const void* const EnemyBatabataInit_p = (void*)0x007A0EE0;
__declspec(naked)
static void
__EnemyBatabataInitHook(void)
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
__EnemyBeetonInitHook(void)
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
EnemyKumiModInit(task* tp)
{
    tp->disp_shad = EnemyKumiShadow;
}

static const void* const EnemyKumiInit_p = (void*)0x004FFCF0;
__declspec(naked)
static void
__EnemyKumiInitHook(void)
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

static void
EnemyKyokoInitHook(task* tp)
{
    EnemyKyokoInit(tp);
    tp->disp_shad = EnemyKyokoShadow;
}

static void
EnemyShoukoModInit(task* tp)
{
    tp->disp_shad = EnemyShoukoShadow;
}

static const void* const EnemyShoukoInit_p = (void*)0x004F9150;
__declspec(naked)
static void
__EnemyShoukoInitHook(void)
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

/****** Init ************************************************************************************/
void
CHS_EnemyInit(void)
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
}
