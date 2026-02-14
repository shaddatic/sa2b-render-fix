#include <samt/core.h>
#include <samt/config.h>
#include <samt/writemem.h>
#include <samt/writeop.h>
#include <samt/modinfo.h>

/** Ninja **/
#include <samt/ninja/ninja.h>

/** Player **/
#include <samt/sonic/player.h>

/** Figure **/
#define SAMT_INCL_FUNCPTRS
#include <samt/sonic/figure/sonic.h>
#include <samt/sonic/figure/shadow.h>
#include <samt/sonic/figure/miles.h>
#include <samt/sonic/figure/knuckles.h>
#include <samt/sonic/figure/rouge.h>
#include <samt/sonic/figure/ewalker.h>
#include <samt/sonic/figure/twalker.h>
#undef  SAMT_INCL_FUNCPTRS

/** Render Fix **/
#include <rf_core.h>

/** Self **/
#include <rf_module/rfm_shadows/shd_internal.h>

enum
{
    EQUIP_MD_OFF,
    EQUIP_MD_OG_ONLY,
    EQUIP_MD_FULL
};

static bool DrawSonicFlameRing;
static bool DrawSonicRubberUnit;
static bool DrawSonicMagicWrist;
static bool DrawSonicShoes;

static bool DrawShadowFlameRing;
static bool DrawShadowShoes;

static bool DrawKnuxClaw;
static bool DrawKnuxAir;
static bool DrawKnuxGloves;
static bool DrawKnuxSunglass;

static bool DrawRougeNails;
static bool DrawRougeBoots;
static bool DrawRougeScope;

static int8_t DrawMilesLazerBlaster;
static int8_t DrawMilesHyperCannon;
static bool   DrawMilesBooster;

static int8_t DrawEggmanPowerGun;
static int8_t DrawEggmanBazooka;
static bool   DrawEggmanJetEngine;
static bool   DrawEggmanExtraShield;

static int
GetCharacterPlayer(int character)
{
    return (int)(playerpwp[1] && playerpwp[1]->character == character);
}

static void
DrawSonicShadow(NJS_MOTION* motion, float frame)
{
    sonicwk* spwp = (sonicwk*) playerpwp[ GetCharacterPlayer( PLNO_SONIC ) ];
    SonicWorkPointer = spwp;

    njCnkSetMotionCallback(SonicMotionCallBack_p);
    njCnkDrawMotion(plobjects[0].obj, motion, frame);

    if (DrawSonicFlameRing && spwp->pw.equipment & EQUIP_SONIC_FLAMERING)
    {
        if (plobjects[25].obj)
        {
            njSetMatrix(0, &mtx_SonicHandR);
            njCnkDrawModel(plobjects[25].obj->model);
        }
    }

    if (DrawSonicRubberUnit && spwp->pw.equipment & EQUIP_SONIC_RUBBERUNIT)
    {
        if (plobjects[26].obj)
        {
            njSetMatrix(0, &mtx_SonicHandL);
            njCnkDrawModel(plobjects[26].obj->model);
        }
    }

    if (DrawSonicMagicWrist && spwp->pw.equipment & EQUIP_SONIC_MAGICWRIST)
    {
        if (plobjects[27].obj)
        {
            njSetMatrix(0, &mtx_SonicHandL);
            njCnkDrawObject(plobjects[27].obj);
        }
    }

    if (DrawSonicShoes && spwp->pw.equipment & EQUIP_SONIC_SHOES)
    {
        if (plobjects[14].obj)
        {
            njSetMatrix(0, &mtx_SonicFootL);
            njCnkDrawObject(plobjects[14].obj);
        }

        if (plobjects[13].obj)
        {
            njSetMatrix(0, &mtx_SonicFootR);
            njCnkDrawObject(plobjects[13].obj);
        }
    }

    njCnkSetMotionCallback(NULL);
}

static void
DrawShadowShadow(NJS_MOTION* motion, float frame)
{
    sonicwk* spwp = (sonicwk*)playerpwp[ GetCharacterPlayer(PLNO_SHADOW) ];
    SonicWorkPointer = spwp;

    njCnkSetMotionCallback(ShadowMotionCallBack_p);
    njCnkDrawMotion(plobjects[65].obj, motion, frame);

    if (DrawShadowFlameRing && spwp->pw.equipment & EQUIP_SHADOW_FLAMERING) // Flame Ring
    {
        if (plobjects[100].obj)
        {
            njSetMatrix(NULL, &mtx_SonicHandR);
            njCnkDrawModel(plobjects[100].obj->model);
        }
    }

    if (DrawShadowShoes && spwp->pw.equipment & EQUIP_SHADOW_SHOES) // Air Shoes
    {
        if (plobjects[79].obj)
        {
            njSetMatrix(NULL, &mtx_SonicFootL);
            njCnkDrawObject(plobjects[79].obj);
        }

        if (plobjects[78].obj)
        {
            njSetMatrix(NULL, &mtx_ShadowFootR);
            njCnkDrawObject(plobjects[78].obj);
        }
    }

    njCnkSetMotionCallback(NULL);
}

static void
DrawKnucklesShadow(NJS_MOTION* motion, float frame)
{
    knuckleswk* kwp = (knuckleswk*)playerpwp[GetCharacterPlayer( PLNO_KNUCKLES )];
    KnucklesWorkPointer = kwp;

    njCnkSetMotionCallback(KnucklesMotionCallBack_p);
    njCnkDrawMotion(plobjects[142].obj, motion, frame);

    njPushMatrixEx();

    if (DrawKnuxSunglass && kwp->pw.equipment & EQUIP_KNUCKLES_SUNGLASS)
    {
        if (plobjects[161].obj)
        {
            NJS_CNK_OBJECT* pobj = plobjects[161].obj->child;

            njSetMatrix(NULL, &mtx_KnucklesHead);
            njTranslateA(NULL, pobj->pos);
            njRotateZ(   NULL, kwp->sunglass_ang - 0x2000);  

            njCnkDrawModel(pobj->model);
        }
    }

    if (DrawKnuxAir && kwp->pw.equipment & EQUIP_KNUCKLES_AIR)
    {
        if (plobjects[168].obj)
        {
            njSetMatrix(NULL, &mtx_KnucklesBody);
            njCnkDrawObject(plobjects[168].obj);
        }
    }

    if ((DrawKnuxClaw || DrawKnuxGloves) && kwp->pw.equipment & (EQUIP_KNUCKLES_GROVES | EQUIP_KNUCKLES_CLAW))
    {
        njSetMatrix(NULL, &mtx_KnucklesHandL);
        if (DrawKnuxClaw && kwp->pw.equipment & EQUIP_KNUCKLES_CLAW)
        {
            if (plobjects[162].obj)
            {
                njCnkDrawObject(plobjects[162].obj);
            }
        }
        if (DrawKnuxGloves && kwp->pw.equipment & EQUIP_KNUCKLES_GROVES)
        {
            if (plobjects[164].obj)
            {
                njCnkDrawObject(plobjects[164].obj);
            }
        }
        njSetMatrix(NULL, &mtx_KnucklesHandR);
        if (DrawKnuxClaw && kwp->pw.equipment & EQUIP_KNUCKLES_CLAW)
        {
            if (plobjects[163].obj)
            {
                njCnkDrawObject(plobjects[163].obj);
            }
        }
        if (DrawKnuxGloves && kwp->pw.equipment & EQUIP_KNUCKLES_GROVES)
        {
            if (plobjects[165].obj)
            {
                njCnkDrawObject(plobjects[165].obj);
            }
        }
    }

    njPopMatrixEx();

    njCnkSetMotionCallback(NULL);
}

static void
DrawRougeShadow(NJS_MOTION* motion, float frame)
{
    knuckleswk* rwp = (knuckleswk*) playerpwp[ GetCharacterPlayer( PLNO_ROUGE ) ];
    KnucklesWorkPointer = rwp;

    njCnkSetMotionCallback(RougeMotionCallBack_p);
    njCnkDrawMotion(plobjects[171].obj, motion, frame);

    njPushMatrixEx();

    if (DrawRougeScope && rwp->pw.equipment & EQUIP_ROUGE_SCOPE)
    {
        if (plobjects[205].obj)
        {
            NJS_CNK_OBJECT* pobj = plobjects[205].obj;

            njSetMatrix(NULL, &mtx_KnucklesHead);
            njCnkDrawModel(pobj->model);

            pobj = pobj->child;

            njTranslateA(NULL, pobj->pos);
            njRotateZ(   NULL, rwp->sunglass_ang - 0x2000);  

            njCnkDrawModel(pobj->model);
        }
    }

    if (DrawRougeBoots && rwp->pw.equipment & EQUIP_ROUGE_BOOTS)
    {
        if (plobjects[201].obj)
        {
            njSetMatrix(NULL, &mtx_KnucklesHandL);
            njCnkDrawObject(plobjects[201].obj);
        }

        if (plobjects[203].obj)
        {
            njSetMatrix(NULL, &mtx_KnucklesHandR);
            njCnkDrawObject(plobjects[203].obj);
        }
    }

    if (DrawRougeNails && rwp->pw.equipment & EQUIP_ROUGE_NAILS)
    {
        if (plobjects[199].obj)
        {
            njSetMatrix(NULL, &mtx_RougeBootL);
            njCnkDrawObject(plobjects[199].obj);
        }

        if (plobjects[195].obj)
        {
            njSetMatrix(NULL, &mtx_RougeBootR);
            njCnkDrawObject(plobjects[195].obj);
        }
    }

    njPopMatrixEx();

    njCnkSetMotionCallback(NULL);
}

static void
DrawEggWalkerShadow(NJS_MOTION* motion, float frame)
{
    walkerwk* ewwp = (walkerwk*) playerpwp[ GetCharacterPlayer( PLNO_EGG_WALKER ) ];
    EggWalkerWorkPointer = ewwp;

    njCnkSetMotionCallback(EggWalkerMotionCallBack_p);
    njCnkDrawMotion(plobjects[248].obj, motion, frame);

    if (DrawEggmanPowerGun)
    {
        const int num = DrawEggmanPowerGun == EQUIP_MD_FULL && (ewwp->pw.equipment & EQUIP_EGGMAN_POWERGUN) ? 260 : 258;

        NJS_CNK_OBJECT* powergun = plobjects[num].obj;

        if (powergun)
        {
            njSetMatrix(NULL, &mtx_EWalkerLaserBlaster); // Laser Blaster
            while (powergun)
            {
                njTranslate(NULL, powergun->pos[0], powergun->pos[1], powergun->pos[2]);
                njRotateEx(powergun->ang, 0);

                if (powergun->model)
                    njCnkDrawModel(powergun->model);

                powergun = powergun->child;
            }
        }
    }

    if (DrawEggmanBazooka)
    {
        njSetMatrix(NULL, &mtx_EWalkerLargeCannon);
        if (DrawEggmanBazooka == EQUIP_MD_FULL && ewwp->pw.equipment & EQUIP_EGGMAN_BAZOOKA) // Large Cannon
        {
            if (plobjects[263].obj)
            {
                njTranslate(NULL, 1.0f - njCos(ewwp->CannonRecoil), 0, 0);
                njCnkDrawObject(plobjects[263].obj);
            }
        }
        else
        {
            if (plobjects[266].obj)
            {
                njCnkDrawObject(plobjects[266].obj);
            }
        }
    }

    if (DrawEggmanJetEngine && ewwp->pw.equipment & EQUIP_EGGMAN_JETENGINE) // Jets
    {
        //njPushMatrixEx();

        if (plobjects[274].obj)
        {
            njSetMatrix(NULL, &mtx_EWalkerJetEngineL);
            njCnkDrawObject(plobjects[274].obj);
        }

        if (plobjects[276].obj)
        {
            njSetMatrix(NULL, &mtx_EWalkerJetEngineR);
            njCnkDrawObject(plobjects[276].obj);
        }

        //njPopMatrixEx();
    }

    if (DrawEggmanExtraShield && ewwp->pw.equipment & EQUIP_EGGMAN_EXTRASHIELD) // Armor
    {
        if (plobjects[278].obj)
        {
            njPushMatrix(&mtx_EWalkerProtectiveArmor);
            njCnkDrawObject(plobjects[278].obj);
            njPopMatrixEx();
        }
    }

    njCnkSetMotionCallback(NULL);
}

static void
DrawTornadoShadow(NJS_MOTION* motion, float frame)
{
    walkerwk* ewwp = (walkerwk*)playerpwp[ GetCharacterPlayer( PLNO_TAILS_WALKER ) ];
    EggWalkerWorkPointer = ewwp;

    njCnkSetMotionCallback(TailsWalkerMotionCallBack_p);
    njCnkDrawMotion(plobjects[293].obj, motion, frame);

    if (DrawMilesLazerBlaster)
    {
        const int num = DrawMilesLazerBlaster == EQUIP_MD_FULL && (ewwp->pw.equipment & EQUIP_MILES_LASERBALSTER) ? 306 : 304;

        NJS_CNK_OBJECT* blaster = plobjects[num].obj;

        if (blaster)
        {
            njSetMatrix(NULL, &mtx_EWalkerLaserBlaster);
            while (blaster)    // laser blaster
            {
                njTranslateEx((NJS_POINT3*)&blaster->pos);
                njRotateEx(blaster->ang, 0);
                if (blaster->model)
                    njCnkDrawModel(blaster->model);

                blaster = blaster->child;
            }
        }
    }

    if (DrawMilesHyperCannon)
    {
        if (DrawMilesHyperCannon == EQUIP_MD_FULL && ewwp->pw.equipment & EQUIP_MILES_HYPERCANNON)
        {
            NJS_CNK_OBJECT* hypercannon = plobjects[309].obj;

            if (hypercannon)
            {
                njSetMatrix(NULL, &mtx_TornadoBazooka);

                njTranslate(NULL, hypercannon->pos[0], hypercannon->pos[1], hypercannon->pos[2]);
                njRotateEx(hypercannon->ang, 0);
                njCnkDrawModel(hypercannon->model);

                hypercannon = hypercannon->child;

                njTranslate(NULL, hypercannon->pos[0], hypercannon->pos[1], hypercannon->pos[2]);
                njRotateEx(hypercannon->ang, 0);
                njTranslate(0, 0, (njCos(ewwp->CannonRecoil) - 1.0f) * 1.25f, 0);
                njCnkDrawModel(hypercannon->model);
            }
        }
        else
        {
            NJS_CNK_OBJECT* hypercannon = plobjects[312].obj;

            if (hypercannon)
            {
                njSetMatrix(NULL, &mtx_TornadoBazooka);

                njTranslate(NULL, hypercannon->pos[0], hypercannon->pos[1], hypercannon->pos[2]);
                njRotateEx(hypercannon->ang, 0);
                njCnkDrawModel(hypercannon->model);
            }
        }
    }

    if (DrawMilesBooster && ewwp->pw.equipment & EQUIP_MILES_BOOSTER) // Booster
    {
        if (plobjects[319].obj)
        {
            njSetMatrix(NULL, &mtx_TornadoBoosterL);
            njCnkDrawObject(plobjects[319].obj);
        }

        if (plobjects[321].obj)
        {
            njSetMatrix(NULL, &mtx_TornadoBoosterR);
            njCnkDrawObject(plobjects[321].obj);
        }

        //njPopMatrixEx();
    }

    njCnkSetMotionCallback(NULL);
}

static void
DrawEggmanShadow(NJS_MOTION* motion, float frame)
{
    njCnkDrawMotion(plobjects[230].obj, motion, frame);
}

static void
DrawMilesShadow(NJS_MOTION* motion, float frame)
{
    MilesWorkPointer = (mileswk*) playerpwp[GetCharacterPlayer( PLNO_MILES )];

    njCnkSetMotionCallback(MilesMotionCallBack_p);
    njCnkDrawMotion(plobjects[208].obj, motion, frame);
}

static void __cdecl
njCnkDrawMotionHook(NJS_CNK_OBJECT* object, NJS_MOTION* motion, float frame)
{
    if (object == plobjects[48].obj) // Sonic
    {
        DrawSonicShadow(motion, frame);
        return;
    }

    if (object == plobjects[123].obj) // Shadow
    {
        DrawShadowShadow(motion, frame);
        return;
    }

    if (object == plobjects[142].obj) // Knuckes
    {
        DrawKnucklesShadow(motion, frame);
        return;
    }

    if (object == plobjects[171].obj) // Rouge
    {
        DrawRougeShadow(motion, frame);
        return;
    }

    if (object == plobjects[463].obj || object == plobjects[248].obj) // Mech Eggman
    {
        DrawEggWalkerShadow(motion, frame);
        return;
    }

    if (object == plobjects[464].obj || object == plobjects[293].obj) // Mech Tails
    {
        DrawTornadoShadow(motion, frame);
        return;
    }

    if (object == plobjects[527].obj) // Eggman
    {
        DrawEggmanShadow(motion, frame);
        return;
    }

    if (object == plobjects[528].obj) // Miles
    {
        DrawMilesShadow(motion, frame);
        return;
    }

    njCnkDrawMotion(object, motion, frame);
}

__declspec(naked)
static void 
__njCnkDrawMotionHook(void)
{
    __asm
    {
        push[esp + 08h] // frame
        push ecx        // motion
        push[esp + 0Ch] // object

        call njCnkDrawMotionHook

        add esp, 4        // object
        pop ecx            // motion
        add esp, 4        // frame
        retn
    }
}

static mt_config*
GetDisableUpgradeModelsConfig(void)
{
    const ml_modinfo* p_modinfo = miGetInfoByDllName("SA2DisableUpgradeModels");

    if ( !p_modinfo )
        return NULL;

    return miGetConfig(p_modinfo);
}

void
EnhancedPlayerShadowsInit(void)
{
    WriteCall(0x0071EA0F, __njCnkDrawMotionHook); // Sonic/Shadow

    WriteCall(0x0072E216, __njCnkDrawMotionHook); // Knux
    WriteCall(0x0072E28F, __njCnkDrawMotionHook);
    WriteCall(0x0072E8A6, __njCnkDrawMotionHook); // Rouge
    WriteCall(0x0072E91F, __njCnkDrawMotionHook);

    WriteCall(0x00745B63, __njCnkDrawMotionHook); // Mechs
    WriteCall(0x00745C11, __njCnkDrawMotionHook);

    WriteCall(0x0073E9F5, __njCnkDrawMotionHook); // Eggman
    WriteCall(0x0073EA50, __njCnkDrawMotionHook);

    WriteCall(0x0075013B, __njCnkDrawMotionHook); // Miles
    WriteCall(0x00750196, __njCnkDrawMotionHook);
    WritePointer(0x007501B2, &mtx_MilesTails);  // Point shader tails matrix to actual tails matrix
    WritePointer(0x00750230, &mtx_MilesTails);  // ^

    mt_config* pupgradeconf = GetDisableUpgradeModelsConfig();

    if (pupgradeconf)
    {
        DrawSonicFlameRing =  !mtConfigGetBool(pupgradeconf, "Sonic", "DisableFlameRing", true);
        DrawSonicRubberUnit = !mtConfigGetBool(pupgradeconf, "Sonic", "DisableBounceBracelet", true);
        DrawSonicMagicWrist = !mtConfigGetBool(pupgradeconf, "Sonic", "DisableMagicGloves", true);
        DrawSonicShoes =      !mtConfigGetBool(pupgradeconf, "Sonic", "DisableLightShoes", true);

        DrawShadowFlameRing = !mtConfigGetBool(pupgradeconf, "Shadow", "DisableFlameRing", true);
        DrawShadowShoes =     !mtConfigGetBool(pupgradeconf, "Shadow", "DisableAirShoes", true);

        DrawKnuxClaw =     !mtConfigGetBool(pupgradeconf, "Knuckles", "DisableShovelClaw", true);
        DrawKnuxAir =      !mtConfigGetBool(pupgradeconf, "Knuckles", "DisableAirNecklace", true);
        DrawKnuxGloves =   !mtConfigGetBool(pupgradeconf, "Knuckles", "DisableHammerGloves", true);
        DrawKnuxSunglass = !mtConfigGetBool(pupgradeconf, "Knuckles", "DisableSunglasses", true);

        DrawRougeNails = !mtConfigGetBool(pupgradeconf, "Rouge", "DisablePickNails", true);
        DrawRougeBoots = !mtConfigGetBool(pupgradeconf, "Rouge", "DisableIronBoots", true);
        DrawRougeScope = !mtConfigGetBool(pupgradeconf, "Rouge", "DisableTreasureScope", true);

        DrawMilesLazerBlaster = !mtConfigGetBool(pupgradeconf, "Tails", "DisableLaserBlaster", true) ? EQUIP_MD_FULL : EQUIP_MD_OG_ONLY;
        DrawMilesHyperCannon =  !mtConfigGetBool(pupgradeconf, "Tails", "DisableBazooka", true) ? EQUIP_MD_FULL : EQUIP_MD_OG_ONLY;
        DrawMilesBooster =      !mtConfigGetBool(pupgradeconf, "Tails", "DisableBooster", true);

        DrawEggmanPowerGun =    !mtConfigGetBool(pupgradeconf, "Eggman", "DisableLaserBlaster", true) ? EQUIP_MD_FULL : EQUIP_MD_OG_ONLY;
        DrawEggmanBazooka =     !mtConfigGetBool(pupgradeconf, "Eggman", "DisableLargeCannon", true) ? EQUIP_MD_FULL : EQUIP_MD_OG_ONLY;
        DrawEggmanJetEngine =   !mtConfigGetBool(pupgradeconf, "Eggman", "DisableJetEngine", true);
        DrawEggmanExtraShield = !mtConfigGetBool(pupgradeconf, "Eggman", "DisableProtectiveArmor", true);

        mtConfigFree(pupgradeconf);
    }
    else
    {
        DrawSonicFlameRing = true;
        DrawSonicRubberUnit = true;
        DrawSonicMagicWrist = true;
        DrawSonicShoes = true;

        DrawShadowFlameRing = true;
        DrawShadowShoes = true;

        DrawKnuxClaw = true;
        DrawKnuxAir = true;
        DrawKnuxGloves = true;
        DrawKnuxSunglass = true;

        DrawRougeNails = true;
        DrawRougeBoots = true;
        DrawRougeScope = true;

        DrawMilesLazerBlaster = EQUIP_MD_FULL;
        DrawMilesHyperCannon = EQUIP_MD_FULL;
        DrawMilesBooster = true;

        DrawEggmanPowerGun = EQUIP_MD_FULL;
        DrawEggmanBazooka = EQUIP_MD_FULL;
        DrawEggmanJetEngine = true;
        DrawEggmanExtraShield = true;
    }
}
