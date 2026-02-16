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

#include "velocity.h"

#include "units.h"
#include "libs/compiler.h"
#include "core/log/log.h"

#define VELOCITY_REMAINDER(v) ((v) & (VELOCITY_SCALE - 1))

void GetCurrentVelocityComponents(VELOCITY_DESC* velocityptr, uqm::SIZE* pdx, uqm::SIZE* pdy)
{
	*pdx = WORLD_TO_VELOCITY(velocityptr->vector.width)
		 + (velocityptr->fract.width - (uqm::SIZE)highByte(velocityptr->incr.width));
	*pdy = WORLD_TO_VELOCITY(velocityptr->vector.height)
		 + (velocityptr->fract.height - (uqm::SIZE)highByte(velocityptr->incr.height));
}

void GetCurrentVelocityComponentsSdword(VELOCITY_DESC* velocityptr, uqm::SDWORD* pdx, uqm::SDWORD* pdy)
{
	*pdx = WORLD_TO_VELOCITY(velocityptr->vector.width)
		 + ((uqm::SDWORD)velocityptr->fract.width - (uqm::SDWORD)highByte(velocityptr->incr.width));
	*pdy = WORLD_TO_VELOCITY(velocityptr->vector.height)
		 + ((uqm::SDWORD)velocityptr->fract.height - (uqm::SDWORD)highByte(velocityptr->incr.height));
}

void GetNextVelocityComponents(VELOCITY_DESC* velocityptr, uqm::SIZE* pdx, uqm::SIZE* pdy, uqm::COUNT num_frames)
{
	uqm::COUNT e;

	e = (uqm::COUNT)((uqm::COUNT)velocityptr->error.width + ((uqm::COUNT)velocityptr->fract.width * num_frames));

	*pdx = (velocityptr->vector.width * num_frames)
		 + ((uqm::SIZE)((uqm::SBYTE)lowByte(velocityptr->incr.width))
			* (e >> VELOCITY_SHIFT));

	velocityptr->error.width = VELOCITY_REMAINDER(e);

	e = (uqm::COUNT)((uqm::COUNT)velocityptr->error.height + ((uqm::COUNT)velocityptr->fract.height * num_frames));

	*pdy = (velocityptr->vector.height * num_frames)
		 + ((uqm::SIZE)((uqm::SBYTE)lowByte(velocityptr->incr.height))
			* (e >> VELOCITY_SHIFT));

	velocityptr->error.height = VELOCITY_REMAINDER(e);
}

// JMS_GFX: New function to prevent overflows in hi-res.
void GetNextVelocityComponentsSdword(VELOCITY_DESC* velocityptr, uqm::SDWORD* pdx, uqm::SDWORD* pdy, uqm::DWORD num_frames)
{
	uqm::DWORD e;

	e = (uqm::DWORD)((uqm::DWORD)velocityptr->error.width + ((uqm::DWORD)velocityptr->fract.width * num_frames));

	*pdx = ((uqm::SDWORD)velocityptr->vector.width * num_frames)
		 + ((uqm::SDWORD)((uqm::SBYTE)lowByte(velocityptr->incr.width))
			* (e >> VELOCITY_SHIFT));

	velocityptr->error.width = (uqm::COUNT)(VELOCITY_REMAINDER(e));

	e = (uqm::DWORD)((uqm::DWORD)velocityptr->error.height + ((uqm::DWORD)velocityptr->fract.height * num_frames));

	*pdy = ((uqm::SDWORD)velocityptr->vector.height * num_frames)
		 + ((uqm::SDWORD)((uqm::SBYTE)lowByte(velocityptr->incr.height))
			* (e >> VELOCITY_SHIFT));

	velocityptr->error.height = (uqm::COUNT)(VELOCITY_REMAINDER(e));
}

// JMS_GFX: Preventing overflows in hi-res: The uqm::SDWORD in this function's parameters was uqm::SIZE.
void SetVelocityVector(VELOCITY_DESC* velocityptr, uqm::SDWORD magnitude, uqm::COUNT facing)
{
	uqm::COUNT angle;
	uqm::SIZE dx, dy;

	angle = velocityptr->TravelAngle =
		FACING_TO_ANGLE(NORMALIZE_FACING(facing));
	magnitude = WORLD_TO_VELOCITY(magnitude);
	dx = COSINE(angle, magnitude);
	dy = SINE(angle, magnitude);
	if (dx >= 0)
	{
		velocityptr->vector.width = VELOCITY_TO_WORLD(dx);
		velocityptr->incr.width = MAKE_WORD((uqm::BYTE)1, (uqm::BYTE)0);
	}
	else
	{
		dx = -dx;
		velocityptr->vector.width = -VELOCITY_TO_WORLD(dx);
		velocityptr->incr.width =
			MAKE_WORD((uqm::BYTE)0xFF, (uqm::BYTE)(VELOCITY_REMAINDER(dx) << 1));
	}
	if (dy >= 0)
	{
		velocityptr->vector.height = VELOCITY_TO_WORLD(dy);
		velocityptr->incr.height = MAKE_WORD((uqm::BYTE)1, (uqm::BYTE)0);
	}
	else
	{
		dy = -dy;
		velocityptr->vector.height = -VELOCITY_TO_WORLD(dy);
		velocityptr->incr.height =
			MAKE_WORD((uqm::BYTE)0xFF, (uqm::BYTE)(VELOCITY_REMAINDER(dy) << 1));
	}

	velocityptr->fract.width = VELOCITY_REMAINDER(dx);
	velocityptr->fract.height = VELOCITY_REMAINDER(dy);
	velocityptr->error.width = velocityptr->error.height = 0;
}

// JMS_GFX: Preventing overflows in hi-res: The SDWORDs in this function's parameters were SIZEs.
void SetVelocityComponents(VELOCITY_DESC* velocityptr, uqm::SDWORD dx, uqm::SDWORD dy)
{
	uqm::COUNT angle;

	if ((angle = ARCTAN(dx, dy)) == FULL_CIRCLE)
	{
		ZeroVelocityComponents(velocityptr);
	}
	else
	{
		if (dx >= 0)
		{
			velocityptr->vector.width = VELOCITY_TO_WORLD(dx);
			velocityptr->incr.width = MAKE_WORD((uqm::BYTE)1, (uqm::BYTE)0);
		}
		else
		{
			dx = -dx;
			velocityptr->vector.width = -VELOCITY_TO_WORLD(dx);
			velocityptr->incr.width =
				MAKE_WORD((uqm::BYTE)0xFF, (uqm::BYTE)(VELOCITY_REMAINDER(dx) << 1));
		}
		if (dy >= 0)
		{
			velocityptr->vector.height = VELOCITY_TO_WORLD(dy);
			velocityptr->incr.height = MAKE_WORD((uqm::BYTE)1, (uqm::BYTE)0);
		}
		else
		{
			dy = -dy;
			velocityptr->vector.height = -VELOCITY_TO_WORLD(dy);
			velocityptr->incr.height =
				MAKE_WORD((uqm::BYTE)0xFF, (uqm::BYTE)(VELOCITY_REMAINDER(dy) << 1));
		}

		velocityptr->fract.width = VELOCITY_REMAINDER(dx);
		velocityptr->fract.height = VELOCITY_REMAINDER(dy);
		velocityptr->error.width = velocityptr->error.height = 0;
	}

	velocityptr->TravelAngle = angle;
}

// JMS_GFX: Preventing overflows in hi-res: The SDWORDs in this function's parameters were SIZEs.
void DeltaVelocityComponents(VELOCITY_DESC* velocityptr, uqm::SDWORD dx, uqm::SDWORD dy)
{

	dx += WORLD_TO_VELOCITY(velocityptr->vector.width)
		+ (velocityptr->fract.width - (uqm::SIZE)highByte(velocityptr->incr.width));
	dy += WORLD_TO_VELOCITY(velocityptr->vector.height)
		+ (velocityptr->fract.height - (uqm::SIZE)highByte(velocityptr->incr.height));

	SetVelocityComponents(velocityptr, dx, dy);
}
