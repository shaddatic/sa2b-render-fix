/*
*   Sonic Adventure Mod Tools (SA2B) - '/sonic/adx.h'
*
*   Description:
*     Contains functions for playing ADX files.
*
*   Contributors:
*     - SEGA - Sonic Team,
*     - Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC
*/
#ifndef H_SA2B_ADX
#define H_SA2B_ADX

EXTERN_START

/************************/
/*  Enums               */
/************************/
enum
{
    ADX_MD_OFF,
    ADX_MD_PLAY,
    ADX_MD_FADEIN,
    ADX_MD_FADEOUT,
    ADX_MD_PAUSE,
};

enum
{
    SERIFU_PRI_STAGE,       /* can't be overwritten                                 */
    SERIFU_PRI_STAGE2,      /* overwritten by STAGE                                 */
    SERIFU_PRI_NORMAL,      /* overwritten by STAGE, STAGE2, & NORMAL               */
    SERIFU_PRI_OTHER,       /* overwritten by STAGE, STAGE2, & OTHER                */
};

/************************/
/*  Structures          */
/************************/
typedef struct
{
    uint8_t mode;
    uint8_t pri;
    int num;
    int gap0[1];
    int status;
    void* pAdxt;
    void* pBuffer;
    void* pOtherBuf;
}
SERIF_WORK;

typedef struct
{
    char bgm_mode;
    char FadeInOut;
    int16_t once_mode;
    int bgm_next;       /* next mode */
    int volume;
    int status;
    int bgm_ready;
    char* bgm_name;
    char* once_next;    /* next once file name */
    char* once_name;    /* current once file name */
    void* pBuffer;
    SERIF_WORK serif[3];
}
ADX_WORK;

/************************/
/*  Data                */
/************************/
/****** ADX Task ********************************************************************/
#define ADXtaskP            DATA_REF(TASK*    , 0x01A55994)
#define ADXworkP            DATA_REF(ADX_WORK*, 0x01A55998)

/****** Voice Constants *************************************************************/
#define VOICE_COUNT         DATA_REF(int, 0x01A5599C) /* max 3                       */
#define VOICE_VOLUME        DATA_REF(int, 0x01A55990)

/************************/
/*  Functions           */
/************************/
/****** BGM *************************************************************************/
/*
*   Description:
*     Play an ADX file as the background music
*
*   Examples:
*     BGM_Play("chao_g_bgm_n.adx");
*
*   Parameters:
*     - fname   : name of the adx file, including '.adx'
*/
void    BGM_Play( const char* fname );
/*
*   Description:
*     Restart current background music
*/
void    BGM_Replay( void );
/*
*   Description:
*     Stop the background music
*/
void    BGM_Stop( void );
/*
*   Description:
*     Fade the background music out
*/
void    BGM_FadeOut( void );
/*
*   Description:
*     Fade the background music out
*/
void    BGM_FadeIn( void );
/*
*   Description:
*     Play an ADX file as the background music
*
*   Examples:
*     BGM_Volume(0); // Max volume
*
*   Parameters:
*     - vol     : volume of the background music from '0' to '-999'
*/
void    BGM_Volume( int32_t vol );
/*
*   Description:
*     Set an ADX file to the current active BGM file. Requires a call to
*   'BGM_Replay()' for the file to switch
*
*   Parameters:
*     - fname   : name of the adx file, including '.adx'
*/
void    BGM_SetFile( const char* fname );

/****** Jingle **********************************************************************/
/*
*   Description:
*     Temporarily stops the current BGM and plays a new ADX file to its end; on
*   ending, the current BGM is restarted. If the ADX file is endless (has loop
*   parameters), you must call 'Jingle_Stop' to simulate its end.
*
*   Parameters:
*     - fname   : name of the adx file, including '.adx'
*/
void    Jingle_Play( const char* fname );
/*
*   Description:
*     Stop the currently playing Jingle, and restart the BGM
*
*   Parameters:
*     - fname   : name of the adx file, including '.adx'
*/
void    Jingle_Stop( void );

/****** Voice ***********************************************************************/
/*
*   Description:
*     Play a voice line, せりふ, using index 'no' at a set priority. 'Serif_Play'
*   calls 'Serif_PlayPri' with a priority of 'NORMAL'. A maximum of 3 serifs slots
*   exist concurrently, if this limit is reached lower priority serifs are
*   overwritten or the voice line isn't played
*
*   Examples:
*     Serif_Play(1597);                      // "Too easy! Piece of cake!" Sonic, B Rank
*     Serif_PlayPri(SERIFU_PRI_STAGE, 1806); // "Attention all units! Suspect seen heading south. ..."
*
*   Parameters:
*     - pri     : play priority of voice line, eg. 'SERIF_PRI_...'
*     - no      : index of voice line
*
*   Returns:
*     The voice slot number used (0-2). -1 indicates no serif slots are available
*/
int32_t Serif_Play( int32_t no );
int32_t Serif_PlayPri( int32_t pri, int32_t no );
/*
*   Description:
*     Stop all voice lines
*/
void    Serif_Stop( void );
/*
*   Description:
*     Stop voice line in slot 'num'
*
*   Parameters:
*     - num     : slot to stop, as returned by 'Serif_Play' and 'Serif_PlayPri'
*/
void    Serif_StopNum( int32_t num );

/****** ADX *************************************************************************/
/*
*   Description:
*     Begin the ADX_TaskLoop TASK
*
*   Returns:
*     1 on success, 0 on error
*/
int32_t ADX_TaskInit( void );
/*
*   Description:
*     Close the ADX_TaskLoop TASK
*/
void    ADX_Close( void );

/************************/
/*  Function Ptrs       */
/************************/
#ifdef SAMT_INCL_FUNCPTRS
/** Function ptrs **/
#   define BGM_Replay_p             FUNC_PTR(void   , __cdecl, (void), 0x00442D90)
#   define BGM_Stop_p               FUNC_PTR(void   , __cdecl, (void), 0x00442F50)
#   define BGM_FadeOut_p            FUNC_PTR(void   , __cdecl, (void), 0x00443090)
#   define Jingle_Stop_p            FUNC_PTR(void   , __cdecl, (void), 0x004432D0)
#   define Serif_Stop_p             FUNC_PTR(void   , __cdecl, (void), 0x004431B0)
#   define ADX_TaskInit_p           FUNC_PTR(int32_t, __cdecl, (void), 0x00442490)

/** User-Function ptrs **/
#   define BGM_Volume_p             ((void*)0x00443030)
#   define BGM_SetFile_p            ((void*)0x00442CF0)
#   define Jingle_Play_p            ((void*)0x00443480)
#   define Serif_PlayPri_p          ((void*)0x00443130)
#   define Serif_StopNum_p          ((void*)0x00443200)

#endif/*SAMT_INCL_FUNCPTRS*/

EXTERN_END

#endif/*H_SA2B_ADX*/
