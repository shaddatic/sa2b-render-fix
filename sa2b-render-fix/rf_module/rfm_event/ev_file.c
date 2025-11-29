/********************************/
/*  Includes                    */
/********************************/
/****** SAMT ************************************************************************************/
#include <samt/core.h>              /* core                                                     */
#include <samt/memory.h>            /* memalloc                                                 */
#include <samt/writeop.h>           /* writecall                                                */
#include <samt/string.h>            /* strformat                                                */

/****** Ninja ***********************************************************************************/
#include <samt/ninja/ninja.h>       /* ninja                                                    */

/****** Game ***********************************************************************************/
#include <samt/sonic/game.h>        /* language/speech                                         */

/****** Render Fix ******************************************************************************/
#include <rf_core.h>                /* core                                                     */

/****** Self ************************************************************************************/
#include <rf_module/rfm_event/ev_internal.h>  /* parent & siblings                              */

/********************************/
/*  Macros                      */
/********************************/
/****** Sound Struct Vals ***********************************************************************/
#define DEF_SOUND_STRUC             .snd_begin = 0xFF, .staff_ctrl = 0xFF, .voice_num = -1

/****** Copy Sound Value ************************************************************************/
/*
*   Description:
*     Copy a single data value of one sound entry to another, keeping the other values as
*   default.
*
*   Parameters:
*     - d           : sound entry struct
*     - m           : struct member name
*/
#define COPY_SOUND_DATA(d, m)       (EV_EFF_SOUND){ DEF_SOUND_STRUC, .frame = (d).frame, .m = (d).m }

/********************************/
/*  Game Defs                   */
/********************************/
/****** Effect Data *****************************************************************************/
#define EvEffectInfo                DATA_REF(EV_EFF_INFO, 0x01FEFE20)

#define LargeFileBuffer             DATA_ARY(EV_EFF_INFO, 0x01EEFE20, [4])

/********************************/
/*  Data                        */
/********************************/
/****** Event Lang Names ************************************************************************/
static c7 LangFileChars[NUM_LANGUAGE] =
{
    [JAPANESE] = 'j',
    [ENGLISH]  = '1',
    [GERMAN]   = '2',
    [FRENCH]   = '3',
    [SPANISH]  = '4',
    [ITALIAN]  = '5',
};

/********************************/
/*  Source                      */
/********************************/
/****** Sound Struct Vals ***********************************************************************/
static int
LoadAndDecompressPrs(const c7* pcPrsFile, void* pDstAddr)
{
    static const pint LoadAndDecompressPrs_p = 0x00454980;

    int result;

    __asm
    {
        push            [pDstAddr]
        mov eax,        [pcPrsFile]

        call            LoadAndDecompressPrs_p

        add esp,        4

        mov [result],   eax
    }

    return result;
}

/****** Load Effect File ************************************************************************/
void
EV_LoadEffectFiles(void)
{
    RF_DbgInfo("Loading Event effect files...");

    c7 c_buf[64];

    const size sz_buf = ARYLEN(c_buf);

    EV_EFF_INFO* const p_core_buf = &LargeFileBuffer[0];
    EV_EFF_INFO* const p_file_buf = &LargeFileBuffer[1];

    /** Load Event Files ************************************************************************/

    // file info
    bool use_new_logic   = false; // if the '_c' file was loaded, so use new RF event file logic
    int  wait_vsync_val = 0;

    // structure info
    const size nb_snd = ARYLEN(EvEffectInfo.sound);

    int ix_cur_snd = 0;

    // core file (_c/_0)
    {
        mtStrFormat(c_buf, sz_buf, "e%04i_c.prs", EventNum);

        if ( LoadAndDecompressPrs(c_buf, p_core_buf) >= 0 )
        {
            use_new_logic = true;

            EV_ByteswapEffectInfo(p_core_buf, false);

            mtMemCopy( &EvEffectInfo, p_core_buf, sizeof(EvEffectInfo) );

            // copy sound init and staff control 'sound' data entries

            for ( int i = 0; i < nb_snd; ++i )
            {
                const EV_EFF_SOUND* p_sound = &p_core_buf->sound[i];

                if ( p_sound->frame == 0 ) continue;

                if ( p_sound->snd_begin  != 0xFF ) EvEffectInfo.sound[ix_cur_snd++] = COPY_SOUND_DATA(*p_sound, snd_begin);
                if ( p_sound->staff_ctrl != 0xFF ) EvEffectInfo.sound[ix_cur_snd++] = COPY_SOUND_DATA(*p_sound, staff_ctrl);
            }

            wait_vsync_val = p_core_buf->sound[0].WaitVsyncCount;
        }
        else // error, no '_c' file available! Use Vanilla logic (_0)
        {
            use_new_logic = false;

            RF_DbgInfo("Core Event file (_c) not found, falling back to vanilla logic");

            mtStrFormat(c_buf, sz_buf, "e%04i_0.prs", EventNum);

            if ( LoadAndDecompressPrs(c_buf, p_core_buf) >= 0 )
            {
                EV_ByteswapEffectInfo(p_core_buf, false);
            }

            mtMemCopy( &EvEffectInfo, p_core_buf, sizeof(EvEffectInfo) );
        }
    }

    // language/subtitle file (_j/1/2/3/4)
    {
        mtStrFormat(c_buf, sz_buf, "e%04i_%c.prs", EventNum, LangFileChars[Language]);

        if ( LoadAndDecompressPrs(c_buf, p_file_buf) >= 0 )
        {
            EV_ByteswapEffectInfo(p_file_buf, true);
        }

        mtMemCopy( EvEffectInfo.subtitle, p_file_buf->subtitle, sizeof(EvEffectInfo.subtitle) );

        if ( !use_new_logic )
        {
            // if the core file was not found, we need to get the core 'sound' data from the
            // language file.

            for ( int i = 0; i < nb_snd; ++i )
            {
                const EV_EFF_SOUND* p_sound = &p_file_buf->sound[i];

                if ( p_sound->frame == 0 ) continue;

                if ( p_sound->snd_begin  != 0xFF ) EvEffectInfo.sound[ix_cur_snd++] = COPY_SOUND_DATA(*p_sound, snd_begin);
                if ( p_sound->staff_ctrl != 0xFF ) EvEffectInfo.sound[ix_cur_snd++] = COPY_SOUND_DATA(*p_sound, staff_ctrl);
            }

            // and the vsync data
            wait_vsync_val = p_file_buf->sound[0].WaitVsyncCount;
        }
    }

    // speech/voice file (_j/1/2/3/4)
    {
        if ( Language != Speech )
        {
            mtStrFormat(c_buf, sz_buf, "e%04i_%c.prs", EventNum, LangFileChars[Speech]);
        
            if ( LoadAndDecompressPrs(c_buf, p_file_buf) >= 0 )
            {
                EV_ByteswapEffectInfo(p_file_buf, true);
            }
        }

        for ( int i = 0; i < nb_snd; ++i )
        {
            const EV_EFF_SOUND* restrict p_sound = &p_file_buf->sound[i];
        
            if ( p_sound->frame == 0 ) continue;
        
            if ( p_sound->voice_num != -1 ) EvEffectInfo.sound[ix_cur_snd++] = COPY_SOUND_DATA(*p_sound, voice_num);
        }
    }

    // music/jingle file (_m)
    {
        const EV_EFF_INFO* restrict p_src = p_file_buf;

        if ( use_new_logic )
        {
            mtStrFormat(c_buf, sz_buf, "e%04i_m.prs", EventNum);

            if ( LoadAndDecompressPrs(c_buf, p_file_buf) >= 0 )
            {
                EV_ByteswapEffectInfo(p_file_buf, true);
            }
            else // error
            {
                RF_DbgInfo("Music Event file (_m) not found, using core file data");

                p_src = p_core_buf;
            }
        }

        for ( int i = 0; i < nb_snd; ++i )
        {
            const EV_EFF_SOUND* restrict p_sound = &p_src->sound[i];

            if ( p_sound->frame == 0 ) continue;

            if ( p_sound->bgm[0] && p_sound->bgm[0] != 0xFF )
            {
                EvEffectInfo.sound[ix_cur_snd] = (EV_EFF_SOUND){ DEF_SOUND_STRUC, .frame = p_sound->frame };

                mtMemCopy( EvEffectInfo.sound[ix_cur_snd++].bgm, p_sound->bgm, sizeof(p_sound->bgm) );
            }

            if ( p_sound->jingle[0] && p_sound->jingle[0] != 0xFF )
            {
                EvEffectInfo.sound[ix_cur_snd] = (EV_EFF_SOUND){ DEF_SOUND_STRUC, .frame = p_sound->frame };

                mtMemCopy( EvEffectInfo.sound[ix_cur_snd++].jingle, p_sound->jingle, sizeof(p_sound->jingle) );
            }
        }
    }

    // light file (_l)
    if ( use_new_logic )
    {
        mtStrFormat(c_buf, sz_buf, "e%04i_l.prs", EventNum);

        if ( LoadAndDecompressPrs(c_buf, p_file_buf) >= 0 )
        {
            EV_ByteswapEffectInfo(p_file_buf, false);

            mtMemCopy( EvEffectInfo.lights, p_file_buf->lights, sizeof(EvEffectInfo.lights) );
        }
        else // error
        {
            RF_DbgInfo("Light Event file (_l) not found, using core file data");
        }
    }
    // end sound info

    RF_DbgExtraInfo("%i/512 Event sound entries used", ix_cur_snd);

    for ( int i = ix_cur_snd; i < nb_snd; ++i )
    {
        EvEffectInfo.sound[i] = (EV_EFF_SOUND){ DEF_SOUND_STRUC };
    }

    EvEffectInfo.sound[0].WaitVsyncCount = wait_vsync_val;
}

/****** Init ************************************************************************************/
__declspec(naked)
static void
___RetnFail(void)
{
    __asm
    {
        mov eax, -1
        retn
    }
}

void
EV_FileInit(void)
{
    WriteCall(0x005FFAF0, ___RetnFail); // kill all load file calls
    WriteCall(0x005FFB3C, ___RetnFail);
    WriteCall(0x005FFB69, ___RetnFail);
    WriteCall(0x005FFBEB, ___RetnFail);
    
    KillCall(0x005FFB8C); // stop byteswapping
    KillCall(0x005FFC0E);
    
    WriteNOP( 0x005FFB99, 0x005FFC79); // clear room for custom call
    WriteCall(0x005FFB99, EV_LoadEffectFiles);
}
