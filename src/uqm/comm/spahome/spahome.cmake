############################################################


set(uqm_src_uqm_comm_spahome_master_files "")


############################################################
# Local files
set(uqm_src_uqm_comm_spahome_files
	"src/uqm/comm/spahome/spahome.cmake"
	"src/uqm/comm/spahome/spahome.cpp"
	"src/uqm/comm/spahome/strings.h"
)

source_group("src\\uqm\\comm\\spahome" FILES ${uqm_src_uqm_comm_spahome_files})
list(APPEND uqm_src_uqm_comm_spahome_master_files ${uqm_src_uqm_comm_spahome_files})
