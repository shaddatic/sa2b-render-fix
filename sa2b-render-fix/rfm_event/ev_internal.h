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
/*  Constants           */
/************************/
/****** Frame Constants *************************************************************/
#define EVENT_SPEED_BASE        (0.5f)
#define EVENT_FRAME_STEP        (0.5f)

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

/****** Task ************************************************************************/
#define DBG_FLAG_SPEED          (1<<0) /* timescale control                         */
#define DBG_FLAG_CAMERA         (1<<1) /* debug camera                              */
#define DBG_FLAG_CAMERAINIT     (1<<2) /* debug camera init                         */
#define DBG_FLAG_CAMERAFAST     (1<<3) /* fast debug camera                         */
#define DBG_FLAG_PRINTINFO      (1<<4) /* print event debug                         */

/************************/
/*  Opaque Types        */
/************************/
/****** Task ************************************************************************/
typedef struct task             task;

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

/****** 4:3 Mode ********************************************************************/
typedef enum
{
    EV_43MD_NEVER,              /* never force 4:3                                  */
    EV_43MD_VANILLA,            /* use 4:3 when vanilla would       (unimplimented) */
    EV_43MD_ALWAYS              /* always force 4:3                                 */
}
RFE_EV_43MODE;

/****** Draw Pass *******************************************************************/
typedef enum
{
    DBG_DRAWPASS_ALL,
    DBG_DRAWPASS_OPAQUE,
    DBG_DRAWPASS_TRANS,

    DBG_DRAWPASS_LAYER_START,
    DBG_DRAWPASS_LAYER_END      = DBG_DRAWPASS_LAYER_START + 16,

    NB_DBG_DRAWPASS,
}
RFE_DBG_DRAWPASS;

/************************/
/*  Extern Data         */
/************************/
/****** Draw Pass *******************************************************************/
EXTERN s32 DebugDrawPass;

/************************/
/*  Prototypes          */
/************************/
/****** Init ************************************************************************/
/*
*   Description:
*     Init Render Fix Event renderer.
*/
void    EV_DrawInit( void );
/*
*   Description:
*     Init event camera parameter fix.
*/
void    EV_ByteSwapInit( void );

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
EV_ENTRY_TYPE   EventGetEntryType( const EVENT_ENTRY* pEntry );

/****** Event Reflections ***********************************************************/
/*
*   Description:
*     Draw reflected event entries.
*/
void    EventDrawReflections( void );

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

/****** Get Settings ****************************************************************/
/*
*   Description:
*     Get player equipment draw mode.
*
*   Returns:
*     'true' if equipment is to be drawn, 'false' if not.
*/
bool    EV_GetEquipmentMode( void );
/*
*   Description:
*     Get current 4:3 event mode.
*/
RFE_EV_43MODE EV_Get43Mode( void );
/*
*   Description:
*     Check if wide aspect ratio is currently allowed.
*/
bool    EV_AllowsWideAspect( void );

/****** Task ************************************************************************/
/*
*   Description:
*     Event executor init.
*/
void    EventInitiator( task* tp );
/*
*   Description:
*     Event displayers.
*/
void    EventDisplayer( task* tp );
void    EventDisplayerSort( task* tp );
void    EventDisplayerDelayed( task* tp );
void    EventDisplayerShadow( task* tp );

/****** Event Exec ******************************************************************/
/*
*   Description:
*     Execute Blare data.
*/
void    EV_BlareExec( int ixScene );
/*
*   Description:
*     Execute texture index animations.
*/
void    EV_TexAnimExec( void );
/*
*   Description:
*     Execute event camera.
*/
void    EV_CameraExec( task* tp );

/****** Debug Exec ******************************************************************/
/*
*   Description:
*     Execute debug logic.
*/
void    EV_DebugExec( task* tp );
/*
*   Description:
*     Display debug info.
*/
void    EV_DebugDisp( task* tp );
/*
*   Description:
*     Execute debug camera.
*/
void    EV_DebugCameraExec( task* tp );

EXTERN_END

#endif/*H_RF_EVENT_INTERNAL*/
