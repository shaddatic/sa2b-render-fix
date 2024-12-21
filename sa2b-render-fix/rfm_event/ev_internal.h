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
/*  Enums               */
/************************/
/****** 4:3 Mode ********************************************************************/
typedef enum
{
    EV_43MD_NEVER,              /* never force 4:3                                  */
    EV_43MD_VANILLA,            /* use 4:3 when vanilla would       (unimplimented) */
    EV_43MD_ALWAYS              /* always force 4:3                                 */
}
RFE_EV_43MODE;

/************************/
/*  Prototypes          */
/************************/
/****** Event Draw ******************************************************************/
/*
*   Description:
*     Init Render Fix Event draw functions.
*/
void    EV_DrawInit(void);
/*
*   Description:
*     Init Old (< 1.3.3) Render Fix Event draw functions.
*/
void    EV_OldDrawInit(void);

/****** Event Modifiers *************************************************************/
/*
*   Description:
*     Init temporary event modifier drawing system.
*/
void    EV_ModifierInit(void);

/****** Event Camera ****************************************************************/
/*
*   Description:
*     Init event camera parameter fix.
*/
void    EV_CameraInit(void);

/****** Event File Bytewapping ******************************************************/
/*
*   Description:
*     Init event camera parameter fix.
*/
void    EV_ByteSwapInit(void);

/****** Get Settings ****************************************************************/
/*
*   Description:
*     Get player equipment draw mode.
*
*   Returns:
*     'true' if equipment is to be drawn, 'false' if not.
*/
bool    EV_GetEquipmentMode(void);
/*
*   Description:
*     Get current 4:3 event mode.
*
*   Returns:
*     Current 4:3 mode.
*/
RFE_EV_43MODE EV_Get43Mode(void);

EXTERN_END

#endif/*H_RF_EVENT_INTERNAL*/
