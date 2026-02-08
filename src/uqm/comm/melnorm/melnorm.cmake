############################################################


set(uqm_src_uqm_comm_melnorm_master_files "")


############################################################
# Local files
set(uqm_src_uqm_comm_melnorm_files
	"src/uqm/comm/melnorm/melnorm.cmake"
	"src/uqm/comm/melnorm/melnorm.cpp"
	"src/uqm/comm/melnorm/resinst.h"
	"src/uqm/comm/melnorm/strings.h"
)

source_group("src\\uqm\\comm\\melnorm" FILES ${uqm_src_uqm_comm_melnorm_files})
list(APPEND uqm_src_uqm_comm_melnorm_master_files ${uqm_src_uqm_comm_melnorm_files})
