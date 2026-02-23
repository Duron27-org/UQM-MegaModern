#include "platform.h"

#include <stdlib.h>

namespace uqm
{

uqstl::string getEnvironmentValue(uqgsl::czstring env_name)
{
#ifdef _MSC_VER
	// Windows version
	char* buffer {};
	size_t bufferSize {};
	if (_dupenv_s(&buffer, &bufferSize, env_name) == 0 && buffer != nullptr)
	{
		ret.reserve(bufferSize);
		uqstl::string ret {buffer, bufferSize};

		free(buffer);
		return ret;
	}
#else
	// This also works on Windows, but gives a warning
	if (char* buffer = std::getenv(env_name.c_str()); buffer != nullptr)
	{
		return {buffer};
	}
#endif
	return {};
}


} // namespace uqm