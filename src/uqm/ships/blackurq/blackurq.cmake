############################################################


set(uqm_src_uqm_ships_blackurq_master_files "")


############################################################
# Local files
set(uqm_src_uqm_ships_blackurq_files
	"src/uqm/ships/blackurq/blackurq.cmake"
	"src/uqm/ships/blackurq/blackurq.cpp"
	"src/uqm/ships/blackurq/blackurq.h"
	"src/uqm/ships/blackurq/icode.h"
	"src/uqm/ships/blackurq/resinst.h"
)

source_group("src\\uqm\\ships\\blackurq" FILES ${uqm_src_uqm_ships_blackurq_files})
list(APPEND uqm_src_uqm_ships_blackurq_master_files ${uqm_src_uqm_ships_blackurq_files})
