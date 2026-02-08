############################################################


set(uqm_src_uqm_ships_vux_master_files "")


############################################################
# Local files
set(uqm_src_uqm_ships_vux_files
	"src/uqm/ships/vux/icode.h"
	"src/uqm/ships/vux/resinst.h"
	"src/uqm/ships/vux/vux.cmake"
	"src/uqm/ships/vux/vux.cpp"
	"src/uqm/ships/vux/vux.h"
)

source_group("src\\uqm\\ships\\vux" FILES ${uqm_src_uqm_ships_vux_files})
list(APPEND uqm_src_uqm_ships_vux_master_files ${uqm_src_uqm_ships_vux_files})
