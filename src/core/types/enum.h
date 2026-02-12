#pragma once
#include <type_traits>

#define ENUM_BITWISE_OPS(enumName)                                                                                                             \
	[[nodiscard]] inline enumName operator|(enumName lhs, enumName rhs) noexcept                                                               \
	{                                                                                                                                          \
		return static_cast<enumName>(static_cast<std::underlying_type_t<enumName>>(lhs) | static_cast<std::underlying_type_t<enumName>>(rhs)); \
	}                                                                                                                                          \
	[[nodiscard]] inline enumName operator&(enumName lhs, enumName rhs) noexcept                                                               \
	{                                                                                                                                          \
		return static_cast<enumName>(static_cast<std::underlying_type_t<enumName>>(lhs) & static_cast<std::underlying_type_t<enumName>>(rhs)); \
	}                                                                                                                                          \
	[[nodiscard]] inline enumName operator^(enumName lhs, enumName rhs) noexcept                                                               \
	{                                                                                                                                          \
		return static_cast<enumName>(static_cast<std::underlying_type_t<enumName>>(lhs) ^ static_cast<std::underlying_type_t<enumName>>(rhs)); \
	}                                                                                                                                          \
	[[nodiscard]] inline enumName operator~(enumName rhs) noexcept                                                                             \
	{                                                                                                                                          \
		return static_cast<enumName>(~static_cast<std::underlying_type_t<enumName>>(rhs));                                                     \
	}                                                                                                                                          \
	inline enumName& operator|=(enumName& lhs, enumName rhs) noexcept                                                                          \
	{                                                                                                                                          \
		lhs = lhs | rhs;                                                                                                                       \
		return lhs;                                                                                                                            \
	}                                                                                                                                          \
	inline enumName& operator&=(enumName& lhs, enumName rhs) noexcept                                                                          \
	{                                                                                                                                          \
		lhs = lhs & rhs;                                                                                                                       \
		return lhs;                                                                                                                            \
	}                                                                                                                                          \
	inline enumName& operator^=(enumName& lhs, enumName rhs) noexcept                                                                          \
	{                                                                                                                                          \
		lhs = lhs ^ rhs;                                                                                                                       \
		return lhs;                                                                                                                            \
	}                                                                                                                                          \
	[[nodiscard]] inline bool testBit(enumName lhs, enumName rhs) noexcept                                                                     \
	{                                                                                                                                          \
		return (lhs & rhs) != static_cast<enumName>(0);                                                                                        \
	}                                                                                                                                          \
	[[nodiscard]] inline bool testAllBits(enumName lhs, enumName rhs) noexcept                                                                 \
	{                                                                                                                                          \
		return (lhs & rhs) == rhs;                                                                                                             \
	}
