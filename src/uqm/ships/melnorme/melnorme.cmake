############################################################


set(uqm_src_uqm_ships_melnorme_master_files "")


############################################################
# Local files
set(uqm_src_uqm_ships_melnorme_files
	"src/uqm/ships/melnorme/icode.h"
	"src/uqm/ships/melnorme/melnorme.cmake"
	"src/uqm/ships/melnorme/melnorme.cpp"
	"src/uqm/ships/melnorme/melnorme.h"
	"src/uqm/ships/melnorme/resinst.h"
)

source_group("src\\uqm\\ships\\melnorme" FILES ${uqm_src_uqm_ships_melnorme_files})
list(APPEND uqm_src_uqm_ships_melnorme_master_files ${uqm_src_uqm_ships_melnorme_files})
