/*
*	Magic audio stuff
*
*/

#ifndef _MAGIC_AUDIO_H_
#define _MAGIC_AUDIO_H_

namespace Magic::MEDIA
{
	struct MC_Audio;

	const struct AudioParam
	{

	};

	enum AudioPlayParam : uint32
	{
		AUDIO_PLAY_DEFAULT = 0x0,
		AUDIO_PLAY_LOOP = 0x1,
		AUDIO_PLAY_AUTO_DESTROY = 0x2,
	};

	enum AudioStat : uint32
	{
		AUDIO_STAT_CLOSED = 0x0,
		AUDIO_STAT_OPENED = 0x1,
		AUDIO_STAT_STOP = 0x2,
		AUDIO_STAT_PREP = 0x3,
		AUDIO_STAT_PLAYING = 0x4,
		AUDIO_STAT_END = 0x5,
		AUDIO_STAT_PAUSE = 0x6,
		AUDIO_STAT_ERROR = 0xFFFFFFFF,
	};

	struct /*VFT*/ MC_Audio_vtbl
	{
		void(__thiscall* dest_MC_Audio)(MC_Audio* ths);
		void(__thiscall* Initialize)(MC_Audio* ths);
		void(__thiscall* Finalize)(MC_Audio* ths);
		void(__thiscall* Update)(MC_Audio* ths);
		bool(__thiscall* Open)(MC_Audio* ths, void*, const Magic::MEDIA::AudioParam*, bool);
		bool(__thiscall* OpenMem)(MC_Audio* ths, void*, int, const Magic::MEDIA::AudioParam*);
		void(__thiscall* Close)(MC_Audio* ths);
		bool(__thiscall* Play)(MC_Audio* ths, Magic::MEDIA::AudioPlayParam);
		bool(__thiscall* Pause)(MC_Audio* ths);
		bool(__thiscall* Resume)(MC_Audio* ths);
		bool(__thiscall* Stop)(MC_Audio* ths);
		float(__thiscall* GetPlayTime)(MC_Audio* ths);
		float(__thiscall* GetTotalTime)(MC_Audio* ths);
		float(__thiscall* GetVolume)(MC_Audio* ths);
		void(__thiscall* SetVolume)(MC_Audio* ths, float);
		void(__thiscall* SetPan)(MC_Audio* ths, float);
		float(__thiscall* GetPan)(MC_Audio* ths);
		void(__thiscall* SetSpeed)(MC_Audio* ths, float);
		bool(__thiscall* Set3DPosition)(MC_Audio* ths, float, float, float);
		bool(__thiscall* SetMinDistance)(MC_Audio* ths, float);
		bool(__thiscall* SetMaxDistance)(MC_Audio* ths, float);
		bool(__thiscall* SetDistanceFactor)(MC_Audio* ths, float);
		Magic::MEDIA::AudioStat(__thiscall* GetStat)(MC_Audio* ths);
		Magic::MEDIA::AudioPlayParam(__thiscall* GetParam)(MC_Audio* ths);
	};

	struct MC_Audio
	{
		MC_Audio_vtbl* __vftable /*VFT*/;
	};
}

#endif /* _MAGIC_AUDIO_H_ */