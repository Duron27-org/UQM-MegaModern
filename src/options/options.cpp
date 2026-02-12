#include "options.h"

#include "../options.h"
#include "libs/log/uqmlog.h"
#include "getopt/getopt.h"

#include "uqm/battle.h" // for BATTLE_FRAME_RATE
#ifdef NETPLAY
#include "uqm/supermelee/netplay/netoptions.h" // for NETPLAY options
#endif

static int InvalidArgument(const char* supplied, const char* opt_name)
{
	error::saveError("Invalid argument '%s' to option %s.", supplied, opt_name);
	return EXIT_FAILURE;
}

enum
{
	CSCAN_OPT = 1000,
	MENU_OPT,
	FONT_OPT,
	SHIELD_OPT,
	SCROLL_OPT,
	SOUND_OPT,
	STEREOSFX_OPT,
	ADDON_OPT,
	ADDONDIR_OPT,
	ACCEL_OPT,
	SAFEMODE_OPT,
	RENDERER_OPT,
	CHEATMODE_OPT,
	GODMODE_OPT,
	TDM_OPT,
	BWARP_OPT,
	UNLOCKSHIPS_OPT,
	HEADSTART_OPT,
	UPGRADES_OPT,
	INFINITERU_OPT,
	SKIPINTRO_OPT,
	MENUMUS_OPT,
	NEBU_OPT,
	ORBITS_OPT,
	TEXTPLAN_OPT,
	DATE_OPT,
	INFFUEL_OPT,
	PICKUP_OPT,
	SUBMENU_OPT,
	INFCRED_OPT,
	CUSTBORD_OPT,
	SEEDTYPE_OPT,
	EXSEED_OPT,
	SHIPSEED_OPT,
	SPHERECOLORS_OPT,
	SPACEMUSIC_OPT,
	WHOLEFUEL_OPT,
	DIRJOY_OPT,
	LANDHOLD_OPT,
	SCRTRANS_OPT,
	DIFFICULTY_OPT,
	FUELRANGE_OPT,
	EXTENDED_OPT,
	NOMAD_OPT,
	GAMEOVER_OPT,
	SHIPDIRIP_OPT,
	HAZCOLORS_OPT,
	ORZFONT_OPT,
	CONTYPE_OPT,
	SISFACEHS_OPT,
	COLORPLAN_OPT,
	PLANSTYLE_OPT,
	STARBACK_OPT,
	SCANSTYLE_OPT,
	OSCILLO_OPT,
	OSCSTYLE_OPT,
	HYPERSTARS_OPT,
	LANDSTYLE_OPT,
	PLANTEX_OPT,
	SISENGINE_OPT,
	NOHSENC_OPT,
	DECLEANSE_OPT,
	NOMELEEOBJ_OPT,
	SHOWSTARS_OPT,
	UNSCALEDSS_OPT,
	SCANSPH_OPT,
	SLAUGHTER_OPT,
	SISADVAP_OPT,
	MELEETIPS_OPT,
	MUSICRESUME_OPT,
	WINDTYPE_OPT,
	SCATTERELEMS_OPT,
	SHOWUPG_OPT,
	FLTPTSYS_OPT,
	SHIPSTORE_OPT,
	CAPTNAMES_OPT,
	DOSMENUS_OPT,
	MELEE_OPT,
	LOADGAME_OPT,
	NEBUVOL_OPT,
	CLAPAK_OPT,
#ifdef NETPLAY
	NETHOST1_OPT,
	NETPORT1_OPT,
	NETHOST2_OPT,
	NETPORT2_OPT,
	NETDELAY_OPT,
#endif
};

constexpr const char* optString = "+r:f:oc:b:spC:n:?hM:S:T:q:ug:l:i:vwxk";
struct option longOptions[] =
	{
		{"res",				1, NULL, 'r'				},
		{"fullscreen",		   1, NULL, 'f'			   },
		{"opengl",			   0, NULL, 'o'			   },
		{"scale",			  1, NULL, 'c'			  },
		{"meleezoom",		  1, NULL, 'b'			  },
		{"scanlines",		  0, NULL, 's'			  },
		{"fps",				0, NULL, 'p'				},
		{"configdir",		  1, NULL, 'C'			  },
		{"contentdir",		   1, NULL, 'n'			   },
		{"help",				 0, NULL, 'h'			 },
		{"musicvol",			 1, NULL, 'M'			 },
		{"sfxvol",			   1, NULL, 'S'			   },
		{"speechvol",		  1, NULL, 'T'			  },
		{"audioquality",		 1, NULL, 'q'			 },
		{"nosubtitles",		0, NULL, 'u'				},
		{"gamma",			  1, NULL, 'g'			  },
		{"logfile",			1, NULL, 'l'				},
		{"intro",			  1, NULL, 'i'			  },
		{"version",			0, NULL, 'v'				},
		{"windowed",			 0, NULL, 'w'			 },
		{"nogl",				 0, NULL, 'x'			 },
		{"keepaspectratio",	0, NULL, 'k'				},

		//  options with no short equivalent:
		{"cscan",			  1, NULL, CSCAN_OPT		},
		{"menu",				 1, NULL, MENU_OPT		  },
		{"font",				 1, NULL, FONT_OPT		  },
		{"shield",			   1, NULL, SHIELD_OPT	  },
		{"scroll",			   1, NULL, SCROLL_OPT	  },
		{"sound",			  1, NULL, SOUND_OPT		},
		{"stereosfx",		  0, NULL, STEREOSFX_OPT	},
		{"addon",			  1, NULL, ADDON_OPT		},
		{"addondir",			 1, NULL, ADDONDIR_OPT	  },
		{"accel",			  1, NULL, ACCEL_OPT		},
		{"safe",				 0, NULL, SAFEMODE_OPT	  },
		{"renderer",			 1, NULL, RENDERER_OPT	  },
		{"kohrstahp",		  0, NULL, CHEATMODE_OPT	},
		{"precursormode",	  1, NULL, GODMODE_OPT	  },
		{"timedilation",		 1, NULL, TDM_OPT		 },
		{"bubblewarp",		   0, NULL, BWARP_OPT		 },
		{"unlockships",		0, NULL, UNLOCKSHIPS_OPT },
		{"headstart",		  0, NULL, HEADSTART_OPT	},
		{"unlockupgrades",	   0, NULL, UPGRADES_OPT	},
		{"infiniteru",		   0, NULL, INFINITERU_OPT  },
		{"skipintro",		  0, NULL, SKIPINTRO_OPT	},
		{"mainmenumusic",	  0, NULL, MENUMUS_OPT	  },
		{"nebulae",			0, NULL, NEBU_OPT		 },
		{"orbitingplanets",	0, NULL, ORBITS_OPT	   },
		{"texturedplanets",	0, NULL, TEXTPLAN_OPT	 },
		{"dateformat",		   1, NULL, DATE_OPT		},
		{"infinitefuel",		 0, NULL, INFFUEL_OPT	 },
		{"partialpickup",	  0, NULL, PICKUP_OPT		 },
		{"submenu",			0, NULL, SUBMENU_OPT		},
		{"infinitecredits",	0, NULL, INFCRED_OPT		},
		{"customborder",		 0, NULL, CUSTBORD_OPT	  },
		{"seedtype",			 0, NULL, SEEDTYPE_OPT	  },
		{"customseed",		   1, NULL, EXSEED_OPT	  },
		{"shipseed",			 0, NULL, SHIPSEED_OPT	  },
		{"spherecolors",		 0, NULL, SPHERECOLORS_OPT},
		{"spacemusic",		   1, NULL, SPACEMUSIC_OPT  },
		{"wholefuel",		  0, NULL, WHOLEFUEL_OPT	},
		{"dirjoystick",		0, NULL, DIRJOY_OPT	   },
		{"landerhold",		   0, NULL, LANDHOLD_OPT	},
		{"scrtrans",			 1, NULL, SCRTRANS_OPT	  },
		{"melee",			  0, NULL, MELEE_OPT		},
		{"loadgame",			 0, NULL, LOADGAME_OPT	  },
		{"difficulty",		   1, NULL, DIFFICULTY_OPT  },
		{"fuelrange",		  1, NULL, FUELRANGE_OPT	},
		{"extended",			 0, NULL, EXTENDED_OPT	  },
		{"nomad",			  1, NULL, NOMAD_OPT		},
		{"gameover",			 0, NULL, GAMEOVER_OPT	  },
		{"shipdirectionip",	0, NULL, SHIPDIRIP_OPT	  },
		{"hazardcolors",		 0, NULL, HAZCOLORS_OPT   },
		{"orzcompfont",		0, NULL, ORZFONT_OPT		},
		{"smartautopilot",	   0, NULL, SISFACEHS_OPT	 },
		{"tintplansphere",	   1, NULL, COLORPLAN_OPT	 },
		{"planetstyle",		1, NULL, PLANSTYLE_OPT	  },
		{"starbackground",	   1, NULL, STARBACK_OPT	},
		{"scanstyle",		  1, NULL, SCANSTYLE_OPT	},
		{"nonstoposcill",	  0, NULL, OSCILLO_OPT	  },
		{"scopestyle",		   1, NULL, OSCSTYLE_OPT	},
		{"animhyperstars",	   0, NULL, HYPERSTARS_OPT  },
		{"landerview",		   1, NULL, LANDSTYLE_OPT	 },
		{"planettexture",	  1, NULL, PLANTEX_OPT	  },
		{"sisenginecolor",	   1, NULL, SISENGINE_OPT	 },
		{"nohqencounters",	   0, NULL, NOHSENC_OPT	   },
		{"decleanse",		  0, NULL, DECLEANSE_OPT	},
		{"nomeleeobstacles",	 0, NULL, NOMELEEOBJ_OPT	},
		{"showvisitstars",	   0, NULL, SHOWSTARS_OPT	 },
		{"unscaledstarsystem", 0, NULL, UNSCALEDSS_OPT  },
		{"spheretype",		   1, NULL, SCANSPH_OPT	   },
		{"nebulaevol",		   1, NULL, NEBUVOL_OPT	   },
		{"slaughtermode",	  0, NULL, SLAUGHTER_OPT	},
		{"advancedautopilot",  0, NULL, SISADVAP_OPT	   },
		{"meleetooltips",	  0, NULL, MELEETIPS_OPT	},
		{"musicresume",		1, NULL, MUSICRESUME_OPT },
		{"windowtype",		   1, NULL, WINDTYPE_OPT	},
		{"noclassic",		  0, NULL, CLAPAK_OPT		 },
		{"scatterelements",	0, NULL, SCATTERELEMS_OPT},
		{"showupgrades",		 0, NULL, SHOWUPG_OPT	 },
		{"fleetpointsys",	  0, NULL, FLTPTSYS_OPT	   },
		{"shipstore",		  0, NULL, SHIPSTORE_OPT	},
		{"captainnames",		 0, NULL, CAPTNAMES_OPT   },
		{"dosmenus",			 0, NULL, DOSMENUS_OPT	  },
#ifdef NETPLAY
		{"nethost1",			 1, NULL, NETHOST1_OPT	  },
		{"netport1",			 1, NULL, NETPORT1_OPT	  },
		{"nethost2",			 1, NULL, NETHOST2_OPT	  },
		{"netport2",			 1, NULL, NETPORT2_OPT	  },
		{"netdelay",			 1, NULL, NETDELAY_OPT	  },
#endif
		{0,					0, 0,	  0			   }
};

template <typename OptionT, typename OptionValueT = typename OptionT::value_type>
inline void setOption(OptionT& option, OptionValueT value)
{
	option = value;
}

template <typename OptionT>
bool setOption(OptionT& option, uqgsl::czstring strval, uqgsl::czstring optionName)
{
	if (const auto temp {parseOptionValue<typename OptionT::value_type>(strval, optionName)}; temp.has_value())
	{
		option = *temp;
		return true;
	}
	return false;
}

// returns true is value was found and set successfully
template <typename OptionT, typename OptionListT>
bool setListOption(OptionT& option, uqgsl::czstring strval, const OptionListT& list)
{
	if (const auto val {getOptionListValue(list, strval)}; val.has_value())
	{
		option = *val;
		return true;
	}

	return false;
}

template <typename OptionT>
inline bool setChoiceOption(OptionT& option, uqgsl::czstring strval)
{
	return setListOption(option, strval, EmulationChoiceList);
}

bool setVolumeOption(FloatOption& option, uqgsl::czstring strval, uqgsl::czstring optName)
{
	if (const auto optionIntValue {parseOptionValue<int>(strval, optName)}; optionIntValue.has_value())
	{
		option.value = normalizeValue(*optionIntValue, 100);
		option.set = true;
		return true;
	}
	return false;
}



int parseOptions(uqstl::span<const char* const> args, OptionsStruct& options)
{
	int optionIndex;
	bool badArg = false;

	opterr = 0;

	if (args.empty())
	{
		error::saveError("Error: Bad command line.");
		return EXIT_FAILURE;
	}

#ifdef __APPLE__
	// If we are launched by double-clicking an application bundle, Finder
	// sticks a "-psn_<some_number>" argument into the list, which makes
	// getopt extremely unhappy. Check for this case and wipe out the
	// entire command line if it looks like it happened.
	if ((argc >= 2) && (strncmp(argv[1], "-psn_", 5) == 0))
	{
		return EXIT_SUCCESS;
	}
#endif

	while (!badArg)
	{
		int c;
		optionIndex = -1;
		c = getopt_long(args.size(), args.data(), optString, longOptions, &optionIndex);
		if (c == -1)
		{
			break;
		}


		switch (c)
		{
			case '?':
				if (optopt != '?')
				{
					error::saveError("Invalid option or its argument \"%c\"", c);
					badArg = true;
					break;
				}
				// fall through
			case 'h':
				options.runMode = RunMode::Usage;
				return EXIT_SUCCESS;
			case 'v':
				options.runMode = RunMode::Version;
				return EXIT_SUCCESS;
			case 'r':
				{
					int width {};
					int height {};
					if (sscanf(optarg, "%dx%d", &width, &height) != 2)
					{
						error::saveError("Error: invalid argument \"%s\" specified as resolution.", optarg);
						badArg = true;
						break;
					}
					options.resolution.value.width = width;
					options.resolution.value.height = height;
					options.resolution.set = true;
					break;
				}
			case 'f':
				{
					if (const auto fsValue {parseOptionValue<int>(optarg, "Fullscreen")}; fsValue.has_value())
					{
						if (*fsValue < 0 || *fsValue > 2)
						{
							error::saveError("\nFullscreen has to be 0, 1, or 2. Not %d\n", *fsValue);
							badArg = true;
						}
						else
						{
							options.fullscreen = *fsValue;
						}
					}
					else
					{
						badArg = true;
					}
					break;
				}
			case 'w':
				options.fullscreen = 0;
				break;
			case 'o':
				options.opengl = true;
				break;
			case 'x':
				options.opengl = false;
				break;
			case 'k':
				options.keepAspectRatio = true;
				break;
			case 'c':
				if (!setListOption(options.scaler, optarg, ScalerList))
				{
					InvalidArgument(optarg, "--scale or -c");
					badArg = true;
				}
				break;
			case 'b':
				if (!setListOption(options.meleeScale, optarg, MeleeScaleList))
				{
					InvalidArgument(optarg, "--meleezoom or -b");
					badArg = true;
				}
				break;
			case 's':
				options.scanlines = true;
				break;
			case 'p':
				options.showFps = true;
				break;
			case 'n':
				options.contentDir = optarg;
				break;
			case 'M':
				if (!setVolumeOption(options.musicVolumeScale, optarg, "music volume"))
				{
					badArg = true;
				}
				break;
			case 'S':
				if (!setVolumeOption(options.sfxVolumeScale, optarg, "sfx volume"))
				{
					badArg = true;
				}
				break;
			case 'T':
				if (!setVolumeOption(options.speechVolumeScale, optarg, "speech volume"))
				{
					badArg = true;
				}
				break;
			case 'q':
				if (!setListOption(options.soundQuality, optarg, AudioQualityList))
				{
					InvalidArgument(optarg, "--audioquality or -q");
					badArg = true;
				}
				break;
			case 'u':
				options.subtitles = false;
				break;
			case 'g':
				if (!setOption(options.gamma, optarg, "gamma correction"))
				{
					badArg = true;
				}
				break;
			case 'l':
				options.logFile = optarg;
				break;
			case 'C':
				options.configDir = optarg;
				break;
			case 'i':
				if (!setOption(options.whichIntro, optarg, "introduction"))
				{
					InvalidArgument(optarg, "--intro or -i");
					badArg = true;
				}
				break;
			case CSCAN_OPT:
				{
					int temp;
					if (const auto scanVal {parseOptionValue<int>(optarg, "Coarse Scans")}; scanVal.has_value())
					{
						if (temp < 0 || temp > 2)
						{
							error::saveError("\nCoarse Scan has to be 0, 1, 2 or 3.\n");
							badArg = true;
						}
						else
						{
							options.whichCoarseScan = temp;
						}
					}
					else
					{
						badArg = true;
					}
					break;
				}
			case MENU_OPT:
				if (!parseOption(options.whichMenu, optarg, "Menu Emulation"))
				{
					InvalidArgument(optarg, "--menu");
					badArg = true;
				}
				break;
			case FONT_OPT:
				if (!parseOption(options.whichFonts, optarg, "Font Emulation"))
				{
					InvalidArgument(optarg, "--font");
					badArg = true;
				}
				break;
			case SHIELD_OPT:
				if (!parseOption(options.whichShield, optarg, "Shield Emulation"))
				{
					InvalidArgument(optarg, "--shield");
					badArg = true;
				}
				break;
			case SCROLL_OPT:
				if (!parseOption(options.smoothScroll, optarg, "Scrolling emulation"))
				{
					InvalidArgument(optarg, "--scroll");
					badArg = true;
				}
				break;
			case SOUND_OPT:
				if (!setListOption(options.soundDriver, optarg, AudioDriverList))
				{
					InvalidArgument(optarg, "--sound");
					badArg = true;
				}
				break;
			case STEREOSFX_OPT:
				options.stereoSFX = true;
				break;
			case ADDON_OPT:
				options.addons.push_back(optarg);
				break;
			case ADDONDIR_OPT:
				options.addonDir = optarg;
				break;
			case ACCEL_OPT:
				{
					if (const auto listValue {getOptionListValue(AccelList, optarg)}; listValue.has_value())
					{
						force_platform = static_cast<PLATFORM_TYPE>(*listValue);
					}
					else
					{
						InvalidArgument(optarg, "--accel");
						badArg = true;
					}
					break;
				}
			case SAFEMODE_OPT:
				options.safeMode = true;
				break;
			case RENDERER_OPT:
				options.graphicsBackend = optarg;
				break;
			case CHEATMODE_OPT:
				setOption(options.cheatMode, true);
				break;
			case GODMODE_OPT:
				{
					int temp;
					if (const auto godModeVal {parseOptionValue<int>(optarg, "God Modes")}; godModeVal.has_value())
					{
						if (temp < 0 || temp > 2)
						{
							error::saveError("God Mode has to be 0, 1, or 2. Got %d", *godModeVal);
							badArg = true;
						}
						else
						{
							options.optGodModes = *godModeVal;
						}
					}
					else
					{
						badArg = true;
					}
					break;
				}
			case TDM_OPT:
				{
					if (const auto temp {parseOptionValue<int>(optarg, "Time Dilation scale")}; temp.has_value())
					{
						if (*temp < 0 || *temp > 2)
						{
							error::saveError("\nTime Dilation scale has to be "
											 "0, 1, or 2.\n");
							badArg = true;
						}
						else
						{
							options.timeDilationScale = *temp;
						}
					}
					else
					{
						badArg = true;
					}
					break;
				}
			case BWARP_OPT:
				setOption(options.bubbleWarp, true);
				break;
			case UNLOCKSHIPS_OPT:
				setOption(options.unlockShips, true);
				break;
			case HEADSTART_OPT:
				setOption(options.headStart, true);
				break;
			case UPGRADES_OPT:
				//setBoolOption (&options.unlockUpgrades, true);
				break;
			case INFINITERU_OPT:
				setOption(options.infiniteRU, true);
				break;
			case SKIPINTRO_OPT:
				setOption(options.skipIntro, true);
				break;
			case MENUMUS_OPT:
				setOption(options.mainMenuMusic, true);
				break;
			case NEBU_OPT:
				setOption(options.nebulae, true);
				break;
			case ORBITS_OPT:
				setOption(options.orbitingPlanets, true);
				break;
			case TEXTPLAN_OPT:
				setOption(options.texturedPlanets, true);
				break;
			case DATE_OPT:
				{
					if (const auto temp {parseOptionValue<int>(optarg, "Date Format")}; temp.has_value())
					{
						if (*temp < 0 || *temp > 3)
						{
							error::saveError("\nDate Format has to be 0, 1, 2, or 3.\n");
							badArg = true;
						}
						else
						{
							options.optDateFormat = *temp;
						}
					}
					else
					{
						badArg = true;
						break;
					}
					break;
				}
			case INFFUEL_OPT:
				setOption(options.infiniteFuel, true);
				break;
			case PICKUP_OPT:
				setOption(options.partialPickup, true);
				break;
			case SUBMENU_OPT:
				setOption(options.submenu, true);
				break;
			case INFCRED_OPT:
				setOption(options.infiniteCredits, true);
				break;
			case CUSTBORD_OPT:
				setOption(options.customBorder, true);
				break;
			case SEEDTYPE_OPT:
				{
					if (const auto temp {parseOptionValue<int>(optarg, "Seed Type")}; temp.has_value())
					{
						if (*temp < 0 || *temp > 3)
						{
							error::saveError("\nSeed Type has to be 0, 1, 2, or 3.\n");
							badArg = true;
						}
						else
						{
							options.seedType = static_cast<SeedType>(*temp);
						}
					}
					else
					{
						badArg = true;
					}
					break;
				}
			case EXSEED_OPT:
				{
					if (const auto temp {parseOptionValue<int>(optarg, "Custom Seed")}; temp.has_value())
					{
						if (!SANE_SEED(*temp))
						{
							error::saveError("\nCustom Seed can not be less than %d or "
											 "greater than %d.\n",
											 MIN_SEED, MAX_SEED);
							badArg = true;
						}
						else
						{
							options.customSeed = *temp;
						}
					}
					else
					{
						badArg = true;
					}
					break;
				}
			case SHIPSEED_OPT:
				setOption(options.shipSeed, true);
				break;
			case SPHERECOLORS_OPT:
				{
					if (const auto temp {parseOptionValue<int>(optarg, "Sphere Colors")}; temp.has_value())
					{
						if (*temp < 0 || *temp > 1)
						{
							error::saveError("\nSphere Colors has to 0 or 1.\n");
							badArg = true;
						}
						else
						{
							options.sphereColors = *temp;
						}
					}
					else
					{
						badArg = true;
					}
					break;
				}
			case SPACEMUSIC_OPT:
				{
					if (const auto temp {parseOptionValue<int>(optarg, "Ambient Space Music")}; temp.has_value())
					{
						if (*temp < 0 || *temp > 2)
						{
							error::saveError("\nAmbient Space Music has to be "
											 "0, 1, or 2.\n");
							badArg = true;
						}
						else
						{
							options.spaceMusic = *temp;
						}
					}
					else
					{
						badArg = true;
						break;
					}
					break;
				}
			case WHOLEFUEL_OPT:
				setOption(options.wholeFuel, true);
				break;
			case DIRJOY_OPT:
				setOption(options.directionalJoystick, true);
				break;
			case LANDHOLD_OPT:
				if (!setChoiceOption(options.landerHold, optarg))
				{
					InvalidArgument(optarg, "--landerhold");
					badArg = true;
				}
				break;
			case SCRTRANS_OPT:
				if (!setChoiceOption(options.scrTrans, optarg))
				{
					InvalidArgument(optarg, "--scrtrans");
					badArg = true;
				}
				break;
			case DIFFICULTY_OPT:
				{
					if (const auto temp {parseOptionValue<int>(optarg, "Difficulty")}; temp.has_value())
					{
						if (*temp < 0 || *temp > 3)
						{
							error::saveError("\nDifficulty has to be 0, 1, 2, or 3.\n");
							badArg = true;
						}
						else
						{
							options.optDiffChooser = options.optDifficulty = *temp;
							if (temp > 2)
							{
								options.optDifficulty = 0;
							}
						}
					}
					else
					{
						badArg = true;
					}
					break;
				}
			case FUELRANGE_OPT:
				{
					if (const auto temp {parseOptionValue<int>(optarg, "Fuel range indicator")}; temp.has_value())
					{
						if (*temp < 0 || *temp > 3)
						{
							error::saveError("\nFuel range indicator has to be 0, 1, 2,"
											 " or 3.\n");
							badArg = true;
						}
						else
						{
							options.optFuelRange = *temp;
						}
					}
					else
					{
						badArg = true;
					}
					break;
				}
			case EXTENDED_OPT:
				setOption(options.extended, true);
				break;
			case NOMAD_OPT:
				{
					if (const auto temp {parseOptionValue<int>(optarg, "Nomad Mode type")}; temp.has_value())
					{
						if (*temp < 0 || *temp > 2)
						{
							error::saveError("\nNomad Mode has to be 0, 1, or 2.");
							badArg = true;
						}
						else
						{
							options.nomad = *temp;
						}
					}
					else
					{
						badArg = true;
					}
					break;
				}
			case GAMEOVER_OPT:
				setOption(options.gameOver, true);
				break;
			case SHIPDIRIP_OPT:
				setOption(options.shipDirectionIP, true);
				break;
			case HAZCOLORS_OPT:
				setOption(options.hazardColors, true);
				break;
			case ORZFONT_OPT:
				setOption(options.orzCompFont, true);
				break;
			case CONTYPE_OPT:
				{
					if (const auto temp {parseOptionValue<int>(optarg, "Controller Type")}; temp.has_value())
					{
						if (*temp < 0 || *temp > 2)
						{
							error::saveError("Controller type has to be 0, 1, or 2.");
							badArg = true;
						}
						else
						{
							options.optControllerType = *temp;
						}
					}
					else
					{
						badArg = true;
					}
					break;
				}
			case SISFACEHS_OPT:
				setOption(options.smartAutoPilot, true);
				break;
			case COLORPLAN_OPT:
				if (!setOption(options.tintPlanSphere, optarg, "Planet sphere tint"))
				{
					InvalidArgument(optarg, "--tintplansphere");
					badArg = true;
				}
				break;
			case PLANSTYLE_OPT:
				if (!setOption(options.planetStyle, optarg, "Planet style"))
				{
					InvalidArgument(optarg, "--planetstyle");
					badArg = true;
				}
				break;
			case STARBACK_OPT:
				{
					if (const auto temp {parseOptionValue<int>(optarg, "Star Background")}; temp.has_value())
					{
						if (*temp < 0 || *temp > 3)
						{
							error::saveError("Star background has to be between 0-3.");
							badArg = true;
						}
						else
						{
							options.starBackground = *temp;
						}
					}
					else
					{
						badArg = true;
					}
					break;
				}
			case SCANSTYLE_OPT:
				if (!setOption(options.scanStyle, optarg, "Scan style"))
				{
					InvalidArgument(optarg, "--scanstyle");
					badArg = true;
				}
				break;
			case OSCILLO_OPT:
				setOption(options.nonStopOscill, true);
				break;
			case OSCSTYLE_OPT:
				if (!setOption(options.scopeStyle, optarg, "Oscilloscope style"))
				{
					InvalidArgument(optarg, "--scopestyle");
					badArg = true;
				}
				break;
			case HYPERSTARS_OPT:
				setOption(options.hyperStars, true);
				break;
			case LANDSTYLE_OPT:
				if (!setOption(options.landerStyle, optarg, "Lander view"))
				{
					InvalidArgument(optarg, "--landerview");
					badArg = true;
				}
				break;
			case PLANTEX_OPT:
				if (strcmp(optarg, "uqm") == 0)
				{
					setOption(options.planetTexture, true);
				}
				else if (strcmp(optarg, "3do") == 0)
				{
					setOption(options.planetTexture, false);
				}
				else
				{
					InvalidArgument(optarg, "--planettexture");
					error::saveError("Planet Texture can only be set to '3do' or 'uqm'");
					badArg = true;
				}
				break;
			case SISENGINE_OPT:
				if (!setChoiceOption(options.flagshipColor, optarg))
				{
					InvalidArgument(optarg, "--sisenginecolor");
					badArg = true;
				}
				break;
			case NOHSENC_OPT:
				setOption(options.noHQEncounters, true);
				break;
			case DECLEANSE_OPT:
				setOption(options.deCleansing, true);
				break;
			case NOMELEEOBJ_OPT:
				setOption(options.meleeObstacles, true);
				break;
			case SHOWSTARS_OPT:
				setOption(options.showVisitedStars, true);
				break;
			case UNSCALEDSS_OPT:
				setOption(options.unscaledStarSystem, true);
				break;
			case SCANSPH_OPT:
				if (const auto temp {parseOptionValue<int>(optarg, "Sphere Type")}; temp.has_value())
				{
					if (*temp < 0 || *temp > 2)
					{
						error::saveError("Sphere Type has to be between 0-2");
						badArg = true;
					}
					else
					{
						options.sphereType = *temp;
					}
				}
				else
				{
					badArg = true;
				}
				break;
SLAUGHTER_OPT:
				setOption(options.slaughterMode, true);
				break;
			case SISADVAP_OPT:
				setOption(options.advancedAutoPilot, true);
				break;
			case MELEETIPS_OPT:
				setOption(options.meleeToolTips, true);
				break;
			case MUSICRESUME_OPT:
				if (const auto temp {parseOptionValue<int>(optarg, "Music Resume")}; temp.has_value())
				{
					if (*temp < 0 || *temp > 2)
					{
						error::saveError("Music Resume has to be between 0-2");
						badArg = true;
					}
					else
					{
						options.musicResume = *temp;
					}
				}
				else
				{
					badArg = true;
				}
				break;
			case WINDTYPE_OPT:
				if (const auto temp {parseOptionValue<int>(optarg, "Window Type")}; temp.has_value())
				{
					if (*temp < 0 || *temp > 2)
					{
						error::saveError("Window type has to be between 0-2");
						badArg = true;
					}
					else
					{
						options.windowType = *temp;
					}
				}
				else
				{
					badArg = true;
				}
				break;
			case SCATTERELEMS_OPT:
				setOption(options.scatterElements, true);
				break;
			case SHOWUPG_OPT:
				setOption(options.showUpgrades, true);
				break;
			case FLTPTSYS_OPT:
				setOption(options.fleetPointSys, true);
				break;
			case SHIPSTORE_OPT:
				setOption(options.shipStore, true);
				break;
			case CAPTNAMES_OPT:
				setOption(options.captainNames, true);
				break;
			case DOSMENUS_OPT:
				setOption(options.dosMenus, true);
				break;
			case MELEE_OPT:
				optSuperMelee = true;
				break;
			case LOADGAME_OPT:
				optLoadGame = true;
				break;
			case NEBUVOL_OPT:
				if (const auto temp {parseOptionValue<int>(optarg, "Nebulae Volume")}; temp.has_value())
				{
					if (*temp < 0 || *temp > 50)
					{
						error::saveError("Nebulae volume has to be between 0-50");
						badArg = true;
					}
					else
					{
						options.nebulaevol = *temp;
					}
				}
				else
				{
					badArg = true;
				}
				break;
			case CLAPAK_OPT:
				optNoClassic = true;
				break;
#ifdef NETPLAY
			case NETHOST1_OPT:
				g_netplayOptions.peer[0].isServer = false;
				g_netplayOptions.peer[0].host = optarg;
				break;
			case NETPORT1_OPT:
				g_netplayOptions.peer[0].port = optarg;
				break;
			case NETHOST2_OPT:
				g_netplayOptions.peer[1].isServer = false;
				g_netplayOptions.peer[1].host = optarg;
				break;
			case NETPORT2_OPT:
				g_netplayOptions.peer[1].port = optarg;
				break;
			case NETDELAY_OPT:
				if (const auto temp {parseOptionValue<int>(optarg, "network input delay")}; temp.has_value())
				{

					if (g_netplayOptions.inputDelay > BATTLE_FRAME_RATE)
					{
						error::saveError("Network input delay is absurdly large.");
						badArg = true;
					}
					else
					{
						g_netplayOptions.inputDelay = *temp;
					}
				}
				else
				{
					badArg = true;
				}
				break;

#endif
			default:
				error::saveError("Error: Unknown option '%s'",
								 optionIndex < 0 ? "<unknown>" :
												   longOptions[optionIndex].name);
				badArg = true;
				break;
		}
	}

	if (!badArg && optind != args.size())
	{
		error::saveError("\nError: Extra arguments found on the command line.");
		badArg = true;
	}

	return badArg ? EXIT_FAILURE : EXIT_SUCCESS;
}


void printUsage(FILE* out, const OptionsStruct& defaults)
{
	FILE* old = log_setOutput(out);
	log_captureLines(LOG_CAPTURE_ALL);

	log_add(log_User, "Options:");
	log_add(log_User, "  -r, --res=WIDTHxHEIGHT (default: 640x480, bigger "
					  "works only with --opengl)");
	log_add(log_User, "  -f, --fullscreen (default: 0)");
	log_add(log_User, "  -w, --windowed (default: true)");
	log_add(log_User, "  -o, --opengl (default: %s)", defaults.opengl.toString());
	log_add(log_User, "  -x, --nogl (default: %s)", defaults.opengl.value ? OptionFalseText : OptionTrueText);
	log_add(log_User, "  -k, --keepaspectratio (default: %s)", defaults.keepAspectRatio.toString());
	log_add(log_User, "  -c, --scale=MODE (bilinear, biadapt, biadv, triscan, hq or none (default) )");
	log_add(log_User, "  -b, --meleezoom=MODE (step, aka pc, or smooth, aka 3do; default is 3do)");
	log_add(log_User, "  -s, --scanlines (default: %s)", defaults.scanlines.toString());
	log_add(log_User, "  -p, --fps (default: %s)", defaults.showFps.toString());
	log_add(log_User, "  -g, --gamma=CORRECTIONVALUE (default: 1.0, which causes no change)");
	log_add(log_User, "  -C, --configdir=CONFIGDIR");
	log_add(log_User, "  -n, --contentdir=CONTENTDIR");
	log_add(log_User, "  -M, --musicvol=VOLUME (0-100, default 100)");
	log_add(log_User, "  -S, --sfxvol=VOLUME (0-100, default 100)");
	log_add(log_User, "  -T, --speechvol=VOLUME (0-100, default 100)");
	log_add(log_User, "  -q, --audioquality=QUALITY (high, medium or low, default medium)");
	log_add(log_User, "  -u, --nosubtitles");
	log_add(log_User, "  -l, --logfile=FILE (sends console output to logfile FILE)");
	log_add(log_User, "  --addon ADDON (using a specific addon; may be specified multiple times)");
	log_add(log_User, "  --addondir=ADDONDIR (directory where addons reside)");
	log_add(log_User, "  --renderer=name (Select named rendering engine if possible)");
	log_add(log_User, "  --sound=DRIVER (openal, mixsdl, none; default mixsdl)");
	log_add(log_User, "  --stereosfx (enables positional sound effects, currently only for openal)");
	log_add(log_User, "  --safe (start in safe mode)");
#ifdef NETPLAY
	log_add(log_User, "  --nethostN=HOSTNAME (server to connect to for player N (1=bottom, 2=top)");
	log_add(log_User, "  --netportN=PORT (port to connect to/listen on for player N (1=bottom, 2=top)");
	log_add(log_User, "  --netdelay=FRAMES (number of frames to buffer/delay network input for");
#endif
	log_add(log_User, "The following options can take either '3do' or 'pc' as an option:");
	log_add(log_User, "  -i, --intro : Intro/ending version (default: %s)", defaults.whichIntro.toString());
	log_add(log_User, "  --cscan     : coarse-scan display, pc=text, 3do=hieroglyphs (default: %s)", defaults.whichCoarseScan.toString());
	log_add(log_User, "  --menu      : menu type, pc=text, 3do=graphical (default: %s)", defaults.whichMenu.toString());
	log_add(log_User, "  --font      : font types and colors (default: %s)", defaults.whichFonts.toString());
	log_add(log_User, "  --shield    : slave shield type; pc=static, 3do=throbbing (default: %s)", defaults.whichShield.toString());
	log_add(log_User, "  --scroll    : ff/frev during comm.  pc=per-page, 3do=smooth (default: %s)", defaults.smoothScroll.toString());

	log_add(log_User, "\nThe following options are MegaMod specific\n");

	log_add(log_User, "  --kohrstahp : Stops Kohr-Ah advancing. (default: %s)", defaults.cheatMode.toString());
	log_add(log_User, "  --precursormode : =1 Infinite ship battery. =2 No damage, =3 Infinite ship battery and no damage (default: 0)");
	log_add(log_User, "  --timedilation : =1 Time is slowed down times 6. =2 Time is sped up times 5 (default: 0)");
	log_add(log_User, "  --bubblewarp : Instantaneous travel to any point on the Starmap. (default: %s)", defaults.bubbleWarp.toString());
	log_add(log_User, "  --unlockships : Allows you to purchase ships that you can't normally acquire in the main game. (default: %s)", defaults.unlockShips.toString());
	log_add(log_User, "  --headstart : Gives you an extra storage bay full of minerals, Fwiffo, and the Moonbase during a new game (default: %s)", defaults.headStart.toString());
	log_add(log_User, "  --unlockupgrades : Unlocks every upgrade for your flagship and landers. (default: %s)", defaults.unlockUpgrades.toString());
	log_add(log_User, "  --infiniteru : Gives you infinite R.U. as long as the cheat is on (default: %s)", defaults.infiniteRU.toString());
	log_add(log_User, "  --skipintro : Skips the intro and Logo fmv (default: %s)", defaults.skipIntro.toString());
	log_add(log_User, "  --mainmenumusic : Switches the main menu music on/off (default: %s)", defaults.mainMenuMusic.toString());
	log_add(log_User, "  --nebulae : Enables/Disables nebulae in star systems (default: %s)", defaults.nebulae.toString());
	log_add(log_User, "  --orbitingplanets : Enables/Disables orbiting planets in star systems (default: %s)", defaults.orbitingPlanets.toString());
	log_add(log_User, "  --texturedplanets : Enables/Disables textured planets in star systems (default: %s)", defaults.texturedPlanets.toString());
	log_add(log_User, "  --infinitefuel : Infinite fuel in the main game (default: %s)", defaults.infiniteFuel.toString());
	log_add(log_User, "  --partialpickup : Enables/Disables partial mineral pickup  (default: %s)", defaults.partialPickup.toString());
	log_add(log_User, "  --submenu : Enables/Disables mineral and star map keys submenu  (default: %s)", defaults.submenu.toString());
	log_add(log_User, "  --dateformat : 0: MMM DD.YYYY | 1: MM.DD.YYYY | 2: DD MMM.YYYY | 3: DD.MM.YYYY (default: 0)");
	log_add(log_User, "  --infinitecredits: Gives you infinite Melnorme Credits  (default: %s)", defaults.infiniteCredits.toString());
	log_add(log_User, "  --melee : Takes you straight to Super Melee after the splash screen.");
	log_add(log_User, "  --loadgame : Takes you straight to the Load Game sceen after the splash screen.");
	log_add(log_User, "  --customborder : Enables the custom border frame. (default: %s)", defaults.customBorder.toString());
	log_add(log_User, "  --seedtype: 0: Default seed | 1: Seed planets  | 2: Seed Melnorme/Rainbow/Quasispace  | 3: Seed Starmap (default: 0)");
	log_add(log_User, "  --customseed=# : Allows you to customize the internal seed used to generate the solar systems in-game. (default: 16807)");
	log_add(log_User, "  --shipseed: Seed the ships assigned to each race. Uses --customseed value (default %s)", defaults.shipSeed.toString());
	log_add(log_User, "  --spherecolors: 0: Default colors | 1: StarSeed colors (default: 0)");
	log_add(log_User, "  --spacemusic #: Enables localized music for aliens when you are in their sphere of influence\n0: Default (OFF) | 1: No Spoilers | 2: Spoilers");
	log_add(log_User, "  --wholefuel : Enables the display of the whole fuel value in the ship status (default: %s)", defaults.wholeFuel.toString());
	log_add(log_User, "  --dirjoystick : Enables the use of directional joystick controls for Android (default: %s)", defaults.directionalJoystick.toString());
	log_add(log_User, "  --landerhold : Switch between PC/3DO max lander hold, pc=64, 3do=50 (default: %s)", defaults.landerHold.toString());
	log_add(log_User, "  --scrtrans : Screen transitions, pc=instantaneous, 3do=crossfade (default: %s)", defaults.scrTrans.toString());
	log_add(log_User, "  --difficulty : 0: Normal | 1: Easy | 2: Hard | 3: Choose at Start (default: 0)");
	log_add(log_User, "  --fuelrange : Enables extra fuel range indicators : 0: No indicators | 1: Fuel range at destination | 2: Remaining fuel range to Sol | 3: Both option 1 and 2  enabled simultaneously (default: 0)");
	log_add(log_User, "  --extended : Enables Extended Edition features (default: %s)", defaults.extended.toString());
	log_add(log_User, "  --nomad : Enables 'Nomad Mode' (No Starbase) : 0: Off | 1: Easy | 2: Normal (default: 0)");
	log_add(log_User, "  --gameover : Enables Game Over cutscenes (default: %s)", defaults.gameOver.toString());
	log_add(log_User, "  --shipdirectionip : Enable NPC ships in IP to face their direction of travel (default: %s)", defaults.shipDirectionIP.toString());
	log_add(log_User, "  --hazardcolors : Enable colored text based on hazard severity when viewing planetary scans (default: %s)", defaults.hazardColors.toString());
	log_add(log_User, "  --orzcompfont : Enable alternate font for untranslatable Orz speech (default: %s)", defaults.orzCompFont.toString());
	log_add(log_User, "  --smartautopilot : Activating Auto-Pilot within Solar System pilots the Flagship out via the shortest route. (default: %s)", defaults.smartAutoPilot.toString());
	log_add(log_User, "  --controllertype : 0: Keyboard | 1: Xbox | 2: PlayStation 4 (default: 0)");
	log_add(log_User, "  --tintplansphere : Tint the planet sphere with scan color during scan (default: %s)", defaults.tintPlanSphere.toString());
	log_add(log_User, "  --planetstyle : Choose between PC or 3DO planet color and shading (default: %s)", defaults.planetStyle.toString());
	log_add(log_User, "  --starbackground : Set the background stars in solar system between PC, 3DO, UQM, or HD-mod patterns (default: pc)");
	log_add(log_User, "  --scanstyle : Choose between PC or 3DO scanning types (default: %s)", defaults.scanStyle.toString());
	log_add(log_User, "  --nonstoposcill : Oscilloscope uses both voice and music data (default: %s)", defaults.nonStopOscill.toString());
	log_add(log_User, "  --scopestyle : Choose between either the PC or 3DO oscilloscope type (default: %s)", defaults.scopeStyle.toString());
	log_add(log_User, "  --animhyperstars : HD only - Use old HD-mod animated HyperSpace stars (default: %s)", defaults.hyperStars.toString());
	log_add(log_User, "  --landerview : Choose between either the PC or 3DO lander view (default: %s)", defaults.landerStyle.toString());
	log_add(log_User, "  --planettexture : Choose between either 3DO or UQM planet map texture [when not using custom seed] (default: 3do)");
	log_add(log_User, "  --sisenginecolor : Choose between either the PC or 3DO Flagship engine color (default: %s)", defaults.flagshipColor.toString());
	log_add(log_User, "  --nohqencounters : Disables HyperSpace encounters (default: %s)", defaults.noHQEncounters.toString());
	log_add(log_User, "  --decleanse : Moves the Death March 100 years ahead from its actual start date [does not work once the Death March has started] (default: %s)", defaults.deCleansing.toString());
	log_add(log_User, "  --nomeleeobstacles : Removes the planet and asteroids from Super Melee (default: %s)", defaults.meleeObstacles.toString());
	log_add(log_User, "  --showvisitstars : Dim visited stars on the StarMap and encase the star name in parenthesis (default: %s)", defaults.showVisitedStars.toString());
	log_add(log_User, "  --unscaledstarsystem : Show the classic HD-mod Beta Star System view (default: %s)", defaults.unscaledStarSystem.toString());
	log_add(log_User, "  --spheretype : Choose between PC, 3DO, or UQM scan sphere styles (default: %s)", defaults.sphereType.toString());
	log_add(log_User, "  --nebulaevol=VOLUME (0-50, default 11)");
	log_add(log_User, "  --slaughtermode : Affect a race's SOI by destroying their ships in battle (default: %s)", defaults.slaughterMode.toString());
	log_add(log_User, "  --advancedautopilot : Finds the route that uses the least amount of fuel through HyperSpace or QuasiSpace and Auto-Pilots the Flagship on the best route (default: %s)", defaults.advancedAutoPilot.toString());
	log_add(log_User, "  --meleetooltips : Show SC1-style ship description tooltips at the bottom of the Super-Melee screen when picking a ship for your fleet (default: %s)", defaults.meleeToolTips.toString());
	log_add(log_User, "  --musicresume : Resumes the music in UQM where it last left off : 0: Off | 1: 5 Minutes | 2: Indefinite (default: 0)");
	log_add(log_User, "  --windowtype : Choose between DOS, 3DO or UQM window types : 0: DOS | 1: 3DO | 2: UQM (default: 0)");
	log_add(log_User, "  --scatterelements : Scatter a percentage of the elements in the lander's cargo hold onto the planet's surface when the lander explodes (default: %s)", defaults.scatterElements.toString());
	log_add(log_User, "  --showupgrades : Show lander upgrade graphics when exploring planets (default: %s)", defaults.showUpgrades.toString());
	log_add(log_User, "  --fleetpointsys : Restrict the amount of ships that can be purchased via their melee points (default: %s)", defaults.fleetPointSys.toString());
	log_add(log_User, "  --shipstore : Enable a storage queue accessed at the shipyard (default: %s)", defaults.shipStore.toString());
	log_add(log_User, "  --captainnames : Display captain names at shipyard (default: %s)", defaults.captainNames.toString());
	log_add(log_User, "  --dosmenus : Display DOS style menu in shipyard in place of SIS window (default: %s)", defaults.dosMenus.toString());

	log_setOutput(old);
}
