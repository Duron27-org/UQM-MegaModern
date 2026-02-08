############################################################


set(uqm_src_libs_time_sdl_master_files "")


############################################################
# Local files
set(uqm_src_libs_time_sdl_files
	"src/libs/time/sdl/sdl.cmake"
	"src/libs/time/sdl/sdltime.cpp"
	"src/libs/time/sdl/sdltime.h"
)

source_group("src\\libs\\time\\sdl" FILES ${uqm_src_libs_time_sdl_files})
list(APPEND uqm_src_libs_time_sdl_master_files ${uqm_src_libs_time_sdl_files})
