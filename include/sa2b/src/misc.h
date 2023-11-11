/*
*   Sonic Adventure Mod Tools (SA2B) - '/src/misc.h'
*
*   Contains anything that hasn't yet found a place elsewhere
*   Please don't add to this, it either goes somewhere or not in here
*
*   Contributors:
*   -   SEGA - Sonic Team,
*   -   Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC.
*/
#pragma once

enum Menus
{
    Menus_TitleScreen = 0x0,
    Menus_Main = 0x1,
    Menus_StorySelect = 0x2,
    Menus_StageSelect = 0x3,
    Menus_Old2PBattle = 0x4,
    Menus_Unknown_5 = 0x5,
    Menus_Settings = 0x6,
    Menus_Unknown_7 = 0x7,
    Menus_SoundTest = 0x8,
    Menus_FileSelect = 0x9,
    Menus_Kart = 0xA,
    Menus_DownloadEventMaybe = 0xB,
    Menus_BossAttack = 0xC,
    Menus_Tutorial = 0xD,
    Menus_Unknown_E = 0xE,
    Menus_Emblems = 0xF,
    Menus_Battle = 0x10,
    Menus_Unknown_11 = 0x11,
    Menus_Unknown_12 = 0x12,
    Menus_Unknown_13 = 0x13,
    Menus_Unknown_14 = 0x14,
    Menus_Controls = 0x15,
    Menus_BonusVideo = 0x16,
    Menus_HowToPlay = 0x17,
    Menus_Unknown_18 = 0x18,
};

#define LastLevel DataRef(sint16, 0x1934B84)

#define SelectedMissionCharacter DataRef(char, 0x01D1BF05)
#define StageSelectLevelSelection DataRef(char, 0x01D1BF08)

#define gsGameCameraMode DataRef(int, 0x01DD0194) // Unofficial name

#define GameTime DataRef(int, 0x01DEC62C)

#define GameMode DataRef(int, 0x0174B040)
#define NextGameMode DataRef(int, 0x0174B044)

#define TwoPlayerMode DataRef(bool, 0x0174AFDE)

#define CurrentMenu DataRef(int, 0x01D7BB10)
#define CurrentSubMenu DataRef(int, 0x01D7BB14)