/************************/
/*  Includes            */
/************************/
/****** Core Toolkit ****************************************************************/
#include <samt/core.h>          /* core                                             */
#include <samt/writeop.h>       /* writejump                                        */
#include <samt/string.h>        /* strformat                                        */

/****** Utl *************************************************************************************/
#include <samt/util/asm.h>          /* asm helper                                               */

/****** Game ************************************************************************/
#include <samt/sonic/texture.h> /* texcreatetexture                                 */

/****** Render Fix ******************************************************************/
#include <rf_core.h>            /* core                                             */
#include <rf_util.h>            /* switch displayer                                 */
#include <rf_system.h>          /* pillarbox                                        */

/****** RFU *************************************************************************/
#include <rfu_texture.h>        /* create texlist                                   */

/****** Config **********************************************************************/
#include <cnf.h>                /* config get                                       */

/****** Self ************************************************************************/
#include <rf_module/rfm_event/ev_renderer/evr_internal.h> /* children               */

/************************/
/*  Game Defs           */
/************************/
/****** Tails Plain *****************************************************************/
#define DrawTailsPlain          FUNC_PTR(void, __cdecl   , (void)                     , 0x00601600)

/************************/
/*  Data                */
/************************/
/****** Pillarbox Settings **********************************************************/
static u32 Event43Mode[(EV_PILLARBOX_MAX / BITSIN(u32)) + 1];

/****** Event Settings **************************************************************/
bool            EventEquipmentEnable;
RFE_EV_VSYNC    EventVsyncMode;
bool            EventDebugFlag;
bool            EventDebugMovie;

/****** Init Flag *******************************************************************/
static bool EvrInitFlag;

/****** Big Tex *********************************************************************/
NJS_TEXLIST*    EvBigTexture;

/************************/
/*  Source              */
/************************/
/****** 4:3 Mode ********************************************************************/
bool
EV_GetPillarbox(int evnum)
{
    if ( evnum > EV_PILLARBOX_MAX )
    {
        return false;
    }

    const int num_ary = evnum / BITSIN(u32);
    const int num_bit = evnum % BITSIN(u32);

    return (Event43Mode[num_ary] >> num_bit) & 1;
}

static void
SetPillarboxSub(int evnum, b32 sw)
{
    const int num_ary = evnum / BITSIN(u32);
    const int num_bit = evnum % BITSIN(u32);

    if ( sw == ON )
    {
        Event43Mode[num_ary] |= (1<<num_bit);
    }
    else // OFF
    {
        Event43Mode[num_ary] &= ~(1<<num_bit);
    }
}

void
EV_SetPillarbox(int evnum, b32 sw)
{
    if ( evnum <= -1 )
    {
        for ( int i = 0; i < EV_PILLARBOX_NB; ++i )
        {
            SetPillarboxSub(i, sw);
        }

        return;
    }

    SetPillarboxSub(evnum, sw);
}

/****** Static **********************************************************************/
static void
DrawTailsPlainWithPillar(void)
{
    DrawTailsPlain();

    RF_SysCtrlDrawPillar(true);
    RF_SysCtrlResetPillar();
}

void
EVR_EventInit(void)
{
    if ( EvrInitFlag )
    {
        EVR_EventExit();
    }

    c7 buf[32];

    // load extra big textures
    mtStrFormat(buf, 32, "EVENT/e%04ibigtex", EventNum);

    EvBigTexture = RFU_CreateTexlist(buf);

    // init event data
    EVR_FixShapes();
    EVR_StartReplaceAttr();

    // scan event for draw flags
    EVR_ScanEvent();

    EvrInitFlag = true;
}

void
EVR_EventExit(void)
{
    if ( EvBigTexture )
    {
        RFU_FreeTexlist(EvBigTexture);
    
        EvBigTexture = nullptr;
    }

    EVR_EndReplaceAttr();

    EvrInitFlag = false;
}

/****** Init ************************************************************************/
void
EV_RendererInit(void)
{
    EventEquipmentEnable = CNF_GetInt(CNF_MISC_EVEQUIPMENT);
    EventVsyncMode       = CNF_GetInt(CNF_EVENT_VSYNC);

    EventDebugFlag       = CNF_GetInt(CNF_DEBUG_EVENT);
    EventDebugMovie      = CNF_GetInt(CNF_DEBUG_TEXMOVIE);

    switch ( CNF_GetInt(CNF_EVENT_43MD) )
    {
        case CNFE_EVENT_43MD_ALWAYS:
        {
            EV_SetPillarbox(-1, ON);
            break;
        }
        case CNFE_EVENT_43MD_NOINTRO:
        {
            EV_SetPillarbox(-1 , ON);
            EV_SetPillarbox(350, OFF);
            break;
        }
        case CNFE_EVENT_43MD_SPECIFIC:
        {
            EV_SetPillarbox( 21, ON);
            EV_SetPillarbox(205, ON);
            EV_SetPillarbox(206, ON);
            EV_SetPillarbox(360, ON);
            EV_SetPillarbox(361, ON);
            break;
        }
        case CNFE_EVENT_43MD_NEVER:
        {
            break;
        }
    }

    EV_SetPillarbox(211, ON);

    EVR_TaskInit();
    EVR_VsyncInit();
    EVR_MovieInit();

    // call for just after file load
    WriteNOP(0x00600063, 0x0060006F);
    WriteCall(0x00600063, EVR_EventInit);

    WriteJump(0x005FB4FD, 0x005FB5B9); // disable vanilla black bars
    WriteJump(0x00601938, 0x00601A0A); // ^^ movies

    // task loop does exec during movies, so hook this so pillars can still appear if needed
    WriteCall(0x00601A18, DrawTailsPlainWithPillar);

    SwitchDisplayer(0x005FB04D, DISP_SORT); // set screen effect to sorted displayer

    if ( !CNF_GetInt(CNF_EVENT_SUBTITLE) )
    {
        WriteJump(0x0060221D, 0x00602299);
    }
}
