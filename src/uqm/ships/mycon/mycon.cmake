############################################################


set(uqm_src_uqm_ships_mycon_master_files "")


############################################################
# Local files
set(uqm_src_uqm_ships_mycon_files
	"src/uqm/ships/mycon/icode.h"
	"src/uqm/ships/mycon/mycon.cmake"
	"src/uqm/ships/mycon/mycon.cpp"
	"src/uqm/ships/mycon/mycon.h"
	"src/uqm/ships/mycon/resinst.h"
)

source_group("src\\uqm\\ships\\mycon" FILES ${uqm_src_uqm_ships_mycon_files})
list(APPEND uqm_src_uqm_ships_mycon_master_files ${uqm_src_uqm_ships_mycon_files})
