############################################################


set(uqm_doc_devel_netplay_master_files "")


############################################################
# Local files
set(uqm_doc_devel_netplay_files
	"doc/devel/netplay/netplay.cmake"
	"doc/devel/netplay/notes"
	"doc/devel/netplay/protocol"
	"doc/devel/netplay/states"
	"doc/devel/netplay/todo"
)

source_group("doc\\devel\\netplay" FILES ${uqm_doc_devel_netplay_files})
list(APPEND uqm_doc_devel_netplay_master_files ${uqm_doc_devel_netplay_files})
