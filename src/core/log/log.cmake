############################################################


set(uqm_src_core_log_master_files "")

############################################################
# Sub-directories
include("src/core/log/msgbox/msgbox.cmake")
list(APPEND uqm_src_core_log_master_files ${uqm_src_core_log_msgbox_master_files})

############################################################
# Local files
set(uqm_src_core_log_files
	"src/core/log/BacktraceCaptureSink.cpp"
	"src/core/log/BacktraceCaptureSink.h"
	"src/core/log/log.cmake"
	"src/core/log/log.cpp"
	"src/core/log/log.h"
	"src/core/log/logger.cpp"
	"src/core/log/logger.h"
)

source_group("src\\core\\log" FILES ${uqm_src_core_log_files})
list(APPEND uqm_src_core_log_master_files ${uqm_src_core_log_files})
