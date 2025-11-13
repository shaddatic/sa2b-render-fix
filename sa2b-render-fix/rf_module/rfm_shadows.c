/************************/
/*  Includes            */
/************************/
/****** Core Toolkit ****************************************************************/
#include <samt/core.h>          /* core                                             */
#include <samt/writeop.h>       /* writejump                                        */
#include <samt/writemem.h>      /* writedata                                        */
#include <samt/funchook.h>      /* function hook                                    */

/****** Ninja ***********************************************************************/
#include <samt/ninja/ninja.h>   /* ninja                                            */

/****** Game ************************************************************************/
#include <samt/sonic/task.h>    /* task                                             */

/****** Render Fix ******************************************************************/
#include <rf_core.h>            /* core                                             */
#include <rf_ninja.h>           /* set cheap shadow intensity                       */
#include <rf_samdl.h>           /* file load                                        */

/****** Config **********************************************************************/
#include <cnf.h>                /* config get                                       */

/****** Self ************************************************************************/
#include <rf_module/rfm_shadows/shd_internal.h> /* children                         */

/************************/
/*  External Functions  */
/************************/
/****** Hacky Function to Force Shadow Map Drawing **********************************/
EXTERN void     RFG_ForceShadowMaps( void );

/************************/
/*  Macros              */
/************************/
/****** Shadow Intensity To Float ***************************************************/
#define CHEAPSHDWMD_TO_FLOAT(mode)      (1.f-((Float)(mode)*(1.f/256.f)))

/************************/
/*  Constants           */
/************************/
/****** Shadow Intensity ************************************************************/
#define CHEAPSHDWMD_NORMAL              ( 80)
#define CHEAPSHDWMD_CHAO                (115)

/************************/
/*  Data                */
/************************/
/****** Shadow Map Resolution *******************************************************/
static const uint32_t ResolutionList[] = { 256, 512, 1024, 2048, 4096, 8192 };

/****** Mod Shadow ******************************************************************/
static NJS_CNK_MODEL* model_basic_shadow;

/************************/
/*  Source              */
/************************/
/****** Static **********************************************************************/
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

/****** Draw Basic Mod **************************************************************/
void
DrawBasicShadow(void)
{
    njCnkModDrawModel(model_basic_shadow);
}

/****** Set Shadow Intensity ********************************************************/
#define AL_Constructor      FUNC_PTR(void, __cdecl, (task*), 0x0052AB60)
#define AL_Destructor       FUNC_PTR(void, __cdecl, (task*), 0x0052AE70)

static mt_hookinfo AL_ConstructorHookInfo[1];
static void
AL_ConstructorHook(task* tp)
{
    FuncHookCall( AL_ConstructorHookInfo, AL_Constructor(tp) );

    rjSetCheapShadowMode(CHEAPSHDWMD_CHAO);
}

static mt_hookinfo AL_DestructorHookInfo[1];
static void
AL_DestructorHook(task* tp)
{
    FuncHookCall( AL_DestructorHookInfo, AL_Destructor(tp) );

    rjSetCheapShadowMode(CHEAPSHDWMD_NORMAL);
}

/****** Init ************************************************************************/
void
RFM_ShadowsInit(void)
{
    if ( CNF_GetInt(CNF_MISC_NOSHADOWS) )
    {
        WriteRetn(0x0046FBC0); // Disable all shadows
        return;
    }

    const CNFE_GLOBAL_CHSMD chs_mode = CNF_GetInt(CNF_GLOBAL_CHSMD);

    /****** Global Shadow Mode ******/

    switch ( CNF_GetInt(CNF_PLAYER_SHADOWMD) )
    {
        case CNFE_PLAYER_SHADOWMD_MODIFIER:
        {
            if ( chs_mode == CNFE_GLOBAL_CHSMD_DISABLED )
                break;

            CHS_PlayerInit();
            break;
        }
        case CNFE_PLAYER_SHADOWMD_ENHANCED:
        {
            EnhancedPlayerShadowsInit();
            RFG_ForceShadowMaps();
            break;
        }
        case CNFE_PLAYER_SHADOWMD_VANILLA:
        {
            RFG_ForceShadowMaps();
            break;
        }
    }

    const CNFE_MISC_SHDWRES shdwres = CNF_GetInt(CNF_MISC_SHADOWRES);

    if ( shdwres != CNFE_MISC_SHDWRES_LOW )
    {
        WriteData(0x0041F810, ResolutionList[shdwres], u32);
    }

    /** Init cheap shadows **/

    if ( chs_mode == CNFE_GLOBAL_CHSMD_DISABLED )
    {
        RFG_ForceShadowMaps();
        return;
    }

    // get basic shadow model
    model_basic_shadow = RF_GetCnkModel("common/basic_mod.sa2mdl");

    if ( CNF_GetInt(CNF_DEBUG_MODIFIER) )
    {
        rjCheapShadowDebug( ON );
    }

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

    /** Set default intensity **/
    rjSetCheapShadowMode(CHEAPSHDWMD_NORMAL);

    /** Shadow opacity function hooks **/
    FuncHook(AL_ConstructorHookInfo, AL_Constructor, AL_ConstructorHook);
    FuncHook(AL_DestructorHookInfo , AL_Destructor , AL_DestructorHook);
}
