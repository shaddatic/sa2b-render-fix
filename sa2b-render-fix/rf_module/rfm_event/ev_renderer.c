/************************/
/*  Includes            */
/************************/
/****** Core Toolkit ****************************************************************/
#include <samt/core.h>          /* core                                             */
#include <samt/writeop.h>       /* writejump                                        */

/****** Render Fix ******************************************************************/
#include <rf_core.h>            /* core                                             */
#include <rf_util.h>            /* switch displayer                                 */

/****** Config **********************************************************************/
#include <cnf.h>                /* config get                                       */

/****** Self ************************************************************************/
#include <rf_module/rfm_event/ev_renderer/evr_internal.h> /* children               */

/************************/
/*  Data                */
/************************/
/****** Pillarbox Settings **********************************************************/
static u32 Event43Mode[400 / BITSIN(u32)];

/****** Event Settings **************************************************************/
bool            EventEquipmentEnable;
RFE_EV_VSYNC    EventVsyncMode;
bool            EventDebugFlag;

/****** Feature *********************************************************************/
static bool     NewEventRenderer;

/************************/
/*  Source              */
/************************/
/****** Feature *********************************************************************/
bool
RFF_NewEventRenderer(void)
{
    return NewEventRenderer;
}

/****** 4:3 Mode ********************************************************************/
bool
EV_GetPillarbox(int evnum)
{
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
        for ( int i = 0; i < 400; ++i )
        {
            SetPillarboxSub(i, sw);
        }

        return;
    }

    SetPillarboxSub(evnum, sw);
}

/****** Init ************************************************************************/
void
EV_RendererInit(void)
{
    EventEquipmentEnable = CNF_GetInt(CNF_EVENT_DRAWEQUIP);
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
            EV_SetPillarbox( 24, ON);
            EV_SetPillarbox(100, ON);
            EV_SetPillarbox(101, ON);
            EV_SetPillarbox(126, ON);
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

    WriteJump(0x005FB4FD, 0x005FB5B9); // disable vanilla black bars
    WriteJump(0x00601938, 0x00601A0A); // ^^ movies

    SwitchDisplayer(0x005FB04D, DISP_SORT); // set screen effect to sorted displayer

    NewEventRenderer = true;
}
