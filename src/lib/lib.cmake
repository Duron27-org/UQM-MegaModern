############################################################


set(uqm_src_lib_master_files "")

############################################################
# Sub-directories
include("src/lib/Math2D/Math2D.cmake")
list(APPEND uqm_src_lib_master_files ${uqm_src_lib_Math2D_master_files})

############################################################
# Local files
set(uqm_src_lib_files
	"src/lib/lib.cmake"
)

source_group("src\\lib" FILES ${uqm_src_lib_files})
list(APPEND uqm_src_lib_master_files ${uqm_src_lib_files})
