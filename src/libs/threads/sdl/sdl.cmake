############################################################


set(uqm_src_libs_threads_sdl_master_files "")


############################################################
# Local files
set(uqm_src_libs_threads_sdl_files
	"src/libs/threads/sdl/sdl.cmake"
	"src/libs/threads/sdl/sdlthreads.cpp"
	"src/libs/threads/sdl/sdlthreads.h"
)

source_group("src\\libs\\threads\\sdl" FILES ${uqm_src_libs_threads_sdl_files})
list(APPEND uqm_src_libs_threads_sdl_master_files ${uqm_src_libs_threads_sdl_files})
