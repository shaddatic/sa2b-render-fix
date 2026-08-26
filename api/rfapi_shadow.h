/*
*   SA2 Render Fix - '/rfapi_shadow.h'
*
*   Description:
*     The 'Shadow' API module is the cheap shadow (or Dreamcast) shadow system, and for getting
*   the default cheap shadow displayer used by Render Fix by default
* 
*   Version History:
*     - v1.5.5.0        : Version 0, initial release
* 
*   Availability:
*     - Before Init     : No
*     - At Init         : Yes
*     - After Init      : Yes
*/
#ifndef H_RFAPI_SHADOW
#define H_RFAPI_SHADOW

/********************************/
/*  Opaque Types                */
/********************************/
/****** Task ************************************************************************************/
typedef struct task                 task;

/********************************/
/*  Constants                   */
/********************************/
/****** API Module Version **********************************************************************/
#define RFAPI_SHADOW_VER            (0) /* api version                                          */

/****** Shadow Model ****************************************************************************/
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

/********************************/
/*  API Structures              */
/********************************/
/****** Shadow API ******************************************************************************/
typedef struct rfapi_shadow
{
    int32_t version;                /* structure version                                        */

    /****** Version >= 0 ************************************************************************/

    /********************************************************/
    /*
    *   Get and Set
    */
    /**** Get Shadow ****************************************/
    /*
    *   Description:
    *     Get a shadow modifier model by index.
    *
    *   Parameters:
    *     - ix          : shadow model index
    *   
    *   Returns:
    *     Shadow model; or 'nullptr' on failure.
    */
    NJS_CNK_OBJECT* (*GetShadow)( RF_SHADOW ix );

    /**** Set Shadow ****************************************/
    /*
    *   Description:
    *     Set a shadow modifier model by index.
    *
    *   Parameters:
    *     - ix          : shadow model index
    *     - object      : shadow model
    *   
    *   Returns:
    *     '0' on success; or a negative value on failure.
    */
    int32_t (*SetShadow)( RF_SHADOW ix, NJS_CNK_OBJECT* object );

    /********************************************************/
    /*
    *   Shadow Displayers
    * 
    *   Notes:
    *     - To be set as a task's shadow displayer, or
    *       called within it. 
    *     - As of writing this, shadows cannot be drawn
    *       during the other displayers.
    */
    /**** Player ********************************************/
    /*
    *   Description:
    *     Sonic (& Shadow, Amy, Metal Sonic) shadow displayer.
    */
    void (*SonicShadow)( task* tp );
    /*
    *   Description:
    *     Miles "Tails" Prower shadow displayer.
    */
    void (*MilesShadow)( task* tp );
    /*
    *   Description:
    *     Eggman shadow displayer.
    */
    void (*EggmanShadow)( task* tp );
    /*
    *   Description:
    *     Knuckles (& Rouge, Tikal, Chaos 0) shadow displayer.
    */
    void (*KnucklesShadow)( task* tp );
    /*
    *   Description:
    *     Egg Walker (& Tornado, Chao, Dark Walker) shadow displayer.
    */
    void (*EggWalkerShadow)( task* tp );
    /*
    *   Description:
    *     Player cart shadow displayer.
    */
    void (*cartShadow)( task* tp );

    /**** Object ********************************************/
    /*
    *   Description:
    *     Minimal shadow displayer.
    */
    void (*Minimal_Shad)( task* tp );
    /*
    *   Description:
    *     Chaos Drive shadow displayer.
    */
    void (*ChaosDriveShadow)( task* tp );
    /*
    *   Description:
    *     Pickup item shadow displayer.
    */
    void (*ObjectPickUpShadow)( task* tp );
    /*
    *   Description:
    *     Search box shadow displayer.
    */
    void (*ObjectSearchBoxShadow)( task* tp );
    /*
    *   Description:
    *     Omochao shadow displayer.
    */
    void (*ObjectMessengerShadow)( task* tp );
    /*
    *   Description:
    *     Floating weight hazard shadow displayer.
    */
    void (*ObjectBunchinShadow)( task* tp );
    /*
    *   Description:
    *     Spinning spike ball shadow displayer.
    */
    void (*ObjectIronBall2Shadow)( task* tp );
    /*
    *   Description:
    *     Player pulley shadow displayer.
    */
    void (*ObjectUdreelShadow)( task* tp );
    /*
    *   Description:
    *     Goal Ring (& lost Chao) shadow displayer..
    */
    void (*ObjectGoalRingShadow)( task* tp );

    /**** Object (Metal Harbor) *****************************/
    /*
    *   Description:
    *     Snow board shadow displayer.
    */
    void (*ObjectBoardShadow_MH)( task* tp );

    /**** Object (City Escape) ******************************/
    /*
    *   Description:
    *     Snow board shadow displayer.
    */
    void (*ObjectBoardShadow_CE)( task* tp );
    /*
    *   Description:
    *     Car shadow displayer.
    */
    void (*ObjectCarShadow_CE)( task* tp );
    /*
    *   Description:
    *     Car crash shadow displayer.
    */
    void (*ObjectCarCrashShadow_CE)( task* tp );
    /*
    *   Description:
    *     City Escape GUN Truck shadow displayer.
    */
    void (*ObjectTruckShadow)( task* tp );

    /**** Object (Mission Street) ***************************/
    /*
    *   Description:
    *     Car shadow displayer.
    */
    void (*ObjectCarShadow_MS)( task* tp );
    /*
    *   Description:
    *     Car crash shadow displayer.
    */
    void (*ObjectCarCrashShadow_MS)( task* tp );

    /**** Object (Egg Quaters) ******************************/
    /*
    *   Description:
    *     Egg Quaters robot beetle shadow displayer.
    */
    void (*ObjectRobotShadow)( task* tp );

    /**** Object (Meteor Herd) ******************************/
    /*
    *   Description:
    *     Meteor Herd huge blue container shadow displayer.
    */
    void (*ObjectContainerBoxShadow)( task* tp );
    /*
    *   Description:
    *     Meteor Herd moveable meteor shadow displayer.
    */
    void (*ObjectMeteoBigShadow)( task* tp );
    /*
    *   Description:
    *     Meteor Herd falling meteor shadow displayer.
    */
    void (*ObjectFireBallShadow)( task* tp );
    /*
    *   Description:
    *     Meteor Herd small overhead tank shadow displayer.
    */
    void (*ObjectTankShadow)( task* tp );

    /**** Object (Cannon's Core) ****************************/
    /*
    *   Description:
    *     Floating Cannons Core block shadow displayers.
    */
    void (*ObjectBlockShadow)( task* tp );
    void (*ObjectBlock2Shadow)( task* tp );

    /**** Object (Boss Golem) *******************************/
    /*
    *   Description:
    *     Player pulley (golem boss) shadow displayer.
    */
    void (*GolemUdreelShadow)( task* tp );

    /**** Enemy *********************************************/
    /*
    *   Description:
    *     Enemy Hunter shadow displayer.
    */
    void (*EnemyAiShadow)( task* tp );
    /*
    *   Description:
    *     Enemy Beetle shadow displayer.
    */
    void (*EnemyKumiShadow)( task* tp );    
    /*
    *   Description:
    *     Enemy Gold Beetle shadow displayer.
    */
    void (*EnemyGoldShadow)( task* tp );
    /*
    *   Description:
    *     Enemy Hawk shadow displayer.
    */
    void (*EnemyKyokoShadow)( task* tp );
    /*
    *   Description:
    *     Enemy Beetle/Hawk that follows a path shadow displayer.
    */
    void (*EnemyPathShadow)( task* tp );
    /*
    *   Description:
    *     Enemy Chaos that follows a path shadow displayer.
    */
    void (*EnemyChaosPathShadow)( task* tp );
    /*
    *   Description:
    *     Enemy Unidus/Ghola shadow displayer, and floating orbs.
    */
    void (*EnemyUniShadow)( task* tp );
    void (*UniTogeAShadow)( task* tp );
    void (*UniTogeBShadow)( task* tp );
    /*
    *   Description:
    *     Enemy Hornet shadow displayer, and rockets.
    */
    void (*EnemyNamieShadow)( task* tp );
    void (*NamieRocketShadow)( task* tp );
    /*
    *   Description:
    *     Enemy Pheonix shadow displayer, and rockets.
    */
    void (*EnemyAkahigeShadow)( task* tp );
    void (*AkahigeRocketShadow)( task* tp );
    /*
    *   Description:
    *     Enemy Jet shadow displayer.
    */
    void (*EnemyShoukoShadow)( task* tp );
    /*
    *   Description:
    *     Enemy Monkey shadow displayer.
    */
    void (*EnemySaruShadow)( task* tp );
    /*
    *   Description:
    *     Enemy E1000 shadow displayer.
    */
    void (*EnemyE1000Shadow)( task* tp );
    /*
    *   Description:
    *     Enemy Chomper shadow displayer.
    */
    void (*EnemyBataBataShadow)( task* tp );
    /*
    *   Description:
    *     Enemy Bee Bot shadow displayer.
    */
    void (*EnemyBeetonShadow)( task* tp );
    /*
    *   Description:
    *     Big the Cat shadow displayer
    */
    void (*BigTheCatShadow)( task* tp );

    /**** Chao **********************************************/
    /*
    *   Description:
    *     Chao shadow displayer.
    */
    void (*ChaoShadow)( task* tp );
    /*
    *   Description:
    *     Chao egg shadow displayer.
    */
    void (*AL_EggShadow)( task* tp );
    /*
    *   Description:
    *     Minimal (Chao World) shadow displayer.
    */
    void (*AL_MinimalShadow)( task* tp );
    /*
    *   Description:
    *     Chaos Drive (Chao World) shadow displayer.
    */
    void (*ALO_ChaosDriveShadow)( task* tp );
    /*
    *   Description:
    *     Chao fruit shadow displayer.
    */
    void (*ALO_FruitShadow)( task* tp );
    /*
    *   Description:
    *     Race fruit shadow displayer.
    */
    void (*ALO_RaceFruitShadow)( task* tp );
    /*
    *   Description:
    *     Garden tree shadow displayer.
    */
    void (*ALO_GrowTreeShadow)( task* tp );
    /*
    *   Description:
    *     Race tree shadow displayer
    */
    void (*ALO_RaceTreeShadow)( task* tp );
    /*
    *   Description:
    *     TV toy shadow displayer.
    */
    void (*ALO_TVShadow)( task* tp );
    /*
    *   Description:
    *     Radio toy shadow displayer.
    */
    void (*ALO_RadicaseShadow)( task* tp );
    /*
    *   Description:
    *     Ball toy shadow displayer.
    */
    void (*ALO_BallShadow)( task* tp );
    /*
    *   Description:
    *     Rocking horse toy shadow displayer.
    */
    void (*ALO_HorseShadow)( task* tp );
    /*
    *   Description:
    *     Jack-in-the-Box toy shadow displayer.
    */
    void (*ALO_BoxShadow)( task* tp );
    /*
    *   Description:
    *     Tree seed shadow displayer.
    */
    void (*ALO_SeedShadow)( task* tp );
    /*
    *   Description:
    *     Chao mask shadow displayer.
    */
    void (*ALO_ObakeHeadShadow)( task* tp );

    /**** Boss **********************************************/
    /*
    *   Description:
    *     King Boom Boo shadow displayer.
    */
    void    (*BossBogyShadow)( task* tp );
    /*
    *   Description:
    *     Guard robot Big Foot shadow displayer.
    */
    void    (*BossBigFootShadow)( task* tp );
    /*
    *   Description:
    *     Guard robot Hot Shot shadow displayer.
    */
    void    (*BossHotShotShadow)( task* tp );
    /*
    *   Description:
    *     Guard robot Flying Dog shadow displayer.
    */
    void    (*BossFlyingDogShadow)( task* tp );
    /*
    *   Description:
    *     Guard robot boss missile shadow displayer.
    */
    void    (*GRoboMissileShadow)( task* tp );
    /*
    *   Description:
    *     Biolizard boss energy shadow displayer.
    */
    void    (*BossLastEnergyShadow)( task* tp );
}
RFAPI_SHADOW;

#endif/*H_RFAPI_SHADOW*/
