/********************************/
/*  Includes                    */
/********************************/
/****** SAMT ************************************************************************************/
#include <samt/core.h>              /* core                                                     */
#include <samt/writeop.h>           /* write op                                                 */
#include <samt/writemem.h>          /* write mem                                                */
#include <samt/funchook.h>          /* function hook                                            */

/****** Ninja ***********************************************************************************/
#include <samt/ninja/ninja.h>       /* ninja                                                    */

/****** Cart ************************************************************************************/
#include <samt/sonic/cart/cartcar.h> /* cart cars                                               */

/****** Render Fix ******************************************************************************/
#include <rf_core.h>                /* core                                                     */
#include <rf_model.h>               /* get chunk                                                */
#include <rf_ninja.h>               /* render fix ninja                                         */

/****** Config **********************************************************************************/
#include <cnf.h>                    /* config core                                              */

/****** Self ************************************************************************************/
#include <rf_shadow.h>              /* self                                                     */
#include <rf_shadow/chs_internal.h> /* children                                                 */

/********************************/
/*  Prototypes                  */
/********************************/
/****** Shadow Texture **************************************************************************/
/*
*   Description:
*     Hacky Function to Force Shadow Map Drawing.
*/
EXTERN void     RFG_ForceShadowMaps( void );

/********************************/
/*  Game Refs                   */
/********************************/
/****** 2D Array ********************************************************************************/
#define AL_Constructor              FUNC_PTR(void, __cdecl, (task*), 0x0052AB60)
#define AL_Destructor               FUNC_PTR(void, __cdecl, (task*), 0x0052AE70)

/********************************/
/*  Macro                       */
/********************************/
/****** 2D Array ********************************************************************************/
#define ARY_X2(a, b)                ((a*2)+b)

/********************************/
/*  Constants                   */
/********************************/
/****** Shadow Intensity ************************************************************************/
#define CHEAPSHDWMD_NORMAL          ( 80)
#define CHEAPSHDWMD_CHAO            (115)

/********************************/
/*  Variables                   */
/********************************/
/************************************************************************************************/
/*
*   Models
*/
/****** Common **********************************************************************************/
NJS_CNK_OBJECT*                     object_shadow;
NJS_CNK_OBJECT*                     object_kage_marukage_marukage;

/****** Player (Action) *************************************************************************/
NJS_CNK_OBJECT*                     object_sonic_head_mod;
NJS_CNK_OBJECT*                     object_terios_head_mod;
NJS_CNK_OBJECT*                     object_amy_head_mod;
NJS_CNK_OBJECT*                     object_metalsonic_head_mod;

/****** Player (Miles/Eggman) *******************************************************************/
NJS_CNK_OBJECT*                     object_miles_head_mod;
NJS_CNK_OBJECT*                     object_eggman_head_mod;

/****** Player (Hunter) *************************************************************************/
NJS_CNK_OBJECT*                     object_knuckles_head_mod;
NJS_CNK_OBJECT*                     object_rouge_head_mod;
NJS_CNK_OBJECT*                     object_tikal_head_mod;
NJS_CNK_OBJECT*                     object_chaos_head_mod;

/****** Player (Walker) *************************************************************************/
NJS_CNK_OBJECT*                     object_twalker_body_mod;
NJS_CNK_OBJECT*                     object_twalker_foot_mod;
NJS_CNK_OBJECT*                     object_cwalker_body_mod;
NJS_CNK_OBJECT*                     object_cwalker_foot_mod;
NJS_CNK_OBJECT*                     object_ewalker_body_mod;
NJS_CNK_OBJECT*                     object_ewalker_foot_mod;
NJS_CNK_OBJECT*                     object_dwalker_body_mod;
NJS_CNK_OBJECT*                     object_dwalker_foot_mod;

/****** Player (Cart) ***************************************************************************/
NJS_CNK_OBJECT*                     CartObjectList[CART_NUM][CART_DLC_NUM];

/****** Object **********************************************************************************/
NJS_CNK_OBJECT*                     object_modmod_hex;
NJS_CNK_OBJECT*                     object_modmod_box;

NJS_CNK_OBJECT*                     object_ce_board_mod;
NJS_CNK_OBJECT*                     object_mh_board_mod;

NJS_CNK_OBJECT*                     object_eq_robot_mod;

NJS_CNK_OBJECT*                     object_md_contbox_mod;
NJS_CNK_OBJECT*                     object_md_meteo_mod;
NJS_CNK_OBJECT*                     object_md_tank_mod;

/****** Enemy ***********************************************************************************/
NJS_CNK_OBJECT*                     object_e_shouko_mod;

/****** Boss ************************************************************************************/
NJS_CNK_OBJECT*                     object_b_bigfoot_body_mod;
NJS_CNK_OBJECT*                     object_b_bigfoot_foot_mod;
NJS_CNK_OBJECT*                     object_b_hotshot_body_mod;
NJS_CNK_OBJECT*                     object_b_hotshot_foot_mod;
NJS_CNK_OBJECT*                     object_b_fdog_body_mod;
NJS_CNK_OBJECT*                     object_b_grobo_missile_mod;
NJS_CNK_OBJECT*                     object_b_bigbogy_mod;

/************************************************************************************************/
/*
*   Model List
*/
/****** Model List ******************************************************************************/
static NJS_CNK_OBJECT** const ShadowList[RF_NB_SHADOW] =
{
    [RF_SHADOW_COMMON] = &object_shadow,
    [RF_SHADOW_CHAO]   = &object_kage_marukage_marukage,

    [RF_SHADOW_PLAYER_SONIC]      = &object_sonic_head_mod,
    [RF_SHADOW_PLAYER_SHADOW]     = &object_terios_head_mod,
    [RF_SHADOW_PLAYER_MILES]      = &object_miles_head_mod,
    [RF_SHADOW_PLAYER_EGGMAN]     = &object_eggman_head_mod,
    [RF_SHADOW_PLAYER_KNUCKLES]   = &object_knuckles_head_mod,
    [RF_SHADOW_PLAYER_ROUGE]      = &object_rouge_head_mod,
    [RF_SHADOW_PLAYER_EWALK_BODY] = &object_ewalker_body_mod,
    [RF_SHADOW_PLAYER_EWALK_FOOT] = &object_ewalker_foot_mod,
    [RF_SHADOW_PLAYER_AMY]        = &object_amy_head_mod,
    [RF_SHADOW_PLAYER_METAL]      = &object_metalsonic_head_mod,
    [RF_SHADOW_PLAYER_CWALK_BODY] = &object_cwalker_body_mod,
    [RF_SHADOW_PLAYER_CWALK_FOOT] = &object_cwalker_foot_mod,
    [RF_SHADOW_PLAYER_DWALK_BODY] = &object_dwalker_body_mod,
    [RF_SHADOW_PLAYER_DWALK_FOOT] = &object_dwalker_foot_mod,
    [RF_SHADOW_PLAYER_TICAL]      = &object_tikal_head_mod,
    [RF_SHADOW_PLAYER_CHAOS0]     = &object_chaos_head_mod,

    [RF_SHADOW_CART_BIG_TAILS]    = &CartObjectList[CART_CAR_TAILS_SPECIAL][FALSE],
    [RF_SHADOW_CART_BIG_ROUGE]    = &CartObjectList[CART_CAR_ROUGE_SPECIAL][FALSE],

    [RF_SHADOW_CART_SONIC]        = &CartObjectList[CART_CAR_SONIC][FALSE],
    [RF_SHADOW_CART_KNUCKLES]     = &CartObjectList[CART_CAR_KNUCKLES][FALSE],
    [RF_SHADOW_CART_TAILS]        = &CartObjectList[CART_CAR_TAILS][FALSE],
    [RF_SHADOW_CART_EGGMAN]       = &CartObjectList[CART_CAR_EGGMAN][FALSE],
    [RF_SHADOW_CART_SHADOW]       = &CartObjectList[CART_CAR_SHADOW][FALSE],
    [RF_SHADOW_CART_ROUGE]        = &CartObjectList[CART_CAR_ROUGE][FALSE],

    [RF_SHADOW_CART_DLC_SONIC]    = &CartObjectList[CART_CAR_SONIC][TRUE],
    [RF_SHADOW_CART_DLC_KNUCKLES] = &CartObjectList[CART_CAR_KNUCKLES][TRUE],
    [RF_SHADOW_CART_DLC_CHAO]     = &CartObjectList[CART_CAR_TAILS][TRUE],
    [RF_SHADOW_CART_DLC_EGGMAN]   = &CartObjectList[CART_CAR_EGGMAN][TRUE],
    [RF_SHADOW_CART_DLC_SHADOW]   = &CartObjectList[CART_CAR_SHADOW][TRUE],
    [RF_SHADOW_CART_DLC_EGGROBO]  = &CartObjectList[CART_CAR_ROUGE][TRUE],

    [RF_SHADOW_OBJECT_MODMOD_HEX] = &object_modmod_hex,
    [RF_SHADOW_OBJECT_MODMOD_BOX] = &object_modmod_box,

    [RF_SHADOW_OBJECT_CE_BOARD] = &object_ce_board_mod,
    [RF_SHADOW_OBJECT_MH_BOARD] = &object_mh_board_mod,

    [RF_SHADOW_OBJECT_EQ_ROBOT] = &object_eq_robot_mod,

    [RF_SHADOW_OBJECT_MD_CONTBOX] = &object_md_contbox_mod,
    [RF_SHADOW_OBJECT_MD_METEO]   = &object_md_meteo_mod,
    [RF_SHADOW_OBJECT_MD_TANK]    = &object_md_tank_mod,

    [RF_SHADOW_ENEMY_SHOUKO] = &object_e_shouko_mod,

    [RF_SHADOW_BOSS_BIGFOOT_BODY]  = &object_b_bigfoot_body_mod,
    [RF_SHADOW_BOSS_BIGFOOT_FOOT]  = &object_b_bigfoot_foot_mod,
    [RF_SHADOW_BOSS_HOTSHOT_BODY]  = &object_b_hotshot_body_mod,
    [RF_SHADOW_BOSS_HOTSHOT_FOOT]  = &object_b_hotshot_foot_mod,
    [RF_SHADOW_BOSS_FDOG_BODY]     = &object_b_fdog_body_mod,
    [RF_SHADOW_BOSS_GROBO_MISSILE] = &object_b_grobo_missile_mod,
    [RF_SHADOW_BOSS_BIGBOGY]       = &object_b_bigbogy_mod,
};

/************************************************************************************************/
/*
*   Shadow Tex
*/
/****** Shadow Map Resolution *******************************************************/
static const u16 ResolutionList[] = { 256, 512, 1024, 2048, 4096, 8192 };

/********************************/
/*  Source                      */
/********************************/
/****** Set Shadow Intensity ********************************************************************/
static mt_hookinfo AL_ConstructorHookInfo[1];
static void
AL_ConstructorHook(task* tp)
{
    mtHookInfoCall( AL_ConstructorHookInfo, AL_Constructor(tp) );

    rjSetCheapShadowMode(CHEAPSHDWMD_CHAO);
}

static mt_hookinfo AL_DestructorHookInfo[1];
static void
AL_DestructorHook(task* tp)
{
    mtHookInfoCall( AL_DestructorHookInfo, AL_Destructor(tp) );

    rjSetCheapShadowMode(CHEAPSHDWMD_NORMAL);
}

/****** Kill Displayer **************************************************************************/
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

/****** Kill Shadow Tex *************************************************************************/
void* __cdecl
CreateNoStencilTexture(void)
{
    return NULL;
}

/****** Get/Set *********************************************************************************/
NJS_CNK_OBJECT*
GetShadow(RF_SHADOW kind)
{
    if ( kind < 0 )
    {
        return nullptr;
    }

    if ( kind >= RF_NB_SHADOW )
    {
        return nullptr;
    }

    return *ShadowList[kind];
}

i32
SetShadow(RF_SHADOW kind, NJS_CNK_OBJECT* object)
{
    if ( kind < 0 )
    {
        return -1;
    }

    if ( kind >= RF_NB_SHADOW )
    {
        return -2;
    }

    if ( !object )
    {
        return -3;
    }

    // additional operations
    switch ( kind )
    {
        case RF_SHADOW_OBJECT_MODMOD_HEX:
        {
            ModModModels[MODMOD_MODEL_HEX] = object->model;
            break;
        }
        case RF_SHADOW_OBJECT_MODMOD_BOX:
        {
            ModModModels[MODMOD_MODEL_BOX] = object->model;
            break;
        }
    }

    *ShadowList[kind] = object;
    return 0;
}

/****** Init ************************************************************************************/
void
RF_ShadowInit(void)
{
    // common
    object_shadow                 = DATA_ARY(NJS_CNK_OBJECT, 0x017165F4, [1]);
    object_kage_marukage_marukage = DATA_ARY(NJS_CNK_OBJECT, 0x01349D9C, [1]);

    // player, action
    object_sonic_head_mod      = RF_GetCnkObject("figure/sonic_head_mod");
    object_terios_head_mod     = RF_GetCnkObject("figure/terios_head_mod");
    object_amy_head_mod        = RF_GetCnkObject("figure/amy_head_mod");
    object_metalsonic_head_mod = RF_GetCnkObject("figure/metalsonic_head_mod");

    // player, miles/eggman
    object_miles_head_mod  = RF_GetCnkObject("figure/miles_head_mod");
    object_eggman_head_mod = RF_GetCnkObject("figure/eggman_head_mod");

    // player, hunter
    object_knuckles_head_mod = RF_GetCnkObject("figure/knuckles_head_mod");
    object_rouge_head_mod    = RF_GetCnkObject("figure/rouge_head_mod");
    object_tikal_head_mod    = RF_GetCnkObject("figure/tikal_head_mod");
    object_chaos_head_mod    = RF_GetCnkObject("figure/chaos_head_mod");

    // player, walker
    object_twalker_body_mod = RF_GetCnkObject("figure/twalker_body_mod");
    object_twalker_foot_mod = RF_GetCnkObject("figure/twalker_foot_mod");
    object_ewalker_body_mod = RF_GetCnkObject("figure/ewalker_body_mod");
    object_ewalker_foot_mod = RF_GetCnkObject("figure/ewalker_foot_mod");
    object_cwalker_body_mod = RF_GetCnkObject("figure/cwalker_body_mod");
    object_cwalker_foot_mod = RF_GetCnkObject("figure/cwalker_foot_mod");
    object_dwalker_body_mod = RF_GetCnkObject("figure/dwalker_body_mod");
    object_dwalker_foot_mod = RF_GetCnkObject("figure/dwalker_foot_mod");

    // player, carts
    RFS_OBJFILE obj_list[8 * 2] =
    {
        { .puPath = "cart/cart_tails_big_mod" },
        { .puPath = nullptr },

        { .puPath = "cart/cart_rouge_big_mod" },
        { .puPath = nullptr },

        { .puPath = "cart/cart_sonic_mod" },
        { .puPath = "cart/cart_sonic_alt_mod" },

        { .puPath = "cart/cart_knuckles_mod" },
        { .puPath = "cart/cart_knuckles_alt_mod" },

        { .puPath = "cart/cart_tails_mod" },
        { .puPath = "cart/cart_chao_mod" },

        { .puPath = "cart/cart_eggman_mod" },
        { .puPath = "cart/cart_eggman_alt_mod" },

        { .puPath = "cart/cart_shadow_mod" },
        { .puPath = "cart/cart_shadow_alt_mod" },

        { .puPath = "cart/cart_rouge_mod" },
        { .puPath = "cart/cart_eggrobo_mod" },
    };

    RF_GetCnkObjectList( obj_list, ARYLEN(obj_list) );

    for ( i32 i = 0; i < CART_NUM; ++i )
    {
        CartObjectList[i][FALSE] = obj_list[ARY_X2(i, FALSE)].pObject;
        CartObjectList[i][TRUE]  = obj_list[ARY_X2(i, TRUE) ].pObject;
    }

    // object, modmod
    object_modmod_hex = DATA_ARY(NJS_CNK_OBJECT, 0x00B4D414, [1]);
    object_modmod_box = DATA_ARY(NJS_CNK_OBJECT, 0x00B4D254, [1]);

    // object, board
    object_ce_board_mod = DATA_ARY(NJS_CNK_OBJECT, 0x0108ACB8, [1]);
    object_mh_board_mod = DATA_ARY(NJS_CNK_OBJECT, 0x00AE7B10, [1]);

    // object, egg quaters
    object_eq_robot_mod = DATA_ARY(NJS_CNK_OBJECT, 0x00C42144, [1]);

    // object, meteor herd
    object_md_contbox_mod = DATA_ARY(NJS_CNK_OBJECT, 0x01146E9C, [1]);
    object_md_meteo_mod   = DATA_ARY(NJS_CNK_OBJECT, 0x01153A60, [1]);
    object_md_tank_mod    = DATA_ARY(NJS_CNK_OBJECT, 0x01149C74, [1]);

    // enemy
    object_e_shouko_mod = DATA_ARY(NJS_CNK_OBJECT, 0x014D0C68, [1]);

    // boss
    object_b_bigfoot_body_mod  = DATA_ARY(NJS_CNK_OBJECT, 0x01134BC4, [1]);
    object_b_bigfoot_foot_mod  = DATA_ARY(NJS_CNK_OBJECT, 0x01134E30, [1]);
    object_b_hotshot_body_mod  = DATA_ARY(NJS_CNK_OBJECT, 0x01134BC4, [1]);
    object_b_hotshot_foot_mod  = DATA_ARY(NJS_CNK_OBJECT, 0x01134E30, [1]);
    object_b_grobo_missile_mod = DATA_ARY(NJS_CNK_OBJECT, 0x01118F30, [1]);
    object_b_fdog_body_mod     = DATA_ARY(NJS_CNK_OBJECT, 0x01134BC4, [1]);
    object_b_bigbogy_mod       = RF_GetCnkObject("boss/bigbogy/bigbogy_mod");

    /*
    *   End of models section
    */

    if ( CNF_GetInt(CNF_MISC_NOSHADOWS) )
    {
        WriteRetn(0x0046FBC0); // Disable all shadows
        return;
    }

    const bool chs_enabled = CNF_GetInt(CNF_GAME_CHSMD) != CNFE_GAME_CHSMD_DISABLED;
    const i32  md_player  = CNF_GetInt(CNF_PLAYER_SHADOWMD);

    // init cheap shadows
    if ( chs_enabled )
    {
        if ( CNF_GetInt(CNF_DEBUG_MODIFIER) )
        {
            rjCheapShadowDebug( ON );
        }

        if ( md_player == CNFE_PLAYER_SHADOWMD_MODIFIER )
        {
            CHS_PlayerInit();
        }
        else // player uses shadow tex
        {
            RFG_ForceShadowMaps();
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

        // set default shadow intensity
        rjSetCheapShadowMode(CHEAPSHDWMD_NORMAL);

        // shadow intensity change funcs
        mtHookFunc(AL_ConstructorHookInfo, AL_Constructor, AL_ConstructorHook);
        mtHookFunc(AL_DestructorHookInfo , AL_Destructor , AL_DestructorHook);
    }
    else // cheap shadows disabled
    {
        const CNFE_MISC_SHDWRES shdwres = CNF_GetInt(CNF_MISC_SHADOWRES);

        if ( shdwres != CNFE_MISC_SHDWRES_LOW )
        {
            WriteData(0x0041F810, ResolutionList[shdwres], u32);
        }

        RFG_ForceShadowMaps();
    }

    // player enhanced shadow tex, legacy
    if ( md_player == CNFE_PLAYER_SHADOWMD_ENHANCED )
    {
        EnhancedPlayerShadowsInit();
    }
}
