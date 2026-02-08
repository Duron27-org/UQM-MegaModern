############################################################


set(uqm_src_libs_callback_master_files "")


############################################################
# Local files
set(uqm_src_libs_callback_files
	"src/libs/callback/alarm.cpp"
	"src/libs/callback/alarm.h"
	"src/libs/callback/async.cpp"
	"src/libs/callback/async.h"
	"src/libs/callback/callback.cmake"
	"src/libs/callback/callback.cpp"
	"src/libs/callback/callback.h"
)

source_group("src\\libs\\callback" FILES ${uqm_src_libs_callback_files})
list(APPEND uqm_src_libs_callback_master_files ${uqm_src_libs_callback_files})
