############################################################


set(uqm_src_uqm_comm_supox_master_files "")


############################################################
# Local files
set(uqm_src_uqm_comm_supox_files
	"src/uqm/comm/supox/resinst.h"
	"src/uqm/comm/supox/strings.h"
	"src/uqm/comm/supox/supox.cmake"
	"src/uqm/comm/supox/supoxc.cpp"
)

source_group("src\\uqm\\comm\\supox" FILES ${uqm_src_uqm_comm_supox_files})
list(APPEND uqm_src_uqm_comm_supox_master_files ${uqm_src_uqm_comm_supox_files})
