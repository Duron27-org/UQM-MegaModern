############################################################


set(uqm_src_libs_sound_mixer_master_files "")

############################################################
# Sub-directories
include("src/libs/sound/mixer/nosound/nosound.cmake")
list(APPEND uqm_src_libs_sound_mixer_master_files ${uqm_src_libs_sound_mixer_nosound_master_files})
include("src/libs/sound/mixer/sdl/sdl.cmake")
list(APPEND uqm_src_libs_sound_mixer_master_files ${uqm_src_libs_sound_mixer_sdl_master_files})

############################################################
# Local files
set(uqm_src_libs_sound_mixer_files
	"src/libs/sound/mixer/mixer.cmake"
	"src/libs/sound/mixer/mixer.cpp"
	"src/libs/sound/mixer/mixer.h"
	"src/libs/sound/mixer/mixerint.h"
)

source_group("src\\libs\\sound\\mixer" FILES ${uqm_src_libs_sound_mixer_files})
list(APPEND uqm_src_libs_sound_mixer_master_files ${uqm_src_libs_sound_mixer_files})
