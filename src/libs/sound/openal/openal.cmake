############################################################


set(uqm_src_libs_sound_openal_master_files "")


############################################################
# Local files
set(uqm_src_libs_sound_openal_files
	"src/libs/sound/openal/audiodrv_openal.cpp"
	"src/libs/sound/openal/audiodrv_openal.h"
	"src/libs/sound/openal/openal.cmake"
)

source_group("src\\libs\\sound\\openal" FILES ${uqm_src_libs_sound_openal_files})
list(APPEND uqm_src_libs_sound_openal_master_files ${uqm_src_libs_sound_openal_files})
