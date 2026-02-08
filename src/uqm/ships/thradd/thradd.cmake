############################################################


set(uqm_src_uqm_ships_thradd_master_files "")


############################################################
# Local files
set(uqm_src_uqm_ships_thradd_files
	"src/uqm/ships/thradd/icode.h"
	"src/uqm/ships/thradd/resinst.h"
	"src/uqm/ships/thradd/thradd.cmake"
	"src/uqm/ships/thradd/thradd.cpp"
	"src/uqm/ships/thradd/thradd.h"
)

source_group("src\\uqm\\ships\\thradd" FILES ${uqm_src_uqm_ships_thradd_files})
list(APPEND uqm_src_uqm_ships_thradd_master_files ${uqm_src_uqm_ships_thradd_files})
