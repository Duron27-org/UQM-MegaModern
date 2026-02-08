############################################################


set(uqm_src_uqm_comm_yehat_master_files "")


############################################################
# Local files
set(uqm_src_uqm_comm_yehat_files
	"src/uqm/comm/yehat/resinst.h"
	"src/uqm/comm/yehat/strings.h"
	"src/uqm/comm/yehat/yehat.cmake"
	"src/uqm/comm/yehat/yehatc.cpp"
)

source_group("src\\uqm\\comm\\yehat" FILES ${uqm_src_uqm_comm_yehat_files})
list(APPEND uqm_src_uqm_comm_yehat_master_files ${uqm_src_uqm_comm_yehat_files})
