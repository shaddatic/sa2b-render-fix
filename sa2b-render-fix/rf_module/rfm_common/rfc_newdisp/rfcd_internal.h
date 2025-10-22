/*
*   SA2 Render Fix - '/rf_draw/rfc_newdisp/rfcd_internal.h'
*
*   Description:
*     Internal header for common/new displayer sub-module.
*
*   Contributors:
*     - Shaddatic
*/
#ifndef H_RF_COMMON_NEWDISP_INTERNAL
#define H_RF_COMMON_NEWDISP_INTERNAL

EXTERN_START

/********************************/
/*  Constants                   */
/********************************/
/****** DirectDraw ******************************************************************************/
#define EnemyDrawAllowDirect        DATA_REF(Bool, 0x0174AFFC)

/************************/
/*  Prototypes          */
/************************/
/****** Init ************************************************************************/
/*
*   Description:
*     UDReel new displayer init.
*/
void    RFCD_UDReelInit( void );
/*
*   Description:
*     Enemy Jet effects displayer init.
*/
void    RFCD_EnemyJetInit( void );
/*
*   Description:
*     Mizugomi effects displayer init.
*/
void    RFCD_MizugomiInit( void );
/*
*   Description:
*     Item box displayer init.
*/
void    RFCD_ItemBoxInit( void );
/*
*   Description:
*     Final Chase gravity cylinder displayer init.
*/
void    RFCD_FinalChaseGravityCylinderInit( void );
/*
*   Description:
*     Prison siren displayer init.
*/
void    RFCD_PrisonSirenInit( void );
/*
*   Description:
*     Ring displayer init.
*/
void    RFCD_RingInit( void );
/*
*   Description:
*     Spring displayers init.
*/
void    RFCD_SpringInit( void );
/*
*   Description:
*     Goalring/Lost Chao displayer init.
*/
void    RFCD_GoalringInit( void );
/*
*   Description:
*     Green Forest 'Jungle Object' displayer init.
*/
void    RFCD_JungleObjectInit( void );
/*
*   Description:
*     Enemy Kumi Beetle.
*/
void    RFCD_EnemyKumiInit( void );
/*
*   Description:
*     Enemy bullet init.
*/
void    RFCD_EnemyBulletInit( void );
/*
*   Description:
*     Sonic/Shadow trick ramps.
*/
void    RFCD_TrickJumpDaiInit( void );

EXTERN_END

#endif/*H_RF_COMMON_NEWDISP_INTERNAL*/
