############################################################


set(uqm_src_core_platform_master_files "")


############################################################
# Local files
set(uqm_src_core_platform_files
	"src/core/platform/platform.h"
#	"src/core/platform/platform_win.cpp"
)

source_group("src\\core\\platform" FILES ${uqm_src_core_platform_files})
list(APPEND uqm_src_core_platform_master_files ${uqm_src_core_platform_files})
