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

/****** Character *******************************************************************/
#include <samt/sonic/figure/knuckles.h> /* knuckles work                            */

/****** Render Fix ******************************************************************/
#include <rf_core.h>            /* core                                             */
#include <rf_config.h>          /* config                                           */
#include <rf_njcnk.h>           /* emulated njcnk draw functions                    */
#include <rf_util.h>            /* change displayer                                 */
#include <rf_renderstate.h>     /* render state                                     */

void    rjCnkSetTextureCallback( Sint16(__cdecl* callback)(Sint16 texid) );

/************************/
/*  Constants           */
/************************/
/****** Texture Anim Start **********************************************************/
#define CHAOS0_WWA_TEXID        (2) /* start texid for water animation              */

/************************/
/*  Game Functions      */
/************************/
/****** Chaos 0 Displayer ***********************************************************/
#define Chaos0Disp          FUNC_PTR(void, __cdecl, (task*), 0x00731A30)
#define Chaos0DispDely      FUNC_PTR(void, __cdecl, (task*), 0x00732100)

/************************/
/*  Data                */
/************************/
/****** Texture Animation ***********************************************************/
static bool     Chaos0TexAnim;

/****** Texture Anim Offset *********************************************************/
static Sint16   ChaosWaterAnimId;

/************************/
/*  Source              */
/************************/
/****** Texture Callback ************************************************************/
static Sint16
ChaosTextureCallback(Sint16 texid)
{
    if ( texid == CHAOS0_WWA_TEXID )
        return ChaosWaterAnimId;

    return texid;
}

/****** Displayer *******************************************************************/
static hook_info Chaos0DispHookInfo[1];
static void
Chaos0DispHook(task* tp)
{
    /** Force alpha test specifically for DC Chaos, since we want at least *some*
      of him to not be drawn over **/

    RFRS_SetTransMode(RFRS_TRANSMD_AUTO_ATEST);

    const KNUCKLESWK* knwp = GET_KNUCKLESWK(tp);

    if (Chaos0TexAnim)
    {
        ChaosWaterAnimId = (knwp->chaos0_texid >> 1) + CHAOS0_WWA_TEXID;

        rjCnkSetTextureCallback( ChaosTextureCallback );
    }

    FuncHookCall( Chaos0DispHookInfo, Chaos0Disp(tp) );

    rjCnkSetTextureCallback( NULL );

    RFRS_SetTransMode(RFRS_TRANSMD_END);
}

/****** Displayer Delayed ***********************************************************/
static void
Chaos0DelyMotionCallback(NJS_CNK_OBJECT* object)
{
    if ( object == CHAR_OBJECTS[525].pObject->child->child->child->sibling )
    {
        if ( playertwp[KnucklesWorkPointer->pw.pl_num]->mode != 1 )
            return;

        njRotateX(NULL, KnucklesWorkPointer->pw.lean);
    }
}

static hook_info Chaos0DispDelyHookInfo[1];
static void
Chaos0DispDelyHook(task* tp)
{
    const KNUCKLESWK* knwp = GET_KNUCKLESWK(tp);

    KnucklesWorkPointer = GET_KNUCKLESWK(tp);

    if (Chaos0TexAnim)
    {
        ChaosWaterAnimId = (knwp->chaos0_texid >> 1) + CHAOS0_WWA_TEXID;

        rjCnkSetTextureCallback( ChaosTextureCallback );
    }

    njCnkSetMotionCallback( Chaos0DelyMotionCallback );

    FuncHookCall( Chaos0DispDelyHookInfo, Chaos0DispDely(tp) );

    njCnkSetMotionCallback(  NULL );
    rjCnkSetTextureCallback( NULL );
}

/****** Feature *********************************************************************/
bool
RFF_Chaos0TexAnim(void)
{
    return Chaos0TexAnim;
}

/****** Init ************************************************************************/
void
RFPL_Chaos0Init(void)
{
    /** Move main displayer to 'disp_sort',
      as DC Chaos 0 is totally transparent. **/
    SwitchDisplayer(0x00728CC7, DISP_SORT);

    FuncHook(Chaos0DispHookInfo    , Chaos0Disp    , Chaos0DispHook);
    FuncHook(Chaos0DispDelyHookInfo, Chaos0DispDely, Chaos0DispDelyHook);

    /** Kill the inlaid texture animation code. We replace it with a better
      system using Render Fix's Chunk 'TextureCallback' feature, where we can
      change a specific texture at draw time, rather than a specific offset of the
      model. This also means it can be easily disabled, and works with DC Chaos. **/

    WriteNOP(0x00731F01, 0x00731FAA); // kill chaos0 tex anim code
    WriteNOP(0x0073257F, 0x0073261A); // ^ dely

    Chaos0TexAnim = RF_ConfigGetInt(CNF_PLAYER_CHAOS0ANIM) == CNFE_BOOL_ENABLED;
}
