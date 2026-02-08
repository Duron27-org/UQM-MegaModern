############################################################


set(uqm_src_libs_sound_mixer_sdl_master_files "")


############################################################
# Local files
set(uqm_src_libs_sound_mixer_sdl_files
	"src/libs/sound/mixer/sdl/audiodrv_sdl.cpp"
	"src/libs/sound/mixer/sdl/audiodrv_sdl.h"
	"src/libs/sound/mixer/sdl/sdl.cmake"
)

source_group("src\\libs\\sound\\mixer\\sdl" FILES ${uqm_src_libs_sound_mixer_sdl_files})
list(APPEND uqm_src_libs_sound_mixer_sdl_master_files ${uqm_src_libs_sound_mixer_sdl_files})
