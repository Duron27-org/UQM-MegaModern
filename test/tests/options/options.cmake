############################################################


set(uqm_tests_options_master_files "")

list(APPEND uqm_tests_options_master_files 
	"../src/options/OptionDefs.h"
	"../src/options/OptionTypes.h"
	"../src/options/options.h"
)

############################################################
# Local files
set(uqm_tests_options_files
	"tests/options/options.cmake"
	"tests/options/testOptions.cpp"
)

source_group("tests\\options" FILES ${uqm_tests_options_files})
list(APPEND uqm_tests_options_master_files ${uqm_tests_options_files})
