############################################################


set(uqm_src_uqm_ships_zoqfot_master_files "")


############################################################
# Local files
set(uqm_src_uqm_ships_zoqfot_files
	"src/uqm/ships/zoqfot/icode.h"
	"src/uqm/ships/zoqfot/resinst.h"
	"src/uqm/ships/zoqfot/zoqfot.cmake"
	"src/uqm/ships/zoqfot/zoqfot.cpp"
	"src/uqm/ships/zoqfot/zoqfot.h"
)

source_group("src\\uqm\\ships\\zoqfot" FILES ${uqm_src_uqm_ships_zoqfot_files})
list(APPEND uqm_src_uqm_ships_zoqfot_master_files ${uqm_src_uqm_ships_zoqfot_files})
