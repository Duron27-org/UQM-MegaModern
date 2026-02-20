
#include "options.h"
#include "options/options.h"
#include "Configuration.h" // TODO: Figure out why this has to go here for OptionsStruct to be recognized by the header.
#include "core/log/log.h"

namespace uqm
{

static void getBoolConfigValue(BoolOption& option, const char* config_val)
{
	if (option.set || !res_IsBoolean(config_val))
	{
		return;
	}

	option.value = res_GetBoolean(config_val);
	option.set = true;
}

template <typename OptionT, typename OptionValueT = typename OptionT::value_type>
static void getBoolConfigValueXlat(OptionT& option, const char* config_val, OptionValueT true_val, OptionValueT false_val)
{
	if (option.set || !res_IsBoolean(config_val))
	{
		return;
	}

	option.value = res_GetBoolean(config_val) ? true_val : false_val;
	option.set = true;
}

static void getVolumeConfigValue(FloatOption& option, const char* config_val)
{
	if (option.set || !res_IsInteger(config_val))
	{
		return;
	}

	option = normalizeValue(res_GetInteger(config_val), 100);
}

static void getGammaConfigValue(FloatOption& option, const char* config_val)
{
	if (option.set || !res_IsInteger(config_val))
	{
		return;
	}

	const int val = res_GetInteger(config_val);
	// gamma config option is a fixed-point number
	// ignore ridiculously out-of-range values
	if (val < (int)(0.03 * GAMMA_SCALE) || val > (int)(9.9 * GAMMA_SCALE))
	{
		return;
	}
	option.value = val / (float)GAMMA_SCALE;
	// avoid setting gamma when not necessary
	if (option.value != 1.0f)
	{
		option.set = true;
	}
}

template <typename OptionType, typename OptionListT>
static bool getListConfigValue(OptionType& option, const char* config_val, const OptionListT& list)
{
	if (option.set || !res_IsString(config_val) || list.empty())
	{
		return false;
	}

	const char* strval = res_GetString(config_val);
	if (const auto val {getOptionListValue(list, strval)}; val.has_value())
	{
		option = *val;
		return true;
	}

	return false;
}

template <typename E>
static bool getEnumConfigValue(OptionT<E>& option, const char* config_val)
{
	if (option.set || !res_IsString(config_val))
	{
		return false;
	}

	const char* strval = res_GetString(config_val);
	if (const auto val {fromString<E>(strval)}; val.has_value())
	{
		option = *val;
		return true;
	}

	return false;
}

void getUserConfigOptions(OptionsStruct& options)
{
	// Most of the user config options are only applied if they
	// have not already been set (i.e. on the commandline)

	if (res_IsInteger("config.reswidth")
		&& res_IsInteger("config.resheight")
		&& !options.resolution.set)
	{
		options.resolution.value.x = res_GetInteger("config.reswidth");
		options.resolution.value.y = res_GetInteger("config.resheight");
		options.resolution.set = true;
	}

	if (res_IsBoolean("config.alwaysgl") && !options.opengl.set)
	{ // config.alwaysgl is processed differently than others
		// Only set when it's 'true'
		if (res_GetBoolean("config.alwaysgl"))
		{
			options.opengl.value = true;
			options.opengl.set = true;
		}
	}
	getBoolConfigValue(options.opengl, "config.usegl");

	getEnumConfigValue(options.scaler, "config.scaler");

	//getBoolConfigValue (options.fullscreen, "config.fullscreen");
	if (res_IsInteger("config.fullscreen") && !options.windowMode.set)
	{
		options.windowMode.value = (WindowMode)res_GetInteger("config.fullscreen");
	}
	getBoolConfigValue(options.scanlines, "config.scanlines");
	getBoolConfigValue(options.showFps, "config.showfps");
	getBoolConfigValue(options.keepAspectRatio,
					   "config.keepaspectratio");
	getGammaConfigValue(options.gamma, "config.gamma");

	getBoolConfigValue(options.subtitles, "config.subtitles");

	getBoolConfigValueXlat(options.whichMenu, "config.textmenu", uqm::EmulationMode::Console3DO, uqm::EmulationMode::PC);
	getBoolConfigValueXlat(options.whichFonts, "config.textgradients", uqm::EmulationMode::Console3DO, uqm::EmulationMode::PC);
	if (res_IsInteger("config.iconicscan") && !options.whichCoarseScan.set)
	{
		options.whichCoarseScan.value = (EmulationMode)res_GetInteger("config.iconicscan");
	}
	getBoolConfigValueXlat(options.smoothScroll, "config.smoothscroll", uqm::EmulationMode::Console3DO, uqm::EmulationMode::PC);
	getBoolConfigValueXlat(options.whichShield, "config.pulseshield", uqm::EmulationMode::Console3DO, uqm::EmulationMode::PC);
	getBoolConfigValueXlat(options.whichIntro, "config.3domovies", uqm::EmulationMode::Console3DO, uqm::EmulationMode::PC);

	getBoolConfigValue(options.use3doMusic, "config.3domusic");
	getBoolConfigValue(options.useRemixMusic, "config.remixmusic");
	getBoolConfigValue(options.useSpeech, "config.speech");

	getEnumConfigValue(options.meleeScale, "config.meleescale");

	getEnumConfigValue(options.soundDriver, "config.audiodriver");
	getEnumConfigValue(options.soundQuality, "config.audioquality");
	getBoolConfigValue(options.stereoSFX, "config.positionalsfx");
	getVolumeConfigValue(options.musicVolumeScale, "config.musicvol");
	getVolumeConfigValue(options.sfxVolumeScale, "config.sfxvol");
	getVolumeConfigValue(options.speechVolumeScale, "config.speechvol");


	if (res_IsInteger("config.resolutionfactor")
		&& !options.resolutionFactor.set)
	{
		options.resolutionFactor.value =
			res_GetInteger("config.resolutionfactor");
		options.resolutionFactor.set = true;
	}


	if (res_IsInteger("config.loresBlowupScale"))
	{
		options.loresBlowupScale.value =
			res_GetInteger("config.loresBlowupScale");
		options.loresBlowupScale.set = true;
	}

	getBoolConfigValue(options.cheatMode, "cheat.kohrStahp");

	if (res_IsInteger("cheat.godModes") && !options.optGodModes.set)
	{
		options.optGodModes.value = (uqm::GodModeFlags)res_GetInteger("cheat.godModes");
	}

	if (res_IsInteger("cheat.timeDilationPct")
		&& !options.timeDilationPct.set)
	{
		options.timeDilationPct.value = res_GetInteger("cheat.timeDilationPct");
	}
	getBoolConfigValue(options.bubbleWarp, "cheat.bubbleWarp");
	getBoolConfigValue(options.unlockShips, "cheat.unlockShips");
	getBoolConfigValue(options.headStart, "cheat.headStart");
	//getBoolConfigValue (options.unlockUpgrades, "cheat.unlockUpgrades");
	getBoolConfigValue(options.infiniteRU, "cheat.infiniteRU");
	getBoolConfigValue(options.skipIntro, "mm.skipIntro");
	getBoolConfigValue(options.mainMenuMusic, "mm.mainMenuMusic");
	getBoolConfigValue(options.nebulae, "mm.nebulae");
	getBoolConfigValue(options.orbitingPlanets, "mm.orbitingPlanets");
	getBoolConfigValue(options.texturedPlanets, "mm.texturedPlanets");

	if (res_IsInteger("mm.dateFormat") && !options.optDateFormat.set)
	{
		options.optDateFormat.value = res_GetInteger("mm.dateFormat");
	}

	getBoolConfigValue(options.infiniteFuel, "cheat.infiniteFuel");
	getBoolConfigValue(options.partialPickup, "mm.partialPickup");
	getBoolConfigValue(options.submenu, "mm.submenu");
	getBoolConfigValue(options.infiniteCredits, "cheat.infiniteCredits");
	getBoolConfigValue(options.customBorder, "mm.customBorder");
	if (res_IsInteger("mm.seedType") && !options.seedType.set)
	{
		options.seedType.value = static_cast<SeedType>(res_GetInteger("mm.seedType"));
	}
	if (res_IsInteger("mm.customSeed") && !options.customSeed.set)
	{
		options.customSeed.value = res_GetInteger("mm.customSeed");
		if (!SANE_SEED(options.customSeed.value))
		{
			options.customSeed.value = PrimeA;
		}
	}
	getBoolConfigValue(options.shipSeed, "mm.shipSeed");
	if (res_IsInteger("mm.sphereColors") && !options.sphereColors.set)
	{
		options.sphereColors.value = res_GetInteger("mm.sphereColors");
	}
	if (res_IsInteger("mm.spaceMusic") && !options.spaceMusic.set)
	{
		options.spaceMusic.value = res_GetInteger("mm.spaceMusic");
	}
	getBoolConfigValue(options.volasMusic, "mm.volasMusic");
	getBoolConfigValue(options.wholeFuel, "mm.wholeFuel");

#ifdef DIRECTIONAL_JOY
	getBoolConfigValue(options.directionalJoystick,
					   "mm.directionalJoystick"); // For Android
#endif

	getBoolConfigValueXlat(options.landerHold, "mm.landerHold", uqm::EmulationMode::Console3DO, uqm::EmulationMode::PC);
	getBoolConfigValueXlat(options.scrTrans, "mm.scrTransition", uqm::EmulationMode::Console3DO, uqm::EmulationMode::PC);
	if (res_IsInteger("mm.difficulty") && !options.optDifficulty.set)
	{
		options.optDifficulty.value = res_GetInteger("mm.difficulty");
		options.optDiffChooser.value = options.optDifficulty.value;
		if (options.optDifficulty.value > 2)
		{
			options.optDifficulty.value = 0;
		}
	}
	if (res_IsInteger("mm.fuelRange") && !options.optFuelRange.set)
	{
		options.optFuelRange.value = res_GetInteger("mm.fuelRange");
	}
	getBoolConfigValue(options.extended, "mm.extended");
	if (res_IsInteger("mm.nomad") && !options.nomad.set)
	{
		options.nomad.value = res_GetInteger("mm.nomad");
		if (options.nomad.value > 2)
		{
			options.nomad.value = 0;
		}
	}
	getBoolConfigValue(options.gameOver, "mm.gameOver");
	getBoolConfigValue(options.shipDirectionIP, "mm.shipDirectionIP");
	getBoolConfigValue(options.hazardColors, "mm.hazardColors");
	getBoolConfigValue(options.orzCompFont, "mm.orzCompFont");

	if (res_IsInteger("mm.controllerType")
		&& !options.optControllerType.set)
	{
		options.optControllerType.value =
			res_GetInteger("mm.controllerType");
	}

	getBoolConfigValue(options.smartAutoPilot, "mm.smartAutoPilot");
	getBoolConfigValueXlat(options.tintPlanSphere, "mm.tintPlanSphere", uqm::EmulationMode::Console3DO, uqm::EmulationMode::PC);
	getBoolConfigValueXlat(options.planetStyle, "mm.planetStyle", uqm::EmulationMode::Console3DO, uqm::EmulationMode::PC);

	if (res_IsInteger("mm.starBackground")
		&& !options.starBackground.set)
	{
		options.starBackground.value =
			res_GetInteger("mm.starBackground");
	}

	getBoolConfigValueXlat(options.scanStyle, "mm.scanStyle", uqm::EmulationMode::Console3DO, uqm::EmulationMode::PC);

	getBoolConfigValue(options.nonStopOscill, "mm.nonStopOscill");
	getBoolConfigValueXlat(options.scopeStyle, "mm.scopeStyle", uqm::EmulationMode::Console3DO, uqm::EmulationMode::PC);

	getBoolConfigValue(options.hyperStars, "mm.hyperStars");

	getBoolConfigValueXlat(options.landerStyle, "mm.landerStyle", uqm::EmulationMode::Console3DO, uqm::EmulationMode::PC);

	getBoolConfigValue(options.planetTexture, "mm.planetTexture");

	getBoolConfigValueXlat(options.flagshipColor, "mm.flagshipColor", uqm::EmulationMode::Console3DO, uqm::EmulationMode::PC);

	getBoolConfigValue(options.noHQEncounters, "cheat.noHQEncounters");

	getBoolConfigValue(options.deCleansing, "cheat.deCleansing");

	getBoolConfigValue(options.meleeObstacles, "cheat.meleeObstacles");

	getBoolConfigValue(options.showVisitedStars, "mm.showVisitedStars");

	getBoolConfigValue(options.unscaledStarSystem,
					   "mm.unscaledStarSystem");

	if (res_IsInteger("mm.sphereType") && !options.sphereType.set)
	{
		options.sphereType.value = res_GetInteger("mm.sphereType");
	}

	if (res_IsInteger("mm.nebulaevol") && !options.nebulaevol.set)
	{
		options.nebulaevol.value = res_GetInteger("mm.nebulaevol");
		if (options.nebulaevol.value > 50)
		{
			options.nebulaevol.value = 11;
		}
	}

	getBoolConfigValue(options.slaughterMode, "mm.slaughterMode");
	getBoolConfigValue(options.advancedAutoPilot,
					   "mm.advancedAutoPilot");
	getBoolConfigValue(options.meleeToolTips, "mm.meleeToolTips");

	if (res_IsInteger("mm.musicResume") && !options.musicResume.set)
	{
		options.musicResume.value = res_GetInteger("mm.musicResume");
	}

	if (res_IsInteger("mm.windowType") && !options.windowEmulationMode.set)
	{
		options.windowEmulationMode.value = res_GetInteger("mm.windowType");
	}

	getBoolConfigValue(options.scatterElements, "mm.scatterElements");

	getBoolConfigValue(options.showUpgrades, "mm.showUpgrades");

	getBoolConfigValue(options.fleetPointSys, "mm.fleetPointSys");

	getBoolConfigValue(options.shipStore, "mm.shipStore");

	getBoolConfigValue(options.captainNames, "mm.captainNames");

	getBoolConfigValue(options.dosMenus, "mm.dosMenus");

	memset(&optDeviceArray, 0, sizeof(optDeviceArray));

	memset(&optUpgradeArray, 0, sizeof(optUpgradeArray));

	if (res_IsInteger("config.player1control"))
	{
		PlayerControlTemplates[0] = (ControlTemplate)res_GetInteger("config.player1control");
		/* This is an unsigned, so no < 0 check is necessary */
		if (PlayerControlTemplates[0] >= ControlTemplate::NUM)
		{
			uqm::log::error("Illegal control template '{}' ({}) for Player One.", static_cast<int>(PlayerControlTemplates[0]), toString(PlayerControlTemplates[0]));
			PlayerControlTemplates[0] = ControlTemplate::KB_1;
		}
	}

	if (res_IsInteger("config.player2control"))
	{
		/* This is an unsigned, so no < 0 check is necessary */
		PlayerControlTemplates[1] = (ControlTemplate)res_GetInteger("config.player2control");
		if (PlayerControlTemplates[1] >= ControlTemplate::NUM)
		{
			uqm::log::error("Illegal control template '{}' ({}) for Player Two.", static_cast<int>(PlayerControlTemplates[1]), toString(PlayerControlTemplates[1]));
			PlayerControlTemplates[1] = ControlTemplate::JOY_1;
		}
	}
}

} // namespace uqm