############################################################


set(uqm_src_libs_uio_stdio_master_files "")


############################################################
# Local files
set(uqm_src_libs_uio_stdio_files
	"src/libs/uio/stdio/stdio.cmake"
	"src/libs/uio/stdio/stdio.cpp"
	"src/libs/uio/stdio/stdio.h"
)

source_group("src\\libs\\uio\\stdio" FILES ${uqm_src_libs_uio_stdio_files})
list(APPEND uqm_src_libs_uio_stdio_master_files ${uqm_src_libs_uio_stdio_files})
