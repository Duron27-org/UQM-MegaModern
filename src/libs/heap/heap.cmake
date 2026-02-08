############################################################


set(uqm_src_libs_heap_master_files "")


############################################################
# Local files
set(uqm_src_libs_heap_files
	"src/libs/heap/heap.cmake"
	"src/libs/heap/heap.cpp"
	"src/libs/heap/heap.h"
)

source_group("src\\libs\\heap" FILES ${uqm_src_libs_heap_files})
list(APPEND uqm_src_libs_heap_master_files ${uqm_src_libs_heap_files})
