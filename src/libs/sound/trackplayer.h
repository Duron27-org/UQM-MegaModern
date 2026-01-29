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

#ifndef TRACKPLAYER_H
#define TRACKPLAYER_H

#include "libs/compiler.h"
#include "libs/callback.h"

#define ACCEL_SCROLL_SPEED 300

#define VERY_SLOW 0
#define SLOW 12
#define MODERATE_SPEED 16
#define FAST 24
#define VERY_FAST 32

static const uqm::BYTE speed_array[] =
{
	VERY_SLOW,
	SLOW,
	MODERATE_SPEED,
	FAST,
	VERY_FAST
};

extern void PlayTrack (void);
extern void StopTrack (void);
extern void JumpTrack (void);
extern void PauseTrack (void);
extern void ResumeTrack (void);
extern uqm::COUNT PlayingTrack (void);
extern uqm::COUNT GetSubtitleNumber (const uqm::CHAR_T *sub);

extern void FastReverse_Smooth (void);
extern void FastForward_Smooth (void);
extern void FastReverse_Page (void);
extern void FastForward_Page (void);

extern void SpliceTrack (uqm::CHAR_T *filespec, uqm::CHAR_T *textspec, uqm::CHAR_T *TimeStamp, CallbackFunction cb);
extern void SpliceMultiTrack (uqm::CHAR_T *TrackNames[], uqm::CHAR_T *TrackText);

extern int GetTrackPosition (int in_units);

typedef struct tfb_soundchunk *SUBTITLE_REF;

extern SUBTITLE_REF GetFirstTrackSubtitle (void);
extern SUBTITLE_REF GetNextTrackSubtitle (SUBTITLE_REF LastRef);
extern const uqm::CHAR_T *GetTrackSubtitleText (SUBTITLE_REF SubRef);

extern const uqm::CHAR_T *GetTrackSubtitle (void);
extern uqm::COUNT GetSubtitleNumberByTrack (uqm::COUNT track);
extern uqm::DWORD RecalculateDelay (uqm::DWORD numChars, bool talk);

#endif
