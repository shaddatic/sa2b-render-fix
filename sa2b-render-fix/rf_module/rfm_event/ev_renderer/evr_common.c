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
#include <samt/sonic/camera.h>  /* camcontwk                                        */

/****** Render Fix ******************************************************************/
#include <rf_core.h>            /* core                                             */
#include <rf_renderstate.h>     /* render state                                     */
#include <rf_njcnk.h>           /* emulated njcnk draw functions                    */

/****** Self ************************************************************************/
#include <rf_module/rfm_event/ev_renderer/evr_internal.h> /* parent & siblings      */

/************************/
/*  Game Definitions    */
/************************/
/****** Camera **********************************************************************/
#define EvCamRangeOutPos                DATA_REF(NJS_POINT3, 0x01DB0FF0)

/************************/
/*  Source              */
/************************/
/****** Static **********************************************************************/
static bool
EntryRangeOut(const EVENT_ENTRY* pEntry, f32 dist)
{
    const NJS_VECTOR v =
    {
        pEntry->position.x - EvCamRangeOutPos.x,
        pEntry->position.y - EvCamRangeOutPos.y,
        pEntry->position.z - EvCamRangeOutPos.z
    };

    return ( njScalor2(&v) >= (dist*dist) );
}

/****** Extern **********************************************************************/
EV_ENTRY_TYPE
EventGetEntryType(const EVENT_ENTRY* pEntry)
{
    if (!pEntry->pObject && !pEntry->pGjsObject)
    {
        return EV_ENTRY_TYPE_NONE;
    }

    const int attr = pEntry->attr;

    if ( !pEntry->pMotion )
    {
        if ( attr & EV_ENTF_NOFOG )
        {
            return EV_ENTRY_TYPE_EASYNOFOG;
        }

        if ( CutsceneMode != EVENTMD_START && EntryRangeOut(pEntry, 1000.f) )
        {
            return EV_ENTRY_TYPE_NONE;
        }

        if ( attr & EV_ENTF_MODVOL )
        {
            return EV_ENTRY_TYPE_MODDRAW;
        }

        if ( attr & EV_ENTF_FORCESIMPLE )
        {
            return EV_ENTRY_TYPE_DRAW;
        }
        else
        {
            return (attr & EV_ENTF_MULTILIGHT) ? EV_ENTRY_TYPE_MULTIDRAW : EV_ENTRY_TYPE_DRAW;
        }
    }

    if ( attr & EV_ENTF_MODVOL )
    {
        return EV_ENTRY_TYPE_MODMTN;
    }

    if ( pEntry->pShape )
    {
        if ( attr & EV_ENTF_FORCESIMPLE )
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
        if ( attr & EV_ENTF_FORCESIMPLE )
        {
            return EV_ENTRY_TYPE_MTN;
        }
        else
        {
            return (attr & EV_ENTF_MULTILIGHT) ? EV_ENTRY_TYPE_MULTIMTN : EV_ENTRY_TYPE_MTN;
        }
    }
}
