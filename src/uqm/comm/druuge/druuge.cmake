############################################################


set(uqm_src_uqm_comm_druuge_master_files "")


############################################################
# Local files
set(uqm_src_uqm_comm_druuge_files
	"src/uqm/comm/druuge/druuge.cmake"
	"src/uqm/comm/druuge/druugec.cpp"
	"src/uqm/comm/druuge/resinst.h"
	"src/uqm/comm/druuge/strings.h"
)

source_group("src\\uqm\\comm\\druuge" FILES ${uqm_src_uqm_comm_druuge_files})
list(APPEND uqm_src_uqm_comm_druuge_master_files ${uqm_src_uqm_comm_druuge_files})
