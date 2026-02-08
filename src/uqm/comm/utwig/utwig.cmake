############################################################


set(uqm_src_uqm_comm_utwig_master_files "")


############################################################
# Local files
set(uqm_src_uqm_comm_utwig_files
	"src/uqm/comm/utwig/resinst.h"
	"src/uqm/comm/utwig/strings.h"
	"src/uqm/comm/utwig/utwig.cmake"
	"src/uqm/comm/utwig/utwigc.cpp"
)

source_group("src\\uqm\\comm\\utwig" FILES ${uqm_src_uqm_comm_utwig_files})
list(APPEND uqm_src_uqm_comm_utwig_master_files ${uqm_src_uqm_comm_utwig_files})
