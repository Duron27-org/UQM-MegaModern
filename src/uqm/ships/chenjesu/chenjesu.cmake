############################################################


set(uqm_src_uqm_ships_chenjesu_master_files "")


############################################################
# Local files
set(uqm_src_uqm_ships_chenjesu_files
	"src/uqm/ships/chenjesu/chenjesu.cmake"
	"src/uqm/ships/chenjesu/chenjesu.cpp"
	"src/uqm/ships/chenjesu/chenjesu.h"
	"src/uqm/ships/chenjesu/icode.h"
	"src/uqm/ships/chenjesu/resinst.h"
)

source_group("src\\uqm\\ships\\chenjesu" FILES ${uqm_src_uqm_ships_chenjesu_files})
list(APPEND uqm_src_uqm_ships_chenjesu_master_files ${uqm_src_uqm_ships_chenjesu_files})
