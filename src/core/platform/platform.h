#pragma once
#if !defined CORE_PLATFORM_PLATFORM_H_
#define CORE_PLATFORM_PLATFORM_H_

#include "core/stl/stl.h"

namespace uqm
{
uqstl::string getEnvironmentValue(uqgsl::czstring env_name);
bool setEnvironmentValue(uqgsl::czstring name, uqgsl::czstring value, bool overwrite);
uqstl::string strerror(errno_t err);
} 

#endif /* CORE_PLATFORM_PLATFORM_H_ */