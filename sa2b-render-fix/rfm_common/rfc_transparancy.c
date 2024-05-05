/************************/
/*  Includes            */
/************************/
/****** Core Toolkit ****************************************************************/
#include <sa2b/core.h>      /* core                                                 */
#include <sa2b/memutil.h>   /* WriteData, WriteJump, WritePointer                   */

/****** Render Fix ******************************************************************/
#include <rf_core.h>        /* core                                                 */
#include <rf_util.h>        /* ReplaceFloat, SwitchDisplayer                        */
#include <rf_config.h>      /* RF_ConfigGet                                         */

/****** Self ************************************************************************/
#include <rfm_common/rfc_transparancy/rfct_internal.h> /* self                      */

void
RFC_TransparancyInit(void)
{
    if (!RF_ConfigGetInt(CNF_COMMON_TR_SORT))
        return;

    /** Displayer switching **/
    {
        SwitchDisplayer(0x006EDB91, DISP_SORT); // Water Ripples
        SwitchDisplayer(0x0075A166, DISP_DELY); // Bubble draw fix
        SwitchDisplayer(0x006FD65E, DISP_SORT); // PC Wall

        SwitchDisplayer(0x005113AA, DISP_DELY); // Enemy Jet
        SwitchDisplayer(0x00511422, DISP_DELY); // ^

        WritePointer(0x005BA0F6, 0x0117EEEC); // Sky Rail clouds
        WritePointer(0x005BA13E, 0x0117EE34); // ^

        SwitchDisplayer(0x004B39CD, DISP_SORT); // P-Hill clouds

        SwitchDisplayer(0x006A5338, DISP_SORT); // W-Canyon Fans

        SwitchDisplayer(0x007048E6, DISP_SORT); // P-Cave Spiderwebs
        SwitchDisplayer(0x0070248C, DISP_SORT); // P-Cave Wall Eyes
        SwitchDisplayer(0x006FC851, DISP_SORT); // P-Cave Chimney
        SwitchDisplayer(0x00701F3E, DISP_SORT); // P-Cave Firepot Fire
        SwitchDisplayer(0x00707826, DISP_SORT); // P-Cave Snakedish Fire
        SwitchDisplayer(0x007042E7, DISP_SORT); // P-Cave Awning Fire
        SwitchDisplayer(0x00707E27, DISP_SORT); // P-Cave Snake Head Fire
        SwitchDisplayer(0x006FE59E, DISP_SORT); // P-Cave Torch Cup Fire

        SwitchDisplayer(0x00762D75, DISP_LAST); // Boss Title Text

        SwitchDisplayer(0x00501BA5, DISP_SORT); // Enemy Ghosts

        SwitchDisplayer(0x0060B5CE, DISP_SORT); // Boss Bogy
        SwitchDisplayer(0x00761C04, DISP_LAST); // Boss Bogy Powergauge

        SwitchDisplayer(0x0044F845, DISP_LAST); // Results Score Text
        SwitchDisplayer(0x00450805, DISP_LAST); // Results Time Text
        SwitchDisplayer(0x0044F65B, DISP_LATE); // Results Window
        SwitchDisplayer(0x004531DF, DISP_LATE); // Results Ring Window
        SwitchDisplayer(0x004531E6, DISP_LAST); // Results Ring Window

        SwitchDisplayer(0x00476CAF, DISP_SORT); // "PlayerDrawMotionWithAlphaReducing"

        SwitchDisplayer(0x00545633, DISP_SORT); // ALO_ChaosDrive

        SwitchDisplayer(0x0061BB94, DISP_DELY); // Cart HUD

        SwitchDisplayer(0x006054F6, DISP_SORT); // Tails Prison search lights

        SwitchDisplayer(0x006A5D89, DISP_SORT); // Wild Canyon flags (upper)

        SwitchDisplayer(0x006409E9, DISP_SORT); // Dry Lagoon Plant2
        SwitchDisplayer(0x006471F9, DISP_SORT); // Dry Lagoon Plant3
        SwitchDisplayer(0x0063D70F, DISP_DELY); // Dry Lagoon BgDisp

        SwitchDisplayer(0x005B4944, DISP_SORT); // Mission Street Cars

        if (RF_ConfigGetInt(CNF_COMPAT_DCSHADCRASH))
        {
            WriteNoOP(0x00612C86, 0x00612CAA);  // DC Shadows crash patch for Boss Bogy
        }
    }

    RFCT_ExplosionInit();
    RFCT_ItemBoxInit();
    RFCT_PrisonSirenInit();
    RFCT_FinalChaseGravityCylinderInit();
}
