/*
*   Sonic Adventure Mod Tools (SA2B) - '/src/userconfig.h'
*
*   Contains structs and data related to the users config settings
*
*   Contributors:
*   -   SEGA - Sonic Team,
*   -   Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC.
*/
#ifndef _SA2B_USERCONFIG_H_
#define _SA2B_USERCONFIG_H_

/************************/
/*  Defines             */
/************************/
#define INPUTWAY_KEYBOARD   (0)
#define INPUTWAY_GAMEPAD    (1)

/************************/
/*  Structures          */
/************************/
typedef struct 
{
    int sub_4025E0;
}
UserConfig_vtable;

typedef struct 
{
    UserConfig_vtable* vtable;
    int Fullscreen;
    int Width;
    int Height;
    int RefreshRate;
    int Language;
    int Display;
    int Res;
    int Analytics;
    int ConfigLoaded;        // Always 0, possibly an oversight
    int ControlsLoaded;        // Only 0 if failed to load
    int InputWay_P1;
    int InputWay_P2;
    int Vibrate_P1;
    int Vibrate_P2;
    char gap_38[447];
    char field_1FB;
}
UserConfig;

/************************/
/*  Data                */
/************************/
#define gpUserConfig    DataRef(UserConfig*, 0x1AF19EC)

#endif /* _SA2B_USERCONFIG_H_ */
