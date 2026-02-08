############################################################


set(uqm_src_uqm_comm_shofixt_master_files "")


############################################################
# Local files
set(uqm_src_uqm_comm_shofixt_files
	"src/uqm/comm/shofixt/resinst.h"
	"src/uqm/comm/shofixt/shofixt.cmake"
	"src/uqm/comm/shofixt/shofixt.cpp"
	"src/uqm/comm/shofixt/strings.h"
)

source_group("src\\uqm\\comm\\shofixt" FILES ${uqm_src_uqm_comm_shofixt_files})
list(APPEND uqm_src_uqm_comm_shofixt_master_files ${uqm_src_uqm_comm_shofixt_files})
