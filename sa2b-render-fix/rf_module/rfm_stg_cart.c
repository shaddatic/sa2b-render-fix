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

/****** Game ************************************************************************************/
#include <samt/sonic/game.h>        /* stagenumber                                              */
#include <samt/sonic/light.h>       /* loadlightfile                                            */

/****** Carts ***********************************************************************************/
#include <samt/sonic/cart/cartcar.h> /* cart info                                               */

/****** Render Fix ******************************************************************************/
#include <rf_core.h>                /* core                                                     */
#include <rf_util.h>                /* replace model                                            */
#include <rf_samdl.h>               /* get chunk                                                */

/****** Config **********************************************************************************/
#include <cnf.h>                    /* config get                                               */

/****** RF Utility ******************************************************************************/
#include <rfu_float.h>              /* replacefloat                                             */

/********************************/
/*  Game Defs                   */
/********************************/
/****** Function Ptrs **************************************************************************/
#define CartSeaDisplay              FUNC_PTR(void, __cdecl, (void), 0x00621C90)

/********************************/
/*  Enums                       */
/********************************/
/****** Cart Number/Type ************************************************************************/
enum
{
    CART_SONIC,
    CART_KNUCKLES,
    CART_TAILS,
    CART_EGGMAN,
    CART_SHADOW,
    CART_ROUGE,

    NB_CART,
};

enum
{
    TYPE_NORMAL,
    TYPE_FAR,
    TYPE_SPECIAL,

    NB_TYPE,
};

/********************************/
/*  Data                        */
/********************************/
/****** Cart Objects ***************************************************************************/
static NJS_CNK_OBJECT* ObjCarts[NB_CART][NB_TYPE];

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
    if ( CNF_GetInt(CNF_CART_KANBAN) )
    {
        WriteData(0x006224EC, -1063 + 28, s32);
    }

    switch ( CNF_GetInt(CNF_CART_CARTSPRITE) )
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

    if ( CNF_GetInt(CNF_CART_ZANKI) )
    {
        /** Okay, but how does a mistake like this occur? **/
        const f64 zanki_py = 424.0 + 3.0 + 7.0;

        RFU_ReplaceFloat(0x0044E78F, zanki_py);
    }

    ObjCarts[CART_SONIC][TYPE_NORMAL]  = RF_GetCnkObject("cart/cart_sonic.sa2mdl");
    ObjCarts[CART_SONIC][TYPE_FAR]     = RF_GetCnkObject("cart/cart_sonic_far.sa2mdl");
    ObjCarts[CART_SONIC][TYPE_SPECIAL] = RF_GetCnkObject("cart/cart_sonic_special.sa2mdl");

    ObjCarts[CART_TAILS][TYPE_NORMAL]  = RF_GetCnkObject("cart/cart_tails.sa2mdl");
    ObjCarts[CART_TAILS][TYPE_FAR]     = RF_GetCnkObject("cart/cart_tails_far.sa2mdl");
    ObjCarts[CART_TAILS][TYPE_SPECIAL] = RF_GetCnkObject("cart/cart_chao.sa2mdl");

    ObjCarts[CART_KNUCKLES][TYPE_NORMAL]  = RF_GetCnkObject("cart/cart_knuckles.sa2mdl");
    ObjCarts[CART_KNUCKLES][TYPE_FAR]     = RF_GetCnkObject("cart/cart_knuckles_far.sa2mdl");
    ObjCarts[CART_KNUCKLES][TYPE_SPECIAL] = RF_GetCnkObject("cart/cart_knuckles_special.sa2mdl");

    ObjCarts[CART_SHADOW][TYPE_NORMAL]  = RF_GetCnkObject("cart/cart_shadow.sa2mdl");
    ObjCarts[CART_SHADOW][TYPE_FAR]     = RF_GetCnkObject("cart/cart_shadow_far.sa2mdl");
    ObjCarts[CART_SHADOW][TYPE_SPECIAL] = RF_GetCnkObject("cart/cart_shadow_special.sa2mdl");

    ObjCarts[CART_EGGMAN][TYPE_NORMAL]  = RF_GetCnkObject("cart/cart_eggman.sa2mdl");
    ObjCarts[CART_EGGMAN][TYPE_FAR]     = RF_GetCnkObject("cart/cart_eggman_far.sa2mdl");
    ObjCarts[CART_EGGMAN][TYPE_SPECIAL] = RF_GetCnkObject("cart/cart_eggman_special.sa2mdl");

    ObjCarts[CART_ROUGE][TYPE_NORMAL]  = RF_GetCnkObject("cart/cart_rouge.sa2mdl");
    ObjCarts[CART_ROUGE][TYPE_FAR]     = RF_GetCnkObject("cart/cart_rouge_far.sa2mdl");
    ObjCarts[CART_ROUGE][TYPE_SPECIAL] = nullptr; // eggrobo matches DC anyway

    {
        CAR_INFO(*player00)[2][6] = datadll_player00;

        *(*player00)[0][0].obj = *ObjCarts[CART_SONIC][TYPE_NORMAL];
        *(*player00)[1][0].obj = *ObjCarts[CART_SONIC][TYPE_SPECIAL];

        *(*player00)[0][1].obj = *ObjCarts[CART_TAILS][TYPE_NORMAL];
        *(*player00)[1][1].obj = *ObjCarts[CART_TAILS][TYPE_SPECIAL];

        *(*player00)[0][2].obj = *ObjCarts[CART_KNUCKLES][TYPE_NORMAL];
        *(*player00)[1][2].obj = *ObjCarts[CART_KNUCKLES][TYPE_SPECIAL];

        *(*player00)[0][3].obj = *ObjCarts[CART_SHADOW][TYPE_NORMAL];
        *(*player00)[1][3].obj = *ObjCarts[CART_SHADOW][TYPE_SPECIAL];

        *(*player00)[0][4].obj = *ObjCarts[CART_EGGMAN][TYPE_NORMAL];
        *(*player00)[1][4].obj = *ObjCarts[CART_EGGMAN][TYPE_SPECIAL];

        *(*player00)[0][5].obj = *ObjCarts[CART_ROUGE][TYPE_NORMAL];
    }

    {
        CAR_MODEL_INFO(*p_obj)[9] = (void*) datadll_specialInfo;

        *(*p_obj)[2].carFarObj = *ObjCarts[CART_SONIC][TYPE_FAR];
        *(*p_obj)[3].carFarObj = *ObjCarts[CART_KNUCKLES][TYPE_FAR];
        *(*p_obj)[4].carFarObj = *ObjCarts[CART_TAILS][TYPE_FAR];
        *(*p_obj)[5].carFarObj = *ObjCarts[CART_EGGMAN][TYPE_FAR];
        *(*p_obj)[6].carFarObj = *ObjCarts[CART_SHADOW][TYPE_FAR];
        *(*p_obj)[7].carFarObj = *ObjCarts[CART_ROUGE][TYPE_FAR];
    }

    // this overlaps with `player00` data, so just leave it
    #if 0
    {
        NJS_CNK_OBJECT** p_obj = (void*) datadll_exModels;
    }
    #endif

    // load cart light files
    WriteNOP( 0x0061A4F9, 0x0061A53D);
    WriteCall(0x0061A4F9, LoadCartLightFiles);
}
