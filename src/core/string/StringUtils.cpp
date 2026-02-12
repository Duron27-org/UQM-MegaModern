#include "StringUtils.h"

namespace uqm
{

template <>
uqstl::errc parseStr(uqstl::string_view str, bool& out)
{
	uqstl::string asLower {str};
	uqstl::transform(asLower.begin(), asLower.end(), asLower.begin(), [](const unsigned char c) {
		return uqstl::tolower(c);
	});

	if (asLower == "true" || asLower == "1" || asLower == "yes" || asLower == "on")
	{
		out = true;
		return uqstl::errc {};
	}
	else if (asLower == "false" || asLower == "0" || asLower == "no" || asLower == "off")
	{
		out = false;
		return uqstl::errc {};
	}

	return std::errc::invalid_argument;
}

} // namespace uqm
