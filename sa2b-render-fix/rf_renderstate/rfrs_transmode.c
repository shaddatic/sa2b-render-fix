/************************/
/*  Includes            */
/************************/
/****** Core Toolkit ****************************************************************/
#include <sa2b/core.h>      /* core                                                 */

/****** Render Fix ******************************************************************/
#include <rf_core.h>        /* core                                                 */
#include <rf_magic.h>       /* magic                                                */

/****** Self ************************************************************************/
#include <rf_renderstate/rfrs_internal.h> /* parent & siblings                      */

/************************/
/*  Game Enums          */
/************************/
/****** Transparancy Mode ***********************************************************/
typedef enum
{
    GJE_ALPHAMD_OPAQUE,
    GJE_ALPHAMD_ALPHATEST,
    GJE_ALPHAMD_TRANSPARENT,

    GJE_ALPHAMD_RESET
}
GJE_ALPHAMD;

/************************/
/*  Game Data           */
/************************/
/****** Transparancy Mode ***********************************************************/
#define _gj_alpha_mode_     DATA_REF(GJE_ALPHAMD, 0x025EFE50)
#define _gj_lock_alphamd_   DATA_REF(bool       , 0x01A55831)

/************************/
/*  Source              */
/************************/
/****** Extern **********************************************************************/
void
SetTransModeOpaque(void)
{
    if (_gj_lock_alphamd_)
        return;

    if (_gj_alpha_mode_ != GJE_ALPHAMD_OPAQUE)
    {
        RF_MagicSetAlphaTestEnable(false); // this isn't done in vanilla, this certainly slowed the game down some

        RF_MagicSetZEnable(true);
        RF_MagicSetZFunc(MAGIC_CMP_LESS);
        RF_MagicSetZWrite(true);

        _gj_alpha_mode_ = GJE_ALPHAMD_OPAQUE;
    }
}

void
SetTransModeAlphaTest(const RFRS_CMPMD func, const int32_t ref)
{
    if (_gj_lock_alphamd_)
        return;

    if (_gj_alpha_mode_ != GJE_ALPHAMD_ALPHATEST)
    {
        RF_MagicSetAlphaTestEnable(true);
        RF_MagicSetAlphaTestFunc(func);
        RF_MagicSetAlphaRef(ref);

        RF_MagicSetZEnable(true);
        RF_MagicSetZFunc(MAGIC_CMP_LESS);
        RF_MagicSetZWrite(true);

        _gj_alpha_mode_ = GJE_ALPHAMD_ALPHATEST;
    }
}

void
SetTransModeTransparent(void)
{
    if (_gj_lock_alphamd_)
        return;

    if (_gj_alpha_mode_ != GJE_ALPHAMD_TRANSPARENT)
    {
        RF_MagicSetAlphaTestEnable(false);

        RF_MagicSetZEnable(true);
        RF_MagicSetZFunc(MAGIC_CMP_LESS);
        RF_MagicSetZWrite(false);

        _gj_alpha_mode_ = GJE_ALPHAMD_TRANSPARENT;
    }
}
