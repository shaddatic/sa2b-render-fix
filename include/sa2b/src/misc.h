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

DataRef(sint16, LastLevel, 0x1934B84);

DataRef(char, SelectedMissionCharacter, 0x1D1BF05);
DataRef(char, StageSelectLevelSelection, 0x1D1BF08);

DataRef(int, gsGameCameraMode, 0x01DD0194); // Unofficial name

DataRef(int, GameTime, 0x01DEC62C);

DataRef(int, GameMode, 0x174B040);
DataRef(int, NextGameMode, 0x174B044);

DataRef(bool, TwoPlayerMode, 0x174AFDE);

DataRef(int, CurrentMenu, 0x1D7BB10);
DataRef(int, CurrentSubMenu, 0x1D7BB14);