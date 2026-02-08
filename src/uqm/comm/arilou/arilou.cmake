############################################################


set(uqm_src_uqm_comm_arilou_master_files "")


############################################################
# Local files
set(uqm_src_uqm_comm_arilou_files
	"src/uqm/comm/arilou/arilou.cmake"
	"src/uqm/comm/arilou/arilouc.cpp"
	"src/uqm/comm/arilou/resinst.h"
	"src/uqm/comm/arilou/strings.h"
)

source_group("src\\uqm\\comm\\arilou" FILES ${uqm_src_uqm_comm_arilou_files})
list(APPEND uqm_src_uqm_comm_arilou_master_files ${uqm_src_uqm_comm_arilou_files})
