############################################################


set(uqm_src_libs_log_master_files "")


############################################################
# Local files
set(uqm_src_libs_log_files
	"src/libs/log/log.cmake"
	"src/libs/log/loginternal.h"
	"src/libs/log/msgbox.h"
#	"src/libs/log/msgbox_macosx.m"
#	"src/libs/log/msgbox_stub.cpp"
	"src/libs/log/msgbox_win.cpp"
	"src/libs/log/uqmlog.cpp"
	"src/libs/log/uqmlog.h"
)

source_group("src\\libs\\log" FILES ${uqm_src_libs_log_files})
list(APPEND uqm_src_libs_log_master_files ${uqm_src_libs_log_files})
