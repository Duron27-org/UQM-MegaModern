############################################################


set(uqm_src_libs_uio_zip_master_files "")


############################################################
# Local files
set(uqm_src_libs_uio_zip_files
	"src/libs/uio/zip/zip.cmake"
	"src/libs/uio/zip/zip.cpp"
	"src/libs/uio/zip/zip.h"
)

source_group("src\\libs\\uio\\zip" FILES ${uqm_src_libs_uio_zip_files})
list(APPEND uqm_src_libs_uio_zip_master_files ${uqm_src_libs_uio_zip_files})
