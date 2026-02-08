############################################################


set(uqm_src_core_memory_master_files "")


############################################################
# Local files
set(uqm_src_core_memory_files
	"src/core/memory/memory.cmake"
	"src/core/memory/memory.h"
)

source_group("src\\core\\memory" FILES ${uqm_src_core_memory_files})
list(APPEND uqm_src_core_memory_master_files ${uqm_src_core_memory_files})
