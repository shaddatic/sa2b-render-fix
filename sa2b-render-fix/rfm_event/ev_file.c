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
#include <rf_eventinfo.h>           /* eventinfo                                                */

/****** Self ************************************************************************************/
#include <rfm_event/ev_internal.h>  /* parent & siblings                                        */

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
#define EvEffectInfo            DATA_REF(EV_EFF_INFO, 0x01FEFE20)

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

    c7 pc_buf[64];

    const size sz_buf = ARYLEN(pc_buf);

    EV_EFF_INFO* const p_eff_buffer = mtAlloc(EV_EFF_INFO, 5);

    EV_EFF_INFO* const p_eff_core = &p_eff_buffer[0];
    EV_EFF_INFO* const p_eff_msic = &p_eff_buffer[1];
    EV_EFF_INFO* const p_eff_lite = &p_eff_buffer[2];
    EV_EFF_INFO* const p_eff_lang = &p_eff_buffer[3];
    EV_EFF_INFO* const p_eff_spch = &p_eff_buffer[4];

    /** Load Event Files ************************************************************************/

    bool core_err = false; // if the '_c' file wasn't loaded

    // core file (_c/_0)
    {
        mtStrFormat(pc_buf, sz_buf, "e%04i_c.prs", EventNum);

        if ( LoadAndDecompressPrs(pc_buf, p_eff_core) >= 0 )
        {
            EV_ByteswapEffectInfo(p_eff_core);
        }
        else // error
        {
            core_err = true;

            RF_DbgInfo("Event file '%s' not found, falling back to 'e%04i_0.prs' and vanilla logic", pc_buf, EventNum);

            mtStrFormat(pc_buf, sz_buf, "e%04i_0.prs", EventNum);

            if ( LoadAndDecompressPrs(pc_buf, p_eff_core) >= 0 )
            {
                EV_ByteswapEffectInfo(p_eff_core);
            }
        }
    }
    // language/subtitle file (_j/1/2/3/4)
    {
        mtStrFormat(pc_buf, sz_buf, "e%04i_%c.prs", EventNum, LangFileChars[Language]);

        if ( LoadAndDecompressPrs(pc_buf, p_eff_lang) >= 0 )
        {
            EV_ByteswapEffectInfo(p_eff_lang);

            // copy language file data to fill in gaps left by '_c' not being loaded
            if ( core_err )
            {
                mtMemCopy( p_eff_core->sound, p_eff_lang->sound, sizeof(p_eff_lang->sound) );
            }
        }
    }
    // speech/voice file (_j/1/2/3/4)
    {
        if ( Language != Speech )
        {
            mtStrFormat(pc_buf, sz_buf, "e%04i_%c.prs", EventNum, LangFileChars[Speech]);

            if ( LoadAndDecompressPrs(pc_buf, p_eff_spch) >= 0 )
            {
                EV_ByteswapEffectInfo(p_eff_spch);
            }
        }
        else // if language matches speech mode, just copy language info
        {
            mtMemCopy( p_eff_spch->sound, p_eff_lang->sound, sizeof(p_eff_lang->sound) );
        }
    }
    // music/jingle file (_m)
    {
        mtStrFormat(pc_buf, sz_buf, "e%04i_m.prs", EventNum);

        if ( LoadAndDecompressPrs(pc_buf, p_eff_msic) >= 0 )
        {
            EV_ByteswapEffectInfo(p_eff_msic);
        }
        else // error
        {
            RF_DbgInfo("Event file '%s' not found, falling back to language info", pc_buf);

            mtMemCopy( p_eff_msic->sound, p_eff_lang->sound, sizeof(p_eff_lang->sound) );
        }
    }
    // light file (_l)
    {
        mtStrFormat(pc_buf, sz_buf, "e%04i_l.prs", EventNum);

        if ( LoadAndDecompressPrs(pc_buf, p_eff_lite) >= 0 )
        {
            EV_ByteswapEffectInfo(p_eff_lite);
        }
        else // error
        {
            RF_DbgInfo("Event file '%s' not found, falling back to core info", pc_buf);

            mtMemCopy( p_eff_lite->lights, p_eff_core->lights, sizeof(p_eff_core->lights) );
        }
    }

    /** Apply Files *****************************************************************************/

    // subtitles
    {
        mtMemCopy(EvEffectInfo.subtitle, p_eff_lang->subtitle, sizeof(EvEffectInfo.subtitle));
    }
    // sound info
    {
        int ix_snd = 0; // current sound entry index

        const size nb_snd = ARYLEN(EvEffectInfo.sound);

        // sound/staff control (core file)

        for ( int i = 0; i < nb_snd; ++i )
        {
            const EV_EFF_SOUND* p_sound = &p_eff_core->sound[i];

            if ( p_sound->frame == 0 )
            {
                continue;
            }

            if ( p_sound->snd_begin != 0xFF )
            {
                EvEffectInfo.sound[ix_snd++] = COPY_SOUND_DATA(*p_sound, snd_begin);
            }

            if ( p_sound->staff_ctrl != 0xFF )
            {
                EvEffectInfo.sound[ix_snd++] = COPY_SOUND_DATA(*p_sound, staff_ctrl);
            }
        }

        // music/jingle (music file)

        for ( int i = 0; i < nb_snd; ++i )
        {
            const EV_EFF_SOUND* p_sound = &p_eff_msic->sound[i];

            if ( p_sound->frame == 0 )
            {
                continue;
            }

            if ( p_sound->bgm[0] )
            {
                EvEffectInfo.sound[ix_snd] = (EV_EFF_SOUND){ DEF_SOUND_STRUC, .frame = p_sound->frame };

                mtMemCopy( EvEffectInfo.sound[ix_snd].bgm, p_sound->bgm, sizeof(p_sound->bgm) );

                ix_snd++;
            }

            if ( p_sound->jingle[0] )
            {
                EvEffectInfo.sound[ix_snd] = (EV_EFF_SOUND){ DEF_SOUND_STRUC, .frame = p_sound->frame };

                mtMemCopy( EvEffectInfo.sound[ix_snd].jingle, p_sound->jingle, sizeof(p_sound->jingle) );

                ix_snd++;
            }
        }

        // voice/speech info (language file)

        for ( int i = 0; i < nb_snd; ++i )
        {
            const EV_EFF_SOUND* p_sound = &p_eff_spch->sound[i];

            if ( p_sound->frame == 0 )
            {
                continue;
            }

            if ( p_sound->voice_num != -1 )
            {
                EvEffectInfo.sound[ix_snd++] = COPY_SOUND_DATA(*p_sound, voice_num);
            }
        }

        // end sound info

        for ( int i = ix_snd; i < nb_snd; ++i )
        {
            EvEffectInfo.sound[i] = (EV_EFF_SOUND){ DEF_SOUND_STRUC };
        }
    }
    // rest info (core/light file)
    {
        mtMemCopy( EvEffectInfo.screen    , p_eff_core->screen    , sizeof(EvEffectInfo.screen)     );
        mtMemCopy( EvEffectInfo.simpleptcl, p_eff_core->simpleptcl, sizeof(EvEffectInfo.simpleptcl) );

        // light info (light file)
        mtMemCopy( EvEffectInfo.lights    , p_eff_lite->lights    , sizeof(EvEffectInfo.lights)     );

        mtMemCopy( EvEffectInfo.blares    , p_eff_core->blares    , sizeof(EvEffectInfo.blares)     );
        mtMemCopy( EvEffectInfo.ptcls     , p_eff_core->ptcls     , sizeof(EvEffectInfo.ptcls)      );
        mtMemCopy( EvEffectInfo.overlays  , p_eff_core->overlays  , sizeof(EvEffectInfo.overlays)   );

        EvEffectInfo.sound[0].WaitVsyncCount = p_eff_core->sound[0].WaitVsyncCount;
    }

    mtFree(p_eff_buffer);
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
