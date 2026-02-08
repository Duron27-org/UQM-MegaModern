############################################################


set(uqm_src_uqm_comm_spathi_master_files "")


############################################################
# Local files
set(uqm_src_uqm_comm_spathi_files
	"src/uqm/comm/spathi/resinst.h"
	"src/uqm/comm/spathi/spathi.cmake"
	"src/uqm/comm/spathi/spathic.cpp"
	"src/uqm/comm/spathi/strings.h"
)

source_group("src\\uqm\\comm\\spathi" FILES ${uqm_src_uqm_comm_spathi_files})
list(APPEND uqm_src_uqm_comm_spathi_master_files ${uqm_src_uqm_comm_spathi_files})
