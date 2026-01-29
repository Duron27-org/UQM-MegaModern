//Copyright Paul Reiche, Fred Ford. 1992-2002

/*
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#ifndef LIBS_SNDLIB_H_
#define LIBS_SNDLIB_H_

#include "port.h"
#include "libs/strlib.h"

#if 0 //defined(__cplusplus)
extern "C" {
#endif

typedef STRING_TABLE SOUND_REF;
typedef STRING SOUND;
// SOUNDPTR is really a TFB_SoundSample**
typedef void *SOUNDPTR;

typedef struct soundposition
{
	bool positional;
	int x, y;
} SoundPosition;

#define InitSoundResources InitStringTableResources
#define CaptureSound CaptureStringTable
#define ReleaseSound ReleaseStringTable
#define GetSoundRef GetStringTable
#define GetSoundCount GetStringTableCount
#define GetSoundIndex GetStringTableIndex
#define SetAbsSoundIndex SetAbsStringTableIndex
#define SetRelSoundIndex SetRelStringTableIndex

extern SOUNDPTR GetSoundAddress (SOUND sound);

typedef struct tfb_soundsample TFB_SoundSample;
typedef TFB_SoundSample **MUSIC_REF;

extern bool InitSound (int argc, char *argv[]);
extern void UninitSound (void);
extern SOUND_REF LoadSoundFile (const char *pStr);
extern MUSIC_REF LoadMusicFile (const char *pStr);
extern bool InstallAudioResTypes (void);
extern SOUND_REF LoadSoundInstance (RESOURCE res);
extern MUSIC_REF LoadMusicInstance (RESOURCE res);
extern bool DestroySound (SOUND_REF SoundRef);
extern bool DestroyMusic (MUSIC_REF MusicRef);

#define MAX_CHANNELS 8
#define MAX_VOLUME 255
#define NORMAL_VOLUME 160
#define MUTE_VOLUME 0

#define FIRST_SFX_CHANNEL  0
#define MIN_FX_CHANNEL     1
#define NUM_FX_CHANNELS    4
#define LAST_SFX_CHANNEL   (MIN_FX_CHANNEL + NUM_FX_CHANNELS - 1)
#define NUM_SFX_CHANNELS   (MIN_FX_CHANNEL + NUM_FX_CHANNELS)

extern void PLRPlaySong (MUSIC_REF MusicRef, bool Continuous, uqm::BYTE
		Priority);
extern void PLRStop (MUSIC_REF MusicRef);
extern bool PLRPlaying (MUSIC_REF MusicRef);
extern void PLRSeek (MUSIC_REF MusicRef, uqm::DWORD pos);
extern void PLRPause (MUSIC_REF MusicRef);
extern void PLRResume (MUSIC_REF MusicRef);
extern void snd_PlaySpeech (MUSIC_REF SpeechRef);
extern void snd_StopSpeech (void);
extern void PlayChannel (uqm::COUNT channel, SOUND snd, SoundPosition pos,
		void *positional_object, unsigned char priority);
extern bool ChannelPlaying (uqm::COUNT Channel);
extern void * GetPositionalObject (uqm::COUNT channel);
extern void SetPositionalObject (uqm::COUNT channel, void *positional_object);
extern void UpdateSoundPosition (uqm::COUNT channel, SoundPosition pos);
extern void StopChannel (uqm::COUNT Channel, uqm::BYTE Priority);
extern void SetMusicVolume (uqm::COUNT Volume);
extern void SetChannelVolume (uqm::COUNT Channel, uqm::COUNT Volume, uqm::BYTE
		Priority);

extern void StopSound (void);
extern bool SoundPlaying (void);

extern uqm::DWORD PLRGetPos (void);

extern void WaitForSoundEnd (uqm::COUNT Channel);
#define TFBSOUND_WAIT_ALL ((uqm::COUNT)~0)

extern uqm::DWORD FadeMusic (uqm::BYTE end_vol, uqm::SIZE TimeInterval);
extern uqm::BYTE GetCurrMusicVol (void);

// For music resume option
typedef struct music_position
{
	uqm::DWORD filename_hash;
	uqm::DWORD position;
	uqm::DWORD last_played;
} MUSIC_POSITION;

extern void SetMusicPosition (void);
extern bool OkayToResume (void);
extern uqm::DWORD GetMusicPosition (void);
extern void ResetMusicResume (void);

static inline void
print_mp (const MUSIC_POSITION mp)
{
	printf ("filename_hash: 0x%X, position: %d, last_played: %d\n",
		mp.filename_hash, mp.position, mp.last_played);
}

static inline void
print_mp_array (const MUSIC_POSITION mp_array[], const uqm::COUNT num_items)
{
	uqm::COUNT i;

	//system ("cls");
	printf ("--------------------\n\n");
	for (i = num_items; i > 0; --i)
	{
		printf ("Index %d -> ", i);
		print_mp (mp_array[i]);
	}
	printf ("Index 0 -> ");
	print_mp (mp_array[0]);
	printf ("\n--------------------\n\n");
}

#if 0 //defined(__cplusplus)
}
#endif

#endif /* LIBS_SNDLIB_H_ */

