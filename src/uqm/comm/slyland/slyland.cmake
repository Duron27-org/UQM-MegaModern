############################################################


set(uqm_src_uqm_comm_slyland_master_files "")


############################################################
# Local files
set(uqm_src_uqm_comm_slyland_files
	"src/uqm/comm/slyland/resinst.h"
	"src/uqm/comm/slyland/slyland.cmake"
	"src/uqm/comm/slyland/slyland.cpp"
	"src/uqm/comm/slyland/strings.h"
)

source_group("src\\uqm\\comm\\slyland" FILES ${uqm_src_uqm_comm_slyland_files})
list(APPEND uqm_src_uqm_comm_slyland_master_files ${uqm_src_uqm_comm_slyland_files})
