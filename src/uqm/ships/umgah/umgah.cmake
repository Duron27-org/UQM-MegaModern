############################################################


set(uqm_src_uqm_ships_umgah_master_files "")


############################################################
# Local files
set(uqm_src_uqm_ships_umgah_files
	"src/uqm/ships/umgah/icode.h"
	"src/uqm/ships/umgah/resinst.h"
	"src/uqm/ships/umgah/umgah.cmake"
	"src/uqm/ships/umgah/umgah.cpp"
	"src/uqm/ships/umgah/umgah.h"
)

source_group("src\\uqm\\ships\\umgah" FILES ${uqm_src_uqm_ships_umgah_files})
list(APPEND uqm_src_uqm_ships_umgah_master_files ${uqm_src_uqm_ships_umgah_files})
