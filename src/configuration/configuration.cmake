############################################################


set(uqm_src_configuration_master_files "")


############################################################
# Local files
set(uqm_src_configuration_files
	"src/configuration/Configuration.cpp"
	"src/configuration/Configuration.h"
	"src/configuration/configuration.cmake"
)

source_group("src\\configuration" FILES ${uqm_src_configuration_files})
list(APPEND uqm_src_configuration_master_files ${uqm_src_configuration_files})
