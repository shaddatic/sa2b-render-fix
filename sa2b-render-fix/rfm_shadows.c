#include <sa2b/core.h>
#include <sa2b/memory.h>
#include <sa2b/funchook.h>
#include <sa2b/mods.h>

/** Ninja **/
#include <sa2b/ninja/ninja.h>

/** Render Fix **/
#include <rf_core.h>
#include <rf_config.h>
#include <rf_mod.h>
#include <rf_draw.h>
#include <rf_util.h>
#include <rf_file.h>
#include <rf_usermsg.h>
#include <rf_objpak.h>

/** Self **/
#include <rfm_shadows.h>
#include <rfm_shadows/shd_internal.h>

/** Enums **/
typedef enum
{
    CHSMD_OFF,
    CHSMD_PERFORMANCE,
    CHSMD_ON,
}
eCHS_MODE;

enum
{
    GLSHD_OFF,
    GLSHD_VANILLA,
    GLSHD_MODIFIER,
};

enum
{
    OPACITY_PC,
    OPACITY_DREAMCAST,
    OPACITY_DREAMCAST_CHAO,
};

/** Constants **/
#define CHEAP_SHDW_MD_NORM  (0x50)
#define CHEAP_SHDW_MD_CHAO  (0x73)

static const float    OpacityList[] = { 0.75f, 0.6862745098039216f, 0.5490196078431373f };
static const uint32_t ResolutionList[] = { 256, 512, 1024, 2048, 4096, 8192 };

/** Globals **/
static float ShadowOpacityGlobal;
static float ShadowOpacityChao;

static eCHS_MODE CheapShadowMode;
static bool      CheapShadowPlayer;

static bool      ShadowWriteObjPak;

static NJS_CNK_MODEL* model_basic_shadow;

/** Static functions **/
static void
SetShadowOpacityGlobal(void)
{
    RFMOD_SetAlpha(ShadowOpacityGlobal);

    if (!ShadowWriteObjPak)
        return;

    RF_ObjPakRegisterShadowOpacity(ShadowOpacityGlobal);
    RF_ObjPakWriteChangesToFile();
}

static void
SetShadowOpacityChao(void)
{
    RFMOD_SetAlpha(ShadowOpacityChao);

    if (!ShadowWriteObjPak)
        return;

    RF_ObjPakRegisterShadowOpacity(ShadowOpacityChao);
    RF_ObjPakWriteChangesToFile();
}

/** Extern functions **/
void
njSetCheapShadowMode(int32_t mode)
{
    if (mode < 0)
    {
        RFMOD_SetAlpha(0.0f);
        return;
    }
    else if (mode > 255)
        mode = 255;

    RFMOD_SetAlphaI(255 - mode);
}

void
DrawBasicShadow(void)
{
    njCnkModDrawModel(model_basic_shadow);
}

bool
RF_CheapShadow(void)
{
    return CheapShadowMode != CHSMD_OFF;
}

bool
RF_CheapShadowPerformance(void)
{
    return CheapShadowMode == CHSMD_PERFORMANCE;
}

bool
RF_CheapShadowPlayer(void)
{
    return CheapShadowPlayer;
}

float
RF_ShadowOpacityGlobal(void)
{
    return ShadowOpacityGlobal;
}

float
RF_ShadowOpacityChao(void)
{
    return ShadowOpacityChao;
}

void
RFM_ShadowsInit(void)
{
    if (ModCheckDll("enhanced-shadows"))
    {
        RF_ModConflict("Enhanced Shadows",
            "The 'Enhanced Shadows' mod is obsolete and will conflict with Render Fix!\n\n"
            "Please disable the 'Enhanced Shadows' mod!");
        return;
    }

    /****** Cheap Shadows / Modifiers ******/
    {
        const eCHS_MODE chs_mode = RF_ConfigGetInt(CNF_SHADOW_CHS_MODE);

        if (chs_mode != CHSMD_OFF)
        {
            ___VITAL("Double check feature name");

            /** Mod check and warning **/
            if (ModCheckDll("sa2-dc-lighting"))
                RF_ModConflictEx("DC Shadows", "Modifer Shadows");

            /** Init modifier engine **/
            RFMOD_Init();

            /** Load basic shadow **/
            NJS_CNK_OBJECT* objp = RF_ChunkLoadObjectFile("basic_shadow");

            model_basic_shadow = objp->model;

            MemFree(objp); // We only use the model, so free
        }

        CheapShadowMode = chs_mode;
    }

    ShadowOpacityGlobal = OpacityList[RF_ConfigGetInt(CNF_SHADOW_GLOPACITY)];
    ShadowOpacityChao   = OpacityList[RF_ConfigGetInt(CNF_SHADOW_CHOPACITY)];

    ShadowWriteObjPak = RF_ConfigGetInt(CNF_EXP_SHD_OPACITY_SW) == 1;

    /** Set default alpha **/
    RFMOD_SetAlpha(ShadowOpacityGlobal);

    /** Shadow opacity function hooks **/
    Trampoline(0x0052AB7F, SetShadowOpacityChao);   // AL Constructor
    Trampoline(0x0052AEA9, SetShadowOpacityGlobal); // AL Destructor

    /****** Global Shadow Mode ******/

    switch (RF_ConfigGetInt(CNF_SHADOW_GLMODE)) {
    case GLSHD_MODIFIER:
        CHS_BoardInit();
        CHS_MessengerInit();
        CHS_BunchinInit();
        CHS_ModModInit();
        CHS_UdreelInit();
        CHS_SearchBoxInit();
        CHS_GoalRingInit();
        CHS_EnemyInit();
        CHS_IronBall2Init();
        CHS_EggQuatersRobotInit();
        CHS_ChaosDriveInit();
        CHS_MinimalInit();
        CHS_PickUpInit();
        CHS_TankInit();
        CHS_MDContainerBoxInit();
        CHS_MeteoBigInit();
        CHS_CCBlockInit();
        CHS_BossInit();
        CHS_CartInit();
        CHS_ChaoWorldInit();
        CHS_TruckInit();
        CHS_CarInit();
        break;

    case GLSHD_VANILLA:
        /** Vanilla shadows **/
        break;

    case GLSHD_OFF:
        WriteRetn(0x0046FBC0); // Disable all shadows
        return;
    }

    switch (RF_ConfigGetInt(CNF_SHADOW_PLMODE)) {
    case PL_SHDMD_MODIFIER:
        if (!RF_CheapShadow())
            break;

        CHS_PlayerInit();
        CheapShadowPlayer = true;
        break;

    case PL_SHDMD_ENH_EQUIP:
        EnhancedPlayerShadowsInit();
        EnhancedPlayerShadowsEquipmentInit();
        break;

    case PL_SHDMD_ENHANCED:
        EnhancedPlayerShadowsInit();
        break;

    case PL_SHDMD_VANILLA:
        /** Vanilla **/
        break;
    }

    const int resolution = RF_ConfigGetInt(CNF_SHADOW_RES);

    if (resolution != 1)
        WriteData(0x0041F810, ResolutionList[resolution], uint32_t);

    RF_ObjPakRegisterShadowOpacity( RF_ShadowOpacityGlobal() );
}
