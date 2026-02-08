############################################################


set(uqm_src_uqm_ships_lastbat_master_files "")


############################################################
# Local files
set(uqm_src_uqm_ships_lastbat_files
	"src/uqm/ships/lastbat/icode.h"
	"src/uqm/ships/lastbat/lastbat.cmake"
	"src/uqm/ships/lastbat/lastbat.cpp"
	"src/uqm/ships/lastbat/lastbat.h"
	"src/uqm/ships/lastbat/resinst.h"
)

source_group("src\\uqm\\ships\\lastbat" FILES ${uqm_src_uqm_ships_lastbat_files})
list(APPEND uqm_src_uqm_ships_lastbat_master_files ${uqm_src_uqm_ships_lastbat_files})
