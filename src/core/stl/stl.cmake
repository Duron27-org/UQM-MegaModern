############################################################


set(uqm_src_core_stl_master_files "")


############################################################
# Local files
set(uqm_src_core_stl_files
	"src/core/stl/array.h"
	"src/core/stl/map.h"
	"src/core/stl/memory.h"
	"src/core/stl/optional.h"
	"src/core/stl/ring_buffer.h"
	"src/core/stl/stl.cmake"
	"src/core/stl/stl.cpp"
	"src/core/stl/stl.h"
	"src/core/stl/string.h"
	"src/core/stl/vector.h"
)

source_group("src\\core\\stl" FILES ${uqm_src_core_stl_files})
list(APPEND uqm_src_core_stl_master_files ${uqm_src_core_stl_files})
