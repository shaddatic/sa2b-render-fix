/************************/
/*  Includes            */
/************************/
/****** Core Toolkit ****************************************************************/
#include <samt/core.h>          /* core                                             */
#include <samt/writeop.h>       /* writejump                                        */
#include <samt/funchook.h>      /* function hook                                    */

/****** Ninja ***********************************************************************/
#include <samt/ninja/ninja.h>   /* ninja                                            */

/****** Game ************************************************************************/
#include <samt/sonic/task.h>    /* task                                             */
#include <samt/sonic/player.h>  /* player                                           */
#include <samt/sonic/game.h>    /* game info                                        */
#include <samt/sonic/score.h>   /* timer info                                       */
#include <samt/sonic/njctrl.h>  /* oncontrol3d                                      */

#define SAMT_INCL_FUNCPTRS

/****** Player **********************************************************************/
#include <samt/sonic/figure/sonic.h>    /* sonic                                    */
#include <samt/sonic/figure/knuckles.h> /* knuckles work                            */

#undef SAMT_INCL_FUNCPTRS

/****** Render Fix ******************************************************************/
#include <rf_core.h>            /* core                                             */
#include <rf_njcnk.h>           /* emulated njcnk draw functions                    */
#include <rf_util.h>            /* change displayer                                 */
#include <rf_renderstate.h>     /* render state                                     */
#include <rf_feature.h>         /* render fix feature check                         */

/****** RF Utility ******************************************************************/
#include <rfu_file.h>           /* filereplace                                      */

/****** Config **********************************************************************/
#include <cnf.h>                /* config get                                       */

/****** Self ************************************************************************/
#include <rf_module/rfm_player/rfpl_internal.h> /* children                         */

/************************/
/*  Game Functions      */
/************************/
/****** Player Displayer Pointers ***************************************************/
#define SonicDisp_p             FUNC_PTR(void, __cdecl, (task*), 0x00720090)
#define KnucklesDisp_p          FUNC_PTR(void, __cdecl, (task*), 0x0072EF20)
#define RougeDisp_p             FUNC_PTR(void, __cdecl, (task*), 0x00730970)
#define MilesDisp_p             FUNC_PTR(void, __cdecl, (task*), 0x007507D0)
#define EggmanDisp_p            FUNC_PTR(void, __cdecl, (task*), 0x0073EF20)
#define TailsWalkerDisp_p       FUNC_PTR(void, __cdecl, (task*), 0x00747DD0)
#define EggWalkerDisp_p         FUNC_PTR(void, __cdecl, (task*), 0x007444F0)
#define SuperSonicDisp_p        FUNC_PTR(void, __cdecl, (task*), 0x0049CA60)
#define ChaoWalkerDisp_p        FUNC_PTR(void, __cdecl, (task*), 0x007444F0)
#define DarkChaoWalkerDisp_p    FUNC_PTR(void, __cdecl, (task*), 0x007444F0)
#define TicalDisp_p             FUNC_PTR(void, __cdecl, (task*), 0x0072FB10)
#define ChaosDisp_p             FUNC_PTR(void, __cdecl, (task*), 0x00731A30)
#define ChaosDispDely_p         FUNC_PTR(void, __cdecl, (task*), 0x00731A30)

/****** Player Displayers ***********************************************************/
#define SonicDisp               SonicDisp_p
#define KnucklesDisp            KnucklesDisp_p
#define RougeDisp               RougeDisp_p
#define MilesDisp               MilesDisp_p
#define EggmanDisp              EggmanDisp_p
#define TailsWalkerDisp         TailsWalkerDisp_p
#define EggWalkerDisp           EggWalkerDisp_p
#define SuperSonicDisp          SuperSonicDisp_p
#define ChaoWalkerDisp          ChaoWalkerDisp_p
#define DarkChaoWalkerDisp      DarkChaoWalkerDisp_p
#define TicalDisp               TicalDisp_p
#define ChaosDisp               ChaosDisp_p
#define ChaosDispDely           ChaosDispDely_p

/****** Player Object ***************************************************************/
#define CreatePlayerObjectData          FUNC_PTR(PLAYER_OBJECT*, __cdecl, (NJS_CNK_OBJECT*), 0x00447580)

/************************/
/*  Data                */
/************************/
/****** Compatibility ***************************************************************/
static bool BrokenModelFix;
static bool ConstTexMaterial;

/************************/
/*  Source              */
/************************/
/****** Static **********************************************************************/
static void
FixRougeInitCrash(NJS_CNK_OBJECT* object, KNUCKLESWK* knwp)
{
    if ( !object->model || !object->model->vlist )
        return;

    PLAYER_OBJECT* plobj = CreatePlayerObjectData(object);

    knwp->pObjectData2 = plobj;

    plobj->data0[0] = 14;
    plobj->someFlt = 0.4f;

    plobj->someInt0 = 0x3000;
    plobj->someInt2 = 0x400;

    plobj->pObj2 = object;
}

__declspec(naked)
static void
___FixRougeInitCrash(void)
{
    __asm
    {
        push        [esp+0Ch+4+4]
        push        edx
        call        FixRougeInitCrash
        add esp,    4
        pop esi
        retn
    }
}

static void
DrawMotionWithSorting(const NJS_CNK_OBJECT* object, const NJS_MOTION* motion, float frame)
{
    rjCnkSetControl( ~RJD_CNK_CTRL_MASK_DRAW, RJD_CNK_CTRL_OPAQUE );

    njCnkDrawMotion(object, motion, frame);

    rjCnkSetControl( ~RJD_CNK_CTRL_MASK_DRAW, RJD_CNK_CTRL_TRANSLUCENT );

    njCnkDrawMotion(object, motion, frame);

    rjCnkSetControl( ~0, RJD_CNK_CTRL_MASK_DRAW );
}

__declspec(naked)
static void
___DrawMotionWithSorting(void)
{
    __asm
    {
        push        [esp + 8]   // frame
        push        ecx         // motion
        push        [esp + 12]  // object
        call        DrawMotionWithSorting
        add esp,    12
        retn
    }
}

#define CreatePlayerDrawMotionWithAlphaReducing         FUNC_PTR(void, __cdecl, (NJS_CNK_OBJECT*, NJS_MOTION*, NJS_TEXLIST*, Float, Sint8), 0x00476C20)

static void
CreatePlayerDrawLightDashWithAlphaReducing(const taskwk* twp, const playerwk* pwp, const SONICWK* swp)
{
    if ( GetGameTime() & 1 )
    {
        NJS_CNK_OBJECT* object;

        switch ( pwp->ch_num )
        {
            case PLNO_SONIC:
            {
                object = CHAR_OBJECTS[30].pObject;
                break;
            }
            case PLNO_SHADOW:
            {
                object = CHAR_OBJECTS[103].pObject;
                break;
            }
            default:
            {
                return;
            }
        }

        if ( !object )
        {
            return;
        }

        njPushMatrix( &_nj_unit_matrix_ );

        njTranslateV( NULL, &twp->pos );

        njRotateZ( NULL,           twp->ang.z );
        njRotateX( NULL,           twp->ang.x );
        njRotateY( NULL,  0x8000 - twp->ang.y );

        if ( uc2PVSMode == MD_2PVS_1PLAYER )
        {
            CreatePlayerDrawMotionWithAlphaReducing(object, NULL, swp->TextureList, 0.f, pwp->pl_num);
        }

        njPopMatrixEx();
    }
}

__declspec(naked)
static void
___CreatePlayerDrawLightDashWithAlphaReducing(void)
{
    __asm
    {
        push        [esp+8]     // swp
        push        [esp+8]     // pwp
        push        esi         // twp
        call        CreatePlayerDrawLightDashWithAlphaReducing
        add esp,    12
        retn
    }
}

/****** Player Model Compat *********************************************************/
static void
ConstTexMaterialCompatStart(int pno)
{
    OffControl3D( NJD_CONTROL_3D_CONSTANT_TEXTURE_MATERIAL );
}

static void
ConstTexMaterialCompatEnd(int pno)
{
    OnControl3D( NJD_CONTROL_3D_CONSTANT_TEXTURE_MATERIAL );
}

static void
BrokenModelCompatStart(int pno)
{
    OnControl3D( NJD_CONTROL_3D_CNK_CONSTANT_ATTR );

    // double sided lighting, off
    rjCnkSetControl( ~RJD_CNK_CTRL_DBLIGHT, 0 );

    _nj_constant_attr_and_ = ~(NJD_FST_IA|NJD_FST_FL);
    _nj_constant_attr_or_  =  (NJD_FST_IS|NJD_FST_DB);
}

static void
BrokenModelCompatEnd(int pno)
{
    _nj_constant_attr_and_ =  NJD_FST_MASK;
    _nj_constant_attr_or_  = ~NJD_FST_MASK;

    // double sided lighting, restore
    rjCnkSetControl( ~0, RJD_CNK_CTRL_DBLIGHT );

    OffControl3D( NJD_CONTROL_3D_CNK_CONSTANT_ATTR );
}

static void
PlayerModelCompatStartDisplayer(int pno)
{
    if ( ConstTexMaterial )
    {
        ConstTexMaterialCompatStart(pno);
    }

    if ( BrokenModelFix )
    {
        BrokenModelCompatStart(pno);
    }
}

static void
PlayerModelCompatEndDisplayer(int pno)
{
    if ( BrokenModelFix )
    {
        BrokenModelCompatEnd(pno);
    }

    if ( ConstTexMaterial )
    {
        ConstTexMaterialCompatEnd(pno);
    }
}

static mt_hookinfo SonicDisp_CompatHookInfo[1];
static void
SonicDisp_CompatHook(task* tp)
{
    PlayerModelCompatStartDisplayer(PLNO_SONIC);

    FuncHookCall( SonicDisp_CompatHookInfo, SonicDisp(tp) );

    PlayerModelCompatEndDisplayer(PLNO_SONIC);
}

static mt_hookinfo MilesDisp_CompatHookInfo[1];
static void
MilesDisp_CompatHook(task* tp)
{
    PlayerModelCompatStartDisplayer(PLNO_MILES);

    FuncHookCall( MilesDisp_CompatHookInfo, MilesDisp(tp) );

    PlayerModelCompatEndDisplayer(PLNO_MILES);
}

static mt_hookinfo KnucklesDisp_CompatHookInfo[1];
static void
KnucklesDisp_CompatHook(task* tp)
{
    PlayerModelCompatStartDisplayer(PLNO_KNUCKLES);

    FuncHookCall( KnucklesDisp_CompatHookInfo, KnucklesDisp(tp) );

    PlayerModelCompatEndDisplayer(PLNO_KNUCKLES);
}

static mt_hookinfo EggmanDisp_CompatHookInfo[1];
static void
EggmanDisp_CompatHook(task* tp)
{
    PlayerModelCompatStartDisplayer(PLNO_EGGMAN);

    FuncHookCall( EggmanDisp_CompatHookInfo, EggmanDisp(tp) );

    PlayerModelCompatEndDisplayer(PLNO_EGGMAN);
}

static mt_hookinfo RougeDisp_CompatHookInfo[1];
static void
RougeDisp_CompatHook(task* tp)
{
    PlayerModelCompatStartDisplayer(PLNO_ROUGE);

    FuncHookCall( RougeDisp_CompatHookInfo, RougeDisp(tp) );

    PlayerModelCompatEndDisplayer(PLNO_ROUGE);
}

static mt_hookinfo EggWalkerDisp_CompatHookInfo[1];
static void
EggWalkerDisp_CompatHook(task* tp)
{
    PlayerModelCompatStartDisplayer(PLNO_EGG_WALKER);

    FuncHookCall( EggWalkerDisp_CompatHookInfo, EggWalkerDisp(tp) );

    PlayerModelCompatEndDisplayer(PLNO_EGG_WALKER);
}

static mt_hookinfo TailsWalkerDisp_CompatHookInfo[1];
static void
TailsWalkerDisp_CompatHook(task* tp)
{
    PlayerModelCompatStartDisplayer(PLNO_TAILS_WALKER);

    FuncHookCall( TailsWalkerDisp_CompatHookInfo, TailsWalkerDisp(tp) );

    PlayerModelCompatEndDisplayer(PLNO_TAILS_WALKER);
}

static mt_hookinfo SuperSonicDisp_CompatHookInfo[1];
static void
SuperSonicDisp_CompatHook(task* tp)
{
    PlayerModelCompatStartDisplayer(PLNO_SUPER_SONIC);

    FuncHookCall( SuperSonicDisp_CompatHookInfo, SuperSonicDisp(tp) );

    PlayerModelCompatEndDisplayer(PLNO_SUPER_SONIC);
}

static mt_hookinfo ChaoWalkerDisp_CompatHookInfo[1];
static void
ChaoWalkerDisp_CompatHook(task* tp)
{
    PlayerModelCompatStartDisplayer(PLNO_CHAO_WALKER);

    FuncHookCall( ChaoWalkerDisp_CompatHookInfo, ChaoWalkerDisp(tp) );

    PlayerModelCompatEndDisplayer(PLNO_CHAO_WALKER);
}

static mt_hookinfo DarkChaoWalkerDisp_CompatHookInfo[1];
static void
DarkChaoWalkerDisp_CompatHook(task* tp)
{
    PlayerModelCompatStartDisplayer(PLNO_DARK_WALKER);

    FuncHookCall( DarkChaoWalkerDisp_CompatHookInfo, DarkChaoWalkerDisp(tp) );

    PlayerModelCompatEndDisplayer(PLNO_DARK_WALKER);
}

static mt_hookinfo TicalDisp_CompatHookInfo[1];
static void
TicalDisp_CompatHook(task* tp)
{
    PlayerModelCompatStartDisplayer(PLNO_TICAL);

    FuncHookCall( TicalDisp_CompatHookInfo, TicalDisp(tp) );

    PlayerModelCompatEndDisplayer(PLNO_TICAL);
}

static mt_hookinfo ChaosDisp_CompatHookInfo[1];
static void
ChaosDisp_CompatHook(task* tp)
{
    PlayerModelCompatStartDisplayer(PLNO_CHAOS0);

    FuncHookCall( ChaosDisp_CompatHookInfo, ChaosDisp(tp) );

    PlayerModelCompatEndDisplayer(PLNO_CHAOS0);
}

static mt_hookinfo ChaosDispDely_CompatHookInfo[1];
static void
ChaosDispDely_CompatHook(task* tp)
{
    PlayerModelCompatStartDisplayer(PLNO_CHAOS0);

    FuncHookCall( ChaosDispDely_CompatHookInfo, ChaosDispDely(tp) );

    PlayerModelCompatEndDisplayer(PLNO_CHAOS0);
}

static void
PlayerModelCompatHook(void)
{
    static bool IsHooked = false;

    if ( IsHooked )
    {
        return;
    }

    FuncHook( SonicDisp_CompatHookInfo          , SonicDisp_p           , SonicDisp_CompatHook );
    FuncHook( MilesDisp_CompatHookInfo          , MilesDisp_p           , MilesDisp_CompatHook );
    FuncHook( KnucklesDisp_CompatHookInfo       , KnucklesDisp_p        , KnucklesDisp_CompatHook );
    FuncHook( EggmanDisp_CompatHookInfo         , EggmanDisp_p          , EggmanDisp_CompatHook );
    FuncHook( RougeDisp_CompatHookInfo          , RougeDisp_p           , RougeDisp_CompatHook );
    FuncHook( EggWalkerDisp_CompatHookInfo      , EggWalkerDisp_p       , EggWalkerDisp_CompatHook );
    FuncHook( TailsWalkerDisp_CompatHookInfo    , TailsWalkerDisp_p     , TailsWalkerDisp_CompatHook );
    FuncHook( SuperSonicDisp_CompatHookInfo     , SuperSonicDisp_p      , SuperSonicDisp_CompatHook );
    FuncHook( ChaoWalkerDisp_CompatHookInfo     , ChaoWalkerDisp_p      , ChaoWalkerDisp_CompatHook );
    FuncHook( DarkChaoWalkerDisp_CompatHookInfo , DarkChaoWalkerDisp_p  , DarkChaoWalkerDisp_CompatHook );
    FuncHook( TicalDisp_CompatHookInfo          , TicalDisp_p           , TicalDisp_CompatHook );
    FuncHook( ChaosDisp_CompatHookInfo          , ChaosDisp_p           , ChaosDisp_CompatHook );
    FuncHook( ChaosDispDely_CompatHookInfo      , ChaosDispDely_p       , ChaosDispDely_CompatHook );

    IsHooked = true;
}

/****** Init ************************************************************************/
void
RFM_PlayerInit(void)
{
    RFPL_ModelPrsInit();
    RFPL_Chaos0Init();

    if ( CNF_GetInt( CNF_COMPAT_PLBROKENFIX ) )
    {
        PlayerModelCompatHook();

        BrokenModelFix = true;
    }

    if ( CNF_GetInt( CNF_COMPAT_PLTEXMAT ) )
    {
        PlayerModelCompatHook();

        ConstTexMaterial = true;
    }

    /** This fixes a crash in 'SetRouge' caused by her DC model having no vlist data
        on one of her body object nodes, seemingly just adjusting some weights on
        her back (?) that was added for Battle. They never check for 'NULL', so
        this just checks for that case. **/
    WriteCall(0x007286B6, ___FixRougeInitCrash);
    WriteNOP(0x007286BB, 0x007286F8);
    WriteNOP(0x007286FB, 0x007286FE);

    /** Player Displayer **/
    SwitchDisplayer(0x00741077, DISP_SORT); // tails walker
    SwitchDisplayer(0x00741265, DISP_SORT); // chao walker
    SwitchDisplayer(0x00740E17, DISP_SORT); // egg walker

    //SwitchDisplayer(0x00741445, DISP_SORT); // dark walker

    /** Player Draw **/
    WriteCall(0x0074810F, ___DrawMotionWithSorting); // tails walker
    WriteCall(0x007465B1, ___DrawMotionWithSorting); // chao walker 1
    WriteCall(0x0074662A, ___DrawMotionWithSorting); // chao walker 2
    WriteCall(0x0074662A, ___DrawMotionWithSorting); // chao walker 3
    WriteCall(0x00744842, ___DrawMotionWithSorting); // egg walker 1
    WriteCall(0x007448BB, ___DrawMotionWithSorting); // egg walker 2

    if ( CNF_GetInt( CNF_PLAYER_MODEL ) == CNFE_PLAYER_MODEL_DREAMCAST )
    {
        RFU_ReplacePlayerPrs("SONICMDL" , "plmdl_dc");
        RFU_ReplacePlayerPrs("TERIOSMDL", "plmdl_dc");
        RFU_ReplacePlayerPrs("MILESMDL" , "plmdl_dc");
        RFU_ReplacePlayerPrs("EGGMDL"   , "plmdl_dc");
        RFU_ReplacePlayerPrs("KNUCKMDL" , "plmdl_dc");

        if ( RFU_ReplacePlayerPrs("ROUGEMDL", "plmdl_dc") )
        {
            RFU_ReplacePlayerPrs("ROUGEMTN", "plmdl_dc");
        }

        RFU_ReplacePlayerPrs("TWALKMDL" , "plmdl_dc");
        RFU_ReplacePlayerPrs("EWALKMDL" , "plmdl_dc");
        RFU_ReplacePlayerPrs("AMYMDL"   , "plmdl_dc");
        RFU_ReplacePlayerPrs("SSONICMDL", "plmdl_dc");

        if ( RFU_ReplacePlayerPrs("SSHADOWMDL", "plmdl_dc") )
        {
            RFU_ReplaceTexture("SSHADOWTEX", "plmdl_dc");
        }

        RFU_ReplacePlayerPrs("METALSONICMDL", "plmdl_dc");
        RFU_ReplacePlayerPrs("CWALKMDL"     , "plmdl_dc");
        RFU_ReplacePlayerPrs("TICALMDL"     , "plmdl_dc");

        if ( RFU_ReplacePlayerPrs("CHAOS0MDL", "plmdl_dc") )
        {
            if ( !RFF_Chaos0TexAnim() )
            {
                RFU_ReplaceTexture("CHAOS0TEX", "plmdl_dc");
            }
        }
    }

    if ( CNF_GetInt( CNF_PLAYER_MDLSHADOW ) == CNFE_BOOL_DISABLED )
    {
        // disable player shadowing
        WriteData(0x00720131+6, 0x00, u32); // Sonic/shadow/amy/mtlsonic
        WriteData(0x00744567+6, 0x00, u32); // Egg Walker
        WriteData(0x00747138+6, 0x00, u32); // Dark Chao Walker
        WriteData(0x00747E38+6, 0x00, u32); // Tails Walker
        WriteData(0x007462F8+6, 0x00, u32); // Chao Walker
        WriteData(0x0072F011+6, 0x00, u32); // Knuckles
        WriteData(0x00730A64+6, 0x00, u32); // Rouge
        WriteData(0x0072FC01+6, 0x00, u32); // Tical
        WriteData(0x00731B21+6, 0x00, u32); // Chaos
        WriteData(0x00750819+6, 0x00, u32); // Miles
        WriteData(0x0073EF67+6, 0x00, u32); // Eggman
    }

    if ( CNF_GetInt( CNF_PLAYER_SHADLITEDASH ) )
    {
        WriteJump(0x0071E460, ___CreatePlayerDrawLightDashWithAlphaReducing);
    }

    switch ( CNF_GetInt( CNF_PLAYER_LODMDL ) ) // Player LOD Models
    {
        case CNFE_PLAYER_LOD_ENABLED:
        {
            break;
        }
        case CNFE_PLAYER_LOD_DISABLED:
        {
            WriteNOP(0x00720603, 0x0072060A);
            WriteShortJump(0x0072060A, 0x0072060E);

//          [[fallthrough]];
        }
        case CNFE_PLAYER_LOD_2PONLY:
        {
            WriteNOP(0x0072055A, 0x00720561);
            WriteShortJump(0x0072056D, 0x0072058A);
            break;
        }
    }
}
