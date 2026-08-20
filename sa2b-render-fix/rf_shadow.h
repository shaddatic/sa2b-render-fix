/*
*   SA2 Render Fix - '/rf_shadow.h'
*
*   Description:
*     All Task shadow displayers for exporting to API.
*/
#ifndef H_RF_SHADOW
#define H_RF_SHADOW

EXTERN_START

/********************************/
/*  Opaque Types                */
/********************************/
/****** Task ************************************************************************************/
typedef struct task                 task;
typedef struct taskwk               taskwk;

/****** Enemy ***********************************************************************************/
typedef struct enemywk              enemywk;

/********************************/
/*  Constants                   */
/********************************/
/****** Object **********************************************************************************/
typedef enum
{
    RF_SHADOW_COMMON,               /* circular shadow                                          */
    RF_SHADOW_CHAO,                 /* circular shadow used in Chao World                       */

    RF_SHADOW_PLAYER_SONIC,         /* sonic head shadow                                        */
    RF_SHADOW_PLAYER_SHADOW,        /* shadow head shadow                                       */
    RF_SHADOW_PLAYER_MILES,         /* sonic head shadow                                        */
    RF_SHADOW_PLAYER_EGGMAN,        /* sonic head shadow                                        */
    RF_SHADOW_PLAYER_KNUCKLES,      /* sonic head shadow                                        */
    RF_SHADOW_PLAYER_ROUGE,         /* sonic head shadow                                        */
    RF_SHADOW_PLAYER_EWALK_BODY,    /* egg walker body shadow                                   */
    RF_SHADOW_PLAYER_EWALK_FOOT,    /* egg walker foot shadow                                   */
    RF_SHADOW_PLAYER_TWALK_BODY,    /* tails walker body shadow                                 */
    RF_SHADOW_PLAYER_TWALK_FOOT,    /* tails walker foot shadow                                 */
    RF_SHADOW_PLAYER_AMY,           /* amy head shadow                                          */
    RF_SHADOW_PLAYER_METAL,         /* metal sonic head shadow                                  */
    RF_SHADOW_PLAYER_CWALK_BODY,    /* chao walker body shadow                                  */
    RF_SHADOW_PLAYER_CWALK_FOOT,    /* chao walker foot shadow                                  */
    RF_SHADOW_PLAYER_DWALK_BODY,    /* dark walker (chao or big) body shadow                    */
    RF_SHADOW_PLAYER_DWALK_FOOT,    /* dark walker (chao or big) foot shadow                    */
    RF_SHADOW_PLAYER_TICAL,         /* tikal head shadow                                        */
    RF_SHADOW_PLAYER_CHAOS0,        /* chaos 0 head shadow                                      */

    RF_SHADOW_CART_BIG_TAILS,       /* story tails cart shadow                                  */
    RF_SHADOW_CART_BIG_ROUGE,       /* story rouge cart shadow                                  */
    RF_SHADOW_CART_SONIC,           /* sonic cart shadow                                        */
    RF_SHADOW_CART_KNUCKLES,        /* knuckles cart shadow                                     */
    RF_SHADOW_CART_TAILS,           /* tails cart shadow                                        */
    RF_SHADOW_CART_EGGMAN,          /* eggman cart shadow                                       */
    RF_SHADOW_CART_SHADOW,          /* shadow cart shadow                                       */
    RF_SHADOW_CART_ROUGE,           /* rouge cart shadow                                        */
    RF_SHADOW_CART_DLC_SONIC,       /* sonic alt cart shadow                                    */
    RF_SHADOW_CART_DLC_KNUCKLES,    /* knuckles alt cart shadow                                 */
    RF_SHADOW_CART_DLC_CHAO,        /* chao cart shadow                                         */
    RF_SHADOW_CART_DLC_EGGMAN,      /* eggman alt cart shadow                                   */
    RF_SHADOW_CART_DLC_SHADOW,      /* shadow alt cart shadow                                   */
    RF_SHADOW_CART_DLC_EGGROBO,     /* eggrobo cart shadow                                      */

    RF_SHADOW_OBJECT_MODMOD_HEX,    /* modmod object shadow, hexagon                            */
    RF_SHADOW_OBJECT_MODMOD_BOX,    /* modmod object shadow, cube                               */

    RF_SHADOW_OBJECT_CE_BOARD,      /* player snow board shadow, city escape                    */
    RF_SHADOW_OBJECT_MH_BOARD,      /* player snow board shadow, metal harbor                   */

    RF_SHADOW_OBJECT_EQ_ROBOT,      /* egg quaters robot beetle shadow                          */

    RF_SHADOW_OBJECT_MD_CONTBOX,    /* meteor herd large blue container shadow                  */
    RF_SHADOW_OBJECT_MD_METEO,      /* meteor herd meteor shadow                                */
    RF_SHADOW_OBJECT_MD_TANK,       /* meteor herd small overhead tank shadow                   */

    RF_SHADOW_ENEMY_SHOUKO,         /* enemy jet shadow                                         */

    RF_SHADOW_BOSS_BIGFOOT_BODY,    /* boss big foot body shadow                                */
    RF_SHADOW_BOSS_BIGFOOT_FOOT,    /* boss big foot foot shadow                                */
    RF_SHADOW_BOSS_HOTSHOT_BODY,    /* boss hot shot body shadow                                */
    RF_SHADOW_BOSS_HOTSHOT_FOOT,    /* boss hot shot foot shadow                                */
    RF_SHADOW_BOSS_FDOG_BODY,       /* boss flying dog body shadow                              */
    RF_SHADOW_BOSS_GROBO_MISSILE,   /* boss guard robot missile shadow                          */
    RF_SHADOW_BOSS_BIGBOGY,         /* boss king boom boo shadow                                */

    RF_NB_SHADOW,                   /* enum count                                               */
}
RF_SHADOW;

/****** Cart Shadow *****************************************************************************/
#define CART_NUM                    (8) /* cart number                                          */
#define CART_DLC_NUM                (2) /* true/false                                           */

/********************************/
/*  Extern Vars                 */
/********************************/
/****** Common **********************************************************************************/
EXTERN NJS_CNK_OBJECT*              object_shadow;
EXTERN NJS_CNK_OBJECT*              object_kage_marukage_marukage;

/****** Player (Action) *************************************************************************/
EXTERN NJS_CNK_OBJECT*              object_sonic_head_mod;
EXTERN NJS_CNK_OBJECT*              object_terios_head_mod;
EXTERN NJS_CNK_OBJECT*              object_amy_head_mod;
EXTERN NJS_CNK_OBJECT*              object_metalsonic_head_mod;

/****** Player (Miles/Eggman) *******************************************************************/
EXTERN NJS_CNK_OBJECT*              object_miles_head_mod;
EXTERN NJS_CNK_OBJECT*              object_eggman_head_mod;

/****** Player (Hunter) *************************************************************************/
EXTERN NJS_CNK_OBJECT*              object_knuckles_head_mod;
EXTERN NJS_CNK_OBJECT*              object_rouge_head_mod;
EXTERN NJS_CNK_OBJECT*              object_tikal_head_mod;
EXTERN NJS_CNK_OBJECT*              object_chaos_head_mod;

/****** Player (Walker) *************************************************************************/
EXTERN NJS_CNK_OBJECT*              object_twalker_body_mod;
EXTERN NJS_CNK_OBJECT*              object_twalker_foot_mod;
EXTERN NJS_CNK_OBJECT*              object_cwalker_body_mod;
EXTERN NJS_CNK_OBJECT*              object_cwalker_foot_mod;
EXTERN NJS_CNK_OBJECT*              object_ewalker_body_mod;
EXTERN NJS_CNK_OBJECT*              object_ewalker_foot_mod;
EXTERN NJS_CNK_OBJECT*              object_dwalker_body_mod;
EXTERN NJS_CNK_OBJECT*              object_dwalker_foot_mod;

/****** Player (Cart) ***************************************************************************/
EXTERN NJS_CNK_OBJECT*              CartObjectList[CART_NUM][CART_DLC_NUM];

/****** Object **********************************************************************************/
EXTERN NJS_CNK_OBJECT*              object_modmod_hex;
EXTERN NJS_CNK_OBJECT*              object_modmod_box;

EXTERN NJS_CNK_OBJECT*              object_ce_board_mod;
EXTERN NJS_CNK_OBJECT*              object_mh_board_mod;

EXTERN NJS_CNK_OBJECT*              object_eq_robot_mod;

EXTERN NJS_CNK_OBJECT*              object_md_contbox_mod;
EXTERN NJS_CNK_OBJECT*              object_md_meteo_mod;
EXTERN NJS_CNK_OBJECT*              object_md_tank_mod;

/****** Enemy ***********************************************************************************/
EXTERN NJS_CNK_OBJECT*              object_e_shouko_mod;

/****** Boss ************************************************************************************/
EXTERN NJS_CNK_OBJECT*              object_b_bigfoot_body_mod;
EXTERN NJS_CNK_OBJECT*              object_b_bigfoot_foot_mod;
EXTERN NJS_CNK_OBJECT*              object_b_hotshot_body_mod;
EXTERN NJS_CNK_OBJECT*              object_b_hotshot_foot_mod;
EXTERN NJS_CNK_OBJECT*              object_b_fdog_body_mod;
EXTERN NJS_CNK_OBJECT*              object_b_grobo_missile_mod;
EXTERN NJS_CNK_OBJECT*              object_b_bigbogy_mod;

/********************************/
/*  Prototypes                  */
/********************************/
/************************************************************************************************/
/*
*   Models
*/
/****** Get/Set *********************************************************************************/
/*
*   Description:
*     Get a shadow modifier.
*
*   Parameters:
*     - kind        : type of modifier shadow
*
*   Returns:
*     Modifier model; or 'nullptr' on failure.
*/
NJS_CNK_OBJECT* GetShadow( RF_SHADOW kind );
/*
*   Description:
*     Set a shadow modifier.
*
*   Notes:
*     - This function also handles any other references to that model in the game.
*
*   Parameters:
*     - kind        : type of modifier shadow
*     - object      : modifier model
*
*   Returns:
*     '0' on success; or a negative value of failure.
*/
i32     SetShadow( RF_SHADOW kind, NJS_CNK_OBJECT* object );

#ifdef RF_SHADOW_INCL_TASKS

/************************************************************************************************/
/*
*   Task Shadow Displayer
*/
/****** Player **********************************************************************************/
/*
*   Description:
*     Sonic (& Shadow, Amy, Metal Sonic) shadow displayer.
*/
void    SonicShadow( task* tp );
/*
*   Description:
*     Miles "Tails" Prower shadow displayer.
*/
void    MilesShadow( task* tp );
/*
*   Description:
*     Eggman shadow displayer.
*/
void    EggmanShadow( task* tp );
/*
*   Description:
*     Knuckles (& Rouge, Tikal, Chaos 0) shadow displayer.
*/
void    KnucklesShadow( task* tp );
/*
*   Description:
*     Egg Walker (& Tornado, Chao, Dark Walker) shadow displayer.
*/
void    EggWalkerShadow( task* tp );
/*
*   Description:
*     Player cart shadow displayer.
*/
void    cartShadow( task* tp );

/****** Object **********************************************************************************/
/*
*   Description:
*     Minimal shadow displayer.
*/
void    MinimalShadow( task* tp );
/*
*   Description:
*     Chaos Drive shadow displayer.
*/
void    ChaosDriveShadow( task* tp );
/*
*   Description:
*     Pickup item shadow displayer.
*/
void    ObjectPickUpShadow( task* tp );
/*
*   Description:
*     Search box shadow displayer.
*/
void    ObjectSearchBoxShadow( task* tp );
/*
*   Description:
*     Omochao shadow displayer.
*/
void    ObjectMessengerShadow( task* tp );
/*
*   Description:
*     Floating weight hazard shadow displayer.
*/
void    ObjectBunchinShadow( task* tp );
/*
*   Description:
*     Spinning spike ball shadow displayer.
*/
void    ObjectIronBall2Shadow(task* tp);
/*
*   Description:
*     Player pulley shadow displayer.
*/
void    ObjectUdreelShadow( task* tp );
/*
*   Description:
*     Player pulley (golem boss) shadow displayer.
*/
void    ObjectGolemUdreelShadow( task* tp );
/*
*   Description:
*     Snow board shadow displayer.
*/
void    ObjectBoardShadow_CE( task* tp );
void    ObjectBoardShadow_MH( task* tp );
/*
*   Description:
*     City Escape GUN Truck shadow displayer.
*/
void    ObjectTruckShadow( task* tp );
/*
*   Description:
*     Car shadow displayer.
*/
void    ObjectCarShadow_CE( task* tp );
void    ObjectCarShadow_MS( task* tp );
/*
*   Description:
*     Car crash shadow displayer.
*/
void    ObjectCarCrashShadow_CE( task* tp );
void    ObjectCarCrashShadow_MS( task* tp );
/*
*   Description:
*     Meteor Herd huge blue container shadow displayer.
*/
void    ObjectContainerBoxShadow(task* tp);
/*
*   Description:
*     Meteor Herd moveable meteor shadow displayer.
*/
void    ObjectMeteoBigShadow( task* tp );
/*
*   Description:
*     Meteor Herd falling meteor shadow displayer.
*/
void    ObjectFireBallShadow( task* tp );
/*
*   Description:
*     Meteor Herd small overhead tank shadow displayer.
*/
void    ObjectTankShadow( task* tp );
/*
*   Description:
*     Floating Cannons Core block shadow displayers.
*/
void    ObjectBlockShadow( task* tp );
void    ObjectBlock2Shadow( task* tp );

/****** Enemy ***********************************************************************************/
/*
*   Description:
*     Generic circular enemy shadow displayer.
*
*   Notes:
*     - Not to be directly exported to API, apply seperately to enemies that use it:
*       
*       - AI            (hunter)
*       - Ghora         (Ghola)
*       - E1000
*       - Big the Cat
*/
void    EnemyShadow( task* tp );
/*
*   Description:
*     Enemy Hawk shadow displayer.
*/
void    EnemyKyokoShadow( task* tp );
/*
*   Description:
*     Enemy Beetle shadow displayer.
*/
void    EnemyKumiShadow( task* tp );
/*
*   Description:
*     Enemy gold Beetle shadow displayer.
*/
void    EnemyGoldShadow( task* tp );
/*
*   Description:
*     Enemy Jet shadow displayer.
*/
void    EnemyShoukoShadow( task* tp );
/*
*   Description:
*     Enemy Hornet shadow displayer.
*/
void    EnemyNamieShadow( task* tp );
/*
*   Description:
*     Enemy Hornet rocket/missile shadow displayer.
*/
void    EnemyNamieRocketShadow( task* tp );
/*
*   Description:
*     Enemy Pheonix shadow displayer.
*/
void    EnemyAkahigeShadow( task* tp );
/*
*   Description:
*     Enemy Pheonix rocket/missile shadow displayer.
*/
void    EnemyAkahigeRocketShadow( task* tp );
/*
*   Description:
*     Enemy Beetle/Hawk that follows a path shadow displayer.
*/
void    EnemyPathShadow( task* tp );
/*
*   Description:
*     Enemy Chaos that follows a path shadow displayer.
*/
void    EnemyChaosPathShadow( task* tp );
/*
*   Description:
*     Green Hill specific Enemy shadow displayer.
*
*   Notes:
*     - Not to be directly exported to API, apply seperately to enemies that use it:
*       - Batabata      (chomper)
*       - Beeton        (bee bot)
*/
void    EnemyBataBeeShadow( task* tp );

/****** Chao ************************************************************************************/
/*
*   Description:
*     Chao shadow displayer.
*/
void    ChaoShadow( task* tp );
/*
*   Description:
*     Chao egg shadow displayer.
*/
void    AL_EggShadow( task* tp );
/*
*   Description:
*     Minimal shadow displayer.
*/
void    AL_MinimalShadow( task* tp );
/*
*   Description:
*     Chaos Drive (Chao World) shadow displayer.
*/
void    ALO_ChaosDriveShadow( task* tp );
/*
*   Description:
*     Chao fruit shadow displayer.
*/
void    ALO_FruitShadow( task* tp );
/*
*   Description:
*     Race fruit shadow displayer.
*/
void    ALO_RaceFruitShadow( task* tp );
/*
*   Description:
*     Garden tree shadow displayer.
*/
void    ALO_GrowTreeShadow( task* tp );
/*
*   Description:
*     Race tree shadow displayer
*/
void    ALO_RaceTreeShadow( task* tp );
/*
*   Description:
*     TV toy shadow displayer.
*/
void    ALO_TVShadow( task* tp );
/*
*   Description:
*     Radio toy shadow displayer.
*/
void    ALO_RadicaseShadow( task* tp );
/*
*   Description:
*     Ball toy shadow displayer.
*/
void    ALO_BallShadow( task* tp );
/*
*   Description:
*     Rocking horse toy shadow displayer.
*/
void    ALO_HorseShadow( task* tp );
/*
*   Description:
*     Jack-in-the-Box toy shadow displayer.
*/
void    ALO_BoxShadow( task* tp );
/*
*   Description:
*     Tree seed shadow displayer.
*/
void    ALO_SeedShadow( task* tp );
/*
*   Description:
*     Chao mask shadow displayer.
*/
void    ALO_ObakeHeadShadow( task* tp );

/****** Boss ************************************************************************************/
/*
*   Description:
*     King Boom Boo shadow displayer.
*/
void    BossBogyShadow( task* tp );
/*
*   Description:
*     Guard robot Big Foot shadow displayer.
*/
void    BossBigFootShadow( task* tp );
/*
*   Description:
*     Guard robot Hot Shot shadow displayer.
*/
void    BossHotShotShadow( task* tp );
/*
*   Description:
*     Guard robot Flying Dog shadow displayer.
*/
void    BossFlyingDogShadow( task* tp );

/****** Boss Misc *******************************************************************************/
/*
*   Description:
*     Guard robot boss missile shadow displayer.
*/
void    GRoboMissileShadow( task* tp );
/*
*   Description:
*     Biolizard boss energy shadow displayer.
*/
void    BossLastEnergyShadow( task* tp );

#endif/*RF_SHADOW_INCL_TASKS*/

EXTERN_END

#endif/*H_RF_SHADOW*/
