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

#include "core/log/log.h"
#include "options/options.h"
#include "core/log/log.h"
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
// For BattleFrameRateTicks
#include "libs/file.h"
#include "types.h"
#include "port.h"
#include "libs/memlib.h"
#include "libs/platform.h"
#include "core/log/log.h"
#include "options.h"
#include "uqmversion.h"
#include "uqm/comm.h"
#ifdef NETPLAY
#include "libs/callback/callback.h"
#include "libs/callback/alarm.h"
#include "libs/net.h"
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


namespace uqm
{

UQMGame* UQMGame::s_instance {nullptr};

UQMGame::UQMGame()
{
	assert(s_instance == nullptr);
	s_instance = this;
}

UQMGame::~UQMGame()
{
	assert(s_instance == this);
	s_instance = nullptr;
}

UQMGame& UQMGame::getInstance()
{
	assert(s_instance != nullptr);
	return *s_instance;
}

uqstl::pair<int, bool> UQMGame::setup(uqstl::span<uqgsl::zstring> args)
{

	// NOTE: we cannot use the logging facility yet because we may have to
	//   log to a file, and we'll only get the log file name after parsing
	//   the options.
	const auto [parseResult, needExit] = m_options.parseArgs(args);
	if (parseResult != 0 || needExit)
	{
		return {parseResult, needExit};
	}

	//log_init(15);

	const auto& options {m_options.get()};

	// For debugging!!
	if (options.logFile.empty())
	{
		m_options.edit().logFile = "uqm.log";
	}

	m_logger.init(options.logFile);

	for (size_t i = 0; i < args.size(); ++i)
	{
		uqm::log::debug("argv[{}] = \"{}\"", i, args[i]);
	}

	if (options.runMode == RunMode::Version)
	{
		uqm::log::info("{}.{}.{} {}\n", UQM_MAJOR_VERSION, UQM_MINOR_VERSION,
					   UQM_PATCH_VERSION,
					   (resolutionFactor ? "HD " UQM_EXTRA_VERSION : UQM_EXTRA_VERSION));
		//log_showBox(false, false);
		return {EXIT_SUCCESS, true};
	}

	uqm::log::info("!! The Ur-Quan Masters v{}.{}.{} {} (compiled {} {})", UQM_MAJOR_VERSION, UQM_MINOR_VERSION, UQM_PATCH_VERSION, (resolutionFactor ? "HD " UQM_EXTRA_VERSION : UQM_EXTRA_VERSION), __DATE__, __TIME__);
	uqm::log::info("!! This software comes with ABSOLUTELY NO WARRANTY;");
	uqm::log::info("!! for details see the included 'COPYING' file.");

#ifdef NETPLAY
	uqm::log::info("Netplay protocol version {}.{}. Netplay opponent "
				   "must have UQM {}.{}.{} or later.",
				   NETPLAY_PROTOCOL_VERSION_MAJOR, NETPLAY_PROTOCOL_VERSION_MINOR,
				   NETPLAY_MIN_UQM_VERSION_MAJOR, NETPLAY_MIN_UQM_VERSION_MINOR,
				   NETPLAY_MIN_UQM_VERSION_PATCH);
#endif

	// Compiler info to help with future debugging.
#ifdef _MSC_VER
	uqm::log::info("MSC_VER: {}", _MSC_VER);
	uqm::log::info("MSC_FULL_VER: {}", _MSC_FULL_VER);
	uqm::log::info("MSC_BUILD: {}", _MSC_BUILD);
#endif // _MSC_VER

#ifdef __GNUC__
	uqm::log::info("GCC_VERSION: {}.{}.{}", __GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__);
#endif // __GNUC__

#ifdef __clang__
	uqm::log::info("CLANG_VERSION: {}.{}.{}", __clang_major__, __clang_minor__, __clang_patchlevel__);
#endif // __clang__

#ifdef __MINGW32__
	uqm::log::info("MINGW32_VERSION: {}.{}", __MINGW32_MAJOR_VERSION, __MINGW32_MINOR_VERSION);
#endif // __MINGW32__

#ifdef __MINGW64__
	uqm::log::info("MINGW64_VERSION: {}.{}", __MINGW32_MAJOR_VERSION, __MINGW32_MINOR_VERSION);
#endif // __MINGW64__

	/*if (options.runMode == RunMode::Usage)
	{
		const OptionsStruct defaults {};
		printUsage(stdout, defaults);
		m_logger.showLogOnExit(true, false);
		return EXIT_SUCCESS;
	}*/

	//if (optionsResult != EXIT_SUCCESS)
	//{ // Options parsing failed. Oh, well.
	//	uqm::log::critical("Run with -h to see the allowed arguments.");
	//	return optionsResult;
	//}

	TFB_PreInit();
	mem_init();
	InitThreadSystem();
	//log_initThreads();
	initIO();
	prepareConfigDir(options.configDir.c_str());

	PlayerControlTemplates[0] = ControlTemplate::KB_1;
	PlayerControlTemplates[1] = ControlTemplate::JOY_1;

	// Fill in the options struct based on uqm.cfg
	if (!options.safeMode.value)
	{
		LoadResourceIndex(configDir, "uqm.cfg", "config.");
		LoadResourceIndex(configDir, "cheats.cfg", "cheat.");
		LoadResourceIndex(configDir, "megamod.cfg", "mm.");
		getUserConfigOptions(m_options.edit());
	}

	{ /* remove old control template names */
		int i;

		for (i = 0; i < 6; ++i)
		{
			char cfgkey[64] {};

			fmt::format_to_sz_n(cfgkey, sizeof(cfgkey), "config.keys.{}.name", i + 1);
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
	// clear existing quality flag before applying the option value.
	soundflags &= ~AudioQualityFlagMask;
	soundflags |= toAudioFlags(*options.soundQuality);

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
	m_options.edit().resolutionFactor.value = resolutionFactor;
	m_options.edit().resolutionFactor.set = true;

	loresBlowupScale = (unsigned int)options.loresBlowupScale.value;
	optKeepAspectRatio = (OPT_ENABLABLE)options.keepAspectRatio.value;

	optWindowType = OPTVAL_UQM_WINDOW;
	const char* windowMode = WINDOW_MODE(resolutionFactor, options.windowEmulationMode.value);
	if (options.windowEmulationMode.value < OPTVAL_UQM_WINDOW && isAddonAvailable(windowMode))
	{
		optWindowType = options.windowEmulationMode.value;
	}
	m_options.edit().windowEmulationMode.value = optWindowType;
	m_options.edit().windowEmulationMode.set = true;
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
			SavedWidth = inBounds(options.resolution.value.x, 320, 1920);
			SavedHeight = inBounds(options.resolution.value.y, 200, 1440);
		}

		if (optKeepAspectRatio)
		{
			float threshold = 0.75f;
			float ratio = (float)SavedHeight / (float)SavedWidth;

			if (ratio > threshold) // screen is narrower than 4:3
			{
				m_options.edit().resolution.value.y = SavedHeight / threshold;
			}
			else if (ratio < threshold) // screen is wider than 4:3
			{
				m_options.edit().resolution.value.x = SavedWidth * threshold;
			}
		}
		else
		{
			m_options.edit().resolution.value.x = SavedWidth;
			m_options.edit().resolution.value.y = SavedHeight;
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
	const uqm::GfxDriver gfxDriver = options.opengl.value ?
										 uqm::GfxDriver::SDL_OpenGL :
										 uqm::GfxDriver::SDL_Pure;
#else
	const uqm::GfxDriver gfxDriver = uqm::GfxDriver::SDL_Pure;
#endif
	uqm::GfxFlags gfxFlags = toGfxFlags(options.scaler);
	switch (options.windowMode)
	{
		case WindowMode::Windowed:
			break;
		case WindowMode::WindowedFullscreen:
			gfxFlags |= uqm::GfxFlags::Fullscreen;
			break;
		case WindowMode::Fullscreen:
			gfxFlags |= uqm::GfxFlags::ExclusiveFullscreen;
			break;
	}

	if (options.scanlines.value)
	{
		gfxFlags |= uqm::GfxFlags::Scanlines;
	}
	if (options.showFps.value)
	{
		gfxFlags |= uqm::GfxFlags::ShowFPS;
	}
	TFB_InitGraphics(gfxDriver, gfxFlags, options.graphicsBackend.c_str(),
					 options.resolution.value.x, options.resolution.value.y,
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
	assert(sizeof(int[static_cast<int>(ControlTemplate::NUM) * NUM_KEYS]) == sizeof(int[static_cast<int>(ControlTemplate::NUM)][NUM_KEYS]));
	
	TFB_SetInputVectors((int*)ImmediateInputState.menu, NUM_MENU_KEYS,
						(int*)ImmediateInputState.key, NUM_KEYS,
						static_cast<int>(ControlTemplate::NUM));
	TFB_InitInput(TFB_INPUTDRIVER_SDL, 0);

	return {EXIT_SUCCESS, false};
}

int UQMGame::run()
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
			HibernateThread(getTicksForFramerate(4));
		}

		TFB_ProcessEvents();
		ProcessUtilityKeys();
		ProcessThreadLifecycles();
		TFB_FlushGraphics();
	}

	return EXIT_SUCCESS;
}

void UQMGame::teardown()
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

} // namespace uqm