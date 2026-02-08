############################################################


set(uqm_src_libs_uio_doc_master_files "")


############################################################
# Local files
set(uqm_src_libs_uio_doc_files
#	"src/libs/uio/doc/basics"
#	"src/libs/uio/doc/conventions"
	"src/libs/uio/doc/doc.cmake"
#	"src/libs/uio/doc/todo"
)

source_group("src\\libs\\uio\\doc" FILES ${uqm_src_libs_uio_doc_files})
list(APPEND uqm_src_libs_uio_doc_master_files ${uqm_src_libs_uio_doc_files})
