############################################################


set(uqm_src_uqm_ships_ilwrath_master_files "")


############################################################
# Local files
set(uqm_src_uqm_ships_ilwrath_files
	"src/uqm/ships/ilwrath/icode.h"
	"src/uqm/ships/ilwrath/ilwrath.cmake"
	"src/uqm/ships/ilwrath/ilwrath.cpp"
	"src/uqm/ships/ilwrath/ilwrath.h"
	"src/uqm/ships/ilwrath/resinst.h"
)

source_group("src\\uqm\\ships\\ilwrath" FILES ${uqm_src_uqm_ships_ilwrath_files})
list(APPEND uqm_src_uqm_ships_ilwrath_master_files ${uqm_src_uqm_ships_ilwrath_files})
