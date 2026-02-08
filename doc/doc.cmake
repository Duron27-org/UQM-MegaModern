############################################################


set(uqm_doc_master_files "")

############################################################
# Sub-directories
include("doc/devel/devel.cmake")
list(APPEND uqm_doc_master_files ${uqm_doc_devel_master_files})
include("doc/fonts/fonts.cmake")
list(APPEND uqm_doc_master_files ${uqm_doc_fonts_master_files})
include("doc/release/release.cmake")
list(APPEND uqm_doc_master_files ${uqm_doc_release_master_files})
include("doc/users/users.cmake")
list(APPEND uqm_doc_master_files ${uqm_doc_users_master_files})

############################################################
# Local files
set(uqm_doc_files
	"doc/doc.cmake"
)

source_group("doc" FILES ${uqm_doc_files})
list(APPEND uqm_doc_master_files ${uqm_doc_files})
