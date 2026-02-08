############################################################


set(uqm_src_res_darwin_master_files "")


############################################################
# Local files
set(uqm_src_res_darwin_files
#	"src/res/darwin/Info.plist"
#	"src/res/darwin/PkgInfo"
#	"src/res/darwin/The Ur-Quan Masters MegaMod.icns"
	"src/res/darwin/darwin.cmake"
#	"src/res/darwin/uqm.r"
)

source_group("src\\res\\darwin" FILES ${uqm_src_res_darwin_files})
list(APPEND uqm_src_res_darwin_master_files ${uqm_src_res_darwin_files})
