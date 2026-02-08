############################################################


set(uqm_src_core_master_files "")

############################################################
# Sub-directories
include("src/core/memory/memory.cmake")
list(APPEND uqm_src_core_master_files ${uqm_src_core_memory_master_files})

############################################################
# Local files
set(uqm_src_core_files
	"src/core/core.cmake"
)

source_group("src\\core" FILES ${uqm_src_core_files})
list(APPEND uqm_src_core_master_files ${uqm_src_core_files})
