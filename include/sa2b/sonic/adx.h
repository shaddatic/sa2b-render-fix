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
    ADX_MD_OFF,                 /* no bgm                                           */
    ADX_MD_PLAY,                /* bgm playing                                      */
    ADX_MD_FADEIN,              /* bgm fade-in                                      */
    ADX_MD_FADEOUT,             /* bgm fade-out                                     */
    ADX_MD_PAUSE,               /* bgm paused                                       */
};

enum
{
    SERIFU_PRI_STAGE,           /* can't be overwritten                             */
    SERIFU_PRI_STAGE2,          /* overwritten by STAGE                             */
    SERIFU_PRI_NORMAL,          /* overwritten by STAGE, STAGE2, & NORMAL           */
    SERIFU_PRI_OTHER,           /* overwritten by STAGE, STAGE2, & OTHER            */
};

/************************/
/*  Structures          */
/************************/
typedef struct
{
    s8      mode;
    s8      pri;
    s32     num;
    s32     gap0[1];
    s32     status;
    void*   pAdxt;
    void*   pBuffer;
    void*   pOtherBuf;
}
SERIF_WORK;

typedef struct
{
    s8      bgm_mode;
    s8      FadeInOut;
    s16     once_mode;
    s32     bgm_next;           /* next mode                                        */
    s32     volume;
    s32     status;
    s32     bgm_ready;
    s8*     bgm_name;
    s8*     once_next;          /* next once file name                              */
    s8*     once_name;          /* current once file name                           */
    void*   pBuffer;
    SERIF_WORK serif[3];
}
ADX_WORK;

/************************/
/*  Data                */
/************************/
/****** ADX Task ********************************************************************/
#define ADXtaskP            DATA_REF(task*    , 0x01A55994)
#define ADXworkP            DATA_REF(ADX_WORK*, 0x01A55998)

/****** Voice Constants *************************************************************/
#define VOICE_COUNT         DATA_REF(s32, 0x01A5599C) /* max 3                       */
#define VOICE_VOLUME        DATA_REF(s32, 0x01A55990)

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
*     - pcAdx       : name of the adx file, including '.adx'
*/
void    BGM_Play( const char* pcAdx );
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
*     - vol         : volume of the background music from '0' to '-999'
*/
void    BGM_Volume( s32 vol );
/*
*   Description:
*     Set an ADX file to the current active BGM file. Requires a call to
*   'BGM_Replay()' for the file to switch
*
*   Parameters:
*     - pcAdx       : name of the adx file, including '.adx'
*/
void    BGM_SetFile( const char* pcAdx );

/****** Jingle **********************************************************************/
/*
*   Description:
*     Temporarily stops the current BGM and plays a new ADX file to its end; on
*   ending, the current BGM is restarted. If the ADX file is endless (has loop
*   parameters), you must call 'Jingle_Stop' to simulate its end.
*
*   Parameters:
*     - pcAdx       : name of the adx file, including '.adx'
*/
void    Jingle_Play( const char* pcAdx );
/*
*   Description:
*     Stop the currently playing Jingle, and restart the BGM
*/
void    Jingle_Stop( void );

/****** Voice ***********************************************************************/
/*
*   Description:
*     Play a voice line, せりふ, of index 'no'. A maximum of 3 serifs slots exist
*   concurrently, if this limit is reached lower priority serifs are overwritten or
*   the voice line isn't played
*
*   Notes:
*     - Calls 'Serif_PlayPri' with a priority of 'NORMAL'.
*
*   Examples:
*     Serif_Play(1597);                      // "Too easy! Piece of cake!" Sonic, B Rank
*
*   Parameters:
*     - no      : index of voice line
*
*   Returns:
*     The voice slot number used (0~2), or '-1' indicates no serif slots are available
*/
s32     Serif_Play( s32 no );
/*
*   Description:
*     Play a voice line, せりふ, using index 'no' at a set priority. A maximum of 3
*   serifs slots exist concurrently, if this limit is reached lower priority serifs
*   are overwritten or the voice line isn't played
*
*   Examples:
*     Serif_PlayPri(SERIFU_PRI_STAGE, 1806); // "Attention all units! Suspect seen heading south. ..."
*
*   Parameters:
*     - pri     : play priority of voice line, eg. 'SERIF_PRI_...'
*     - no      : index of voice line
*
*   Returns:
*     The voice slot number used (0~2), or '-1' indicates no serif slots are available
*/
s32     Serif_PlayPri( s32 pri, s32 no );
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
void    Serif_StopNum( s32 num );

/****** ADX *************************************************************************/
/*
*   Description:
*     Begin the ADX_TaskLoop Task
*
*   Returns:
*     1 on success, 0 on error
*/
s32     ADX_TaskInit( void );
/*
*   Description:
*     Close the ADX_TaskLoop Task
*/
void    ADX_Close( void );

/************************/
/*  Function Ptrs       */
/************************/
#ifdef SAMT_INCL_FUNCPTRS
/****** Function Pointers ***********************************************************/
#   define BGM_Replay_p             FUNC_PTR(void, __cdecl, (void), 0x00442D90)
#   define BGM_Stop_p               FUNC_PTR(void, __cdecl, (void), 0x00442F50)
#   define BGM_FadeOut_p            FUNC_PTR(void, __cdecl, (void), 0x00443090)
#   define Jingle_Stop_p            FUNC_PTR(void, __cdecl, (void), 0x004432D0)
#   define Serif_Stop_p             FUNC_PTR(void, __cdecl, (void), 0x004431B0)
#   define ADX_TaskInit_p           FUNC_PTR(s32 , __cdecl, (void), 0x00442490)

/****** Usercall Pointers ***********************************************************/
#   define BGM_Volume_p             ((void*)0x00443030)/* ###(EAX)                  */
#   define BGM_SetFile_p            ((void*)0x00442CF0)/* ###(EDI)                  */
#   define Jingle_Play_p            ((void*)0x00443480)/* ###(EBX)                  */
#   define Serif_PlayPri_p          ((void*)0x00443130)/* EAX(EDX, STK)             */
#   define Serif_StopNum_p          ((void*)0x00443200)/* ###(EAX)                  */

#endif/*SAMT_INCL_FUNCPTRS*/

EXTERN_END

#endif/*H_SA2B_ADX*/
