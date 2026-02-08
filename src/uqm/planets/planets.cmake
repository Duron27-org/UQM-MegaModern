############################################################


set(uqm_src_uqm_planets_master_files "")

############################################################
# Sub-directories
include("src/uqm/planets/generate/generate.cmake")
list(APPEND uqm_src_uqm_planets_master_files ${uqm_src_uqm_planets_generate_master_files})

############################################################
# Local files
set(uqm_src_uqm_planets_files
	"src/uqm/planets/calc.cpp"
	"src/uqm/planets/cargo.cpp"
	"src/uqm/planets/devices.cpp"
	"src/uqm/planets/elemdata.h"
	"src/uqm/planets/generate.h"
	"src/uqm/planets/gentopo.cpp"
	"src/uqm/planets/lander.cpp"
	"src/uqm/planets/lander.h"
	"src/uqm/planets/lifeform.h"
	"src/uqm/planets/orbits.cpp"
	"src/uqm/planets/oval.cpp"
	"src/uqm/planets/pl_stuff.cpp"
	"src/uqm/planets/plandata.h"
	"src/uqm/planets/planets.cmake"
	"src/uqm/planets/planets.cpp"
	"src/uqm/planets/planets.h"
	"src/uqm/planets/plangen.cpp"
	"src/uqm/planets/pstarmap.cpp"
	"src/uqm/planets/report.cpp"
	"src/uqm/planets/roster.cpp"
	"src/uqm/planets/scan.cpp"
	"src/uqm/planets/scan.h"
	"src/uqm/planets/solarsys.cpp"
	"src/uqm/planets/solarsys.h"
	"src/uqm/planets/sundata.h"
	"src/uqm/planets/surface.cpp"
)

source_group("src\\uqm\\planets" FILES ${uqm_src_uqm_planets_files})
list(APPEND uqm_src_uqm_planets_master_files ${uqm_src_uqm_planets_files})
