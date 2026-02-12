#pragma once
#ifndef UQM_OPTIONS_OPTIONTYPES_H_
#define UQM_OPTIONS_OPTIONTYPES_H_

#include "core/stl/stl.h"
#include "core/types/enum.h"

enum class SeedType
{
	None = 0,
	Planet = 1,
	MRQ = 2,
	Prime = 3,
	StarSeed = 4
};
[[nodiscard]] inline constexpr const char* toString(const SeedType type)
{
	switch (type)
	{
		case SeedType::None:
			return "None";
		case SeedType::Planet:
			return "Planet";
		case SeedType::MRQ:
			return "MRQ";
		case SeedType::Prime:
			return "Prime";
		case SeedType::StarSeed:
			return "StarSeed";
		default:
			return "???";
	}
};

enum class EmulationMode : int
{
	None = 0x0,
	Console3DO = 0x1, // would just call it "3d0" but enum names can't start with a number.
	PC = 0x2,
	All = 0xFF
};
ENUM_BITWISE_OPS(EmulationMode);
[[nodiscard]] constexpr const char* toString(const EmulationMode mode)
{
	switch (mode)
	{
		case EmulationMode::None:
			return "None";
		case EmulationMode::Console3DO:
			return "3DO";
		case EmulationMode::PC:
			return "PC";
		case EmulationMode::All:
			return "All";
		default:
			return "???";
	}
};


///////////////////////////////////////////////////////////////////////////////////////////////////
//* Option types
//*
//* These are the types of options used by the setup menu and config file. They are designed to be
//* simple and easy to use, but they don't have any built-in validation or range checking, so be
//* careful when using them.
///////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
struct OptionT
{
	using value_type = T;

	T value {};
	bool set {};

	constexpr OptionT() = default;
	constexpr explicit OptionT(T defaultValue)
		: value(defaultValue)
	{
	}

	T operator=(T newValue)
	{
		value = newValue;
		set = true;
		return newValue;
	}

	T operator*() const
	{
		return value;
	}
	operator T() const
	{
		return value;
	}

	const char* toString() const;
};

template <typename T>
struct OptionListValueT
{
	using value_type = T;
	uqgsl::czstring name {};
	T value {};
};

using BoolOption = OptionT<bool>;
using IntOption = OptionT<int>;
using FloatOption = OptionT<float>;
using EmulationOption = OptionT<EmulationMode>;

static inline constexpr const char* OptionTrueText {"on"};
static inline constexpr const char* OptionFalseText {"off"};

template <typename T>
inline const char* OptionT<T>::toString() const
{
	return ::toString(value);
}

template <>
inline const char* OptionT<bool>::toString() const
{
	return value ? OptionTrueText : OptionFalseText;
}

struct Resolution // TODO: Replace this with a standard 2D vector type.
{
	int width {};
	int height {};
};

enum class RunMode
{
	Normal,
	Usage,
	Version,
};



#endif /* UQM_OPTIONS_OPTIONTYPES_H_ */