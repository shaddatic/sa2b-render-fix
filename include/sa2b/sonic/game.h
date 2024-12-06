/*
*   Sonic Adventure Mod Tools (SA2B) - '/sonic/game.h'
*
*   ~~ Under Construction ~~
* 
*   Description:
*       Contains data and functions related to core game elements.
*
*   Contributors:
*     - SEGA - Sonic Team,
*     - Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC
*/
#ifndef _SA2B_GAME_H_
#define _SA2B_GAME_H_

/************************/
/*  Enums               */
/************************/
/****** Global Mode *****************************************************************/
enum /* ulGlobalMode */
{
    MD_START,           /* startup the game from boot                               */
    MD_TITLE_INIT,      /* begin title sequence                                     */
    MD_TITLE,           /* start advertise menu                                     */
    MD_SELECTPLAYER,    /* unused sa1 mode, best guess                    (missing) */
    MD_ACTION_INIT,     /* begin gameplay/action                                    */
    MD_ACTION,          /* gameplay/action                                          */
    MD_ACTION_NEXT,     /* moving stage outside SeqCtrl, eg. to Chao World or in 2P */
    MD_EVENT_INIT,      /* init event                                               */
    MD_EVENT,           /* event                                                    */
    MD_TRIAL_INIT,      /* begin gameplay demo                                      */
    MD_TRIAL,           /* title screen gameplay demo                               */
    MD_SEQCTRL_INIT,    /* begin sequence control                         (missing) */
    MD_SEQCTRL,         /* sequence control                                         */
    MD_ADVERTISE_INIT,  /* init advertise menus                                     */
    MD_ADVERTISE,       /* advertise menus                                          */
    MD_ENDING_INIT,     /* init ending                                              */
    MD_ENDING,          /* ending                                                   */
    MD_EMBLEMGET_INIT,  /* init emblem get screen                                   */
    MD_EMBLEMGET,       /* emblem get screen                                        */
    MD_MCWARN_INIT,     /* begin memory card warning                                */
    MD_MCWARN,          /* warn there's no memory card                              */
    MD_LOGO_INIT,       /* begin startup logos                                      */
    MD_LOGO,            /* startup logos                                            */
    MD_TVSETTING_INIT,  /* begin TV setting                                (unused) */
    MD_TVSETTING,       /* progressive scan select screen                  (unused) */
    MD_TVSETTING_END,   /* end TV setting, same as 'TITLE_INIT'            (unused) */
    MD_PAL60_INIT,      /* begin PAL60                                    (missing) */
    MD_PAL60,           /* PAL60 select screen                            (missing) */
    NUM_MODE,
};

enum /* ssGameMode */
{
    MD_GAME_NONE,                   /* not currently in-game (eg. in menu or event) */
    MD_GAME_INIT,                   /* stage loading                                */
    MD_GAME_FADEIN = 0x07,          /* screen fading in                             */
    MD_GAME_FADEOUT_CLEAR = 0x08,   /* screen fading out after clearing stage       */
    MD_GAME_FADEOUT_MISS,
    MD_GAME_FADEOUT_RESTART = 0x0D, /* screen fading out for restart                */
    MD_GAME_MAIN  = 0x10,           /* game playing as normal                       */
    MD_GAME_PAUSE = 0x11,           /* game paused                                  */
    NUM_GAMEMD = 0x32,
};

enum
{
    JAPANESE,
    ENGLISH,
    GERMAN,
    FRENCH,
    SPANISH,
    ITALIAN,
    NUM_LANGUAGE,
};

/****** Stage Number ****************************************************************/
enum
{
    STAGE_BASICTEST,            /* Basic Test                                       */
    STAGE_KNUCKLESTEST,         /* Knuckles Test                                    */
    STAGE_SONICTEST,            /* Sonic Test                                       */

    STAGE_JUNGLE,               /* Green Forest                                (JG) */
    STAGE_FOGJUNGLE,            /* White Jungle                                (FG) */
    STAGE_PUMPKIN,              /* Pumpkin Hill                                (PP) */
    STAGE_MOUNTAIN,             /* Sky Rail                                    (PM) */
    STAGE_COALMINE,             /* Aquatic Mine                                (CM) */
    STAGE_SECURITYHALL,         /* Security Hall                               (SH) */
    STAGE_TAILSPRISON,          /* Prison Lane                                 (PR) */
    STAGE_METALHARBOR,          /* Metal Harbor                                (MH) */
    STAGE_PRISON,               /* Iron Gate                                   (RN) */
    STAGE_WEAPONSBED,           /* Weapons Bed                                 (WB) */
    STAGE_CITYESCAPE,           /* City Escape                                 (CE) */
    STAGE_HIGHWAY,              /* Radical Highway                             (RH) */
    STAGE_WEAPONSBED_2P,        /* Weapons Bed 2P                             (WB2) */
    STAGE_WILDCANYON,           /* Wild Canyon                                 (WC) */
    STAGE_MISSION,              /* Mission Street                              (MS) */
    STAGE_DRYLAGOON,            /* Dry Lagoon                                  (DL) */
    STAGE_SONICVSSHADOW,        /* Sonic vs Shadow 1                                */
    STAGE_EWVSTW,               /* Tails vs Eggman 1                                */
    STAGE_SANDOCEAN,            /* Sand Ocean                                  (SO) */
    STAGE_CRAZYGADGET,          /* Crazy Gadget                                (CG) */
    STAGE_HIDDENBASE,           /* Hidden Base                                 (HB) */
    STAGE_ETERNALENGINE,        /* Eternal Engine                              (EE) */
    STAGE_DEATHCHAMBER,         /* Death Chamber                               (DC) */
    STAGE_EGGQUATER,            /* Egg Quaters                                 (EQ) */
    STAGE_LOSTCOLONY,           /* Lost Colony                                 (LC) */
    STAGE_PYRAMIDCAVE,          /* Pyramid Cave                                (PC) */
    STAGE_EWVSTW2,              /* Tails vs Eggman 2                                */
    STAGE_FINALRUSH,            /* Final Rush                                  (FR) */
    STAGE_GREENHILL,            /* Green Hill                                  (GH) */
    STAGE_METEORHERD,           /* Meteor Herd                                 (MD) */
    STAGE_KNUCKLESVSROUGE,      /* Knuckles vs Rouge                                */
    STAGE_CANNONSCORESONIC,     /* Cannons Core: Sonic                         (CC) */
    STAGE_CANNONSCOREEGGMAN,    /* Cannons Core: Eggman                        (CC) */
    STAGE_CANNONSCORETAILS,     /* Cannons Core: Tails                         (CC) */
    STAGE_CANNONSCOREROUGE,     /* Cannons Core: Rouge                        (CC2) */
    STAGE_CANNONSCOREKNUCKLES,  /* Cannons Core: Knuckles                      (CC) */
    STAGE_MISSION_2P,           /* Mission Street 2P                          (MS2) */
    STAGE_FINALCHASE,           /* Final Chase                                 (FC) */
    STAGE_WILDCANYON_2P,        /* Wild Canyon 2P                             (WC2) */
    STAGE_SONICVSSHADOW2,       /* Sonic vs Shadow 2                                */
    STAGE_COSMICWALL,           /* Cosmic Wall                                 (CW) */
    STAGE_MADSPACE,             /* Mad Space                                   (MS) */
    STAGE_SANDOCEAN_2P,         /* Sand Ocean                                 (SO2) */

    STAGE_DRYLAGOON_2P,         /* Dry lagoon 2P                              (DL2) */
    STAGE_SHORTPYRAMID_2P,      /* Pyramid Race                                     */
    STAGE_HIDDENBASE_2P,        /* Hidden Base 2P                                   */
    STAGE_AQUATICMINE_2P,       /* Pool Quest                                       */
    STAGE_MADSPACE_2P,          /* Mad Space 2P                                     */
    STAGE_SHORTDECK_2P,         /* Deck Race                                        */
    STAGE_SHORTCITY_2P,         /* Downtown Race                                    */
    STAGE_COSMICWALL_2P,        /* Cosmic Wall 2P                                   */
    STAGE_PYRAMIDCAVE_2P,       /* Grind Race                                       */
    STAGE_LOSTCOLONY_2P,        /* Lost Colony 2P                                   */
    STAGE_ETERNALENGINE_2P,     /* Eternal Engine 2P                                */
    STAGE_METALHARBOR_2P,       /* Metal Harbor 2P                                  */
    STAGE_IRONGATE_2P,          /* Iron Gate 2P                                (I2) */
    STAGE_DEATHCHAMBER_2P,      /* Death Chamber 2P                           (DC2) */

    STAGE_B_BIGFOOT       = 60, /* Boss Big Foot                                    */
    STAGE_B_HOTSHOT,            /* Boss Hot Shot                                    */
    STAGE_B_FDOG,               /* Boss Flying Dog                                  */
    STAGE_B_BIGBOGY,            /* Boss King Boom Boo                               */
    STAGE_B_GOLEM,              /* Boss Egg Golem                                   */
    STAGE_B_LAST1,              /* Boss Biolizard                                   */
    STAGE_B_LAST2,              /* Boss Biohazard                                   */
    STAGE_B_GOLEM_E,            /* Boss Egg Golem Eggman                            */

    STAGE_CART            = 70, /* Route 101/280                                    */
    STAGE_CARTMINI,             /* Cart Minigames Beginner/Standard/Expert          */

    STAGE_CHAOWORLD       = 90, /* Chao World                                       */
};

enum // uc2PVSMode
{
    MD_2PVS_1PLAYER,            /* single-player                                    */
    MD_2PVS_BESTOF3,            /* best of 3 rounds                                 */
    MD_2PVS_BESTOF1,            /* single battle                                    */
};

/************************/
/*  Data                */
/************************/
#define ulGlobalMode        DATA_REF(uint32_t, 0x0174B040)
#define ulNextGlobalMode    DATA_REF(uint32_t, 0x0174B044)

#define ssGameMode          DATA_REF(int16_t , 0x01934BE0)

#define ssGameModeChange    DATA_REF(int16_t , 0x01A558A4)

#define ssLastStageNumber   DATA_REF(int16_t , 0x01934B84)

#define ssStageNumber       DATA_REF(int16_t , 0x01934B70)
#define ucMissionNumber     DATA_REF(uint8_t , 0x0174AFE3)

#define uc2PVSMode          DATA_REF(u8      , 0x0174AFDE)

#define Language            DATA_REF(int8_t  , 0x0174AFD1)
#define Speech              DATA_REF(int8_t  , 0x0174AFD2)

#define ucPauseSelect       DATA_REF(uint8_t , 0x01933EB1)

#define bPauseDisable       DATA_REF(int8_t  , 0x0174AFD6)

#define pause_flg           DATA_REF(int8_t  , 0x0174AFD7)

/************************/
/*  Functions           */
/************************/
EXTERN_START
void    RestartStageWithFadeOut( void );

void    PauseEnable( void );
void    PauseDisable( void );

b32     ChkPause( void );

EXTERN_END

#endif/*_SA2B_GAME_H_*/
