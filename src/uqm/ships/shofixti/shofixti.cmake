############################################################


set(uqm_src_uqm_ships_shofixti_master_files "")


############################################################
# Local files
set(uqm_src_uqm_ships_shofixti_files
	"src/uqm/ships/shofixti/icode.h"
	"src/uqm/ships/shofixti/resinst.h"
	"src/uqm/ships/shofixti/shofixti.cmake"
	"src/uqm/ships/shofixti/shofixti.cpp"
	"src/uqm/ships/shofixti/shofixti.h"
)

source_group("src\\uqm\\ships\\shofixti" FILES ${uqm_src_uqm_ships_shofixti_files})
list(APPEND uqm_src_uqm_ships_shofixti_master_files ${uqm_src_uqm_ships_shofixti_files})
