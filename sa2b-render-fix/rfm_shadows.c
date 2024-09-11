#include <sa2b/core.h>
#include <sa2b/memory.h>
#include <sa2b/funchook.h>
#include <sa2b/writeop.h>

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

/** Constants **/
#define CHEAP_SHDW_MD_NORM  (0x50)
#define CHEAP_SHDW_MD_CHAO  (0x73)

static const float    OpacityList[]    = { 0.75f, 0.6862745098039216f, 0.5490196078431373f };
static const uint32_t ResolutionList[] = { 256, 512, 1024, 2048, 4096, 8192 };

/** Globals **/
static float ShadowOpacityGlobal;
static float ShadowOpacityChao;

static int  CheapShadowMode;
static bool CheapShadowPlayer;

static bool ShadowWriteObjPak;

static NJS_CNK_MODEL* model_basic_shadow;

/** Static functions **/
static void
CHS_ObjectBurstInit(void)
{
    WriteRetn(0x004AF660); // Kill disp_shad
    KillCall( 0x004AE522); // Kill SetStencilInfo
}

static void
CHS_ObjectMSMadBox(void)
{
    WriteRetn(0x0064FD40); // Kill disp_shad
    KillCall( 0x0064F999); // Kill SetStencilInfo
}

static void
CHS_ObjectMDContWood(void)
{
    WriteRetn(0x005C43C0); // Kill disp_shad
    KillCall( 0x005C455E); // Kill SetStencilInfo
}

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
DrawBasicShadow(void)
{
    njCnkModDrawModel(model_basic_shadow);
}

bool
RFF_CheapShadow(void)
{
    return CheapShadowMode != CNFE_SHADOW_CHSMD_DISABLED;
}

bool
RFF_CheapShadowPerformance(void)
{
    return CheapShadowMode == CNFE_SHADOW_CHSMD_PERFORMANCE;
}

bool
RFF_CheapShadowUltraPerformance(void)
{
    return false;
}

bool
RFF_CheapShadowPlayer(void)
{
    return CheapShadowPlayer;
}

float
RFF_ShadowOpacityGlobal(void)
{
    return ShadowOpacityGlobal;
}

float
RFF_ShadowOpacityChao(void)
{
    return ShadowOpacityChao;
}

void
RFM_ShadowsInit(void)
{
    /****** Cheap Shadows / Modifiers ******/
    {
        const CNFE_SHADOW_CHSMD chs_mode = RF_ConfigGetInt(CNF_SHADOW_CHSMD);

        if (chs_mode != CNFE_SHADOW_CHSMD_DISABLED)
        {
            /** Init modifier engine **/
            RFMOD_Init();

            /** Load basic shadow **/
            {
                NJS_CNK_OBJECT* objp = RF_ChunkLoadObjectFile("basic_shadow");

                model_basic_shadow = objp->model;

                MemFree(objp); // We only use the model, so free
            }

            if (RF_ConfigGetInt(CNF_DEBUG_MODIFIER))
                RFMOD_SetDrawMode(MODMD_DEBUG);

            CheapShadowMode = chs_mode;
        }
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

    switch (RF_ConfigGetInt(CNF_SHADOW_GLMD)) {
    case CNFE_SHADOW_GLMD_MODIFIER:

        if (!RFF_CheapShadow())
            break;

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
        CHS_ObjectBurstInit();
        CHS_ObjectMSMadBox();
        CHS_ObjectMDContWood();
        break;

    case CNFE_SHADOW_GLMD_VANILLA:
        /** Vanilla shadows **/
        break;

    case CNFE_SHADOW_GLMD_DISABLED:
        WriteRetn(0x0046FBC0); // Disable all shadows
        return;
    }

    switch (RF_ConfigGetInt(CNF_SHADOW_PLMD)) {
    case CNFE_SHADOW_PLMD_MODIFIER:

        if (!RFF_CheapShadow())
            break;

        CHS_PlayerInit();
        CheapShadowPlayer = true;
        break;

    case CNFE_SHADOW_PLMD_EQUIPMENT:
        EnhancedPlayerShadowsInit();
        EnhancedPlayerShadowsEquipmentInit();
        break;

    case CNFE_SHADOW_PLMD_ENHANCED:
        EnhancedPlayerShadowsInit();
        break;

    case CNFE_SHADOW_PLMD_VANILLA:
        /** Vanilla **/
        break;
    }

    const int resolution = RF_ConfigGetInt(CNF_SHADOW_RES);

    if (resolution != 1)
        WriteData(0x0041F810, ResolutionList[resolution], uint32_t);

    RF_ObjPakRegisterShadowOpacity( RFF_ShadowOpacityGlobal() );
}
