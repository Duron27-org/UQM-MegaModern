############################################################


set(uqm_src_uqm_ships_sis_ship_master_files "")


############################################################
# Local files
set(uqm_src_uqm_ships_sis_ship_files
	"src/uqm/ships/sis_ship/icode.h"
	"src/uqm/ships/sis_ship/resinst.h"
	"src/uqm/ships/sis_ship/sis_ship.cmake"
	"src/uqm/ships/sis_ship/sis_ship.cpp"
	"src/uqm/ships/sis_ship/sis_ship.h"
)

source_group("src\\uqm\\ships\\sis_ship" FILES ${uqm_src_uqm_ships_sis_ship_files})
list(APPEND uqm_src_uqm_ships_sis_ship_master_files ${uqm_src_uqm_ships_sis_ship_files})
