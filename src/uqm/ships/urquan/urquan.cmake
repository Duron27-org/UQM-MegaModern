############################################################


set(uqm_src_uqm_ships_urquan_master_files "")


############################################################
# Local files
set(uqm_src_uqm_ships_urquan_files
	"src/uqm/ships/urquan/icode.h"
	"src/uqm/ships/urquan/resinst.h"
	"src/uqm/ships/urquan/urquan.cmake"
	"src/uqm/ships/urquan/urquan.cpp"
	"src/uqm/ships/urquan/urquan.h"
)

source_group("src\\uqm\\ships\\urquan" FILES ${uqm_src_uqm_ships_urquan_files})
list(APPEND uqm_src_uqm_ships_urquan_master_files ${uqm_src_uqm_ships_urquan_files})
