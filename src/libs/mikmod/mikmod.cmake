############################################################


set(uqm_src_libs_mikmod_master_files "")


############################################################
# Local files
set(uqm_src_libs_mikmod_files
#	"src/libs/mikmod/AUTHORS"
#	"src/libs/mikmod/README"
	"src/libs/mikmod/drv_nos.cpp"
	"src/libs/mikmod/load_it.cpp"
	"src/libs/mikmod/load_mod.cpp"
	"src/libs/mikmod/load_s3m.cpp"
	"src/libs/mikmod/load_stm.cpp"
	"src/libs/mikmod/load_xm.cpp"
	"src/libs/mikmod/mdreg.cpp"
	"src/libs/mikmod/mdriver.cpp"
#	"src/libs/mikmod/mdulaw.cpp"
	"src/libs/mikmod/mikmod.cmake"
	"src/libs/mikmod/mikmod.h"
	"src/libs/mikmod/mikmod_build.h"
#	"src/libs/mikmod/mikmod_ctype.h"
	"src/libs/mikmod/mikmod_internals.h"
	"src/libs/mikmod/mloader.cpp"
	"src/libs/mikmod/mlreg.cpp"
	"src/libs/mikmod/mlutil.cpp"
	"src/libs/mikmod/mmalloc.cpp"
	"src/libs/mikmod/mmerror.cpp"
	"src/libs/mikmod/mmio.cpp"
	"src/libs/mikmod/mplayer.cpp"
	"src/libs/mikmod/munitrk.cpp"
	"src/libs/mikmod/mwav.cpp"
	"src/libs/mikmod/npertab.cpp"
	"src/libs/mikmod/sloader.cpp"
	"src/libs/mikmod/virtch.cpp"
	"src/libs/mikmod/virtch2.cpp"
	"src/libs/mikmod/virtch_common.cpp"
)

source_group("src\\libs\\mikmod" FILES ${uqm_src_libs_mikmod_files})
list(APPEND uqm_src_libs_mikmod_master_files ${uqm_src_libs_mikmod_files})
