############################################################


set(uqm_src_libs_network_connect_master_files "")


############################################################
# Local files
set(uqm_src_libs_network_connect_files
	"src/libs/network/connect/connect.cmake"
	"src/libs/network/connect/connect.cpp"
	"src/libs/network/connect/connect.h"
	"src/libs/network/connect/listen.cpp"
	"src/libs/network/connect/listen.h"
	"src/libs/network/connect/resolve.cpp"
	"src/libs/network/connect/resolve.h"
)

source_group("src\\libs\\network\\connect" FILES ${uqm_src_libs_network_connect_files})
list(APPEND uqm_src_libs_network_connect_master_files ${uqm_src_libs_network_connect_files})
