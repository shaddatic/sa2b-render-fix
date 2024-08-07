/*
*   Sonic Adventure Mod Tools (SA2B) - '/sonic/advertise.h'
*
*   ~~ Under Construction ~~
* 
*   Description:
*       Enums and data for the main menu system.
*
*   Contributors:
*     - SEGA - Sonic Team,
*     - Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC
*/
#ifndef _SA2B_ADVERTISE_H_
#define _SA2B_ADVERTISE_H_

typedef enum
{
    ADVA_MODE_TITLE_MENU,
    ADVA_MODE_Main,
    ADVA_MODE_StorySelect,
    ADVA_MODE_StageSelect,
    ADVA_MODE_2P,
    ADVA_MODE_Unknown_5,
    ADVA_MODE_OPTIONS,
    ADVA_MODE_Unknown_7,
    ADVA_MODE_SND_TEST,
    ADVA_MODE_FILE_SEL,
    ADVA_MODE_CARTRACE,
    ADVA_MODE_DownloadEventMaybe,
    ADVA_MODE_BossAttack,
    ADVA_MODE_Tutorial,
    ADVA_MODE_Unknown_E,
    ADVA_MODE_EMBLEMVIEW,
    ADVA_MODE_2P_BTL,
    ADVA_MODE_Unknown_11,
    ADVA_MODE_Unknown_12,
    ADVA_MODE_Unknown_13,
    ADVA_MODE_Unknown_14,
    ADVA_MODE_Controls,
    ADVA_MODE_BonusVideo,
    ADVA_MODE_HowToPlay,
    ADVA_MODE_Unknown_18,
}
AdvaModeEnum;

#define AdvaMode        DATA_REF(int32_t, 0x01D7BB10)
#define AdvaSubMode     DATA_REF(int32_t, 0x01D7BB14)

#endif/*_SA2B_ADVERTISE_H_*/
