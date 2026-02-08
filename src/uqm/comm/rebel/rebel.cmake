############################################################


set(uqm_src_uqm_comm_rebel_master_files "")


############################################################
# Local files
set(uqm_src_uqm_comm_rebel_files
	"src/uqm/comm/rebel/rebel.cmake"
	"src/uqm/comm/rebel/rebel.cpp"
	"src/uqm/comm/rebel/strings.h"
)

source_group("src\\uqm\\comm\\rebel" FILES ${uqm_src_uqm_comm_rebel_files})
list(APPEND uqm_src_uqm_comm_rebel_master_files ${uqm_src_uqm_comm_rebel_files})
