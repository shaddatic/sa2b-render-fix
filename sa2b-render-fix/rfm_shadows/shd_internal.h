/*
*   SA2 Render Fix - '/cheap_shadow/chs_internal.h'
*
*   Description:
*       Internal header for the Cheap Shadow feature.
*
*   Contributors:
*   -   Shaddatic
*   -   Exant (Original Creator)
*/
#ifndef _RFM_SHADOW_INTERNAL_H_
#define _RFM_SHADOW_INTERNAL_H_

/************************/
/*  Enums               */
/************************/
enum
{
    PL_SHDMD_VANILLA,
    PL_SHDMD_ENHANCED,
    PL_SHDMD_ENH_EQUIP,
    PL_SHDMD_MODIFIER
};

/************************/
/*  Functions           */
/************************/
EXTERN_START
void    CHS_PlayerInit();
void    CHS_BoardInit();
void    CHS_MessengerInit();
void    CHS_BunchinInit();
void    CHS_ModModInit();
void    CHS_UdreelInit();
void    CHS_SearchBoxInit();
void    CHS_GoalRingInit();
void    CHS_EnemyInit();
void    CHS_IronBall2Init();
void    CHS_EggQuatersRobotInit();
void    CHS_TruckInit();
void    CHS_ChaosDriveInit();
void    CHS_MinimalInit();
void    CHS_PickUpInit();
void    CHS_CarInit();
void    CHS_TankInit();
void    CHS_MDContainerBoxInit();
void    CHS_MeteoBigInit();
void    CHS_CCBlockInit();
void    CHS_BossInit();
void    CHS_CartInit();
void    CHS_ChaoWorldInit();

void    EnhancedPlayerShadowsInit();

EXTERN_END

#endif/*_RFM_SHADOW_INTERNAL_H_*/
