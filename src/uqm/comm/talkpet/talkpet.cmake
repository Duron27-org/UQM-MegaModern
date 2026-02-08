############################################################


set(uqm_src_uqm_comm_talkpet_master_files "")


############################################################
# Local files
set(uqm_src_uqm_comm_talkpet_files
	"src/uqm/comm/talkpet/resinst.h"
	"src/uqm/comm/talkpet/strings.h"
	"src/uqm/comm/talkpet/talkpet.cmake"
	"src/uqm/comm/talkpet/talkpet.cpp"
)

source_group("src\\uqm\\comm\\talkpet" FILES ${uqm_src_uqm_comm_talkpet_files})
list(APPEND uqm_src_uqm_comm_talkpet_master_files ${uqm_src_uqm_comm_talkpet_files})
