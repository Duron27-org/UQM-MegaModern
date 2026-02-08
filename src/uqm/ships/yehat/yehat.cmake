############################################################


set(uqm_src_uqm_ships_yehat_master_files "")


############################################################
# Local files
set(uqm_src_uqm_ships_yehat_files
	"src/uqm/ships/yehat/icode.h"
	"src/uqm/ships/yehat/resinst.h"
	"src/uqm/ships/yehat/yehat.cmake"
	"src/uqm/ships/yehat/yehat.cpp"
	"src/uqm/ships/yehat/yehat.h"
)

source_group("src\\uqm\\ships\\yehat" FILES ${uqm_src_uqm_ships_yehat_files})
list(APPEND uqm_src_uqm_ships_yehat_master_files ${uqm_src_uqm_ships_yehat_files})
