#define RF_SHADOW_INCL_TASKS

/********************************/
/*  Includes                    */
/********************************/
/****** SAMT ************************************************************************************/
#include <samt/core.h>              /* core                                                     */

/****** Render Fix ******************************************************************************/
#include <rf_core.h>                /* core                                                     */

/****** Self ************************************************************************************/
#include <rf_api/rfapi_internal.h>  /* parent & siblings                                        */
#include <rf_shadow.h>              /* self                                                     */

/********************************/
/*  Export Data                 */
/********************************/
/****** Shadow API ******************************************************************************/
EXTERN
const RFAPI_SHADOW rfapi_shadow =
{
    .version = RFAPI_SHADOW_VER,

    .GetShadow = GetShadow,
    .SetShadow = SetShadow,

    // player
    .SonicShadow            = SonicShadow,
    .MilesShadow            = MilesShadow,
    .EggmanShadow           = EggmanShadow,
    .KnucklesShadow         = KnucklesShadow,
    .EggWalkerShadow        = EggWalkerShadow,
    .cartShadow             = cartShadow,

    // object
    .Minimal_Shad           = Minimal_Shad,
    .ChaosDriveShadow       = ChaosDriveShadow,
    .ObjectPickUpShadow     = ObjectPickUpShadow,
    .ObjectSearchBoxShadow  = ObjectSearchBoxShadow,
    .ObjectMessengerShadow  = ObjectMessengerShadow,
    .ObjectBunchinShadow    = ObjectBunchinShadow,
    .ObjectIronBall2Shadow  = ObjectIronBall2Shadow,
    .ObjectUdreelShadow     = ObjectUdreelShadow,
    .ObjectGoalRingShadow   = ObjectGoalRingShadow,

    .ObjectBoardShadow_MH   = ObjectBoardShadow_MH,

    .ObjectBoardShadow_CE    = ObjectBoardShadow_CE,
    .ObjectCarShadow_CE      = ObjectCarShadow_CE,
    .ObjectCarCrashShadow_CE = ObjectCarCrashShadow_CE,
    .ObjectTruckShadow       = ObjectTruckShadow,

    .ObjectCarShadow_MS      = ObjectCarShadow_MS,
    .ObjectCarCrashShadow_MS = ObjectCarCrashShadow_MS,

    .ObjectContainerBoxShadow = ObjectContainerBoxShadow,
    .ObjectMeteoBigShadow     = ObjectMeteoBigShadow,
    .ObjectFireBallShadow     = ObjectFireBallShadow,
    .ObjectTankShadow         = ObjectTankShadow,

    .ObjectBlockShadow      = ObjectBlockShadow,
    .ObjectBlock2Shadow     = ObjectBlock2Shadow,

    // enemy
    .EnemyAiShadow          = EnemyShadow,
    .EnemyKumiShadow        = EnemyKumiShadow,
    .EnemyGoldShadow        = EnemyGoldShadow,
    .EnemyKyokoShadow       = EnemyKyokoShadow,
    .EnemyPathShadow        = EnemyPathShadow,
    .EnemyChaosPathShadow   = EnemyChaosPathShadow,
    .EnemyUniShadow         = EnemyShadow,
    .UniTogeAShadow         = EnemyShadow,
    .UniTogeBShadow         = EnemyShadow,
    .EnemyNamieShadow       = EnemyNamieShadow,
    .NamieRocketShadow      = EnemyNamieRocketShadow,
    .EnemyAkahigeShadow     = EnemyAkahigeShadow,
    .AkahigeRocketShadow    = EnemyAkahigeRocketShadow,
    .EnemyShoukoShadow      = EnemyShoukoShadow,
    .EnemySaruShadow        = EnemyShadow,
    .EnemyE1000Shadow       = EnemyShadow,
    .EnemyBataBataShadow    = EnemyBataBeeShadow,
    .EnemyBeetonShadow      = EnemyBataBeeShadow,
    .BigTheCatShadow        = EnemyShadow,

    // chao
    .ChaoShadow             = ChaoShadow,
    .AL_EggShadow           = AL_EggShadow,
    .AL_MinimalShadow       = AL_MinimalShadow,
    .ALO_ChaosDriveShadow   = ALO_ChaosDriveShadow,
    .ALO_FruitShadow        = ALO_FruitShadow,
    .ALO_RaceFruitShadow    = ALO_RaceFruitShadow,
    .ALO_GrowTreeShadow     = ALO_GrowTreeShadow,
    .ALO_RaceTreeShadow     = ALO_RaceTreeShadow,
    .ALO_SeedShadow         = ALO_SeedShadow,
    .ALO_ObakeHeadShadow    = ALO_ObakeHeadShadow,

    // chao toys
    .ALO_TVShadow           = ALO_TVShadow,
    .ALO_RadicaseShadow     = ALO_RadicaseShadow,
    .ALO_BallShadow         = ALO_BallShadow,
    .ALO_HorseShadow        = ALO_HorseShadow,
    .ALO_BoxShadow          = ALO_BoxShadow,

    // boss
    .BossBogyShadow         = BigBogyShadow,
    .BossBigFootShadow      = BossBigFootShadow,
    .BossHotShotShadow      = BossHotShotShadow,
    .BossFlyingDogShadow    = BossFlyingDogShadow,
    .GRoboMissileShadow     = GRoboMissileShadow,
    .BossLastEnergyShadow   = BossLastEnergyShadow,
};
