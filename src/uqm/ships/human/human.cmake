############################################################


set(uqm_src_uqm_ships_human_master_files "")


############################################################
# Local files
set(uqm_src_uqm_ships_human_files
	"src/uqm/ships/human/human.cmake"
	"src/uqm/ships/human/human.cpp"
	"src/uqm/ships/human/human.h"
	"src/uqm/ships/human/icode.h"
	"src/uqm/ships/human/resinst.h"
)

source_group("src\\uqm\\ships\\human" FILES ${uqm_src_uqm_ships_human_files})
list(APPEND uqm_src_uqm_ships_human_master_files ${uqm_src_uqm_ships_human_files})
