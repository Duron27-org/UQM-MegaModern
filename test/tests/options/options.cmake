############################################################


set(uqm_tests_options_master_files "")

include("../src/core/string/string.cmake")
list(APPEND uqm_tests_options_master_files 
	"../src/options/OptionTypes.h"
	"../src/options/OptionTypes.cpp"
)

############################################################
# Local files
set(uqm_tests_options_files
	"tests/options/testOptions.cpp"
)

source_group("tests\\options" FILES ${uqm_tests_options_files})
list(APPEND uqm_tests_options_master_files ${uqm_tests_options_files})
