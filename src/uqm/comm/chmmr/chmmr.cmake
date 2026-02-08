############################################################


set(uqm_src_uqm_comm_chmmr_master_files "")


############################################################
# Local files
set(uqm_src_uqm_comm_chmmr_files
	"src/uqm/comm/chmmr/chmmr.cmake"
	"src/uqm/comm/chmmr/chmmrc.cpp"
	"src/uqm/comm/chmmr/resinst.h"
	"src/uqm/comm/chmmr/strings.h"
)

source_group("src\\uqm\\comm\\chmmr" FILES ${uqm_src_uqm_comm_chmmr_files})
list(APPEND uqm_src_uqm_comm_chmmr_master_files ${uqm_src_uqm_comm_chmmr_files})
