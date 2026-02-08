############################################################


set(uqm_src_uqm_ships_arilou_master_files "")


############################################################
# Local files
set(uqm_src_uqm_ships_arilou_files
	"src/uqm/ships/arilou/arilou.cmake"
	"src/uqm/ships/arilou/arilou.cpp"
	"src/uqm/ships/arilou/arilou.h"
	"src/uqm/ships/arilou/icode.h"
	"src/uqm/ships/arilou/resinst.h"
)

source_group("src\\uqm\\ships\\arilou" FILES ${uqm_src_uqm_ships_arilou_files})
list(APPEND uqm_src_uqm_ships_arilou_master_files ${uqm_src_uqm_ships_arilou_files})
