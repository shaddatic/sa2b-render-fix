/*
*   Sonic Adventure Mod Tools (SA2B) - '/magic/media.h'
*
*   Description:
*     Magic's MEDIA namespace.
*
*   Contributors:
*   - Magic Developers
*   - Shaddatic
*
*   Only for use with Sonic Adventure 2 for PC
*/
#ifndef H_MAGIC_MEDIA
#define H_MAGIC_MEDIA

#ifdef  __cplusplus

/************************/
/*  External Headers    */
/************************/
/****** Utility *********************************************************************/
#include <sa2b/util/cpp_old.h>  /* cppold::std::basic_string                        */

/************************/
/*  Media               */
/************************/
/****** MEDIA::Audio ****************************************************************/
namespace Magic::MEDIA
{
    enum AudioPlayParam
    {
        AUDIO_PLAY_DEFAULT,
        AUDIO_PLAY_LOOP,
        AUDIO_PLAY_AUTO_DESTROY,
    };

    enum AudioStat
    {
        AUDIO_STAT_ERROR = -1,
        AUDIO_STAT_CLOSED,
        AUDIO_STAT_OPENED,
        AUDIO_STAT_STOP,
        AUDIO_STAT_PREP,
        AUDIO_STAT_PLAYING,
        AUDIO_STAT_END,
        AUDIO_STAT_PAUSE,
    };

    struct AudioParam
    {

    };

    struct MC_Audio
    {
        struct vft_s
        {
            void          (__cdecl* Destructor       )( MC_Audio* self                                                                  );
            void          (__cdecl* Initialize       )( MC_Audio* self                                                                  );
            void          (__cdecl* Finalize         )( MC_Audio* self                                                                  );
            void          (__cdecl* Update           )( MC_Audio* self                                                                  );
            bool          (__cdecl* Open             )( MC_Audio* self, const cppold::std::basic_string<char>*, const AudioParam*, bool );
            bool          (__cdecl* OpenMem          )( MC_Audio* self, void*, int, const AudioParam*                                   );
            void          (__cdecl* Close            )( MC_Audio* self                                                                  );
            bool          (__cdecl* Play             )( MC_Audio* self, AudioPlayParam                                                  );
            bool          (__cdecl* Pause            )( MC_Audio* self                                                                  );
            bool          (__cdecl* Resume           )( MC_Audio* self                                                                  );
            bool          (__cdecl* Stop             )( MC_Audio* self                                                                  );
            float         (__cdecl* GetPlayTime      )( MC_Audio* self                                                                  );
            float         (__cdecl* GetTotalTime     )( MC_Audio* self                                                                  );
            float         (__cdecl* GetVolume        )( MC_Audio* self                                                                  );
            void          (__cdecl* SetVolume        )( MC_Audio* self, float                                                           );
            void          (__cdecl* SetPan           )( MC_Audio* self, float                                                           );
            float         (__cdecl* GetPan           )( MC_Audio* self                                                                  );
            void          (__cdecl* SetSpeed         )( MC_Audio* self, float                                                           );
            bool          (__cdecl* Set3DPosition    )( MC_Audio* self, float, float, float                                             );
            bool          (__cdecl* SetMinDistance   )( MC_Audio* self, float                                                           );
            bool          (__cdecl* SetMaxDistance   )( MC_Audio* self, float                                                           );
            bool          (__cdecl* SetDistanceFactor)( MC_Audio* self, float                                                           );
            AudioStat     (__cdecl* GetStat          )( MC_Audio* self                                                                  );
            AudioPlayParam(__cdecl* GetParam         )( MC_Audio* self                                                                  );
        }*vft;
    };

    struct MC_AudioSystem
    {
        struct vft_s
        {
            void     (__cdecl* Initialize    )( MC_AudioSystem* self, void*, void*                                              );
            void     (__cdecl* Finalize      )( MC_AudioSystem* self                                                            );
            void     (__cdecl* Update        )( MC_AudioSystem* self                                                            );
            MC_Audio*(__cdecl* CreateAudio   )( MC_AudioSystem* self, const cppold::std::basic_string<char>*, const AudioParam* );
            MC_Audio*(__cdecl* CreateAudio2  )( MC_AudioSystem* self                                                            );
            MC_Audio*(__cdecl* CreateAudioMem)( MC_AudioSystem* self, void*, int, const AudioParam*                             );
            bool     (__cdecl* DestroyAudio  )( MC_AudioSystem* self, MC_Audio*                                                 );
            void     (__cdecl* Destructor    )( MC_AudioSystem* self                                                            );
        }*vft;
    };
}

/****** MEDIA::Movie ****************************************************************/


#endif/*__cplusplus*/

#endif/*H_MAGIC_MEDIA*/
