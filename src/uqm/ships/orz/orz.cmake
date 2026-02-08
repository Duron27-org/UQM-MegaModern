############################################################


set(uqm_src_uqm_ships_orz_master_files "")


############################################################
# Local files
set(uqm_src_uqm_ships_orz_files
	"src/uqm/ships/orz/icode.h"
	"src/uqm/ships/orz/orz.cmake"
	"src/uqm/ships/orz/orz.cpp"
	"src/uqm/ships/orz/orz.h"
	"src/uqm/ships/orz/resinst.h"
)

source_group("src\\uqm\\ships\\orz" FILES ${uqm_src_uqm_ships_orz_files})
list(APPEND uqm_src_uqm_ships_orz_master_files ${uqm_src_uqm_ships_orz_files})
