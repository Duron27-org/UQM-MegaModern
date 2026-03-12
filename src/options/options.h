#pragma once

#include "core/stl/stl.h"
#include "core/string/StringUtils.h"
#include "options/netoptions.h"
#include "options/OptionConstants.h"
#include "options/OptionTypes.h"
#include "options/OptionDefs.h"

#include "lib/Math2D/Math2D.h"
#include "libs/math/randomdefs.h" // TODO: only used for the PrimeA constant and SeedType. Find a better way to share that perhaps?
#include "libs/platform.h"

namespace uqm
{

enum class RunMode
{
	Normal,
	Usage,
	Version,
};


struct OptionsStruct
{
	// Commandline-only options
	RunMode runMode {RunMode::Normal};		// Controls whether the game runs normally or just prints version/usage.
	uqstl::string logFile {};				// Path to the log output file.
	uqstl::string configDir {};				// Directory where uqm.cfg and other config files are read/written.
	uqstl::string contentDir {};			// Root directory for game content packages (.uqm files).
	uqstl::string addonDir {};				// Directory scanned for optional add-on packages.
	uqstl::vector<uqstl::string> addons {}; // Ordered list of add-on package names to load at startup.

	uqstl::string graphicsBackend {}; // SDL renderer backend hint passed to TFB_InitGraphics.

	// Commandline and user config options
	BoolOption opengl {false}; // Force OpenGL renderer on SDL1 builds; ignored on SDL2.
	OptionT<Vec2u> resolution {
		{640, 480}
	  };												// Window/framebuffer pixel dimensions when not using a blowup scaler.
	OptionT<WindowMode> windowMode {WindowMode::Fullscreen};		// Windowed, windowed-fullscreen, or exclusive fullscreen.
	BoolOption scanlines {false};									// Overlay a scanline effect over the rendered frame.
	OptionT<ScalingMode> scaler {ScalingMode::None};				// Post-process pixel scaler applied when blitting to the display.
	BoolOption showFps {false};										// Draw an on-screen frames-per-second counter.
	BoolOption keepAspectRatio {false};								// Letterbox/pillarbox to preserve the native 4:3 aspect ratio.
	FloatOption gamma {1.0f};										// Display gamma correction value applied via the GPU or SDL.
	OptionT<AudioDriverType> soundDriver {AudioDriverType::MixSDL}; // Backend used for audio output (MixSDL, OpenAL, or silence).
	OptionT<AudioQuality> soundQuality {AudioQuality::High};		// Resampling quality level for the audio mixer.
	BoolOption use3doMusic {true};									// Play the 3DO remixed music tracks instead of the PC MIDI/MOD originals.
	BoolOption useRemixMusic {false};								// Play the Precursors fan-remix music pack when available.
	BoolOption useSpeech {true};									// Enable voiced dialogue during alien conversations.
	EmulationOption whichCoarseScan {EmulationMode::PC};			// Planetary coarse-scan display: iconic (PC) or full image (3DO).
	EmulationOption whichMenu {uqm::EmulationMode::PC};				// Main menu layout: text list (PC) or animated orb (3DO).
	EmulationOption whichFonts {uqm::EmulationMode::PC};			// Text rendering style: flat PC fonts or gradient 3DO fonts.
	EmulationOption whichIntro {uqm::EmulationMode::PC};			// Introduction sequence: slides (PC) or FMV movies (3DO).
	EmulationOption whichShield {uqm::EmulationMode::PC};			// Flagship shield appearance: static (PC) or animated pulse (3DO).
	EmulationOption smoothScroll {uqm::EmulationMode::PC};			// Starmap/comm scrolling: stepped (PC) or smooth (3DO).
	OptionT<MeleeScaleMode> meleeScale {MeleeScaleMode::Smooth};	// Scaling algorithm used when zooming the melee battle view.
	BoolOption subtitles {true};									// Show text subtitles alongside voiced alien dialogue.
	BoolOption stereoSFX {false};									// Pan sound effects in stereo based on screen position.
	FloatOption musicVolumeScale {1.0f};							// Master volume multiplier for background music (0–1).
	FloatOption sfxVolumeScale {1.0f};								// Master volume multiplier for sound effects (0–1).
	FloatOption speechVolumeScale {1.0f};							// Master volume multiplier for speech audio (0–1).
	BoolOption safeMode {false};									// Skip loading uqm.cfg so the game starts with all defaults.

	// megamod options
	IntOption resolutionFactor {0};													  // HD scale factor: 0 = SD (320×240), 2 = HD (640×480 canvas).
	IntOption loresBlowupScale {1};													  // Integer upscale applied to the SD canvas for windowed HD displays.
	BoolOption cheatMode {false};													  // Freeze the Kohr-Ah death march timer so their fleet never advances.
	OptionT<GodModeFlags> optGodModes {GodModeFlags::None};							  // Bitfield enabling infinite battery and/or no-damage in combat.
	IntOption timeDilationPct {100};												  // Game clock speed as a percentage of normal (100 = real-time).
	BoolOption bubbleWarp {false};													  // Allow warping to any star system regardless of fuel range.
	BoolOption unlockShips {false};													  // Make all ships available in the Full-Game Melee roster from the start.
	BoolOption headStart {false};													  // Begin the campaign with extra fuel, RU, and crew.
	BoolOption unlockUpgrades {false};												  // Make all ship upgrades purchasable immediately at the starbase.
	BoolOption infiniteRU {false};													  // Grant unlimited Resource Units so the player never runs out of money.
	BoolOption skipIntro {false};													  // Jump past the opening intro sequence directly to the main menu.
	BoolOption mainMenuMusic {true};												  // Play background music on the main menu screen.
	BoolOption nebulae {false};														  // Render nebula cloud artwork in the Hyperspace star map.
	BoolOption orbitingPlanets {false};												  // Animate planets orbiting their star in the solar system view.
	BoolOption texturedPlanets {false};												  // Apply surface texture maps to planets in the solar system view.
	OptionT<DateFormat> optDateFormat {DateFormat::MMM_dd_yyyy};					  // Date display format shown on the starmap HUD clock.
	BoolOption infiniteFuel {false};												  // Flagship fuel never depletes during hyperspace travel.
	BoolOption partialPickup {false};												  // Allow picking up a partial mineral load when the lander is nearly full.
	BoolOption submenu {false};														  // Show an extra submenu layer in the in-flight status/outfit screens.
	BoolOption infiniteCredits {false};												  // Crew cost at the starbase is waived; credits never decrease.
	BoolOption customBorder {false};												  // Draw a decorative border frame around the game viewport.
	OptionT<SeedType> seedType {SeedType::None};									  // Algorithm used to generate the galaxy map seed (None, Planet, MRQ, etc.).
	IntOption customSeed {PrimeA};													  // Explicit seed value fed to the star/planet generation RNG.
	BoolOption shipSeed {false};													  // Derive the starting ship layout from the custom seed instead of a fixed value.
	OptionT<SphereOfInfluenceColors> sphereColors {SphereOfInfluenceColors::Default}; // Color scheme for alien sphere-of-influence overlays on the starmap.
	OptionT<SphereOfInfluenceMusic> spaceMusic {SphereOfInfluenceMusic::None};		  // Switch hyperspace music to the race whose SOI the flagship is inside.
	BoolOption volasMusic {false};													  // Enable the Volasaurus fan-remix music pack when available.
	BoolOption wholeFuel {false};													  // Snap fuel pickup amounts to whole units, avoiding fractional values.
	BoolOption directionalJoystick {false};											  // Treat joystick input as a D-pad (Android/touch-device support).
	EmulationOption landerHold {EmulationMode::Console3DO};							  // Lander cargo-hold display: text list (PC) or graphical icons (3DO).
	EmulationOption scrTrans {EmulationMode::Console3DO};							  // Screen-transition style: cut (PC) or crossfade (3DO).
	OptionT<Difficulty> optDifficulty {Difficulty::Normal};							  // Active difficulty level applied to game mechanics (Normal/Easy/Hard).
	OptionT<Difficulty> optDiffChooser {Difficulty::ChooseYourOwn};					  // Difficulty shown in the setup menu (may be ChooseYourOwn).
	OptionT<FuelRangeDisplay> optFuelRange {FuelRangeDisplay::Normal};				  // Starmap fuel-range indicator style (circle, destination, Sol distance).
	BoolOption extended {false};													  // Enable extended game content (extra star systems, dialogue, events).
	OptionT<NomadMode> nomad {NomadMode::Off};										  // Nomad variant: starts the player without a homeworld or starbase.
	BoolOption gameOver {false};													  // End the game when the flagship is destroyed instead of retrying.
	BoolOption shipDirectionIP {false};												  // Rotate the flagship icon to face its travel direction in interplanetary space.
	BoolOption hazardColors {false};												  // Color-code planetary hazard indicators (bio, weather, tectonics) distinctly.
	BoolOption orzCompFont {false};													  // Use a compact font variant for Orz dialogue to fit their unusual phrasing.

	OptionT<ControllerType> optControllerType {ControllerType::KeyboardMouse}; // Button-prompt artwork set: keyboard/mouse, Xbox, or PlayStation layout.
	BoolOption smartAutoPilot {false};										   // Auto-pilot avoids obstacles and optimises the hyperspace route to the destination.
	EmulationOption tintPlanSphere {uqm::EmulationMode::Console3DO};		   // Tint the planet sphere with its dominant surface color (3DO style).
	EmulationOption planetStyle {uqm::EmulationMode::Console3DO};			   // Planet rendering pipeline: PC flat-color or 3DO shaded sphere.
	IntOption starBackground {0};											   // Starfield density/style index used in the Hyperspace and combat backgrounds.
	EmulationOption scanStyle {uqm::EmulationMode::Console3DO};				   // Planetary scan display layout: PC text readout or 3DO graphical panels.
	BoolOption nonStopOscill {false};										   // Keep the comm oscilloscope animating continuously instead of only during speech.
	EmulationOption scopeStyle {uqm::EmulationMode::Console3DO};			   // Oscilloscope visual style: simple PC waveform or stylized 3DO display.
	BoolOption hyperStars {false};											   // Draw animated star-streak effect during hyperspace travel.
	EmulationOption landerStyle {uqm::EmulationMode::Console3DO};			   // Planetary lander mini-game rendering: PC sprites or 3DO visuals.
	BoolOption planetTexture {true};										   // Apply surface detail textures to the rotating planet sphere.
	EmulationOption flagshipColor {uqm::EmulationMode::PC};					   // Flagship hull color palette: original PC blue or 3DO gold scheme.
	BoolOption noHQEncounters {false};										   // Suppress random Hierarchy ship encounters in Ur-Quan-controlled space.
	BoolOption deCleansing {false};											   // Remove the Kohr-Ah Cleansing event so the death march never triggers a loss.
	BoolOption meleeObstacles {false};										   // Spawn asteroid/obstacle fields in the melee combat arena.
	BoolOption showVisitedStars {false};									   // Mark previously visited star systems with a distinct icon on the starmap.
	BoolOption unscaledStarSystem {false};									   // Display the solar system view at native canvas resolution without HD scaling.
	IntOption sphereType {2};												   // Visual style index for the sphere-of-influence overlay (filled, outline, etc.).
	IntOption nebulaevol {16};												   // Opacity/density of the hyperspace nebula cloud overlay (0–50).
	BoolOption slaughterMode {false};										   // Hostile alien ships no longer flee combat, always fighting to the death.
	BoolOption advancedAutoPilot {false};									   // Auto-pilot also handles refuelling stops and quasispace portal navigation.
	BoolOption meleeToolTips {false};										   // Show contextual control hints during melee battles.
	IntOption musicResume {0};												   // Music resume mode: 0 = restart track, 1 = resume from last position.
	IntOption windowEmulationMode {2};										   // Window chrome/border style: 0 = DOS, 1 = 3DO, 2 = UQM native.
	BoolOption scatterElements {false};										   // Scatter mineral element deposits randomly across the planet surface.
	BoolOption showUpgrades {false};										   // Display purchased ship-upgrade icons in the flagship status screen.
	BoolOption fleetPointSys {false};										   // Use a fleet-point budget system to limit ships chosen in Full-Game Melee.
	BoolOption shipStore {false};											   // Enable a ship store at the starbase where ally vessels can be purchased.
	BoolOption captainNames {false};										   // Show individual captain names on ships in the melee roster.
	BoolOption dosMenus {false};											   // Use the DOS-style text menus for outfit, crew, and fuel purchasing screens.
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

class UQMOptions
{
public:
	UQMOptions();
	~UQMOptions();

	[[nodiscard]] static UQMOptions& getInstance();

	// Returns an [exit code, needs exit] result.
	uqstl::pair<int, bool> parseArgs(uqstl::span<uqgsl::zstring> args);
	//void printUsage(FILE* out, const OptionsStruct& defaultOptions);

	const OptionsStruct& get() const
	{
		return m_options;
	}

	static const OptionsStruct& read()
	{
		return getInstance().m_options;
	}

	static OptionsStruct& edit()
	{
		return getInstance().m_options;
	}
#ifdef NETPLAY
	NetplayOptions& getNetplayOptions()
	{
		return m_netplayOptions;
	}
#endif


private:
	OptionsStruct m_options;
#ifdef NETPLAY
	NetplayOptions m_netplayOptions;
#endif

	static UQMOptions* s_instance;
};

} // namespace uqm