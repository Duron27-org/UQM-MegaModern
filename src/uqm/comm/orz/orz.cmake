############################################################


set(uqm_src_uqm_comm_orz_master_files "")


############################################################
# Local files
set(uqm_src_uqm_comm_orz_files
	"src/uqm/comm/orz/orz.cmake"
	"src/uqm/comm/orz/orzc.cpp"
	"src/uqm/comm/orz/resinst.h"
	"src/uqm/comm/orz/strings.h"
)

source_group("src\\uqm\\comm\\orz" FILES ${uqm_src_uqm_comm_orz_files})
list(APPEND uqm_src_uqm_comm_orz_master_files ${uqm_src_uqm_comm_orz_files})
