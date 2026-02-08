############################################################


set(uqm_src_uqm_ships_pkunk_master_files "")


############################################################
# Local files
set(uqm_src_uqm_ships_pkunk_files
	"src/uqm/ships/pkunk/icode.h"
	"src/uqm/ships/pkunk/pkunk.cmake"
	"src/uqm/ships/pkunk/pkunk.cpp"
	"src/uqm/ships/pkunk/pkunk.h"
	"src/uqm/ships/pkunk/resinst.h"
)

source_group("src\\uqm\\ships\\pkunk" FILES ${uqm_src_uqm_ships_pkunk_files})
list(APPEND uqm_src_uqm_ships_pkunk_master_files ${uqm_src_uqm_ships_pkunk_files})
