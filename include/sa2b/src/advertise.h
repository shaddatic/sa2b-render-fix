/*
*   Sonic Adventure Mod Tools (SA2B) - '/src/advertise.h'
*
*   ~~ Under Construction ~~
* 
*   Description:
*       Enums and data for the main menu system.
*
*   Contributors:
*   -   SEGA - Sonic Team,
*   -   Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC.
*/
#ifndef _SA2B_ADVERTISE_H_
#define _SA2B_ADVERTISE_H_

typedef enum
{
    ADVA_MODE_TITLE_MENU = 0x0,
    ADVA_MODE_Main = 0x1,
    ADVA_MODE_StorySelect = 0x2,
    ADVA_MODE_StageSelect = 0x3,
    ADVA_MODE_2P = 0x4,
    ADVA_MODE_Unknown_5 = 0x5,
    ADVA_MODE_OPTIONS = 0x6,
    ADVA_MODE_Unknown_7 = 0x7,
    ADVA_MODE_SND_TEST = 0x8,
    ADVA_MODE_FILE_SEL = 0x9,
    ADVA_MODE_CARTRACE = 0xA,
    ADVA_MODE_DownloadEventMaybe = 0xB,
    ADVA_MODE_BossAttack = 0xC,
    ADVA_MODE_Tutorial = 0xD,
    ADVA_MODE_Unknown_E = 0xE,
    ADVA_MODE_EMBLEMVIEW = 0xF,
    ADVA_MODE_2P_BTL = 0x10,
    ADVA_MODE_Unknown_11 = 0x11,
    ADVA_MODE_Unknown_12 = 0x12,
    ADVA_MODE_Unknown_13 = 0x13,
    ADVA_MODE_Unknown_14 = 0x14,
    ADVA_MODE_Controls = 0x15,
    ADVA_MODE_BonusVideo = 0x16,
    ADVA_MODE_HowToPlay = 0x17,
    ADVA_MODE_Unknown_18 = 0x18,
}
AdvaModeEnum;

#define AdvaMode        DataRef(int32_t, 0x01D7BB10)
#define AdvaSubMode     DataRef(int32_t, 0x01D7BB14)

#endif/*_SA2B_ADVERTISE_H_*/
