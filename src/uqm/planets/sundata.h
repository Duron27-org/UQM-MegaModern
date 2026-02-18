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

#ifndef UQM_PLANETS_SUNDATA_H_
#define UQM_PLANETS_SUNDATA_H_

#include "plandata.h"
#include "libs/compiler.h"

#if 0 //defined(__cplusplus)
extern "C" {
#endif

/*------------------------------ Global Data ------------------------------ */

#define NUMBER_OF_SUN_SIZES (SUPER_GIANT_STAR - DWARF_STAR + 1)

#define DWARF_ENERGY 1
#define GIANT_ENERGY 5
#define SUPERGIANT_ENERGY 20

typedef struct
{
	uqm::BYTE StarSize;
	uqm::BYTE StarIntensity;
	uqm::UWORD StarEnergy;

	PLANET_INFO PlanetInfo;
} SYSTEM_INFO;

#define GENERATE_ALL ((uqm::COUNT)~0)

extern uqm::COUNT GenerateMineralDeposits(const SYSTEM_INFO*, uqm::COUNT whichDeposit,
										  NODE_INFO* info);
extern uqm::COUNT GenerateLifeForms(const SYSTEM_INFO*, uqm::COUNT whichLife,
									NODE_INFO* info);
extern void GenerateRandomLocation(GFXPOINT* loc);
extern uqm::COUNT GenerateRandomNodes(const SYSTEM_INFO*, uqm::COUNT scan, uqm::COUNT numNodes,
									  uqm::COUNT type, uqm::COUNT whichNode, NODE_INFO* info);
extern uqm::COUNT CustomMineralDeposits(const SYSTEM_INFO* SysInfoPtr, uqm::COUNT which_deposit,
										NODE_INFO* info, uqm::COUNT numNodes, uqm::COUNT type, uqm::BYTE quality);
extern uqm::COUNT CustomMineralDeposit(NODE_INFO* info, uqm::COUNT type, uqm::BYTE quality,
									   GFXPOINT location);
// Generate lifeforms from a preset lifeTypes[] array
extern uqm::COUNT GeneratePresetLife(const SYSTEM_INFO*,
									 const uqm::SBYTE* lifeTypes, uqm::COUNT whichLife, NODE_INFO* info);

#define DWARF_ELEMENT_DENSITY 1
#define GIANT_ELEMENT_DENSITY 3
#define SUPERGIANT_ELEMENT_DENSITY 8

#define MAX_ELEMENT_DENSITY ((MAX_ELEMENT_UNITS * SUPERGIANT_ELEMENT_DENSITY) << 1)

extern void DoPlanetaryAnalysis(SYSTEM_INFO* SysInfoPtr,
								PLANET_DESC* pPlanetDesc);

#if 0 //defined(__cplusplus)
}
#endif

#endif /* UQM_PLANETS_SUNDATA_H_ */
