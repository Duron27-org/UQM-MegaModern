############################################################


set(uqm_src_uqm_supermelee_netplay_proto_master_files "")


############################################################
# Local files
set(uqm_src_uqm_supermelee_netplay_proto_files
	"src/uqm/supermelee/netplay/proto/npconfirm.cpp"
	"src/uqm/supermelee/netplay/proto/npconfirm.h"
	"src/uqm/supermelee/netplay/proto/proto.cmake"
	"src/uqm/supermelee/netplay/proto/ready.cpp"
	"src/uqm/supermelee/netplay/proto/ready.h"
	"src/uqm/supermelee/netplay/proto/reset.cpp"
	"src/uqm/supermelee/netplay/proto/reset.h"
)

source_group("src\\uqm\\supermelee\\netplay\\proto" FILES ${uqm_src_uqm_supermelee_netplay_proto_files})
list(APPEND uqm_src_uqm_supermelee_netplay_proto_master_files ${uqm_src_uqm_supermelee_netplay_proto_files})
