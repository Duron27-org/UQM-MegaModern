############################################################


set(uqm_src_uqm_ships_syreen_master_files "")


############################################################
# Local files
set(uqm_src_uqm_ships_syreen_files
	"src/uqm/ships/syreen/icode.h"
	"src/uqm/ships/syreen/resinst.h"
	"src/uqm/ships/syreen/syreen.cmake"
	"src/uqm/ships/syreen/syreen.cpp"
	"src/uqm/ships/syreen/syreen.h"
)

source_group("src\\uqm\\ships\\syreen" FILES ${uqm_src_uqm_ships_syreen_files})
list(APPEND uqm_src_uqm_ships_syreen_master_files ${uqm_src_uqm_ships_syreen_files})
