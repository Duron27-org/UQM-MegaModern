############################################################


set(uqm_src_libs_uio_master_files "")

############################################################
# Sub-directories
# include("src/libs/uio/doc/doc.cmake")
# list(APPEND uqm_src_libs_uio_master_files ${uqm_src_libs_uio_doc_master_files})
include("src/libs/uio/stdio/stdio.cmake")
list(APPEND uqm_src_libs_uio_master_files ${uqm_src_libs_uio_stdio_master_files})
include("src/libs/uio/zip/zip.cmake")
list(APPEND uqm_src_libs_uio_master_files ${uqm_src_libs_uio_zip_master_files})

############################################################
# Local files
set(uqm_src_libs_uio_files
#	"src/libs/uio/COPYING"
	"src/libs/uio/charhashtable.cpp"
	"src/libs/uio/charhashtable.h"
	"src/libs/uio/debug.cpp"
	"src/libs/uio/debug.h"
	"src/libs/uio/defaultfs.cpp"
	"src/libs/uio/defaultfs.h"
	"src/libs/uio/fileblock.cpp"
	"src/libs/uio/fileblock.h"
	"src/libs/uio/fstypes.cpp"
	"src/libs/uio/fstypes.h"
	"src/libs/uio/getint.h"
	"src/libs/uio/gphys.cpp"
	"src/libs/uio/gphys.h"
	"src/libs/uio/hashtable.cpp"
	"src/libs/uio/hashtable.h"
	"src/libs/uio/io.cpp"
	"src/libs/uio/io.h"
	"src/libs/uio/ioaux.cpp"
	"src/libs/uio/ioaux.h"
	"src/libs/uio/iointrn.h"
	"src/libs/uio/match.cpp"
	"src/libs/uio/match.h"
	"src/libs/uio/mem.h"
	"src/libs/uio/memdebug.cpp"
	"src/libs/uio/memdebug.h"
	"src/libs/uio/mount.cpp"
	"src/libs/uio/mount.h"
	"src/libs/uio/mounttree.cpp"
	"src/libs/uio/mounttree.h"
	"src/libs/uio/paths.cpp"
	"src/libs/uio/paths.h"
	"src/libs/uio/physical.cpp"
	"src/libs/uio/physical.h"
	"src/libs/uio/types.h"
	"src/libs/uio/uio.cmake"
	"src/libs/uio/uioport.h"
	"src/libs/uio/uiostream.cpp"
	"src/libs/uio/uiostream.h"
	"src/libs/uio/uioutils.cpp"
	"src/libs/uio/uioutils.h"
	"src/libs/uio/utils.cpp"
	"src/libs/uio/utils.h"
)

source_group("src\\libs\\uio" FILES ${uqm_src_libs_uio_files})
list(APPEND uqm_src_libs_uio_master_files ${uqm_src_libs_uio_files})
