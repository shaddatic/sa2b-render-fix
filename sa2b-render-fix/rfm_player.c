/************************/
/*  Includes            */
/************************/
/****** Core Toolkit ****************************************************************/
#include <samt/core.h>          /* core                                             */
#include <samt/writeop.h>       /* writejump                                        */

/****** Ninja ***********************************************************************/
#include <samt/ninja/ninja.h>   /* ninja                                            */

/****** Game ************************************************************************/
#include <samt/sonic/task.h>    /* task                                             */
#include <samt/sonic/player.h>  /* player                                           */
#include <samt/sonic/game.h>    /* game info                                        */
#include <samt/sonic/score.h>   /* timer info                                       */

/****** Player **********************************************************************/
#include <samt/sonic/figure/sonic.h> /* sonic                                       */

/****** Character *******************************************************************/
#include <samt/sonic/figure/knuckles.h> /* knuckles work                            */

/****** Render Fix ******************************************************************/
#include <rf_core.h>            /* core                                             */
#include <rf_config.h>          /* config                                           */
#include <rf_njcnk.h>           /* emulated njcnk draw functions                    */
#include <rf_util.h>            /* change displayer                                 */
#include <rf_renderstate.h>     /* render state                                     */
#include <rf_feature.h>         /* render fix feature check                         */

/****** RF Utility ******************************************************************/
#include <rfu_file.h>           /* filereplace                                      */

/****** Self ************************************************************************/
#include <rfm_player.h>               /* self                                       */
#include <rfm_player/rfpl_internal.h> /* children                                   */

/************************/
/*  Game Functions      */
/************************/
/****** Player Object ***************************************************************/
#define CreatePlayerObjectData          FUNC_PTR(PLAYER_OBJECT*, __cdecl, (NJS_CNK_OBJECT*), 0x00447580)

/************************/
/*  Data                */
/************************/
/****** Feature Booleans ************************************************************/
static bool DreamcastPlayerModels[NB_PLNO];
static bool DisablePlayerShadowing;

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
    RFRS_SetCnkDrawMode(RFRS_CNKDRAWMD_OPAQUE);

    njCnkDrawMotion(object, motion, frame);

    RFRS_SetCnkDrawMode(RFRS_CNKDRAWMD_TRANSPARENT);

    njCnkDrawMotion(object, motion, frame);

    RFRS_SetCnkDrawMode(RFRS_CNKDRAWMD_END);
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

/****** Feature *********************************************************************/
bool
RFF_DreamcastPlayerModel(int pno)
{
    if (pno < 0 || pno >= NB_PLNO)
        return false;

    return DreamcastPlayerModels[pno];
}

bool
RFF_DisablePlayerShadowing(void)
{
    return DisablePlayerShadowing;
}

/****** Init ************************************************************************/
void
RFM_PlayerInit(void)
{
    RFPL_ModelPrsInit();
    RFPL_Chaos0Init();

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

    if ( RF_ConfigGetInt( CNF_PLAYER_MODEL ) == CNFE_PLAYER_MODEL_DREAMCAST )
    {
        DreamcastPlayerModels[PLNO_SONIC]    = RFU_ReplacePlayerPrs("SONICMDL" , "plmdl_dc");
        DreamcastPlayerModels[PLNO_SHADOW]   = RFU_ReplacePlayerPrs("TERIOSMDL", "plmdl_dc");
        DreamcastPlayerModels[PLNO_MILES]    = RFU_ReplacePlayerPrs("MILESMDL" , "plmdl_dc");
        DreamcastPlayerModels[PLNO_EGGMAN]   = RFU_ReplacePlayerPrs("EGGMDL"   , "plmdl_dc");
        DreamcastPlayerModels[PLNO_KNUCKLES] = RFU_ReplacePlayerPrs("KNUCKMDL" , "plmdl_dc");

        if ( RFU_ReplacePlayerPrs("ROUGEMDL", "plmdl_dc") )
        {
            DreamcastPlayerModels[PLNO_ROUGE] = true;

            RFU_ReplacePlayerPrs("ROUGEMTN", "plmdl_dc");
        }

        DreamcastPlayerModels[PLNO_TAILS_WALKER] = RFU_ReplacePlayerPrs("TWALKMDL" , "plmdl_dc");
        DreamcastPlayerModels[PLNO_EGG_WALKER]   = RFU_ReplacePlayerPrs("EWALKMDL" , "plmdl_dc");
        DreamcastPlayerModels[PLNO_AMY]          = RFU_ReplacePlayerPrs("AMYMDL"   , "plmdl_dc");
        DreamcastPlayerModels[PLNO_SUPER_SONIC]  = RFU_ReplacePlayerPrs("SSONICMDL", "plmdl_dc");

        if ( RFU_ReplacePlayerPrs("SSHADOWMDL", "plmdl_dc") )
        {
            DreamcastPlayerModels[PLNO_SUPER_SONIC] = true;

            RFU_ReplaceTexture("SSHADOWTEX", "plmdl_dc");
        }

        DreamcastPlayerModels[PLNO_METAL_SONIC] = RFU_ReplacePlayerPrs("METALSONICMDL", "plmdl_dc");
        DreamcastPlayerModels[PLNO_CHAO_WALKER] = RFU_ReplacePlayerPrs("CWALKMDL"     , "plmdl_dc");
        DreamcastPlayerModels[PLNO_TICAL]       = RFU_ReplacePlayerPrs("TICALMDL"     , "plmdl_dc");

        if ( RFU_ReplacePlayerPrs("CHAOS0MDL", "plmdl_dc") )
        {
            DreamcastPlayerModels[PLNO_CHAOS0] = true;

            if ( !RFF_Chaos0TexAnim() )
            {
                RFU_ReplaceTexture("CHAOS0TEX", "plmdl_dc");
            }
        }
    }

    if ( RF_ConfigGetInt( CNF_PLAYER_MDLSHADOW ) == CNFE_BOOL_DISABLED )
    {
        DisablePlayerShadowing = true;

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

    if ( RF_ConfigGetInt( CNF_PLAYER_SHADLITEDASH ) )
    {
        WriteJump(0x0071E460, ___CreatePlayerDrawLightDashWithAlphaReducing);
    }
}
