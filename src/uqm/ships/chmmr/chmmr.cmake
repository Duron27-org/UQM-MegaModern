############################################################


set(uqm_src_uqm_ships_chmmr_master_files "")


############################################################
# Local files
set(uqm_src_uqm_ships_chmmr_files
	"src/uqm/ships/chmmr/chmmr.cmake"
	"src/uqm/ships/chmmr/chmmr.cpp"
	"src/uqm/ships/chmmr/chmmr.h"
	"src/uqm/ships/chmmr/icode.h"
	"src/uqm/ships/chmmr/resinst.h"
)

source_group("src\\uqm\\ships\\chmmr" FILES ${uqm_src_uqm_ships_chmmr_files})
list(APPEND uqm_src_uqm_ships_chmmr_master_files ${uqm_src_uqm_ships_chmmr_files})
