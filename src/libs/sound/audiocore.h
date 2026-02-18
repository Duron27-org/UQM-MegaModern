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

/* Audio Core API (derived from OpenAL)
 */

#ifndef LIBS_SOUND_AUDIOCORE_H_
#define LIBS_SOUND_AUDIOCORE_H_

#include "config.h"
#include "types.h"
#include "libs/sound/audiocoredefs.h"



extern AudioDriverType snddriver;
extern AudioFlags soundflags;

typedef struct
{
	/* General */
	void (*Uninitialize)(void);
	sint32 (*GetError)(void);
	AudioDriverType driverID;
	sint32 EnumLookup[audio_ENUM_SIZE];

	/* Sources */
	void (*GenSources)(uint32 n, audio_Object* psrcobj);
	void (*DeleteSources)(uint32 n, audio_Object* psrcobj);
	bool (*IsSource)(audio_Object srcobj);
	void (*Sourcei)(audio_Object srcobj, audio_SourceProp pname,
					audio_IntVal value);
	void (*Sourcef)(audio_Object srcobj, audio_SourceProp pname,
					float value);
	void (*Sourcefv)(audio_Object srcobj, audio_SourceProp pname,
					 float* value);
	void (*GetSourcei)(audio_Object srcobj, audio_SourceProp pname,
					   audio_IntVal* value);
	void (*GetSourcef)(audio_Object srcobj, audio_SourceProp pname,
					   float* value);
	void (*SourceRewind)(audio_Object srcobj);
	void (*SourcePlay)(audio_Object srcobj);
	void (*SourcePause)(audio_Object srcobj);
	void (*SourceStop)(audio_Object srcobj);
	void (*SourceQueueBuffers)(audio_Object srcobj, uint32 n,
							   audio_Object* pbufobj);
	void (*SourceUnqueueBuffers)(audio_Object srcobj, uint32 n,
								 audio_Object* pbufobj);

	/* Buffers */
	void (*GenBuffers)(uint32 n, audio_Object* pbufobj);
	void (*DeleteBuffers)(uint32 n, audio_Object* pbufobj);
	bool (*IsBuffer)(audio_Object bufobj);
	void (*GetBufferi)(audio_Object bufobj, audio_BufferProp pname,
					   audio_IntVal* value);
	void (*BufferData)(audio_Object bufobj, uint32 format, void* data,
					   uint32 size, uint32 freq);
} audio_Driver;


/* Initialization */
sint32 initAudio(sint32 driver, sint32 flags);
void unInitAudio(void);

/* General */
sint32 audio_GetError(void);

/* Sources */
void audio_GenSources(uint32 n, audio_Object* psrcobj);
void audio_DeleteSources(uint32 n, audio_Object* psrcobj);
bool audio_IsSource(audio_Object srcobj);
void audio_Sourcei(audio_Object srcobj, audio_SourceProp pname,
				   audio_IntVal value);
void audio_Sourcef(audio_Object srcobj, audio_SourceProp pname,
				   float value);
void audio_Sourcefv(audio_Object srcobj, audio_SourceProp pname,
					float* value);
void audio_GetSourcei(audio_Object srcobj, audio_SourceProp pname,
					  audio_IntVal* value);
void audio_GetSourcef(audio_Object srcobj, audio_SourceProp pname,
					  float* value);
void audio_SourceRewind(audio_Object srcobj);
void audio_SourcePlay(audio_Object srcobj);
void audio_SourcePause(audio_Object srcobj);
void audio_SourceStop(audio_Object srcobj);
void audio_SourceQueueBuffers(audio_Object srcobj, uint32 n,
							  audio_Object* pbufobj);
void audio_SourceUnqueueBuffers(audio_Object srcobj, uint32 n,
								audio_Object* pbufobj);

/* Buffers */
void audio_GenBuffers(uint32 n, audio_Object* pbufobj);
void audio_DeleteBuffers(uint32 n, audio_Object* pbufobj);
bool audio_IsBuffer(audio_Object bufobj);
void audio_GetBufferi(audio_Object bufobj, audio_BufferProp pname,
					  audio_IntVal* value);
void audio_BufferData(audio_Object bufobj, uint32 format, void* data,
					  uint32 size, uint32 freq);

bool audio_GetFormatInfo(uint32 format, int* channels, int* sample_size);

#endif /* LIBS_SOUND_AUDIOCORE_H_ */
