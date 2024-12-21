/*
*   SA2 Render Fix - '/rfm_event/ev_draw/evd_internal.h'
*
*   Description:
*     Render Fix event draw internal header.
*
*   Contributors:
*     - Shaddatic
*/
#ifndef H_RF_EVENT_DRAW_INTERNAL
#define H_RF_EVENT_DRAW_INTERNAL

/************************/
/*  External Includes   */
/************************/
/****** Self ************************************************************************/
#include <rfm_event/ev_internal.h>  /* parent                                       */

EXTERN_START

/************************/
/*  Constants           */
/************************/
/****** Scene Number ****************************************************************/
#define EVENT_BASE_SCENE        (0)

/****** Scene Layer *****************************************************************/
#define EV_ALL_LAYERS           (-1)

/****** Entry Flags *****************************************************************/
#define EV_ENTF_SIMPLEMAT       (0x0001) /* use SimpleDraw variant                  */
#define EV_ENTF_NOFOG           (0x0002) /* draw with no fog & EasyDraw             */
#define EV_ENTF_LIGHT1          (0x0004) /* if multi light 1 is enabled             */
#define EV_ENTF_LIGHT2          (0x0008) /* if multi light 2 is enabled             */
#define EV_ENTF_LIGHT3          (0x0010) /* if multi light 3 is enabled             */
#define EV_ENTF_LIGHT4          (0x0020) /* if multi light 4 is enabled             */
#define EV_ENTF_MODVOL          (0x0040) /* entry is a modifier volume              */
#define EV_ENTF_REFLECT         (0x0080) /* entry has reflection                    */
#define EV_ENTF_BLARE           (0x0100) /* entry has blare                         */
#define EV_ENTF_FORCESIMPLE     (0x0200) /* Force SimpleDraw, no MultiDraw          */

/** if none of the lights are enabled, regular draw will be used **/
#define EV_ENTF_MULTILIGHT      (EV_ENTF_LIGHT1|EV_ENTF_LIGHT2|EV_ENTF_LIGHT3|EV_ENTF_LIGHT4)

/************************/
/*  Enums               */
/************************/
/****** Entry Type ******************************************************************/
typedef enum
{
    EV_ENTRY_TYPE_NONE,         /* None                                             */
    EV_ENTRY_TYPE_DRAW,         /* DrawObject                                       */
    EV_ENTRY_TYPE_MTN,          /* DrawMotion                                       */
    EV_ENTRY_TYPE_SHAPE,        /* DrawShape                                        */
    EV_ENTRY_TYPE_EASYNOFOG,    /* EasyDrawObject                                   */
    EV_ENTRY_TYPE_MULTIDRAW,    /* MultiDrawObject                                  */
    EV_ENTRY_TYPE_MULTIMTN,     /* MultiDrawMotion                                  */
    EV_ENTRY_TYPE_MULTISHAPE,   /* MultiDrawShape                                   */
    EV_ENTRY_TYPE_MODDRAW,      /* ModDrawObject // unused?                         */
    EV_ENTRY_TYPE_MODMTN,       /* ModDrawMotion                                    */
}
EV_ENTRY_TYPE;

/************************/
/*  Prototypes          */
/************************/
/****** Entry Type ******************************************************************/
/*
*   Description:
*     Get entry type number of specific entry.
*
*   Parameters:
*     - pEntry      : event entry pointer
*
*   Returns:
*     Entry type of given entry.
*/
EV_ENTRY_TYPE   EventGetEntryType( const EventEntityData* pEntry );

/****** Event Draw ******************************************************************/
/*
*   Description:
*     Draw reflected event entries.
*/
void    EventDrawReflections( void );
/*
*   Description:
*     Draw 4:3 aspect ratio bars.
*/
void    Draw43Bars( void );

/****** Event Lights ****************************************************************/
/*
*   Description:
*     Setup event light data for this frame.
*/
void    EventLightSet( void );
/*
*   Description:
*     Switch light loadout for single draw. Eg. EasyDraw/SimpleDraw
*/
void    EventLightSwitchSingle( void );
/*
*   Description:
*     Switch light loadout for multi-light draw. Eg. EasyMultiDraw/SimpleMultiDraw
*
*   Parameters:
*     - attr        : event entry attributes
*/
void    EventLightSwitchMulti( Uint32 attr );

EXTERN_END

#endif/*H_RF_EVENT_DRAW_INTERNAL*/
