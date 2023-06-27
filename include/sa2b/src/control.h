#pragma once

#define Buttons_R 0x010000
#define Buttons_L 0x020000
#define Buttons_A 0x04
#define Buttons_B 0x02
#define Buttons_Start 0x08
#define Buttons_Y 0x0200
#define Buttons_Up 0x10
#define Buttons_Down 0x20
#define Buttons_Left 0x40
#define Buttons_Right 0x80

#include <sa2b/ninja/ninjapad.h>

DataAry(bool, ControllerEnabled, 0x174AFFF, [2]); // Toggle controller movement for a player.

DataAry(PDS_PERIPHERAL, ControllersRaw, 0x1A52918, [4]); // 4
DataAry(PDS_PERIPHERAL, perG, 0x1DEFC00, [4]); // 4

DataRef(bool, ucInputStatus, 0x0174AFFE);
DataRef(bool, ssPauseDisable, 0x0174AFD6);

inline void PauseEnable()
{
	ssPauseDisable = false;
}

inline void PauseDisable()
{
	ssPauseDisable = true;
}

inline void PadReadOn()
{
	ucInputStatus = true;
}

inline void PadReadOff()
{
	ucInputStatus = false;
}