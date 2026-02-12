//Copyright Paul Reiche, Fred Ford. 1992-2002

/*
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#include "UQMGame.h"
#include "options/options.h"
#include "libs/log/uqmlog.h"
#include "core/string/StringUtils.h"
#include "configuration/Configuration.h"

//////////////////////////////////////////////////
// legacy includes below


#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif

#ifdef HAVE_GETOPT_LONG
#include <getopt.h>
#else
#include "getopt/getopt.h"
#endif

#include <stdarg.h>
#include <errno.h>
#include "libs/graphics/gfx_common.h"
#include "libs/graphics/cmap.h"
#include "libs/sound/sound.h"
#include "libs/input/input_common.h"
#include "libs/inplib.h"
#include "libs/tasklib.h"
#include "libs/scriptlib.h"
#include "uqm/controls.h"
#include "uqm/battle.h"
// For BATTLE_FRAME_RATE
#include "libs/file.h"
#include "types.h"
#include "port.h"
#include "libs/memlib.h"
#include "libs/platform.h"
#include "libs/log.h"
#include "options.h"
#include "uqmversion.h"
#include "uqm/comm.h"
#ifdef NETPLAY
#include "libs/callback/callback.h"
#include "libs/callback/alarm.h"
#include "libs/net.h"
#include "uqm/supermelee/netplay/netoptions.h"
#include "uqm/supermelee/netplay/netplay.h"
#endif
#include "uqm/setup.h"
#include "uqm/starcon.h"
#include "libs/math/random.h"

bool restartGame;

#if defined(GFXMODULE_SDL)
#include <SDL.h>
// Including this is actually necessary on OSX.
#endif


// Looks up the given string value in the given list and passes
// the associated int value back. returns true if value was found.
//// The list is terminated by a nullptr 'str' value.
//static bool lookupOptionValue(const struct option_list_value* list,
//							  const char* strval, int* ret);
//
//
//static int parseOptions(int argc, char* argv[],
//						struct options_struct* options);
//static void getUserConfigOptions(struct options_struct* options);
//static void usage(FILE* out, const struct options_struct* defaultOptions);
//static int parseIntOption(const char* str, int* result,
//						  const char* optName);
//static int parseFloatOption(const char* str, float* f,
//							const char* optName);
//static void parseIntVolume(int intVol, float* vol);
//static int InvalidArgument(const char* supplied, const char* opt_name);
//static const char* choiceOptString(const struct int_option* option);
//static const char* boolOptString(const struct bool_option* option);
//static const char* boolNotOptString(const struct bool_option* option);

[[nodiscard]] int legacyinit(uqstl::span<const char* const> args, OptionsStruct& options)
{


	const OptionsStruct defaults {};


	// NOTE: we cannot use the logging facility yet because we may have to
	//   log to a file, and we'll only get the log file name after parsing
	//   the options.
	const int optionsResult = parseOptions(args, options);

	log_init(15);

	if (!options.logFile.empty())
	{
		int i;
		if (!freopen(options.logFile.c_str(), "w", stderr))
		{
			printf("Error %d calling freopen() on stderr\n", errno);
			return EXIT_FAILURE;
		}
#ifdef UNBUFFERED_LOGFILE
		setbuf(stderr, nullptr);
#endif
		for (i = 0; i < args.size(); ++i)
		{
			log_add(log_User, "argv[%d] = [%s]", i, args[i]);
		}
	}

	if (options.runMode == RunMode::Version)
	{
		printf("%d.%d.%d %s\n", UQM_MAJOR_VERSION, UQM_MINOR_VERSION,
			   UQM_PATCH_VERSION,
			   (resolutionFactor ? "HD " UQM_EXTRA_VERSION : UQM_EXTRA_VERSION));
		log_showBox(false, false);
		return EXIT_SUCCESS;
	}

	log_add(log_User, "The Ur-Quan Masters v%d.%d.%d %s (compiled %s %s)\n"
					  "This software comes with ABSOLUTELY NO WARRANTY;\n"
					  "for details see the included 'COPYING' file.\n",
			UQM_MAJOR_VERSION, UQM_MINOR_VERSION,
			UQM_PATCH_VERSION,
			(resolutionFactor ? "HD " UQM_EXTRA_VERSION : UQM_EXTRA_VERSION),
			__DATE__, __TIME__);
#ifdef NETPLAY
	log_add(log_User, "Netplay protocol version %d.%d. Netplay opponent "
					  "must have UQM %d.%d.%d or later.\n",
			NETPLAY_PROTOCOL_VERSION_MAJOR, NETPLAY_PROTOCOL_VERSION_MINOR,
			NETPLAY_MIN_UQM_VERSION_MAJOR, NETPLAY_MIN_UQM_VERSION_MINOR,
			NETPLAY_MIN_UQM_VERSION_PATCH);
#endif

	// Compiler info to help with future debugging.
#ifdef _MSC_VER
	printf("MSC_VER: %d\n", _MSC_VER);
	printf("MSC_FULL_VER: %d\n", _MSC_FULL_VER);
	printf("MSC_BUILD: %d\n\n", _MSC_BUILD);
	log_add(log_Info, "MSC_VER: %d\n", _MSC_VER);
	log_add(log_Info, "MSC_FULL_VER: %d\n", _MSC_FULL_VER);
	log_add(log_Info, "MSC_BUILD: %d\n", _MSC_BUILD);
#endif // _MSC_VER

#ifdef __GNUC__
	printf("GCC_VERSION: %d.%d.%d\n\n", __GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__);
	log_add(log_Info, "GCC_VERSION: %d.%d.%d\n", __GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__);
#endif // __GNUC__

#ifdef __clang__
	printf("CLANG_VERSION: %d.%d.%d\n\n", __clang_major__, __clang_minor__, __clang_patchlevel__);
	log_add(log_Info, "CLANG_VERSION: %d.%d.%d\n", __clang_major__, __clang_minor__, __clang_patchlevel__);
#endif // __clang__

#ifdef __MINGW32__
	printf("MINGW32_VERSION: %d.%d\n\n", __MINGW32_MAJOR_VERSION, __MINGW32_MINOR_VERSION);
	log_add(log_Info, "MINGW32_VERSION: %d.%d\n", __MINGW32_MAJOR_VERSION, __MINGW32_MINOR_VERSION);
#endif // __MINGW32__

#ifdef __MINGW64__
	printf("MINGW64_VERSION: %d.%d\n\n", __MINGW32_MAJOR_VERSION, __MINGW32_MINOR_VERSION);
	log_add(log_Info, "MINGW64_VERSION: %d.%d\n", __MINGW32_MAJOR_VERSION, __MINGW32_MINOR_VERSION);
#endif // __MINGW64__

	printf("Build Time: %s %s\n\n", __DATE__, __TIME__);

	if (error::haveError())
	{ // Have some saved error to log
		log_add(log_Error, "%s", error::getError());
		error::clear();
	}

	if (options.runMode == RunMode::Usage)
	{
		printUsage(stdout, defaults);
		log_showBox(true, false);
		return EXIT_SUCCESS;
	}

	if (optionsResult != EXIT_SUCCESS)
	{ // Options parsing failed. Oh, well.
		log_add(log_Fatal, "Run with -h to see the allowed arguments.");
		return optionsResult;
	}

	TFB_PreInit();
	mem_init();
	InitThreadSystem();
	log_initThreads();
	initIO();
	prepareConfigDir(options.configDir.c_str());

	PlayerControls[0] = CONTROL_TEMPLATE_KB_1;
	PlayerControls[1] = CONTROL_TEMPLATE_JOY_1;

	// Fill in the options struct based on uqm.cfg
	if (!options.safeMode.value)
	{
		LoadResourceIndex(configDir, "uqm.cfg", "config.");
		LoadResourceIndex(configDir, "cheats.cfg", "cheat.");
		LoadResourceIndex(configDir, "megamod.cfg", "mm.");
		getUserConfigOptions(options);
	}

	{ /* remove old control template names */
		int i;

		for (i = 0; i < 6; ++i)
		{
			char cfgkey[64];

			snprintf(cfgkey, sizeof(cfgkey), "config.keys.%d.name", i + 1);
			cfgkey[sizeof(cfgkey) - 1] = '\0';

			res_Remove(cfgkey);
		}
	}


	/* TODO: Once threading is gone, these become local variables
	   again.  In the meantime, they must be global so that
	   initAudio (in StarCon2Main) can see them.  initAudio needed
	   to be moved there because calling AssignTask in the main
	   thread doesn't work */
	snddriver = options.soundDriver.value;
	soundflags = options.soundQuality.value;

	// Fill in global variables:
	opt3doMusic = (OPT_ENABLABLE)options.use3doMusic.value;
	optRemixMusic = (OPT_ENABLABLE)options.useRemixMusic.value;
	optSpeech = (OPT_ENABLABLE)options.useSpeech.value;
	optWhichCoarseScan = options.whichCoarseScan.value;
	optWhichMenu = options.whichMenu.value;
	optWhichFonts = options.whichFonts.value;
	optWhichIntro = options.whichIntro.value;
	optWhichShield = options.whichShield.value;
	optSmoothScroll = options.smoothScroll.value;
	optMeleeScale = options.meleeScale.value;
	optSubtitles = (OPT_ENABLABLE)options.subtitles.value;
	optStereoSFX = (OPT_ENABLABLE)options.stereoSFX.value;
	musicVolumeScale = options.musicVolumeScale.value;
	sfxVolumeScale = options.sfxVolumeScale.value;
	speechVolumeScale = options.speechVolumeScale.value;
	optAddons = options.addons;

	optGodModes = options.optGodModes.value;
	timeDilationScale = options.timeDilationScale.value;
	optBubbleWarp = (OPT_ENABLABLE)options.bubbleWarp.value;
	optUnlockShips = (OPT_ENABLABLE)options.unlockShips.value;
	optHeadStart = (OPT_ENABLABLE)options.headStart.value;
	//optUnlockUpgrades = options.unlockUpgrades.value;
	optInfiniteRU = (OPT_ENABLABLE)options.infiniteRU.value;
	optSkipIntro = (OPT_ENABLABLE)options.skipIntro.value;
	optMainMenuMusic = (OPT_ENABLABLE)options.mainMenuMusic.value;
	optNebulae = (OPT_ENABLABLE)options.nebulae.value;
	optOrbitingPlanets = (OPT_ENABLABLE)options.orbitingPlanets.value;
	optTexturedPlanets = (OPT_ENABLABLE)options.texturedPlanets.value;
	optCheatMode = (OPT_ENABLABLE)options.cheatMode.value;
	optDateFormat = options.optDateFormat.value;
	optInfiniteFuel = (OPT_ENABLABLE)options.infiniteFuel.value;
	optPartialPickup = (OPT_ENABLABLE)options.partialPickup.value;
	optSubmenu = (OPT_ENABLABLE)options.submenu.value;
	optInfiniteCredits = (OPT_ENABLABLE)options.infiniteCredits.value;
	optCustomBorder = (OPT_ENABLABLE)options.customBorder.value;
	g_seedType = options.seedType.value;
	optCustomSeed = options.customSeed.value;
	optShipSeed = (OPT_ENABLABLE)options.shipSeed.value;
	optSphereColors = options.sphereColors.value;
	optRequiresReload = false;
	optRequiresRestart = false;
	optSpaceMusic = options.spaceMusic.value;
	optVolasMusic = (OPT_ENABLABLE)options.volasMusic.value;
	optWholeFuel = (OPT_ENABLABLE)options.wholeFuel.value;
	optDirectionalJoystick = (OPT_ENABLABLE)options.directionalJoystick.value;
	optLanderHold = options.landerHold.value;
	optScrTrans = options.scrTrans.value;
	optDifficulty = options.optDifficulty.value;
	optDiffChooser = options.optDiffChooser.value;
	optFuelRange = options.optFuelRange.value;
	optExtended = (OPT_ENABLABLE)options.extended.value;
	optNomad = options.nomad.value;
	optGameOver = (OPT_ENABLABLE)options.gameOver.value;
	optShipDirectionIP = (OPT_ENABLABLE)options.shipDirectionIP.value;
	optHazardColors = (OPT_ENABLABLE)options.hazardColors.value;
	optOrzCompFont = (OPT_ENABLABLE)options.orzCompFont.value;
	optControllerType = options.optControllerType.value;
	optSmartAutoPilot = (OPT_ENABLABLE)options.smartAutoPilot.value;
	optTintPlanSphere = options.tintPlanSphere.value;
	optPlanetStyle = options.planetStyle.value;
	optStarBackground = options.starBackground.value;
	optScanStyle = options.scanStyle.value;
	optNonStopOscill = (OPT_ENABLABLE)options.nonStopOscill.value;
	optScopeStyle = options.scopeStyle.value;
	optHyperStars = (OPT_ENABLABLE)options.hyperStars.value;
	optSuperPC = options.landerStyle.value;
	optPlanetTexture = (OPT_ENABLABLE)options.planetTexture.value;
	optFlagshipColor = options.flagshipColor.value;
	optNoHQEncounters = (OPT_ENABLABLE)options.noHQEncounters.value;
	optDeCleansing = (OPT_ENABLABLE)options.deCleansing.value;
	optMeleeObstacles = (OPT_ENABLABLE)options.meleeObstacles.value;
	optShowVisitedStars = (OPT_ENABLABLE)options.showVisitedStars.value;
	optUnscaledStarSystem = (OPT_ENABLABLE)options.unscaledStarSystem.value;
	optScanSphere = options.sphereType.value;
	optNebulaeVolume = options.nebulaevol.value;
	optSlaughterMode = (OPT_ENABLABLE)options.slaughterMode.value;
	optAdvancedAutoPilot = (OPT_ENABLABLE)options.advancedAutoPilot.value;
	optMeleeToolTips = (OPT_ENABLABLE)options.meleeToolTips.value;
	optMusicResume = options.musicResume.value;
	optScatterElements = (OPT_ENABLABLE)options.scatterElements.value;
	optShowUpgrades = (OPT_ENABLABLE)options.showUpgrades.value;
	optFleetPointSys = (OPT_ENABLABLE)options.fleetPointSys.value;
	optShipStore = (OPT_ENABLABLE)options.shipStore.value;
	optCaptainNames = (OPT_ENABLABLE)options.captainNames.value;
	optDosMenus = (OPT_ENABLABLE)options.dosMenus.value;

	#pragma clang optimize off
	prepareContentDir(c_str(options.contentDir), c_str(options.addonDir), c_str(args.front()));

	resolutionFactor = isAddonAvailable(HD_MODE) ?
						   (unsigned int)options.resolutionFactor.value :
						   0;
	options.resolutionFactor.value = resolutionFactor;
	options.resolutionFactor.set = true;

	loresBlowupScale = (unsigned int)options.loresBlowupScale.value;
	optKeepAspectRatio = (OPT_ENABLABLE)options.keepAspectRatio.value;

	optWindowType = OPTVAL_UQM_WINDOW;
	const char* windowMode = WINDOW_MODE(resolutionFactor, options.windowType.value);
	if (options.windowType.value < OPTVAL_UQM_WINDOW && isAddonAvailable(windowMode))
	{
		optWindowType = options.windowType.value;
	}
	options.windowType.value = optWindowType;
	options.windowType.set = true;
	#pragma clang optimize on

	{
		int w = 320;
		int h = (DOS_BOOL(240, 200));
		int scaleFactor = loresBlowupScale + 1; // stored value starts with 0

		CanvasWidth = w << resolutionFactor;
		CanvasHeight = h << resolutionFactor;

		if (loresBlowupScale < 6)
		{
			SavedWidth = loresBlowupScale ? (w * scaleFactor) : CanvasWidth;
			SavedHeight = loresBlowupScale ? (h * scaleFactor) : CanvasHeight;
		}
		else
		{
			SavedWidth = inBounds(options.resolution.value.width, 320, 1920);
			SavedHeight = inBounds(options.resolution.value.height, 200, 1440);
		}

		if (optKeepAspectRatio)
		{
			float threshold = 0.75f;
			float ratio = (float)SavedHeight / (float)SavedWidth;

			if (ratio > threshold) // screen is narrower than 4:3
			{
				options.resolution.value.width = SavedHeight / threshold;
			}
			else if (ratio < threshold) // screen is wider than 4:3
			{
				options.resolution.value.height = SavedWidth * threshold;
			}
		}
		else
		{
			options.resolution.value.width = SavedWidth;
			options.resolution.value.height = SavedHeight;
		}
	}


	prepareMeleeDir();
	prepareSaveDir();
	prepareScrShotDir();
	prepareShadowAddons(options.addons);
#if 0
	initTempDir ();
#endif

	InitTimeSystem();
	InitTaskSystem();

	luaUqm_init();

	Alarm_init();
	Callback_init();

#ifdef NETPLAY
	Network_init();
	NetManager_init();
#endif

#if SDL_MAJOR_VERSION == 1
	const int gfxDriver = options.opengl.value ?
							  TFB_GFXDRIVER_SDL_OPENGL :
							  TFB_GFXDRIVER_SDL_PURE;
#else
	const int gfxDriver = TFB_GFXDRIVER_SDL_PURE;
#endif
	int gfxFlags = options.scaler.value;
	if (options.fullscreen.value)
	{
		if (options.fullscreen.value > 1)
		{
			gfxFlags |= TFB_GFXFLAGS_FULLSCREEN;
		}
		else
		{
			gfxFlags |= TFB_GFXFLAGS_EX_FULLSCREEN;
		}
	}
	if (options.scanlines.value)
	{
		gfxFlags |= TFB_GFXFLAGS_SCANLINES;
	}
	if (options.showFps.value)
	{
		gfxFlags |= TFB_GFXFLAGS_SHOWFPS;
	}
	TFB_InitGraphics(gfxDriver, gfxFlags, options.graphicsBackend.c_str(),
					 options.resolution.value.width, options.resolution.value.height,
					 &resolutionFactor, &optWindowType);
	if (options.gamma.set && setGammaCorrection(options.gamma.value))
	{
		optGamma = options.gamma.value;
	}
	else
	{
		optGamma = 1.0f; // failed or default
	}

	InitColorMaps();
	init_communication();
	/* TODO: Once threading is gone, restore initAudio here.
	   initAudio calls AssignTask, which currently blocks on
	   ProcessThreadLifecycles... */
	// initAudio (snddriver, soundflags);
	// Make sure that the compiler treats multidim arrays the way we expect
	assert(sizeof(int[NUM_TEMPLATES * NUM_KEYS]) == sizeof(int[NUM_TEMPLATES][NUM_KEYS]));
	TFB_SetInputVectors(ImmediateInputState.menu, NUM_MENU_KEYS,
						(volatile int*)ImmediateInputState.key, NUM_TEMPLATES,
						NUM_KEYS);
	TFB_InitInput(TFB_INPUTDRIVER_SDL, 0);

	return EXIT_SUCCESS;
}

int legacyRun()
{
	StartThread(Starcon2Main, nullptr, 1024, "Starcon2Main");

	for (int i = 0; i < 2000 && !MainExited;)
	{
		if (QuitPosted)
		{ /* Try to stop the main thread, but limited number of times */
			SignalStopMainThread();
			++i;
		}
		else if (!GameActive)
		{ // Throttle down the main loop when game is inactive
			HibernateThread(ONE_SECOND / 4);
		}

		TFB_ProcessEvents();
		ProcessUtilityKeys();
		ProcessThreadLifecycles();
		TFB_FlushGraphics();
	}

	return EXIT_SUCCESS;
}

void legacyTeardown()
{

	/* Currently, we use atexit() callbacks everywhere, so we
	 *   cannot simply call unInitAudio() and the like, because other
	 *   tasks might still be using it */
	if (MainExited)
	{
		TFB_UninitInput();
		unInitAudio();
		uninit_communication();

		TFB_PurgeDanglingGraphics();
		// Purge above refers to colormaps which have to be still up
		UninitColorMaps();
		TFB_UninitGraphics();

#ifdef NETPLAY
		NetManager_uninit();
		Network_uninit();
#endif

		Callback_uninit();
		Alarm_uninit();

		luaUqm_uninit();

		CleanupTaskSystem();
		UnInitTimeSystem();
#if 0
		unInitTempDir ();
#endif
		unprepareAllDirs();
		uninitIO();
		UnInitThreadSystem();
		mem_uninit();
	}
}

//static bool lookupOptionValue(const OptionListValue& list, const char* strval, int* ret)
//{
//	if (!list)
//	{
//		return false;
//	}
//
//	// The list is terminated by a nullptr 'str' value.
//	while (list->str && strcmp(strval, list->str) != 0)
//	{
//		++list;
//	}
//	if (!list->str)
//	{
//		return false;
//	}
//
//	*ret = list->value;
//	return true;
//}


//static int parseIntOption(const char* str, int* result, const char* optName)
//{
//	char* endPtr;
//	int temp;
//
//	if (str == nullptr || str[0] == '\0')
//	{
//		saveError("Error: Invalid value for '%s'.", optName);
//		return -1;
//	}
//	temp = (int)strtol(str, &endPtr, 10);
//	if (*endPtr != '\0')
//	{
//		saveError("Error: Junk characters in argument '%s'.", optName);
//		return -1;
//	}
//
//	*result = temp;
//	return 0;
//}

//static int
//parseFloatOption(const char* str, float* f, const char* optName)
//{
//	char* endPtr;
//	float temp;
//
//	if (str[0] == '\0')
//	{
//		saveError("Error: Invalid value for '%s'.", optName);
//		return -1;
//	}
//	temp = (float)strtod(str, &endPtr);
//	if (*endPtr != '\0')
//	{
//		saveError("Error: Junk characters in argument '%s'.", optName);
//		return -1;
//	}
//
//	*f = temp;
//	return 0;
//}


///////////////////////////////////////////////////
// new stuff

UQMGame::UQMGame()
{
}

int UQMGame::setup(uqstl::span<const char* const> args)
{
	return legacyinit(args, m_options);
}

int UQMGame::run()
{
	return legacyRun();
}

void UQMGame::teardown()
{
	legacyTeardown();
}