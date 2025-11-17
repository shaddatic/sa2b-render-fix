/*
*   SA2 Render Fix - '/event/ev_renderer/evr_internal.h'
*
*   Description:
*     Internal header for Render Fix's Event renderer and logic sub-module.
*/
#ifndef H_RF_EVENT_RENDERER_INTERNAL
#define H_RF_EVENT_RENDERER_INTERNAL

___TODO("Inline the eventinfo header into this one");

#include <rf_eventinfo.h>

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

/****** Pillarbox *******************************************************************/
#define EV_PILLARBOX_MAX       (609)
#define EV_PILLARBOX_NB        (EV_PILLARBOX_MAX+1)

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

/****** WaitVsync Mode **************************************************************/
typedef enum
{
    EV_VSYNCMD_30,              /* always 30fps                                     */
    EV_VSYNCMD_EVENT,           /* event choses vsync                               */
    EV_VSYNCMD_60,              /* always 60fps                                     */
}
RFE_EV_VSYNC;

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
/****** Settings ********************************************************************/
EXTERN bool             EventEquipmentEnable;
EXTERN RFE_EV_VSYNC     EventVsyncMode;
EXTERN bool             EventDebugFlag;

/****** Draw Pass *******************************************************************/
EXTERN s32 DebugDrawPass;

/****** Big Tex *********************************************************************/
EXTERN NJS_TEXLIST* EvBigTexture;

/************************/
/*  Prototypes          */
/************************/
/****** Sub-module Init *************************************************************/
/*
*   Description:
*     Init RF Event task.
*/
void    EVR_TaskInit( void );
/*
*   Description:
*     Init Vsync controller.
*/
void    EVR_VsyncInit( void );
/*
*   Description:
*     Init movie/overlay sub-module.
*/
void    EVR_MovieInit( void );

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

/****** Event Exec ******************************************************************/
/*
*   Description:
*     Execute Scene number, frame, and Big frame logic.
*/
void    EV_SceneExec( void );
/*
*   Description:
*     Execute Blare data.
*
*   Parameters:
*     - ixScene     : scene to execute blare logic for.
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
*
*   Parameters:
*     - tp          : event executor task pointer
*/
void    EV_CameraExec( task* tp );

/****** Event Draw ******************************************************************/
/*
*   Description:
*     Set constant material based on Event sprite data, also known as Alpha Effect.
*   This is used in the intro to control the env map material over the logo.
*/
void    EV_SetConstMat( void );
/*
*   Description:
*     Draw all non-modifier entries in an Event scene of a specific layer.
*
*   Parameters:
*     - ixScene     : scene index to draw
*     - ixLayer     : layer index to draw                      [opt: EV_ALL_LAYERS]
*/
void    EventSceneDraw( int ixScene, int ixLayer );
/*
*   Description:
*     Draw all modifier entries in an Event scene.
*
*   Parameters:
*     - ixScene     : scene index to draw
*/
void    EventSceneModDraw( int ixScene );
/*
*   Description:
*     Begin equipment draw for this frame.
*/
void    EventResetEquipmentFlags( void );
/*
*   Description:
*     Draw player equipment models.
*
*   Notes:
*     - Requires matrix data from the main models, ensure the current scene has been
*       drawn with the 'All Layers' flag before calling this.
*/
void    EventEquipmentDraw( void );
/*
*   Description:
*     Draw the screen color effect.
*/
void    EV_DrawScreenEffect( void );

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

/****** Pillarbox *******************************************************************/
/*
*   Description:
*     Get the pillarbox mode for an event.
*/
bool    EV_GetPillarbox( int evnum );
/*
*   Description:
*     Set the pillarbox mode for an event.
*/
void    EV_SetPillarbox( int evnum, b32 sw );

EXTERN_END

#endif/*H_RF_EVENT_RENDERER_INTERNAL*/
