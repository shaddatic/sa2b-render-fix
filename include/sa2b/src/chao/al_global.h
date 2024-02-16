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
    float32_t WalkAcc;
    float32_t WalkSlowAcc;
    float32_t RunAcc;
    float32_t BoundFriction;
    float32_t BoundFloor;
    int16_t  SkillLimit;
    int16_t  LifeMaxLimit;
    uint8_t   EmotionMoodLimit;
    int16_t  EmotionStateLimit;
    uint8_t   EmotionPersonalityLimit;
    float32_t DeformLimit;
    float32_t GrowthLimit;
    float32_t GrowthMayuPoint;
    float32_t NormalBoundary;
    float32_t NeutralBoundary;
    float32_t AddGrowthTime;
    float32_t TimeAddGrowthChild;
    float32_t TimeAddGrowthAdult;
    float32_t TimeAddAttrChild;
    float32_t TimeAddAttrAdult;
    float32_t PartsSetProb;
    float32_t PartsRemoveProb;
    float32_t CamDistShadowCutLev1;
    float32_t CamDistShadowCutLev2;
    float32_t CamDistShadowCutLev3;
    float32_t CamDistShadowCutLev4;
    float32_t CamDistShadowCutLev5;
    int32_t  MayuWaitTime;
    int32_t  MayuFadeInTime;
    int32_t  MayuTypeChageTime;
    int32_t  MayuFadeOutTime;
    int32_t  MayuRelaxTime;
    float32_t MayuExpandRatio;
    float32_t MayuShrinkRatio;
    float32_t MayuInitAlpha;
    int16_t  SucceedBoundaryUserLike;
    int16_t  SucceedBoundaryStress;
    int16_t  SucceedBoundaryCondition;
    int16_t  SucceedBoundaryMood;
    float32_t FruitAddGrowthChild;
    float32_t FruitAddGrowthAdult;
    int16_t  FruitAddStaminaChild;
    int16_t  FruitAddStaminaAdult;
    int32_t  FruitAddRecoverLife;
    int32_t  FruitAddLifeMax;
    int32_t  FruitAddUserLike;
    float32_t FruitAddAttrChild;
    float32_t FruitAddAttrAdult;
    float32_t FruitDislikeSubAttr;
    float32_t FruitPakuriSubAttr;
    float32_t MinimalAddFormChild;
    float32_t MinimalAddFormAdult;
    float32_t MinimalAddAttrChild;
    float32_t MinimalAddAttrAdult;
    float32_t MinimalAddGrowthChild;
    float32_t MinimalAddGrowthAdult;
    int32_t  MinimalAddUserLike;
    float32_t DakkoAddAttr;
    float32_t DamageSubAttr;
    float32_t NadeAddAttr;
    float32_t ThrownSubAttr;
    int32_t  DamageAddLife;
    int32_t  DamageAddLifeMax;
    int16_t  NestFlowerInterval;
    int16_t  nbNestFlower;
    float32_t NestRange;
    int16_t  NestWaitTime;
    int16_t  SeedClock;
    int16_t  SaplingClock;
    int16_t  TreeClock;
    int16_t  WaterSub;
    float32_t TreeFruitAddGrowth;
    int16_t  FruitMaxNum;
    int16_t  KwSubFear;
    int16_t  KwAddDistance;
    int16_t  SkillWalk;
    int16_t  SkillRun;
    int16_t  SkillRun2;
    float32_t SkillRunAccBase;
    float32_t SkillRunAccRatio;
    int16_t  SkillSwimInukaki;
    int16_t  SkillSwimBataashi;
    int16_t  SkillSwimCrawl;
    float32_t SkillSwimAccBase;
    float32_t SkillSwimAccRatio;
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
    float32_t IntentionScoreRandomRatio;
    float32_t IntentionMinScore;
    int32_t  IntentionAngerTrigger;
    int32_t  IntentionAngerPlayerTrigger;
    float32_t IntentionAngerMinScore;
    float32_t IntentionAngerMaxScore;
    int32_t  IntentionFearTrigger;
    int32_t  IntentionFearPlayerTrigger;
    float32_t IntentionFearMinScore;
    float32_t IntentionFearMaxScore;
    int32_t  IntentionSorrowTrigger;
    float32_t IntentionSorrowMinScore;
    float32_t IntentionSorrowMaxScore;
    int32_t  IntentionPainTrigger;
    float32_t IntentionPainMinScore;
    float32_t IntentionPainMaxScore;
    int32_t  IntentionPleasureTrigger;
    float32_t IntentionPleasureMinScore;
    float32_t IntentionPleasureMaxScore;
    int32_t  IntentionHungerGooMinInterval;
    int32_t  IntentionHungerGooIntervalRange;
    int32_t  IntentionHungerGooTrigger;
    float32_t IntentionHungerGooMaxScore;
    int32_t  IntentionHungerFruitGoToEatTrigger;
    float32_t IntentionHungerFruitGoToEatMaxScore;
    int32_t  IntentionHungerFruitSearchTrigger;
    float32_t IntentionHungerFruitSearchMaxScore;
    int32_t  IntentionAkubiMinInterval;
    int32_t  IntentionAkubiIntervalRange;
    int32_t  IntentionAkubiTrigger1;
    int32_t  IntentionAkubiTrigger2;
    int32_t  IntentionAkubiTrigger3;
    float32_t IntentionAkubiMaxScore;
    int32_t  IntentionPlayerGreetLonelyTrigger;
    float32_t IntentionPlayerGreetMaxScore;
    int32_t  IntentionPlayerSuriSuriLonelyTrigger;
    float32_t IntentionPlayerSuriSuriMaxScore;
    int32_t  IntentionSleepTrigger;
    float32_t IntentionSleepMaxScore;
    int32_t  IntentionHimaTrigger;
    float32_t IntentionHimaMaxScore;
    int32_t  IntentionThirstyTrigger;
    float32_t IntentionThirstyMaxScore;
    int32_t  IntentionApproachNestTrigger;
    float32_t IntentionApproachNestMaxScore;
    int32_t  IntentionJyouroThirstyTrigger;
    float32_t IntentionJyouroMaxScore;
    int32_t  IntentionRestTrigger1;
    int32_t  IntentionRestTrigger2;
    float32_t IntentionRestMaxScore;
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
    float32_t RaceTurboRatioSwim;
    float32_t RaceTurboRatioFly;
    float32_t RaceTurboRatioRun;
    float32_t RaceTurboRatioClimb;
    float32_t RaceTurboRatioTree;
    float32_t RaceTurboRatioOther;
}
CHAO_GLOBAL;

/************************/
/*  Data                */
/************************/
#define ChaoGlobal          DataRef(CHAO_GLOBAL, 0x01312C48)
#define ChaoGlobalTimer     DataRef(int32_t     , 0x01DBED70)

#endif /* _SA2B_CHAO_GLOBAL_H_ */
