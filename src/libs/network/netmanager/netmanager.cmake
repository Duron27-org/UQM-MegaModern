############################################################


set(uqm_src_libs_network_netmanager_master_files "")


############################################################
# Local files
set(uqm_src_libs_network_netmanager_files
	"src/libs/network/netmanager/ndesc.cpp"
	"src/libs/network/netmanager/ndesc.h"
	"src/libs/network/netmanager/ndindex.ci"
	"src/libs/network/netmanager/netmanager.cmake"
	"src/libs/network/netmanager/netmanager.h"
#	"src/libs/network/netmanager/netmanager_bsd.cpp"
#	"src/libs/network/netmanager/netmanager_bsd.h"
	"src/libs/network/netmanager/netmanager_common.ci"
	"src/libs/network/netmanager/netmanager_win.cpp"
	"src/libs/network/netmanager/netmanager_win.h"
)

source_group("src\\libs\\network\\netmanager" FILES ${uqm_src_libs_network_netmanager_files})
list(APPEND uqm_src_libs_network_netmanager_master_files ${uqm_src_libs_network_netmanager_files})
