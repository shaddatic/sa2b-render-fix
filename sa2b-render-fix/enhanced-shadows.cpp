#define _CRT_SECURE_NO_WARNINGS

#include <sa2b/core.h>
#include <sa2b/config.h>
#include <sa2b/memtools.h>
#include <sa2b/mods.h>

#include <sa2b/ninja/ninja.h>

#include <sa2b/src/player.h>

#include <sa2b/src/figure/sonic.h>
#include <sa2b/src/figure/shadow.h>
#include <sa2b/src/figure/miles.h>
#include <sa2b/src/figure/knuckles.h>
#include <sa2b/src/figure/rouge.h>
#include <sa2b/src/figure/ewalker.h>
#include <sa2b/src/figure/twalker.h>

#include <tools.h>

static int DrawSonicFlameRing;
static int DrawSonicRubberUnit;
static int DrawSonicMagicWrist;
static int DrawSonicShoes;

static int DrawShadowFlameRing;
static int DrawShadowShoes;

static int DrawKnuxClaw;
static int DrawKnuxAir;
static int DrawKnuxGloves;
static int DrawKnuxSunglass;

static int DrawRougeNails;
static int DrawRougeBoots;
static int DrawRougeScope;

static int DrawMilesLazerBlaster;
static int DrawMilesHyperCannon;
static int DrawMilesBooster;

static int DrawEggmanPowerGun;
static int DrawEggmanBazooka;
static int DrawEggmanJetEngine;
static int DrawEggmanExtraShield;

static int
GetCharacterPlayer(int character)
{
    return (int)(playerpwp[1] && playerpwp[1]->ch_num == character);
}

static void
DrawSonicShadow(NJS_MOTION* motion, float frame)
{
    SONICWK* spwp = (SONICWK*)playerpwp[GetCharacterPlayer(ADV2_PLNO_SONIC)];
    pSonicWork = spwp;

    njCnkSetMotionCallback(SonicMotionCallBack);
    njCnkDrawMotion(CHAR_OBJECTS[0].pObject, motion, frame);

    if (DrawSonicFlameRing && spwp->pwk.equipment & EQUIP_SONIC_FLAMERING)
    {
        if (CHAR_OBJECTS[25].pObject)
        {
            njSetMatrix(0, &mtx_SonicHandR);
            njCnkDrawModel(CHAR_OBJECTS[25].pObject->model);
        }
    }

    if (DrawSonicRubberUnit && spwp->pwk.equipment & EQUIP_SONIC_RUBBERUNIT)
    {
        if (CHAR_OBJECTS[26].pObject)
        {
            njSetMatrix(0, &mtx_SonicHandL);
            njCnkDrawModel(CHAR_OBJECTS[26].pObject->model);
        }
    }

    if (DrawSonicMagicWrist && spwp->pwk.equipment & EQUIP_SONIC_MAGICWRIST)
    {
        if (CHAR_OBJECTS[27].pObject)
        {
            njSetMatrix(0, &mtx_SonicHandL);
            njCnkDrawObject(CHAR_OBJECTS[27].pObject);
        }
    }

    if (DrawSonicShoes && spwp->pwk.equipment & EQUIP_SONIC_SHOES)
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
    SONICWK* spwp = (SONICWK*)playerpwp[GetCharacterPlayer(ADV2_PLNO_SHADOW)];
    pSonicWork = spwp;

    njCnkSetMotionCallback(ShadowMotionCallBack);
    njCnkDrawMotion(CHAR_OBJECTS[65].pObject, motion, frame);

    if (DrawShadowFlameRing && spwp->pwk.equipment & EQUIP_SHADOW_FLAMERING) // Flame Ring
    {
        if (CHAR_OBJECTS[100].pObject)
        {
            njSetMatrix(NULL, &mtx_SonicHandR);
            njCnkDrawModel(CHAR_OBJECTS[100].pObject->model);
        }
    }

    if (DrawShadowShoes && spwp->pwk.equipment & EQUIP_SHADOW_SHOES) // Air Shoes
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
    KNUCKLESWK* kwp = (KNUCKLESWK*)playerpwp[GetCharacterPlayer(ADV2_PLNO_KNUCKLES)];
    pKnucklesWork = kwp;

    njCnkSetMotionCallback(KnucklesMotionCallBack);
    njCnkDrawMotion(CHAR_OBJECTS[142].pObject, motion, frame);

    njPushMatrixEx();

    if (DrawKnuxSunglass && kwp->pwk.equipment & EQUIP_KNUCKLES_SUNGLASS)
    {
        NJS_CNK_OBJECT* pobj = CHAR_OBJECTS[161].pObject->child;

        njSetMatrix(NULL, &mtx_KnucklesHead);
        njTranslateEx((NJS_VECTOR*)pobj->pos);

        if (kwp->someHeadAng != 0x2000)
            njRotateZ(0, kwp->someHeadAng - 0x2000);

        njCnkDrawModel(pobj->model);
    }

    if (DrawKnuxAir && kwp->pwk.equipment & EQUIP_KNUCKLES_AIR)
    {
        njSetMatrix(NULL, &mtx_KnucklesBody);
        njCnkDrawObject(CHAR_OBJECTS[168].pObject);
    }

    if ((DrawKnuxClaw || DrawKnuxGloves) && kwp->pwk.equipment & (EQUIP_KNUCKLES_GROVES | EQUIP_KNUCKLES_CLAW))
    {
        njSetMatrix(NULL, &mtx_KnucklesHandL);
        if (DrawKnuxClaw && kwp->pwk.equipment & EQUIP_KNUCKLES_CLAW && CHAR_OBJECTS[162].pObject)
        {
            njCnkDrawObject(CHAR_OBJECTS[162].pObject);
        }
        if (DrawKnuxGloves && kwp->pwk.equipment & EQUIP_KNUCKLES_GROVES && CHAR_OBJECTS[164].pObject)
        {
            njCnkDrawObject(CHAR_OBJECTS[164].pObject);
        }
        njSetMatrix(NULL, &mtx_KnucklesHandR);
        if (DrawKnuxClaw && kwp->pwk.equipment & EQUIP_KNUCKLES_CLAW && CHAR_OBJECTS[163].pObject)
        {
            njCnkDrawObject(CHAR_OBJECTS[163].pObject);
        }
        if (DrawKnuxGloves && kwp->pwk.equipment & EQUIP_KNUCKLES_GROVES && CHAR_OBJECTS[165].pObject)
        {
            njCnkDrawObject(CHAR_OBJECTS[165].pObject);
        }
    }

    njPopMatrixEx();

    njCnkSetMotionCallback(NULL);
}

static void
DrawRougeShadow(NJS_MOTION* motion, float frame)
{
    KNUCKLESWK* rwp = (KNUCKLESWK*)playerpwp[GetCharacterPlayer(ADV2_PLNO_ROUGE)];
    pKnucklesWork = rwp;

    njCnkSetMotionCallback(RougeMotionCallBack);
    njCnkDrawMotion(CHAR_OBJECTS[171].pObject, motion, frame);

    njPushMatrixEx();

    if (DrawRougeScope && rwp->pwk.equipment & EQUIP_ROUGE_SCOPE)
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

    if (DrawRougeBoots && rwp->pwk.equipment & EQUIP_ROUGE_BOOTS)
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

    if (DrawRougeNails && rwp->pwk.equipment & EQUIP_ROUGE_NAILS)
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
    WALKERWK* ewwp = (WALKERWK*)playerpwp[GetCharacterPlayer(ADV2_PLNO_EGGWALKER)];
    pEWalkerWork = ewwp;

    njCnkSetMotionCallback(EggWalkerMotionCallBack);
    njCnkDrawMotion(CHAR_OBJECTS[248].pObject, motion, frame);

    if (DrawEggmanPowerGun)
    {
        const int num = DrawEggmanPowerGun == 2 && (ewwp->pwk.equipment & EQUIP_EGGMAN_POWERGUN) ? 260 : 258;

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
        if (DrawEggmanBazooka == 2 && ewwp->pwk.equipment & EQUIP_EGGMAN_BAZOOKA) // Large Cannon
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

    if (DrawEggmanJetEngine && ewwp->pwk.equipment & EQUIP_EGGMAN_JETENGINE) // Jets
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

    if (DrawEggmanExtraShield && ewwp->pwk.equipment & EQUIP_EGGMAN_EXTRASHIELD) // Armor
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
    WALKERWK* ewwp = (WALKERWK*)playerpwp[GetCharacterPlayer(ADV2_PLNO_TORNADO)];
    pEWalkerWork = ewwp;

    njCnkSetMotionCallback(TornadoMotionCallBack);
    njCnkDrawMotion(CHAR_OBJECTS[293].pObject, motion, frame);

    if (DrawMilesLazerBlaster)
    {
        const int num = DrawMilesLazerBlaster == 2 && (ewwp->pwk.equipment & EQUIP_MILES_LASERBALSTER) ? 306 : 304;

        NJS_CNK_OBJECT* blaster = CHAR_OBJECTS[num].pObject;

        if (blaster)
        {
            njSetMatrix(NULL, &mtx_EWalkerLaserBlaster);
            while (blaster)	// laser blaster
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
        if (DrawMilesHyperCannon == 2 && ewwp->pwk.equipment & EQUIP_MILES_HYPERCANNON)
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

    if (DrawMilesBooster && ewwp->pwk.equipment & EQUIP_MILES_BOOSTER) // Booster
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
    pMilesWork = (MILESWK*)playerpwp[GetCharacterPlayer(ADV2_PLNO_TAILS)];

    njCnkSetMotionCallback(MilesMotionCallBack);
    njCnkDrawMotion(CHAR_OBJECTS[208].pObject, motion, frame);
}

static void __cdecl
_CnkDrawMotionHook(NJS_CNK_OBJECT* object, NJS_MOTION* motion, float frame)
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

static void __declspec(naked)
njCnkDrawMotionHook()
{
    __asm
    {
        push[esp + 08h] // frame
        push ecx		// motion
        push[esp + 0Ch] // object

        call _CnkDrawMotionHook

        add esp, 4		// object
        pop ecx			// motion
        add esp, 4		// frame
        retn
    }
}

static config*
GetDisableUpgradeModelsConfig()
{
    mod_handle* shadow = GetModHandle("SA2DisableUpgradeModels");

    if (!shadow)
        return NULL;

    return GetModConfig(shadow);
}

static float OpacityList[] = { 0.25f, 0.3f, 0.375f, 0.5f };

static uint32 ResolutionList[] = { 256, 512, 1024, 2048, 4096, 8192 };

#define SECT "shadows"

static float ShadowOpacity = -1.0f;

float
GetShadowOpacitySetting()
{
    return ShadowOpacity;
}

void
ShadowSettings(const config* pConf)
{
    if (CheckForMod("enhanced-shadows"))
    {
        ModConflictWarning("The 'Enhanced Shadows' mod is obsolete and will conflict with Render Fix!\n\n"
            "Please disable the 'Enhanced Shadows' mod!");
        return;
    }

    int mode = ConfigGetInt(pConf, SECT, "enable", 2);

    if (!mode) // Disabled
    {
        WriteRetn(0x0046FBC0);
        return;
    }
    
    if (mode == 2) // Enhanced
    {
        WriteCall(0x0071EA0F, njCnkDrawMotionHook); // Sonic/Shadow

        WriteCall(0x0072E216, njCnkDrawMotionHook); // Knux
        WriteCall(0x0072E28F, njCnkDrawMotionHook);
        WriteCall(0x0072E8A6, njCnkDrawMotionHook); // Rouge
        WriteCall(0x0072E91F, njCnkDrawMotionHook);

        WriteCall(0x00745B63, njCnkDrawMotionHook); // Mechs
        WriteCall(0x00745C11, njCnkDrawMotionHook);

        WriteCall(0x0073E9F5, njCnkDrawMotionHook); // Eggman
        WriteCall(0x0073EA50, njCnkDrawMotionHook);

        WriteCall(0x0075013B, njCnkDrawMotionHook); // Miles
        WriteCall(0x00750196, njCnkDrawMotionHook);
        WritePointer(0x007501B2, &mtx_MilesTails);	// Point shader tails matrix to actual tails matrix
        WritePointer(0x00750230, &mtx_MilesTails);	// ^

        if (ConfigGetInt(pConf, SECT, "equipment", 1))
        {
            config* pupgradeconf = GetDisableUpgradeModelsConfig();

            if (pupgradeconf)
            {
                DrawSonicFlameRing =    !ConfigGetBool(pupgradeconf, "Sonic", "DisableFlameRing", true);
                DrawSonicRubberUnit =   !ConfigGetBool(pupgradeconf, "Sonic", "DisableBounceBracelet", true);
                DrawSonicMagicWrist =   !ConfigGetBool(pupgradeconf, "Sonic", "DisableMagicGloves", true);
                DrawSonicShoes =        !ConfigGetBool(pupgradeconf, "Sonic", "DisableLightShoes", true);

                DrawShadowFlameRing =   !ConfigGetBool(pupgradeconf, "Shadow", "DisableFlameRing", true);
                DrawShadowShoes =       !ConfigGetBool(pupgradeconf, "Shadow", "DisableAirShoes", true);

                DrawKnuxClaw =          !ConfigGetBool(pupgradeconf, "Knuckles", "DisableShovelClaw", true);
                DrawKnuxAir =           !ConfigGetBool(pupgradeconf, "Knuckles", "DisableAirNecklace", true);
                DrawKnuxGloves =        !ConfigGetBool(pupgradeconf, "Knuckles", "DisableHammerGloves", true);
                DrawKnuxSunglass =      !ConfigGetBool(pupgradeconf, "Knuckles", "DisableSunglasses", true);

                DrawRougeNails =        !ConfigGetBool(pupgradeconf, "Rouge", "DisablePickNails", true);
                DrawRougeBoots =        !ConfigGetBool(pupgradeconf, "Rouge", "DisableIronBoots", true);
                DrawRougeScope =        !ConfigGetBool(pupgradeconf, "Rouge", "DisableTreasureScope", true);

                DrawMilesLazerBlaster = !ConfigGetBool(pupgradeconf, "Tails", "DisableLaserBlaster", true) ? 2 : 1;
                DrawMilesHyperCannon =  !ConfigGetBool(pupgradeconf, "Tails", "DisableBazooka", true) ? 2 : 1;
                DrawMilesBooster =      !ConfigGetBool(pupgradeconf, "Tails", "DisableBooster", true);

                DrawEggmanPowerGun =    !ConfigGetBool(pupgradeconf, "Eggman", "DisableLaserBlaster", true) ? 2 : 1;
                DrawEggmanBazooka =     !ConfigGetBool(pupgradeconf, "Eggman", "DisableLargeCannon", true) ? 2 : 1;
                DrawEggmanJetEngine =   !ConfigGetBool(pupgradeconf, "Eggman", "DisableJetEngine", true);
                DrawEggmanExtraShield = !ConfigGetBool(pupgradeconf, "Eggman", "DisableProtectiveArmor", true);

                ConfigClose(pupgradeconf);
            }
            else
            {
                DrawSonicFlameRing = 1;
                DrawSonicRubberUnit = 1;
                DrawSonicMagicWrist = 1;
                DrawSonicShoes = 1;

                DrawShadowFlameRing = 1;
                DrawShadowShoes = 1;

                DrawKnuxClaw = 1;
                DrawKnuxAir = 1;
                DrawKnuxGloves = 1;
                DrawKnuxSunglass = 1;

                DrawRougeNails = 1;
                DrawRougeBoots = 1;
                DrawRougeScope = 1;

                DrawMilesLazerBlaster = 2;
                DrawMilesHyperCannon = 2;
                DrawMilesBooster = 1;

                DrawEggmanPowerGun = 2;
                DrawEggmanBazooka = 2;
                DrawEggmanJetEngine = 1;
                DrawEggmanExtraShield = 1;
            }
        }
    }

    int resolution = ConfigGetInt(pConf, SECT, "resolution", 1);

    if (resolution != 1)
        WriteData(0x0041F810, ResolutionList[resolution], uint32);

    int opacity = ConfigGetInt(pConf, SECT, "opacity", 0);

    ShadowOpacity = OpacityList[opacity];
}