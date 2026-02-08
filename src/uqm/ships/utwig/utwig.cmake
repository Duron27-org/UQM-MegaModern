############################################################


set(uqm_src_uqm_ships_utwig_master_files "")


############################################################
# Local files
set(uqm_src_uqm_ships_utwig_files
	"src/uqm/ships/utwig/icode.h"
	"src/uqm/ships/utwig/resinst.h"
	"src/uqm/ships/utwig/utwig.cmake"
	"src/uqm/ships/utwig/utwig.cpp"
	"src/uqm/ships/utwig/utwig.h"
)

source_group("src\\uqm\\ships\\utwig" FILES ${uqm_src_uqm_ships_utwig_files})
list(APPEND uqm_src_uqm_ships_utwig_master_files ${uqm_src_uqm_ships_utwig_files})
