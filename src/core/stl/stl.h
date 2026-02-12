#pragma once
#ifndef UQM_CORE_STL_H_
#define UQM_CORE_STL_H_

#include <array>
#include <optional>
#include <string>
#include <string_view>
#include <span>
#include <vector>
#include <gsl-lite/gsl-lite.hpp>

namespace uqstl = std;
namespace uqgsl = gsl_lite;

namespace gsl_lite
{
using not_null_czstring = not_null<czstring>;
}

#endif //UQM_CORE_STL_H_