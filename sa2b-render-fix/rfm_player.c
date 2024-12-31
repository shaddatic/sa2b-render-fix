/************************/
/*  Includes            */
/************************/
/****** Core Toolkit ****************************************************************/
#include <sa2b/core.h>          /* core                                             */
#include <sa2b/writeop.h>       /* writejump                                        */

/****** Ninja ***********************************************************************/
#include <sa2b/ninja/ninja.h>   /* ninja                                            */

/****** Game ************************************************************************/
#include <sa2b/sonic/task.h>    /* task                                             */
#include <sa2b/sonic/camera.h>  /* game camera                                      */
#include <sa2b/sonic/light.h>   /* light                                            */
#include <sa2b/sonic/njctrl.h>  /* ninja controls                                   */
#include <sa2b/sonic/c_colli.h> /* core colli                                       */
#include <sa2b/sonic/misc.h>    /* misc                                             */

/****** Character *******************************************************************/
#include <sa2b/sonic/figure/knuckles.h> /* knuckles work                            */

/****** Render Fix ******************************************************************/
#include <rf_core.h>            /* core                                             */
#include <rf_config.h>          /* config                                           */
#include <rf_njcnk.h>           /* emulated njcnk draw functions                    */
#include <rf_util.h>            /* change displayer                                 */
#include <rf_renderstate.h>     /* render state                                     */

/****** Self ************************************************************************/
#include <rfm_player.h>               /* self                                       */
#include <rfm_player/rfpl_internal.h> /* children                                   */

/************************/
/*  Game Functions      */
/************************/
/****** Player Object ***************************************************************/
#define CreatePlayerObjectData          FUNC_PTR(PLAYER_OBJECT*, __cdecl, (NJS_CNK_OBJECT*), 0x00447580)

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

    if ( RF_ConfigGetInt( CNF_PLAYER_MODSHADOW ) == CNFE_BOOL_DISABLED )
    {
        // disable player shadowing
        WriteData(0x00720131+6, 0x0, u32); // Sonic/shadow/amy/mtlsonic
        WriteData(0x00744567+6, 0x0, u32); // Egg Walker
        WriteData(0x00747138+6, 0x0, u32); // Dark Chao Walker
        WriteData(0x00747E38+6, 0x0, u32); // Tails Walker
        WriteData(0x007462F8+6, 0x0, u32); // Chao Walker
        WriteData(0x0072F011+6, 0x0, u32); // Knuckles
        WriteData(0x00730A64+6, 0x0, u32); // Rouge
        WriteData(0x0072FC01+6, 0x0, u32); // Tical
        WriteData(0x00731B21+6, 0x0, u32); // Chaos
    }
}
