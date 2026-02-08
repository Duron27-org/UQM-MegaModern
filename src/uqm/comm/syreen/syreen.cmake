############################################################


set(uqm_src_uqm_comm_syreen_master_files "")


############################################################
# Local files
set(uqm_src_uqm_comm_syreen_files
	"src/uqm/comm/syreen/resinst.h"
	"src/uqm/comm/syreen/strings.h"
	"src/uqm/comm/syreen/syreen.cmake"
	"src/uqm/comm/syreen/syreenc.cpp"
)

source_group("src\\uqm\\comm\\syreen" FILES ${uqm_src_uqm_comm_syreen_files})
list(APPEND uqm_src_uqm_comm_syreen_master_files ${uqm_src_uqm_comm_syreen_files})
