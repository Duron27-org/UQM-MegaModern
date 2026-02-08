############################################################


set(uqm_src_libs_sound_decoders_master_files "")


############################################################
# Local files
set(uqm_src_libs_sound_decoders_files
	"src/libs/sound/decoders/aiffaud.cpp"
	"src/libs/sound/decoders/aiffaud.h"
	"src/libs/sound/decoders/decoder.cpp"
	"src/libs/sound/decoders/decoder.h"
	"src/libs/sound/decoders/decoders.cmake"
	"src/libs/sound/decoders/dukaud.cpp"
	"src/libs/sound/decoders/dukaud.h"
	"src/libs/sound/decoders/modaud.cpp"
	"src/libs/sound/decoders/modaud.h"
	"src/libs/sound/decoders/oggaud.cpp"
	"src/libs/sound/decoders/oggaud.h"
	"src/libs/sound/decoders/wav.cpp"
	"src/libs/sound/decoders/wav.h"
)

source_group("src\\libs\\sound\\decoders" FILES ${uqm_src_libs_sound_decoders_files})
list(APPEND uqm_src_libs_sound_decoders_master_files ${uqm_src_libs_sound_decoders_files})
