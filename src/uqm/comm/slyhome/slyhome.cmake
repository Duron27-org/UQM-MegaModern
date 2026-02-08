############################################################


set(uqm_src_uqm_comm_slyhome_master_files "")


############################################################
# Local files
set(uqm_src_uqm_comm_slyhome_files
	"src/uqm/comm/slyhome/resinst.h"
	"src/uqm/comm/slyhome/slyhome.cmake"
	"src/uqm/comm/slyhome/slyhome.cpp"
	"src/uqm/comm/slyhome/strings.h"
)

source_group("src\\uqm\\comm\\slyhome" FILES ${uqm_src_uqm_comm_slyhome_files})
list(APPEND uqm_src_uqm_comm_slyhome_master_files ${uqm_src_uqm_comm_slyhome_files})
