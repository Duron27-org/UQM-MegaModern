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

#ifndef UQM_INTEL_H_
#define UQM_INTEL_H_

#include "options/OptionDefs.h"
#include "battlecontrols.h"
#include "controls.h"
#include "element.h"
#include "races.h"
#include "setup.h"

#define MANEUVERABILITY(pi) ((pi)->ManeuverabilityIndex)
#define WEAPON_RANGE(pi) ((pi)->WeaponRange)

#define WORLD_TO_TURN(d) ((d) >> 6)

#define CLOSE_RANGE_WEAPON DISPLAY_TO_WORLD(50)
#define LONG_RANGE_WEAPON DISPLAY_TO_WORLD(1000)
#define FAST_SHIP 150
#define MEDIUM_SHIP 45
#define SLOW_SHIP 25


#define CLOSE_RANGE_WEAPON_HD DISPLAY_TO_WORLD(200)
#define LONG_RANGE_WEAPON_HD DISPLAY_TO_WORLD(4000)

// JMS_GFX: Multiplied by 4*4=16 because of the way the ManeuverabilityIndex
// is calculated in InitCyborg () (cyborg.c).
#define FAST_SHIP_HD 2400
#define MEDIUM_SHIP_HD 720
#define SLOW_SHIP_HD 400


#define RESOLUTION_COMPENSATED(speed) (RES_SCALE(RES_SCALE(speed)))

enum
{
	ENEMY_SHIP_INDEX = 0,
	CREW_OBJECT_INDEX,
	ENEMY_WEAPON_INDEX,
	GRAVITY_MASS_INDEX,
	FIRST_EMPTY_INDEX
};

extern BATTLE_INPUT_STATE computer_intelligence(
	ComputerInputContext* context, STARSHIP* StarShipPtr);
extern BATTLE_INPUT_STATE tactical_intelligence(
	ComputerInputContext* context, STARSHIP* StarShipPtr);
extern void ship_intelligence(ELEMENT* ShipPtr,
							  EVALUATE_DESC* ObjectsOfConcern, uqm::COUNT ConcernCounter);
extern bool ship_weapons(ELEMENT* ShipPtr, ELEMENT* OtherPtr,
						 uqm::COUNT margin_of_error);

extern void Pursue(ELEMENT* ShipPtr, EVALUATE_DESC* EvalDescPtr);
extern void Entice(ELEMENT* ShipPtr, EVALUATE_DESC* EvalDescPtr);
extern void Avoid(ELEMENT* ShipPtr, EVALUATE_DESC* EvalDescPtr);
extern bool TurnShip(ELEMENT* ShipPtr, uqm::COUNT angle);
extern bool ThrustShip(ELEMENT* ShipPtr, uqm::COUNT angle);


#define HUMAN_CONTROL (uqm::BYTE)(1 << 0)
#define CYBORG_CONTROL (uqm::BYTE)(1 << 1)
// The computer fights the battles.
#define PSYTRON_CONTROL (uqm::BYTE)(1 << 2)
// The computer selects the ships to fight with.
#define NETWORK_CONTROL (uqm::BYTE)(1 << 3)
#define COMPUTER_CONTROL (CYBORG_CONTROL | PSYTRON_CONTROL)
#define CONTROL_MASK (HUMAN_CONTROL | COMPUTER_CONTROL | NETWORK_CONTROL)

#define STANDARD_RATING (uqm::BYTE)(1 << 4)
#define GOOD_RATING (uqm::BYTE)(1 << 5)
#define AWESOME_RATING (uqm::BYTE)(1 << 6)

static inline bool
antiCheatImpl(const ELEMENT* element, const bool swapPlayers, const uqm::GodModeFlags testFlags, uqstl::span<const uqm::BYTE> playerControl, const uqm::GodModeFlags godModeData)
{
	if ((playerControl[0] & COMPUTER_CONTROL) && (playerControl[1] & COMPUTER_CONTROL))
	{
		return false; // both players are AI-controlled
	}

	if (!testFlag(godModeData, testFlags))
	{
		return false;
	}

	const int elementOwner = element->playerNr;
	const int opponent = elementOwner ^ 1;

	const int playerIndex = swapPlayers ? elementOwner : opponent;

	return (playerControl[playerIndex] & COMPUTER_CONTROL) != 0;
}

static inline bool
antiCheat(ELEMENT* ElementPtr, bool SwapBool, uqm::GodModeFlags godModeType)
{
	return antiCheatImpl(ElementPtr, SwapBool, godModeType, {PlayerControl, NUM_PLAYERS}, optGodModes);
}

static inline bool
antiCheatAltImpl(const uqm::GodModeFlags testFlags, const uqstl::span<const uqm::BYTE> playerControl, const uqm::GodModeFlags godModeData)
{
	const bool player0Computer = (playerControl[0] & COMPUTER_CONTROL) != 0;
	const bool player1Computer = (playerControl[1] & COMPUTER_CONTROL) != 0;

	if (player0Computer && player1Computer)
	{
		return false;
	}

	if (!testFlag(godModeData, testFlags))
	{
		return false;
	}

	return player0Computer != player1Computer;
}

static inline bool
antiCheatAlt(uqm::GodModeFlags godModeFlags)
{
	return antiCheatAltImpl(godModeFlags, {PlayerControl, NUM_PLAYERS}, optGodModes);
}

static inline bool
isNetwork(void)
{
	return (PlayerControl[0] & NETWORK_CONTROL
			|| PlayerControl[1] & NETWORK_CONTROL);
}

#if 0 //defined(__cplusplus)
}
#endif

#endif /* UQM_INTEL_H_ */
