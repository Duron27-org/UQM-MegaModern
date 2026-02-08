############################################################


set(uqm_src_libs_md5_master_files "")


############################################################
# Local files
set(uqm_src_libs_md5_files
#	"src/libs/md5/README"
	"src/libs/md5/md5.cmake"
	"src/libs/md5/md5.cpp"
	"src/libs/md5/md5.h"
)

source_group("src\\libs\\md5" FILES ${uqm_src_libs_md5_files})
list(APPEND uqm_src_libs_md5_master_files ${uqm_src_libs_md5_files})
