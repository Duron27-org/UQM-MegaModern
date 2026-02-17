############################################################


set(uqm_src_lib_Math2D_master_files "")


############################################################
# Local files
set(uqm_src_lib_Math2D_files
	"src/lib/Math2D/Math2D.cmake"
	"src/lib/Math2D/Math2D.cpp"
	"src/lib/Math2D/Math2D.h"
	"src/lib/Math2D/Math2DStringUtils.cpp"
	"src/lib/Math2D/Math2DStringUtils.h"
)

source_group("src\\lib\\Math2D" FILES ${uqm_src_lib_Math2D_files})
list(APPEND uqm_src_lib_Math2D_master_files ${uqm_src_lib_Math2D_files})
