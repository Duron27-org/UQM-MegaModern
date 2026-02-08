############################################################


set(uqm_src_libs_threads_master_files "")

############################################################
# Sub-directories
# include("src/libs/threads/pthread/pthread.cmake")
# list(APPEND uqm_src_libs_threads_master_files ${uqm_src_libs_threads_pthread_master_files})
include("src/libs/threads/sdl/sdl.cmake")
list(APPEND uqm_src_libs_threads_master_files ${uqm_src_libs_threads_sdl_master_files})

############################################################
# Local files
set(uqm_src_libs_threads_files
	"src/libs/threads/thrcommon.cpp"
	"src/libs/threads/thrcommon.h"
	"src/libs/threads/threads.cmake"
)

source_group("src\\libs\\threads" FILES ${uqm_src_libs_threads_files})
list(APPEND uqm_src_libs_threads_master_files ${uqm_src_libs_threads_files})
