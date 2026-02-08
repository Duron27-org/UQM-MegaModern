############################################################


set(uqm_src_uqm_ships_supox_master_files "")


############################################################
# Local files
set(uqm_src_uqm_ships_supox_files
	"src/uqm/ships/supox/icode.h"
	"src/uqm/ships/supox/resinst.h"
	"src/uqm/ships/supox/supox.cmake"
	"src/uqm/ships/supox/supox.cpp"
	"src/uqm/ships/supox/supox.h"
)

source_group("src\\uqm\\ships\\supox" FILES ${uqm_src_uqm_ships_supox_files})
list(APPEND uqm_src_uqm_ships_supox_master_files ${uqm_src_uqm_ships_supox_files})
