/************************/
/*  Includes            */
/************************/
/****** Core Toolkit ****************************************************************/
#include <samt/core.h>          /* core                                             */
#include <samt/writeop.h>       /* writejump                                        */
#include <samt/string.h>        /* strformat                                        */

/****** Game ************************************************************************/
#include <samt/sonic/texture.h> /* texcreatetexture                                 */

/****** Render Fix ******************************************************************/
#include <rf_core.h>            /* core                                             */
#include <rf_util.h>            /* switch displayer                                 */
#include <rf_system.h>          /* pillarbox                                        */

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

static void
LoadTexPrs_WithExt(char* filename, NJS_TEXLIST* ptlo, void* buffer)
{
    const void* const fptr = (void*) 0x0044C410;

    __asm
    {
        push [buffer]
        mov edx, [ptlo]
        mov ecx, [filename]

        call fptr

        add esp, 4
    }
}

static void __cdecl
LoadEventTextures(char* filename, NJS_TEXLIST* ptlo, void* buffer)
{
    LoadTexPrs_WithExt(filename, ptlo, buffer);
    
    c7 buf[16];
    mtStrFormat(buf, ARYLEN(buf), "e%04ibigtex", EventNum);
    
    EvBigTexture = texCreateTexlist(buf);
    
    if ( EvBigTexture && !EvBigTexture->nbTexture )
    {
        texFreeTexlist(EvBigTexture);
    
        EvBigTexture = nullptr;
    }
}

__declspec(naked)
static void
___LoadEventTextures(void)
{
    __asm
    {
        push [esp+4]
        push edx
        push ecx

        call LoadEventTextures

        add esp, 12
        retn
    }
}

static void
EventPostLoad(void)
{
    EVR_StartReplaceAttr();
    EVR_ScanEvent();
}

/****** Init ************************************************************************/
void
EV_RendererInit(void)
{
    EventEquipmentEnable = CNF_GetInt(CNF_MISC_EVEQUIPMENT);
    EventVsyncMode       = CNF_GetInt(CNF_EVENT_VSYNC);

    EventDebugFlag       = CNF_GetInt(CNF_DEBUG_EVENT);

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
    WriteNOP(0x00600054, 0x0060005A);
    WriteCall(0x00600054, EventPostLoad);

    WriteJump(0x005FB4FD, 0x005FB5B9); // disable vanilla black bars
    WriteJump(0x00601938, 0x00601A0A); // ^^ movies

    // task loop does exec during movies, so hook this so pillars can still appear if needed
    WriteCall(0x00601A18, DrawTailsPlainWithPillar);

    // Load bigtex
    WriteCall(0x005FFE34, ___LoadEventTextures);

    SwitchDisplayer(0x005FB04D, DISP_SORT); // set screen effect to sorted displayer

    if ( !CNF_GetInt(CNF_EVENT_SUBTITLE) )
    {
        WriteJump(0x0060221D, 0x00602299);
    }
}
