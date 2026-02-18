#pragma once
#ifndef OPTIONS_OPTIONDEFS_H_
#define OPTIONS_OPTIONDEFS_H_

#include "libs/graphics/gfx_defs.h" // for GfxFlags*

namespace uqm
{

///////////////////////////////////////////////////////////////////////////////////////////////////

enum class SeedType
{
	None = 0,
	Planet = 1,
	MRQ = 2,
	Prime = 3,
	StarSeed = 4
};

///////////////////////////////////////////////////////////////////////////////////////////////////

enum class EmulationMode : int
{
	None = 0x0,
	Console3DO = 0x1, // would just call it "3d0" but enum names can't start with a number.
	PC = 0x2,
	All = 0xFF
};
ENUM_BITWISE_OPS(EmulationMode);

static constexpr const char* toStringImpl(const EmulationMode e)
{
	switch (e)
	{
		case EmulationMode::None:
			return "None";
		case EmulationMode::Console3DO:
			return "3DO";
		case EmulationMode::PC:
			return "PC";
		case EmulationMode::All:
			return "All";
	}
	return "???";
}

///////////////////////////////////////////////////////////////////////////////////////////////////

enum class WindowMode
{
	Windowed,
	WindowedFullscreen,
	Fullscreen,
};

///////////////////////////////////////////////////////////////////////////////////////////////////

enum class ScalingMode : int
{
	None,
	Bilinear = static_cast<int>(GfxFlags::Scale_Bilinear),
	BiAdapt = static_cast<int>(GfxFlags::Scale_BiAdapt),
	BiAdaptAdv = static_cast<int>(GfxFlags::Scale_BiAdaptAdv),
	Triscan = static_cast<int>(GfxFlags::Scale_Triscan),
	HQ = static_cast<int>(GfxFlags::Scale_HQXX),
};
static constexpr GfxFlags toGfxFlags(const ScalingMode mode)
{
	return static_cast<GfxFlags>(mode);
}

///////////////////////////////////////////////////////////////////////////////////////////////////

enum class MeleeScaleMode : int
{
	Step,
	PC,
	Nearest,
	Bilinear,
	Console3DO,
	Smooth,
};
static constexpr TFBScaleMode toTFBScaleMode(const MeleeScaleMode mode)
{
	switch (mode)
	{
		case MeleeScaleMode::Step:
			return TFBScaleMode::Step;
		case MeleeScaleMode::PC:
			return TFBScaleMode::Step;
		case MeleeScaleMode::Nearest:
			return TFBScaleMode::Nearest;
		case MeleeScaleMode::Bilinear:
			return TFBScaleMode::Bilinear;
		case MeleeScaleMode::Console3DO:
			return TFBScaleMode::Trilinear;
		case MeleeScaleMode::Smooth:
			return TFBScaleMode::Trilinear;
	}
	return TFBScaleMode::Step;
}
static constexpr MeleeScaleMode toMeleeScaleMode(const TFBScaleMode mode)
{
	switch (mode)
	{
		case TFBScaleMode::None:
			break;
		case TFBScaleMode::Step:
			return MeleeScaleMode::PC; // also MeleeScaleMode::Step
		case TFBScaleMode::Nearest:
			return MeleeScaleMode::Nearest;
		case TFBScaleMode::Bilinear:
			return MeleeScaleMode::Bilinear;
		case TFBScaleMode::Trilinear:
			return MeleeScaleMode::Console3DO; // also MeleeScaleMode::Smooth
	}
	return MeleeScaleMode::Step;
}


static constexpr const char* toStringImpl(const MeleeScaleMode mode)
{
	switch (mode)
	{
		case MeleeScaleMode::Step: // = TFB_SCALE_STEP,
			return "Step";
		case MeleeScaleMode::PC: // = TFB_SCALE_STEP,
			return "PC";
		case MeleeScaleMode::Nearest: // = TFB_SCALE_NEAREST,
			return "Nearest";
		case MeleeScaleMode::Bilinear: // = TFB_SCALE_BILINEAR,
			return "Bilinear";
		case MeleeScaleMode::Console3DO: // = TFB_SCALE_TRILINEAR,
			return "3DO";
		case MeleeScaleMode::Smooth: // = TFB_SCALE_TRILINEAR,
			return "Smooth";
	}
	return "???";
}


//static inline constexpr uqstl::array<OptionListValueT<int>, 6> MeleeScaleList {
//	{{"smooth", TFB_SCALE_TRILINEAR},
//	 {"3do", TFB_SCALE_TRILINEAR},
//	 {"step", TFB_SCALE_STEP},
//	 {"pc", TFB_SCALE_STEP},
//	 {"bilinear", TFB_SCALE_BILINEAR},
//	 {"nearest", TFB_SCALE_NEAREST}}
//};
//static inline constexpr uqstl::array<OptionListValueT<int>, 7> ScalerList {
//	{
//		{"bilinear", TFB_GFXFLAGS_SCALE_BILINEAR},
//		{"biadapt", TFB_GFXFLAGS_SCALE_BIADAPT},
//		{"biadv", TFB_GFXFLAGS_SCALE_BIADAPTADV},
//		{"triscan", TFB_GFXFLAGS_SCALE_TRISCAN},
//		{"hq", TFB_GFXFLAGS_SCALE_HQXX},
//		{"none", 0},
//		{"no", 0}, /* uqm.cfg value */
//	}
//};

///////////////////////////////////////////////////////////////////////////////////////////////////

} // namespace uqm

#endif /* OPTIONS_OPTIONDEFS_H_ */