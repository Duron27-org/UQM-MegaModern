############################################################


set(uqm_src_libs_memory_master_files "")


############################################################
# Local files
set(uqm_src_libs_memory_files
	"src/libs/memory/memory.cmake"
	"src/libs/memory/w_memlib.cpp"
)

source_group("src\\libs\\memory" FILES ${uqm_src_libs_memory_files})
list(APPEND uqm_src_libs_memory_master_files ${uqm_src_libs_memory_files})
