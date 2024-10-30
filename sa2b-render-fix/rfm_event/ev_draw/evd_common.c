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
#include <sa2b/sonic/njctrl.h>  /* ninja control                                    */
#include <sa2b/sonic/display.h> /* screen display                                   */

/****** Render Fix ******************************************************************/
#include <rf_core.h>            /* core                                             */
#include <rf_eventinfo.h>       /* event data                                       */
#include <rf_renderstate.h>     /* render state                                     */
#include <rf_njcnk.h>           /* emulated njcnk draw functions                    */

/****** Self ************************************************************************/
#include <rfm_event/ev_draw/evd_internal.h> /* parent & siblings                    */

EV_ENTRY_TYPE
EventGetEntryType(const EventEntityData* pEntry)
{
    if (!pEntry->object && !pEntry->GjsObject)
        return EV_ENTRY_TYPE_NONE;

    const int attr = pEntry->attr;

    if (!pEntry->motion)
    {
        if (attr & EV_ENTF_MODVOL) // Added for Render Fix
        {
            return EV_ENTRY_TYPE_MODDRAW;
        }

        return (attr & EV_ENTF_NOFOG) ? EV_ENTRY_TYPE_EASYNOFOG : EV_ENTRY_TYPE_DRAW;
    }

    if (attr & EV_ENTF_MODVOL)
    {
        return EV_ENTRY_TYPE_MODMTN;
    }

    if (pEntry->shape)
    {
        if (attr & EV_ENTF_USESIMPLE)
        {
            return EV_ENTRY_TYPE_SHAPE;
        }
        else
        {
            return (attr & EV_ENTF_MULTILIGHT) ? EV_ENTRY_TYPE_MULTISHAPE : EV_ENTRY_TYPE_SHAPE;
        }
    }
    else // is regular motion
    {
        if (attr & EV_ENTF_USESIMPLE)
        {
            return EV_ENTRY_TYPE_MTN;
        }
        else
        {
            return (attr & EV_ENTF_MULTILIGHT) ? EV_ENTRY_TYPE_MULTIMTN : EV_ENTRY_TYPE_MTN;
        }
    }
}
