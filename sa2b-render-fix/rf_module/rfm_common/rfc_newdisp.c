/************************/
/*  Includes            */
/************************/
/****** Core Toolkit ****************************************************************/
#include <samt/core.h>          /* core                                             */

/****** Render Fix ******************************************************************/
#include <rf_core.h>            /* core                                             */

/****** Self ************************************************************************/
#include <rf_module/rfm_common/rfc_internal.h>              /* parent & siblings    */
#include <rf_module/rfm_common/rfc_newdisp/rfcd_internal.h> /* children             */

/************************/
/*  Source              */
/************************/
/****** Init ************************************************************************/
void
RFC_NewDisplayerInit(void)
{
    RFCD_RingInit();
    RFCD_SpringInit();
    RFCD_GoalringInit();
    RFCD_UDReelInit();
    RFCD_MizugomiInit();
    RFCD_ItemBoxInit();
    RFCD_PrisonSirenInit();
    RFCD_FinalChaseGravityCylinderInit();
    RFCD_JungleObjectInit();

    EnemyDrawAllowDirect = TRUE;

    RFCD_EnemyJetInit();
    RFCD_EnemyKumiInit();
    RFCD_EnemyBulletInit();
}
