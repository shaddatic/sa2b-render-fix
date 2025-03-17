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
#include <samt/sonic/njctrl.h>  /* ninja control                                    */
#include <samt/sonic/display.h> /* screen display                                   */

/****** Render Fix ******************************************************************/
#include <rf_core.h>            /* core                                             */
#include <rf_eventinfo.h>       /* event data                                       */
#include <rf_renderstate.h>     /* render state                                     */
#include <rf_njcnk.h>           /* emulated njcnk draw functions                    */

/****** Self ************************************************************************/
#include <rfm_event/ev_draw/evd_internal.h> /* parent & siblings                    */

/************************/
/*  Source              */
/************************/
/****** Extern **********************************************************************/
EV_ENTRY_TYPE
EventGetEntryType(const EVENT_ENTRY* pEntry)
{
    if (!pEntry->pObject && !pEntry->pGjsObject)
        return EV_ENTRY_TYPE_NONE;

    const int attr = pEntry->attr;

    if (!pEntry->pMotion)
    {
        if (attr & EV_ENTF_NOFOG)
        {
            return EV_ENTRY_TYPE_EASYNOFOG;
        }

        if (attr & EV_ENTF_MODVOL)
        {
            return EV_ENTRY_TYPE_MODDRAW;
        }

        if (attr & EV_ENTF_FORCESIMPLE)
        {
            return EV_ENTRY_TYPE_DRAW;
        }
        else
        {
            return (attr & EV_ENTF_MULTILIGHT) ? EV_ENTRY_TYPE_MULTIDRAW : EV_ENTRY_TYPE_DRAW;
        }
    }

    if (attr & EV_ENTF_MODVOL)
    {
        return EV_ENTRY_TYPE_MODMTN;
    }

    if (pEntry->pShape)
    {
        if (attr & EV_ENTF_FORCESIMPLE)
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
        if (attr & EV_ENTF_FORCESIMPLE)
        {
            return EV_ENTRY_TYPE_MTN;
        }
        else
        {
            return (attr & EV_ENTF_MULTILIGHT) ? EV_ENTRY_TYPE_MULTIMTN : EV_ENTRY_TYPE_MTN;
        }
    }
}
