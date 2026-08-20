/*
*   SA2 Render Fix - '/rf_shadow/chs_internal.h'
*
*   Description:
*     Internal header for the cheap shadow module.
*/
#ifndef H_RF_SHADOW_INTERNAL
#define H_RF_SHADOW_INTERNAL

/********************************/
/*  Includes                    */
/********************************/
/****** Self ************************************************************************************/
#include <rf_shadow.h>              /* root parent                                              */

EXTERN_START

/********************************/
/*  Constants                   */
/********************************/
/****** ModMod **********************************************************************************/
enum
{
    MODMOD_MODEL_HEX_DEBUG,         /* debug hexagon shadow                                     */
    MODMOD_MODEL_HEX,               /* hexagon shadow                                           */
    MODMOD_MODEL_BOX_DEBUG,         /* debug cube shadow                                        */
    MODMOD_MODEL_BOX,               /* cube shadow                                              */

    MODMOD_MODEL_NUM,               /* enum count                                               */
};

/********************************/
/*  Game Refs                   */
/********************************/
/****** ModMod **********************************************************************************/
#define ModModModels                DATA_ARY(NJS_CNK_MODEL*, 0x00B4D82C, [MODMOD_MODEL_NUM])

/********************************/
/*  Prototypes                  */
/********************************/
/****** Init ************************************************************************************/
void    CHS_PlayerInit(void);
void    CHS_BoardInit(void);
void    CHS_MessengerInit(void);
void    CHS_BunchinInit(void);
void    CHS_ModModInit(void);
void    CHS_UdreelInit(void);
void    CHS_SearchBoxInit(void);
void    CHS_GoalRingInit(void);
void    CHS_EnemyInit(void);
void    CHS_IronBall2Init(void);
void    CHS_EggQuatersRobotInit(void);
void    CHS_TruckInit(void);
void    CHS_ChaosDriveInit(void);
void    CHS_MinimalInit(void);
void    CHS_PickUpInit(void);
void    CHS_CarInit(void);
void    CHS_TankInit(void);
void    CHS_MDContainerBoxInit(void);
void    CHS_MeteoBigInit(void);
void    CHS_CCBlockInit(void);
void    CHS_BossInit(void);
void    CHS_CartInit(void);
void    CHS_ChaoWorldInit(void);

/****** Kill Shadow Tex *************************************************************************/
/*
*   Description:
*     Nullsub that returns 'NULL'.
*/
void*   CreateNoStencilTexture( void );

/****** Legacy **********************************************************************************/
void    EnhancedPlayerShadowsInit( void );

EXTERN_END

#endif/*H_RF_SHADOW_INTERNAL*/
