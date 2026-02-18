#pragma once
#ifndef LIBS_SOUND_AUDIOCOREDEFS_H_
#define LIBS_SOUND_AUDIOCOREDEFS_H_

#include "core/types/enum.h"
/* Available drivers */
enum class AudioDriverType
{
	NoSound,
	MixSDL,
	OpenAL,
};

/* Initialization flags */
enum class AudioFlags : uint32_t
{
	None,
	QualityLow = 1,
	QualityMedium = 1 << 1,
	QualityHigh = 1 << 2,
};
ENUM_BITWISE_OPS(AudioFlags)
static constexpr inline AudioFlags AudioQualityFlagMask {AudioFlags::QualityLow | AudioFlags::QualityMedium | AudioFlags::QualityHigh};

/* Interface Types */
using audio_Object = uintptr_t;
using audio_IntVal = intptr_t;
using audio_SourceProp = const int32_t;
using audio_BufferProp = const int32_t;

enum
{
	/* Errors */
	audio_NO_ERROR = 0,
	audio_INVALID_NAME,
	audio_INVALID_ENUM,
	audio_INVALID_VALUE,
	audio_INVALID_OPERATION,
	audio_OUT_OF_MEMORY,
	audio_DRIVER_FAILURE,

	/* Source properties */
	audio_POSITION,
	audio_LOOPING,
	audio_BUFFER,
	audio_GAIN,
	audio_SOURCE_STATE,
	audio_BUFFERS_QUEUED,
	audio_BUFFERS_PROCESSED,

	/* Source state information */
	audio_INITIAL,
	audio_STOPPED,
	audio_PLAYING,
	audio_PAUSED,

	/* Sound buffer properties */
	audio_FREQUENCY,
	audio_BITS,
	audio_CHANNELS,
	audio_SIZE,
	audio_FORMAT_MONO16,
	audio_FORMAT_STEREO16,
	audio_FORMAT_MONO8,
	audio_FORMAT_STEREO8,
	audio_ENUM_SIZE
};

#endif /*LIBS_SOUND_AUDIOCOREDEFS_H_*/