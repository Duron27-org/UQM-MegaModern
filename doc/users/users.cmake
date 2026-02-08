############################################################


set(uqm_doc_users_master_files "")


############################################################
# Local files
set(uqm_doc_users_files
	"doc/users/manual.txt"
	"doc/users/unixinstall"
	"doc/users/uqm.6"
	"doc/users/users.cmake"
)

source_group("doc\\users" FILES ${uqm_doc_users_files})
list(APPEND uqm_doc_users_master_files ${uqm_doc_users_files})
