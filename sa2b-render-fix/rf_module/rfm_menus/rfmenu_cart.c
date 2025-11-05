/********************************/
/*  Includes                    */
/********************************/
/****** Core Toolkit ****************************************************************************/
#include <samt/core.h>              /* core                                                     */
#include <samt/writeop.h>           /* writejump                                                */

/****** Game ************************************************************************************/
#include <samt/sonic/njctrl.h>      /* nj control utils                                         */
#include <samt/sonic/light.h>       /* lights                                                   */
#include <samt/sonic/score.h>       /* timer                                                    */

/****** Carts ***********************************************************************************/
#include <samt/sonic/cart/cartcar.h> /* cart data                                               */

/****** Render Fix ******************************************************************************/
#include <rf_core.h>                /* core                                                     */
#include <rf_ninja.h>               /* rf ninja                                                 */
#include <rf_light.h>               /* cnk light                                                */
#include <rf_util.h>                /* switch displayer                                         */

/****** Self ************************************************************************************/
#include <rf_module/rfm_menus/rfmenu_internal.h> /* parent & siblings                           */

/********************************/
/*  Game Defs                   */
/********************************/
/****** Carts ***********************************************************************************/
#define CartIs2P                    DATA_REF(u8 , 0x01D1B865)
#define CartPlayer1P                DATA_REF(u8 , 0x01D1B814)
#define CartPlayer2P                DATA_REF(u8 , 0x01D1B81B)
#define CartSpecial1P               DATA_REF(u8 , 0x01D1B819)
#define CartSpecial2P               DATA_REF(u8 , 0x01D1B820)

#define CartModelFade               DATA_REF(f32, 0x01A50218)

#define CartModelLight              DATA_ARY(LIGHT, 0x0C70D14, [1])

typedef CAR_INFO(PLAYER00_DEF)[2][6];

/********************************/
/*  Data                        */
/********************************/
/****** Carts ***********************************************************************************/
static PLAYER00_DEF*   player00;
static NJS_TEXLIST*    texlist_kartrace;
static NJS_TEXLIST*    texlist_kartexmodel;
static NJS_TEXLIST*    texlist_cartdata;
static NJS_CNK_OBJECT* object_kartrace_kartlight;

/********************************/
/*  Source                      */
/********************************/
/****** Core Toolkit ****************************************************************************/
static void
DrawCartModel(int index, int player, int special)
{
    SaveConstantAttr();
    SaveControl3D();

    OnControl3D(NJD_CONTROL_3D_CNK_CONSTANT_ATTR);

    if ( CartModelFade < 1.0f )
    {
        const f32 fade = 0.f - (1.f - CartModelFade);
    
        njSetConstantAttr(~NJD_FST_IS, NJD_FST_UA|RJD_FST_EUA);
        SetConstantMaterial(fade, fade, fade, fade);
    }
    else
    {
        njSetConstantAttr(~NJD_FST_IS, 0);
    }

    Float xpos = 0.f;

    if ( index != 0 )
    {
        xpos = (index == 1) ? -19.f : +19.f;
    }

    SetLightSwitchGC(0, OFF); // disable GC light

    SetLightStruct(0, CartModelLight);
    SetLight(0);

    njPushMatrixEx();
    {
        njTranslate( NULL, xpos, -3.f, 0.f            );
        njRotateY(   NULL, NJM_DEG_ANG(GetGameTime()) );

        njSetTexture( texlist_kartrace );
        njCnkSimpleDrawObject( object_kartrace_kartlight );

        njSetTexture( special ? texlist_kartexmodel : texlist_cartdata );

        rjCnkSetControl( ~RJD_CNK_CTRL_MASK_DRAW, RJD_CNK_CTRL_OPAQUE );

        njCnkSimpleDrawObject( (*player00)[special][player].obj );

        rjCnkSetControl( ~RJD_CNK_CTRL_MASK_DRAW, RJD_CNK_CTRL_TRANSLUCENT );

        njCnkSimpleDrawObject( (*player00)[special][player].obj );

        rjCnkSetControl( ~0, RJD_CNK_CTRL_MASK_DRAW );
    }
    njPopMatrixEx();

    ResetConstantMaterial();

    LoadControl3D();
    LoadConstantAttr();
}

static void
DrawCartsForMenu(void)
{
    NJS_CAMERA cam;

    njInitCamera(&cam);

    cam.py = +20.f;
    cam.pz = +70.f;
    cam.vy = -20.f;
    cam.vz = -70.f;

    njSetCamera(&cam);

    if ( CartIs2P )
    {
        DrawCartModel(1, CartPlayer1P, CartSpecial1P);
        DrawCartModel(2, CartPlayer2P, CartSpecial2P);
    }
    else
    {
        DrawCartModel(0, CartPlayer1P, CartSpecial1P);
    }
}

/****** Init ************************************************************************************/
void
RFM_MenuCartInit(void)
{
    player00                  = datadll_player00;
    texlist_kartrace          = GetDataDllAddr(NJS_TEXLIST   , "texlist_kartRace");
    texlist_kartexmodel       = GetDataDllAddr(NJS_TEXLIST   , "texlist_kartExModel_kartRace");
    texlist_cartdata          = GetDataDllAddr(NJS_TEXLIST   , "texlist_cartData_kartRace");
    object_kartrace_kartlight = GetDataDllAddr(NJS_CNK_OBJECT, "object_kartrace_kartlight_kartlight");

    CartModelLight[0] = (LIGHT)
    {
        .x = 0.f,
        .y = 0.f,
        .z = -1.f,

        .inten   = 1.0f,
        .ambient = 0.6f,

        .r = 1.f,
        .g = 1.f,
        .b = 1.f,
    };

    WriteJump(0x0068B8B0, DrawCartsForMenu);
}
