############################################################


set(uqm_src_libs_decomp_master_files "")


############################################################
# Local files
set(uqm_src_libs_decomp_files
	"src/libs/decomp/decomp.cmake"
	"src/libs/decomp/lzdecode.cpp"
	"src/libs/decomp/lzencode.cpp"
	"src/libs/decomp/lzh.h"
	"src/libs/decomp/update.cpp"
)

source_group("src\\libs\\decomp" FILES ${uqm_src_libs_decomp_files})
list(APPEND uqm_src_libs_decomp_master_files ${uqm_src_libs_decomp_files})
