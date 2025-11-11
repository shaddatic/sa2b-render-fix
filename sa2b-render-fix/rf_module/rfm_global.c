/********************************/
/*  Includes                    */
/********************************/
/****** SAMT ************************************************************************************/
#include <samt/core.h>              /* core                                                     */
#include <samt/writemem.h>          /* writedata                                                */
#include <samt/writeop.h>           /* writejump                                                */
#include <samt/funchook.h>          /* funchook                                                 */

/****** GX **************************************************************************************/
#define SAMT_INCL_FUNCPTRS
#include <samt/gx/gx.h>             /* gx                                                       */
#undef  SAMT_INCL_FUNCPTRS

/****** Ninja ***********************************************************************************/
#include <samt/ninja/ninja.h>       /* ninja                                                    */

/****** Game ************************************************************************************/
#include <samt/sonic/display.h>     /* getdisplayratio                                          */

/****** Render Fix ******************************************************************************/
#include <rf_core.h>                /* core                                                     */
#include <rf_renderstate.h>         /* setdefaultcullmode                                       */
#include <rf_magic.h>               /* setpointsize                                             */

/****** Config **********************************************************************************/
#include <cnf.h>                    /* config get                                               */

/****** RF Utility ******************************************************************************/
#include <rfu_float.h>              /* replaceflaot                                             */

/****** Self ************************************************************************************/
#include <rf_module/rfm_global/rfg_internal.h> /* children                                      */

/********************************/
/*  Data                        */
/********************************/
/****** Feature *********************************************************************************/
static bool RfgBackColor;           /* backcolor setting                                        */
static bool RfgSpotLight;           /* spotlight fix                                            */

/********************************/
/*  Prototypes                  */
/********************************/
/****** Static **********************************************************************************/
static int __cdecl
njSearchTexMemList_(void)
{
    return -1;
}

static void __cdecl
RF_SetPointSize(uint8_t size)
{
    RF_MagicSetPointSize(((float)size) * GetDisplayRatioY());
}

__declspec(naked)
static void
__SetPointSize(void)
{
    __asm
    {
        push eax
        call RF_SetPointSize
        pop eax
        retn
    }
}

/****** Feature *********************************************************************************/
bool
RFF_BackColorDraw(void)
{
    return RfgBackColor;
}

bool
RFF_SpotLightFix(void)
{
    return true;
}

/****** Init ************************************************************************************/
void
RFM_GlobalInit(void)
{
    RFG_UiFilterInit();
    RFG_DrawFunctionInit();

    if ( CNF_GetInt(CNF_GLOBAL_IGBIX) )
    {
        WriteJump(0x0042FAD0, njSearchTexMemList_);
    }

    RFG_BackfaceCullingInit();

    RfgBackColor = true;
    RFG_NinjaBackColorInit();

    {
        constexpr double ptcldbl00 = 1.5;
        constexpr double ptcldbl01 = 2.0;

        constexpr double ptcldbl02 = 1.0;

        constexpr double ptcldbl03 = 30.0;
        constexpr double ptcldbl04 = 32.5;

        constexpr double ptcldbl05 = 0.0000457763671875;

        /** Some particles were made 2x as big to counteract
            the halvaning, this reverts that **/

        RFU_ReplaceFloat(0x006D6117, ptcldbl00); // RocketRocket
        RFU_ReplaceFloat(0x006D611D, ptcldbl01); // ^

        RFU_ReplaceFloat(0x006D5455, ptcldbl02); // Rocket
        RFU_ReplaceFloat(0x006D545B, ptcldbl01); // ^

        RFU_ReplaceFloat(0x006F4FC3, ptcldbl03); // MH Rocket
        RFU_ReplaceFloat(0x006F4FC9, ptcldbl04);
        RFU_ReplaceFloat(0x006F500C, ptcldbl03); // ^
        RFU_ReplaceFloat(0x006F5012, ptcldbl04);
        RFU_ReplaceFloat(0x006F50C9, ptcldbl03); // ^
        RFU_ReplaceFloat(0x006F50CF, ptcldbl04);

        WriteData(0x006CF22E, 0x9090, uint16_t);// RocketMissile
        RFU_ReplaceFloat(0x006CF228, ptcldbl05); // ^
        RFU_ReplaceFloat(0x006CF230, ptcldbl01); // ^
        WriteData(0x006CEEF2, 0x9090, uint16_t);// ^
        RFU_ReplaceFloat(0x006CEEE8, ptcldbl05); // ^
        RFU_ReplaceFloat(0x006CEEF4, ptcldbl01); // ^

        RFU_ReplaceFloat(0x004B1290, ptcldbl00); // StartRocketRocket (Final Rush)
        RFU_ReplaceFloat(0x004B1296, ptcldbl01);

        WriteNOP(0x00492506, 0x0049250C); // ptcl * 0.5

        /** PtclPolygon **/
        double ptclpolyscl = CNF_GetFloat(CNF_MISC_PTCLPOLYSCL);

        RFU_ReplaceFloat(0x007801A6, ptclpolyscl);
        WriteJump(GX_SetPointSize_p, __SetPointSize);
    }

    RFG_ModelTintInit();

    RFG_EnvMapFlip();

    RFG_TaskDisplayInit();

    RFG_3DSpriteInit();

    if (true) // Aspect test
    {
        const f64 new_asp_test = (4.0/3.0);

        RFU_ReplaceFloat(0x00794778, new_asp_test); // ActionWindow button sprite
        RFU_ReplaceFloat(0x0079499D, new_asp_test); // ^

        /** Stage map completely breaks **/
        /*
        ReplaceFloat(0x00677B04, &new_asp_test); // Stage Map init
        ReplaceFloat(0x00675E09, &new_asp_test); // Stage Map
        */
    }
}
