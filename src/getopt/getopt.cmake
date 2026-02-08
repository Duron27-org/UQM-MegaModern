############################################################


set(uqm_src_getopt_master_files "")


############################################################
# Local files
set(uqm_src_getopt_files
	"src/getopt/getopt.cmake"
	"src/getopt/getopt.cpp"
	"src/getopt/getopt.h"
	"src/getopt/getopt1.cpp"
)

source_group("src\\getopt" FILES ${uqm_src_getopt_files})
list(APPEND uqm_src_getopt_master_files ${uqm_src_getopt_files})
