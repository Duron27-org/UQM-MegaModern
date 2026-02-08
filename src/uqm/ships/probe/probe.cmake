############################################################


set(uqm_src_uqm_ships_probe_master_files "")


############################################################
# Local files
set(uqm_src_uqm_ships_probe_files
	"src/uqm/ships/probe/icode.h"
	"src/uqm/ships/probe/probe.cmake"
	"src/uqm/ships/probe/probe.cpp"
	"src/uqm/ships/probe/probe.h"
	"src/uqm/ships/probe/resinst.h"
)

source_group("src\\uqm\\ships\\probe" FILES ${uqm_src_uqm_ships_probe_files})
list(APPEND uqm_src_uqm_ships_probe_master_files ${uqm_src_uqm_ships_probe_files})
