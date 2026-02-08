############################################################


set(uqm_src_uqm_comm_starbas_master_files "")


############################################################
# Local files
set(uqm_src_uqm_comm_starbas_files
	"src/uqm/comm/starbas/starbas.cmake"
	"src/uqm/comm/starbas/starbas.cpp"
	"src/uqm/comm/starbas/strings.h"
)

source_group("src\\uqm\\comm\\starbas" FILES ${uqm_src_uqm_comm_starbas_files})
list(APPEND uqm_src_uqm_comm_starbas_master_files ${uqm_src_uqm_comm_starbas_files})
