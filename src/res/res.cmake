############################################################


set(uqm_src_res_master_files "")

############################################################
# Sub-directories
# include("src/res/darwin/darwin.cmake")
# list(APPEND uqm_src_res_master_files ${uqm_src_res_darwin_master_files})

############################################################
# Local files
set(uqm_src_res_files
#	"src/res/UrQuanMasters.rc"
#	"src/res/kohr-ah.ico"
	"src/res/kohr-ah1.ico"
#	"src/res/megamod.desktop"
#	"src/res/megamod.png"
	"src/res/res.cmake"
	"src/res/sis1.ico"
	"src/res/starcon2.ico"
#	"src/res/ur-quan-icon-24-hover-alpha.ico"
#	"src/res/ur-quan-icon-24-hover.ico"
	"src/res/ur-quan-icon-alpha.ico"
	"src/res/ur-quan-icon-std.ico"
	"src/res/ur-quan1.ico"
	"src/res/ur-quan2.ico"
)

source_group("src\\res" FILES ${uqm_src_res_files})
list(APPEND uqm_src_res_master_files ${uqm_src_res_files})
