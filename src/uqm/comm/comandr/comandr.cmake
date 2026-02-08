############################################################


set(uqm_src_uqm_comm_comandr_master_files "")


############################################################
# Local files
set(uqm_src_uqm_comm_comandr_files
	"src/uqm/comm/comandr/comandr.cmake"
	"src/uqm/comm/comandr/comandr.cpp"
	"src/uqm/comm/comandr/resinst.h"
	"src/uqm/comm/comandr/strings.h"
)

source_group("src\\uqm\\comm\\comandr" FILES ${uqm_src_uqm_comm_comandr_files})
list(APPEND uqm_src_uqm_comm_comandr_master_files ${uqm_src_uqm_comm_comandr_files})
