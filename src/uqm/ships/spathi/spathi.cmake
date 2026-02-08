############################################################


set(uqm_src_uqm_ships_spathi_master_files "")


############################################################
# Local files
set(uqm_src_uqm_ships_spathi_files
	"src/uqm/ships/spathi/icode.h"
	"src/uqm/ships/spathi/resinst.h"
	"src/uqm/ships/spathi/spathi.cmake"
	"src/uqm/ships/spathi/spathi.cpp"
	"src/uqm/ships/spathi/spathi.h"
)

source_group("src\\uqm\\ships\\spathi" FILES ${uqm_src_uqm_ships_spathi_files})
list(APPEND uqm_src_uqm_ships_spathi_master_files ${uqm_src_uqm_ships_spathi_files})
