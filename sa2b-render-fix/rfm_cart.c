/********************************/
/*  Includes                    */
/********************************/
/****** SAMT ************************************************************************************/
#include <samt/core.h>              /* core                                                     */
#include <samt/writemem.h>          /* writedata                                                */
#include <samt/writeop.h>           /* writecall                                                */
#include <samt/string.h>            /* strformat                                                */

/****** Ninja ***********************************************************************************/
#include <samt/ninja/ninja.h>       /* ninja                                                    */

/****** Render Fix ******************************************************************************/
#include <samt/sonic/game.h>        /* stagenumber                                              */
#include <samt/sonic/light.h>       /* loadlightfile                                            */

/****** Render Fix ******************************************************************************/
#include <rf_core.h>                /* core                                                     */
#include <rf_config.h>              /* getconfig                                                */

/****** RF Utility ******************************************************************************/
#include <rfu_float.h>              /* replacefloat                                             */

/****** Self ************************************************************************************/
#include <rfm_cart.h>               /* self                                                     */

/********************************/
/*  Game Defs                   */
/********************************/
/****** Function Ptrs **************************************************************************/
#define CartSeaDisplay              FUNC_PTR(void, __cdecl, (void), 0x00621C90)

/********************************/
/*  Prototypes                  */
/********************************/
/****** Static **********************************************************************************/
static void
LoadCartLightFiles(void)
{
    c8 ubuf[32];

    mtStrFormat(ubuf, 32, "stg%02i_light.bin", ssStageNumber);

    LoadLightFile(ubuf);
}

/****** Init ************************************************************************************/
void
RFM_CartInit(void)
{
    if (RF_ConfigGetInt(CNF_CART_KANBAN))
    {
        WriteData(0x006224EC, -1063 + 39, s32);
    }

    switch (RF_ConfigGetInt(CNF_CART_CARTSPRITE))
    {
        case CNFE_CART_CARTSPRITE_DREAMCAST:
        {
            WriteNOP(0x0061CB07, 0x0061CB0C);
            break;
        }
        case CNFE_CART_CARTSPRITE_ENABLED:
        {
            RFU_ReplaceFloat(0x0061EE25, 6.0); // sprite sub
            break;
        }
    }

    if (RF_ConfigGetInt(CNF_CART_ZANKI))
    {
        /** Okay, but how does a mistake like this occur? **/
        const f64 zanki_py = 424.0 + 3.0 + 7.0;

        RFU_ReplaceFloat(0x0044E78F, zanki_py);
    }

    // load cart light files
    WriteNOP( 0x0061A4F9, 0x0061A53D);
    WriteCall(0x0061A4F9, LoadCartLightFiles);
}
