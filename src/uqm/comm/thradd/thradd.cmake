############################################################


set(uqm_src_uqm_comm_thradd_master_files "")


############################################################
# Local files
set(uqm_src_uqm_comm_thradd_files
	"src/uqm/comm/thradd/resinst.h"
	"src/uqm/comm/thradd/strings.h"
	"src/uqm/comm/thradd/thradd.cmake"
	"src/uqm/comm/thradd/thraddc.cpp"
)

source_group("src\\uqm\\comm\\thradd" FILES ${uqm_src_uqm_comm_thradd_files})
list(APPEND uqm_src_uqm_comm_thradd_master_files ${uqm_src_uqm_comm_thradd_files})
