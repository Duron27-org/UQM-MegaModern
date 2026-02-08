############################################################


set(uqm_doc_release_master_files "")


############################################################
# Local files
set(uqm_doc_release_files
	"doc/release/AUTHORS.txt"
	"doc/release/CHANGELOG.txt"
	"doc/release/COPYING.txt"
	"doc/release/MegaMod-README.txt"
	"doc/release/README-SDL.txt"
	"doc/release/UQM-Manual.txt"
	"doc/release/UQM-README.txt"
	"doc/release/release.cmake"
)

source_group("doc\\release" FILES ${uqm_doc_release_files})
list(APPEND uqm_doc_release_master_files ${uqm_doc_release_files})
