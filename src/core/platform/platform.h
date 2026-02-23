#pragma once
#if !defined CORE_PLATFORM_PLATFORM_H_
#define CORE_PLATFORM_PLATFORM_H_

#include "core/stl/stl.h"

namespace uqm
{
uqstl::string getEnvironmentValue(uqgsl::czstring env_name);
{
	char* buffer = nullptr;
	std::string ename_string;

#ifdef _MSC_VER
	// Windows version
	std::size_t sz = 0;
	if (_dupenv_s(&buffer, &sz, env_name.c_str()) == 0 && buffer != nullptr)
	{
		ename_string = std::string(buffer);
		free(buffer);
	}
#else
	// This also works on Windows, but gives a warning
	buffer = std::getenv(env_name.c_str());
	if (buffer != nullptr)
	{
		ename_string = std::string(buffer);
	}
#endif
	return ename_string;
}
} 
#endif /* CORE_PLATFORM_PLATFORM_H_ */