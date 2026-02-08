############################################################


set(uqm_src_uqm_comm_zoqfot_master_files "")


############################################################
# Local files
set(uqm_src_uqm_comm_zoqfot_files
	"src/uqm/comm/zoqfot/resinst.h"
	"src/uqm/comm/zoqfot/strings.h"
	"src/uqm/comm/zoqfot/zoqfot.cmake"
	"src/uqm/comm/zoqfot/zoqfotc.cpp"
)

source_group("src\\uqm\\comm\\zoqfot" FILES ${uqm_src_uqm_comm_zoqfot_files})
list(APPEND uqm_src_uqm_comm_zoqfot_master_files ${uqm_src_uqm_comm_zoqfot_files})
