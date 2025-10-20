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
#include <rf_config.h>

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
    return (int)(playerpwp[1] && playerpwp[1]->ch_num == character);
}

static void
DrawSonicShadow(NJS_MOTION* motion, float frame)
{
    SONICWK* spwp = (SONICWK*)playerpwp[ GetCharacterPlayer( PLNO_SONIC ) ];
    SonicWorkPointer = spwp;

    njCnkSetMotionCallback(SonicMotionCallBack_p);
    njCnkDrawMotion(CHAR_OBJECTS[0].pObject, motion, frame);

    if (DrawSonicFlameRing && spwp->pw.equipment & EQUIP_SONIC_FLAMERING)
    {
        if (CHAR_OBJECTS[25].pObject)
        {
            njSetMatrix(0, &mtx_SonicHandR);
            njCnkDrawModel(CHAR_OBJECTS[25].pObject->model);
        }
    }

    if (DrawSonicRubberUnit && spwp->pw.equipment & EQUIP_SONIC_RUBBERUNIT)
    {
        if (CHAR_OBJECTS[26].pObject)
        {
            njSetMatrix(0, &mtx_SonicHandL);
            njCnkDrawModel(CHAR_OBJECTS[26].pObject->model);
        }
    }

    if (DrawSonicMagicWrist && spwp->pw.equipment & EQUIP_SONIC_MAGICWRIST)
    {
        if (CHAR_OBJECTS[27].pObject)
        {
            njSetMatrix(0, &mtx_SonicHandL);
            njCnkDrawObject(CHAR_OBJECTS[27].pObject);
        }
    }

    if (DrawSonicShoes && spwp->pw.equipment & EQUIP_SONIC_SHOES)
    {
        if (CHAR_OBJECTS[14].pObject)
        {
            njSetMatrix(0, &mtx_SonicFootL);
            njCnkDrawObject(CHAR_OBJECTS[14].pObject);
        }

        if (CHAR_OBJECTS[13].pObject)
        {
            njSetMatrix(0, &mtx_SonicFootR);
            njCnkDrawObject(CHAR_OBJECTS[13].pObject);
        }
    }

    njCnkSetMotionCallback(NULL);
}

static void
DrawShadowShadow(NJS_MOTION* motion, float frame)
{
    SONICWK* spwp = (SONICWK*)playerpwp[ GetCharacterPlayer(PLNO_SHADOW) ];
    SonicWorkPointer = spwp;

    njCnkSetMotionCallback(ShadowMotionCallBack_p);
    njCnkDrawMotion(CHAR_OBJECTS[65].pObject, motion, frame);

    if (DrawShadowFlameRing && spwp->pw.equipment & EQUIP_SHADOW_FLAMERING) // Flame Ring
    {
        if (CHAR_OBJECTS[100].pObject)
        {
            njSetMatrix(NULL, &mtx_SonicHandR);
            njCnkDrawModel(CHAR_OBJECTS[100].pObject->model);
        }
    }

    if (DrawShadowShoes && spwp->pw.equipment & EQUIP_SHADOW_SHOES) // Air Shoes
    {
        if (CHAR_OBJECTS[79].pObject)
        {
            njSetMatrix(NULL, &mtx_SonicFootL);
            njCnkDrawObject(CHAR_OBJECTS[79].pObject);
        }

        if (CHAR_OBJECTS[78].pObject)
        {
            njSetMatrix(NULL, &mtx_ShadowFootR);
            njCnkDrawObject(CHAR_OBJECTS[78].pObject);
        }
    }

    njCnkSetMotionCallback(NULL);
}

static void
DrawKnucklesShadow(NJS_MOTION* motion, float frame)
{
    KNUCKLESWK* kwp = (KNUCKLESWK*)playerpwp[GetCharacterPlayer( PLNO_KNUCKLES )];
    KnucklesWorkPointer = kwp;

    njCnkSetMotionCallback(KnucklesMotionCallBack_p);
    njCnkDrawMotion(CHAR_OBJECTS[142].pObject, motion, frame);

    njPushMatrixEx();

    if (DrawKnuxSunglass && kwp->pw.equipment & EQUIP_KNUCKLES_SUNGLASS)
    {
        if (CHAR_OBJECTS[161].pObject)
        {
            NJS_CNK_OBJECT* pobj = CHAR_OBJECTS[161].pObject->child;

            njSetMatrix(NULL, &mtx_KnucklesHead);
            njTranslateEx((NJS_VECTOR*)pobj->pos);

            if (kwp->someHeadAng != 0x2000)
                njRotateZ(0, kwp->someHeadAng - 0x2000);

            njCnkDrawModel(pobj->model);
        }
    }

    if (DrawKnuxAir && kwp->pw.equipment & EQUIP_KNUCKLES_AIR)
    {
        if (CHAR_OBJECTS[168].pObject)
        {
            njSetMatrix(NULL, &mtx_KnucklesBody);
            njCnkDrawObject(CHAR_OBJECTS[168].pObject);
        }
    }

    if ((DrawKnuxClaw || DrawKnuxGloves) && kwp->pw.equipment & (EQUIP_KNUCKLES_GROVES | EQUIP_KNUCKLES_CLAW))
    {
        njSetMatrix(NULL, &mtx_KnucklesHandL);
        if (DrawKnuxClaw && kwp->pw.equipment & EQUIP_KNUCKLES_CLAW)
        {
            if (CHAR_OBJECTS[162].pObject)
            {
                njCnkDrawObject(CHAR_OBJECTS[162].pObject);
            }
        }
        if (DrawKnuxGloves && kwp->pw.equipment & EQUIP_KNUCKLES_GROVES)
        {
            if (CHAR_OBJECTS[164].pObject)
            {
                njCnkDrawObject(CHAR_OBJECTS[164].pObject);
            }
        }
        njSetMatrix(NULL, &mtx_KnucklesHandR);
        if (DrawKnuxClaw && kwp->pw.equipment & EQUIP_KNUCKLES_CLAW)
        {
            if (CHAR_OBJECTS[163].pObject)
            {
                njCnkDrawObject(CHAR_OBJECTS[163].pObject);
            }
        }
        if (DrawKnuxGloves && kwp->pw.equipment & EQUIP_KNUCKLES_GROVES)
        {
            if (CHAR_OBJECTS[165].pObject)
            {
                njCnkDrawObject(CHAR_OBJECTS[165].pObject);
            }
        }
    }

    njPopMatrixEx();

    njCnkSetMotionCallback(NULL);
}

static void
DrawRougeShadow(NJS_MOTION* motion, float frame)
{
    KNUCKLESWK* rwp = (KNUCKLESWK*)playerpwp[ GetCharacterPlayer( PLNO_ROUGE ) ];
    KnucklesWorkPointer = rwp;

    njCnkSetMotionCallback(RougeMotionCallBack_p);
    njCnkDrawMotion(CHAR_OBJECTS[171].pObject, motion, frame);

    njPushMatrixEx();

    if (DrawRougeScope && rwp->pw.equipment & EQUIP_ROUGE_SCOPE)
    {
        if (CHAR_OBJECTS[205].pObject)
        {
            NJS_CNK_OBJECT* pobj = CHAR_OBJECTS[205].pObject;

            njSetMatrix(NULL, &mtx_KnucklesHead);
            njCnkDrawModel(pobj->model);

            pobj = pobj->child;

            njTranslateEx((NJS_VECTOR*)pobj->pos);

            if (rwp->someHeadAng != 0x2000)
                njRotateZ(0, rwp->someHeadAng - 0x2000);

            njCnkDrawModel(pobj->model);
        }
    }

    if (DrawRougeBoots && rwp->pw.equipment & EQUIP_ROUGE_BOOTS)
    {
        if (CHAR_OBJECTS[201].pObject)
        {
            njSetMatrix(NULL, &mtx_KnucklesHandL);
            njCnkDrawObject(CHAR_OBJECTS[201].pObject);
        }

        if (CHAR_OBJECTS[203].pObject)
        {
            njSetMatrix(NULL, &mtx_KnucklesHandR);
            njCnkDrawObject(CHAR_OBJECTS[203].pObject);
        }
    }

    if (DrawRougeNails && rwp->pw.equipment & EQUIP_ROUGE_NAILS)
    {
        if (CHAR_OBJECTS[199].pObject)
        {
            njSetMatrix(NULL, &mtx_RougeBootL);
            njCnkDrawObject(CHAR_OBJECTS[199].pObject);
        }

        if (CHAR_OBJECTS[195].pObject)
        {
            njSetMatrix(NULL, &mtx_RougeBootR);
            njCnkDrawObject(CHAR_OBJECTS[195].pObject);
        }
    }

    njPopMatrixEx();

    njCnkSetMotionCallback(NULL);
}

static void
DrawEggWalkerShadow(NJS_MOTION* motion, float frame)
{
    WALKERWK* ewwp = (WALKERWK*)playerpwp[ GetCharacterPlayer( PLNO_EGG_WALKER ) ];
    EggWalkerWorkPointer = ewwp;

    njCnkSetMotionCallback(EggWalkerMotionCallBack_p);
    njCnkDrawMotion(CHAR_OBJECTS[248].pObject, motion, frame);

    if (DrawEggmanPowerGun)
    {
        const int num = DrawEggmanPowerGun == EQUIP_MD_FULL && (ewwp->pw.equipment & EQUIP_EGGMAN_POWERGUN) ? 260 : 258;

        NJS_CNK_OBJECT* powergun = CHAR_OBJECTS[num].pObject;

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
            if (CHAR_OBJECTS[263].pObject)
            {
                njTranslate(NULL, 1.0f - njCos(ewwp->CannonRecoil), 0, 0);
                njCnkDrawObject(CHAR_OBJECTS[263].pObject);
            }
        }
        else
        {
            if (CHAR_OBJECTS[266].pObject)
            {
                njCnkDrawObject(CHAR_OBJECTS[266].pObject);
            }
        }
    }

    if (DrawEggmanJetEngine && ewwp->pw.equipment & EQUIP_EGGMAN_JETENGINE) // Jets
    {
        //njPushMatrixEx();

        if (CHAR_OBJECTS[274].pObject)
        {
            njSetMatrix(NULL, &mtx_EWalkerJetEngineL);
            njCnkDrawObject(CHAR_OBJECTS[274].pObject);
        }

        if (CHAR_OBJECTS[276].pObject)
        {
            njSetMatrix(NULL, &mtx_EWalkerJetEngineR);
            njCnkDrawObject(CHAR_OBJECTS[276].pObject);
        }

        //njPopMatrixEx();
    }

    if (DrawEggmanExtraShield && ewwp->pw.equipment & EQUIP_EGGMAN_EXTRASHIELD) // Armor
    {
        if (CHAR_OBJECTS[278].pObject)
        {
            njPushMatrix(&mtx_EWalkerProtectiveArmor);
            njCnkDrawObject(CHAR_OBJECTS[278].pObject);
            njPopMatrixEx();
        }
    }

    njCnkSetMotionCallback(NULL);
}

static void
DrawTornadoShadow(NJS_MOTION* motion, float frame)
{
    WALKERWK* ewwp = (WALKERWK*)playerpwp[ GetCharacterPlayer( PLNO_TAILS_WALKER ) ];
    EggWalkerWorkPointer = ewwp;

    njCnkSetMotionCallback(TornadoWalkerMotionCallBack_p);
    njCnkDrawMotion(CHAR_OBJECTS[293].pObject, motion, frame);

    if (DrawMilesLazerBlaster)
    {
        const int num = DrawMilesLazerBlaster == EQUIP_MD_FULL && (ewwp->pw.equipment & EQUIP_MILES_LASERBALSTER) ? 306 : 304;

        NJS_CNK_OBJECT* blaster = CHAR_OBJECTS[num].pObject;

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
            NJS_CNK_OBJECT* hypercannon = CHAR_OBJECTS[309].pObject;

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
            NJS_CNK_OBJECT* hypercannon = CHAR_OBJECTS[312].pObject;

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
        if (CHAR_OBJECTS[319].pObject)
        {
            njSetMatrix(NULL, &mtx_TornadoBoosterL);
            njCnkDrawObject(CHAR_OBJECTS[319].pObject);
        }

        if (CHAR_OBJECTS[321].pObject)
        {
            njSetMatrix(NULL, &mtx_TornadoBoosterR);
            njCnkDrawObject(CHAR_OBJECTS[321].pObject);
        }

        //njPopMatrixEx();
    }

    njCnkSetMotionCallback(NULL);
}

static void
DrawEggmanShadow(NJS_MOTION* motion, float frame)
{
    njCnkDrawMotion(CHAR_OBJECTS[230].pObject, motion, frame);
}

static void
DrawMilesShadow(NJS_MOTION* motion, float frame)
{
    MilesWorkPointer = (MILESWK*)playerpwp[GetCharacterPlayer( PLNO_MILES )];

    njCnkSetMotionCallback(MilesMotionCallBack_p);
    njCnkDrawMotion(CHAR_OBJECTS[208].pObject, motion, frame);
}

static void __cdecl
njCnkDrawMotionHook(NJS_CNK_OBJECT* object, NJS_MOTION* motion, float frame)
{
    if (object == CHAR_OBJECTS[48].pObject) // Sonic
    {
        DrawSonicShadow(motion, frame);
        return;
    }

    if (object == CHAR_OBJECTS[123].pObject) // Shadow
    {
        DrawShadowShadow(motion, frame);
        return;
    }

    if (object == CHAR_OBJECTS[142].pObject) // Knuckes
    {
        DrawKnucklesShadow(motion, frame);
        return;
    }

    if (object == CHAR_OBJECTS[171].pObject) // Rouge
    {
        DrawRougeShadow(motion, frame);
        return;
    }

    if (object == CHAR_OBJECTS[463].pObject || object == CHAR_OBJECTS[248].pObject) // Mech Eggman
    {
        DrawEggWalkerShadow(motion, frame);
        return;
    }

    if (object == CHAR_OBJECTS[464].pObject || object == CHAR_OBJECTS[293].pObject) // Mech Tails
    {
        DrawTornadoShadow(motion, frame);
        return;
    }

    if (object == CHAR_OBJECTS[527].pObject) // Eggman
    {
        DrawEggmanShadow(motion, frame);
        return;
    }

    if (object == CHAR_OBJECTS[528].pObject) // Miles
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

        mtConfigClose(pupgradeconf);
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
