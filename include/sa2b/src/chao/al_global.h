/*
*   Sonic Adventure Mod Tools (SA2B) - '/src/chao/al_global.h'
*
*   Contains the Chao Garden's global params.
*
*   Contributors:
*   -   SEGA - Sonic Team,
*   -   Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC.
*/
#ifndef _SA2B_CHAO_GLOBAL_H_
#define _SA2B_CHAO_GLOBAL_H_

/************************/
/*  Structures          */
/************************/
typedef struct
{
    sint32  CalcBuyo;
    sint32  DispWorldEntry;
    sint32  DispOnScreen;
    sint32  DispScreenFrame;
    sint32  DispField;
    sint16  InitMulPotentialSkill;
    sint16  InitBaseLife;
    sint16  InitMulLife;
    sint16  InitMulForm;
    sint16  InitMulAttr;
    float32 WalkAcc;
    float32 WalkSlowAcc;
    float32 RunAcc;
    float32 BoundFriction;
    float32 BoundFloor;
    sint16  SkillLimit;
    sint16  LifeMaxLimit;
    uint8   EmotionMoodLimit;
    sint16  EmotionStateLimit;
    uint8   EmotionPersonalityLimit;
    float32 DeformLimit;
    float32 GrowthLimit;
    float32 GrowthMayuPoint;
    float32 NormalBoundary;
    float32 NeutralBoundary;
    float32 AddGrowthTime;
    float32 TimeAddGrowthChild;
    float32 TimeAddGrowthAdult;
    float32 TimeAddAttrChild;
    float32 TimeAddAttrAdult;
    float32 PartsSetProb;
    float32 PartsRemoveProb;
    float32 CamDistShadowCutLev1;
    float32 CamDistShadowCutLev2;
    float32 CamDistShadowCutLev3;
    float32 CamDistShadowCutLev4;
    float32 CamDistShadowCutLev5;
    sint32  MayuWaitTime;
    sint32  MayuFadeInTime;
    sint32  MayuTypeChageTime;
    sint32  MayuFadeOutTime;
    sint32  MayuRelaxTime;
    float32 MayuExpandRatio;
    float32 MayuShrinkRatio;
    float32 MayuInitAlpha;
    sint16  SucceedBoundaryUserLike;
    sint16  SucceedBoundaryStress;
    sint16  SucceedBoundaryCondition;
    sint16  SucceedBoundaryMood;
    float32 FruitAddGrowthChild;
    float32 FruitAddGrowthAdult;
    sint16  FruitAddStaminaChild;
    sint16  FruitAddStaminaAdult;
    sint32  FruitAddRecoverLife;
    sint32  FruitAddLifeMax;
    sint32  FruitAddUserLike;
    float32 FruitAddAttrChild;
    float32 FruitAddAttrAdult;
    float32 FruitDislikeSubAttr;
    float32 FruitPakuriSubAttr;
    float32 MinimalAddFormChild;
    float32 MinimalAddFormAdult;
    float32 MinimalAddAttrChild;
    float32 MinimalAddAttrAdult;
    float32 MinimalAddGrowthChild;
    float32 MinimalAddGrowthAdult;
    sint32  MinimalAddUserLike;
    float32 DakkoAddAttr;
    float32 DamageSubAttr;
    float32 NadeAddAttr;
    float32 ThrownSubAttr;
    sint32  DamageAddLife;
    sint32  DamageAddLifeMax;
    sint16  NestFlowerInterval;
    sint16  nbNestFlower;
    float32 NestRange;
    sint16  NestWaitTime;
    sint16  SeedClock;
    sint16  SaplingClock;
    sint16  TreeClock;
    sint16  WaterSub;
    float32 TreeFruitAddGrowth;
    sint16  FruitMaxNum;
    sint16  KwSubFear;
    sint16  KwAddDistance;
    sint16  SkillWalk;
    sint16  SkillRun;
    sint16  SkillRun2;
    float32 SkillRunAccBase;
    float32 SkillRunAccRatio;
    sint16  SkillSwimInukaki;
    sint16  SkillSwimBataashi;
    sint16  SkillSwimCrawl;
    float32 SkillSwimAccBase;
    float32 SkillSwimAccRatio;
    sint16  ParamSubPleasure;
    sint16  ParamSubAnger;
    sint16  ParamSubSorrow;
    sint16  ParamSubFear;
    sint16  ParamSubSurprise;
    sint16  ParamSubPain;
    sint16  ParamSubRelax;
    sint16  ParamAddSleepy;
    sint16  ParamSubSleepy;
    sint16  ParamAddSleepDepth;
    sint16  ParamSubSleepDepth;
    sint16  ParamWakeUpSleepDepth;
    sint16  ParamAddHunger;
    sint16  ParamSubHunger;
    sint16  ParamAddBreed;
    sint16  ParamAddTediousCuriosity;
    sint16  ParamAddTediousAggressive;
    sint16  ParamAddTediousCalm;
    sint16  ParamSubTediousWalk;
    sint16  ParamSubTediousSwim;
    sint16  ParamAddLonely;
    sint16  ParamAddLonelyGreet;
    sint16  ParamAddLonelySuri;
    sint16  ParamAddLonelyAttack;
    sint16  ParamAddTireNormal;
    sint16  ParamSubTireSleep;
    sint16  ParamSubTireRest;
    sint16  ParamAddTireWalk;
    sint16  ParamAddTireRun;
    sint16  ParamAddTireSwim;
    sint16  ParamSubTireSwimStop;
    sint16  ParamSubNourishment;
    sint16  ParamAddConditionN;
    sint16  ParamConditionTriggerAddN;
    sint16  ParamSubConditionN;
    sint16  ParamConditionTriggerSubN;
    sint16  ParamSubConditionS;
    sint16  ParamConditionTriggerS;
    sint16  ParamSubConditionP;
    sint16  ParamConditionTriggerP;
    sint16  ParamAddConditionRest;
    sint16  ParamAddThirsty;
    sint16  ParamSubThirstySwim;
    sint16  ChaoTimerBaseInterval;
    sint16  ChaoTimerLifeInterval;
    sint16  ChaoTimerEmotionInterval;
    sint16  ChaoTimerMoodInterval;
    sint16  ChaoTimerKnowledgeInterval;
    sint16  ChaoTimerIllInterval;
    float32 IntentionScoreRandomRatio;
    float32 IntentionMinScore;
    sint32  IntentionAngerTrigger;
    sint32  IntentionAngerPlayerTrigger;
    float32 IntentionAngerMinScore;
    float32 IntentionAngerMaxScore;
    sint32  IntentionFearTrigger;
    sint32  IntentionFearPlayerTrigger;
    float32 IntentionFearMinScore;
    float32 IntentionFearMaxScore;
    sint32  IntentionSorrowTrigger;
    float32 IntentionSorrowMinScore;
    float32 IntentionSorrowMaxScore;
    sint32  IntentionPainTrigger;
    float32 IntentionPainMinScore;
    float32 IntentionPainMaxScore;
    sint32  IntentionPleasureTrigger;
    float32 IntentionPleasureMinScore;
    float32 IntentionPleasureMaxScore;
    sint32  IntentionHungerGooMinInterval;
    sint32  IntentionHungerGooIntervalRange;
    sint32  IntentionHungerGooTrigger;
    float32 IntentionHungerGooMaxScore;
    sint32  IntentionHungerFruitGoToEatTrigger;
    float32 IntentionHungerFruitGoToEatMaxScore;
    sint32  IntentionHungerFruitSearchTrigger;
    float32 IntentionHungerFruitSearchMaxScore;
    sint32  IntentionAkubiMinInterval;
    sint32  IntentionAkubiIntervalRange;
    sint32  IntentionAkubiTrigger1;
    sint32  IntentionAkubiTrigger2;
    sint32  IntentionAkubiTrigger3;
    float32 IntentionAkubiMaxScore;
    sint32  IntentionPlayerGreetLonelyTrigger;
    float32 IntentionPlayerGreetMaxScore;
    sint32  IntentionPlayerSuriSuriLonelyTrigger;
    float32 IntentionPlayerSuriSuriMaxScore;
    sint32  IntentionSleepTrigger;
    float32 IntentionSleepMaxScore;
    sint32  IntentionHimaTrigger;
    float32 IntentionHimaMaxScore;
    sint32  IntentionThirstyTrigger;
    float32 IntentionThirstyMaxScore;
    sint32  IntentionApproachNestTrigger;
    float32 IntentionApproachNestMaxScore;
    sint32  IntentionJyouroThirstyTrigger;
    float32 IntentionJyouroMaxScore;
    sint32  IntentionRestTrigger1;
    sint32  IntentionRestTrigger2;
    float32 IntentionRestMaxScore;
    sint32  IntentionRestEndTrigger;
    sint32  RaceIntervalSubStamina;
    sint32  RaceSubStaminaSwim;
    sint32  RaceSubStaminaFly;
    sint32  RaceSubStaminaRun;
    sint32  RaceSubStaminaClimb;
    sint32  RaceSubStaminaTree;
    sint32  RaceSubStaminaOther;
    sint32  RaceAddStaminaSit;
    sint32  RaceCheerInterval;
    sint32  RaceCheerDecAimStamina;
    sint32  RaceCheerDecStamina;
    float32 RaceTurboRatioSwim;
    float32 RaceTurboRatioFly;
    float32 RaceTurboRatioRun;
    float32 RaceTurboRatioClimb;
    float32 RaceTurboRatioTree;
    float32 RaceTurboRatioOther;
}
CHAO_GLOBAL;

/************************/
/*  Data                */
/************************/
#define ChaoGlobal          DataRef(CHAO_GLOBAL, 0x01312C48)
#define ChaoGlobalTimer     DataRef(sint32     , 0x01DBED70)

#endif /* _SA2B_CHAO_GLOBAL_H_ */