############################################################


set(uqm_src_libs_list_master_files "")


############################################################
# Local files
set(uqm_src_libs_list_files
	"src/libs/list/list.cmake"
	"src/libs/list/list.cpp"
	"src/libs/list/list.h"
)

source_group("src\\libs\\list" FILES ${uqm_src_libs_list_files})
list(APPEND uqm_src_libs_list_master_files ${uqm_src_libs_list_files})
