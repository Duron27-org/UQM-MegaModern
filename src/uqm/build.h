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

#ifndef UQM_BUILD_H_
#define UQM_BUILD_H_

#include "races.h"
#include "displist.h"
#include "libs/compiler.h"
#include "starmap.h"

#if 0 //defined(__cplusplus)
extern "C" {
#endif

#define NUM_RACE_LABELS  3
#define NUM_CLASS_LABELS 2
#define NAME_OFFSET (NUM_RACE_LABELS + NUM_CLASS_LABELS)
#define NUM_CAPTAINS_NAMES 16

#define PickCaptainName() (((uqm::COUNT)TFB_Random () \
								& (NUM_CAPTAINS_NAMES - 1)) \
								+ NAME_OFFSET)

extern HLINK Build (QUEUE *pQueue, SPECIES_ID SpeciesID);
extern HSHIPFRAG CloneShipFragment (RACE_ID shipIndex, QUEUE *pDstQueue,
		uqm::COUNT crew_level);
extern HLINK GetStarShipFromIndex (QUEUE *pShipQ, uqm::COUNT Index);
extern HFLEETINFO GetSeededFleetFromIndex (uqm::COUNT Index);
extern HSHIPFRAG GetEscortByStarShipIndex (uqm::COUNT index);
extern uqm::BYTE NameCaptain (QUEUE *pQueue, SPECIES_ID SpeciesID);

extern uqm::COUNT GetIndexFromStarShip (QUEUE *pShipQ, HLINK hStarShip);
extern int SetEscortCrewComplement (RACE_ID which_ship, uqm::COUNT crew_level,
		uqm::BYTE captain);

extern SPECIES_ID ShipIdStrToIndex (const char *shipIdStr);
extern RACE_ID RaceIdStrToIndex (const char *raceIdStr);
extern uqm::COUNT AddEscortShips (RACE_ID race, uqm::SIZE count);
extern uqm::COUNT CalculateEscortsWorth (void);
extern uqm::COUNT CalculateEscortsPoints (void);
extern bool CanBuyPoints (HFLEETINFO hFleet);
extern bool ShipsReady (RACE_ID race);
extern void PrepareShip (RACE_ID race);
extern bool SetRaceAllied (RACE_ID race, bool flag);
extern uqm::COUNT StartSphereTracking (RACE_ID race);
extern bool CheckSphereTracking (RACE_ID race);
extern bool KillRace (RACE_ID race);
extern uqm::COUNT CountEscortShips (RACE_ID race);
extern bool HaveEscortShip (RACE_ID race);
extern uqm::COUNT EscortFeasibilityStudy (RACE_ID race);
extern uqm::COUNT CheckAlliance (RACE_ID race);
extern bool RaceDead (RACE_ID race);
extern uqm::COUNT RemoveSomeEscortShips (RACE_ID race, uqm::COUNT count);
extern uqm::COUNT RemoveEscortShips (RACE_ID race);

extern RACE_DESC *load_ship (SPECIES_ID SpeciesID, bool LoadBattleData);
extern void free_ship (RACE_DESC *RaceDescPtr, bool FreeIconData,
		bool FreeBattleData);
extern void loadGameCheats (void);
// WarEraStrength gives the hard coded strength values (formerly an array)
extern uqm::COUNT WarEraStrength (SPECIES_ID SpeciesID);
// SeedFleetLocation moves the fleet to the plot location specified in visit.
extern POINT SeedFleetLocation (FLEET_INFO *FleetPtr, PLOT_LOCATION *plotmap,
		uqm::COUNT visit);
// SeedFleet does initial fleet placement for StarSeed
extern void SeedFleet (FLEET_INFO *FleetPtr, PLOT_LOCATION *plotmap);
// SeedShip handles ship seeding, used in build.c to handle the load window
extern SPECIES_ID SeedShip (SPECIES_ID SpeciesID, bool loadWindow);
extern bool legacySave;
extern uqm::BYTE GTFO;

#if 0 //defined(__cplusplus)
}
#endif

#endif /* UQM_BUILD_H_ */

