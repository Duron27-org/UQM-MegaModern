############################################################


set(uqm_src_uqm_comm_blackur_master_files "")


############################################################
# Local files
set(uqm_src_uqm_comm_blackur_files
	"src/uqm/comm/blackur/blackur.cmake"
	"src/uqm/comm/blackur/blackurc.cpp"
	"src/uqm/comm/blackur/resinst.h"
	"src/uqm/comm/blackur/strings.h"
)

source_group("src\\uqm\\comm\\blackur" FILES ${uqm_src_uqm_comm_blackur_files})
list(APPEND uqm_src_uqm_comm_blackur_master_files ${uqm_src_uqm_comm_blackur_files})
