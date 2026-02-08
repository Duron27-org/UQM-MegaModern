############################################################


set(uqm_src_libs_cdp_master_files "")


############################################################
# Local files
set(uqm_src_libs_cdp_files
	"src/libs/cdp/cdp.cmake"
#	"src/libs/cdp/cdp.cpp"
#	"src/libs/cdp/cdp.h"
#	"src/libs/cdp/cdp_alli.h"
#	"src/libs/cdp/cdp_iio.h"
#	"src/libs/cdp/cdp_imem.h"
#	"src/libs/cdp/cdp_isnd.h"
#	"src/libs/cdp/cdp_ivid.h"
#	"src/libs/cdp/cdpapi.cpp"
#	"src/libs/cdp/cdpapi.h"
#	"src/libs/cdp/cdpint.h"
#	"src/libs/cdp/cdpmod.h"
#	"src/libs/cdp/windl.cpp"
#	"src/libs/cdp/windl.h"
)

source_group("src\\libs\\cdp" FILES ${uqm_src_libs_cdp_files})
list(APPEND uqm_src_libs_cdp_master_files ${uqm_src_libs_cdp_files})
