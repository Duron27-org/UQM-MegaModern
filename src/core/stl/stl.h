#pragma once
#ifndef UQM_CORE_STL_H_
#define UQM_CORE_STL_H_

#ifndef __STDC_WANT_LIB_EXT1__
#define __STDC_WANT_LIB_EXT1__ 1
#endif

#ifndef USING_EASTL

#include <algorithm>
#include <array>
#include <map>
#include <memory>
#include <numeric>
#include <optional>
#include <string>
#include <string_view>
#include <span>
#include <vector>
#include <type_traits>
#include <gsl-lite/gsl-lite.hpp>

namespace uqstl = std;
namespace uqgsl = gsl_lite;

namespace gsl_lite
{
using not_null_czstring = not_null<czstring>;
}

namespace std
{
template <size_t N>
using fixed_string = string; // std library has no fixed string :(
}
#else
static_assert(false, "EASTL is not supported yet. If you want to add support for it, submit a PR!");
#endif /* !defined(USING_EASTL)*/


#endif //UQM_CORE_STL_H_