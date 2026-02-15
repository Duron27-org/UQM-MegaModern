#pragma once
#ifndef UQM_CORE_MISC_BITTRICKS_H_
#define UQM_CORE_MISC_BITTRICKS_H_

#include "core/stl/stl.h"

namespace uqm
{

template <typename T>
constexpr bool isPowerOfTwo(T value) noexcept
{
	static_assert(uqstl::is_integral_v<T>, "Integral type required");

	return value > 0 && (value & (value - 1)) == 0;
}

}

#endif /* UQM_CORE_MISC_BITTRICKS_H_ */