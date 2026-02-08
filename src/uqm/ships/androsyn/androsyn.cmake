############################################################


set(uqm_src_uqm_ships_androsyn_master_files "")


############################################################
# Local files
set(uqm_src_uqm_ships_androsyn_files
	"src/uqm/ships/androsyn/androsyn.cmake"
	"src/uqm/ships/androsyn/androsyn.cpp"
	"src/uqm/ships/androsyn/androsyn.h"
	"src/uqm/ships/androsyn/icode.h"
	"src/uqm/ships/androsyn/resinst.h"
)

source_group("src\\uqm\\ships\\androsyn" FILES ${uqm_src_uqm_ships_androsyn_files})
list(APPEND uqm_src_uqm_ships_androsyn_master_files ${uqm_src_uqm_ships_androsyn_files})
