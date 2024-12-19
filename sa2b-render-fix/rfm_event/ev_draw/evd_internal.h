#pragma once

#include <rfm_event/ev_internal.h>

/************************/
/*  Includes            */
/************************/
/****** Self ************************************************************************/
#define EVENT_BASE_SCENE    (0)

#define EV_ENTF_SIMPLEMAT       (0x0001) // Use SimpleDraw variant

#define EV_ENTF_NOFOG           (0x0002) // Draw with no fog & EasyDraw

/** if none of these lights are enabled, regular draw will be used **/
#define EV_ENTF_LIGHT1          (0x0004) // if multi light 1 is enabled
#define EV_ENTF_LIGHT2          (0x0008) // if multi light 2 is enabled
#define EV_ENTF_LIGHT3          (0x0010) // if multi light 3 is enabled
#define EV_ENTF_LIGHT4          (0x0020) // if multi light 4 is enabled

#define EV_ENTF_MODVOL          (0x0040) // entry is a modifier

#define EV_ENTF_REFLECT         (0x0080) // entry has reflection
#define EV_ENTF_BLARE           (0x0100) // entry has blare

#define EV_ENTF_FORCESIMPLE     (0x0200) // Force SimpleDraw, no MultiDraw

#define EV_ENTF_MULTILIGHT      (EV_ENTF_LIGHT1|EV_ENTF_LIGHT2|EV_ENTF_LIGHT3|EV_ENTF_LIGHT4)

typedef enum
{
    EV_ENTRY_TYPE_NONE,         // None
    EV_ENTRY_TYPE_DRAW,         // DrawObject
    EV_ENTRY_TYPE_MTN,          // DrawMotion
    EV_ENTRY_TYPE_SHAPE,        // DrawShape
    EV_ENTRY_TYPE_EASYNOFOG,    // EasyDrawObject
    EV_ENTRY_TYPE_MULTIDRAW,    // MultiDrawObject
    EV_ENTRY_TYPE_MULTIMTN,     // MultiDrawMotion
    EV_ENTRY_TYPE_MULTISHAPE,   // MultiDrawShape
    EV_ENTRY_TYPE_MODDRAW,      // ModDrawObject // unused?
    EV_ENTRY_TYPE_MODMTN,       // ModDrawMotion
}
EV_ENTRY_TYPE;

EV_ENTRY_TYPE
EventGetEntryType(const EventEntityData* pEntry);

void
EventDrawReflections(void);

void
EventLightSet(void);

void
EventLightSwitchSingle(void);

void
EventLightSwitchMulti(Uint32 attr);

void
Draw43Bars(void);
