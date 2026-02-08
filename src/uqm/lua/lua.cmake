############################################################


set(uqm_src_uqm_lua_master_files "")

############################################################
# Sub-directories
include("src/uqm/lua/luafuncs/luafuncs.cmake")
list(APPEND uqm_src_uqm_lua_master_files ${uqm_src_uqm_lua_luafuncs_master_files})

############################################################
# Local files
set(uqm_src_uqm_lua_files
	"src/uqm/lua/lua.cmake"
	"src/uqm/lua/luacomm.cpp"
	"src/uqm/lua/luacomm.h"
	"src/uqm/lua/luadebug.cpp"
	"src/uqm/lua/luadebug.h"
	"src/uqm/lua/luaevent.cpp"
	"src/uqm/lua/luaevent.h"
	"src/uqm/lua/luainit.cpp"
	"src/uqm/lua/luainit.h"
	"src/uqm/lua/luastate.cpp"
	"src/uqm/lua/luastate.h"
)

source_group("src\\uqm\\lua" FILES ${uqm_src_uqm_lua_files})
list(APPEND uqm_src_uqm_lua_master_files ${uqm_src_uqm_lua_files})
