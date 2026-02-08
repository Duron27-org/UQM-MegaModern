############################################################


set(uqm_src_uqm_comm_vux_master_files "")


############################################################
# Local files
set(uqm_src_uqm_comm_vux_files
	"src/uqm/comm/vux/resinst.h"
	"src/uqm/comm/vux/strings.h"
	"src/uqm/comm/vux/vux.cmake"
	"src/uqm/comm/vux/vuxc.cpp"
)

source_group("src\\uqm\\comm\\vux" FILES ${uqm_src_uqm_comm_vux_files})
list(APPEND uqm_src_uqm_comm_vux_master_files ${uqm_src_uqm_comm_vux_files})
