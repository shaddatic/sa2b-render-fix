/*
*   Sonic Adventure Mod Tools (SA2B) - '/sonic/misc.h'
*
*   Contains anything that hasn't yet found a place elsewhere
*   Please don't add to this, it either goes somewhere or not in here
*
*   Contributors:
*     - SEGA - Sonic Team,
*     - Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC
*/
#pragma once

enum
{
    PLAYER_1,
    PLAYER_2
}

#define LastLevel DATA_REF(int16_t, 0x1934B84)

#define SelectedMissionCharacter    DATA_REF(char, 0x01D1BF05)
#define StageSelectLevelSelection   DATA_REF(char, 0x01D1BF08)

#define gsGameCameraMode DATA_REF(int, 0x01DD0194) // Unofficial name

#define GameTime DATA_REF(int, 0x01DEC62C)

#define TwoPlayerMode DATA_REF(bool, 0x0174AFDE)
