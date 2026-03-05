#pragma once
#ifndef UQM_CORE_STL_H_
#define UQM_CORE_STL_H_

#ifndef __STDC_WANT_LIB_EXT1__
#define __STDC_WANT_LIB_EXT1__ 1
#endif

#include <gsl-lite/gsl-lite.hpp>
namespace uqgsl = gsl_lite;

#ifndef USING_EASTL

#include <algorithm>
#include <type_traits>
#include <numeric>
#include <span>

namespace uqstl = std;

#else
static_assert(false, "EASTL is not supported yet. If you want to add support for it, submit a PR!");
#endif /* !defined(USING_EASTL)*/


#endif //UQM_CORE_STL_H_