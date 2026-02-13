#pragma once
#ifndef UQM_LIBS_MATH_RANDOMDEFS_H_
#define UQM_LIBS_MATH_RANDOMDEFS_H_


#include "options/OptionConstants.h"

// The Planet Generation seeding code alters SeedA to function.
// All other modes use proper PrimeA == SeedA == 16807
extern uqm::SeedType g_seedType;

#define PrimeA 16807
#define MAX_SEED 2147483644
#define MIN_SEED 3
#define SANE_SEED(a) (((a) < MIN_SEED || (a) > MAX_SEED) ? false : true)
#define PrimeSeed (g_seedType == uqm::SeedType::Prime)
#define StarSeed (g_seedType > uqm::SeedType::Planet)

#endif /* UQM_LIBS_MATH_RANDOMDEFS_H_ */