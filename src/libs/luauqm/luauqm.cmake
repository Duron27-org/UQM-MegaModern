############################################################


set(uqm_src_libs_luauqm_master_files "")


############################################################
# Local files
set(uqm_src_libs_luauqm_files
	"src/libs/luauqm/luauqm.cmake"
	"src/libs/luauqm/luauqm.cpp"
	"src/libs/luauqm/luauqm.h"
	"src/libs/luauqm/scriptres.cpp"
	"src/libs/luauqm/scriptres.h"
)

source_group("src\\libs\\luauqm" FILES ${uqm_src_libs_luauqm_files})
list(APPEND uqm_src_libs_luauqm_master_files ${uqm_src_libs_luauqm_files})
