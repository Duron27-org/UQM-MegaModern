############################################################


set(uqm_src_uqm_comm_urquan_master_files "")


############################################################
# Local files
set(uqm_src_uqm_comm_urquan_files
	"src/uqm/comm/urquan/resinst.h"
	"src/uqm/comm/urquan/strings.h"
	"src/uqm/comm/urquan/urquan.cmake"
	"src/uqm/comm/urquan/urquanc.cpp"
)

source_group("src\\uqm\\comm\\urquan" FILES ${uqm_src_uqm_comm_urquan_files})
list(APPEND uqm_src_uqm_comm_urquan_master_files ${uqm_src_uqm_comm_urquan_files})
