/********************************/
/*  Includes                    */
/********************************/
/****** Core Toolkit ****************************************************************************/
#include <samt/core.h>              /* core                                                     */
#include <samt/writeop.h>           /* writejump                                                */
#include <samt/writemem.h>          /* writedata                                                */

#define SAMT_INCL_INTERNAL

/****** Ninja ***********************************************************************************/
#include <samt/ninja/ninja.h>       /* ninja                                                    */

#undef SAMT_INCL_INTERNAL

/****** Gx **************************************************************************************/
#include <samt/gx/gx.h>             /* gx                                                       */

/****** Render Fix ******************************************************************************/
#include <rf_core.h>                /* core                                                     */
#include <rf_renderstate.h>         /* alpha test and punchthrough settings                     */
#include <rf_magic.h>               /* render state                                             */

/****** Self ************************************************************************************/
#include <rf_draw/rfd_internal.h>               /* parent & siblings                            */
#include <rf_draw/rfd_cnkmdl/rfdcnk_internal.h> /* self                                         */

/********************************/
/*  Game Defs                   */
/********************************/
/****** Transparancy Mode ***********************************************************************/
typedef enum
{
    GJE_ALPHAMD_RESET = -1,

    GJE_ALPHAMD_OPAQUE,
    GJE_ALPHAMD_ALPHATEST,
    GJE_ALPHAMD_TRANSPARENT,
    GJE_ALPHAMD_PUNCHTHROUGH,
}
GJE_ALPHAMD;

/****** Transparancy Mode ***********************************************************************/
#define _gj_alpha_mode_     DATA_REF(GJE_ALPHAMD, 0x025EFE50)
#define _gj_lock_alphamd_   DATA_REF(bool       , 0x01A55831)

/****** External Functions **********************************************************************/
#define SetOpaqueDraw               FUNC_PTR(void, __cdecl, (void), 0x0042C030)
#define SetAlphaTestDraw            FUNC_PTR(void, __cdecl, (void), 0x0042C0A0)
#define SetTransparentDraw          FUNC_PTR(void, __cdecl, (void), 0x0042C170)

/********************************/
/*  Source                      */
/********************************/
/****** Direct Set ******************************************************************************/
static void
___SetAlphaMode_Opaque(void)
{
    if ( _gj_lock_alphamd_ )
    {
        return;
    }

    if ( _gj_alpha_mode_ != GJE_ALPHAMD_OPAQUE )
    {
        RF_MagicSetAlphaTestEnable(false); // this isn't done in vanilla, this certainly slowed the game down some

        RF_MagicSetZEnable(true);
        RF_MagicSetZFunc(MAGIC_CMP_LESSEQUAL);
        RF_MagicSetZWrite(true);

        _gj_alpha_mode_ = GJE_ALPHAMD_OPAQUE;
    }
}

static void
___SetAlphaMode_Transparent(void)
{
    if (_gj_lock_alphamd_)
    {
        return;
    }

    if ( _gj_alpha_mode_ != GJE_ALPHAMD_TRANSPARENT )
    {
        RF_MagicSetAlphaTestEnable(false);

        RF_MagicSetZEnable(true);
        RF_MagicSetZFunc(MAGIC_CMP_LESSEQUAL);
        RF_MagicSetZWrite(false);

        _gj_alpha_mode_ = GJE_ALPHAMD_TRANSPARENT;
    }
}

static void
___SetAlphaMode_Alphatest(void)
{
    if (_gj_lock_alphamd_)
    {
        return;
    }

    if ( _gj_alpha_mode_ != GJE_ALPHAMD_ALPHATEST )
    {
        const RFRS_CMPMD func = RFRS_GetAlphaTestFunc();
        const Sint32     ref  = RFRS_GetAlphaTestRef();

        RF_MagicSetAlphaTestEnable(true);
        RF_MagicSetAlphaTestFunc(func);
        RF_MagicSetAlphaRef(ref);

        RF_MagicSetZEnable(true);
        RF_MagicSetZFunc(MAGIC_CMP_LESSEQUAL);
        RF_MagicSetZWrite(true);

        _gj_alpha_mode_ = GJE_ALPHAMD_ALPHATEST;
    }
}

static void
___SetAlphaMode_Punchthrough(void)
{
    if (_gj_lock_alphamd_)
    {
        return;
    }

    if ( _gj_alpha_mode_ != GJE_ALPHAMD_PUNCHTHROUGH )
    {
        const RFRS_CMPMD func = RFRS_CMPMD_GTR;
        const Sint32     ref  = 64;

        RF_MagicSetAlphaTestEnable(true);
        RF_MagicSetAlphaTestFunc(func);
        RF_MagicSetAlphaRef(ref);

        RF_MagicSetZEnable(true);
        RF_MagicSetZFunc(MAGIC_CMP_LESSEQUAL);
        RF_MagicSetZWrite(true);

        _gj_alpha_mode_ = GJE_ALPHAMD_PUNCHTHROUGH;
    }
}

/****** Set Blend *******************************************************************************/
static void
rjSetAlphaMode_Opaque(void)
{
    switch ( RFRS_GetTransMode() )
    {
        case RFRS_TRANSMD_AUTO:
        case RFRS_TRANSMD_OPAQUE:
        case RFRS_TRANSMD_AUTO_ATEST:
        case RFRS_TRANSMD_AUTO_TRANS:
        {
            ___SetAlphaMode_Opaque();
            break;
        }
        case RFRS_TRANSMD_ALPHATEST:
        {
            ___SetAlphaMode_Alphatest();
            break;
        }
        case RFRS_TRANSMD_TRANSPARENT:
        {
            ___SetAlphaMode_Transparent();
            break;
        }
    }
}

static void
rjSetAlphaMode_Transparent(void)
{
    switch ( RFRS_GetTransMode() )
    {
        case RFRS_TRANSMD_OPAQUE:
        {
            ___SetAlphaMode_Opaque();
            break;
        }
        case RFRS_TRANSMD_ALPHATEST:
        case RFRS_TRANSMD_AUTO_ATEST:
        {
            ___SetAlphaMode_Alphatest();
            break;
        }
        case RFRS_TRANSMD_AUTO:
        case RFRS_TRANSMD_TRANSPARENT:
        case RFRS_TRANSMD_AUTO_TRANS:
        {
            ___SetAlphaMode_Transparent();
            break;
        }
    }
}

static void
rjSetAlphaMode_Alphatest(void)
{
    switch ( RFRS_GetTransMode() )
    {
        case RFRS_TRANSMD_OPAQUE:
        {
            ___SetAlphaMode_Opaque();
            break;
        }
        case RFRS_TRANSMD_AUTO:
        case RFRS_TRANSMD_ALPHATEST:
        case RFRS_TRANSMD_AUTO_ATEST:
        {
            ___SetAlphaMode_Alphatest();
            break;
        }
        case RFRS_TRANSMD_TRANSPARENT:
        case RFRS_TRANSMD_AUTO_TRANS:
        {
            ___SetAlphaMode_Transparent();
            break;
        }
    }
}

static void
rjSetAlphaMode_Punchthrough(void)
{
    switch ( RFRS_GetTransMode() )
    {
        case RFRS_TRANSMD_OPAQUE:
        {
            ___SetAlphaMode_Opaque();
            break;
        }
        case RFRS_TRANSMD_ALPHATEST:
        case RFRS_TRANSMD_AUTO_ATEST:
        {
            ___SetAlphaMode_Alphatest();
            break;
        }
        case RFRS_TRANSMD_TRANSPARENT:
        case RFRS_TRANSMD_AUTO_TRANS:
        {
            ___SetAlphaMode_Transparent();
            break;
        }
        case RFRS_TRANSMD_AUTO:
        {
            ___SetAlphaMode_Punchthrough();
        }
    }
}

/****** Extern **********************************************************************************/
void
rjSetAlphaMode(Sint32 src, Sint32 dst, RJE_ALPHA mode)
{
    Bool trans;

    switch (mode)
    {
        case RJE_ALPHA_OPAQUE: default:
        {
            trans = FALSE;

            rjSetAlphaMode_Opaque();
            break;
        }
        case RJE_ALPHA_TRANS:
        {
            trans = TRUE;

            rjSetAlphaMode_Transparent();
            break;
        }
        case RJE_ALPHA_ALPHATEST:
        {
            trans = TRUE;

            rjSetAlphaMode_Alphatest();
            break;
        }
        case RJE_ALPHA_PUNCHTHROUGH:
        {
            trans = FALSE;

            rjSetAlphaMode_Punchthrough();
            break;
        }
    }

    GX_SetBlendMode(src, dst, trans);
}

/****** Init ************************************************************************************/
void
RFD_AlphaBlendInit(void)
{
    /** Transparancy draw set **/
    WriteJump(SetOpaqueDraw     , rjSetAlphaMode_Opaque);
    WriteJump(SetAlphaTestDraw  , rjSetAlphaMode_Alphatest);
    WriteJump(SetTransparentDraw, rjSetAlphaMode_Transparent);

    /** Fix direct calls to Magic draw set **/
    WriteNOP( 0x005FF290, 0x005FF2E2);
    WriteData(0x005FF290, 0x56, u8); // push esi
    WriteData(0x005FF291, 0x57, u8); // push edi
    WriteCall(0x005FF292, rjSetAlphaMode_Transparent);

    WriteNOP( 0x00600569, 0x006005B3);
    WriteData(0x00600569, 0x83, u8);  // add esp, 8
    WriteData(0x0060056A, 0xC4, u8);  // ^^^
    WriteData(0x0060056B, 0x08, u8);  // ^^^
    WriteCall(0x0060056C, rjSetAlphaMode_Transparent);
}
