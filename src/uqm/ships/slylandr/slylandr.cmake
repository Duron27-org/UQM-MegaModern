############################################################


set(uqm_src_uqm_ships_slylandr_master_files "")


############################################################
# Local files
set(uqm_src_uqm_ships_slylandr_files
	"src/uqm/ships/slylandr/icode.h"
	"src/uqm/ships/slylandr/resinst.h"
	"src/uqm/ships/slylandr/slylandr.cmake"
	"src/uqm/ships/slylandr/slylandr.cpp"
	"src/uqm/ships/slylandr/slylandr.h"
)

source_group("src\\uqm\\ships\\slylandr" FILES ${uqm_src_uqm_ships_slylandr_files})
list(APPEND uqm_src_uqm_ships_slylandr_master_files ${uqm_src_uqm_ships_slylandr_files})
