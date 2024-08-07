/*
*   Sonic Adventure Mod Tools (SA2B) - '/sonic/chao/al_global.h'
*
*   Description:
*       Contains the Chao Garden's global params.
*
*   Contributors:
*     - SEGA - Sonic Team,
*     - Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC
*/
#ifndef _SA2B_CHAO_GLOBAL_H_
#define _SA2B_CHAO_GLOBAL_H_

/************************/
/*  Structures          */
/************************/
typedef struct
{
    int32_t  CalcBuyo;
    int32_t  DispWorldEntry;
    int32_t  DispOnScreen;
    int32_t  DispScreenFrame;
    int32_t  DispField;
    int16_t  InitMulPotentialSkill;
    int16_t  InitBaseLife;
    int16_t  InitMulLife;
    int16_t  InitMulForm;
    int16_t  InitMulAttr;
    f32       WalkAcc;
    f32       WalkSlowAcc;
    f32       RunAcc;
    f32       BoundFriction;
    f32       BoundFloor;
    int16_t  SkillLimit;
    int16_t  LifeMaxLimit;
    uint8_t   EmotionMoodLimit;
    int16_t  EmotionStateLimit;
    uint8_t   EmotionPersonalityLimit;
    f32       DeformLimit;
    f32       GrowthLimit;
    f32       GrowthMayuPoint;
    f32       NormalBoundary;
    f32       NeutralBoundary;
    f32       AddGrowthTime;
    f32       TimeAddGrowthChild;
    f32       TimeAddGrowthAdult;
    f32       TimeAddAttrChild;
    f32       TimeAddAttrAdult;
    f32       PartsSetProb;
    f32       PartsRemoveProb;
    f32       CamDistShadowCutLev1;
    f32       CamDistShadowCutLev2;
    f32       CamDistShadowCutLev3;
    f32       CamDistShadowCutLev4;
    f32       CamDistShadowCutLev5;
    int32_t  MayuWaitTime;
    int32_t  MayuFadeInTime;
    int32_t  MayuTypeChageTime;
    int32_t  MayuFadeOutTime;
    int32_t  MayuRelaxTime;
    f32       MayuExpandRatio;
    f32       MayuShrinkRatio;
    f32       MayuInitAlpha;
    int16_t  SucceedBoundaryUserLike;
    int16_t  SucceedBoundaryStress;
    int16_t  SucceedBoundaryCondition;
    int16_t  SucceedBoundaryMood;
    f32       FruitAddGrowthChild;
    f32       FruitAddGrowthAdult;
    int16_t  FruitAddStaminaChild;
    int16_t  FruitAddStaminaAdult;
    int32_t  FruitAddRecoverLife;
    int32_t  FruitAddLifeMax;
    int32_t  FruitAddUserLike;
    f32       FruitAddAttrChild;
    f32       FruitAddAttrAdult;
    f32       FruitDislikeSubAttr;
    f32       FruitPakuriSubAttr;
    f32       MinimalAddFormChild;
    f32       MinimalAddFormAdult;
    f32       MinimalAddAttrChild;
    f32       MinimalAddAttrAdult;
    f32       MinimalAddGrowthChild;
    f32       MinimalAddGrowthAdult;
    int32_t  MinimalAddUserLike;
    f32       DakkoAddAttr;
    f32       DamageSubAttr;
    f32       NadeAddAttr;
    f32       ThrownSubAttr;
    int32_t  DamageAddLife;
    int32_t  DamageAddLifeMax;
    int16_t  NestFlowerInterval;
    int16_t  nbNestFlower;
    f32       NestRange;
    int16_t  NestWaitTime;
    int16_t  SeedClock;
    int16_t  SaplingClock;
    int16_t  TreeClock;
    int16_t  WaterSub;
    f32       TreeFruitAddGrowth;
    int16_t  FruitMaxNum;
    int16_t  KwSubFear;
    int16_t  KwAddDistance;
    int16_t  SkillWalk;
    int16_t  SkillRun;
    int16_t  SkillRun2;
    f32       SkillRunAccBase;
    f32       SkillRunAccRatio;
    int16_t  SkillSwimInukaki;
    int16_t  SkillSwimBataashi;
    int16_t  SkillSwimCrawl;
    f32       SkillSwimAccBase;
    f32       SkillSwimAccRatio;
    int16_t  ParamSubPleasure;
    int16_t  ParamSubAnger;
    int16_t  ParamSubSorrow;
    int16_t  ParamSubFear;
    int16_t  ParamSubSurprise;
    int16_t  ParamSubPain;
    int16_t  ParamSubRelax;
    int16_t  ParamAddSleepy;
    int16_t  ParamSubSleepy;
    int16_t  ParamAddSleepDepth;
    int16_t  ParamSubSleepDepth;
    int16_t  ParamWakeUpSleepDepth;
    int16_t  ParamAddHunger;
    int16_t  ParamSubHunger;
    int16_t  ParamAddBreed;
    int16_t  ParamAddTediousCuriosity;
    int16_t  ParamAddTediousAggressive;
    int16_t  ParamAddTediousCalm;
    int16_t  ParamSubTediousWalk;
    int16_t  ParamSubTediousSwim;
    int16_t  ParamAddLonely;
    int16_t  ParamAddLonelyGreet;
    int16_t  ParamAddLonelySuri;
    int16_t  ParamAddLonelyAttack;
    int16_t  ParamAddTireNormal;
    int16_t  ParamSubTireSleep;
    int16_t  ParamSubTireRest;
    int16_t  ParamAddTireWalk;
    int16_t  ParamAddTireRun;
    int16_t  ParamAddTireSwim;
    int16_t  ParamSubTireSwimStop;
    int16_t  ParamSubNourishment;
    int16_t  ParamAddConditionN;
    int16_t  ParamConditionTriggerAddN;
    int16_t  ParamSubConditionN;
    int16_t  ParamConditionTriggerSubN;
    int16_t  ParamSubConditionS;
    int16_t  ParamConditionTriggerS;
    int16_t  ParamSubConditionP;
    int16_t  ParamConditionTriggerP;
    int16_t  ParamAddConditionRest;
    int16_t  ParamAddThirsty;
    int16_t  ParamSubThirstySwim;
    int16_t  ChaoTimerBaseInterval;
    int16_t  ChaoTimerLifeInterval;
    int16_t  ChaoTimerEmotionInterval;
    int16_t  ChaoTimerMoodInterval;
    int16_t  ChaoTimerKnowledgeInterval;
    int16_t  ChaoTimerIllInterval;
    f32       IntentionScoreRandomRatio;
    f32       IntentionMinScore;
    int32_t  IntentionAngerTrigger;
    int32_t  IntentionAngerPlayerTrigger;
    f32       IntentionAngerMinScore;
    f32       IntentionAngerMaxScore;
    int32_t  IntentionFearTrigger;
    int32_t  IntentionFearPlayerTrigger;
    f32       IntentionFearMinScore;
    f32       IntentionFearMaxScore;
    int32_t  IntentionSorrowTrigger;
    f32       IntentionSorrowMinScore;
    f32       IntentionSorrowMaxScore;
    int32_t  IntentionPainTrigger;
    f32       IntentionPainMinScore;
    f32       IntentionPainMaxScore;
    int32_t  IntentionPleasureTrigger;
    f32       IntentionPleasureMinScore;
    f32       IntentionPleasureMaxScore;
    int32_t  IntentionHungerGooMinInterval;
    int32_t  IntentionHungerGooIntervalRange;
    int32_t  IntentionHungerGooTrigger;
    f32       IntentionHungerGooMaxScore;
    int32_t  IntentionHungerFruitGoToEatTrigger;
    f32       IntentionHungerFruitGoToEatMaxScore;
    int32_t  IntentionHungerFruitSearchTrigger;
    f32       IntentionHungerFruitSearchMaxScore;
    int32_t  IntentionAkubiMinInterval;
    int32_t  IntentionAkubiIntervalRange;
    int32_t  IntentionAkubiTrigger1;
    int32_t  IntentionAkubiTrigger2;
    int32_t  IntentionAkubiTrigger3;
    f32       IntentionAkubiMaxScore;
    int32_t  IntentionPlayerGreetLonelyTrigger;
    f32       IntentionPlayerGreetMaxScore;
    int32_t  IntentionPlayerSuriSuriLonelyTrigger;
    f32       IntentionPlayerSuriSuriMaxScore;
    int32_t  IntentionSleepTrigger;
    f32       IntentionSleepMaxScore;
    int32_t  IntentionHimaTrigger;
    f32       IntentionHimaMaxScore;
    int32_t  IntentionThirstyTrigger;
    f32       IntentionThirstyMaxScore;
    int32_t  IntentionApproachNestTrigger;
    f32       IntentionApproachNestMaxScore;
    int32_t  IntentionJyouroThirstyTrigger;
    f32       IntentionJyouroMaxScore;
    int32_t  IntentionRestTrigger1;
    int32_t  IntentionRestTrigger2;
    f32       IntentionRestMaxScore;
    int32_t  IntentionRestEndTrigger;
    int32_t  RaceIntervalSubStamina;
    int32_t  RaceSubStaminaSwim;
    int32_t  RaceSubStaminaFly;
    int32_t  RaceSubStaminaRun;
    int32_t  RaceSubStaminaClimb;
    int32_t  RaceSubStaminaTree;
    int32_t  RaceSubStaminaOther;
    int32_t  RaceAddStaminaSit;
    int32_t  RaceCheerInterval;
    int32_t  RaceCheerDecAimStamina;
    int32_t  RaceCheerDecStamina;
    f32       RaceTurboRatioSwim;
    f32       RaceTurboRatioFly;
    f32       RaceTurboRatioRun;
    f32       RaceTurboRatioClimb;
    f32       RaceTurboRatioTree;
    f32       RaceTurboRatioOther;
}
CHAO_GLOBAL;

/************************/
/*  Data                */
/************************/
#define ChaoGlobal          DATA_REF(CHAO_GLOBAL, 0x01312C48)
#define ChaoGlobalTimer     DATA_REF(int32_t     , 0x01DBED70)

#endif /* _SA2B_CHAO_GLOBAL_H_ */
