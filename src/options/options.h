#pragma once

#include "core/stl/stl.h"
#include "core/string/StringUtils.h"
#include "options/OptionConstants.h"
#include "options/OptionTypes.h"

#include "libs/math/randomdefs.h" // TODO: only used for the PrimeA constant and SeedType. Find a better way to share that perhaps?
#include "libs/platform.h"

namespace uqm
{

struct OptionsStruct
{
	// Commandline-only options
	RunMode runMode {RunMode::Normal};
	std::string logFile {};
	std::string configDir {};
	std::string contentDir {};
	std::string addonDir {};
	uqstl::vector<std::string> addons {};

	std::string graphicsBackend {};

	// Commandline and user config options
	BoolOption opengl {false};
	OptionT<Resolution> resolution {
		{640, 480}
	  };
	IntOption fullscreen {2}; // TODO: what is "2"?
	BoolOption scanlines {false};
	IntOption scaler {0};
	BoolOption showFps {false};
	BoolOption keepAspectRatio {false};
	FloatOption gamma {1.0f};
	IntOption soundDriver {audio_DRIVER_MIXSDL};
	IntOption soundQuality {audio_QUALITY_HIGH};
	BoolOption use3doMusic {true};
	BoolOption useRemixMusic {false};
	BoolOption useSpeech {true};
	IntOption whichCoarseScan {0};
	EmulationOption whichMenu {uqm::EmulationMode::PC};
	EmulationOption whichFonts {uqm::EmulationMode::PC};
	EmulationOption whichIntro {uqm::EmulationMode::PC};
	EmulationOption whichShield {uqm::EmulationMode::PC};
	EmulationOption smoothScroll {uqm::EmulationMode::PC};
	IntOption meleeScale {TFB_SCALE_TRILINEAR};
	BoolOption subtitles {true};
	BoolOption stereoSFX {false};
	FloatOption musicVolumeScale {1.0f};
	FloatOption sfxVolumeScale {1.0f};
	FloatOption speechVolumeScale {1.0f};
	BoolOption safeMode {false};
	// megamod options
	IntOption resolutionFactor {0};
	IntOption loresBlowupScale {1};
	BoolOption cheatMode {false};
	IntOption optGodModes {0};
	IntOption timeDilationScale {0};
	BoolOption bubbleWarp {false};
	BoolOption unlockShips {false};
	BoolOption headStart {false};
	BoolOption unlockUpgrades {false};
	BoolOption infiniteRU {false};
	BoolOption skipIntro {false};
	BoolOption mainMenuMusic {true};
	BoolOption nebulae {false};
	BoolOption orbitingPlanets {false};
	BoolOption texturedPlanets {false};
	IntOption optDateFormat {0};
	BoolOption infiniteFuel {false};
	BoolOption partialPickup {false};
	BoolOption submenu {false};
	BoolOption infiniteCredits {false};
	BoolOption customBorder {false};
	OptionT<SeedType> seedType {SeedType::None};
	IntOption customSeed {PrimeA};
	BoolOption shipSeed {false};
	IntOption sphereColors {0};
	IntOption spaceMusic {0};
	BoolOption volasMusic {false};
	BoolOption wholeFuel {false};
	BoolOption directionalJoystick {false};
	EmulationOption landerHold {uqm::EmulationMode::Console3DO};
	EmulationOption scrTrans {uqm::EmulationMode::Console3DO};
	IntOption optDifficulty {0};
	IntOption optDiffChooser {3};
	IntOption optFuelRange {0};
	BoolOption extended {false};
	IntOption nomad {0};
	BoolOption gameOver {false};
	BoolOption shipDirectionIP {false};
	BoolOption hazardColors {false};
	BoolOption orzCompFont {false};
	IntOption optControllerType {0};
	BoolOption smartAutoPilot {false};
	EmulationOption tintPlanSphere {uqm::EmulationMode::Console3DO};
	EmulationOption planetStyle {uqm::EmulationMode::Console3DO};
	IntOption starBackground {0};
	EmulationOption scanStyle {uqm::EmulationMode::Console3DO};
	BoolOption nonStopOscill {false};
	EmulationOption scopeStyle {uqm::EmulationMode::Console3DO};
	BoolOption hyperStars {false};
	EmulationOption landerStyle {uqm::EmulationMode::Console3DO};
	BoolOption planetTexture {true};
	EmulationOption flagshipColor {uqm::EmulationMode::PC};
	BoolOption noHQEncounters {false};
	BoolOption deCleansing {false};
	BoolOption meleeObstacles {false};
	BoolOption showVisitedStars {false};
	BoolOption unscaledStarSystem {false};
	IntOption sphereType {2};
	IntOption nebulaevol {16};
	BoolOption slaughterMode {false};
	BoolOption advancedAutoPilot {false};
	BoolOption meleeToolTips {false};
	IntOption musicResume {0};
	IntOption windowType {2};
	BoolOption scatterElements {false};
	BoolOption showUpgrades {false};
	BoolOption fleetPointSys {false};
	BoolOption shipStore {false};
	BoolOption captainNames {false};
	BoolOption dosMenus {false};
};

template <typename ListT>
[[nodiscard]] inline uqstl::optional<typename ListT::value_type::value_type> getOptionListValue(const ListT& list, uqstl::string_view name) noexcept
{
	for (const auto& item : list)
	{
		if (name.compare(item.name) == 0)
		{
			return {item.value};
		}
	}
	return uqstl::nullopt;
}

template <typename OptionValueT>
[[nodiscard]] inline uqstl::optional<OptionValueT> parseOptionValue(uqstl::string_view valueStr, uqstl::string_view optionName)
{
	OptionValueT destValue {};
	const uqstl::errc errCode {parseStr(valueStr, destValue)};

	if (errCode == std::errc {})
	{
		return {destValue};
	}
	else if (errCode == std::errc::invalid_argument)
	{
		throw std::invalid_argument(fmt::format("Invalid string for {} option value '{}'.", optionName, valueStr));
	}
	else if (errCode == std::errc::result_out_of_range)
	{
		throw std::out_of_range(fmt::format("The value '{}' held in the option string for {} is too large to be held by the option.", valueStr, optionName));
	}
	return {};
}

template <typename OptionT, typename OptionValueT = typename OptionT::value_type>
inline bool parseOption(OptionT& option, uqstl::string_view valueStr, uqstl::string_view optionName)
{
	if (const auto optionValue {parseOptionValue<OptionValueT>(valueStr, optionName)}; optionValue.has_value())
	{
		option = optionValue.value();
		return true;
	}

	return false;
}

template <>
inline bool parseOption(EmulationOption& option, uqstl::string_view valueStr, uqstl::string_view optionName)
{
	if (const auto listValue {getOptionListValue(EmulationChoiceList, valueStr)}; listValue.has_value())
	{
		option = *listValue;
		return true;
	}
	return false;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

int parseOptions(uqstl::span<uqgsl::czstring const> args, OptionsStruct& options);
void printUsage(FILE* out, const OptionsStruct& defaultOptions);

template <typename InT>
[[nodiscard]] inline float normalizeValue(const InT inVol, const InT max) noexcept
{
	if (inVol < InT {})
	{
		return 0.0f;
	}

	if (inVol > max)
	{
		return 1.0f;
	}

	return inVol / static_cast<float>(max);
}

} // namespace uqm