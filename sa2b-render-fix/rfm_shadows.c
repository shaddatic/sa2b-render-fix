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

/** External Functions **/
void RFG_ForceShadowMaps( void );

/** Constants **/
#define CHEAPSHDWMD_NORMAL              ( 80)
#define CHEAPSHDWMD_CHAO                (115)

#define CHEAPSHDWMD_TO_FLOAT(mode)      (1.f-((Float)(mode)*(1.f/256.f)))

static const uint32_t ResolutionList[] = { 256, 512, 1024, 2048, 4096, 8192 };

/** Globals **/
static int  CheapShadowMode;
static bool CheapShadowPlayer;

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
    rjSetCheapShadowMode(CHEAPSHDWMD_NORMAL);
}

static void
SetShadowOpacityChao(void)
{
    rjSetCheapShadowMode(CHEAPSHDWMD_CHAO);
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
RFF_CheapShadowPlayer(void)
{
    return CheapShadowPlayer;
}

f32
RFF_ShadowOpacityGlobal(void)
{
    return CHEAPSHDWMD_TO_FLOAT( CHEAPSHDWMD_NORMAL );
}

f32
RFF_ShadowOpacityChao(void)
{
    return CHEAPSHDWMD_TO_FLOAT( CHEAPSHDWMD_CHAO );
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

            model_basic_shadow = RF_ChunkLoadModelFile("common/basic_mod");

            if (RF_ConfigGetInt(CNF_DEBUG_MODIFIER))
                RFMOD_SetDrawMode(MODMD_DEBUG);

            CheapShadowMode = chs_mode;
        }
    }

    /** Set default alpha **/
    rjSetCheapShadowMode(CHEAPSHDWMD_NORMAL);

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
        RFG_ForceShadowMaps();
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
        RFG_ForceShadowMaps();
        break;

    case CNFE_SHADOW_PLMD_ENHANCED:
        EnhancedPlayerShadowsInit();
        RFG_ForceShadowMaps();
        break;

    case CNFE_SHADOW_PLMD_VANILLA:
        /** Vanilla **/
        RFG_ForceShadowMaps();
        break;
    }

    const int resolution = RF_ConfigGetInt(CNF_SHADOW_RES);

    if (resolution != 1)
        WriteData(0x0041F810, ResolutionList[resolution], uint32_t);

    RF_ObjPakRegisterShadowOpacity( RFF_ShadowOpacityGlobal() );
}
