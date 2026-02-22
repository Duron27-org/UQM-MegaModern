#pragma once
#ifndef UQM_INTELDEFS_H_
#define UQM_INTELDEFS_H_

#include <cstdint>
#include "core/types/enum.h"


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



enum
{
	ENEMY_SHIP_INDEX = 0,
	CREW_OBJECT_INDEX,
	ENEMY_WEAPON_INDEX,
	GRAVITY_MASS_INDEX,
	FIRST_EMPTY_INDEX
};


enum class PlayerControlFlags : uint8_t
{
	None = 0,
	Human = 1 << 0,
	Network = 1 << 1,
	Cyborg = 1 << 2,  // computer fights battles
	Psytron = 1 << 3, // Psytron is cyborg, AND chooses its own ships during battle
	DifficultyStandard = 1 << 4,
	DifficultyGood = 1 << 5,
	DifficultyAwesome = 1 << 6,
};
ENUM_BITWISE_OPS(PlayerControlFlags);
// ComputerControlFlags is used in SuperMelee; the computer chooses
// the ships and fights the battles.
// PlayerControlFlags::Cyborg is used in the full game; the computer only
// fights the battles. XXX: This will need to be handled
// separately in the future if we want to remove the special
// cases for ship selection with PlayerControlFlags::Cyborg from the
// computer handlers.
 static inline constexpr PlayerControlFlags ComputerControlFlags {PlayerControlFlags::Cyborg | PlayerControlFlags::Psytron};
static inline constexpr PlayerControlFlags ControlFlagsMask {PlayerControlFlags::Human | PlayerControlFlags::Network | ComputerControlFlags};
static inline constexpr PlayerControlFlags DifficultyFlagsMask {PlayerControlFlags::DifficultyStandard | PlayerControlFlags::DifficultyGood | PlayerControlFlags::DifficultyAwesome};

#endif /* UQM_INTELDEFS_H_ */