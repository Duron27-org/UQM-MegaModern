############################################################


set(uqm_src_uqm_comm_umgah_master_files "")


############################################################
# Local files
set(uqm_src_uqm_comm_umgah_files
	"src/uqm/comm/umgah/resinst.h"
	"src/uqm/comm/umgah/strings.h"
	"src/uqm/comm/umgah/umgah.cmake"
	"src/uqm/comm/umgah/umgahc.cpp"
)

source_group("src\\uqm\\comm\\umgah" FILES ${uqm_src_uqm_comm_umgah_files})
list(APPEND uqm_src_uqm_comm_umgah_master_files ${uqm_src_uqm_comm_umgah_files})
