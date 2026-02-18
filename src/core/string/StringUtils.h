#pragma once

#ifndef UQM_CORE_STRING_STRINGUTILS_H_
#define UQM_CORE_STRING_STRINGUTILS_H_

#include <algorithm>
#include <ranges>
#include <charconv>
#include <cctype>
#include <fmt/format.h>
#include "core/stl/stl.h"
#include "core/types/enum.h"

namespace uqm
{
static constexpr const char* TrueText {"true"};
static constexpr const char* FalseText {"false"};

template <typename E>
concept HasToStringImpl =
	requires(E e) {
		{ toStringImpl(e) } -> ::std::convertible_to<const char*>;
	};

[[nodiscard]] inline constexpr bool isEmpty(const char* sz) noexcept
{
	return sz == nullptr || sz[0] == '\0';
}

[[nodiscard]] constexpr size_t strlenConstexpr(uqgsl::czstring str) noexcept
{
	if (isEmpty(str)) [[unlikely]]
	{
		return 0;
	}
	return uqstl::string_view {str}.size();
}

[[nodiscard]] inline const char* toString(bool value)
{
	return value ? TrueText : FalseText;
}

template <typename E, uqstl::enable_if_t<std::is_enum_v<E>, bool> = true>
[[nodiscard]] static constexpr const char* toString(const E e)
{
#ifdef WITH_MAGIC_ENUM
	// a toString implementation will override the magic_enum output.
	if constexpr (HasToStringImpl<E>)
	{
		return toStringImpl(e);
	}
	else
	{
		return magic_enum::enum_name(e).data();
	}
#else
	static_assert(HasToStringImpl<E>, "Enum must have a toStringImpl() method to use this toString() method.") return toStringImpl(e);
#endif
}

template <typename T, typename uqstl::enable_if_t<std::is_arithmetic_v<T>, bool> = true>
inline const char* toString(const T value, uqstl::span<char> buffer)
{
	if (buffer.size() == 0) [[unlikely]]
	{
		buffer[0] = '\0';
		return buffer.data();
	}

	if constexpr (uqstl::is_same_v<bool, uqstl::remove_cv_t<T>>)
	{
		static constexpr size_t TrueLen {strlenConstexpr(TrueText)};
		static constexpr size_t FalseLen {strlenConstexpr(FalseText)};
		if (value)
		{
			if (buffer.size() > TrueLen)
			{
				uqstl::memcpy(buffer.data(), TrueText, TrueLen);
				buffer[TrueLen] = '\0';
			}
			else
			{
				buffer[0] = '\0';
			}
		}
		else
		{
			if (buffer.size() > FalseLen)
			{
				uqstl::memcpy(buffer.data(), FalseText, FalseLen);
				buffer[FalseLen] = '\0';
			}
			else
			{
				buffer[0] = '\0';
			}
		}
		return buffer.data();
	}

	const auto [_, len] {fmt::format_to_n(buffer.data(), buffer.size() - 1, "{}", value)};
	buffer[len] = '\0';
	return buffer.data();
}

template <typename E, uqstl::enable_if_t<std::is_enum_v<E>, bool> = true>
[[nodiscard]] inline uqstl::optional<E> fromString(const uqstl::string_view s)
{
	return magic_enum::enum_cast<E>(s, magic_enum::case_insensitive);
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
[[nodiscard]] inline constexpr const char* c_str<char*>(char* const& str) noexcept
{
	return str;
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

template <typename T, typename uqstl::enable_if_t<std::is_enum_v<T>, bool> = true>
inline uqstl::errc parseStr(uqstl::string_view str, T& out)
{
	using UnderlyingT = std::underlying_type_t<T>;

	UnderlyingT intermediate {};
	const auto ec {parseStr(str, intermediate)};
	if (ec == std::errc {}) [[likely]]
	{
		out = static_cast<T>(intermediate);
	}
	return ec;
}

template <typename E>
struct EnumNames
{
	template <typename T = uqstl::string_view>
	static auto list() -> uqstl::vector<T>
	{
		uqstl::vector<T> out {};
		for (const auto& name : magic_enum::enum_names<E>())
		{
			out.emplace_back(name);
		}
		return out;
	}

};
} // namespace uqm

namespace fmt
{
// same as format_to_n, but zero-terminates the string. "outSize" must be large enough to
// accomodate the trailing null terminator.
template <typename OutputIt, typename... T,
		  FMT_ENABLE_IF(detail::is_output_iterator<OutputIt, char>::value)>
FMT_INLINE auto format_to_sz_n(OutputIt out, size_t outSize, format_string<T...> fmt,
							   T&&... args) -> format_to_n_result<OutputIt>
{
	const auto result {vformat_to_n(out, outSize - 1, fmt.str, vargs<T...> {{args...}})};
	*result.out = '\0';
	return result;
}


template <typename E>
	requires ::std::is_enum_v<E>
struct formatter<E> : formatter<std::underlying_type_t<E>>
{
	using base_formatter = formatter<std::underlying_type_t<E>>;

	bool m_useString {false};
	bool m_includeNumericValueWithString {false};

	constexpr auto parse(format_parse_context& ctx)
	{
		if (auto it {ctx.begin()}; it != ctx.end() && *it == 's')
		{
#ifndef WITH_MAGIC_ENUM
			if constexpr (!::uqm::HasToStringImpl<E>)
			{
				fmt::report_error("Enum requires a toString() impl to use the 's' specifier, or install the magic_enum library.");
			}
#endif

			m_useString = true;
			++it;
			// 's' followed by 'n' will output the numeric value as well.
			if (it != ctx.end() && *it == 'n')
			{
				m_includeNumericValueWithString = true;
				++it;
			}
			ctx.advance_to(it);
		}

		return base_formatter::parse(ctx);
	}

	template <typename FormatContext>
	auto format(E value, FormatContext& ctx) const -> format_context::iterator
	{
		auto out {ctx.out()};
		if (m_useString)
		{
#ifdef WITH_MAGIC_ENUM
			// a toString implementation will override the magic_enum output.
			if constexpr (::uqm::HasToStringImpl<E>)
			{
				out = fmt::format_to(out, "{}", toStringImpl(value));
			}
			else
			{
				out = fmt::format_to(out, "{}", magic_enum::enum_name(value));
			}
#else
			out = fmt::format_to(out, "{}", toString(value));
#endif
			if (m_includeNumericValueWithString)
			{
				*out++ = ' ';
				*out++ = '(';
				out = base_formatter::format(static_cast<std::underlying_type_t<E>>(value), ctx);
				*out++ = ')';
			}

			return out;
		}

		return base_formatter::format(static_cast<std::underlying_type_t<E>>(value), ctx);
	}
};

template <typename E>
struct formatter<::uqm::EnumNames<E>> : formatter<E>
{
	using base_formatter = formatter<E>;
	const char* m_sep {", "};

	constexpr auto parse(format_parse_context& ctx)
	{
		if (auto it {ctx.begin()}; it != ctx.end() && *it == '|')
		{
			m_sep = " | ";
			++it;
			ctx.advance_to(it);
		}

		return base_formatter::parse(ctx);
	}

	template <typename FormatContext>
	auto format(::uqm::EnumNames<E> value, FormatContext& ctx) const -> format_context::iterator
	{
		auto out {ctx.out()};
		static constexpr auto enumValues {magic_enum::enum_values<E>()};
		bool first {true};
		for (const auto val : enumValues)
		{
			if (!first)
			{
				out = fmt::format_to(out, "{}", m_sep);
			}
			out = base_formatter::format(static_cast<E>(val), ctx);
			first = false;
		}

		return out;
	}
};

} // namespace fmt

#endif /* UQM_CORE_STRING_STRINGUTILS_H_ */
