/********************************/
/*  Includes                    */
/********************************/
/****** SAMT ************************************************************************************/
#include <samt/core.h>              /* core                                                     */
#include <samt/writemem.h>          /* writedata                                                */
#include <samt/writeop.h>           /* writejump                                                */
#include <samt/funchook.h>          /* funchook                                                 */
#include <samt/modinfo.h>           /* mod info                                                 */
#include <samt/string.h>            /* string match                                             */

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
#include <rf_module/rfm_game/rfg_internal.h> /* children                                        */

/********************************/
/*  Game Defs                   */
/********************************/
/****** Battle **********************************************************************************/
#define BattleFlag                  DATA_REF(i32, 0x01A556F4)
#define BattleFlag2                 DATA_REF(i32, 0x01A556F8)

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

/****** Init ************************************************************************************/
void
RFM_GlobalInit(void)
{
    RFG_UiFilterInit();
    RFG_DrawFunctionInit();

    if ( CNF_GetInt(CNF_GAME_NOBTL) )
    {
        BattleFlag = FALSE;

        // set things we want to keep enabled to the second battle flag
        WritePointer(0x0044476E +2, &BattleFlag2); // all emblems ach,      cmp val
        WritePointer(0x0044504E +2, &BattleFlag2); // other achieves,       cmp val
        WritePointer(0x00445217 +2, &BattleFlag2); // menu theme set,       cmp val
        WritePointer(0x004568C2 +2, &BattleFlag2); // something steam,      cmp reg
//      WritePointer(0x00458A09 +2, &BattleFlag2); // game intro,           cmp val
        WritePointer(0x00542963 +2, &BattleFlag2); // karate something,     cmp reg
        WritePointer(0x00581891 +2, &BattleFlag2); // chao cave menu,       mov reg
        WritePointer(0x0058A047 +2, &BattleFlag2); // bmarket themes,       cmp val
        WritePointer(0x0058B8F8 +2, &BattleFlag2); // bmarket themes 2,     cmp val
        WritePointer(0x005A882E +2, &BattleFlag2); // chao cave arrows,     cmp reg
        WritePointer(0x005A894D +2, &BattleFlag2); // chao cave arrows,     cmp reg
//      WritePointer(0x00667A6E +2, &BattleFlag2); // screen effect tex,    cmp reg
//      WritePointer(0x00667F0B +2, &BattleFlag2); // screen effect,        mov reg
//      WritePointer(0x006682D2 +2, &BattleFlag2); // screen effect txt,    cmp reg
        WritePointer(0x0066A039 +1, &BattleFlag2); // 2p costumes,          mov eax
        WritePointer(0x0066A69D +2, &BattleFlag2); // btl player select,    cmp reg
        WritePointer(0x0066B191 +2, &BattleFlag2); // btl stg select,       mov reg
        WritePointer(0x0066B344 +2, &BattleFlag2); // btl something,        cmp val
        WritePointer(0x0066B420 +2, &BattleFlag2); // btl something,        cmp val
        WritePointer(0x0066B98A +2, &BattleFlag2); // btl next stage?,      cmp val
        WritePointer(0x0066B9C6 +2, &BattleFlag2); // btl next stage?,      cmp val
        WritePointer(0x0066BA78 +2, &BattleFlag2); // btl next stage?,      cmp val
        WritePointer(0x0066BA87 +2, &BattleFlag2); // btl next stage?,      cmp val
        WritePointer(0x0066C960 +2, &BattleFlag2); // menu background?,     cmp reg
        WritePointer(0x0066CA80 +2, &BattleFlag2); // menu background?,     cmp reg
        WritePointer(0x0066DA03 +2, &BattleFlag2); // settings something?,  cmp reg
        WritePointer(0x0066DF02 +2, &BattleFlag2); // settings something?,  cmp reg
//      WritePointer(0x0066F8D3 +2, &BattleFlag2); // menu bg,              cmp val
//      WritePointer(0x0066FEA1 +2, &BattleFlag2); // alpha title,          cmp val
//      WritePointer(0x00670443 +2, &BattleFlag2); // alpha title tex,      cmp reg
//      WritePointer(0x0067B717 +2, &BattleFlag2); // sound test tex,       cmp val
        WritePointer(0x00687AE8 +2, &BattleFlag2); // btl something?,       cmp val
        WritePointer(0x00687E1F +2, &BattleFlag2); // btl select something?,cmp val
//      WritePointer(0x00688B04 +2, &BattleFlag2); // 2p stage sel,         cmp val
    }

    if ( CNF_GetInt(CNF_GAME_IGBIX) )
    {
        WriteJump(0x0042FAD0, njSearchTexMemList_);
    }

    RFG_BackfaceCullingInit();

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
