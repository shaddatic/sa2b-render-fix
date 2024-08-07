/*
*   Sonic Adventure Mod Tools (SA2B) - '/util/ml_settings.h'
*
*   Description:
*     SAMT mod loader settings utility header
*
*   Contributors:
*     - Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC
*/
#ifndef H_UTIL_MLSETTINGS
#define H_UTIL_MLSETTINGS

EXTERN_START

/************************/
/*  Enums               */
/************************/
/****** Mod Loader User Settings ****************************************************/
typedef enum
{
    ML_SCREEN_MD_WINDOWED,
    ML_SCREEN_MD_FULLSCREEN,
    ML_SCREEN_MD_BORDERLESS,
    ML_SCREEN_MD_CUSTOM,
}
ml_screenmode;

/************************/
/*  Structures          */
/************************/
/****** Mod Loader User Settings ****************************************************/
typedef struct
{
    /****** Mod Loader Version >= 9 *********************************************/
    struct
    {
        bool            console;    /* output debug to console                  */
        bool            screen;     /* output debug to screen text              */
        bool            file;       /* output debug to text file                */
        bool            crashdmp;   /* create crash dumps                       */
    }
    Debug;

    bool               pauseFocus; /* pause game when window is not in focus    */
    bool             noExitPrompt; /* don't prompt when closing window          */
    s32                 screenNum; /* display number                            */
    bool               borderless; /* use borderless window                     */
    bool               fullscreen; /* use fullscreen                            */
    bool                skipIntro; /* skip game intro                           */
    bool              noAsyncLoad; /* no asynchronous file loading              */
    s32                      resH; /* horizontal resolution                     */
    s32                      resV; /* vertical resolution                       */

    struct
    {
        s32 speech;                /* set speech language                       */
        s32 text;                  /* set text language                         */
    }
    Language;

    bool          useCustomWindow; /* use custom window size                    */
    s32             customWindowH; /* horizontal custom window size             */
    s32             customWindowV; /* vertical custom window size               */

    bool          resizableWindow; /* allow resizing of game window             */
    bool         fixedAspectRatio; /* deprecated, use 'screenStretch'           */
    bool               fpsLimiter; /* frame limiter                             */

    struct
    {
        s32            stage;       /* stage number to spawn into               */
        s32            player1;     /* player 1 character                       */
        s32            player2;     /* player 2 character                       */
        bool           setpos;      /* use custom spawn pos                     */
        s32            posX;        /* custom spawn position, X                 */
        s32            posY;        /* custom spawn position, Y                 */
        s32            posZ;        /* custom spawn position, Z                 */
        s32            angY;        /* custom spawn angle, Y                    */
        s32            event;       /* event number                             */
        s32            saveNum;     /* save number                              */
    }
    TestSpawn;

    bool              exVtxBuffer;  /* using extended vertex buffer             */

    bool                fixEnvMap;  /* environment map fix                      */
    bool            fixScreenFade;  /* screen fading fix                        */
    bool                 fixCECar;  /* iGPU city escape tram car fix            */
    bool             fixParticles;  /* iGPU particle fix                        */

    bool       keepAspectOnResize; /* deprecated, use 'screenStretch'           */
    ml_screenmode      screenMode; /* set screen mode                           */

    /****** Mod Loader Version >= 14 ********************************************/
    bool            noBorderImage; /* done use border image PNG                 */
    bool            screenStretch; /* allow stretching of the game              */
}
ml_settings;

/************************/
/*  Prototypes          */
/************************/
/****** Mod Loader User Settings ****************************************************/
/*
*   Description:
*     Get the Mod Loader settings structure.  The pointer will be constant for the
*   lifetime of the program.
*
*   Returns:
*     A pointer to the mod loader settings struct, or 'nullptr' if the Mod Loader
*   helper functions were not given or the Mod Loader version is < 9.
*/
const ml_settings* ML_GetSettings( void );

EXTERN_END

#endif/*H_UTIL_MLSETTINGS*/
