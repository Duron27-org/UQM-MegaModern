############################################################


set(uqm_src_uqm_comm_pkunk_master_files "")


############################################################
# Local files
set(uqm_src_uqm_comm_pkunk_files
	"src/uqm/comm/pkunk/pkunk.cmake"
	"src/uqm/comm/pkunk/pkunkc.cpp"
	"src/uqm/comm/pkunk/resinst.h"
	"src/uqm/comm/pkunk/strings.h"
)

source_group("src\\uqm\\comm\\pkunk" FILES ${uqm_src_uqm_comm_pkunk_files})
list(APPEND uqm_src_uqm_comm_pkunk_master_files ${uqm_src_uqm_comm_pkunk_files})
