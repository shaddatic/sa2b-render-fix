/*
*   SA2 Render Fix - '/event/ev_internal.h'
*
*   Description:
*     Internal header for Event feature module.
*
*   Contributors:
*     - Shaddatic
*     - Exant (Original creator of event modifier system)
*/
#ifndef H_RF_EVENT_INTERNAL
#define H_RF_EVENT_INTERNAL

/************************/
/*  External Includes   */
/************************/
/****** Event Info ******************************************************************/
#include <rf_eventinfo.h>       /* event info and data                              */

/****** Self ************************************************************************/
#include <rfm_event.h>          /* parent                                           */

EXTERN_START

/************************/
/*  Prototypes          */
/************************/
/****** Init ************************************************************************/
/*
*   Description:
*     Init Render Fix Event renderer.
*/
void    EV_RendererInit( void );
/*
*   Description:
*     Init event camera parameter fix.
*/
void    EV_ByteSwapInit( void );

EXTERN_END

#endif/*H_RF_EVENT_INTERNAL*/
