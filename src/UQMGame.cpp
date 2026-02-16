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
// For BATTLE_FRAME_RATE
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


namespace uqm
{

UQMGame::UQMGame()
{
}

int UQMGame::setup(uqstl::span<const char* const> args)
{


	const OptionsStruct defaults {};


	// NOTE: we cannot use the logging facility yet because we may have to
	//   log to a file, and we'll only get the log file name after parsing
	//   the m_options.
	const int optionsResult = parseOptions(args, m_options);

	//log_init(15);

	// For debugging!!
	if (m_options.logFile.empty())
	{
		m_options.logFile = "uqm.log";
	}

	if (!m_options.logFile.empty())
	{
		m_logger.init(m_options.logFile);
		//
		//		int i;
		//		if (!freopen(m_options.logFile.c_str(), "w", stderr))
		//		{
		//			fmt::print("Error {} calling freopen() on stderr\n", errno);
		//			return EXIT_FAILURE;
		//		}
		//#ifdef UNBUFFERED_LOGFILE
		//		setbuf(stderr, nullptr);
		//#endif
		for (size_t i = 0; i < args.size(); ++i)
		{
			uqm::log::info("argv[{}] = \"{}\"", i, args[i]);
		}
	}

	if (m_options.runMode == RunMode::Version)
	{
		uqm::log::info("{}.{}.{} {}\n", UQM_MAJOR_VERSION, UQM_MINOR_VERSION,
					   UQM_PATCH_VERSION,
					   (resolutionFactor ? "HD " UQM_EXTRA_VERSION : UQM_EXTRA_VERSION));
		//log_showBox(false, false);
		return EXIT_SUCCESS;
	}

	uqm::log::info("The Ur-Quan Masters v{}.{}.{} {} (compiled {} {})\n"
				   "This software comes with ABSOLUTELY NO WARRANTY;\n"
				   "for details see the included 'COPYING' file.\n",
				   UQM_MAJOR_VERSION, UQM_MINOR_VERSION,
				   UQM_PATCH_VERSION,
				   (resolutionFactor ? "HD " UQM_EXTRA_VERSION : UQM_EXTRA_VERSION),
				   __DATE__, __TIME__);
#ifdef NETPLAY
	uqm::log::info("Netplay protocol version {}.{}. Netplay opponent "
				   "must have UQM {}.{}.{} or later.\n",
				   NETPLAY_PROTOCOL_VERSION_MAJOR, NETPLAY_PROTOCOL_VERSION_MINOR,
				   NETPLAY_MIN_UQM_VERSION_MAJOR, NETPLAY_MIN_UQM_VERSION_MINOR,
				   NETPLAY_MIN_UQM_VERSION_PATCH);
#endif

	// Compiler info to help with future debugging.
#ifdef _MSC_VER
	fmt::print("MSC_VER: {}\n", _MSC_VER);
	fmt::print("MSC_FULL_VER: {}\n", _MSC_FULL_VER);
	fmt::print("MSC_BUILD: {}\n\n", _MSC_BUILD);
	uqm::log::info("MSC_VER: {}\n", _MSC_VER);
	uqm::log::info("MSC_FULL_VER: {}\n", _MSC_FULL_VER);
	uqm::log::info("MSC_BUILD: {}\n", _MSC_BUILD);
#endif // _MSC_VER

#ifdef __GNUC__
	fmt::print("GCC_VERSION: {}.{}.{}\n\n", __GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__);
	uqm::log::info("GCC_VERSION: {}.{}.{}\n", __GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__);
#endif // __GNUC__

#ifdef __clang__
	fmt::print("CLANG_VERSION: {}.{}.{}\n\n", __clang_major__, __clang_minor__, __clang_patchlevel__);
	uqm::log::info("CLANG_VERSION: {}.{}.{}\n", __clang_major__, __clang_minor__, __clang_patchlevel__);
#endif // __clang__

#ifdef __MINGW32__
	fmt::print("MINGW32_VERSION: {}.{}\n\n", __MINGW32_MAJOR_VERSION, __MINGW32_MINOR_VERSION);
	uqm::log::info("MINGW32_VERSION: {}.{}\n", __MINGW32_MAJOR_VERSION, __MINGW32_MINOR_VERSION);
#endif // __MINGW32__

#ifdef __MINGW64__
	fmt::print("MINGW64_VERSION: {}.{}\n\n", __MINGW32_MAJOR_VERSION, __MINGW32_MINOR_VERSION);
	uqm::log::info("MINGW64_VERSION: {}.{}\n", __MINGW32_MAJOR_VERSION, __MINGW32_MINOR_VERSION);
#endif // __MINGW64__

	fmt::print("Build Time: {} {}\n\n", __DATE__, __TIME__);

	//if (error::haveError())
	//{ // Have some saved error to log
	//	uqm::log::error( "{}", error::getError());
	//	error::clear();
	//}

	if (m_options.runMode == RunMode::Usage)
	{
		printUsage(stdout, defaults);
		m_logger.showLogOnExit(true, false);
		return EXIT_SUCCESS;
	}

	if (optionsResult != EXIT_SUCCESS)
	{ // Options parsing failed. Oh, well.
		uqm::log::critical("Run with -h to see the allowed arguments.");
		return optionsResult;
	}

	TFB_PreInit();
	mem_init();
	InitThreadSystem();
	//log_initThreads();
	initIO();
	prepareConfigDir(m_options.configDir.c_str());

	PlayerControls[0] = ControlTemplate::KB_1;
	PlayerControls[1] = ControlTemplate::JOY_1;

	// Fill in the options struct based on uqm.cfg
	if (!m_options.safeMode.value)
	{
		LoadResourceIndex(configDir, "uqm.cfg", "config.");
		LoadResourceIndex(configDir, "cheats.cfg", "cheat.");
		LoadResourceIndex(configDir, "megamod.cfg", "mm.");
		getUserConfigOptions(m_options);
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
	snddriver = m_options.soundDriver.value;
	soundflags = m_options.soundQuality.value;

	// Fill in global variables:
	opt3doMusic = (OPT_ENABLABLE)m_options.use3doMusic.value;
	optRemixMusic = (OPT_ENABLABLE)m_options.useRemixMusic.value;
	optSpeech = (OPT_ENABLABLE)m_options.useSpeech.value;
	optWhichCoarseScan = m_options.whichCoarseScan.value;
	optWhichMenu = m_options.whichMenu.value;
	optWhichFonts = m_options.whichFonts.value;
	optWhichIntro = m_options.whichIntro.value;
	optWhichShield = m_options.whichShield.value;
	optSmoothScroll = m_options.smoothScroll.value;
	optMeleeScale = m_options.meleeScale.value;
	optSubtitles = (OPT_ENABLABLE)m_options.subtitles.value;
	optStereoSFX = (OPT_ENABLABLE)m_options.stereoSFX.value;
	musicVolumeScale = m_options.musicVolumeScale.value;
	sfxVolumeScale = m_options.sfxVolumeScale.value;
	speechVolumeScale = m_options.speechVolumeScale.value;
	optAddons = m_options.addons;

	optGodModes = m_options.optGodModes.value;
	timeDilationScale = m_options.timeDilationScale.value;
	optBubbleWarp = (OPT_ENABLABLE)m_options.bubbleWarp.value;
	optUnlockShips = (OPT_ENABLABLE)m_options.unlockShips.value;
	optHeadStart = (OPT_ENABLABLE)m_options.headStart.value;
	//optUnlockUpgrades = m_options.unlockUpgrades.value;
	optInfiniteRU = (OPT_ENABLABLE)m_options.infiniteRU.value;
	optSkipIntro = (OPT_ENABLABLE)m_options.skipIntro.value;
	optMainMenuMusic = (OPT_ENABLABLE)m_options.mainMenuMusic.value;
	optNebulae = (OPT_ENABLABLE)m_options.nebulae.value;
	optOrbitingPlanets = (OPT_ENABLABLE)m_options.orbitingPlanets.value;
	optTexturedPlanets = (OPT_ENABLABLE)m_options.texturedPlanets.value;
	optCheatMode = (OPT_ENABLABLE)m_options.cheatMode.value;
	optDateFormat = m_options.optDateFormat.value;
	optInfiniteFuel = (OPT_ENABLABLE)m_options.infiniteFuel.value;
	optPartialPickup = (OPT_ENABLABLE)m_options.partialPickup.value;
	optSubmenu = (OPT_ENABLABLE)m_options.submenu.value;
	optInfiniteCredits = (OPT_ENABLABLE)m_options.infiniteCredits.value;
	optCustomBorder = (OPT_ENABLABLE)m_options.customBorder.value;
	g_seedType = m_options.seedType.value;
	optCustomSeed = m_options.customSeed.value;
	optShipSeed = (OPT_ENABLABLE)m_options.shipSeed.value;
	optSphereColors = m_options.sphereColors.value;
	optRequiresReload = false;
	optRequiresRestart = false;
	optSpaceMusic = m_options.spaceMusic.value;
	optVolasMusic = (OPT_ENABLABLE)m_options.volasMusic.value;
	optWholeFuel = (OPT_ENABLABLE)m_options.wholeFuel.value;
	optDirectionalJoystick = (OPT_ENABLABLE)m_options.directionalJoystick.value;
	optLanderHold = m_options.landerHold.value;
	optScrTrans = m_options.scrTrans.value;
	optDifficulty = m_options.optDifficulty.value;
	optDiffChooser = m_options.optDiffChooser.value;
	optFuelRange = m_options.optFuelRange.value;
	optExtended = (OPT_ENABLABLE)m_options.extended.value;
	optNomad = m_options.nomad.value;
	optGameOver = (OPT_ENABLABLE)m_options.gameOver.value;
	optShipDirectionIP = (OPT_ENABLABLE)m_options.shipDirectionIP.value;
	optHazardColors = (OPT_ENABLABLE)m_options.hazardColors.value;
	optOrzCompFont = (OPT_ENABLABLE)m_options.orzCompFont.value;
	optControllerType = m_options.optControllerType.value;
	optSmartAutoPilot = (OPT_ENABLABLE)m_options.smartAutoPilot.value;
	optTintPlanSphere = m_options.tintPlanSphere.value;
	optPlanetStyle = m_options.planetStyle.value;
	optStarBackground = m_options.starBackground.value;
	optScanStyle = m_options.scanStyle.value;
	optNonStopOscill = (OPT_ENABLABLE)m_options.nonStopOscill.value;
	optScopeStyle = m_options.scopeStyle.value;
	optHyperStars = (OPT_ENABLABLE)m_options.hyperStars.value;
	optSuperPC = m_options.landerStyle.value;
	optPlanetTexture = (OPT_ENABLABLE)m_options.planetTexture.value;
	optFlagshipColor = m_options.flagshipColor.value;
	optNoHQEncounters = (OPT_ENABLABLE)m_options.noHQEncounters.value;
	optDeCleansing = (OPT_ENABLABLE)m_options.deCleansing.value;
	optMeleeObstacles = (OPT_ENABLABLE)m_options.meleeObstacles.value;
	optShowVisitedStars = (OPT_ENABLABLE)m_options.showVisitedStars.value;
	optUnscaledStarSystem = (OPT_ENABLABLE)m_options.unscaledStarSystem.value;
	optScanSphere = m_options.sphereType.value;
	optNebulaeVolume = m_options.nebulaevol.value;
	optSlaughterMode = (OPT_ENABLABLE)m_options.slaughterMode.value;
	optAdvancedAutoPilot = (OPT_ENABLABLE)m_options.advancedAutoPilot.value;
	optMeleeToolTips = (OPT_ENABLABLE)m_options.meleeToolTips.value;
	optMusicResume = m_options.musicResume.value;
	optScatterElements = (OPT_ENABLABLE)m_options.scatterElements.value;
	optShowUpgrades = (OPT_ENABLABLE)m_options.showUpgrades.value;
	optFleetPointSys = (OPT_ENABLABLE)m_options.fleetPointSys.value;
	optShipStore = (OPT_ENABLABLE)m_options.shipStore.value;
	optCaptainNames = (OPT_ENABLABLE)m_options.captainNames.value;
	optDosMenus = (OPT_ENABLABLE)m_options.dosMenus.value;

#pragma clang optimize off
	prepareContentDir(c_str(m_options.contentDir), c_str(m_options.addonDir), c_str(args.front()));

	resolutionFactor = isAddonAvailable(HD_MODE) ?
						   (unsigned int)m_options.resolutionFactor.value :
						   0;
	m_options.resolutionFactor.value = resolutionFactor;
	m_options.resolutionFactor.set = true;

	loresBlowupScale = (unsigned int)m_options.loresBlowupScale.value;
	optKeepAspectRatio = (OPT_ENABLABLE)m_options.keepAspectRatio.value;

	optWindowType = OPTVAL_UQM_WINDOW;
	const char* windowMode = WINDOW_MODE(resolutionFactor, m_options.windowType.value);
	if (m_options.windowType.value < OPTVAL_UQM_WINDOW && isAddonAvailable(windowMode))
	{
		optWindowType = m_options.windowType.value;
	}
	m_options.windowType.value = optWindowType;
	m_options.windowType.set = true;
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
			SavedWidth = inBounds(m_options.resolution.value.width, 320, 1920);
			SavedHeight = inBounds(m_options.resolution.value.height, 200, 1440);
		}

		if (optKeepAspectRatio)
		{
			float threshold = 0.75f;
			float ratio = (float)SavedHeight / (float)SavedWidth;

			if (ratio > threshold) // screen is narrower than 4:3
			{
				m_options.resolution.value.width = SavedHeight / threshold;
			}
			else if (ratio < threshold) // screen is wider than 4:3
			{
				m_options.resolution.value.height = SavedWidth * threshold;
			}
		}
		else
		{
			m_options.resolution.value.width = SavedWidth;
			m_options.resolution.value.height = SavedHeight;
		}
	}


	prepareMeleeDir();
	prepareSaveDir();
	prepareScrShotDir();
	prepareShadowAddons(m_options.addons);
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
	const int gfxDriver = m_options.opengl.value ?
							  TFB_GFXDRIVER_SDL_OPENGL :
							  TFB_GFXDRIVER_SDL_PURE;
#else
	const int gfxDriver = TFB_GFXDRIVER_SDL_PURE;
#endif
	int gfxFlags = m_options.scaler.value;
	if (m_options.fullscreen.value)
	{
		if (m_options.fullscreen.value > 1)
		{
			gfxFlags |= TFB_GFXFLAGS_FULLSCREEN;
		}
		else
		{
			gfxFlags |= TFB_GFXFLAGS_EX_FULLSCREEN;
		}
	}
	if (m_options.scanlines.value)
	{
		gfxFlags |= TFB_GFXFLAGS_SCANLINES;
	}
	if (m_options.showFps.value)
	{
		gfxFlags |= TFB_GFXFLAGS_SHOWFPS;
	}
	TFB_InitGraphics(gfxDriver, gfxFlags, m_options.graphicsBackend.c_str(),
					 m_options.resolution.value.width, m_options.resolution.value.height,
					 &resolutionFactor, &optWindowType);
	if (m_options.gamma.set && setGammaCorrection(m_options.gamma.value))
	{
		optGamma = m_options.gamma.value;
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
	assert(sizeof(int[ControlTemplate::NUM * NUM_KEYS]) == sizeof(int[static_cast<int>(ControlTemplate::NUM)][NUM_KEYS]));
	TFB_SetInputVectors((int*)ImmediateInputState.menu, NUM_MENU_KEYS,
						(int*)ImmediateInputState.key, NUM_KEYS,
						static_cast<int>(ControlTemplate::NUM));
	TFB_InitInput(TFB_INPUTDRIVER_SDL, 0);

	return EXIT_SUCCESS;
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
			HibernateThread(ONE_SECOND / 4);
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