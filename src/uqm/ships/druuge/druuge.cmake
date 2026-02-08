############################################################


set(uqm_src_uqm_ships_druuge_master_files "")


############################################################
# Local files
set(uqm_src_uqm_ships_druuge_files
	"src/uqm/ships/druuge/druuge.cmake"
	"src/uqm/ships/druuge/druuge.cpp"
	"src/uqm/ships/druuge/druuge.h"
	"src/uqm/ships/druuge/icode.h"
	"src/uqm/ships/druuge/resinst.h"
)

source_group("src\\uqm\\ships\\druuge" FILES ${uqm_src_uqm_ships_druuge_files})
list(APPEND uqm_src_uqm_ships_druuge_master_files ${uqm_src_uqm_ships_druuge_files})
