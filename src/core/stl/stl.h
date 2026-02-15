#pragma once
#ifndef UQM_CORE_STL_H_
#define UQM_CORE_STL_H_

#ifdef USING_EASTL
// balh
#else

#include <array>
#include <memory>
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

#endif /* !defined(USING_EASTL)*/

#endif //UQM_CORE_STL_H_