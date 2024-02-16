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

enum
{
    PLAYER_1,
    PLAYER_2
}

#define LastLevel DataRef(int16_t, 0x1934B84)

#define SelectedMissionCharacter    DataRef(char, 0x01D1BF05)
#define StageSelectLevelSelection   DataRef(char, 0x01D1BF08)

#define gsGameCameraMode DataRef(int, 0x01DD0194) // Unofficial name

#define GameTime DataRef(int, 0x01DEC62C)

#define TwoPlayerMode DataRef(bool, 0x0174AFDE)
