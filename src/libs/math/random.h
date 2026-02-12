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

/****************************************************************************
* FILE: random.h
* DESC: definitions and externs for random number generators
*
* HISTORY: Created 6/ 6/1989
* LAST CHANGED:
*
* Copyright (c) 1989, Robert Leyland and Scott Anderson
****************************************************************************/

#ifndef LIBS_MATH_RANDOM_H_
#define LIBS_MATH_RANDOM_H_

#include "../../uqm/globdata.h"
#include "uqm/setupmenu.h"
#include "options/OptionConstants.h"

/* ----------------------------GLOBALS/EXTERNS---------------------------- */

uqm::DWORD TFB_SeedRandom(uqm::DWORD seed);
uqm::DWORD TFB_Random(void);


typedef struct RandomContext RandomContext;


extern uqm::SeedType g_seedType;



#ifdef RANDOM2_INTERNAL
struct RandomContext
{
	uqm::DWORD seed;
};
#endif

// The Planet Generation seeding code alters SeedA to function.
// All other modes use proper PrimeA == SeedA == 16807
#define PrimeA 16807
#define MAX_SEED 2147483644
#define MIN_SEED 3
#define SANE_SEED(a) (((a) < MIN_SEED || (a) > MAX_SEED) ? false : true)
#define SeedA (((g_seedType == uqm::SeedType::Planet) && (SANE_SEED(GLOBAL_SIS(Seed)))) ? GLOBAL_SIS(Seed) : PrimeA)
// Default SeedA (PrimeA): 16807 - a relatively prime number - also M div Q
#define SeedM (UINT32_MAX / 2) // 0xFFFFFFFF div 2
#define SeedQ (SeedM / SeedA)  // Default: 127773L - M div A
#define SeedR (SeedM % SeedA)  // Default: 2836 - M mod A
#define PrimeSeed (g_seedType == uqm::SeedType::Prime)
#define StarSeed (g_seedType > uqm::SeedType::Planet)

RandomContext* RandomContext_New(void);
RandomContext* RandomContext_Set(uqm::DWORD Context);
void RandomContext_Delete(RandomContext* context);
RandomContext* RandomContext_Copy(const RandomContext* source);
uqm::DWORD RandomContext_Random(RandomContext* context);
uqm::DWORD RandomContext_SeedRandom(RandomContext* context, uqm::DWORD new_seed);
uqm::DWORD RandomContext_GetSeed(RandomContext* context);
uqm::DWORD RandomContext_FastRandom(uqm::DWORD seed);
int RangeMinMax(int min, int max, uqm::DWORD rand);
extern void printBits(size_t const size, void const* const ptr);


#endif /* LIBS_MATH_RANDOM_H_ */
