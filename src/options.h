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

/*
 * Eventually this should include all configuration stuff, 
 * for now there's few options which indicate 3do/pc flavors.
 */

#ifndef OPTIONS_H
#define OPTIONS_H

#include "core/stl/stl.h"
#include "port.h"
#include "libs/compiler.h"
#include "libs/uio.h"
#include "uqm/setupmenu.h"

#include "options/OptionTypes.h"

#include "uqmversion.h"


extern int optWhichCoarseScan;
extern uqm::EmulationMode optWhichMenu;
extern uqm::EmulationMode optWhichFonts;
extern uqm::EmulationMode optWhichIntro;
extern uqm::EmulationMode optWhichShield;
extern uqm::EmulationMode optSmoothScroll;
extern int optMeleeScale;
extern unsigned int loresBlowupScale;
extern unsigned int resolutionFactor;
extern unsigned int audioDriver;
extern unsigned int audioQuality;

// Added options
extern bool optRequiresReload;
extern bool optRequiresRestart;
extern OPT_ENABLABLE optCheatMode;
extern int optGodModes;
extern int timeDilationScale;
extern OPT_ENABLABLE optBubbleWarp;
extern OPT_ENABLABLE optUnlockShips;
extern OPT_ENABLABLE optHeadStart;
extern OPT_ENABLABLE optUnlockUpgrades;
extern OPT_ENABLABLE optInfiniteRU;
extern uqm::DWORD oldRU;
extern OPT_ENABLABLE optSkipIntro;
extern OPT_ENABLABLE optMainMenuMusic;
extern OPT_ENABLABLE optNebulae;
extern OPT_ENABLABLE optOrbitingPlanets;
extern OPT_ENABLABLE optTexturedPlanets;
extern int optDateFormat;
extern OPT_ENABLABLE optInfiniteFuel;
extern uqm::DWORD loadFuel;
extern OPT_ENABLABLE optPartialPickup;
extern OPT_ENABLABLE optSubmenu;
extern OPT_ENABLABLE optInfiniteCredits;
extern bool optSuperMelee;
extern bool optLoadGame;
extern OPT_ENABLABLE optCustomBorder;
extern int optCustomSeed;
extern OPT_ENABLABLE optShipSeed;
extern int optSphereColors;
extern int spaceMusicBySOI;
extern int optSpaceMusic;
extern OPT_ENABLABLE optVolasMusic;
extern OPT_ENABLABLE optWholeFuel;
extern OPT_ENABLABLE optDirectionalJoystick;
extern uqm::EmulationMode optLanderHold;
extern uqm::EmulationMode optScrTrans;
extern int optDifficulty;
extern int optDiffChooser;
extern int optFuelRange;
extern OPT_ENABLABLE optExtended;
extern int optNomad;
extern OPT_ENABLABLE optGameOver;
extern OPT_ENABLABLE optShipDirectionIP;
extern OPT_ENABLABLE optHazardColors;
extern OPT_ENABLABLE optOrzCompFont;
extern int optControllerType;
extern OPT_ENABLABLE optSmartAutoPilot;
extern uqm::EmulationMode optTintPlanSphere;
extern uqm::EmulationMode optPlanetStyle;
extern int optStarBackground;
extern uqm::EmulationMode optScanStyle;
extern OPT_ENABLABLE optNonStopOscill;
extern uqm::EmulationMode optScopeStyle;
extern uqm::EmulationMode optSuperPC;
extern OPT_ENABLABLE optHyperStars;
extern OPT_ENABLABLE optPlanetTexture;
extern uqm::EmulationMode optFlagshipColor;
extern OPT_ENABLABLE optNoHQEncounters;
extern OPT_ENABLABLE optDeCleansing;
extern OPT_ENABLABLE optMeleeObstacles;
extern OPT_ENABLABLE optShowVisitedStars;
extern OPT_ENABLABLE optUnscaledStarSystem;
extern int optScanSphere;
extern int optNebulaeVolume;
extern OPT_ENABLABLE optSlaughterMode;
extern bool optMaskOfDeceit;
extern OPT_ENABLABLE optAdvancedAutoPilot;
extern OPT_ENABLABLE optMeleeToolTips;
extern int optMusicResume;
extern uqm::DWORD optWindowType;
extern bool optNoClassic;
extern OPT_ENABLABLE optScatterElements;
extern OPT_ENABLABLE optShowUpgrades;
extern OPT_ENABLABLE optFleetPointSys;
extern OPT_ENABLABLE optShipStore;
extern OPT_ENABLABLE optCaptainNames;
extern OPT_ENABLABLE optDosMenus;
extern OPT_ADD_REMOVE optDeviceArray[28];
extern OPT_ADD_REMOVE optUpgradeArray[13];

extern OPT_ENABLABLE opt3doMusic;
extern OPT_ENABLABLE optRemixMusic;
extern OPT_ENABLABLE optSpeech;
extern OPT_ENABLABLE optSubtitles;
extern OPT_ENABLABLE optStereoSFX;
extern OPT_ENABLABLE optKeepAspectRatio;
extern bool restartGame;

#define GAMMA_SCALE 1000
extern float optGamma;

extern uio_DirHandle* contentDir;
extern uio_DirHandle* configDir;
extern uio_DirHandle* saveDir;
extern uio_DirHandle* meleeDir;
extern uio_DirHandle* scrShotDir;
extern char baseContentPath[PATH_MAX];

extern uqgsl::czstring contentDirPath;
extern uqgsl::czstring addonDirPath;

extern uqstl::span<const uqstl::string> optAddons;


extern uqstl::vector<uqm::DWORD> g_addonList;

// addon names to check against
#define THREEDO_MUSIC "3domusic"
#define REMIX_MUSIC "remix"
#define VOL_RMX_MUSIC "volasaurus-remix-pack"
#define REGION_MUSIC "SpaceMusic"
#define HD_MODE "mm-hd"

#define DOS_MODE(a) ((a) ? "dos-mode-hd" : "dos-mode-sd")
#define THREEDO_MODE(a) ((a) ? "3do-mode-hd" : "3do-mode-sd")
#define WINDOW_MODE(a, b) ((b) == 0 ? DOS_MODE(a) : THREEDO_MODE(a))

#define BASE_CONTENT_NAME "mm-" UQM_MAJOR_VERSION_S "." UQM_MINOR_VERSION_S "." UQM_PATCH_VERSION_S "-content.uqm"

namespace uqm
{

/* These get edited by TEXTENTRY widgets, so they should have room to
 * hold as much as one of them allows by default. */
typedef struct _input_template
{
	char name[30];

	/* This should eventually also hold things like Joystick Port
	 * and whether or not joysticks are enabled at all, and
	 * possibly the whole configuration scheme.  If we do that, we
	 * can actually ditch much of VControl. */
} INPUT_TEMPLATE;

extern INPUT_TEMPLATE input_templates[6];

void prepareContentDir(uqgsl::czstring contentDirName, uqgsl::czstring addonDirName, uqgsl::czstring execFile);
void prepareConfigDir(const char* configDirName);
void prepareMeleeDir(void);
void prepareSaveDir(void);
void prepareScrShotDir(void);
void prepareAddons(uqstl::span<const uqstl::string> addons);
void prepareShadowAddons(uqstl::span<const uqstl::string> addons);
void unprepareAllDirs(void);

bool loadAddon(uqgsl::czstring addon);
int loadIndices(uio_DirHandle* baseDir);
[[nodiscard]] bool isAddonAvailable(uqgsl::czstring addon_name);

bool setGammaCorrection(float gamma);
} // namespace uqm

#endif