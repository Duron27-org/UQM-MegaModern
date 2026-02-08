############################################################


set(uqm_src_libs_input_sdl_master_files "")


############################################################
# Local files
set(uqm_src_libs_input_sdl_files
	"src/libs/input/sdl/input.cpp"
	"src/libs/input/sdl/input.h"
	"src/libs/input/sdl/keynames.cpp"
	"src/libs/input/sdl/keynames.h"
	"src/libs/input/sdl/sdl.cmake"
	"src/libs/input/sdl/vcontrol.cpp"
	"src/libs/input/sdl/vcontrol.h"
)

source_group("src\\libs\\input\\sdl" FILES ${uqm_src_libs_input_sdl_files})
list(APPEND uqm_src_libs_input_sdl_master_files ${uqm_src_libs_input_sdl_files})
