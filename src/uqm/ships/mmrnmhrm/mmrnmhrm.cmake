############################################################


set(uqm_src_uqm_ships_mmrnmhrm_master_files "")


############################################################
# Local files
set(uqm_src_uqm_ships_mmrnmhrm_files
	"src/uqm/ships/mmrnmhrm/icode.h"
	"src/uqm/ships/mmrnmhrm/mmrnmhrm.cmake"
	"src/uqm/ships/mmrnmhrm/mmrnmhrm.cpp"
	"src/uqm/ships/mmrnmhrm/mmrnmhrm.h"
	"src/uqm/ships/mmrnmhrm/resinst.h"
)

source_group("src\\uqm\\ships\\mmrnmhrm" FILES ${uqm_src_uqm_ships_mmrnmhrm_files})
list(APPEND uqm_src_uqm_ships_mmrnmhrm_master_files ${uqm_src_uqm_ships_mmrnmhrm_files})
