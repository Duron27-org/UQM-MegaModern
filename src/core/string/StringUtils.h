#pragma once

#ifndef UQM_CORE_STRING_STRINGUTILS_H_
#define UQM_CORE_STRING_STRINGUTILS_H_

#include <algorithm>
#include <ranges>
#include <charconv>
#include <cctype>
#include <fmt/format.h>
#include "core/stl/stl.h"

template <typename T, typename uqstl::enable_if_t<std::is_arithmetic_v<T>, bool> = true>
[[nodiscard]] inline const char* toString(T value)
{
	if constexpr (uqstl::is_same_v<uqstl::remove_cv_t<T>, bool>)
	{
		return value ? "true" : "false";
	}

	static thread_local char buf[64];
	const auto [_, len] {fmt::format_to_n(buf, 63, "{}", value)};
	buf[len] = '\0';
	return buf;
}


[[nodiscard]] inline bool compareCharICase(const char a, const char b) noexcept
{
	return uqstl::tolower(static_cast<const unsigned char>(a)) == uqstl::tolower(static_cast<const unsigned char>(b));
}

[[nodiscard]] inline bool compareICase(uqstl::string_view lhs, uqstl::string_view rhs) noexcept
{
	return std::ranges::equal(lhs, rhs, [](const char a, const char b) {
		return uqstl::tolower(static_cast<const unsigned char>(a)) == uqstl::tolower(static_cast<const unsigned char>(b));
		});
}


[[nodiscard]] inline constexpr bool isEmpty(const char* sz) noexcept
{
	return sz == nullptr || sz[0] == '\0';
}

[[nodiscard]] inline constexpr bool isEmpty(uqstl::string_view str) noexcept
{
	return str.empty();
}
[[nodiscard]] inline constexpr bool isEmpty(const uqstl::string& str) noexcept
{
	return str.empty();
}

template <typename StringT>
[[nodiscard]] inline constexpr const char* c_str(const StringT& str) noexcept
{
	return str.c_str();
}
template <>
[[nodiscard]] inline constexpr const char* c_str<const char*>(const char* const& str) noexcept
{
	return str;
}
template <>
[[nodiscard]] inline constexpr const char* c_str<uqgsl::not_null_czstring>(const uqgsl::not_null_czstring& str) noexcept
{
	return str;
}
template <>
[[nodiscard]] inline constexpr const char* c_str<uqstl::string_view>(const uqstl::string_view& str) noexcept
{
	return str.data();
}

template <typename T, typename uqstl::enable_if_t<std::is_arithmetic_v<T>, bool> = true>
inline uqstl::errc parseStr(uqstl::string_view str, T& out)
{
	const auto [_, ec] = uqstl::from_chars(str.data(), uqstl::to_address(str.end()), out);
	return ec;
}

// template specialization for bool. Impl in cpp.
template <>
uqstl::errc parseStr(uqstl::string_view str, bool& out);
//uqstl::errc parseStr(uqgsl::czstring str, int& out);
//uqstl::errc parseStr(uqgsl::czstring str, float& out);

template <typename T, typename uqstl::enable_if_t<std::is_enum_v<T>, bool> = true>
inline uqstl::errc parseStr(uqstl::string_view str, T& out)
{
	using UnderlyingT = std::underlying_type_t<T>;

	UnderlyingT intermediate {};
	const auto ec {parseStr(str, intermediate)};
	if (ec == std::errc {})
	{
		out = static_cast<T>(intermediate);
	}
	return ec;
}

#endif /* UQM_CORE_STRING_STRINGUTILS_H_ */
